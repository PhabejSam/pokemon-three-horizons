"""Resolve the project's bounded dynamic elevators for map validation."""
import re

DEPARTMENT = 'MAP_TH14_CELADON_CITY_DEPARTMENT_STORE_ELEVATOR'
HIDEOUT = 'MAP_TH14_ROCKET_HIDEOUT_ELEVATOR'


def dynamic_destinations(root, map_id):
    if map_id == DEPARTMENT:
        text = (root/'data/scripts/three_horizons/chapter14_celadon.inc').read_text()
        actual = {(m, int(x), int(y)) for m, x, y in
                  re.findall(r'setdynamicwarp (\w+), 255, (\d+), (\d+)', text)}
        expected = {(f'MAP_TH14_CELADON_CITY_DEPARTMENT_STORE_{i}F', 6, 1)
                    for i in range(1, 6)}
    elif map_id == HIDEOUT:
        text = (root/'src/three_horizons_hideout.c').read_text()
        table = text.split('} sHideoutFloors[] = {', 1)[1].split('};', 1)[0]
        actual = {(m, int(x), int(y)) for m, x, y in
                  re.findall(r'{(MAP_\w+), \d+, (\d+), (\d+)}', table)}
        expected = {('MAP_TH14_ROCKET_HIDEOUT_B1F', 24, 25),
                    ('MAP_TH14_ROCKET_HIDEOUT_B2F', 28, 16),
                    ('MAP_TH14_ROCKET_HIDEOUT_B4F', 20, 23)}
        fallback = (root/'data/scripts/three_horizons/chapter14_hideout.inc').read_text()
        fallback = {(m, int(x), int(y)) for m, x, y in
                    re.findall(r'setdynamicwarp (\w+), 255, (\d+), (\d+)', fallback)}
        if fallback != {('MAP_TH14_ROCKET_HIDEOUT_B1F', 24, 25)}:
            raise ValueError(f'Unexpected hideout fallback: {fallback}')
    else:
        raise ValueError(f'Unapproved dynamic warp owner: {map_id}')
    if actual != expected:
        raise ValueError(f'Dynamic destinations differ: {map_id}: {actual}')
    return actual


def destinations(root, record):
    result = {c['map'] for c in record['connections'] or []}
    for warp in record['warp_events']:
        if warp['dest_map'] == 'MAP_DYNAMIC':
            if warp['dest_warp_id'] != 'WARP_ID_DYNAMIC':
                raise ValueError(f'Invalid dynamic warp id: {warp}')
            result.update(m for m, _, _ in dynamic_destinations(root, record['id']))
        else:
            result.add(warp['dest_map'])
    return result
