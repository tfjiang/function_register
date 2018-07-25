#pragma once

#include <unordered_map>
#include <functional>
#include <any>

using any_function = std::function<void(std::any)>;

class function_register
{
public:
	void regist(const std::string &key, const any_function& func);
	void run(const std::string &key, const std::any &);
private:
	std::unordered_map<std::string, any_function> function_hub;
};