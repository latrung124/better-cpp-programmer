# Install dependencies (from project root)
conan install . --output-folder=build --build=missing --remote=conancenter

chmod +x ./build/build/Release/generators/conanbuild.sh
./build/build/Release/generators/conanbuild.sh

# Build
cd build
cmake ..
cmake .. -G "Unix Makefiles" \
  -DCMAKE_TOOLCHAIN_FILE=build/build/Release/generators/conan_toolchain.cmake \
  -DCMAKE_BUILD_TYPE=Release