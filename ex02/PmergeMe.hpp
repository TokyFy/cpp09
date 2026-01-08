/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franaivo <franaivo@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 10:33:46 by franaivo          #+#    #+#             */
/*   Updated: 2026/01/08 10:35:07 by franaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <string>
#include <ctime>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <stdexcept>
#include <utility>

bool                is_valid_number(const std::string& str);
int                 parse_number(const std::string& str);
bool                parse_arguments(int argc, char** argv, std::vector<int>& vec, std::deque<int>& deq);


std::vector<size_t> generate_jacobsthal_sequence(size_t n);
std::vector<size_t> generate_insertion_order(size_t n);


void                ford_johnson_sort_vector(std::vector<int>& vec);
size_t              binary_search_insert_pos_vector(const std::vector<int>& sorted, int value, size_t end);
void                binary_insert_vector(std::vector<int>& sorted, int value, size_t limit);

void                ford_johnson_sort_deque(std::deque<int>& deq);
size_t              binary_search_insert_pos_deque(const std::deque<int>& sorted, int value, size_t end);
void                binary_insert_deque(std::deque<int>& sorted, int value, size_t limit);

void                print_sequence_vector(const std::string& prefix, const std::vector<int>& vec);
void                print_sequence_deque(const std::string& prefix, const std::deque<int>& deq);
void                print_time(const std::string& container_name, size_t size, double microseconds);

#endif
