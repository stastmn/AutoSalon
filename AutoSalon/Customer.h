#pragma once

class Customer
{
public:
	Customer(unsigned int id) :m_id(id) {}
	bool operator==(const Customer& other) const
	{
		return this->m_id == other.m_id;
	}
	unsigned int GetId() const { return m_id; }

private:
	unsigned int m_id;
};

