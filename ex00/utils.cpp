/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franaivo <franaivo@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:39:10 by franaivo          #+#    #+#             */
/*   Updated: 2025/07/08 15:39:11 by franaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.hpp>

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

double strtod_except(std::string str)
{
    char *end;

    std::string set = " \v\t+-";
    if(std::find_first_of(str.begin() , str.end() , set.begin() , set.end()) != str.end())
        throw std::runtime_error("["  + str + "] Invalid token");

    double n = std::strtod(str.c_str() , &end);

    if(*end || std::isnan(n))
        throw std::runtime_error("["  + str + "] Invalid token");

    return n;
}

void validate_date(unsigned int year, unsigned int month, unsigned int day) {
    if (year == 0)
        throw std::runtime_error("Invalid date: year cannot be zero.");
    if (month < 1 || month > 12)
        throw std::runtime_error("Invalid date: month must be between 1 and 12.");
    if (day == 0)
        throw std::runtime_error("Invalid date: day cannot be zero.");

    static const unsigned int days_in_month[] = { 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31 };

    bool is_leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));

    unsigned int max_day = days_in_month[month - 1];
    if (is_leap && month == 2)
        max_day = 29;

    if (day > max_day)
        throw std::runtime_error("Invalid date: day exceeds days in the month.");
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

    if(yyyy.size() != 4 || mm.size() != 2 || dd.size() != 2 || !ss_date.eof())
        throw std::runtime_error("invalid date (yyyy-mm-dd)");

    unsigned int year   = strtol_except(yyyy);
    unsigned int month  = strtol_except(mm);
    unsigned int day    = strtol_except(dd);

    validate_date(year , month , day);

    return year * 10000 + month * 100 + day;
}
