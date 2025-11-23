# Data Directory

This directory contains graph instances and test data for the project.

## Structure

```
data/
├── instances/                # Graph instances
│   ├── unweighted/          # Unweighted graph instances
│   ├── weighted/            # Weighted graph instances
│   └── problem-instances/   # Problem-specific instances (T1, T2)
└── README.md                # This file
```

## Usage

Graph instances can be used for testing and benchmarking algorithms:

```bash
# Example: Run algorithm on unweighted graph
./graph_algorithms data/instances/unweighted/unweighted-graph-instances/grafo_1000_1.txt output.txt 0 0 0

# Example: Run algorithm on weighted graph
./graph_algorithms data/instances/weighted/weighted-graph-instances/grafo_1000.txt output.txt 0 1 0
```

## File Formats

### Unweighted Graphs
Format: `<order> <num_edges>` followed by edge pairs
```
5 7
1 2
2 3
3 4
...
```

### Weighted Graphs
Format: `<order> <num_edges>` followed by edge pairs with weights
```
5 7
1 2 1.5
2 3 2.0
3 4 1.0
...
```

## Problem Instances

The `problem-instances/` directory contains instances for specific problems (T1, T2) from the second part of the project.

