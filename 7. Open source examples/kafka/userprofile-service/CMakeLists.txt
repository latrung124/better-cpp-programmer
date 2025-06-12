cmake_minimum_required(VERSION 3.16)

project(userprofile-service LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Find Conan packages
find_package(PkgConfig REQUIRED)
include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake OPTIONAL)

# Find required packages through Conan
find_package(modern-cpp-kafka REQUIRED)
find_package(nlohmann_json REQUIRED)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(INCLUDES
)

set(SOURCES
)

add_executable(${PROJECT_NAME}
    ${INCLUDES}
    ${SOURCES}
    main.cpp)

# Link libraries
target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        modern-cpp-kafka::modern-cpp-kafka
        nlohmann_json::nlohmann_json
        # Add database libraries if needed
        # SQLite::SQLite3
        # PostgreSQL::PostgreSQL
)

# Set target properties
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Install rules
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/
    DESTINATION include/${PROJECT_NAME}
    FILES_MATCHING PATTERN "*.h"
)

# TODO: Add tests
# TODO: Add documentation