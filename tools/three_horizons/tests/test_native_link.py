"""Exercise the actual test-link recipe with Windows-sized input lists."""
import os
from pathlib import Path
import re
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[3]


class NativeLink(unittest.TestCase):
    def test_full_object_list_links_via_windows_response_and_posix_direct_paths(self):
        source = (ROOT/'Makefile').read_text()
        recipe = source.split('$(TESTELF):', 1)[1].split('\n', 1)[1].split('\t$(FIX)', 1)[0]
        for name in ('make', 'gcc', 'ld', 'nm'):
            self.assertIsNotNone(shutil.which(name), name+' required for linker regression')
        with tempfile.TemporaryDirectory(dir=ROOT, prefix='.th-link-') as folder:
            out = Path(folder)
            obj = out/'build/test'; obj.mkdir(parents=True)
            for stem, code in [('main', 'int main_input=1;'), ('last', 'int test_input=2;'),
                               ('repeated_object_with_a_deliberately_long_filename',
                                'static int payload __attribute__((used))=42;')]:
                (obj/(stem+'.c')).write_text(code)
                run = subprocess.run(['gcc', '-c', stem+'.c', '-o', stem+'.o'], cwd=obj,
                                     capture_output=True, text=True)
                self.assertEqual(run.returncode, 0, run.stderr)
            (obj/'ld_script_test.ld').write_text('SECTIONS { .data : { *(.data) } }\n')
            for platform, repetitions in [('Windows_NT', 1800), ('posix', 2)]:
                inputs = ['repeated_object_with_a_deliberately_long_filename.o'] * repetitions + ['last.o']
                if platform == 'Windows_NT':
                    self.assertGreater(len(' '.join(inputs)), 32767)
                target = platform+'.o'
                prefix = ('OS := '+platform+'\nOBJ_DIR := build/test\nTESTELF := '+target+
                          '\nOBJS_REL := main.o\nTEST_OBJS_REL := '+' '.join(inputs)+
                          '\nLD := '+Path(shutil.which('ld')).as_posix()+
                          '\nTESTLDFLAGS := -r\nall: $(TESTELF)\n$(TESTELF):\n')
                (out/'probe.mk').write_text(prefix+recipe)
                run = subprocess.run(['make', '-f', 'probe.mk'], cwd=out, capture_output=True, text=True)
                self.assertEqual(run.returncode, 0, run.stdout+run.stderr)
                symbols = subprocess.run(['nm', '-a', target], cwd=out, capture_output=True, text=True)
                self.assertEqual(symbols.returncode, 0, symbols.stderr)
                self.assertEqual(len(re.findall(r'\bpayload$', symbols.stdout, re.M)), repetitions)
                for symbol in ('main_input', 'test_input'):
                    self.assertEqual(len(re.findall(r'\b'+symbol+'$', symbols.stdout, re.M)), 1)
                if platform == 'Windows_NT':
                    self.assertEqual((obj/'test-link-inputs.rsp').read_text().split(),
                                     ['main.o']+inputs)


if __name__ == '__main__':
    unittest.main()
