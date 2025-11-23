#!/usr/bin/env python3
"""
Data Setup Script for Graph Algorithms Project
Downloads and prepares graph instances for testing and benchmarking
"""

import os
import sys
import shutil
from pathlib import Path

def create_directory_structure():
    """Create necessary directory structure for data"""
    base_dir = Path(__file__).parent.parent
    data_dir = base_dir / "data"
    instances_dir = data_dir / "instances"
    
    directories = [
        data_dir,
        instances_dir,
        instances_dir / "unweighted",
        instances_dir / "weighted",
        instances_dir / "problem-instances",
    ]
    
    for directory in directories:
        directory.mkdir(parents=True, exist_ok=True)
        print(f"✓ Created directory: {directory}")
    
    return data_dir

def check_existing_instances():
    """Check if graph instances already exist"""
    base_dir = Path(__file__).parent.parent
    instances_dir = base_dir / "data" / "instances"
    
    unweighted_dir = instances_dir / "unweighted"
    weighted_dir = instances_dir / "weighted"
    problem_dir = instances_dir / "problem-instances"
    
    unweighted_count = len(list(unweighted_dir.glob("*.txt"))) if unweighted_dir.exists() else 0
    weighted_count = len(list(weighted_dir.glob("*.txt"))) if weighted_dir.exists() else 0
    problem_count = len(list(problem_dir.rglob("*.txt"))) if problem_dir.exists() else 0
    
    return {
        "unweighted": unweighted_count,
        "weighted": weighted_count,
        "problem_instances": problem_count
    }

def generate_sample_graph(output_path, num_nodes, num_edges, weighted=False):
    """Generate a sample graph file for testing"""
    output_path = Path(output_path)
    output_path.parent.mkdir(parents=True, exist_ok=True)
    
    import random
    
    with open(output_path, 'w') as f:
        f.write(f"{num_nodes} {num_edges}\n")
        
        edges_generated = 0
        while edges_generated < num_edges:
            source = random.randint(1, num_nodes)
            target = random.randint(1, num_nodes)
            
            if source != target:
                if weighted:
                    weight = round(random.uniform(0.1, 10.0), 2)
                    f.write(f"{source} {target} {weight}\n")
                else:
                    f.write(f"{source} {target}\n")
                edges_generated += 1
    
    print(f"✓ Generated sample graph: {output_path} ({num_nodes} nodes, {num_edges} edges)")

def generate_test_instances():
    """Generate test instances if they don't exist"""
    base_dir = Path(__file__).parent.parent
    instances_dir = base_dir / "data" / "instances"
    
    # Check existing instances
    counts = check_existing_instances()
    
    if counts["unweighted"] == 0:
        print("\n📝 Generating sample unweighted graphs...")
        unweighted_dir = instances_dir / "unweighted"
        generate_sample_graph(unweighted_dir / "test_small.txt", 10, 15, weighted=False)
        generate_sample_graph(unweighted_dir / "test_medium.txt", 50, 100, weighted=False)
        generate_sample_graph(unweighted_dir / "test_large.txt", 100, 200, weighted=False)
    
    if counts["weighted"] == 0:
        print("\n📝 Generating sample weighted graphs...")
        weighted_dir = instances_dir / "weighted"
        generate_sample_graph(weighted_dir / "test_small.txt", 10, 15, weighted=True)
        generate_sample_graph(weighted_dir / "test_medium.txt", 50, 100, weighted=True)
        generate_sample_graph(weighted_dir / "test_large.txt", 100, 200, weighted=True)

def validate_graph_file(file_path):
    """Validate a graph file format"""
    file_path = Path(file_path)
    
    if not file_path.exists():
        return False, "File does not exist"
    
    try:
        with open(file_path, 'r') as f:
            lines = f.readlines()
            if len(lines) < 1:
                return False, "File is empty"
            
            # Check first line (order and num_edges)
            first_line = lines[0].strip().split()
            if len(first_line) < 2:
                return False, "Invalid format: first line should contain order and num_edges"
            
            order = int(first_line[0])
            num_edges = int(first_line[1])
            
            # Check edge lines
            edge_count = 0
            for line in lines[1:]:
                parts = line.strip().split()
                if len(parts) >= 2:
                    edge_count += 1
            
            return True, f"Valid: {order} nodes, {edge_count} edges found"
    
    except Exception as e:
        return False, f"Error reading file: {str(e)}"

def list_available_instances():
    """List all available graph instances"""
    base_dir = Path(__file__).parent.parent
    instances_dir = base_dir / "data" / "instances"
    
    print("\n📊 Available Graph Instances:")
    print("=" * 60)
    
    # Unweighted
    unweighted_dir = instances_dir / "unweighted"
    if unweighted_dir.exists():
        unweighted_files = list(unweighted_dir.glob("*.txt"))
        if unweighted_files:
            print(f"\nUnweighted Graphs ({len(unweighted_files)} files):")
            for f in sorted(unweighted_files)[:10]:  # Show first 10
                print(f"  - {f.name}")
            if len(unweighted_files) > 10:
                print(f"  ... and {len(unweighted_files) - 10} more")
    
    # Weighted
    weighted_dir = instances_dir / "weighted"
    if weighted_dir.exists():
        weighted_files = list(weighted_dir.glob("*.txt"))
        if weighted_files:
            print(f"\nWeighted Graphs ({len(weighted_files)} files):")
            for f in sorted(weighted_files)[:10]:  # Show first 10
                print(f"  - {f.name}")
            if len(weighted_files) > 10:
                print(f"  ... and {len(weighted_files) - 10} more")
    
    # Problem instances
    problem_dir = instances_dir / "problem-instances"
    if problem_dir.exists():
        problem_files = list(problem_dir.rglob("*.txt"))
        if problem_files:
            print(f"\nProblem Instances ({len(problem_files)} files)")
            print(f"  Location: {problem_dir}")

def main():
    """Main function"""
    print("🚀 Graph Algorithms - Data Setup Script")
    print("=" * 60)
    
    # Create directory structure
    print("\n📁 Creating directory structure...")
    data_dir = create_directory_structure()
    
    # Check existing instances
    print("\n🔍 Checking existing instances...")
    counts = check_existing_instances()
    print(f"  Unweighted graphs: {counts['unweighted']}")
    print(f"  Weighted graphs: {counts['weighted']}")
    print(f"  Problem instances: {counts['problem_instances']}")
    
    # Generate test instances if needed
    if counts["unweighted"] == 0 and counts["weighted"] == 0:
        print("\n⚠️  No graph instances found. Generating sample instances...")
        generate_test_instances()
    else:
        print("\n✓ Graph instances already available")
    
    # List available instances
    list_available_instances()
    
    print("\n" + "=" * 60)
    print("✅ Data setup complete!")
    print("\nUsage examples:")
    print("  ./graph_algorithms data/instances/unweighted/test_small.txt output.txt 0 0 0")
    print("  ./graph_algorithms data/instances/weighted/test_small.txt output.txt 0 1 0")

if __name__ == "__main__":
    main()

