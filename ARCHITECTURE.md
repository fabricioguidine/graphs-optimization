# Architecture

This document describes the module layout, graph input format, algorithms, and
the build/test strategy for the project.

## Overview

A C++17 library and command-line tool implementing classic graph algorithms.
The code is split into a reusable static library (`graphs_lib`), a thin CLI
driver (`graph_algorithms`), and a Google Test suite (`graph_tests`). The build
is fully cross-platform via CMake and runs on GCC, Clang, and MSVC.

## Source layout

```
include/
  Graph.h, Node.h, Edge.h          # Core data structures
  algorithms/                      # Algorithm declarations
    Dijkstra.h  FloydWarshall.h
    Prim.h      Kruskal.h
    TopologicalSort.h
    StronglyConnectedComponents.h
    GRASP.h
  utils/GraphReader.h              # File-instance reader
src/
  core/    Graph.cpp Node.cpp Edge.cpp
  algorithms/  (one .cpp per header above)
  utils/   GraphReader.cpp
  main.cpp                         # CLI entry point
tests/                             # Google Test sources (see Testing)
CMakeLists.txt                     # Single portable build definition
.github/workflows/ci.yml           # CI matrix (Linux/macOS/Windows)
```

## Core data structures

- `Graph` (`GraphLib::Graph`) — adjacency representation supporting directed/
  undirected, edge-weighted, and node-weighted variants. Constructed with
  `Graph(order, directed, weightedEdge, weightedNode)`. Nodes are addressed by
  integer id; `insertEdge(src, tgt, weight)` builds the structure.
- `Node` / `Edge` — node and edge records (id, weight, adjacency links).

All types live in the `GraphLib` namespace.

## Algorithms

| Algorithm | Entry point | Asserted output |
|-----------|-------------|-----------------|
| Dijkstra (single-source shortest path) | `Dijkstra::shortestPath / getDistance / shortestPathTo` | per-node distances |
| Floyd–Warshall (all-pairs shortest path) | `FloydWarshall::allPairsShortestPath` | distance matrix |
| Prim (MST) | `Prim::minimumSpanningTree / getMSTWeight` | MST edge set / total weight |
| Kruskal (MST, union-find) | `Kruskal::minimumSpanningTree / getMSTWeight` | MST edge set / total weight |
| Topological sort | `TopologicalSort::sort` | linear order of a DAG |
| Strongly connected components | `StronglyConnectedComponents::findSCC / getSCCCount` | component partition |
| GRASP (metaheuristic) | `GRASP` | heuristic solution / objective |

## Input format

Two readers in `GraphReader`:

- `readFromFile(path, directed, weightedEdge, weightedNode)` — first token is
  the graph **order** (node count), followed by edge records whose shape
  depends on the weight flags:
  - unweighted: `source target`
  - edge-weighted: `source target weight`
  - node-weighted: `source srcWeight target tgtWeight`
  - both: `source srcWeight target tgtWeight weight`
- `readInstance(path, ...)` — header is `order numEdges`, then `source target`
  pairs (used by the CLI for benchmark instances).

File I/O uses `std::ifstream`/`std::ofstream` exclusively; the CLI opens files
in `std::ios::trunc` mode for deterministic output. A missing or unreadable
file yields a `nullptr` graph (checked by callers and tests).

## CLI

```
graph_algorithms <input_file> <output_file> <directed> <weighted_edge> <weighted_node>
```

The flags are `0`/`1`. The driver reads an instance, runs the selected
operations, and writes results to the output file.

## Build and test layout

- **Build system:** a single `CMakeLists.txt` (C++17, extensions off). Warning
  flags are compiler-gated: `-Wall -Wextra -Wpedantic ...` for GNU/Clang and
  `/W4 /permissive-` for MSVC. Opt-in options expose coverage (gcov),
  AddressSanitizer/UBSan/TSan, benchmarks (Google Benchmark), and
  warnings-as-errors.
- **Test framework:** Google Test, fetched at configure time with CMake
  `FetchContent` (tag `v1.14.0`, `gtest_force_shared_crt=ON` for MSVC). Tests
  are registered with `gtest_discover_tests` and run via CTest.
- **Test categories:**
  - *Per-algorithm unit tests* (`test_Dijkstra.cpp`, `test_Kruskal.cpp`, …) —
    assert known outputs on small handcrafted graphs.
  - *Invariant / property tests* (`test_Invariants.cpp`) — algorithmic
    invariants on handcrafted and seeded-random graphs (triangle inequality,
    MST has V−1 edges, Prim/Kruskal agree, Floyd–Warshall matches Dijkstra,
    topological order respects edges).
  - *End-to-end tests* (`test_EndToEnd.cpp`) — write a known instance to a temp
    file (via `std::filesystem`), read it back through `GraphReader`, run an
    algorithm, and assert the textbook result. This exercises the full
    file-I/O pipeline and cross-platform path handling.

## Cross-platform notes

- No POSIX-only headers (`unistd.h`, `<sys/*>`, `getopt`) — only standard
  library headers are used.
- No GCC builtins, inline `asm`, or `__attribute__` in portable code.
- No variable-length arrays (rejected by MSVC); containers are `std::vector`.
- Paths and temp directories use `std::filesystem` (C++17).
- CI builds and tests the matrix `{ubuntu, macos, windows} × {C++17, C++20}`
  plus explicit GCC and Clang jobs on Linux.
