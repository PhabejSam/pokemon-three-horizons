"""Read-only PT14 final manifest, accessible script and production-table audit.

This complements native behavior tests and mapjson/link checks. It does not
simulate battle, save, inventory or field engines.
"""
import json
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[2]


def require(condition, message):
    if not condition:
        raise ValueError(message)


def validate(root=ROOT, overrides=None):
    root = Path(root)
    overrides = overrides or {}

    def read(path):
        return overrides[path] if path in overrides else (root/path).read_text(encoding='utf-8')

    def data(path):
        return json.loads(read(path))

    content = data('tools/three_horizons/chapter14_content.json')
    chapter = data('tools/three_horizons/chapter14_maps.json')
    names = data('tools/mapjson/three_horizons_maps.json')['maps']
    maps = {m['id']: m for n in names for m in [data(f'data/maps/{n}/map.json')]}
    layouts = {l['id']: l for l in data('data/layouts/layouts.json')['layouts']}
    groups = data('data/maps/map_groups.json')
    require(len(chapter) == 37, 'Missing chapter maps')
    require([m['name'] for m in chapter] == groups['gMapGroup_ThreeHorizons14'],
            'Map group differs from manifest')
    require(groups['group_order'].index('gMapGroup_ThreeHorizons14') == 76, 'Map group moved')
    require(not content['unfinishedInteractions'], 'Unfinished interactions remain')

    receipts = content['receipts']
    by_flag = {r['name']: r for r in receipts}
    require(len(receipts) == len(by_flag) == len({r['value'] for r in receipts}),
            'Duplicate receipt ownership')
    state = data('tools/three_horizons/state_manifest.json')
    owned = {**state['flags'], **state['pickups']}
    for r in receipts:
        value = owned.get(r['name'])
        require((int(value, 0) if isinstance(value, str) else value) == r['value'],
                f'Receipt state mismatch: {r["name"]}')

    # Parse label blocks once. Cross-chapter and native shared helpers are
    # followed for references; donor flag restrictions apply to authored TH14.
    paths = set(p.relative_to(root).as_posix() for p in (root/'data/scripts').rglob('*')
                if p.suffix in ('.inc', '.s'))
    paths.update(f'data/maps/{n}/scripts.inc' for n in names
                 if (root/f'data/maps/{n}/scripts.inc').is_file())
    paths.add('data/event_scripts.s')
    paths.update(p.relative_to(root).as_posix() for p in (root/'data/text').rglob('*.inc'))
    blocks = {}
    sources = {}
    for path in sorted(paths):
        text = read(path)
        sources[path] = text
        labels = list(re.finditer(r'^([A-Za-z_]\w*):{1,2}[ \t]*$', text, re.M))
        for index, match in enumerate(labels):
            end = labels[index+1].start() if index+1 < len(labels) else len(text)
            blocks[match[1]] = text[match.end():end]

    roots = set()
    pickup_owners = {}
    for index, entry in enumerate(chapter):
        require(entry['index'] == index and entry['group'] == 76, 'Map identity moved')
        require(names.count(entry['name']) == 1, f'Map missing/duplicated: {entry["name"]}')
        record = data(f'data/maps/{entry["name"]}/map.json')
        require(record['layout'] == entry['layout'], f'Wrong owned layout: {entry["name"]}')
        roots.add(entry['name']+'_MapScripts')
        for kind in ('object_events', 'coord_events', 'bg_events'):
            for event in record[kind]:
                if event.get('type') == 'clone':
                    require(event['target_map'] in maps, f'Unsafe clone: {event}')
                    target = maps[event['target_map']]
                    require(sum(o.get('local_id') == event['target_local_id']
                                for o in target['object_events']) == 1, f'Missing clone target: {event}')
                    continue
                if event.get('script'):
                    roots.add(event['script'])
                flag = event.get('flag', '0')
                require(flag == '0' or flag in by_flag or flag.startswith('FLAG_TEMP_'),
                        f'Unowned event flag: {entry["name"]}: {flag}')
                if flag.startswith('FLAG_TH14_PICKUP_'):
                    require(flag not in pickup_owners, f'Duplicate pickup source: {flag}')
                    pickup_owners[flag] = (entry['name'], [event['x'], event['y']])
                if event.get('script', '').startswith('TH14_CeladonCoinPickup_'):
                    body = blocks[event['script']]
                    flags = re.findall(r'goto_if_set (FLAG_TH14_PICKUP_\d+),', body)
                    require(len(flags) == 1, f'Invalid hidden coin handler: {event}')
                    flag = flags[0]
                    require(flag not in pickup_owners, f'Duplicate pickup source: {flag}')
                    pickup_owners[flag] = (entry['name'], [event['x'], event['y']])
        for warp in record['warp_events']:
            if warp['dest_map'] == 'MAP_DYNAMIC':
                # Exact production destinations and fallback are validated by
                # map_graph and native floor-selection tests.
                from tools.three_horizons.map_graph import dynamic_destinations
                require(warp['dest_warp_id'] == 'WARP_ID_DYNAMIC', 'Invalid dynamic warp')
                targets = dynamic_destinations(root, record['id'])
                for target, x, y in targets:
                    require(target in maps, f'Unsafe dynamic destination: {target}')
                    layout = layouts[maps[target]['layout']]
                    require(0 <= x < layout['width'] and 0 <= y < layout['height'],
                            f'Dynamic coordinates outside map: {target}')
            else:
                require(warp['dest_map'] in maps, f'Unsafe donor warp: {warp}')
                require(0 <= int(warp['dest_warp_id']) < len(maps[warp['dest_map']]['warp_events']),
                        f'Invalid destination index: {warp}')
        for connection in record['connections'] or []:
            require(connection['map'] in maps, f'Unsafe donor connection: {connection}')
    for flag, (name, coordinate) in pickup_owners.items():
        receipt = by_flag[flag]
        require(receipt['writer'] == name and receipt['coordinate'] == coordinate,
                f'Pickup owner/location mismatch: {flag}')
    expected_pickups = {r['name'] for r in receipts if r['name'].startswith('FLAG_TH14_PICKUP_')}
    require(set(pickup_owners) == expected_pickups, 'Missing pickup delivery sources')

    def references(body):
        for line in body.splitlines():
            line = line.split('@', 1)[0].strip()
            op, _, args = line.partition(' ')
            if op in ('call', 'goto', 'case', 'map_script', 'map_script_2') or op.startswith(('goto_if_', 'call_if_')):
                target = args.rsplit(',', 1)[-1].strip()
                if re.fullmatch(r'[A-Za-z_]\w*', target):
                    yield target
            elif op in ('msgbox', 'message', 'applymovement'):
                args = args.split(',')
                target = args[1 if op == 'applymovement' else 0].strip()
                if re.fullmatch(r'[A-Za-z_]\w*', target):
                    yield target

    visited = set()
    pending = list(roots)
    # These texts are C-defined, linked native resources rather than script blocks.
    c_labels = set()
    for path in (root/'src').glob('*.c'):
        c_labels.update(re.findall(r'\b(?:u8|u16)\s+(\w+)\[\]\s*=', path.read_text(encoding='utf-8')))
    while pending:
        label = pending.pop()
        if label in visited:
            continue
        visited.add(label)
        if label in c_labels:
            continue
        require(label in blocks, f'Unresolved accessible handler/resource: {label}')
        body = blocks[label]
        if label.startswith('TH14_'):
            require(not re.search(r'Please wait a moment|TODO|PLACEHOLDER', body),
                    f'Accessible placeholder: {label}')
            if label in roots and not label.endswith('_MapScripts'):
                commands = [l.strip() for l in body.splitlines() if l.strip() and not l.lstrip().startswith('@')]
                require(commands not in (['end'], ['return']), f'Empty accessible handler: {label}')
        pending.extend(references(body))

    authored = '\n'.join(text for p, text in sources.items()
                         if '/chapter14_' in p or '/TH14_' in p)
    # Native badge, standard flag 0 and temporary field state are intentional.
    allowed_writes = set(owned) | {'FLAG_BADGE04_GET'}
    for flag in re.findall(r'^\s*(?:setflag|clearflag)\s+(FLAG_\w+)', authored, re.M):
        require(flag in allowed_writes or flag.startswith('FLAG_TEMP_'), f'Unsafe donor flag write: {flag}')
    for target in re.findall(r'^\s*(?:warp|setwarp|setdynamicwarp|setescapewarp)\s+(MAP_\w+)', authored, re.M):
        require(target in maps, f'Unsafe scripted warp: {target}')

    unique_source = read('src/three_horizons_chapter14.c').split('sUniqueItems[] =', 1)[1].split('};', 1)[0]
    production_unique = re.findall(r'\{(ITEM_\w+), (FLAG_\w+)\}', unique_source)
    declared_unique = [(r['item'], r['receipt']) for r in content['uniqueItems']]
    require(len(declared_unique) == len(set(declared_unique)), 'Duplicate unique gift')
    require(set(declared_unique) == set(production_unique), 'Unique gift whitelist differs from manifest')
    require(all(flag in by_flag for _, flag in declared_unique), 'Unowned unique gift')

    economy = content['economy']
    require(not content['shops'] and not content['prizes'], 'Conflicting obsolete economy ledgers')
    require(economy['shops'] and economy['itemPrizes'] and economy['monPrizes'], 'Missing economy tables')
    source = read('src/data/three_horizons_celadon.h')

    def table(name, pattern):
        section = source.split(name+'[] =', 1)[1].split('};', 1)[0]
        return re.findall(pattern, section)

    shops = [(str(s['id']), str(r['minBadges']), r['item'], str(r['requiredFlag']))
             for s in economy['shops'] for r in s['stock']]
    require(table('sCeladonStock', r'\{(\d+), (\d+), ITEM_(\w+), (\w+)\}') == shops,
            'Shop stock differs from manifest')
    require(table('sCeladonItemPrizes', r'\{ITEM_(\w+), (\d+), (TRUE|FALSE)\}') ==
            [(r['item'], str(r['coins']), str(r['reusable']).upper()) for r in economy['itemPrizes']],
            'Item prizes differ from manifest')
    require(table('sCeladonMonPrizes', r'\{SPECIES_(\w+), (\d+), (\d+)\}') ==
            [(r['species'], str(r['coins']), str(r['level'])) for r in economy['monPrizes']],
            'Pokemon prizes differ from manifest')
    require(table('sCeladonDrinks', r'\{ITEM_(\w+), ITEM_(\w+), (FLAG_\w+)\}') ==
            [(r['drink'], r['reward'], r['flag']) for r in economy['drinks']],
            'Drink rewards differ from manifest')
    require(table('sCeladonCoinGifts', r'\{(\d+), (FLAG_\w+)\}') ==
            [(str(r['coins']), r['flag']) for r in economy['coinGifts']], 'Coin gifts differ')
    require(table('sCeladonCoinBundles', r'\{(\d+), (\d+)\}') ==
            [(str(a), str(b)) for a, b in economy['coinBundles']], 'Coin bundles differ')

    active = read('include/constants/tms_hms.h').split('#define FOREACH_HM', 1)[0]
    moves = re.findall(r'F\((\w+)\)', active)
    require(len(moves) == 50 and moves[18] == 'GIGA_DRAIN', 'Active TM roster changed')
    tm_tokens = set(re.findall(r'\bITEM_TM(\d+|_\w+)', authored+source+unique_source+json.dumps(maps)))
    for token in tm_tokens:
        require((token[1:] in moves if token.startswith('_') else 1 <= int(token) <= len(moves)),
                f'Unsupported TM row: ITEM_TM{token}')

    encounter_source = content.get('wildEncounterSource')
    require(encounter_source == {'path': 'src/data/wild_encounters.json',
            'maps': ['MAP_TH14_ROUTE8', 'MAP_TH14_ROUTE7']}, 'Missing wild encounter source mapping')
    groups = data(encounter_source['path'])['wild_encounter_groups']
    encounters = [e for g in groups for e in g.get('encounters', []) if e.get('map') in encounter_source['maps']]
    require(len(encounters) == 2, 'Missing/duplicate route encounter tables')
    for row in encounters:
        require(len(row['land_mons']['mons']) == 12, f'Missing encounter slots: {row["map"]}')
    for row in content['encounters'] + content['localTrades']:
        require(row['map'] in maps and row['script'] in blocks, f'Missing authored encounter/trade: {row}')
        require(row['receipt'] in by_flag, f'Missing encounter/trade receipt: {row}')
    return {'maps': len(chapter), 'receipts': len(receipts), 'accessible_labels': len(visited),
            'pickup_sources': len(pickup_owners), 'unique_gifts': len(declared_unique),
            'active_tms': len(moves), 'wild_tables': len(encounters)}


if __name__ == '__main__':
    print(json.dumps(validate(), indent=2))
