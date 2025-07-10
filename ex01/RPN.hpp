#pragma once

#include <string>

enum TOKEN_TYPE {NUMERAL , ADDEND , MINUEND , DIVIDEND , MULTIPLICAND , ERROR};

typedef std::pair<TOKEN_TYPE , double> TOKEN;

class RPN
{
    private :
        RPN();
        ~RPN();
        RPN(const RPN&);
        RPN& operator=(const RPN&);

    public :
        static double   eval(const std::string&);
        static TOKEN    tokenizer(const std::string&);
};

std::ostream& operator<< (std::ostream& stream, const TOKEN token);
