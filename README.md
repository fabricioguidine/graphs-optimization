# Graph Algorithms with GRASP

[![CI](https://github.com/fabricioguidine/graphs-optimization/actions/workflows/ci.yml/badge.svg?branch=master)](https://github.com/fabricioguidine/graphs-optimization/actions/workflows/ci.yml)
[![codecov](https://codecov.io/gh/fabricioguidine/graphs-optimization/branch/master/graph/badge.svg)](https://codecov.io/gh/fabricioguidine/graphs-optimization)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++ Standard](https://img.shields.io/badge/C++-17%2F20-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![CMake](https://img.shields.io/badge/CMake-3.14%2B-064F8C.svg)](https://cmake.org/)

## 📋 Description

A comprehensive C++ implementation of graph algorithms including fundamental graph operations, shortest path algorithms, minimum spanning tree algorithms, and metaheuristic optimization using GRASP (Greedy Randomized Adaptive Search Procedure).

## ✨ Features

### 🔷 Core Graph Operations
- **Graph Data Structure**: Flexible implementation supporting directed/undirected and weighted/unweighted graphs
- **Node and Edge Management**: Efficient insertion, removal, and traversal operations
- **Graph Analysis**: Connectivity checks, circuit detection, complement generation

### 🔷 Graph Algorithms
- **Breadth-First Search (BFS)**: Level-order traversal
- **Depth-First Search (DFS)**: Path finding between nodes
- **Dijkstra's Algorithm**: Single-source shortest paths
- **Floyd-Warshall Algorithm**: All-pairs shortest paths
- **Prim's Algorithm**: Minimum spanning tree
- **Kruskal's Algorithm**: Minimum spanning tree with union-find
- **Strongly Connected Components**: Kosaraju's algorithm
- **Topological Sort**: Kahn's algorithm for DAGs

### 🔷 Metaheuristics
- **GRASP**: Greedy Randomized Adaptive Search Procedure for optimization problems

## 🚀 Getting Started

### 📦 Prerequisites

- CMake 3.10 or higher
- C++17 compatible compiler (GCC, Clang, or MSVC)
- Git (for fetching Google Test)

### 📥 Installation

1. Clone the repository:
```bash
git clone https://github.com/fabricioguidine/graphs-with-grasp.git
cd graphs-with-grasp
```

2. Create build directory:
```bash
mkdir build
cd build
```

3. Configure and build:
```bash
cmake ..
cmake --build .
```

### 📊 Data Setup

Before running the algorithms, set up test data:

```bash
# Run the data setup script
python scripts/setup_data.py
```

This will:
- Create necessary data directories
- Check for existing graph instances
- Generate sample test graphs if needed

## 💻 Usage

### ▶️ Running the Application

```bash
./graph_algorithms <input_file> <output_file> <directed> <weighted_edge> <weighted_node>
```

**Parameters:**
- `input_file`: Path to graph input file
- `output_file`: Path to output file
- `directed`: `0` for undirected, `1` for directed
- `weighted_edge`: `0` for unweighted edges, `1` for weighted edges
- `weighted_node`: `0` for unweighted nodes, `1` for weighted nodes

**Example:**
```bash
./graph_algorithms input.txt output.txt 0 1 0
```

### 📝 Input File Format

The input file should follow this format:

```
<order> <num_edges>
<source_id> <target_id> [<weight>]
...
```

For weighted graphs, include edge weights:
```
5 7
1 2 1.5
2 3 2.0
3 4 1.0
...
```

### 💡 Code Examples

#### Example 1: Find Shortest Path
```cpp
#include "Graph.h"
#include "algorithms/Dijkstra.h"

Graph* graph = new Graph(5, true, true, false);
graph->insertEdge(1, 2, 1.0f);
graph->insertEdge(2, 3, 2.0f);

std::vector<float> distances = Dijkstra::shortestPath(graph, 1);
```

#### Example 2: Minimum Spanning Tree
```cpp
#include "Graph.h"
#include "algorithms/Prim.h"

Graph* graph = new Graph(4, false, true, false);
// ... add edges ...

std::vector<std::pair<int, int>> mst = Prim::minimumSpanningTree(graph);
float weight = Prim::getMSTWeight(graph);
```

#### Example 3: Topological Sort
```cpp
#include "Graph.h"
#include "algorithms/TopologicalSort.h"

Graph* dag = new Graph(5, true, false, false);
// ... add edges ...

std::vector<int> order = TopologicalSort::sort(dag);
```

## 🧪 Testing

The project includes comprehensive unit tests using Google Test framework:

```bash
# Run all tests
./graph_tests

# Run specific test
./graph_tests --gtest_filter=GraphTest.*
```

## 📁 Project Structure

```
graphs-with-grasp/
├── include/                 # Header files
│   ├── Graph.h              # Main graph class
│   ├── Node.h               # Node (vertex) class
│   ├── Edge.h               # Edge class
│   ├── algorithms/          # Algorithm implementations
│   └── utils/               # Utility functions
├── src/                     # Source files
│   ├── core/                # Core data structures
│   ├── algorithms/          # Algorithm implementations
│   └── utils/               # Utility implementations
├── tests/                   # Unit tests
├── docs/                    # Documentation
│   ├── requirements.pdf     # Project specification
│   └── latex/               # LaTeX technical report
├── scripts/                 # Utility scripts
├── data/                    # Graph instances
└── CMakeLists.txt           # Build configuration
```

## 📚 Documentation

### 📄 Technical Report

A comprehensive technical report in LaTeX (following UFJF standards) is located in `docs/latex/`:

- **LaTeX Source**: [`docs/latex/report.tex`](docs/latex/report.tex)
- **Cover Page**: [`docs/latex/cover.tex`](docs/latex/cover.tex)
- **Bibliography**: [`docs/latex/references.bib`](docs/latex/references.bib)

**To compile the PDF report:**

```bash
cd docs/latex
pdflatex report.tex
bibtex report
pdflatex report.tex
pdflatex report.tex
```

**Recommended:** Use [Overleaf](https://www.overleaf.com/) (online LaTeX editor - no installation needed)

### 📋 Requirements

The complete project requirements are available in: [`docs/requirements.pdf`](docs/requirements.pdf)

## ⚡ Algorithm Complexity

| Algorithm | Time Complexity | Space Complexity |
|-----------|----------------|------------------|
| BFS/DFS | O(V + E) | O(V) |
| Dijkstra | O((V + E) log V) | O(V) |
| Floyd-Warshall | O(V³) | O(V²) |
| Prim | O((V + E) log V) | O(V) |
| Kruskal | O(E log E) | O(V) |
| Topological Sort | O(V + E) | O(V) |
| Strongly Connected Components | O(V + E) | O(V) |
| GRASP | O(I × (C + L)) | O(V) |

Where:
- V = number of vertices
- E = number of edges
- I = iterations
- C = construction time
- L = local search time

## 🤝 Contributing

Contributions are welcome! Please follow these guidelines:

1. Maintain code style consistency
2. Add unit tests for new features
3. Update documentation as needed
4. Follow the existing architecture

## Development

### Build, test, coverage and benchmarks

```bash
# Configure (Debug + tests, default)
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel

# Run all tests via CTest
ctest --test-dir build --output-on-failure

# Coverage (Linux/macOS with gcov + gcovr installed)
cmake -S . -B build-cov -DGRAPHS_ENABLE_COVERAGE=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build-cov --parallel
ctest --test-dir build-cov --output-on-failure
gcovr -r . --exclude 'build-cov/_deps/.*' --exclude 'tests/.*' --html -o coverage.html

# Sanitizers
cmake -S . -B build-san -DGRAPHS_ENABLE_ASAN=ON -DGRAPHS_ENABLE_UBSAN=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build-san --parallel
ctest --test-dir build-san --output-on-failure

# Benchmarks (Google Benchmark)
cmake -S . -B build-bench -DGRAPHS_BUILD_BENCHMARKS=ON -DCMAKE_BUILD_TYPE=Release
cmake --build build-bench --target graph_benchmarks --parallel
./build-bench/bin/graph_benchmarks
```

### CMake options

| Option | Default | Description |
|---|---|---|
| `GRAPHS_BUILD_TESTS` | `ON` | Build GoogleTest unit + invariant tests |
| `GRAPHS_BUILD_BENCHMARKS` | `OFF` | Build Google Benchmark micro-benchmarks |
| `GRAPHS_ENABLE_COVERAGE` | `OFF` | Compile with gcov instrumentation |
| `GRAPHS_ENABLE_ASAN` | `OFF` | AddressSanitizer |
| `GRAPHS_ENABLE_UBSAN` | `OFF` | UndefinedBehaviorSanitizer |
| `GRAPHS_ENABLE_TSAN` | `OFF` | ThreadSanitizer |
| `GRAPHS_WARNINGS_AS_ERRORS` | `OFF` | Pass `-Werror` / `/WX` |

### Code style

`.clang-format` and `.clang-tidy` configure the style and static checks. CI runs
`clang-format --dry-run --Werror` and `clang-tidy` on every PR.

### Data instances

The `data/instances/` directory ships ~484 MB of benchmark graphs across 4700+
files. Going forward, please **do not commit new instances**: migrate large
inputs to [Git LFS](https://git-lfs.com/) or attach them to a GitHub Release and
load them on demand via `scripts/setup_data.py`. The `.gitignore` rules ignore
new `.dat` / `.txt` instance files by default; remove that block locally if you
have a legitimate reason to add small fixtures.

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
