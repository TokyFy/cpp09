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
#include <list>

typedef  std::pair< unsigned int , double > BLOCK; 

class BitcoinExchange
{
    private:
        std::list<BLOCK> nodes;

        BitcoinExchange(const BitcoinExchange&);
        BitcoinExchange& operator=(const BitcoinExchange&);

    public :
        BitcoinExchange();
        ~BitcoinExchange();
        void            query(std::string);
        void            sync (std::string);
        static BLOCK    serialise(std::string);
        size_t          size() const;
};

template <typename T>
bool comp(const T &a ,const T &b)
{
    return a.first < b.first;
}
