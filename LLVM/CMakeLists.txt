cmake_minimum_required(VERSION 3.10)

if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
  set(CMAKE_CXX_COMPILER /Users/mahaoyang/repo/llvm-install/bin/clang++)
  set(CMAKE_C_COMPILER /Users/mahaoyang/repo/llvm-install/bin/clang)
elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
  set(CMAKE_CXX_COMPILER /home/gakki/llvm-install-byClang10-rtti/bin/clang++)
  set(CMAKE_C_COMPILER /home/gakki/llvm-install-byClang10-rtti/bin/clang)
endif()

project(LLVM-play)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM? ${LLVM_FOUND}" )
message(STATUS "LLVM version: ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
include(${LLVM_DIR}/AddLLVM.cmake)
message(STATUS "Using AddLLVM.cmake to support add_llvm_executable")

find_package(Clang REQUIRED CONFIG)
message(STATUS "Found Clang? ${Clang_FOUND}")
message(STATUS "Using ClangConfig.cmake in: ${Clang_DIR}")
include(${Clang_DIR}/AddClang.cmake)
message(STATUS "Using AddClang.cmake to support add_clang_executable")

add_subdirectory(CommandLine)
add_subdirectory(ASTVisitor)