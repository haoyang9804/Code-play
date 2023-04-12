#include <iostream>
#include <map>

using namespace std;

class A {
private:
  static A* a_;
  A() {};
public:
  static A* getInstance();
};

A* A::a_ = nullptr;
A* A::getInstance() {
  if (a_ == nullptr) {
    a_ = new A();
  }
  return a_;
}

class B {

};

class C : public B {
  
};

int main() {
  map<A*, int>mp;
  mp[A::getInstance()] = 1;
  if(mp.count(A::getInstance())) {
    cout << 1 << endl;
  }

  map<B*, int> mp2;
  mp2[new B()] = 1;
  if (mp2.count(new B())) {
    cout << 2 << endl;
  }

  C* c = new C();
  B* bc = c;
  
}