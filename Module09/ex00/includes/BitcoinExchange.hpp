#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange {
private:
    std::map<std::string, float> _exchangeRates;
    
    bool isValidDate(const std::string& date) const;
    bool isValidValue(const std::string& valueStr, float& value) const;
    void loadDatabase(const std::string& databaseFile);
    std::string findClosestDate(const std::string& date) const;

public:
    BitcoinExchange();
    BitcoinExchange(const std::string& databaseFile);
    BitcoinExchange(const BitcoinExchange& other);
    ~BitcoinExchange();
    BitcoinExchange& operator=(const BitcoinExchange& other);

    void processInputFile(const std::string& inputFile) const;
};

#endif