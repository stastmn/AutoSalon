#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include "Auto.h"
#include "Customer.h"
#include <unordered_set>
#include <vector>
#include <random>

enum Commands {
	close,
	invalid,
	help,
	printAuto,
	printCustomer,
	addCustomer,
	buyAuto,
	printCustomerAutos,
	filterInfo,
	setFilter,
	filterPrinting
};


class Application
{
public:
	Application();
	void Run();

private:
	void UpdateCurrentCommand(std::string& stringCommand);
	void GenerateAutos();

	void CloseCommand();
	void InvalidCommand();
	void HelpCommand();
	void PrintAutoCommand();
	void PrintCustomerCommand();
	void AddNewCustomerCommand();
	void BuyAutoCommand();
	void printCustomerAutosCommand();
	void filterInfoCommand();
	void setFilterCommand();
	void filterPrintingCommand();
	


private:
	bool m_Running;
	Commands m_currentCommand;
	std::unordered_map<std::string, Commands> stringToCommand;
	std::vector<Auto> autos;
	std::vector<Customer> customers;

	//its autoId to customerId mapping table
	std::unordered_map<unsigned int, unsigned int> transactions;

	Filter m_flt;
	std::mt19937 m_mtRand;
};

