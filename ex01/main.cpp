#include <RPN.hpp>

int main(int argc , char **argv)
{
    if(argc != 2)
    {
        std::cout << "usage : ./RPN expr..." << std::endl;
        return EXIT_FAILURE;
    }

    try
    {
        std::cout << RPN::eval(argv[1]) << std::endl;
    }
    catch(std::exception &e)
    {
        std::cout << "Error : " << e.what() << std::endl; 
    }

    return EXIT_SUCCESS;
}
