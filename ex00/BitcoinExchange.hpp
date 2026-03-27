/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 23:19:33 by akoaik            #+#    #+#             */
/*   Updated: 2026/03/24 20:03:44 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>
#include <string>
#include <sstream>

class BitcoinExchange
{
    private :
        std::map<std::string, float> _db ;
        bool  validateValue(float value) const;
        float getRate(const std::string& date) const;

    public :
        BitcoinExchange();
        BitcoinExchange(const std::string& DBName);
        BitcoinExchange(const BitcoinExchange& other);
        BitcoinExchange& operator=(const BitcoinExchange& other);
        ~BitcoinExchange();

        void processInput(const std::string& filename);
        bool isValidDate(const std::string& date) const;
} ;

#endif
