# Root CMakeLists.txt - redirects to cmake/CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Include the main CMakeLists.txt from cmake directory
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CMakeLists.txt)
