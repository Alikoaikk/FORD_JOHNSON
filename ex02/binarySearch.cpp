/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binarySearch.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 04:55:04 by akoaik            #+#    #+#             */
/*   Updated: 2026/03/27 20:01:30 by akoaik           ###   ########.fr       */
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
