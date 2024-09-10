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
		cout << "Ошибка открытия файла." << endl << endl;
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
	cout << "ПОЕЗД" << endl;
	cout << "Заказать новый билет ......................... 1" << endl;
	cout << "Распечатать все билеты ....................... 2" << endl;
	cout << "Показать общее кол-во билетов ................ 3" << endl;
	cout << "Поиск по имени и фамилии пассажира ........... 4" << endl;
	cout << "Поиск по пункту назначения ................... 5" << endl;
	cout << "Фильтр по цене ............................... 6" << endl;
    cout << "Отменить заказ билета ........................ 7" << endl;
    cout << "Отсортировать пункт назначения по алфавиту ... 8" << endl;
	cout << "Выход из программы ........................... 9" << endl;
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
            cout << endl << " Имя" << " | " << "Фамилия" << " | " << "Пункт прибытия" << " | " << "Цена" << endl;
            for_each(tickets.begin(), tickets.end(), [](Ticket& obj)
                {
                    cout << obj;
                });
            scan = 0;
            break;
        }
        case 3:
        {
            cout << endl << "Общее количество билетов: " << tickets.size() << endl;
            scan = 0;
            break;
        }
        case 4:
        {
            Fio tempPassenger;
            cout << endl << "Введите нужные имя и фамилию: " << endl;
            cin >> tempPassenger;
            cout << endl << "Результаты поиска по записям: " << endl;
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
            cout << endl << "Введите искомый пункт назначения: " << endl;
            cin >> buffer;
            cout << endl << "Результаты поиска по записям: " << endl;
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
            cout << endl << "Введите нижний предел цены: ";
            cin >> lower;
            cout << endl << "Результаты поиска по записям: " << endl;
            for (int i = 0; i < tickets.size(); i++)
            {
                tickets[i].priceFilter(lower);
            }
            scan = 0;
            break;
        }
        case 7:
        {
            cout << "Отменён заказ билета для " << tickets[tickets.size() - 1].getPassenger().getName() << setw(1) << tickets[tickets.size() - 1].getPassenger().getSurname() << " с пунктом прибытия " << tickets[tickets.size() - 1].getArrival() << " по цене " << tickets[tickets.size() - 1].getPrice() << "." << endl;
            tickets.pop_back();
            scan = 0;
            break;
        }
        case 8:
        {
            sort(tickets.begin(), tickets.end(), compareArrival);
            cout << "Билеты отсортированы по пункту назначения. " << endl;
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
            cout << endl << "Файл записан." << endl;
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