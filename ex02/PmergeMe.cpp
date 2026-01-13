/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franaivo <franaivo@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 10:25:28 by franaivo          #+#    #+#             */
/*   Updated: 2026/01/12 22:24:04 by franaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// VECTOR IMPLEMENTATION

void binary_insert(std::vector<int>& sorted, int value, size_t limit)
{
    std::vector<int>::iterator it = std::upper_bound(sorted.begin(), sorted.begin() + limit, value);
    sorted.insert(it, value);
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
    for (size_t i = 0; i < pair_count * 2; i += 2)
    {
        int a = vec[i];
        int b = vec[i + 1];
        
        if (a < b)
            pairs.push_back(std::make_pair(b, a));
        else
            pairs.push_back(std::make_pair(a, b));
    }
    
    // Extract larger values from pairs for recursive sorting
    std::vector<int> main_chain;
    for (size_t i = 0; i < pairs.size(); ++i)
        main_chain.push_back(pairs[i].first);
    
    // Sort pairs based on the order of main_chain after recursion
    ford_johnson_sort_vector(main_chain);
    
    // Generate sorted_pend to match the sorted main_chain order
    std::vector<int> sorted_pend(pairs.size());
    for (size_t i = 0; i < main_chain.size(); ++i)
    {
        for (size_t j = 0; j < pairs.size(); ++j)
        {
            if (pairs[j].first == main_chain[i])
            {
                sorted_pend[i] = pairs[j].second;
                pairs[j].first = -1;
                break;
            }
        }
    }
    
    // Initialize sorted with the first pend element (smallest in entire sequence)
    std::vector<int> sorted;
    if (pair_count > 0)
        sorted.push_back(sorted_pend[0]);
    
    // Add all sorted main_chain elements
    for (size_t i = 0; i < main_chain.size(); ++i)
        sorted.push_back(main_chain[i]);
    
    // Insert remaining pend elements using Jacobsthal order
    std::vector<size_t> insertion_order = generate_insertion_order_vector(pair_count);
    
    for (size_t k = 0; k < insertion_order.size(); ++k)
    {
        size_t pend_idx = insertion_order[k] - 1;
        if (pend_idx >= pair_count)
            continue;
        
        int value_to_insert = sorted_pend[pend_idx];
        int paired_main = main_chain[pend_idx];
        
        // Find current position of paired main_chain element using binary search
        std::vector<int>::iterator it = std::lower_bound(sorted.begin(), sorted.end(), paired_main);
        size_t limit = static_cast<size_t>(std::distance(sorted.begin(), it)) + 1;
        binary_insert(sorted, value_to_insert, limit);
    }
    
    if (has_straggler)
    {
        binary_insert(sorted, straggler, sorted.size());
    }
    
    vec = sorted;
}


// DEQUE IMPLEMENTATION

void binary_insert(std::deque<int>& sorted, int value, size_t limit)
{
    std::deque<int>::iterator it = std::upper_bound(sorted.begin(), sorted.begin() + limit, value);
    sorted.insert(it, value);
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
    for (size_t i = 0; i < pair_count * 2; i += 2)
    {
        int a = deq[i];
        int b = deq[i + 1];
        
        if (a < b)
            pairs.push_back(std::make_pair(b, a));
        else
            pairs.push_back(std::make_pair(a, b));
    }
    
    // Extract larger values from pairs for recursive sorting
    std::deque<int> main_chain;
    for (size_t i = 0; i < pairs.size(); ++i)
        main_chain.push_back(pairs[i].first);
    
    // Sort pairs based on the order of main_chain after recursion
    ford_johnson_sort_deque(main_chain);
    
    // Generate sorted_pend to match the sorted main_chain order
    std::deque<int> sorted_pend(pairs.size());
    for (size_t i = 0; i < main_chain.size(); ++i)
    {
        for (size_t j = 0; j < pairs.size(); ++j)
        {
            if (pairs[j].first == main_chain[i])
            {
                sorted_pend[i] = pairs[j].second;
                pairs[j].first = -1;  // Mark as used
                break;
            }
        }
    }
    
    // Initialize sorted with the first pend element (smallest in entire sequence)
    std::deque<int> sorted;
    if (pair_count > 0)
        sorted.push_back(sorted_pend[0]);
    
    // Add all sorted main_chain elements
    for (size_t i = 0; i < main_chain.size(); ++i)
        sorted.push_back(main_chain[i]);
    
    // Insert remaining pend elements using Jacobsthal order (minimizes comparisons)
    std::deque<size_t> insertion_order = generate_insertion_order_deque(pair_count);
    
    for (size_t k = 0; k < insertion_order.size(); ++k)
    {
        size_t pend_idx = insertion_order[k] - 1;
        if (pend_idx >= pair_count)
            continue;
        
        int value_to_insert = sorted_pend[pend_idx];
        int paired_main = main_chain[pend_idx];
        
        // Find current position of paired main_chain element using binary search
        std::deque<int>::iterator it = std::lower_bound(sorted.begin(), sorted.end(), paired_main);
        size_t limit = static_cast<size_t>(std::distance(sorted.begin(), it)) + 1;
        binary_insert(sorted, value_to_insert, limit);
    }
    
    if (has_straggler)
    {
        binary_insert(sorted, straggler, sorted.size());
    }
    
    deq = sorted;
}


