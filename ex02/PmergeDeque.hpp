/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeDeque.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 22:34:41 by akoaik            #+#    #+#             */
/*   Updated: 2026/03/15 22:34:42 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEDEQUE_HPP
#define PMERGEDEQUE_HPP

#include <deque>
#include <vector>
#include <iostream>
#include <algorithm>

class PmergeDeque
{
    public:
        PmergeDeque();
        PmergeDeque(const PmergeDeque& other);
        PmergeDeque& operator=(const PmergeDeque& other);
        ~PmergeDeque();

        void fordJohnson(std::deque<int>& arr, int& comparisons);

    private:
        void             makePairs(const std::deque<int>& arr, std::deque<int>& main_chain, std::deque<int>& pend, int& comparisons);
        std::deque<int>  remapPend(const std::deque<int>& main_chain, const std::deque<int>& original_main, const std::deque<int>& pend, bool odd);
        void             insertPend(std::deque<int>& main_chain, const std::deque<int>& new_pend, int& comparisons);
        std::vector<int> buildInsertOrder(int pend_size);
        int              findInsertPos(const std::deque<int>& arr, int target, int left, int right, int& comparisons);
        std::vector<int> jacob_seq(int leng);
};

#endif
