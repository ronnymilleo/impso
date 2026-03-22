# =============================================================================
# Library
# =============================================================================

add_library(pso STATIC
    src/pso.cpp
    src/benchmarks.cpp
)

target_include_directories(pso PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
