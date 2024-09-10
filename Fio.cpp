#include "Fio.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

Fio::Fio()
{
	name = "Имя";
	surname = "Фамилия";
}

Fio::Fio(string my_name, string my_surname)
{
	name = my_name;
	surname = my_surname;
}

string Fio::getName()
{
	return name;
}

string Fio::setName(string my_name)
{
	name = my_name;
	return name;
}

string Fio::getSurname()
{
	return surname;
}

string Fio::setSurname(string my_surname)
{
	surname = my_surname;
	return surname;
}

Fio& Fio::operator=(const Fio& rhs)
{
	name = rhs.name;
	surname = rhs.surname;
	return *this;
}

bool Fio::operator==(const Fio& rhs)
{
	if (name == rhs.name && surname == rhs.surname)
	{
		return true;
	}
	else
	{
		return false;
	}
}

ostream& operator<<(ostream& os, Fio& my_object)
{
	cout << "Сотрудник" << setw(8) << my_object.getName() << setw(8) << my_object.getSurname() << endl;
	return os;
}

istream& operator>>(istream& is, Fio& my_object)
{
	string n, s;
	cout << "Введите имя сотрудника: " << endl;
	cin >> n;
	cout << "Введите фамилию сотрудника: " << endl;
	cin >> s;
	my_object.setName(n);
	my_object.setSurname(s);
	return is;
}