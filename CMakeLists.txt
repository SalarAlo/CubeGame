cmake_minimum_required(VERSION 3.31)

project(hello_world)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PROJECT_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# source files
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

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

# require packages
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

# include dirs
target_include_directories(${PROJECT_NAME} PRIVATE external/glad/include)
target_include_directories(${PROJECT_NAME} PRIVATE external/glfw/include)
target_include_directories(${PROJECT_NAME} PRIVATE external/imgui)
target_include_directories(${PROJECT_NAME} PRIVATE external/lua)
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_HEADER_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${GLM_INCLUDE_DIRS})

# link library
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)

