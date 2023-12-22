cmake_minimum_required (VERSION 3.5)
project (Eval)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

set (src_dir "${PROJECT_SOURCE_DIR}/source/")
set (lib_dir "${PROJECT_SOURCE_DIR}/lib/")

file (GLOB src_files "${src_dir}/*.c")
file (GLOB lib_files "${lib_dir}/*.c")

add_executable(${PROJECT_NAME} main.c ${src_files} ${lib_files})
target_link_libraries(${PROJECT_NAME} m)
