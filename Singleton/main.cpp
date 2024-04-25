#include <iostream>
#include "Singleton.h"

int main(int argc, char const *argv[])
{
    Singleton* single = Singleton::getInstance();
    single->Print();
    return 0;
}
