"""Final gate rejects incomplete content; mutations never touch build inputs."""
import json
import unittest
from pathlib import Path
from tools.three_horizons.validate_playtest14 import validate

ROOT = Path(__file__).resolve().parents[3]
LEDGER = 'tools/three_horizons/chapter14_content.json'


class Coverage(unittest.TestCase):
    def test_complete_manifest(self):
        self.assertEqual(validate(ROOT)['maps'], 37)

    def test_rejects_duplicate_receipt_and_unfinished_interaction(self):
        original = json.loads((ROOT/LEDGER).read_text())
        for key, value in [('receipts', original['receipts'] + [original['receipts'][0]]),
                           ('unfinishedInteractions', [{'ownerTask': 18}])]:
            changed = dict(original, **{key: value})
            with self.assertRaises(ValueError):
                validate(ROOT, {LEDGER: json.dumps(changed)})

    def test_rejects_missing_handler_donor_warp_and_duplicate_pickup(self):
        path = 'data/maps/TH14_Route8/map.json'
        for change in ('handler', 'warp', 'pickup'):
            record = json.loads((ROOT/path).read_text())
            if change == 'handler':
                record['object_events'][0]['script'] = 'TH14_MissingHandler'
            elif change == 'warp':
                record['warp_events'][0]['dest_map'] = 'MAP_ROUTE8_FRLG'
            else:
                record['bg_events'].append(record['bg_events'][-1])
            with self.assertRaises(ValueError):
                validate(ROOT, {path: json.dumps(record)})

    def test_rejects_donor_flag_placeholder_and_unsupported_tm(self):
        path = 'data/scripts/three_horizons/chapter14_travel.inc'
        text = (ROOT/path).read_text()
        for changed in (text.replace('TH14_UndergroundSign::', 'TH14_UndergroundSign::\n    setflag FLAG_HIDE_OAK'),
                        text.replace('TH14_UndergroundSign::', 'TH14_UndergroundSign::\n    msgbox TH14_UnfinishedText') +
                        '\nTH14_UnfinishedText::\n    .string "Please wait a moment.$"\n',
                        text + '\nTH14_InvalidReward::\n    giveitem ITEM_TM_UNSUPPORTED\n    end\n'):
            with self.assertRaises(ValueError):
                validate(ROOT, {path: changed})


if __name__ == '__main__':
    unittest.main()
