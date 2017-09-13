# Top level CMakeLists.txt file.
cmake_minimum_required(VERSION 3.1)

# Project settings.
project(VulkanWrapper)
set(CMAKE_CXX_STANDARD 11)

# Project version. These are used for the version info returned by the library.
set(VulkanWrapper_Version_Major 0)
set(VulkanWrapper_Version_Minor 0)
set(VulkanWrapper_Version_Release 0)

# Option to build a static library.
option(Build_Static OFF)
# Option to build doxygen documentation.
option(Build_Documentation OFF)

# Required libraries
find_package(Vulkan REQUIRED)
include_directories(${Vulkan_INCLUDE_DIR})

# Subdirectories
include_directories(include)
add_subdirectory(gen)
include_directories(${CMAKE_BINARY_DIR}/gen/)
add_subdirectory(src)
add_subdirectory(test)

