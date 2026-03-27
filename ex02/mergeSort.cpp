/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mergeSort.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 22:53:06 by akoaik            #+#    #+#             */
/*   Updated: 2026/03/24 19:32:29 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pmerge.hpp"

void Pmerge::makePairs
(
    const std::vector<int>& arr,
    std::vector<int>& main_chain,
    std::vector<int>& pend,
    int& comparisons
)
{
    for (size_t i = 0; i + 1 < arr.size(); i += 2)
    {
        comparisons++;
        if (arr[i] > arr[i + 1])
        {
            main_chain.push_back(arr[i]);
            pend.push_back(arr[i + 1]);
        }
        else
        {
            main_chain.push_back(arr[i + 1]);
            pend.push_back(arr[i]);
        }
    }
    if (arr.size() % 2 != 0)
        pend.push_back(arr.back());

    // straggler: no pair, goes to pend

}

std::vector<int> Pmerge::remapPend
(
    const std::vector<int>& main_chain,
    const std::vector<int>& original_main,
    const std::vector<int>& pend,
    bool odd
)
{
    std::vector<int> new_pend(main_chain.size());
    std::vector<bool> used(main_chain.size(), false);

    for (size_t i = 0; i < main_chain.size(); i++)
    {
        for (size_t j = 0; j < original_main.size(); j++)
        {
            if (!used[j] && original_main[j] == main_chain[i])
            {
                new_pend[i] = pend[j];
                used[j] = true;
                break;
            }
        }
    }
    if (odd)
        new_pend.push_back(pend.back()); // straggler stays at the end
    return new_pend;
}

void Pmerge::fordJohnson(std::vector<int>& arr, int& comparisons)
{
    std::vector<int> main_chain;
    std::vector<int> pend;

    if (arr.size() <= 1)
        return ;
    if (arr.size() == 2)
    {
        comparisons++;
        if (arr[0] > arr[1])
            std::swap(arr[0], arr[1]);
        return ; 
    }

    bool odd = (arr.size() % 2 != 0);
    makePairs(arr, main_chain, pend, comparisons);

    std::vector<int> original_main = main_chain;
    fordJohnson(main_chain, comparisons);

    // remap pend to follow sorted main_chain
    std::vector<int> new_pend = remapPend(main_chain, original_main, pend, odd);

    insertPend(main_chain, new_pend, comparisons);

    arr = main_chain;
}
