#include "Application.h"
#include <chrono>
#include <functional>

const int MAX_AUTO_NUMBER = 10;

Application::Application():m_Running(false),
							m_currentCommand(Commands::invalid),
	stringToCommand({
		{"close", Commands::close},
		{"help", Commands::help},
		{"printAuto", Commands::printAuto},
		{"printCustomer", Commands::printCustomer},
		{"addCustomer", Commands::addCustomer},
		{"buyAuto", Commands::buyAuto},
		{"printCustomerAutos", Commands::printCustomerAutos},
		{"filterInfo", Commands::filterInfo},
		{"setFilter", Commands::setFilter},
		{"filterPrinting", Commands::filterPrinting},
		
		}),
		m_mtRand(std::chrono::high_resolution_clock::now().time_since_epoch().count())
{
	GenerateAutos();
}

void Application::Run()
{
	m_Running = true;
	std::string command;

	std::cout << "Welcome to our auto salon! Enter a command please.\n";

	while (m_Running)
	{
		std::cin >> command;
		UpdateCurrentCommand(command);


		switch (m_currentCommand)
		{
		case(Commands::close):
			CloseCommand();
			break;

		case(Commands::help):
			HelpCommand();
			break;

		case(Commands::invalid):
			InvalidCommand();
			break;

		case(Commands::printAuto):
			PrintAutoCommand();
			break;

		case(Commands::printCustomer):
			PrintCustomerCommand();
			break;

		case(Commands::addCustomer):
			AddNewCustomerCommand();
			break;

		case(Commands::buyAuto):
			BuyAutoCommand();
			break;

		case(Commands::printCustomerAutos):
			printCustomerAutosCommand();
			break;

		case(Commands::filterInfo):
			filterInfoCommand();
			break;

		case(Commands::setFilter):
			setFilterCommand();
			break;

		case(Commands::filterPrinting):
			filterPrintingCommand();
			break;
		default:
			break;
		}
	}
}


void Application::UpdateCurrentCommand(std::string& stringCommand)
{
	auto iterator = stringToCommand.find(stringCommand);
	if ( iterator != stringToCommand.end()) {
		m_currentCommand = iterator->second;
	}
	else {
		m_currentCommand = Commands::invalid;
	}
}

void Application::GenerateAutos()
{
	for (int i = 0; i < MAX_AUTO_NUMBER; i++) {

		auto id = m_mtRand();
		//we use only 3 colors.
		auto color = std::bind(std::uniform_int_distribution<int>(0, 2), m_mtRand)();
		auto speed = std::bind(std::uniform_int_distribution<unsigned int>(60, 300), m_mtRand)();
		auto price = std::bind(std::uniform_int_distribution<unsigned int>(100000, 3000000), m_mtRand)();
		
		//Auto tmpAuto(id, Color(color), price, speed);
		autos.push_back({ id, Color(color), price, speed });
		}
}

void Application::CloseCommand()
{
	m_Running = false;
}

void Application::InvalidCommand()
{
	std::cout << "Invalid command.\n";
}

//TODO: add all commands
void Application::HelpCommand()
{
	std::cout << "----------------------------------\n";
	std::cout<<"You can use these commands:\n \
		\t help \n \
		\t close \n \
		\t printAuto \n \
		\t printCustomer \n \
		\t addCustomer \n \
		\t buyAuto \n \
		\t printCustomerAutos \n \
		\t filterInfo \n \
		\t setFilter \n \
		\t filterPrinting \n";
	std::cout << "----------------------------------\n";
}

void Application::PrintAutoCommand()
{
	std::cout << "----------------------------------\n";
	std::cout << "We have these autos:\n";
	for (const auto& n : autos) {
		if (transactions.find(n.GetId()) == transactions.end()) {
			std::cout << "Id:" << n.GetId() << "\t Color:" << n.GetColor() << "\t Speed:" << n.GetSpeed() << "\t Price:" << n.GetPrice() << "\n";
		}
	}
	std::cout << "----------------------------------\n";
}

void Application::PrintCustomerCommand()
{
	std::cout << "----------------------------------\n";
	std::cout << "We have these customers:\n";
	for (const auto& n : customers) {
		std::cout << "Id:" << n.GetId() << "\n";
	}
	std::cout << "----------------------------------\n";
}

void Application::AddNewCustomerCommand()
{
	std::cout << "----------------------------------\n";
	
	auto id = m_mtRand();
	customers.push_back({ id });
	std::cout << "New customer with customerId:"<<id<<" was added to the system.\n";
	std::cout << "----------------------------------\n";
}

void Application::BuyAutoCommand()
{
	std::cout << "----------------------------------\n";
	std::cout << "Enter a customerId please\n";
	unsigned int customerId;
	std::cin >> customerId;
	//TODO: handle bad type input

	std::cout << "Enter a autoId please\n";
	unsigned int autoId;
	std::cin >> autoId;

	
	if (transactions.find(autoId) != transactions.end() ||
		std::find(autos.begin(),autos.end(),Auto(autoId,Color::blue,0,0)) == autos.end()) {
		std::cout << "Bad autoId.";
		std::cout << "----------------------------------\n";
		return;
	}

	if (std::find(customers.begin(),customers.end(),Customer(customerId)) == customers.end()) {
		std::cout << "Bad customerId.";
		std::cout << "----------------------------------\n";
		return;
	}

	transactions[autoId] = customerId;
	std::cout << "Customer with customerId:"<<customerId<<" has successfully purchase a car with autoId:"<<autoId<<"!\n";
	std::cout << "----------------------------------\n";
}

void Application::printCustomerAutosCommand()
{
	std::cout << "Enter a customerId please\n";
	unsigned int customerId;
	std::cin >> customerId;
	//TODO: handle bad type input

	if (std::find(customers.begin(), customers.end(), Customer(customerId)) == customers.end()) {
		std::cout << "Bad customerId.";
		return;
	}
	std::cout << "----------------------------------\n";
	std::cout << "Customers with id:"<<customerId<<" has these autos:\n";
	auto& autosRef = autos;
	std::for_each(transactions.begin() , transactions.end(), [customerId, &autosRef](const std::unordered_map<unsigned int,unsigned int>::value_type& transaction) { 
		if (transaction.second == customerId) {
			
			auto car = std::find(autosRef.begin(), autosRef.end(), Auto(transaction.first, Color::blue, 0, 0));
			std::cout << "Id:" << car->GetId() << "\t Color:" << car->GetColor() << "\t Speed:" << car->GetSpeed() << "\t Price:" << car->GetPrice() << "\n";

		}

		});
	std::cout << "----------------------------------\n";
}

void Application::filterInfoCommand()
{
	std::cout << "----------------------------------\n";
	std::cout << "Current filter properties:\n\tFilter function: " << m_flt.GetComparisonFunctionString() << "\n\tFilter property: "
		<<m_flt.GetComparisonPropertyString() << "\n\tComparsion value: "<< m_flt.GetComparisonValue()<<"\n";
	std::cout << "----------------------------------\n";
}

void Application::setFilterCommand()
{
	std::cout << "Enter comparsion property\n(0 - color, 1 - speed, 2 - price)\n";
	unsigned int prop;
	std::cin >> prop;
	if (prop == 0) { m_flt.SetComparisonProperty(color); }
	else if (prop == 1) { m_flt.SetComparisonProperty(speed); }
	else if (prop == 2) { m_flt.SetComparisonProperty(price); }
	else { std::cout << "Bad property type."; std::cout << "----------------------------------\n"; return; }

	std::cout << "----------------------------------\n";
	std::cout << "Enter comparsion function\n(0 - equal, 1 - less, 2 - greater)\n";
	unsigned int function;
	std::cin >> function;
	if (function == 0) { m_flt.SetComparisonFunction(equal); }
	else if (function == 1) { m_flt.SetComparisonFunction(less); }
	else if (function == 2) { m_flt.SetComparisonFunction(greater); }
	else { std::cout << "Bad function type."; std::cout << "----------------------------------\n"; return; }

	std::cout << "Enter comparsion value\n(For colors use this values: 0 - red, 1 - green, 2 - blue)\n";
	unsigned int value;
	std::cin >>value;
	m_flt.SetComparisonValue(value);
	std::cout << "New filter was successfully setted.\n";
	std::cout << "----------------------------------\n";
}

void Application::filterPrintingCommand()
{
	std::cout << "----------------------------------\n";
	std::cout << "Filtered list:\n";
	for (const auto& n : autos) {
		if (transactions.find(n.GetId()) == transactions.end() && m_flt(n)) {
			std::cout << "Id:" << n.GetId() << "\t Color:" << n.GetColor() << "\t Speed:" << n.GetSpeed() << "\t Price:" << n.GetPrice() << "\n";
		}
	}
	std::cout << "----------------------------------\n";
}
