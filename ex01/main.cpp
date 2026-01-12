/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: franaivo <franaivo@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 19:14:25 by franaivo          #+#    #+#             */
/*   Updated: 2026/01/12 19:14:26 by franaivo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <RPN.hpp>
#include <iostream>

int main(int argc , char **argv)
{
    if(argc != 2)
    {
        std::cerr << "usage : ./RPN expr..." << std::endl;
        return EXIT_FAILURE;
    }

    try
    {
        std::cout << RPN::eval(argv[1]) << std::endl;
    }
    catch(std::exception &e)
    {
        std::cerr << "Error : " << e.what() << std::endl; 
    }

    return EXIT_SUCCESS;
}
