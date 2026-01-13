/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franaivo <franaivo@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 19:13:54 by franaivo          #+#    #+#             */
/*   Updated: 2026/01/12 19:13:55 by franaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

double get_time(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)tv.tv_sec * 1000.0 + (double)tv.tv_usec / 1000.0;
}

void print_time(const std::string& container_name, size_t size, double microseconds)
{
    std::cout << "Time to process a range of " << size 
              << " elements with std::" << container_name 
              << " : " << std::fixed << std::setprecision(5) 
              << microseconds << " ms" << std::endl;
}

bool is_valid_number(const std::string& str)
{
    if (str.empty())
        return false;
    
    size_t start = 0;
    if (str[0] == '+')
        start = 1;
    
    if (start >= str.size())
        return false;
    
    for (size_t i = start; i < str.size(); ++i)
    {
        if (!std::isdigit(str[i]))
            return false;
    }
    return true;
}                                                                                                                                                                                                               

int parse_number(const std::string& str)
{
    long num = 0;
    size_t start = 0;
    
    if (str[0] == '+')
        start = 1;
    
    for (size_t i = start; i < str.size(); ++i)
    {
        num = num * 10 + (str[i] - '0');
        if (num > std::numeric_limits<int>::max())
            return -1;
    }
    return static_cast<int>(num);
}

bool has_duplicate(const std::vector<int>& vec, int value)
{
    return std::find(vec.begin(), vec.end(), value) != vec.end();
}

bool has_duplicate(const std::deque<int>& deq, int value)
{
    return std::find(deq.begin(), deq.end(), value) != deq.end();
}

bool parse_arguments(int argc, char** argv, std::vector<int>& vec)
{
    for (int i = 1; i < argc; ++i)
    {
        std::string arg(argv[i]);
        
        if (!is_valid_number(arg))
            return false;
        
        int num = parse_number(arg);
        if (num < 0)
            return false;
        
        if (has_duplicate(vec, num))
            return false;
        
        vec.push_back(num);
    }
    return true;
}

bool parse_arguments(int argc, char** argv, std::deque<int>& deq)
{
    for (int i = 1; i < argc; ++i)
    {
        std::string arg(argv[i]);
        
        if (!is_valid_number(arg))
            return false;
        
        int num = parse_number(arg);
        if (num < 0)
            return false;
        
        if (has_duplicate(deq, num))
            return false;
        
        deq.push_back(num);
    }
    return true;
}


std::vector<size_t> generate_insertion_order_vector(size_t n)
{
    static const size_t jacobsthal[] = {
        1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461,
        10923, 21845, 43691, 87381, 174763, 349525, 699051, 1398101,
        2796203, 5592405, 11184811, 22369621, 44739243, 89478485,
        178956971, 357913941, 715827883, 1431655765, 2863311531
    };
    
    std::vector<size_t> order;
    if (n < 2)
        return order;

    size_t prev = 1;
    for (size_t k = 0; prev < n; ++k)
    {
        size_t curr = jacobsthal[k];
        size_t bound = curr;
        if (curr > n)
            bound = n;
        
        for (size_t i = bound; i > prev; --i)
            order.push_back(i);
        
        prev = curr;
    }
    
    return order;
}

std::deque<size_t> generate_insertion_order_deque(size_t n)
{
    static const size_t jacobsthal[] = {
        1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461,
        10923, 21845, 43691, 87381, 174763, 349525, 699051, 1398101,
        2796203, 5592405, 11184811, 22369621, 44739243, 89478485,
        178956971, 357913941, 715827883, 1431655765, 2863311531
    };
    
    std::deque<size_t> order;
    if (n < 2)
        return order;

    size_t prev = 1;
    for (size_t k = 0; prev < n; ++k)
    {
        size_t curr = jacobsthal[k];
        size_t bound = curr;
        if (curr > n)
            bound = n;
        
        for (size_t i = bound; i > prev; --i)
            order.push_back(i);
        
        prev = curr;
    }
    
    return order;
}

void print_sequence(const std::string& prefix, const std::deque<int>& deq)
{
    std::cout << prefix;
    for (size_t i = 0; i < deq.size(); ++i)
    {
        std::cout << deq[i];
        if (i + 1 < deq.size())
            std::cout << " ";
    }
    std::cout << std::endl;
}

void print_sequence(const std::string& prefix, const std::vector<int>& vec)
{
    std::cout << prefix;
    
    for (size_t i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i];
        if (i + 1 < vec.size())
            std::cout << " ";
    }
    
    std::cout << std::endl;
}
