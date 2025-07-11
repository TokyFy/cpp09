#include <RPN.hpp>
#include <iostream>
#include <cstdlib>
#include <utility>
#include <iomanip>
#include <sstream>
#include <deque>

TOKEN op(TOKEN x , const TOKEN y , const TOKEN_TYPE sign)
{
    if(x.first != NUMERAL || y.first != NUMERAL)
        throw std::runtime_error("Invalied operand");

    switch(sign)
    {
        case ADDEND :
            return std::make_pair<TOKEN_TYPE , double>(NUMERAL , x.second + y.second);
        case MINUEND :
            return std::make_pair<TOKEN_TYPE , double>(NUMERAL , x.second - y.second);
        case DIVIDEND :
            return std::make_pair<TOKEN_TYPE , double>(NUMERAL , x.second / y.second);
        case MULTIPLICAND :
            return std::make_pair<TOKEN_TYPE , double>(NUMERAL , x.second * y.second);
        default :
            throw std::runtime_error("Invalid operator");
    }
}

double RPN::eval(const std::string& expr)
{
    (void)(expr);

    std::deque<TOKEN> tokens;

    std::istringstream ss_tokens(expr);
    std::string token;

    while(std::getline(ss_tokens , token , ' '))
    {
        if(!token.empty())
            tokens.push_back(RPN::tokenizer(token));
    }

    std::deque<TOKEN> operand;

    while(!tokens.empty())
    {
        TOKEN t =   tokens.front(); tokens.pop_front();

        if(t.first != NUMERAL)
        {
            if(operand.size() < 2)
                throw std::runtime_error("not enough operand");

            TOKEN x = operand.front() ; operand.pop_front() ;
            TOKEN y = operand.front() ; operand.pop_front() ;
            operand.push_front(op(y,x,t.first));
        }
        else
            operand.push_front(t);
    }

    if(operand.size() != 1)
        throw std::runtime_error("malformed expr");
    
    return operand.front().second;
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
