cmake_minimum_required(VERSION 3.31)
project(hello_modules)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(hello_modules)
target_sources(hello_modules PUBLIC
    "${PROJECT_SOURCE_DIR}/main.cpp"
PUBLIC
FILE_SET CXX_MODULES
FILES
    "${PROJECT_SOURCE_DIR}/my_module.cpp"
)