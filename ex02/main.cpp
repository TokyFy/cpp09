/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franaivo <franaivo@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 19:13:46 by franaivo          #+#    #+#             */
/*   Updated: 2026/01/12 19:13:51 by franaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <sys/time.h>
#include <ctime>

static double get_time_microseconds(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return static_cast<double>(tv.tv_sec) * 1000000.0 + static_cast<double>(tv.tv_usec);
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    
    std::vector<int> vec;
    std::deque<int> deq;
    double start, time_vec, time_deq;
    
    start = get_time_microseconds();
    if (!parse_arguments(argc, argv, deq))
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    std::deque<int> deq_original(deq);
    ford_johnson_sort_deque(deq);
    time_deq = get_time_microseconds() - start;
    
    start = get_time_microseconds();
    if (!parse_arguments(argc, argv, vec))
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    
    ford_johnson_sort_vector(vec);
    time_vec = get_time_microseconds() - start;
    
    print_sequence("Before: ", deq_original);
    print_sequence("After:  ", deq);
    
    print_time("Vector", vec.size(), time_vec);
    print_time("Deque ", deq.size(), time_deq);
    
    return 0;
}
