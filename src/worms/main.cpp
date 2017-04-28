#include "application.h"

#include <iostream>

int main()
{
    try
    {
        worms::Application application;
        application.execute();
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
