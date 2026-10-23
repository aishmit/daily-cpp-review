"""common/pytest_lite.py — run every `test_*` function in the given files. Stdlib only.

    python3 common/pytest_lite.py days/001/design/test_*.py
"""
import importlib.util
import sys
import traceback
from pathlib import Path


def run(paths):
    passed = total = 0
    for p in paths:
        path = Path(p).resolve()
        sys.path.insert(0, str(path.parent))
        spec = importlib.util.spec_from_file_location(path.stem, path)
        mod = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(mod)
        for name in sorted(n for n in dir(mod) if n.startswith("test_")):
            total += 1
            try:
                getattr(mod, name)()
                passed += 1
                print(f"[ OK ] {name}")
            except Exception as e:
                print(f"[FAIL] {name}")
                frames = traceback.extract_tb(e.__traceback__)
                # Where it failed: the line in the test file, then (if different) the line that raised.
                in_test = [f for f in frames if Path(f.filename).resolve() == path]
                shown = ([in_test[-1]] if in_test else []) + ([frames[-1]] if frames and (not in_test or frames[-1] is not in_test[-1]) else [])
                for f in shown:
                    print(f"    {Path(f.filename).name}:{f.lineno}: {f.line}")
                print(f"    {type(e).__name__}{': ' + str(e) if str(e) else ''}")
        sys.path.pop(0)
    print(f"\n{passed}/{total} tests passed")
    return 0 if passed == total else 1


if __name__ == "__main__":
    sys.exit(run(sys.argv[1:]))
