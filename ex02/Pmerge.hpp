/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pmerge.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 02:12:00 by akoaik            #+#    #+#             */
/*   Updated: 2026/03/21 22:31:22 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_HPP
#define HEADER_HPP

#include <vector>
#include <iostream>
#include <cstddef>
#include <string>
#include <climits>
#include <cstdlib>
#include <cerrno>
#include <algorithm>
#include <utility>
#include <stdio.h>
#include <cmath>


class Pmerge
{
    public:
        Pmerge();
        Pmerge(const Pmerge& other);
        Pmerge& operator=(const Pmerge& other);
        ~Pmerge();

        void fordJohnson(std::vector<int>& arr, int& comparisons);
        void binarySearch(std::vector<int>& arr, int target);

    private:
        void                makePairs(const std::vector<int>& arr, std::vector<int>& main_chain, std::vector<int>& pend, int& comparisons);
        std::vector<int>    remapPend(const std::vector<int>& main_chain, const std::vector<int>& original_main, const std::vector<int>& pend, bool odd);
        void                insertPend(std::vector<int>& main_chain, const std::vector<int>& new_pend, int& comparisons);
        std::vector<int>    buildInsertOrder(int pend_size);
        int                 findInsertPos(const std::vector<int>& arr, int target, int left, int right, int& comparisons);
        std::vector<int>    jacob_seq(int leng);
};

std::vector<int> pars(int argc, char **argv);
void printVec(const std::vector<int> &vec);


#endif 