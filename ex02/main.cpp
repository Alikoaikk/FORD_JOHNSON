/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 12:55:09 by akoaik            #+#    #+#             */
/*   Updated: 2026/03/25 21:37:19 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pmerge.hpp"
#include "PmergeDeque.hpp"
#include <time.h>
#include <iomanip>

void printVec(const std::vector<int> &vec)
{
    for (size_t i = 0; i < vec.size(); i++)
        std::cout << vec[i] << " ";
    std::cout << std::endl;
}

void printDeque(const std::deque<int> &dq)
{
    for (size_t i = 0; i < dq.size(); i++)
        std::cout << dq[i] << " ";
    std::cout << std::endl;
}

int main(int argc, char **argv)
{
    int             comparisonsV = 0;
    int             comparisonsD = 0;

    clock_t start = clock();
    std::vector<int> vec = pars(argc, argv);
    Pmerge pm;
    pm.fordJohnson(vec, comparisonsV);
    clock_t vecEnd = clock();

    std::vector<int> tmp = pars(argc, argv);
    std::deque<int>  dq(tmp.begin(), tmp.end());
    PmergeDeque pd;
    pd.fordJohnson(dq, comparisonsD);
    clock_t deqEnd = clock();

    double vecTime = (double)(vecEnd - start) / CLOCKS_PER_SEC * 1e6;
    double deqTime = (double)(deqEnd - start) / CLOCKS_PER_SEC * 1e6;

    std::cout << "Before: ";
    printVec(pars(argc, argv));
    std::cout << "After:  ";
    printVec(vec);
    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Time to process a range of " << vec.size()
              << " elements with std::vector : " << vecTime << " us" << std::endl;
    std::cout << "Time to process a range of " << dq.size()
              << " elements with std::deque  : " << deqTime << " us" << std::endl;
    std::cout << "Number of comparisons (vector) : " << comparisonsV << std::endl;
    std::cout << "Number of comparisons (deque)  : " << comparisonsD << std::endl;
    return (0);
}
/*
    ## the example :

        random solution :   2 11 0 17 8 16 6 15 3 10 1 21 9 18 14 19 5 12 4 20 7
        optimal input :     131 87 56 167 391 142 23 22 537 705 242 305 552 456 303 162 235 13 511 792 450

    ## what i implement :

        1 - Jacobsthal sequence generator
        2 - parsing + validation
        3 - binary search implementation + testing
        4 - makePairs: form (winner, loser) pairs and split into main_chain / pend
        5 - fordJohnson: recursive sort of the main chain (vector + deque)
        6 - remapPend: re-order pend to stay paired with the sorted main chain
        7 - buildInsertOrder: produce Jacobsthal-ordered insertion sequence
        8 - insertPend: insert pend elements with bounded binary search (upper bound = paired winner position)
        9 - PmergeDeque: mirror implementation of the full algorithm for std::deque

*/
