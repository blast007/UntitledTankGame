cmake_minimum_required(VERSION 3.8)

# We're using vcpkg for dependencies, so make sure we can find the toolchail file
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
  message("Using environment variable for VCPKG_ROOT to determine vcpkg directory.")
endif()

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    message(FATAL_ERROR "Missing vcpkg toolchain file")
endif()

project(UntitledTankGame LANGUAGES CXX)

# Check for dependencies
find_package(toml11 CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add any subdirectories to build
add_subdirectory(src/common)
add_subdirectory(tests)
