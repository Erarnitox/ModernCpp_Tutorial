cmake_minimum_required(VERSION 3.31)
project(hello_filesystem)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(bulk_rename)
target_sources(bulk_rename PUBLIC
    "${PROJECT_SOURCE_DIR}/main.cpp"
PUBLIC
FILE_SET CXX_MODULES
FILES
    "${PROJECT_SOURCE_DIR}/file_module.cpp"
)