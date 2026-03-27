/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeDeque.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/15 22:36:45 by akoaik            #+#    #+#             */
/*   Updated: 2026/03/15 22:37:23 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeDeque.hpp"

PmergeDeque::PmergeDeque()
{}
PmergeDeque::PmergeDeque(const PmergeDeque& other)
{
    (void)other;
}
PmergeDeque& PmergeDeque::operator=(const PmergeDeque& other) 
{
    (void)other; return *this;
}
PmergeDeque::~PmergeDeque()
{}

std::vector<int> PmergeDeque::jacob_seq(int leng)
{
    std::vector<int> jNums;
    int count = 0;
    int j0 = 0;
    int j1 = 1;
    while (count <= leng)
    {
        int next = j1 + 2 * j0;
        jNums.push_back(next);
        j0 = j1;
        j1 = next;
        count++;
        if (next > leng)
            break;
    }
    return jNums;
}

std::vector<int> PmergeDeque::buildInsertOrder(int pend_size)
{
    std::vector<int> jraw = jacob_seq(pend_size);
    std::vector<int> order;

    int prev_j = 1;
    for (size_t k = 0; k < jraw.size(); k++)
    {
        int j = std::min(jraw[k], pend_size);
        for (int idx = j; idx > prev_j; idx--)
            order.push_back(idx);
        prev_j = jraw[k];
        if (prev_j >= pend_size)
            break;
    }
    return order;
}

int PmergeDeque::findInsertPos
(
    const std::deque<int>& arr,
    int target,
    int left,
    int right,
    int& comparisons
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

void PmergeDeque::makePairs
(
    const std::deque<int>& arr,
    std::deque<int>& main_chain,
    std::deque<int>& pend,
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
}

std::deque<int> PmergeDeque::remapPend
(
    const std::deque<int>& main_chain,
    const std::deque<int>& original_main,
    const std::deque<int>& pend,
    bool odd
)
{
    std::deque<int> new_pend(main_chain.size());
    std::vector<bool> used(original_main.size(), false);

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
        new_pend.push_back(pend.back());
    return new_pend;
}

void PmergeDeque::insertPend
(
    std::deque<int>& main_chain,
    const std::deque<int>& new_pend,
    int& comparisons
)
{
    if (new_pend.empty())
        return;

    std::deque<int> winners = main_chain;

    main_chain.insert(main_chain.begin(), new_pend[0]);

    if ((int)new_pend.size() == 1)
        return;

    int n = (int)new_pend.size();
    std::vector<int> order = buildInsertOrder(n);

    int high = 3;
    for (size_t k = 0; k < order.size(); k++)
    {
        if (k > 0 && order[k] > order[k - 1])
            high = 2 * high + 1;

        int idx = order[k] - 1;
        int winnerPos;
        if (idx < (int)winners.size())
        {
            std::deque<int>::iterator highWinner = std::find(main_chain.begin(), main_chain.end(), winners[idx]);
            winnerPos = (int)(highWinner - main_chain.begin()) + 1;
        }
        else
            winnerPos = (int)main_chain.size();
        int bound = std::min(high, winnerPos);
        int pos   = findInsertPos(main_chain, new_pend[idx], 0, bound, comparisons);
        main_chain.insert(main_chain.begin() + pos, new_pend[idx]);
    }
}

void PmergeDeque::fordJohnson(std::deque<int>& arr, int& comparisons)
{
    std::deque<int> main_chain;
    std::deque<int> pend;

    if (arr.size() <= 1)
        return;
    if (arr.size() == 2)
    {
        comparisons++;
        if (arr[0] > arr[1])
            std::swap(arr[0], arr[1]);
        return;
    }

    bool odd = (arr.size() % 2 != 0);
    makePairs(arr, main_chain, pend, comparisons);

    std::deque<int> original_main = main_chain;
    fordJohnson(main_chain, comparisons);

    std::deque<int> new_pend = remapPend(main_chain, original_main, pend, odd);
    insertPend(main_chain, new_pend, comparisons);

    arr = main_chain;
}
