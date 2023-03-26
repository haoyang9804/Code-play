#include <iostream>
using namespace std;

void fun() {
}

template<class T, class... Others>
void fun(T x, Others... o) {
  cout << std::forward<T>(x) << endl;
  fun(std::forward<Others>(o)...);
}

int main() {
  fun (1,2,3);
}