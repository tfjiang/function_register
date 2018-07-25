#include "function_register.h"

void function_register::regist(const std::string& key, const any_function& func)
{
	function_hub[key] = func;
}

void function_register::run(const std::string & key, const std::any & param)
{
	auto it = function_hub.find(key);
	if(it == function_hub.end())
	{
		throw std::invalid_argument("Can not find " + key + " in function_register.");
	}
	it->second(param);
}