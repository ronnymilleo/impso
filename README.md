# Particle Swarm Optimization (PSO) in C++

A modern C++23, real-time Particle Swarm Optimization visualization tool designed to help people learn about the algorithm and experiment with its parameters interactively.

## Overview

This project provides a fast, flexible, and visually interactive framework for solving continuous optimization problems. The primary goal is to serve as an educational tool where you can visualize the swarm's progress and tweak parameters on the fly to understand how the inertia weight, social, and cognitive coefficients affect the particles in real-time.

## Features

*   **Interactive Visualization**: Real-time rendering of the particle swarm and objective function landscape using ImGui and ImPlot.
*   **Dynamic Parameter Tweaking**: Change algorithm parameters directly through the UI without recompiling.
*   **Multiple PSO Variants**: Starting with Standard PSO, with more variants planned as the project evolves.
*   **Standard Benchmarks**: Includes standard mathematical optimization benchmarks (like Rastrigin, Rosenbrock) to test the swarm's capabilities.
*   **Modern C++23**: Leverages the latest C++ features for maximum performance and memory safety.
*   **Modular Architecture**: Clean separation between the core optimization library and the graphical application.

## Dependencies

This project relies on the following robust open-source libraries (included as Git submodules in `vendor/`):
*   [GLFW](https://www.glfw.org/) - Windowing and input.
*   [Dear ImGui](https://github.com/ocornut/imgui) - Graphical User Interface.
*   [ImPlot](https://github.com/epezent/implot) - Advanced plotting.
*   [spdlog](https://github.com/gabime/spdlog) - Fast C++ logging library.
*   [GoogleTest](https://github.com/google/googletest) - Testing framework.

## Building the Project

### Prerequisites

*   A C++23 compatible compiler (GCC 13+, Clang 16+, or MSVC).
*   CMake (3.28 or higher).
*   Git.

### Instructions

1.  **Clone the repository correctly:**
    Because this project uses git submodules for its dependencies, make sure to clone with the `--recursive` flag:
    ```bash
    git clone --recursive https://github.com/ronnymilleo/impso.git
    cd impso
    ```
    *(If you already cloned without submodules, run `git submodule update --init --recursive`)*.

2.  **Configure and Build (Release Mode):**
    ```bash
    mkdir build && cd build
    cmake .. -DCMAKE_BUILD_TYPE=Release
    cmake --build . --parallel
    ```

3.  **Run the application:**
    ```bash
    ./out/release/bin/PSO
    ```

## Running Tests

To build and run the unit tests:
```bash
cd build
cmake .. -DPSO_BUILD_TESTS=ON
cmake --build . --parallel
ctest --output-on-failure
```

## License

This project is licensed under the [GNU General Public License v3.0 (GPL-3.0)](LICENSE).
