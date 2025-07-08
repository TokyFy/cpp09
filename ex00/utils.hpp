/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franaivo <franaivo@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 15:40:26 by franaivo          #+#    #+#             */
/*   Updated: 2025/07/08 15:40:28 by franaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <cstdlib>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <iomanip>

long int        strtol_except(std::string str);
double          strtod_except(std::string str);
void            validate_date(unsigned int year, unsigned int month, unsigned int day);
unsigned int    parse_date(std::string str);
