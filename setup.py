import shutil
import subprocess
from pathlib import Path

from setuptools import setup, Extension
from setuptools.command.build_ext import build_ext

with open("README.md", "r") as fh:
    long_description = fh.read()

CONANFILE_TXT = """[requires]
{pkg_ref}

[imports]
lib, *.so -> .
lib, *.pyd -> .
"""


class ConanExtension(Extension):
    def __init__(self, name, package_ref, **kwa):
        super().__init__(name, sources=[], **kwa)
        self.name = name
        self.package_ref = package_ref


class ConanBuild(build_ext):
    def build_extensions(self):
        # TODO check if conan is installed
        self.mkpath(self.build_temp)
        for ext in self.extensions:
            with (Path(self.build_temp) / "conanfile.txt").open("w") as f:
                f.write(CONANFILE_TXT.format(pkg_ref=ext.package_ref))
            subprocess.run(
                ["conan", "install", ".", "_/_", "-s", "compiler.cppstd=17"],
                cwd=self.build_temp,
            )
            install_name = Path(self.get_ext_fullpath(ext.name))
            install_dir = install_name.parent
            self.mkpath(str(install_dir))
            shutil.copyfile(
                str(Path(self.build_temp) / f"{ext.name}.so"), str(install_name),
            )


version = "0.1.0"

setup(
    name="pytinysea",
    version=version,
    author="Joris Vaillant",
    author_email="joris.vaillant@gmail.com",
    description="TinySea python binding",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/jorisv/py_tiny_sea",
    ext_modules=[ConanExtension("pytinysea", f"py_tiny_sea/{version}")],
    cmdclass={"build_ext": ConanBuild},
    python_requires=">=3.6",
)
