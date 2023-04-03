#include <iostream>

class A {
public:
  void f() { std::cout << "A" << std::endl; }
};

class B : public A {
public:
  void f() { std::cout << "B" << std::endl; }
};

void fun(A a) {
  a.f();
}

class C {
public:
  void f() { std::cout << "C" << std::endl; }
};

class D : public C {
public:
  void f() { std::cout << "D" << std::endl; }
};

void fun2(C* c) {
  c->f();
}

class E {
public:
  virtual void f() = 0;
};

class F : public E {
public:
  void f() override { std::cout << "F" << std::endl; }
};

class G : public E {
public:
  void f() override { std::cout << "G" << std::endl; }
};

void fun3(E* e) {
  e->f();
}


int main() {
  B b;
  fun(b); // A

  D* d = new D();
  fun2(d); // C
  C* cd = new D();
  fun2(cd); // C

  F* f = new F(); 
  G* g = new G();
  fun3(f); // F
  fun3(g); // G

  E* ef = new F(); 
  E* eg = new G();
  fun3(ef); // F
  fun3(eg); // G

}