cmake_minimum_required(VERSION 3.0)
project(my_project)

# Find LLVM package
find_package(LLVM REQUIRED CONFIG)

# Set include directories
include_directories(${LLVM_INCLUDE_DIRS})
message("LLVM Include DIR is " ${LLVM_INCLUDE_DIRS})

# Set link directories
link_directories(${LLVM_LIBRARY_DIRS})
message("LLVM Library Dir is " ${LLVM_LIBRARY_DIRS})

# Set link libraries
llvm_map_components_to_libnames(llvm_libs support core irreader)

# # Add executable target
# add_executable(my_target main.cpp)

# # Link target to LLVM libraries
# target_link_libraries(my_target ${llvm_libs})