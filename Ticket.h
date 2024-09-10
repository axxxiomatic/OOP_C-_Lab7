#pragma once
#include "Fio.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Ticket
{
private:
	Fio passenger;
	string arrival;
	double price;
public:
	Ticket();
	Ticket(Fio my_passenger, string my_arrival, double my_price);

	Fio getPassenger();
	Fio setPassenger(Fio my_passenger);
	string getArrival();
	string setArrival(string my_arrival);
	double getPrice();
	double setPrice(double my_price);

	void defineTicketFile(int lineNumber);
	void searchNameSurname(Fio my_passenger);
	Ticket searchArrival(string my_arrival);
	void priceFilter(int my_price);

	friend bool compareArrival(const Ticket& lhs, const Ticket& rhs);

	Ticket& operator=(const Ticket& rhs);
	bool operator==(const Fio& rhs);
	friend ostream& operator<<(ostream& os, Ticket& my_object);
	friend istream& operator>>(istream& is, Ticket& my_object);
};