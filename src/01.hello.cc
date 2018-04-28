#include <memory>
#include <functional>
#include <iostream>
#include <string>

template <class T,class U>
struct AddablePair {
  std::string s;
  T t; U u;

  AddablePair(const T& t, const U& u): t(t), u(u), s("") {}
  AddablePair(const T& t, const U& u, std::string s): t(t), u(u), s(s) {}

  // copy constructor
  AddablePair(const AddablePair<T,U>& o)
      : t(o.t), u(o.u), s(o.s) {
    std::cout << "copy constructor\n";
  }

  // move constructor
  AddablePair(AddablePair<T,U>&& o) noexcept
      : t(std::move(o.t)), u(std::move(o.u)), s(std::move(o.s)) {
    std::cout << "move constructor\n";
  }

  // decltype specifier
  decltype((t + u)) sum() { return (t + u); }
};

template <class T, class U>
AddablePair<T, U> f(AddablePair<T, U> p) {
  return p;
}

int main(int argc, char* argv[]) {
  AddablePair<int, double> l = f(AddablePair<int, double>(7, 9, "awesome"));

  // move semantics
  AddablePair<int, double> m = AddablePair<int, double>(std::move(l));

  std::cout << l.s << ": " << l.t << ", " << l.u << std::endl;
  std::cout << m.s << ": " << m.t << ", " << m.u << std::endl;
 
  // smart pointer
  std::unique_ptr<AddablePair<int, double>> h =
    std::make_unique<AddablePair<int, double>>(3, 4.0);

  std::cout << "sum(): "
            << h->sum() << std::endl;

  return 0;
}
