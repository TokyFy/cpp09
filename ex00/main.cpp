/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franaivo <franaivo@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:39:03 by franaivo          #+#    #+#             */
/*   Updated: 2025/07/08 15:48:31 by franaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <BitcoinExchange.hpp>

#include <fstream>
#include <string>

int main(int argc , char** argv)
{
    if(argc != 2)
    {
        std::cout << "usage : ./btc file" << std::endl;
        return 1;
    }

    std::ifstream data("data.csv");

    if(!data)
    {
        std::cout << "Data not founds" << std::endl;
        return 1;
    }

    BitcoinExchange blockchain;
    std::string line; 

    if(!std::getline(data , line) || line != "date,exchange_rate")
    {
        std::cout << "Error : Invalid database" << std::endl;
        return 1;
    }

    while (std::getline(data, line))
        blockchain.sync(line);        

    if(!blockchain.size())
    {
        std::cout << "Error : Empty database" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);

    if(!input)
    {
        std::cout << "Error : failed to open " << argv[1] << std::endl;
        return 1;
    }

    if(!std::getline(input , line) || line != "date | value")
    {
        std::cout << "Error : Invalid input" << std::endl;
        return 1;
    }

    while (std::getline(input, line))
        blockchain.query(line); 

    return 0;
}

