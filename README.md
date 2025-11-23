# Graph Algorithms with GRASP

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++ Standard](https://img.shields.io/badge/C++-17-blue.svg)](https://en.cppreference.com/w/cpp/17)

## Overview

A comprehensive C++ implementation of graph algorithms including fundamental graph operations, shortest path algorithms, minimum spanning tree algorithms, and metaheuristic optimization using GRASP (Greedy Randomized Adaptive Search Procedure).

## Features

### Core Graph Operations
- **Graph Data Structure**: Flexible implementation supporting directed/undirected and weighted/unweighted graphs
- **Node and Edge Management**: Efficient insertion, removal, and traversal operations
- **Graph Analysis**: Connectivity checks, circuit detection, complement generation

### Graph Algorithms
- **Breadth-First Search (BFS)**: Level-order traversal
- **Depth-First Search (DFS)**: Path finding between nodes
- **Dijkstra's Algorithm**: Single-source shortest paths
- **Floyd-Warshall Algorithm**: All-pairs shortest paths
- **Prim's Algorithm**: Minimum spanning tree
- **Kruskal's Algorithm**: Minimum spanning tree with union-find
- **Strongly Connected Components**: Kosaraju's algorithm
- **Topological Sort**: Kahn's algorithm for DAGs

### Metaheuristics
- **GRASP**: Greedy Randomized Adaptive Search Procedure for optimization problems

## Project Structure

```
graphs-with-grasp/
├── include/                 # Header files
│   ├── Graph.h              # Main graph class
│   ├── Node.h               # Node (vertex) class
│   ├── Edge.h               # Edge class
│   ├── algorithms/          # Algorithm implementations
│   │   ├── Dijkstra.h
│   │   ├── FloydWarshall.h
│   │   ├── Prim.h
│   │   ├── Kruskal.h
│   │   ├── StronglyConnectedComponents.h
│   │   ├── TopologicalSort.h
│   │   └── GRASP.h
│   └── utils/               # Utility functions
│       └── GraphReader.h
├── src/                     # Source files
│   ├── core/                # Core data structures
│   ├── algorithms/          # Algorithm implementations
│   └── utils/               # Utility implementations
├── tests/                   # Unit tests
│   ├── test_Graph.cpp
│   └── test_Algorithms.cpp
├── docs/                    # Documentation
│   ├── requirements.pdf     # Project specification
│   └── latex/               # LaTeX technical report
│       ├── relatorio.tex    # Main LaTeX document
│       ├── capa.tex         # Cover page
│       ├── referencias.bib  # Bibliography
│       └── README.md        # Compilation instructions
├── CMakeLists.txt           # Build configuration
└── README.md               # This file
```

## 📚 Documentation

### Requirements

The complete project requirements are available in:

* **PDF**: `docs/requirements.pdf`

### Technical Report

A comprehensive technical report in LaTeX (following UFJF standards) is located in `docs/latex/`:

* **Main document**: `docs/latex/relatorio.tex`
* **Cover page**: `docs/latex/capa.tex`
* **Bibliography**: `docs/latex/referencias.bib`
* **Compilation instructions**: `docs/latex/README.md`

**To compile the PDF report:**

```bash
cd docs/latex
pdflatex relatorio.tex
bibtex relatorio
pdflatex relatorio.tex
pdflatex relatorio.tex
```

**Recommended:** Use [Overleaf](https://www.overleaf.com/) (online LaTeX editor - no installation needed)

The report includes:
- Introduction and literature review
- Methodology and implementation details
- Algorithm descriptions with pseudocode
- Complexity analysis
- Results and conclusions

## Building the Project

### Prerequisites
- CMake 3.10 or higher
- C++17 compatible compiler (GCC, Clang, or MSVC)
- Git (for fetching Google Test)

### Build Instructions

```bash
# Create build directory
mkdir build
cd build

# Configure and build
cmake ..
cmake --build .

# Run tests
ctest
# Or directly:
./graph_tests
```

### Running the Application

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

## Input File Format

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

## Usage Examples

### Example 1: Find Shortest Path
```cpp
#include "Graph.h"
#include "algorithms/Dijkstra.h"

Graph* graph = new Graph(5, true, true, false);
graph->insertEdge(1, 2, 1.0f);
graph->insertEdge(2, 3, 2.0f);

std::vector<float> distances = Dijkstra::shortestPath(graph, 1);
```

### Example 2: Minimum Spanning Tree
```cpp
#include "Graph.h"
#include "algorithms/Prim.h"

Graph* graph = new Graph(4, false, true, false);
// ... add edges ...

std::vector<std::pair<int, int>> mst = Prim::minimumSpanningTree(graph);
float weight = Prim::getMSTWeight(graph);
```

### Example 3: Topological Sort
```cpp
#include "Graph.h"
#include "algorithms/TopologicalSort.h"

Graph* dag = new Graph(5, true, false, false);
// ... add edges ...

std::vector<int> order = TopologicalSort::sort(dag);
```

## Testing

The project includes comprehensive unit tests using Google Test framework:

```bash
# Run all tests
./graph_tests

# Run specific test
./graph_tests --gtest_filter=GraphTest.*
```

## Algorithm Complexity

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

## Contributing

Contributions are welcome! Please follow these guidelines:
1. Maintain code style consistency
2. Add unit tests for new features
3. Update documentation as needed
4. Follow the existing architecture

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Authors

- **Fabricio Guidine** - Initial work

## Acknowledgments

- Based on the original specification from the graph algorithms course
- Uses Google Test for unit testing framework
- Inspired by classic graph algorithm textbooks

## References

- Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). *Introduction to Algorithms*
- Resende, M. G., & Ribeiro, C. C. (2016). *Optimization by GRASP*
