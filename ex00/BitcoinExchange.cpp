/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franaivo <franaivo@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:38:59 by franaivo          #+#    #+#             */
/*   Updated: 2025/07/08 15:49:13 by franaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <BitcoinExchange.hpp>

#define RESET       "\033[0m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"

BitcoinExchange::BitcoinExchange()
{
    return;
}

BitcoinExchange::~BitcoinExchange()
{
    return;
}


BLOCK BitcoinExchange::serialise(std::string transaction)
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
    
    unsigned int    date_num    = parse_date(date);
    double          value_num   = strtod_except(value);

    return std::make_pair(date_num,value_num); 
}

void BitcoinExchange::sync (std::string transaction)
{
    try
    {
        BLOCK block = BitcoinExchange::serialise(transaction);
        BLOCK last; 
        
        if(!nodes.empty())
            last = nodes.back();

        if(!nodes.empty() && (last.first >= block.first))
        {
            throw std::runtime_error("outdated blocks");
        }

        nodes.push_back(block);
    } 

    catch (std::exception& err)
    {
        std::cout 
            << std::left << std::setw(25) << transaction 
            << RED <<  " Error : " << err.what() << RESET << std::endl;
    }
}
