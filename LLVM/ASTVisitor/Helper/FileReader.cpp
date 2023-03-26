#include "FileReader.hpp"

#include <fstream>
#include <sstream>

std::string readFile(std::string filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    return "";
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}