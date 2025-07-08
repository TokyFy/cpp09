#include <BitcoinExchange.hpp>
#include <sstream>
#include <cstdlib>
#include <algorithm>

BitcoinExchange::BitcoinExchange()
{
    return;
}

BitcoinExchange::~BitcoinExchange()
{
    return;
}

long int strtol_10_except(std::string str)
{
    char *end;

    std::string set = " \v\t+-";
    if(std::find_first_of(str.begin() , str.end() , set.begin() , set.end()) != str.end())
        throw std::runtime_error("[ "  + str + " ] Invalid token");

    long int n = std::strtol(str.c_str() , &end , 10);

    if(*end)
        throw std::runtime_error("[ "  + str + " ] Invalid token");

    return n;
}

double strtod_except(std::string str)
{
    return 0;
}

unsigned int parse_date(std::string str)
{
    std::istringstream ss_date(str);

    std::string yyyy;
    std::string mm;
    std::string dd;

    std::getline(ss_date , yyyy , '-'); 
    std::getline(ss_date , mm   , '-'); 
    std::getline(ss_date , dd   , '-'); 

    if(yyyy.empty() || mm.empty() || dd.empty() || !ss_date.eof())
        throw std::runtime_error("invalid date (yyyy-mm-dd)");

    unsigned int year   = strtol_10_except(yyyy);
    unsigned int month  = strtol_10_except(mm);
    unsigned int day    = strtol_10_except(dd);

    return year + month + day;
}

void BitcoinExchange::sync (std::string transaction)
{
    std::istringstream ss_transaction(transaction);

    std::string date;
    std::string value;

    std::getline(ss_transaction , date , ',');
    std::getline(ss_transaction , value , ',');

    if(date.empty() || value.empty())
        throw std::runtime_error("missing field"); 

    if(!ss_transaction.eof())
        throw std::runtime_error("unkown field");
    
    unsigned int date_int = parse_date(date);

    nodes.push_back(std::make_pair(date_int,0)); 
    return;
}
