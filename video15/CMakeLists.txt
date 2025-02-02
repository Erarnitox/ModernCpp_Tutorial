cmake_minimum_required(VERSION 3.31)
project(cpp_tutorial LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include CPM.cmake
include(cmake/CPM.cmake)

# Add SDL3
CPMAddPackage(
    NAME SDL3
    GITHUB_REPOSITORY libsdl-org/SDL
    GIT_TAG main          # or use a specific release tag
)

# Add Dear ImGui
CPMAddPackage(
    NAME imgui
    GITHUB_REPOSITORY ocornut/imgui
    GIT_TAG docking       # or use a specific version tag
)

# Build ImGui with SDL3 and OpenGL3 backends
add_library(imgui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_sdl3.cpp
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Include directories
include_directories(
    ${SDL3_INCLUDE_DIRS}
    ${imgui_SOURCE_DIR}
    ${imgui_SOURCE_DIR}/backends
)

add_executable(example
    main.cpp
)

# Link libraries
target_link_libraries(example PRIVATE 
    SDL3::SDL3
    imgui
    OpenGL::GL
)

target_compile_options(example PRIVATE
    -Werror            # Treat all warnings as errors
    -Wall              # Enable most compiler warnings
    -Wextra            # Enable extra warnings
    -Wconversion       # Warn about implicit conversions
)

# Enable testing framework
enable_testing()

# Add the tester executable
add_executable(tester tests.cpp)

# Add the test
add_test(NAME Tester COMMAND tester)
