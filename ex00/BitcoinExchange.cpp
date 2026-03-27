/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoaik <akoaik@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 23:19:33 by akoaik            #+#    #+#             */
/*   Updated: 2026/02/23 23:19:33 by akoaik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <cstdlib>
#include <map>

BitcoinExchange::BitcoinExchange()
{}

static void checkCSV(std::ifstream& file, std::map<std::string, float>& db)
{
    std::string line;
    if (!std::getline(file, line))
        throw std::runtime_error("Error: CSV file is empty.");
    if (line != "date,exchange_rate")
        throw std::runtime_error("Error: invalid CSV header => " + line);

    while (std::getline(file, line))
    {
        if (line.empty())
            continue;
        size_t pos = line.find(',');
        if (pos == std::string::npos)
            throw std::runtime_error("Error: corrupted CSV data => " + line);
        std::string date    = line.substr(0, pos);
        std::string rateStr = line.substr(pos + 1);
        if (date.empty() || rateStr.empty())
            throw std::runtime_error("Error: corrupted CSV data => " + line);
        char* end;
        float rate = std::strtof(rateStr.c_str(), &end);
        if (*end != '\0' && *end != '\r')
            throw std::runtime_error("Error: corrupted CSV data => " + line);
        db[date] = rate;
    }
    if (db.empty())
        throw std::runtime_error("Error: CSV file contains no valid data.");
}

BitcoinExchange::BitcoinExchange(const std::string& DBName)
{
    std::ifstream file(DBName.c_str());
    if (!file.is_open())
        throw std::runtime_error("Error: could not open file.");
    checkCSV(file, _db);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
    _db = other._db;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
    if (this != &other)
        _db = other._db;
    return *this ;
}

BitcoinExchange::~BitcoinExchange()
{}

bool BitcoinExchange::validateValue(float value) const
{
    if (value < 0)
    {
        std::cerr << "Error: not a positive number." << std::endl;
        return false;
    }
    if (value > 1000)
    {
        std::cerr << "Error: too large a number." << std::endl;
        return false;
    }
    return true;
}

float BitcoinExchange::getRate(const std::string& date) const
{
    std::map<std::string, float>::const_iterator it = _db.lower_bound(date);
    if (it == _db.end() || it->first != date)
    {
        if (it == _db.begin())
            return -1;
        --it;
    }
    return it->second;
}

bool BitcoinExchange::isValidDate(const std::string& date) const
{

    for(std::size_t i = 0 ; i < date.size() ; i++)
    {
        if (!std::isdigit(date[i]) && date[i] != '-')
            return false;
    }
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        return false;

    int year  = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day   = std::atoi(date.substr(8, 2).c_str());

    if (month < 1 || month > 12 || day < 1)
        return false;

    static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool leapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    int maxDay = daysInMonth[month - 1];
    if (month == 2 && leapYear)
        maxDay = 29;
    return day <= maxDay;
}

void BitcoinExchange::processInput(const std::string& filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: could not open file." << std::endl;
        return ;
    }
    std::string line;
    std::getline(file, line); // skip header
    while (std::getline(file, line))
    {
        size_t pos = line.find(" | ");
        if (pos == std::string::npos)
        {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }
        std::string date     = line.substr(0, pos);
        std::string valueStr = line.substr(pos + 3); // to skip " | "
        if (!isValidDate(date))
        {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }
        std::stringstream ss(valueStr) ;
        float value ;
        if (!(ss >> value))
        {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }
        if (!validateValue(value))
            continue;
        float rate = getRate(date);
        if (rate < 0)
        {
            std::cerr << "Error: bad input => " << date << std::endl;
            continue;
        }
        std::cout << date << " => " << value << " = " << value * rate << std::endl;
    }
}
