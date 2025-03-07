#include <ctime>
#include <iostream>
#include "Account.hpp"

/******************************************************************************/
/*						STATIC MEMBER INITIALIZATION						  */
/******************************************************************************/

int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

/******************************************************************************/
/*						CONSTRUCTORS & DESTRUCTORS							  */
/******************************************************************************/

Account::Account() : _accountIndex(_nbAccounts), _amount(0), _nbDeposits(0), _nbWithdrawals(0) {
  _nbAccounts++;
}

Account::Account(int initial_deposit)
    : _accountIndex(_nbAccounts), _amount(initial_deposit), _nbDeposits(0), _nbWithdrawals(0) {
  _nbAccounts++;
  _totalAmount += _amount;
  _displayTimestamp();
  std::cout << "index:" << _accountIndex << ";"
            << "amount:" << _amount << ";"
            << "created" << std::endl;
}

Account::~Account() {
  _nbAccounts--;
  _displayTimestamp();
  std::cout << "index:" << _accountIndex << ";"
            << "amount:" << _amount << ";"
            << "closed" << std::endl;
}

/******************************************************************************/
/*								GETTERS										  */
/******************************************************************************/

int Account::getNbAccounts() { return _nbAccounts; }

int Account::getTotalAmount() { return _totalAmount; }

int Account::getNbDeposits() { return _totalNbDeposits; }

int Account::getNbWithdrawals() { return _totalNbWithdrawals; }

/******************************************************************************/
/*							PRIVATE FUNCTIONS								  */
/******************************************************************************/

void Account::_displayTimestamp() {
  std::time_t rawTime;
  struct tm* timeInfo;

  std::time(&rawTime);
  timeInfo = std::localtime(&rawTime);

  std::cout << "[" << timeInfo->tm_year + 1900;
  if (timeInfo->tm_mon < 10) std::cout << "0";
  std::cout << timeInfo->tm_mon;
  if (timeInfo->tm_mday < 10) std::cout << "0";
  std::cout << timeInfo->tm_mday << "_";
  if (timeInfo->tm_hour < 10) std::cout << "0";
  std::cout << timeInfo->tm_hour;
  if (timeInfo->tm_min < 10) std::cout << "0";
  std::cout << timeInfo->tm_min;
  if (timeInfo->tm_sec < 10) std::cout << "0";
  std::cout << timeInfo->tm_sec << "] ";
}

/******************************************************************************/
/*							PUBLIC FUNCTIONS								  */
/******************************************************************************/

void Account::makeDeposit(int deposit) {
  _displayTimestamp();
  std::cout << "index:" << _accountIndex << ";"
            << "p_amount:" << _amount << ";"
            << "deposit:";
  _amount += deposit;
  _totalAmount += deposit;
  _nbDeposits++;
  _totalNbDeposits++;
  std::cout << deposit << ";"
            << "amount:" << _amount << ";"
            << "nb_deposits:" << _nbDeposits << std::endl;
}

bool Account::makeWithdrawal(int withdrawal) {
  _displayTimestamp();
  std::cout << "index:" << _accountIndex << ";"
            << "p_amount:" << _amount << ";"
            << "withdrawal:";
  if (withdrawal > _amount) {
    std::cout << "refused" << std::endl;
    return false;
  }
  _amount -= withdrawal;
  _totalAmount -= withdrawal;
  _nbWithdrawals++;
  _totalNbWithdrawals++;
  std::cout << withdrawal << ";"
            << "amount:" << _amount << ";"
            << "nb_withdrawals:" << _nbWithdrawals << std::endl;
  return true;
}

int Account::checkAmount() const { return _amount; }

void Account::displayStatus() const {
  _displayTimestamp();
  std::cout << "index:" << _accountIndex << ";"
            << "amount:" << _amount << ";"
            << "deposits:" << _nbDeposits << ";"
            << "withdrawals:" << _nbWithdrawals << std::endl;
}

void Account::displayAccountsInfos() {
  _displayTimestamp();
  std::cout << "accounts:" << getNbAccounts() << ";"
            << "total:" << getTotalAmount() << ";"
            << "deposits:" << getNbDeposits() << ";"
            << "withdrawals:" << getNbWithdrawals() << std::endl;
}