cmake_minimum_required(VERSION 3.14)
project(GraphAlgorithms VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set build type to Release by default if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# --- Project options ------------------------------------------------------
option(GRAPHS_BUILD_TESTS       "Build unit tests"                   ON)
option(GRAPHS_BUILD_BENCHMARKS  "Build performance benchmarks"       OFF)
option(GRAPHS_ENABLE_COVERAGE   "Enable gcov coverage (GCC/Clang)"   OFF)
option(GRAPHS_ENABLE_ASAN       "Enable AddressSanitizer"            OFF)
option(GRAPHS_ENABLE_UBSAN      "Enable UndefinedBehaviorSanitizer"  OFF)
option(GRAPHS_ENABLE_TSAN       "Enable ThreadSanitizer"             OFF)
option(GRAPHS_WARNINGS_AS_ERRORS "Treat warnings as errors"          OFF)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# --- Warnings, sanitizers, coverage flags ---------------------------------
add_library(graphs_compile_flags INTERFACE)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
    target_compile_options(graphs_compile_flags INTERFACE
        -Wall -Wextra -Wpedantic -Wshadow -Wnon-virtual-dtor
        -Wold-style-cast -Wcast-align -Woverloaded-virtual
        -Wconversion -Wsign-conversion -Wnull-dereference
        -Wdouble-promotion -Wformat=2
    )
    if(GRAPHS_WARNINGS_AS_ERRORS)
        target_compile_options(graphs_compile_flags INTERFACE -Werror)
    endif()
elseif(MSVC)
    target_compile_options(graphs_compile_flags INTERFACE /W4 /permissive-)
    if(GRAPHS_WARNINGS_AS_ERRORS)
        target_compile_options(graphs_compile_flags INTERFACE /WX)
    endif()
endif()

if(GRAPHS_ENABLE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
        target_compile_options(graphs_compile_flags INTERFACE --coverage -O0 -g)
        target_link_options(graphs_compile_flags    INTERFACE --coverage)
    else()
        message(WARNING "Coverage requested but compiler does not support gcov flags.")
    endif()
endif()

if(GRAPHS_ENABLE_ASAN)
    target_compile_options(graphs_compile_flags INTERFACE -fsanitize=address -fno-omit-frame-pointer)
    target_link_options(graphs_compile_flags    INTERFACE -fsanitize=address)
endif()
if(GRAPHS_ENABLE_UBSAN)
    target_compile_options(graphs_compile_flags INTERFACE -fsanitize=undefined)
    target_link_options(graphs_compile_flags    INTERFACE -fsanitize=undefined)
endif()
if(GRAPHS_ENABLE_TSAN)
    target_compile_options(graphs_compile_flags INTERFACE -fsanitize=thread)
    target_link_options(graphs_compile_flags    INTERFACE -fsanitize=thread)
endif()

# --- Sources --------------------------------------------------------------
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

# Reusable library so tests/benchmarks don't recompile everything.
add_library(graphs_lib STATIC
    ${CORE_SOURCES}
    ${ALGORITHM_SOURCES}
    ${UTIL_SOURCES}
)
target_include_directories(graphs_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(graphs_lib PUBLIC graphs_compile_flags)

# Main executable
add_executable(graph_algorithms src/main.cpp)
target_link_libraries(graph_algorithms PRIVATE graphs_lib)

# --- Tests ----------------------------------------------------------------
if(GRAPHS_BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.0
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    add_executable(graph_tests
        tests/test_Graph.cpp
        tests/test_Algorithms.cpp
        tests/test_Dijkstra.cpp
        tests/test_FloydWarshall.cpp
        tests/test_Prim.cpp
        tests/test_Kruskal.cpp
        tests/test_TopologicalSort.cpp
        tests/test_StronglyConnectedComponents.cpp
        tests/test_GRASP.cpp
        tests/test_Invariants.cpp
        tests/test_EndToEnd.cpp
    )
    target_link_libraries(graph_tests
        PRIVATE
            graphs_lib
            GTest::gtest
            GTest::gtest_main
    )

    enable_testing()
    include(GoogleTest)
    gtest_discover_tests(graph_tests
        PROPERTIES LABELS "unit"
        DISCOVERY_TIMEOUT 30
    )
endif()

# --- Benchmarks (Google Benchmark, opt-in) --------------------------------
if(GRAPHS_BUILD_BENCHMARKS)
    include(FetchContent)
    set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
    set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
    FetchContent_Declare(
        benchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG        v1.8.3
    )
    FetchContent_MakeAvailable(benchmark)

    add_executable(graph_benchmarks tests/bench_Algorithms.cpp)
    target_link_libraries(graph_benchmarks PRIVATE graphs_lib benchmark::benchmark)
endif()

# Installation (optional)
install(TARGETS graph_algorithms
    RUNTIME DESTINATION bin
)
