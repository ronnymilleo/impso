# =============================================================================
# App setup
# =============================================================================

cmake_minimum_required(VERSION 3.28)

add_library(app_gui STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/app_gui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/imgui_layer.cpp
)

target_include_directories(app_gui 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/library/include
)

target_link_libraries(app_gui 
    PUBLIC 
        imgui
        implot
        spdlog
)

# =============================================================================
# Main Executable Target
# =============================================================================

add_executable(impso
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_include_directories(impso
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/library/include
)

target_link_libraries(impso 
    PRIVATE 
        app_gui
)



# =============================================================================
# End of file
# =============================================================================
