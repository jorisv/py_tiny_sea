import json
import shutil
import subprocess
from pathlib import Path

from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext


class ConanExtension(Extension):
    def __init__(self, name, version, **kwa):
        super().__init__(name, sources=[], **kwa)
        self.name = name
        self.version = version
        self.package_ref = f"{name}/{version}"


class ConanBuild(build_ext):
    def _extract_lib_path_from_json(self, project_name: str, json_path: Path) -> Path:
        """:return: Binding library path from conanbuildinfo.json"""
        with json_path.open("r") as json_fp:
            json_content = json.load(json_fp)
        # Sort project by name
        projects = {d["name"]: d for d in json_content["dependencies"]}

        # Find first library in project lib_paths
        lib_paths = Path(projects[project_name]["lib_paths"][0])
        return next(lib_paths.glob("*"))

    def build_extensions(self):
        self.mkpath(self.build_temp)
        for ext in self.extensions:
            # Install conan package with json generator
            subprocess.run(
                [
                    "conan",
                    "install",
                    f"{ext.package_ref}@_/_",
                    "-s",
                    "compiler.cppstd=17",
                    "-g",
                    "json",
                ],
                cwd=self.build_temp,
            )
            # Find lib name inside conan package
            lib_path = self._extract_lib_path_from_json(
                ext.name, Path(self.build_temp) / "conanbuildinfo.json"
            )

            # Copy lib
            self.mkpath(self.build_lib)
            shutil.copyfile(
                str(lib_path), str(Path(self.build_lib) / lib_path.name),
            )


def readme():
    with Path("README.md").open("r") as fh:
        return fh.read()


version = "0.3.0"

setup(
    name="pytinysea",
    version=version,
    author="Joris Vaillant",
    author_email="joris.vaillant@gmail.com",
    description="TinySea python binding",
    long_description=readme(),
    long_description_content_type="text/markdown",
    url="https://github.com/jorisv/py_tiny_sea",
    ext_modules=[ConanExtension("py_tiny_sea", version)],
    cmdclass={"build_ext": ConanBuild},
    python_requires=">=3.6",
    setup_requires="conan>=1.25",
    include_package_data=True,
    zip_safe=False,
)
