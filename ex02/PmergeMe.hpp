/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franaivo <franaivo@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 19:13:40 by franaivo          #+#    #+#             */
/*   Updated: 2026/01/12 19:13:42 by franaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

#include <vector>
#include <deque>
#include <map>
#include <string>
#include <ctime>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <stdexcept>
#include <utility>
#include <algorithm>
#include <iterator>
#include <limits>
#include <iomanip>

bool                is_valid_number(const std::string& str);
int                 parse_number(const std::string& str);
bool                parse_arguments_vector(int argc, char** argv, std::vector<int>& vec);
bool                parse_arguments_deque(int argc, char** argv, std::deque<int>& deq);

std::map<size_t, size_t> generate_insertion_order(size_t n);

void                ford_johnson_sort_vector(std::vector<int>& vec);
void                binary_insert_vector(std::vector<int>& sorted, int value, size_t limit);

void                ford_johnson_sort_deque(std::deque<int>& deq);
void                binary_insert_deque(std::deque<int>& sorted, int value, size_t limit);

void                print_sequence_vector(const std::string& prefix, const std::vector<int>& vec);
void                print_sequence_deque(const std::string& prefix, const std::deque<int>& deq);
void                print_time(const std::string& container_name, size_t size, double microseconds);
