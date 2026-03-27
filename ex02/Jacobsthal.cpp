/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Jacobsthal.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 01:00:27 by akoaik            #+#    #+#             */
/*   Updated: 2026/03/21 21:38:49 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Pmerge.hpp"

std::vector<int> Pmerge::jacob_seq(int leng)
{
    // J(n) = J(n-1) + 2 * J(n-2),  starting: J(0)=0, J(1)=1
    std::vector<int> jNums;
    int count = 0 ;
    int j0 = 0;
    int j1 = 1;
    while (count <= leng)
    {
        int next = j1 + 2 * j0;
        jNums.push_back(next);
        j0 = j1;
        j1 = next;
        count++ ;
        if (next > leng)
            break ;
    }

    return jNums;
}
