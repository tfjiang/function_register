#include <any>
#include <functional>
#include <iostream>
#include <vector>
#include <boost/type_index.hpp>

template <typename Ret> 
struct AnyCallable {
  AnyCallable() {}

  template <typename... Args>
  AnyCallable(std::function<Ret(Args...)> fun) : m_any(fun) {
    std::cout << boost::typeindex::type_id_with_cvr<std::function<Ret(Args...)>>().pretty_name()<< std::endl;
  }

  template <typename... Args> 
  Ret operator()(Args &&... args) {
    std::cout << "type list:" << std::endl;
    (std::cout << ... << std::string(std::string(boost::typeindex::type_id_with_cvr<Args>().pretty_name()) + "\n")) << std::endl;
    
    return std::invoke(std::any_cast<std::function<Ret(Args...)>>(m_any),
                       std::forward<Args>(args)...);
  }

  std::any m_any;
};


void print_test(const std::string a)
{
  std::cout << a << std::endl;
}


class func_test
{
public:
  template<typename value>
  void test(value a, value b)
  {
    std::cout << "a+b=" << a + b << std::endl;
  }
};

int main()
{
  std::vector<AnyCallable<void> > func_vecs;
  func_test ft;
  
  const std::function<void(const std::string)> &f1 = std::bind(print_test, std::placeholders::_1);
  const std::function<void()> &f2 = [](){std::cout << "helloworld." << std::endl;};
  const std::function<void(std::string,std::string)> &f3 = std::bind(&func_test::test<std::string>, &ft, std::placeholders::_1, std::placeholders::_2);
  
  func_vecs.emplace_back(f1);
  //  func_vecs.emplace_back(f2);
  //func_vecs.emplace_back(f3);
  
  
  const std::string &a = "hello2";
  std::string b = "test";
  std::string c = "test2";
  func_vecs[0](std::move(a));
  //func_vecs[1]();
  //func_vecs[2](std::string("hello"),std::string("world"));
  //func_vecs[2](std::move(b),std::move(c));
  return 0;
}
