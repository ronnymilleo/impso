# =============================================================================
# Tests
# =============================================================================

add_executable(pso_tests pso_tests.cpp)

target_link_libraries(pso_tests PRIVATE pso gtest_main)

include(GoogleTest)
gtest_discover_tests(pso_tests)
