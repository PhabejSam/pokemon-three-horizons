"""Execute the authored delivery branches; emulator tests cover native UI/movement."""
import copy
import unittest
from tools.three_horizons.tests.test_playtest11_maps import ROOT

MACH = 'ITEM_MACH_BIKE'
ACRO = 'ITEM_ACRO_BIKE'
VOUCHER = 'ITEM_BIKE_VOUCHER'
MACH_RECEIPT = 'FLAG_TH12_BIKE'
ACRO_RECEIPT = 'FLAG_TH13_ACRO'
VOUCHER_RECEIPT = 'FLAG_TH12_VOUCHER'


def visit(label, bag, flags, capacity=999, accept=True):
    source = (ROOT/'data/scripts/three_horizons/chapter12_vermilion.inc').read_text()
    lines, labels = [], {}
    for raw in source.splitlines():
        line = raw.split('@', 1)[0].strip()
        if line.endswith(':'):
            labels[line.rstrip(':')] = len(lines)
        elif line:
            lines.append(line)
    pc, result, messages = labels[label], False, []
    for _ in range(100):
        op, _, tail = lines[pc].partition(' ')
        pc += 1
        args = [a.strip() for a in tail.split(',')]
        if op in ('lock', 'faceplayer', 'release', 'releaseall'):
            continue
        if op == 'end':
            return messages
        if op == 'msgbox':
            messages.append(args[0])
            if len(args) > 1 and args[1] == 'MSGBOX_YESNO':
                result = accept
        elif op == 'checkitem':
            result = bag.get(args[0], 0) != 0
        elif op == 'giveitem':
            result = args[0] in bag or len(bag) < capacity
            if result:
                bag[args[0]] = bag.get(args[0], 0) + 1
        elif op == 'removeitem':
            if args[0] in bag:
                bag[args[0]] -= 1
                if not bag[args[0]]:
                    del bag[args[0]]
        elif op == 'setflag':
            flags.add(args[0])
        elif op == 'goto_if_set':
            if args[0] in flags:
                pc = labels[args[1]]
        elif op == 'goto_if_eq':
            assert args[0] == 'VAR_RESULT'
            if result == (args[1] in ('TRUE', 'YES', '1')):
                pc = labels[args[2]]
        elif op == 'goto':
            pc = labels[args[0]]
        else:
            raise AssertionError('Unmodeled delivery command: ' + lines[pc-1])
    raise AssertionError('Delivery script failed to return')


class Playtest13Bikes(unittest.TestCase):
    def test_bike_shop_completes_partial_dual_delivery(self):
        for inventory, receipts in [
            ({VOUCHER: 1}, set()), ({MACH: 1}, set()),
            ({ACRO: 1}, set()), ({MACH: 1, ACRO: 1}, set()),
            ({}, {MACH_RECEIPT}), ({ACRO: 1}, {MACH_RECEIPT}),
            ({}, {ACRO_RECEIPT}),
        ]:
            with self.subTest(inventory=inventory, receipts=receipts):
                bag, flags = dict(inventory), set(receipts)
                visit('TH12_Bike_Redeem', bag, flags)
                self.assertEqual(bag, {MACH: 1, ACRO: 1})
                self.assertTrue({MACH_RECEIPT, ACRO_RECEIPT} <= flags)
                before = copy.deepcopy((bag, flags))
                for _ in range(3):
                    visit('TH12_Bike_Redeem', bag, flags)
                self.assertEqual((bag, flags), before)

    def test_bike_delivery_full_bag_retry_cancel_and_no_voucher(self):
        bag, flags = {VOUCHER: 1}, set()
        visit('TH12_Bike_Redeem', bag, flags, capacity=1)
        self.assertEqual((bag, flags), ({VOUCHER: 1}, set()))
        # Legacy receipt authorizes both missing bikes; one free slot gives Mach only.
        bag, flags = {'ITEM_OLD_ROD': 1}, {MACH_RECEIPT}
        visit('TH12_Bike_Redeem', bag, flags, capacity=2)
        self.assertEqual(bag, {'ITEM_OLD_ROD': 1, MACH: 1})
        self.assertNotIn(ACRO_RECEIPT, flags)
        visit('TH12_Bike_Redeem', bag, flags, capacity=3)
        self.assertEqual(bag[ACRO], 1)
        for bag, flags in [({VOUCHER: 1}, set()), ({MACH: 1}, {MACH_RECEIPT})]:
            before = copy.deepcopy((bag, flags))
            visit('TH12_Bike_Redeem', bag, flags, accept=False)
            self.assertEqual((bag, flags), before)
        bag, flags = {}, set()
        visit('TH12_Bike_Redeem', bag, flags)
        self.assertEqual((bag, flags), ({}, set()))

    def test_chairman_expanded_story_preserves_voucher_receipt(self):
        bag, flags = {'ITEM_OLD_ROD': 1}, set()
        first = visit('TH12_FanClub_Voucher', bag, flags, capacity=1)
        self.assertIn('TH12_Voucher_Story', first)
        self.assertNotIn(VOUCHER_RECEIPT, flags)
        visit('TH12_FanClub_Voucher', bag, flags, capacity=2)
        self.assertEqual(bag[VOUCHER], 1)
        self.assertIn(VOUCHER_RECEIPT, flags)
        # Re-create state as a cold Continue would, with only saved bag and flags.
        bag, flags = dict(bag), set(flags)
        for _ in range(3):
            self.assertNotIn('TH12_Voucher_Story', visit('TH12_FanClub_Voucher', bag, flags))
            self.assertEqual(bag[VOUCHER], 1)
        source = (ROOT/'data/scripts/three_horizons/chapter12_vermilion.inc').read_text()
        story = source.split('TH12_Voucher_Story:', 1)[1].split('TH12_Voucher_Use:', 1)[0]
        self.assertIn('RAPIDASH', story)
        self.assertGreaterEqual(story.count('\\p'), 2)
        self.assertLessEqual(story.count('\\p'), 4)


if __name__ == '__main__':
    unittest.main()
