/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-alen <fde-alen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:08:13 by fde-alen          #+#    #+#             */
/*   Updated: 2025/07/25 17:17:03 by fde-alen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string& databaseFile) {
    loadDatabase(databaseFile);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) {
    _exchangeRates = other._exchangeRates;
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
    if (this != &other) {
        _exchangeRates = other._exchangeRates;
    }
    return *this;
}

void BitcoinExchange::loadDatabase(const std::string& databaseFile) {
    std::ifstream file(databaseFile.c_str());
    if (!file.is_open()) {
        throw std::runtime_error("Error: could not open database file.");
    }

    std::string line;

    std::getline(file, line);
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string date;
        std::string rateStr;

        if (std::getline(iss, date, ',') && std::getline(iss, rateStr)) {
            float rate = std::atof(rateStr.c_str());
            _exchangeRates[date] = rate;
        }
    }
    file.close();
}

bool BitcoinExchange::isValidDate(const std::string& date) const {
    if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }

    for (int i = 0; i < 10; ++i) {
        if (i == 4 || i == 7) continue;
        if (!std::isdigit(date[i])) {
            return false;
        }
    }

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (year < 2009 || year > 2023) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;

    return true;
}

bool BitcoinExchange::isValidValue(const std::string& valueStr, float& value) const {
    char* endptr;
    value = std::strtof(valueStr.c_str(), &endptr);

    if (*endptr != '\0' && *endptr != ' ') {
        return false;
    }
    if (value < 0) {
        return false;
    }
    if (value > 1000) {
        return false;
    }
    return true;
}

std::string BitcoinExchange::findClosestDate(const std::string& date) const {
    std::map<std::string, float>::const_iterator it = _exchangeRates.lower_bound(date);

    if (it == _exchangeRates.begin()) {
        if (it->first == date) {
            return date;
        } else {
            return ""; // No earlier date available
        }
    }

    if (it != _exchangeRates.end() && it->first == date) {
        return date;
    } else {
        --it; // Get the previous (lower) date
        return it->first;
    }
}

void BitcoinExchange::processInputFile(const std::string& inputFile) const {
    std::ifstream file(inputFile.c_str());
    if (!file.is_open()) {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }
    if (file.peek() == std::ifstream::traits_type::eof()) {
        std::cerr << "Error: file is empty." << std::endl;
        return;
    }

    std::string line;
    bool isFirstLine = true;

    while (std::getline(file, line)) {
        // Skip empty lines
        if (line.empty()) {
            continue;
        }

        std::istringstream iss(line);
        std::string date;
        std::string valueStr;

        if (std::getline(iss, date, '|') && std::getline(iss, valueStr)) {
            // Trim whitespace
            date.erase(date.find_last_not_of(" \t") + 1);
            valueStr.erase(0, valueStr.find_first_not_of(" \t"));
            valueStr.erase(valueStr.find_last_not_of(" \t") + 1);

            // Skip header line if it doesn't contain a valid date
            if (isFirstLine && !isValidDate(date)) {
                isFirstLine = false;
                continue;
            }
            isFirstLine = false;

            if (!isValidDate(date)) {
                std::cerr << "Error: bad input => " << date << std::endl;
                continue;
            }

            float value;
            if (!isValidValue(valueStr, value)) {
                if (value < 0) {
                    std::cerr << "Error: not a positive number." << std::endl;
                } else if (value > 1000) {
                    std::cerr << "Error: too large a number." << std::endl;
                } else {
                    std::cerr << "Error: invalid value format." << std::endl;
                }
                continue;
            }

            std::string closestDate = findClosestDate(date);
            if (closestDate.empty()) {
                std::cerr << "Error: no data available for date " << date << " or earlier." << std::endl;
                continue;
            }

            float rate = _exchangeRates.at(closestDate);
            float result = value * rate;

            std::cout << date << " => " << value << " = " << result << std::endl;
        } else {
            // Only show error if it's not the first line (potential header)
            if (!isFirstLine) {
                std::cerr << "Error: bad input => " << line << std::endl;
            }
            isFirstLine = false;
        }
    }
    file.close();
}
