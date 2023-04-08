#include <iostream>

class A {
protected:
  int a = 3;
};

class B : public A {
public:
  void f() {
    std::cout << this->a << std::endl;
  }
};

int main() {
  B b;
  b.f();
}