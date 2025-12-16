#include <stdexcept>
#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>


long int strtol_except(std::string str)
{
    char *end;

    std::string set = " \v\t+-";
    if(std::find_first_of(str.begin() , str.end() , set.begin() , set.end()) != str.end())
        throw std::runtime_error("["  + str + "] Invalid token");

    long int n = std::strtol(str.c_str() , &end , 10);

    if(*end)
        throw std::runtime_error("["  + str + "] Invalid token");

    return n;
}

void print_vector(std::vector<long int> numbers)
{
    unsigned int i = 0;

    while(i < numbers.size())
    {
        std::cout << numbers[i] << " ,";
        i++;
    }

    std::cout << std::endl;
}

void binary_insert(std::vector<long int> &number, long int n) {
    int left = 0, right = static_cast<int>(number.size());

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (number[mid] < n)
            left = mid + 1;
        else
            right = mid;
    }

    number.insert(number.begin() + left, n);
}

void insert_pending(std::vector<long int> &main_chain , std::vector<long int> &pending )
{
    static const int JACOBSTHAL_NUMBERS[] = { 
        1,     3,      5,     11,    21,    43,    85,     171,    341,   683,   
        1365,  2731,   5461,  10923, 21845, 43691, 87381, 174763, 349525, 699051 }; 

    unsigned int i = 0;

    while(static_cast<unsigned int>(JACOBSTHAL_NUMBERS[i] - 1) < pending.size())
    {
        binary_insert(main_chain , pending[JACOBSTHAL_NUMBERS[i] - 1 ]);
        pending[JACOBSTHAL_NUMBERS[i] - 1] *= -1;
        i++;
    }

    i = 0;

    while(i < pending.size())
    {
        if(pending[i] < 0)
        {
            i++;
            continue;
        }

        binary_insert(main_chain , pending[i]);
        i++;
    }

    pending.clear();
}

void pmergeme(std::vector<long int> &numbers)
{
    if(numbers.size() == 1)
        return;

    std::vector<long int> main_chain;
    std::vector<long int> pending;
    
    while(numbers.size() >  1)
    {
        long int x = numbers[0];
        long int y = numbers[1];

        main_chain.push_back(std::max(x ,y));
        pending.push_back(std::min(x,y));

        numbers.erase(numbers.begin() , numbers.begin() + 2);
    }

    if(numbers.size() == 1)
    {
        pending.push_back(numbers[0]);
        numbers.erase(numbers.begin());
    }

    pmergeme(main_chain);
    insert_pending(main_chain , pending);

    numbers = main_chain;
}

int main(int argc , char** argv)
{
    std::vector<long int> numbers;

    if(argc <= 2)
        return 1;

    unsigned int i = 1;

    try
    {
        while(i < (unsigned int)argc)
        {
            numbers.push_back(strtol_except(argv[i]));
            i++;
        }
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    pmergeme(numbers);
    print_vector(numbers);

    return 0;
}