# Scripts Directory

This directory contains utility scripts for the Graph Algorithms project.

## setup_data.py

Python script to set up and prepare graph data instances for testing and benchmarking.

### Usage

```bash
# Run from project root
python scripts/setup_data.py

# Or make it executable (Linux/Mac)
chmod +x scripts/setup_data.py
./scripts/setup_data.py
```

### Features

- Creates necessary directory structure for data
- Checks for existing graph instances
- Generates sample test graphs if none exist
- Validates graph file formats
- Lists all available instances

### Generated Test Graphs

If no instances are found, the script generates:
- **Unweighted graphs**: `test_small.txt`, `test_medium.txt`, `test_large.txt`
- **Weighted graphs**: `test_small.txt`, `test_medium.txt`, `test_large.txt`

### Requirements

- Python 3.7 or higher
- Standard library only (no external dependencies)

