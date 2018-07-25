cmake_minimum_required(VERSION 3.9)
project(function_register)

file(GLOB header *.h)
file(GLOB source *.cpp)

add_executable(${PROJECT_NAME} ${header} ${source})
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)