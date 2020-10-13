import pathlib
import re
import subprocess


DATA = pathlib.Path('data')


def jsonparser_output(json_file):
    out = subprocess.check_output(['./p.out', json_file])
    return out.decode().strip()


def check_flex_lexical():
    data = DATA/'test_flex'
    p, f = 0, 0
    for src in data.glob('example*.spl'):
        out = jsonparser_output(src)
        if ('_EXCLUDE' in src.name):
            continue
        if ('lexical error' in out):
            f += 1
        else:
            p += 1
        print(f'For file {src.name}:')
        print(out)
        print('-'*80)
    print(f'Pass/Total: {p}/{p+f}')

def check_output():
    data = DATA/'test'
    p, f = 0, 0
    for src in data.glob('test_1_r01.spl'):
        out = jsonparser_output(src)
        if ('_EXCLUDE' in src.name):
            continue
        if ('lexical error' in out):
            f += 1
        else:
            p += 1
        print(f'For file {src.name}:')
        print(out)
        print('-'*80)
    print(f'Pass/Total: {p}/{p+f}')


def check_jsonchecker_fail_syntaxonly():
    data = DATA/'jsonchecker'
    recovered, total = 0, 0
    for failjson in data.glob('fail*.json'):
        out = jsonparser_output(failjson)
        if ('lexical error' in out) or ('_EXCLUDE' in failjson.name):
            continue
        print(f'For file {failjson.name}:')
        print('-'*24)
        print(open(failjson).read())
        print('-'*80)
        print(out)
        print('#'*80)
        m = re.match(r'^syntax(.*?)recovered$', out)
        recovered += bool(m)
        total += 1
    print(f'Recovered/Total: {recovered}/{total}')

def check_pass():
    data = DATA/'jsonchecker'
    passed, total = 0, 0
    for passjson in data.glob('pass*.json'):
        print('-'*24)
        print(open(passjson).read())
        print('-'*80)
        out = jsonparser_output(passjson)
        print(out)


check_flex_lexical()
check_output()
# check_jsonchecker_fail_withlexical()
# check_jsonchecker_fail_syntaxonly()
# check_pass()
