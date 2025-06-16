cmake_minimum_required(VERSION 3.16)

project(userprofile-service LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Add prefix path
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build/build/Release/generators)

# Find Conan packages
find_package(PkgConfig REQUIRED)
include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake OPTIONAL)

# Find required packages through Conan
find_package(modern-cpp-kafka REQUIRED)
find_package(nlohmann_json REQUIRED)
find_package(protobuf REQUIRED)
find_package(SQLiteCpp REQUIRED)

# Proto files
file(GLOB_RECURSE PROTO_FILES config/proto/*.proto)

# Generate protobuf source and header files Handle the case where no .proto
# files are found
if(PROTO_FILES STREQUAL "")
  message(
    WARNING
      "No .proto files found in the proto directory. Skipping protobuf generation."
  )
  set(PROTO_SOURCES "") # Set an empty variable for PROTO_SOURCES
else()
  # Generate protobuf source and header files
  protobuf_generate(
    LANGUAGE
    cpp
    OUT_VAR
    PROTO_SOURCES
    IMPORT_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/config/proto
    PROTOS
    ${PROTO_FILES})
endif()

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(INCLUDES
    include/config/ServiceConfig.h
    include/config/TopicConfig.h

    include/domain/User.h

    include/service/UserProfileService.h

    include/repository/UserRepository.h
    include/repository/connection/IDatabaseConnection.h
    include/repository/connection/SQLiteConnection.h
    
    include/utils/utils.h
)

set(SOURCES
    src/config/ServiceConfig.cpp
    src/config/TopicConfig.cpp

    src/domain/User.cpp

    src/service/UserProfileService.cpp

    src/repository/UserRepository.cpp
    src/repository/connection/SQLiteConnection.cpp
)

add_executable(${PROJECT_NAME}
    ${INCLUDES}
    ${SOURCES}
    ${PROTO_SOURCES}
    main.cpp)

target_include_directories(${PROJECT_NAME}
PRIVATE
    include/config
    include/domain
    include/repository
    include/service
    include/proto
    include/utils)

# Link libraries
target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        modern-cpp-kafka::modern-cpp-kafka
        nlohmann_json::nlohmann_json
        protobuf::libprotobuf
        SQLiteCpp
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