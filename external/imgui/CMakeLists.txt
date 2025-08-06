
cmake_minimum_required(VERSION 3.10)
project(imgui)

add_library(imgui STATIC
    imgui.cpp
    imgui_draw.cpp
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui_demo.cpp
    backends/imgui_impl_glfw.cpp        # Add this
    backends/imgui_impl_opengl3.cpp     # Add this
)

target_include_directories(imgui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/backends   # Ensure backend headers are found
)

