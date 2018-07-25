#include "function_register.h"
#include <iostream>
#include <string>

void plus(const std::any&data)
{
	int a, b;
	std::tie(a, b) = std::any_cast<std::pair<int, int>>(data);
	std::cout << a << "+" << b << "=" << a + b << std::endl;
}

void plus_100(const std::any&data)
{
	int a = std::any_cast<int>(data);
	std::cout << a << "+" << 100 << "=" << a + 100 << std::endl;
}

class test_output
{
public:
	void ppp(const std::any &a)
	{
		std::cout << std::any_cast<const std::string>(a) << std::endl;
	}
};


int main()
{
	function_register fr;
	test_output to;
	fr.regist("plus", std::bind(&plus, std::placeholders::_1));
	fr.regist("plus_100", std::bind(&plus_100, std::placeholders::_1));
	fr.regist("plus_triple", [](const std::any& triple)
	{
		int a, b;
		double c;
		std::tie(a, b, c) = std::any_cast<std::tuple<int, int, double>>(triple);
		std::cout << a << "+" << b << "+" << c << "=" << a + b + c << std::endl;
	});
	fr.regist("test_output::ppp", std::bind(&test_output::ppp, &to, std::placeholders::_1));

	fr.run("plus", std::make_pair(1, 2));
	fr.run("plus_100", 1000);
	fr.run("plus_triple", std::make_tuple(1,10,300.1));
	fr.run("test_output::ppp", std::string("Hello World!"));
	return 0;
}