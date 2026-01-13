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
        std::cerr 
            << std::left << std::setw(25) << transaction 
            << RED <<  " Error : " << err.what() << RESET << std::endl;
    }
}

void BitcoinExchange::query(std::string tranfers)
{
    try
    {
        std::string transaction = tranfers;

        size_t pos = transaction.find(" | " , 0);

        if(pos == std::string::npos)
            throw std::runtime_error("Invalid format (yyyy-mm-dd | 0.0)");

        transaction.replace(pos , 3 , ",");

        BLOCK block = BitcoinExchange::serialise(transaction);

        double          value = block.second;

        if(value < 0 || value > 1000)
            throw std::runtime_error("value should be in [0 - 1000] range");

        std::list<BLOCK>::iterator match = std::lower_bound(nodes.begin() , nodes.end() , block , comp<BLOCK>);
        
        if(match == nodes.begin())
            throw std::runtime_error("match not found");
        else
            match--;
        
        std::cout << tranfers.substr(0 , 10) << " => " << value << " = " << value * match->second << std::endl;
    } 
    catch (std::exception& err)
    {
        std::cerr 
            << std::left << std::setw(25) << tranfers 
            << RED <<  " Error : " << err.what() << RESET << std::endl;
    }
}

size_t BitcoinExchange::size() const
{
    return nodes.size();
}
