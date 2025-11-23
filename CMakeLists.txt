cmake_minimum_required(VERSION 3.10)
project(GraphAlgorithms VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set build type to Release by default if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
set(CORE_SOURCES
    src/core/Graph.cpp
    src/core/Node.cpp
    src/core/Edge.cpp
)

set(ALGORITHM_SOURCES
    src/algorithms/Dijkstra.cpp
    src/algorithms/FloydWarshall.cpp
    src/algorithms/Prim.cpp
    src/algorithms/Kruskal.cpp
    src/algorithms/StronglyConnectedComponents.cpp
    src/algorithms/TopologicalSort.cpp
    src/algorithms/GRASP.cpp
)

set(UTIL_SOURCES
    src/utils/GraphReader.cpp
)

# Main executable
add_executable(graph_algorithms
    src/main.cpp
    ${CORE_SOURCES}
    ${ALGORITHM_SOURCES}
    ${UTIL_SOURCES}
)

# Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Test executable
add_executable(graph_tests
    tests/test_Graph.cpp
    tests/test_Algorithms.cpp
    ${CORE_SOURCES}
    ${ALGORITHM_SOURCES}
    ${UTIL_SOURCES}
)

target_link_libraries(graph_tests
    PRIVATE
    gtest
    gtest_main
)

# Enable testing
enable_testing()
add_test(NAME GraphTests COMMAND graph_tests)

# Installation (optional)
install(TARGETS graph_algorithms graph_tests
    RUNTIME DESTINATION bin
)
