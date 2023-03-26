#include <iostream>
#include <concepts>
#include <type_traits>

// It's best to put Type and Concept definitions at the top

// assure that arguments *as* could be passed to function *f*
template<typename Fp, typename... A>
concept AcanPasstoFp = requires(Fp f, A... as) {
  f(as...);
};
template<typename R, typename Fp, typename... A>
requires AcanPasstoFp<Fp, A...>
using WrapperType = R(*)(Fp, A...);

template<typename R, typename Fp, typename... A>
void metaWrapper(WrapperType<R, Fp, A...> wrapper, Fp f, A... as) {
  wrapper(f, as...);
}

template<typename R, typename... A, typename Fp = R(*)(A...)>
void wrapper1(Fp f, A... as) {
	std::cout << "wrapper1 !!" << std::endl;
  f(as...);
}

template<typename R, typename... A, typename Fp = R(*)(A...)>
void wrapper2(Fp f, A... as) {
	std::cout << "wrapper2 !!" << std::endl;
  f(as...);
}

void f1(int x) {
  std::cout << "f1" << std::endl;
}

void f2() {
  std::cout << "f2" << std::endl;
}




int main() {
  WrapperType<void, void(*)(int), int> wrapper = wrapper1<void, int>;
  // wrapper1 !!
  // f1
	metaWrapper(wrapper, f1, 1);

  // wrapper1 !!
  // f1
  metaWrapper(wrapper1<void, int>, f1, 1);

  metaWrapper<void, void (*)(int), int>(wrapper1, f1, 1);

  // will crash, don't know why
  // metaWrapper(wrapper1, f1, 1); 
}