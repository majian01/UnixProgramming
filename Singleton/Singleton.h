#pragma once

#include <string>

class Singleton
{
private:
    Singleton(const std::string& value);
    ~Singleton();
    Singleton(const Singleton&) = delete;
    Singleton& operator= (const Singleton&) = delete;

private:

    std::string str;

public:
    static Singleton* getInstance();
    void Print();
};
