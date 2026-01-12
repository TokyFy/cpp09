/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franaivo <franaivo@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 10:25:28 by franaivo          #+#    #+#             */
/*   Updated: 2026/01/12 19:13:34 by franaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

// VECTOR IMPLEMENTATION

void binary_insert_vector(std::vector<int>& sorted, int value, size_t limit)
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
    for (size_t i = 0; i < pair_count; ++i)
    {
        int a = vec[2 * i];
        int b = vec[2 * i + 1];
        
        if (a < b)
            pairs.push_back(std::make_pair(b, a));
        else
            pairs.push_back(std::make_pair(a, b));
    }
    
    // Extract larger and smaller values from pairs and create direct mapping
    std::vector<int> main_chain;
    std::map<int, int> value_map;  // Maps main_chain value to its pend value
    for (size_t i = 0; i < pairs.size(); ++i)
    {
        main_chain.push_back(pairs[i].first);
        value_map[pairs[i].first] = pairs[i].second;
    }
    
    ford_johnson_sort_vector(main_chain);
    
    // After recursion: main_chain is sorted. Create sorted_pend using map (O(n log n))
    std::vector<int> sorted_pend(main_chain.size());
    for (size_t i = 0; i < main_chain.size(); ++i)
        sorted_pend[i] = value_map[main_chain[i]];
    
    // Initialize sorted with the first pend element (smallest in entire sequence)
    std::vector<int> sorted;
    if (pair_count > 0)
        sorted.push_back(sorted_pend[0]);
    
    // Add all sorted main_chain elements
    for (size_t i = 0; i < main_chain.size(); ++i)
        sorted.push_back(main_chain[i]);
    
    // Insert remaining pend elements using Jacobsthal order
    std::vector<size_t> insertion_order = generate_insertion_order(pair_count);
    
    for (size_t i = 0; i < insertion_order.size(); ++i)
    {
        size_t pend_idx = insertion_order[i] - 1;
        if (pend_idx >= pair_count)
            continue;
        
        int value_to_insert = sorted_pend[pend_idx];
        int paired_main = main_chain[pend_idx];
        
        // Find current position of paired main_chain element using binary search
        std::vector<int>::iterator it = std::lower_bound(sorted.begin(), sorted.end(), paired_main);
        size_t limit = static_cast<size_t>(std::distance(sorted.begin(), it)) + 1;
        binary_insert_vector(sorted, value_to_insert, limit);
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

// DEQUE IMPLEMENTATION

void binary_insert_deque(std::deque<int>& sorted, int value, size_t limit)
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
    for (size_t i = 0; i < pair_count; ++i)
    {
        int a = deq[2 * i];
        int b = deq[2 * i + 1];
        
        if (a < b)
            pairs.push_back(std::make_pair(b, a));
        else
            pairs.push_back(std::make_pair(a, b));
    }
    
    // Extract larger and smaller values from pairs and create direct mapping
    std::deque<int> main_chain;
    std::map<int, int> value_map;  // Maps main_chain value to its pend value
    for (size_t i = 0; i < pairs.size(); ++i)
    {
        main_chain.push_back(pairs[i].first);
        value_map[pairs[i].first] = pairs[i].second;
    }
    
    ford_johnson_sort_deque(main_chain);
    
    // After recursion: main_chain is sorted. Create sorted_pend using map (O(n log n))
    std::deque<int> sorted_pend(main_chain.size());
    for (size_t i = 0; i < main_chain.size(); ++i)
        sorted_pend[i] = value_map[main_chain[i]];
    
    // Initialize sorted with the first pend element (smallest in entire sequence)
    std::deque<int> sorted;
    if (pair_count > 0)
        sorted.push_back(sorted_pend[0]);
    
    // Add all sorted main_chain elements
    for (size_t i = 0; i < main_chain.size(); ++i)
        sorted.push_back(main_chain[i]);
    
    // Insert remaining pend elements using Jacobsthal order (minimizes comparisons)
    std::vector<size_t> insertion_order = generate_insertion_order(pair_count);
    
    for (size_t i = 0; i < insertion_order.size(); ++i)
    {
        size_t pend_idx = insertion_order[i] - 1;
        if (pend_idx >= pair_count)
            continue;
        
        int value_to_insert = sorted_pend[pend_idx];
        int paired_main = main_chain[pend_idx];
        
        // Find current position of paired main_chain element using binary search
        std::deque<int>::iterator it = std::lower_bound(sorted.begin(), sorted.end(), paired_main);
        size_t limit = static_cast<size_t>(std::distance(sorted.begin(), it)) + 1;
        binary_insert_deque(sorted, value_to_insert, limit);
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
