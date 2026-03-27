/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 02:11:50 by akoaik            #+#    #+#             */
/*   Updated: 2026/03/24 20:23:58 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pmerge.hpp"
#include <sstream>

std::vector<int> pars(int argc, char **argv)
{
    std::vector<int> result;

    if (argc < 2)
    {
        std::cerr << "Error: no input" << std::endl;
        exit(1);
    }

    if (argc == 2)
    {
        // single quoted string: "2 11 0 17 ..."
        std::istringstream iss(argv[1]);
        std::string token;
        while (iss >> token)
        {
            std::istringstream ts(token);
            long val;
            char leftover;

            if (!(ts >> val) || ts.get(leftover))
            {
                std::cerr << "Error: invalid input: " << token << std::endl;
                exit(1);
            }
            if (val < 0 || val > INT_MAX)
            {
                std::cerr << "Error: out of range: " << token << std::endl;
                exit(1);
            }
            result.push_back(static_cast<int>(val));
        }
    }
    else
    {
        // separate args: ./prog 2 11 0 17 ...
        for (int i = 1; i < argc; i++)
        {
            std::istringstream iss(argv[i]);
            long val;
            char leftover;

            if (!(iss >> val) || iss.get(leftover))
            {
                std::cerr << "Error: invalid input: " << argv[i] << std::endl;
                exit(1);
            }
            if (val < 0 || val > INT_MAX)
            {
                std::cerr << "Error: out of range: " << argv[i] << std::endl;
                exit(1);
            }
            result.push_back(static_cast<int>(val));
        }
    }

    return result;
}
