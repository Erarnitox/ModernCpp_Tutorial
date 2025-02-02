cmake_minimum_required(VERSION 3.31)
project(cpp_tutorial LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(example
    main.cpp
)

target_compile_options(example PRIVATE
    -Werror            # Treat all warnings as errors
    -Wall              # Enable most compiler warnings
    -Wextra            # Enable extra warnings
    -Wconversion       # Warn about implicit conversions
)
