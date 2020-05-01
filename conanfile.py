from conans import ConanFile, tools, CMake


class PyTinySeaConan(ConanFile):
    name = "py_tiny_sea"
    version = "0.1.0"
    author = "Joris Vaillant (joris.vaillant@gmail.com)"
    license = "GPL-3.0-only"
    url = "https://github.com/jorisv/py_tiny_sea"
    description = "TinySea python binding"
    settings = "os", "compiler", "build_type", "arch"
    requires = (
        "tiny_sea/[^0.1]",
        "pybind11/[^2.4]",
    )
    default_options = {"tiny_sea:build_tests": False}
    generators = "cmake", "virtualrunenv"

    def configure(self):
        tools.check_min_cppstd(self, "17")

    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.configure()
        return cmake

    def source(self):
        git = tools.Git()
        git.clone(self.url)
        git.checkout("v%s" % self.version)

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()

    def package(self):
        cmake = self._configure_cmake()
        cmake.install()

    def package_info(self):
        self.cpp_info.libs = ["pytinysea"]
