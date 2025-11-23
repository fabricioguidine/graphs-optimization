# Building the Project

This document provides detailed instructions for building the Graph Algorithms project.

## Prerequisites

- **CMake** 3.10 or higher
- **C++ Compiler** supporting C++17:
  - Windows: MinGW-w64, MSVC, or Clang
  - Linux: GCC 7+ or Clang 5+
  - macOS: Xcode Command Line Tools
- **Git** (for fetching Google Test)

## Quick Build

```bash
# Create build directory
mkdir build
cd build

# Configure
cmake ..

# Build
cmake --build .

# Run tests
ctest
# Or directly:
./bin/graph_tests
```

## IDE Setup

### CLion
1. Open the project folder
2. CLion automatically detects `CMakeLists.txt` at root
3. Build: `Build > Build Project` (Ctrl+F9)
4. Run: `Run > Run 'graph_algorithms'` (Shift+F10)

### Visual Studio Code
1. Install extensions: C/C++, CMake Tools
2. Open project folder
3. Press `Ctrl+Shift+P` → "CMake: Configure"
4. Build: `Ctrl+Shift+P` → "CMake: Build"
5. Debug: Press F5

### Visual Studio (Windows)
1. File → Open → CMake → Select `CMakeLists.txt`
2. Build: `Build > Build Solution` (Ctrl+Shift+B)
3. Run: `Debug > Start Debugging` (F5)

## Build Options

### Debug Build
```bash
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build .
```

### Release Build
```bash
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

### Build Specific Target
```bash
cmake --build . --target graph_algorithms
cmake --build . --target graph_tests
```

## Troubleshooting

### Compiler Not Found
- **Windows**: Install MinGW-w64 or Visual Studio Build Tools
- **Linux**: `sudo apt-get install build-essential` (Ubuntu/Debian)
- **macOS**: `xcode-select --install`

### CMake Not Found
- Download from: https://cmake.org/download/
- Or use package manager:
  - Windows: `choco install cmake`
  - Linux: `sudo apt-get install cmake`
  - macOS: `brew install cmake`

### Google Test Download Issues
- Check internet connection
- CMake will download Google Test automatically on first build
- If issues persist, manually clone: `git clone https://github.com/google/googletest.git`

## Output Locations

- **Executables**: `build/bin/`
- **Libraries**: `build/lib/`
- **Test Results**: `build/Testing/`

## Clean Build

```bash
# Remove build directory
rm -rf build  # Linux/Mac
rmdir /s build  # Windows

# Rebuild
mkdir build && cd build
cmake ..
cmake --build .
```

