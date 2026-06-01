# graphs-optimization

C++ coursework implementing classic graph algorithms and a GRASP metaheuristic, with GoogleTest unit tests and optional Google Benchmark micro-benchmarks.

[![CI](https://github.com/fabricioguidine/graphs-optimization/actions/workflows/ci.yml/badge.svg?branch=master)](https://github.com/fabricioguidine/graphs-optimization/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/17)

The graph data structure supports directed/undirected and edge/node-weighted graphs. A single `graph_algorithms` executable reads an instance and runs algorithms through an interactive menu.

## Algorithms

| Algorithm | Problem | Time | Space |
|---|---|---|---|
| BFS | Level-order traversal | O(V + E) | O(V) |
| DFS | Path existence between two nodes | O(V + E) | O(V) |
| Dijkstra | Single-source shortest paths | O((V + E) log V) | O(V) |
| Floyd-Warshall | All-pairs shortest paths | O(V³) | O(V²) |
| Prim | Minimum spanning tree | O((V + E) log V) | O(V) |
| Kruskal | Minimum spanning tree (union-find) | O(E log E) | O(V) |
| Strongly Connected Components | SCC decomposition | O(V + E) | O(V) |
| Topological Sort | Linear order of a DAG | O(V + E) | O(V) |
| GRASP | Greedy randomized adaptive search metaheuristic | O(I × (C + L)) | O(V) |

Also includes graph complement and connectivity checks.

## Build

Requires CMake 3.14+ and a C++17 compiler (GCC, Clang, or MSVC). Tests fetch GoogleTest via `FetchContent` at configure time.

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
```

The binary is written to `build/bin/graph_algorithms`.

### CMake options

| Option | Default | Description |
|---|---|---|
| `GRAPHS_BUILD_TESTS` | `ON` | Build GoogleTest unit tests |
| `GRAPHS_BUILD_BENCHMARKS` | `OFF` | Build Google Benchmark micro-benchmarks |
| `GRAPHS_ENABLE_COVERAGE` | `OFF` | gcov instrumentation (GCC/Clang) |
| `GRAPHS_ENABLE_ASAN` | `OFF` | AddressSanitizer |
| `GRAPHS_ENABLE_UBSAN` | `OFF` | UndefinedBehaviorSanitizer |
| `GRAPHS_ENABLE_TSAN` | `OFF` | ThreadSanitizer |
| `GRAPHS_WARNINGS_AS_ERRORS` | `OFF` | Pass `-Werror` / `/WX` |

## Usage

```bash
./build/bin/graph_algorithms <input_file> <output_file> <directed> <weighted_edge> <weighted_node>
```

The last three flags are `0`/`1`. The program then presents a menu (BFS, DFS, Dijkstra, Floyd-Warshall, Prim, Kruskal, SCC, topological sort, GRASP, complement, connectivity); results are appended to `<output_file>`. Example:

```bash
./build/bin/graph_algorithms input.txt output.txt 1 1 0
```

### Input format

First line is the graph order and edge count; each remaining line is an edge as a source/target node pair:

```
<order> <num_edges>
<source_id> <target_id>
...
```

## Running benchmarks

Build the optional Google Benchmark target (Release recommended):

```bash
cmake -S . -B build-bench -DGRAPHS_BUILD_BENCHMARKS=ON -DCMAKE_BUILD_TYPE=Release
cmake --build build-bench --target graph_benchmarks --parallel
./build-bench/bin/graph_benchmarks
```

The benchmarks (`tests/bench_Algorithms.cpp`) time Dijkstra, Prim, Kruskal, and Floyd-Warshall on randomly generated sparse connected graphs across sizes (64–1024 vertices) and report measured complexity.

## Testing

Unit tests run through CTest:

```bash
ctest --test-dir build --output-on-failure
```

Coverage (Linux/macOS with `gcovr`):

```bash
cmake -S . -B build-cov -DGRAPHS_ENABLE_COVERAGE=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build-cov --parallel
ctest --test-dir build-cov --output-on-failure
gcovr -r . --exclude 'build-cov/_deps/.*' --exclude 'tests/.*' --html -o coverage.html
```

## Data instances

Benchmark graph instances live under `data/instances/`. Use `scripts/setup_data.py` to create the directory layout and generate sample graphs:

```bash
python scripts/setup_data.py
```

## Project structure

```
graphs-optimization/
├── include/                # Headers (Graph, Node, Edge, algorithms/, utils/)
├── src/
│   ├── core/               # Graph, Node, Edge
│   ├── algorithms/         # Dijkstra, FloydWarshall, Prim, Kruskal, SCC, TopologicalSort, GRASP
│   ├── utils/              # GraphReader
│   └── main.cpp            # Interactive menu entry point
├── tests/                  # GoogleTest suites + bench_Algorithms.cpp
├── data/instances/         # Benchmark graph instances
├── docs/                   # Requirements, LaTeX report, literature
├── scripts/                # setup_data.py
└── CMakeLists.txt
```

A LaTeX technical report and the project requirements are in `docs/`.

## License

MIT. See [LICENSE](LICENSE).
