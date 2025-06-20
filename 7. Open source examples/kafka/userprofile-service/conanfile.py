from conan import ConanFile
from conan.tools.cmake import cmake_layout


class ExampleRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps", "CMakeToolchain"

    def requirements(self):
        self.requires("modern-cpp-kafka/2024.07.03")
        self.requires("nlohmann_json/3.11.3")
        self.requires("protobuf/5.27.0")
        self.requires("sqlitecpp/3.3.2")

    def layout(self):
        cmake_layout(self)