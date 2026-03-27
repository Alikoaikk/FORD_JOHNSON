/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 16:48:35 by akoaik            #+#    #+#             */
/*   Updated: 2026/02/28 00:43:56 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN()
{}

RPN::RPN(const RPN& other) 
    : _stack(other._stack)
{}

RPN& RPN::operator=(const RPN& other)
{
    if (this != &other)
        _stack = other._stack;
    return *this;
}

RPN::~RPN()
{}

int RPN::evaluate(const std::string& expr)
{
    std::istringstream ss(expr);
    std::string token;
    int n;

    while (ss >> token)
    {
        if (token == "+" || token == "-" || token == "*" || token == "/")
        {
            if (_stack.size() < 2)
                throw std::runtime_error("Error");


            int b = _stack.top();
            _stack.pop();
            int a = _stack.top();
            _stack.pop();
            
            
            if (token == "+")
                _stack.push(a + b);
            else if (token == "-")
                _stack.push(a - b);
            else if (token == "*")
                _stack.push(a * b);
            else if (token == "/")
            {
                if (b == 0)
                    throw std::runtime_error("Error");
                _stack.push(a / b);
            }
        }
        else
        {
            std::istringstream num(token);
            if (token.length() != 1 || !isdigit(token[0]))
                throw std::runtime_error("invalid input");
            if (!(num >> n))
                throw std::runtime_error("Error");
            _stack.push(n);
        }
    }
    if (_stack.size() != 1)
        throw std::runtime_error("Error");
    return _stack.top();
}