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
    
    print_sequence_vector("Before: ", vec);
    
    double start_vec = get_time_microseconds();
    ford_johnson_sort_vector(vec);
    double end_vec = get_time_microseconds();
    double time_vec = end_vec - start_vec;
    
    double start_deq = get_time_microseconds();
    ford_johnson_sort_deque(deq);
    double end_deq = get_time_microseconds();
    double time_deq = end_deq - start_deq;
    
    print_sequence_vector("After:  ", vec);
    
    print_time("vector", vec.size(), time_vec);
    print_time("deque ", deq.size(), time_deq);
    
    return 0;
}
