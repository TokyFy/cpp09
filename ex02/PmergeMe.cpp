/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franaivo <franaivo@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 10:25:28 by franaivo          #+#    #+#             */
/*   Updated: 2026/01/08 10:28:53 by franaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <climits>
#include <algorithm>

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
        if (str[i] < '0' || str[i] > '9')
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
        if (num > INT_MAX)
            return -1;
    }
    return static_cast<int>(num);
}

bool has_duplicate(const std::vector<int>& vec, int value)
{
    for (size_t i = 0; i < vec.size(); ++i)
    {
        if (vec[i] == value)
            return true;
    }
    return false;
}

bool parse_arguments(int argc, char** argv, std::vector<int>& vec, std::deque<int>& deq)
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
        deq.push_back(num);
    }
    return true;
}


std::vector<size_t> generate_jacobsthal_sequence(size_t n)
{
    static const size_t jacobsthal_numbers[] = {
        0, 1, 1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461,
        10923, 21845, 43691, 87381, 174763, 349525, 699051, 1398101,
        2796203, 5592405, 11184811, 22369621, 44739243, 89478485,
        178956971, 357913941, 715827883, 1431655765, 2863311531
    };
    static const size_t jacobsthal_size = sizeof(jacobsthal_numbers) / sizeof(jacobsthal_numbers[0]);
    
    std::vector<size_t> jacobsthal;
    
    if (n == 0)
        return jacobsthal;
    
    for (size_t i = 0; i < jacobsthal_size && jacobsthal_numbers[i] <= n; ++i)
    {
        jacobsthal.push_back(jacobsthal_numbers[i]);
    }
    
    for (size_t i = 0; i < jacobsthal_size; ++i)
    {
        if (jacobsthal_numbers[i] > n)
        {
            jacobsthal.push_back(jacobsthal_numbers[i]);
            break;
        }
    }
    
    return jacobsthal;
}

std::vector<size_t> generate_insertion_order(size_t n)
{
    std::vector<size_t> order;
    
    if (n == 0)
        return order;
    
    std::vector<size_t> jacobsthal = generate_jacobsthal_sequence(n);
    std::vector<bool> inserted(n + 1, false);
    
    inserted[1] = true;
    
    for (size_t k = 2; k < jacobsthal.size(); ++k)
    {
        size_t jk = jacobsthal[k];
        size_t jk_prev = jacobsthal[k - 1];
        
        for (size_t idx = jk; idx > jk_prev; --idx)
        {
            if (idx <= n && !inserted[idx])
            {
                order.push_back(idx);
                inserted[idx] = true;
            }
        }
    }
    
    for (size_t i = 2; i <= n; ++i)
    {
        if (!inserted[i])
            order.push_back(i);
    }
    
    return order;
}

size_t binary_search_insert_pos_vector(const std::vector<int>& sorted, int value, size_t end)
{
    size_t left = 0;
    size_t right = end;
    
    while (left < right)
    {
        size_t mid = left + (right - left) / 2;
        if (sorted[mid] <= value)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

void binary_insert_vector(std::vector<int>& sorted, int value, size_t limit)
{
    size_t pos = binary_search_insert_pos_vector(sorted, value, limit);
    sorted.insert(sorted.begin() + static_cast<std::vector<int>::difference_type>(pos), value);
}


void ford_johnson_sort_vector(std::vector<int>& vec)
{
    size_t n = vec.size();
    
    if (n <= 1)
        return;
    
    if (n == 2)
    {
        if (vec[0] > vec[1])
            std::swap(vec[0], vec[1]);
        return;
    }
    
    std::vector<std::pair<int, int> > pairs;
    bool has_straggler = (n % 2 == 1);
    int straggler = 0;
    
    if (has_straggler)
        straggler = vec[n - 1];
    
    size_t pair_count = n / 2;
    for (size_t i = 0; i < pair_count; ++i)
    {
        int a = vec[2 * i];
        int b = vec[2 * i + 1];
        
        if (a < b)
            pairs.push_back(std::make_pair(b, a));
        else
            pairs.push_back(std::make_pair(a, b));
    }
    
    std::vector<int> main_chain;
    for (size_t i = 0; i < pairs.size(); ++i)
        main_chain.push_back(pairs[i].first);
    
    ford_johnson_sort_vector(main_chain);
    
    std::vector<int> pend;
    std::vector<size_t> pend_positions;
    
    for (size_t i = 0; i < main_chain.size(); ++i)
    {
        for (size_t j = 0; j < pairs.size(); ++j)
        {
            if (pairs[j].first == main_chain[i])
            {
                pend.push_back(pairs[j].second);
                pend_positions.push_back(i);
                pairs[j].first = -1;
                break;
            }
        }
    }
    
    std::vector<int> sorted;
    if (!pend.empty())
    {
        sorted.push_back(pend[0]);
    }
    for (size_t i = 0; i < main_chain.size(); ++i)
        sorted.push_back(main_chain[i]);
    
    std::vector<size_t> insertion_order = generate_insertion_order(pend.size());
    
    for (size_t i = 0; i < insertion_order.size(); ++i)
    {
        size_t pend_idx = insertion_order[i] - 1;        
        if (pend_idx >= pend.size())
            continue;
        
        int value = pend[pend_idx];
        
        size_t limit = sorted.size();
        int paired_main = main_chain[pend_positions[pend_idx]];
        
        for (size_t j = 0; j < sorted.size(); ++j)
        {
            if (sorted[j] == paired_main)
            {
                limit = j + 1;
                break;
            }
        }
        
        binary_insert_vector(sorted, value, limit);
    }
    
    if (has_straggler)
    {
        binary_insert_vector(sorted, straggler, sorted.size());
    }
    
    vec = sorted;
}

size_t binary_search_insert_pos_deque(const std::deque<int>& sorted, int value, size_t end)
{
    size_t left = 0;
    size_t right = end;
    
    while (left < right)
    {
        size_t mid = left + (right - left) / 2;
        if (sorted[mid] <= value)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

void binary_insert_deque(std::deque<int>& sorted, int value, size_t limit)
{
    size_t pos = binary_search_insert_pos_deque(sorted, value, limit);
    sorted.insert(sorted.begin() + static_cast<std::deque<int>::difference_type>(pos), value);
}

void ford_johnson_sort_deque(std::deque<int>& deq)
{
    size_t n = deq.size();
    
    if (n <= 1)
        return;
    
    if (n == 2)
    {
        if (deq[0] > deq[1])
            std::swap(deq[0], deq[1]);
        return;
    }
    
    std::deque<std::pair<int, int> > pairs;
    bool has_straggler = (n % 2 == 1);
    int straggler = 0;
    
    if (has_straggler)
        straggler = deq[n - 1];
    
    size_t pair_count = n / 2;
    for (size_t i = 0; i < pair_count; ++i)
    {
        int a = deq[2 * i];
        int b = deq[2 * i + 1];
        
        if (a < b)
            pairs.push_back(std::make_pair(b, a));
        else
            pairs.push_back(std::make_pair(a, b));
    }
    
    std::deque<int> main_chain;
    for (size_t i = 0; i < pairs.size(); ++i)
        main_chain.push_back(pairs[i].first);
    
    ford_johnson_sort_deque(main_chain);
    
    std::deque<int> pend;
    std::deque<size_t> pend_positions;
    
    for (size_t i = 0; i < main_chain.size(); ++i)
    {
        for (size_t j = 0; j < pairs.size(); ++j)
        {
            if (pairs[j].first == main_chain[i])
            {
                pend.push_back(pairs[j].second);
                pend_positions.push_back(i);
                pairs[j].first = -1;
                break;
            }
        }
    }
    
    std::deque<int> sorted;
    if (!pend.empty())
    {
        sorted.push_back(pend[0]);
    }
    for (size_t i = 0; i < main_chain.size(); ++i)
        sorted.push_back(main_chain[i]);
    
    std::vector<size_t> insertion_order = generate_insertion_order(pend.size());
    
    for (size_t i = 0; i < insertion_order.size(); ++i)
    {
        size_t pend_idx = insertion_order[i] - 1;
        
        if (pend_idx >= pend.size())
            continue;
        
        int value = pend[pend_idx];
        
        size_t limit = sorted.size();
        int paired_main = main_chain[pend_positions[pend_idx]];
        
        for (size_t j = 0; j < sorted.size(); ++j)
        {
            if (sorted[j] == paired_main)
            {
                limit = j + 1;
                break;
            }
        }
        
        binary_insert_deque(sorted, value, limit);
    }
    
    if (has_straggler)
    {
        binary_insert_deque(sorted, straggler, sorted.size());
    }
    
    deq = sorted;
}

void print_sequence_vector(const std::string& prefix, const std::vector<int>& vec)
{
    std::cout << prefix;
    for (size_t i = 0; i < vec.size(); ++i)
    {
        std::cout << vec[i];
        if (i + 1 < vec.size())
            std::cout << " ";

        if(i >= 42)
        {
            std::cout << "..."; break;
        }
    }
    std::cout << std::endl;
}

void print_sequence_deque(const std::string& prefix, const std::deque<int>& deq)
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

void print_time(const std::string& container_name, size_t size, double microseconds)
{
    std::cout << "Time to process a range of " << size 
              << " elements with std::" << container_name 
              << " : " << std::fixed << microseconds << " us" << std::endl;
}
