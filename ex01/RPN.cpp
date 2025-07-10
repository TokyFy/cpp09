#include <RPN.hpp>
#include <iostream>
#include <cstdlib>
#include <utility>
#include <iomanip>
#include <queue>
#include <sstream>

double RPN::eval(const std::string& expr)
{
    (void)(expr);

    std::queue<TOKEN> tokens;
    std::queue<TOKEN> operand;

    std::istringstream ss_tokens(expr);
    std::string token;

    while(std::getline(ss_tokens , token , ' '))
    {
        if(!token.empty())
            tokens.push(RPN::tokenizer(token));
    }
    
    while(tokens.size() != 1)
    {
            
    }

    return 0;
}

TOKEN RPN::tokenizer(const std::string& expr)
{
    if(expr.size() == 1)
    {
        switch(expr[0])
        {
            case '+' :
                return std::make_pair<TOKEN_TYPE , double>(ADDEND       , 0x0); 
            case '-' :
                return std::make_pair<TOKEN_TYPE , double>(MINUEND      , 0x0); 
            case '*' :
                return std::make_pair<TOKEN_TYPE , double>(MULTIPLICAND , 0x0); 
            case '/' :
                return std::make_pair<TOKEN_TYPE , double>(DIVIDEND     , 0x0); 
        }
    }

    char *end;
    double value = std::strtod(expr.c_str() , &end); 

    if(*end)
        throw std::runtime_error("( " + expr + " ) invalid operand");

    return std::make_pair<TOKEN_TYPE , double>(NUMERAL , static_cast<double>(value));
}

std::ostream& operator<< (std::ostream& stream, const TOKEN token)
{
    const std::string TYPE[] = {"NUMERAL" , "ADDEND" , "MINUEND" , "DIVIDEND" , "MULTIPLICAND"};
    
    std::cout << std::setw(13) << std::left <<TYPE[token.first] << token.second;

    return stream; 
}
