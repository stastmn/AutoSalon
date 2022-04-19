#pragma once
#include <string>

enum Color {
	red,
	green,
	blue
};

class Auto
{
public:
	Auto(unsigned int id, Color color, unsigned int price, unsigned int speed) : m_id(id),
		m_color(color), m_price(price), m_speed(speed) {};
	bool operator==(const Auto& other) const
	{
		return this->m_id == other.m_id;
	}
	unsigned int GetId() const { return m_id; }
	unsigned int GetPrice() const { return m_price; }
	unsigned int GetSpeed() const { return m_speed; }
	unsigned int GetColorNumber() const { return m_color; }
	std::string GetColor() const {
		if (m_color == Color::blue) return "blue";
		else if (m_color == Color::red) return "red";
		else if (m_color == Color::green) return "green";
	}

private:
	unsigned int m_id;
	Color m_color;
	unsigned int m_price;
	unsigned int m_speed;
};





enum Property {

	color,
	speed,
	price
};

enum Function {
	less,
	greater,
	equal
};

class Filter
{
public:
	Filter() = default;

	Property GetComparisonProperty() const { return m_comparisonProperty; }
	Function GetComparisonFunction() const { return m_comparisonFunction; }
	unsigned int GetComparisonValue() const { return m_comparisonValue; }

	std::string GetComparisonPropertyString() const { 
		if (m_comparisonProperty == color) return "color";
		else if (m_comparisonProperty == speed) return "speed";
		else if (m_comparisonProperty == price) return "price";
	
	}
	std::string GetComparisonFunctionString() const {
		if (m_comparisonFunction== equal) return "equal";
		else if (m_comparisonFunction== greater) return "greater";
		else if (m_comparisonFunction== less) return "less";

	}

	void SetComparisonProperty(Property p) { m_comparisonProperty = p; }
	void SetComparisonFunction(Function f) { m_comparisonFunction = f; }
	void SetComparisonValue(unsigned int v) { m_comparisonValue = v; }

	bool operator()(const Auto& a) {
		
		unsigned int value;

		if (m_comparisonProperty == color) {
			value = a.GetColorNumber();
		}
		else if (m_comparisonProperty == price) {
			value = a.GetPrice();
		}
		else if (m_comparisonProperty == speed) {
			value = a.GetSpeed();
		}

		if (m_comparisonFunction == equal) {
			return value == m_comparisonValue;
		}
		else if (m_comparisonFunction == greater) {
			return value > m_comparisonValue;
		}
		else if (m_comparisonFunction == less) {
			return value < m_comparisonValue;
		}

		return false;

	}

private:
	Property m_comparisonProperty;
	Function m_comparisonFunction;
	unsigned int m_comparisonValue;
};

