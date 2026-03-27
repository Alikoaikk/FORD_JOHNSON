/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binarySearch.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 04:55:04 by akoaik            #+#    #+#             */
/*   Updated: 2026/03/15 03:09:22 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pmerge.hpp"

int Pmerge::findInsertPos
(
    const std::vector<int>  &arr,
    int                     target,
    int                     left,
    int                     right,
    int&                    comparisons
)
{
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        comparisons++;
        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

void Pmerge::binarySearch
(
    std::vector<int>&   arr,
    int                 target
)
{
    int dummy = 0;
    int pos = findInsertPos(arr, target, 0, arr.size(), dummy);
    arr.insert(arr.begin() + pos, target);
}
