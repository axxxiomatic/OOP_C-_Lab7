#include "Fio.h"
#include "Ticket.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

Ticket::Ticket()
{
	passenger.setName("Name");
	passenger.setSurname("Surname");
	arrival = "Unknown";
	price = 0;
}

Ticket::Ticket(Fio my_passenger, string my_arrival, double my_price)
{
	passenger = my_passenger;
	arrival = my_arrival;
	price = my_price;
}

Fio Ticket::getPassenger()
{
	return passenger;
}

Fio Ticket::setPassenger(Fio my_passenger)
{
	passenger = my_passenger;
	return passenger;
}

string Ticket::getArrival()
{
	return arrival;
}

string Ticket::setArrival(string my_arrival)
{
	arrival = my_arrival;
	return arrival;
}

double Ticket::getPrice()
{
	return price;
}

double Ticket::setPrice(double my_price)
{
	price = my_price;
	return price;
}

void Ticket::defineTicketFile(int lineNumber)
{
	string buffer;
	ifstream file("tickets.txt", ios::out | ios::app);
	int i;
	if (!file)
	{
		cout << "ќшибка открыти€ файла!" << endl << endl;
	}
	else
	{
		while (buffer != "eotl")
		{
			i = 0;
			for (int j = 0; j < (lineNumber + 1) * 4; j++)
			{
				getline(file, buffer);
				i = (i >= 4 || i < 0) ? 0 : i + 1;
				switch (i)
				{
				case 1:
				{
					if (buffer == "eotl")
					{
						getline(file, buffer);
					}
					passenger.setName(buffer);
					break;
				}
				case 2:
				{
					passenger.setSurname(buffer);
					break;
				}
				case 3:
				{
					arrival = buffer;
					break;
				}
				case 4:
				{
					price = stod(buffer);
					break;
				}
				default:
				{
					break;
				}
				}
			}
			break;
		}
		file.close();
	}
}

void Ticket::searchNameSurname(Fio my_passenger)
{
	if (passenger == my_passenger)
	{
		cout << *this << endl;
	}
}

Ticket Ticket::searchArrival(string my_arrival)
{
	Fio contain;
	Ticket failsafe;
	contain.setName("—оответствий ");
	contain.setSurname("не ");
	failsafe.setPassenger(contain);
	failsafe.setArrival("найдено. ");

	if (arrival == my_arrival)
	{
		cout << *this << endl;
		return *this;
	}
	else
	{
		cout << "—оответствий не найдено." << endl;
		return failsafe;
	}
}

void Ticket::priceFilter(int my_price)
{
	if (price >= my_price)
	{
		cout << *this;
	}
}

Ticket& Ticket::operator=(const Ticket& rhs)
{
	passenger = rhs.passenger;
	arrival = rhs.arrival;
	price = rhs.price;
	return *this;
}

bool Ticket::operator==(const Fio& rhs)
{
	if (passenger == rhs)
	{
		return true;
	}
	else
	{
		return false;
	}
}

ostream& operator<<(ostream& os, Ticket& my_object)
{
	cout << my_object.getPassenger().getName() << setw(10) << my_object.getPassenger().getSurname() << setw(14) << my_object.getArrival() << setw(10) << my_object.getPrice() << endl;
	return os;
}

istream& operator>>(istream& is, Ticket& my_object)
{
	Fio myPassenger;
	string myArrival;
	double myPrice;
	cout << "¬вод данных билета" << endl << endl;
	cin >> myPassenger;
	cout << "¬ведите пункт назначени€: " << endl;
	cin >> myArrival;
	cout << "¬ведите цену билета: " << endl;
	cin >> myPrice;
	my_object.setPassenger(myPassenger);
	my_object.setArrival(myArrival);
	my_object.setPrice(myPrice);
	return is;
}