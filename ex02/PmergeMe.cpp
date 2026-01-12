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

size_t binary_search_insert_pos_vector(const std::vector<int>& sorted, int value, size_t end)
{
    std::vector<int>::const_iterator it = std::upper_bound(sorted.begin(), sorted.begin() + end, value);
    return std::distance(sorted.begin(), it);
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
                pairs[j].first = std::numeric_limits<int>::min();
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
        
        std::vector<int>::iterator it = std::find(sorted.begin(), sorted.end(), paired_main);
        if (it != sorted.end())
        {
            limit = std::distance(sorted.begin(), it) + 1;
        }
        
        binary_insert_vector(sorted, value, limit);
    }
    
    if (has_straggler)
    {
        binary_insert_vector(sorted, straggler, sorted.size());
    }
    
    vec = sorted;
}

void print_sequence_vector(const std::string& prefix, const std::vector<int>& vec)
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

size_t binary_search_insert_pos_deque(const std::deque<int>& sorted, int value, size_t end)
{
    std::deque<int>::const_iterator it = std::upper_bound(sorted.begin(), sorted.begin() + end, value);
    return std::distance(sorted.begin(), it);
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
                pairs[j].first = std::numeric_limits<int>::min();
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
        
        std::deque<int>::iterator it = std::find(sorted.begin(), sorted.end(), paired_main);
        if (it != sorted.end())
        {
            limit = std::distance(sorted.begin(), it) + 1;
        }
        
        binary_insert_deque(sorted, value, limit);
    }
    
    if (has_straggler)
    {
        binary_insert_deque(sorted, straggler, sorted.size());
    }
    
    deq = sorted;
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
