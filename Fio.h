#pragma once
#include <string>
#include <iostream>
using namespace std;

class Fio
{
private:
	string name;
	string surname;
public:
	Fio();
	Fio(string my_name, string my_surname);

	string getName();
	string setName(string my_name);
	string getSurname();
	string setSurname(string my_surname);

	Fio& operator=(const Fio& rhs);
	bool operator==(const Fio& rhs);
	friend ostream& operator<<(ostream& os, Fio& my_object);
	friend istream& operator>>(istream& is, Fio& my_object);
};