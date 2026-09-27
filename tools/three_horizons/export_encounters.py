"""Export the compiled-table inputs; never maintain encounter percentages by hand."""
import argparse
import json
import re
from collections import defaultdict
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2]

def render(revision):
    data=json.loads((ROOT/'src/data/wild_encounters.json').read_text())
    group=data['wild_encounter_groups'][0]
    fields={f['type']:f for f in group['fields']}
    lines=['# Playtest 12 encounter checklist','',f'Source revision: `{revision}`.','',
      'Rates below are shares of encounters, not chances per step. Repels, lead abilities and time settings can affect encounters. Wild starters have ordinary random stats and the same Hidden Ability rules as other wild Pokémon.','',
      'Grass/cave encounters and the Old Rod are available in this chapter. Surf, Rock Smash, Good Rod and Super Rod tables are listed as future access only. Visible research-scene Pokémon do not trigger captures.','']
    entries=[e for e in group['encounters'] if e['map'].startswith(('MAP_TH_','MAP_TH12_'))]
    for e in sorted(entries,key=lambda e:(e['map'],e['base_label'])):
      name=e['map'].removeprefix('MAP_TH12_').removeprefix('MAP_TH_').replace('_',' ').title()
      name=re.sub(r'Route(?=\d)', 'Route ', name)
      timing='night' if e['base_label'].endswith('_Night') else 'day / fallback' if any(o['map']==e['map'] and o['base_label'].endswith('_Night') for o in entries) else 'all times'
      for kind,label in [('land_mons','grass / cave'),('water_mons','Surf — future access'),('rock_smash_mons','Rock Smash — future access'),('fishing_mons','fishing')]:
        if kind not in e:continue
        field=fields[kind];mons=e[kind]['mons'];rates=field['encounter_rates']
        subsets=field.get('groups',{label:list(range(len(mons)))})
        for method,slots in subsets.items():
          title=method.replace('_',' ').title() if kind=='fishing_mons' else label
          if kind=='fishing_mons' and method!='old_rod':title+=' — future access'
          counts=defaultdict(lambda:[0,set()])
          for i in slots:
            mon=mons[i];species=mon['species'].removeprefix('SPECIES_').replace('_',' ').title()
            counts[species][0]+=rates[i];counts[species][1].update(range(mon['min_level'],mon['max_level']+1))
          lines += [f'## {name} — {timing} — {title}','','| Pokémon | Rate | Levels | Seen / caught |','|---|---:|---|---|']
          for species,(rate,levels) in sorted(counts.items(),key=lambda x:(-x[1][0],x[0])):
            lines.append(f'| {species} | {rate}% | '+', '.join(map(str,sorted(levels)))+' | |')
          lines.append('')
    return '\n'.join(lines)

if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('--revision',required=True);p.add_argument('--output',type=Path,required=True);a=p.parse_args()
    a.output.write_text(render(a.revision),encoding='utf-8')
