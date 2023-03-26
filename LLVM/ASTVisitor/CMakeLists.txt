add_subdirectory(Helper)

add_clang_executable(astplayer ASTplayer.cpp)

target_include_directories(astplayer PRIVATE Helper)

target_link_libraries(astplayer
  PRIVATE
  filereader
  clangAST
  clangBasic
  clangFrontend
  clangSerialization
  clangTooling
  )