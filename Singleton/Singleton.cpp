#include "Singleton.h"
#include <iostream>



Singleton::Singleton(const std::string& value):str(value)
{

    std::cout << "创建单例对象" << std::endl;
}


Singleton::~Singleton()
{
    std::cout << "销毁单例对象" << std::endl;
}

Singleton* Singleton::getInstance()
{
    static Singleton singleton("start");

    return &singleton;
}


void Singleton::Print()
{
    std::cout << this->str << std::endl;
}