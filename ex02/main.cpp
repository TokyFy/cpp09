/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franaivo <franaivo@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 00:00:00 by franaivo          #+#    #+#             */
/*   Updated: 2025/01/06 00:00:00 by franaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <sys/time.h>
#include <iomanip>

/*
** Get current time in microseconds
*/
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
    
    if (!parse_arguments(argc, argv, vec, deq))
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    
    if (vec.empty())
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }
    
    /* Display unsorted sequence */
    print_sequence_vector("Before: ", vec);
    
    /* Sort with vector and measure time */
    std::vector<int> vec_copy = vec;
    double start_vec = get_time_microseconds();
    ford_johnson_sort_vector(vec_copy);
    double end_vec = get_time_microseconds();
    double time_vec = end_vec - start_vec;
    
    /* Sort with deque and measure time */
    std::deque<int> deq_copy = deq;
    double start_deq = get_time_microseconds();
    ford_johnson_sort_deque(deq_copy);
    double end_deq = get_time_microseconds();
    double time_deq = end_deq - start_deq;
    
    /* Display sorted sequence */
    print_sequence_vector("After:  ", vec_copy);
    
    /* Display timing information */
    std::cout << std::fixed << std::setprecision(5);
    print_time("vector", vec.size(), time_vec);
    print_time("deque", deq.size(), time_deq);
    
    return 0;
}
