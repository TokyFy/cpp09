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

int main()
{
    std::ifstream data("data.csv");

    if(!data)
    {
        std::cout << "Data not founds" << std::endl;
        return 1;
    }

    BitcoinExchange blockchain;
    std::string line; 

    ;
    if(!std::getline(data , line) || line != "date,exchange_rate")
    {
        std::cout << "Invalid file" << std::endl;
        return 1;
    }

    while (std::getline(data, line))
        blockchain.sync(line);        

    return 0;
}

