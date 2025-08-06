cmake_minimum_required(VERSION 3.31)

project(hello_world)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PROJECT_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Gather all source files, including TextEditor.cpp explicitly
file(GLOB_RECURSE SRC_SOURCES "${SRC_DIR}/*.cpp")
set(SOURCES ${SRC_SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/external/text_editor/TextEditor.cpp)

# SINGLE add_executable call with all sources
add_executable(${PROJECT_NAME} ${SOURCES})

# ... rest remains unchanged

# GLAD
add_subdirectory(external/glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)

# GLFW
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory(external/glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

# IMGUI
add_subdirectory(external/imgui)
target_link_libraries(${PROJECT_NAME} PRIVATE imgui)

# lua
add_subdirectory(external/lua)
target_link_libraries(${PROJECT_NAME} PRIVATE lua)

# Magic enum
add_subdirectory(external/magic_enum)
target_link_libraries(${PROJECT_NAME} PRIVATE magic_enum)

include(FetchContent)
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(json)

find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE external/glad/include)
target_include_directories(${PROJECT_NAME} PRIVATE external/glfw/include)
target_include_directories(${PROJECT_NAME} PRIVATE external/imgui)
target_include_directories(${PROJECT_NAME} PRIVATE external/lua)
target_include_directories(${PROJECT_NAME} PRIVATE external/magic_enum)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_HEADER_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${GLM_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE external/text_editor)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
