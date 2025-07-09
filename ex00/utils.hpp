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
#include <cmath>

#define RESET       "\033[0m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"


long int        strtol_except(std::string str);
double          strtod_except(std::string str);
void            validate_date(unsigned int year, unsigned int month, unsigned int day);
unsigned int    parse_date(std::string str);
