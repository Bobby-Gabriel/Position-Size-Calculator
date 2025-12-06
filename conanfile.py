from conan import ConanFile
from conan.tools.cmake import cmake_layout
from conan.tools.files import copy
import os


class PositionSizeCalculatorConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("qt/6.5.3")

    def configure(self):
        self.options["qt"].shared = True
        self.options["qt"].with_pq = False
        self.options["qt"].with_mysql = False
        self.options["qt"].with_sqlite3 = False

    def layout(self):
        cmake_layout(self)

    def generate(self):
        # Copy Qt DLLs to bin directory after generate
        bin_folder = os.path.join(self.source_folder, "bin")
        for dep in self.dependencies.values():
            copy(self, "*.dll", dep.cpp_info.bindir, bin_folder, keep_path=False)
            # Also copy Qt plugins
            if dep.ref.name == "qt":
                plugins_src = os.path.join(dep.package_folder, "plugins")
                plugins_dst = os.path.join(bin_folder, "plugins")
                copy(self, "*", plugins_src, plugins_dst, keep_path=True)
