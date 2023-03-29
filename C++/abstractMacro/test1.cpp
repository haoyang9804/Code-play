#include <iostream>

// () is used to protect the scope of xy
#define ABSTRACT_MACRO(x) (#x"y")

int main() {
  std::cout << 
#include "macro.inc" 
<< std::endl;
}