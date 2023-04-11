#include <iostream>
#include <memory>
using namespace std;

class A {
public:
  shared_ptr<int> p;
};

auto f() {
  shared_ptr<A> a = make_shared<A>();
  a->p = make_shared<int>(1);
  return a;
}

int main() {
  auto a = f();
  cout << a.use_count() << " " << a->p.use_count() << endl;
}