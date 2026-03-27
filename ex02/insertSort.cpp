/* ************************************************************************ */
/*                                                                          */
/*                                                       :::      ::::::::  */
/*  insertSort.cpp                                     :+:      :+:    :+:  */
/*                                                   +:+ +:+         +:+    */
/*  By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+       */
/*                                               +#+#+#+#+#+   +#+          */
/*  Created: 2026/03/08 00:28:11 by akoaik            #+#    #+#            */
/*  Updated: 2026/03/15 03:10:44 by akoaik           ###   ########.fr      */
/*                                                                          */
/* ************************************************************************ */

#include "Pmerge.hpp"

std::vector<int> Pmerge::buildInsertOrder(int pend_size)
{
    std::vector<int> jseq = jacob_seq(pend_size);
    std::vector<int> order;

    // 2^k - 1 for bounds

    int start = 1;
    for (size_t k = 0; k < jseq.size(); k++)
    {
        int end = std::min(jseq[k], pend_size);
        for (int idx = end; idx > start; idx--)
            order.push_back(idx);
        start = jseq[k];
        if (start >= pend_size)
            break ;
    }
    return order;
}

void Pmerge::insertPend(std::vector<int>& main_chain, const std::vector<int>& new_pend, int& comparisons)
{
    if (new_pend.empty())
        return ;

    std::vector<int> winners = main_chain; // snapshot before any insertions

    // new_pend[0] is guaranteed <= main_chain[0], insert at front (0 comparisons)
    main_chain.insert(main_chain.begin(), new_pend[0]);

    if ((int)new_pend.size() == 1)
        return ;

    int n = (int)new_pend.size();
    std::vector<int> order = buildInsertOrder(n);

    int high = 3;
    for (size_t k = 0; k < order.size(); k++)
    {
        if (k > 0 && order[k] > order[k - 1])
            high = high * 2 + 1;
        int idx   = order[k] - 1; // convert to 0-indexed
        int winnerPos;
        if (idx < (int)winners.size())
        {
            std::vector<int>::iterator highWinner = std::find(main_chain.begin(), main_chain.end(), winners[idx]);
            winnerPos = (int)(highWinner - main_chain.begin() + 1);
        }
        else
            winnerPos = (int)main_chain.size(); // straggler: no paired winner, search full chain
        int bound = std::min(high, winnerPos);
        int pos   = findInsertPos(main_chain, new_pend[idx], 0, bound, comparisons);
        main_chain.insert(main_chain.begin() + pos, new_pend[idx]);
    }
}
