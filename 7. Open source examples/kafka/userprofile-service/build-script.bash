# Create build directory
mkdir build && cd build

# Install dependencies (from project root)
conan install .. --build=missing

# Configure with CMake
cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake

# Build
cmake --build .