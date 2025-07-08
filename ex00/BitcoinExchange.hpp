/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franaivo <franaivo@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 09:16:47 by franaivo          #+#    #+#             */
/*   Updated: 2025/07/08 10:37:24 by franaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <utils.hpp>
#include <vector>


typedef  std::pair< unsigned int , double > BLOCK; 

class BitcoinExchange
{
    private:
        std::vector<BLOCK> nodes;

        BitcoinExchange(const BitcoinExchange&);
        BitcoinExchange& operator=(const BitcoinExchange&);

    public :
        BitcoinExchange();
        ~BitcoinExchange();
        BLOCK           query(unsigned int);
        void            sync (std::string);
        static BLOCK    serialise(std::string);
};
