#!/usr/bin/env python3
"""Give each homework folder its own Eclipse project.

Files in the default package (public class Main) cannot share one Java
project. A directory that directly contains .java files becomes a project;
nested homework folders are excluded from the parent classpath.
"""

import os
from pathlib import Path
import xml.sax.saxutils as xml

ROOT = Path(__file__).resolve().parent.parent / "面向对象的程序设计"
SKIP_DIRS = {".git", ".vscode", ".settings", "bin", ".idea"}


def java_dirs(base: Path) -> list[Path]:
    found = []
    for dirpath, dirnames, filenames in os.walk(base):
        dirnames[:] = [d for d in dirnames if d not in SKIP_DIRS and not d.startswith(".")]
        if any(name.endswith(".java") for name in filenames):
            found.append(Path(dirpath))
    return found


def project_name(folder: Path) -> str:
    rel = folder.relative_to(ROOT)
    return "oop-" + "-".join(rel.parts)


def exclusions(folder: Path, folders: list[Path]) -> str:
    nested = []
    for other in folders:
        if other != folder and folder in other.parents:
            nested.append(other.relative_to(folder).as_posix() + "/**")
    return "|".join(nested)


def write_if_changed(path: Path, text: str) -> bool:
    if path.is_file() and path.read_text(encoding="utf-8") == text:
        return False
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8")
    return True


def project_xml(name: str) -> str:
    safe = xml.escape(name)
    return f"""<?xml version="1.0" encoding="UTF-8"?>
<projectDescription>
	<name>{safe}</name>
	<comment></comment>
	<projects>
	</projects>
	<buildSpec>
		<buildCommand>
			<name>org.eclipse.jdt.core.javabuilder</name>
			<arguments>
			</arguments>
		</buildCommand>
	</buildSpec>
	<natures>
		<nature>org.eclipse.jdt.core.javanature</nature>
	</natures>
</projectDescription>
"""


def classpath_xml(excluding: str) -> str:
    exclude_attr = f' excluding="{xml.escape(excluding, {chr(34): "&quot;"})}"' if excluding else ""
    return f"""<?xml version="1.0" encoding="UTF-8"?>
<classpath>
	<classpathentry kind="src" path=""{exclude_attr}/>
	<classpathentry kind="con" path="org.eclipse.jdt.launching.JRE_CONTAINER"/>
	<classpathentry kind="output" path="bin"/>
</classpath>
"""


def main() -> None:
    if not ROOT.is_dir():
        raise SystemExit(f"missing course folder: {ROOT}")
    folders = java_dirs(ROOT)
    changed = 0
    for folder in folders:
        name = project_name(folder)
        excluding = exclusions(folder, folders)
        if write_if_changed(folder / ".project", project_xml(name)):
            changed += 1
        if write_if_changed(folder / ".classpath", classpath_xml(excluding)):
            changed += 1
        print(name)
    print(f"projects={len(folders)} updated_files={changed}")


if __name__ == "__main__":
    main()
