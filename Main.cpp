#include "Fio.h"
#include "Ticket.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <Windows.h>
using namespace std;

void WriteFile(Ticket my_object)
{
    ofstream out_file("tickets.txt", std::ofstream::app);
    out_file << my_object.getPassenger().getName() << endl << my_object.getPassenger().getSurname() << endl << my_object.getArrival() << endl << my_object.getPrice() << endl << "eotl" << endl;
    out_file.close();
}

int FileLinesCounter(string fname)
{
	int number = 0;
	string check;
	ifstream file_in(fname);
	if (!file_in)
	{
		cout << "������ �������� �����." << endl << endl;
		return 1;
	}
	else
	{
		while (getline(file_in, check))
		{
			if (check != "end")
			{
				++number;
				check = "a";
			}
			if (check == "end") break;
		}
		file_in.close();
		return number;
	}
}

void PrintMenu()
{
	cout << "�����" << endl;
	cout << "�������� ����� ����� ......................... 1" << endl;
	cout << "����������� ��� ������ ....................... 2" << endl;
	cout << "�������� ����� ���-�� ������� ................ 3" << endl;
	cout << "����� �� ����� � ������� ��������� ........... 4" << endl;
	cout << "����� �� ������ ���������� ................... 5" << endl;
	cout << "������ �� ���� ............................... 6" << endl;
    cout << "�������� ����� ������ ........................ 7" << endl;
    cout << "������������� ����� ���������� �� �������� ... 8" << endl;
	cout << "����� �� ��������� ........................... 9" << endl;
}

bool compareArrival(const Ticket& lhs, const Ticket& rhs)
{
    return lhs.arrival < rhs.arrival;
};

int main()
{
    setlocale(LC_ALL, "Russian");
    bool quit = 0;
    int scan = 0;
    int linesNumber = FileLinesCounter("tickets.txt") / 5;
    vector<Ticket> tickets(linesNumber);

    for (int i = 0; i < tickets.size(); i++)
    {
        tickets[i].defineTicketFile(i);
    }
    while (quit == 0)
        switch (scan)
        {
        case 1:
        {
            Ticket tempTicket;
            cin >> tempTicket;
            tickets.push_back(tempTicket);
            scan = 0;
            break;
        }
        case 2:
        {
            cout << endl << " ���" << " | " << "�������" << " | " << "����� ��������" << " | " << "����" << endl;
            for_each(tickets.begin(), tickets.end(), [](Ticket& obj)
                {
                    cout << obj;
                });
            scan = 0;
            break;
        }
        case 3:
        {
            cout << endl << "����� ���������� �������: " << tickets.size() << endl;
            scan = 0;
            break;
        }
        case 4:
        {
            Fio tempPassenger;
            cout << endl << "������� ������ ��� � �������: " << endl;
            cin >> tempPassenger;
            cout << endl << "���������� ������ �� �������: " << endl;
            //for (int i = 0; i < tickets.size(); i++)
            //foreach(tickets.begin(), tickets.end())
            //{
            //    tickets[i].searchNameSurname(tempPassenger);
            //}
      
            //for (auto p = tickets.begin(); p != tickets.end(); p++) 
            //p->searchNameSurname(tempPassenger);
            for (auto p : tickets)
                p.searchNameSurname(tempPassenger);
            scan = 0;
            break;
        }
        case 5:
        {
            string buffer;
            vector<Ticket> results(tickets.size());
            cout << endl << "������� ������� ����� ����������: " << endl;
            cin >> buffer;
            cout << endl << "���������� ������ �� �������: " << endl;
            for (int i = 0; i < tickets.size(); i++)
            {
               results[i] = tickets[i].searchArrival(buffer);
            }
            scan = 0;
            results.clear();
            break;
        }
        case 6:
        {
            int lower;
            cout << endl << "������� ������ ������ ����: ";
            cin >> lower;
            cout << endl << "���������� ������ �� �������: " << endl;
            for (int i = 0; i < tickets.size(); i++)
            {
                tickets[i].priceFilter(lower);
            }
            scan = 0;
            break;
        }
        case 7:
        {
            cout << "������ ����� ������ ��� " << tickets[tickets.size() - 1].getPassenger().getName() << setw(1) << tickets[tickets.size() - 1].getPassenger().getSurname() << " � ������� �������� " << tickets[tickets.size() - 1].getArrival() << " �� ���� " << tickets[tickets.size() - 1].getPrice() << "." << endl;
            tickets.pop_back();
            scan = 0;
            break;
        }
        case 8:
        {
            sort(tickets.begin(), tickets.end(), compareArrival);
            cout << "������ ������������� �� ������ ����������. " << endl;
            scan = 0;
            break;
        }
        case 9:
        {
            remove("tickets.txt");
            for (int i = 0; i < tickets.size(); i++)
            {
                WriteFile(tickets[i]);
            }
            ofstream out_file("tickets.txt", std::ofstream::app);
            out_file << "end" << endl;
            out_file.close();
            quit = 1;
            cout << endl << "���� �������." << endl;
            tickets.clear();
            scan = 0;
            break;
        }
        default:
        {
            scan = 0;
            cout << endl;
            PrintMenu();
            cin.clear();
            cin >> scan;
            break;
        }
        }
    system("pause");
    return 0;
}