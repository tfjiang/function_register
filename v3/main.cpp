#include <any>
#include <functional>
#include <iostream>
#include <vector>

template <typename Ret> 
struct AnyCallable {
  AnyCallable() {}

  template <typename... Args>
  AnyCallable(std::function<Ret(Args...)> fun) : m_any(fun) {}

  template <typename... Args> 
  Ret operator()(Args &&... args) {
    return std::invoke(std::any_cast<std::function<Ret(Args...)>>(m_any),
                       std::forward<Args>(args)...);
  }

  std::any m_any;
};


void print_test(const std::string& a)
{
  std::cout << a << std::endl;
}

int main()
{
  std::vector<AnyCallable<void> > func_vecs;

  const std::function<void(const std::string &)> &f1 = std::bind(print_test, std::placeholders::_1);
  const std::function<void()> &f2 = [](){std::cout << "helloworld." << std::endl;};
    
  func_vecs.emplace_back(f1);
  func_vecs.emplace_back(f2);

  // test
  const std::string & a = "hello2";
  func_vecs[0](a);
  func_vecs[1]();
  
  return 0;
}
