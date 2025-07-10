#include <RPN.hpp>
#include <iostream>

int main(int argc , char **argv)
{

    (void)(argc);
    (void)(argv);

    if(argc != 2)
    {
        std::cout << "usage : ./RPN expr..." << std::endl;
        return 1;
    }

    try
    {
        std::cout << RPN::eval(argv[1]) << std::endl;
    }
    catch(std::exception &e)
    {
        std::cout << "Error : " << e.what() << std::endl; 
    }

    return 0;
}
