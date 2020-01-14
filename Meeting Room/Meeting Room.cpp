
/*
Формат ввода
В первой строке входного файла содержится одно число n (1 ≤ n ≤ 1000) — число запросов.
В следующих n строках содержатся запросы по одному в строке. Запросы бывают двух типов:


APPOINT day time duration k names1 names2… namesk
PRINT day name
day — номер дня в 2018 году (1 ≤ day ≤ 365)

time — время встречи, строка в формате HH:MM (08 ≤ HH ≤ 21, 00 ≤ MM ≤ 59)

duration — длительность встречи в минутах (15 ≤ duration ≤ 120)

k — число участников встречи (1 ≤ k ≤ 10)

namesi, name — имена участников, строки, состоящие из маленьких латинских букв (1 ≤ |name| ≤ 20). У всех коллег уникальные имена. Кроме того гарантируется, что среди участников одной встречи ни одно имя не встречается дважды.

Формат вывода
Если удалось назначить встречу (первый тип запросов), выведите OK.

Иначе выведите в первой строке FAIL, а в следующей строке через пробел список имен участников, для которых время встречи пересекается с другими встречами, в том порядке, в котором имена были даны в запросе.

Для второго типа запросов выведите для данного дня и участника список всех событий на данный момент в этот день в хронологическом порядке, по одному в строке, в формате

HH:MM duration names1 names2 … namesk

где имена участников следуют в том же порядке, что и в исходном описании встречи. Если событий в данный день для этого человека нет, то ничего выводить не нужно.

*/


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
//#include <itetator>
//#include <cstdio>
//#include <cstring>

using namespace std;

struct appoint			//структура для хранения данных об одной встрече
{
	int start;			// начало встречи
	int finish;			//конец встречи
	string names;		// число участников и их имена
};

void make_an_appointment(ifstream& file, vector<appoint> & appointments);	// назначить встречу
void print_an_appointment(ifstream& file, vector<appoint>& appointments); // вывести запрос
void print_fail(vector<appoint>appointments, appoint ap);		
int main()
{
	unsigned int n;		// (1 ≤ n ≤ 1000) — число запросов.
	string a;			// переменная для считывания вида запроса: APPOINT или PRINT
	vector<appoint> appointments; // Вектор элементов, содержащих данные о встречах
	ifstream file("Meetings.txt");		// файл с запросами

	if (!file)
		cout << "\nCant find the file";
	else
	{
		file >> n;
		for (int i = 0; i < n; i++)
		{
			file >>a;	// считываем первое слово запроса

			if (a == "APPOINT")
			{
				make_an_appointment(file, appointments);
			}
			else if (a == "PRINT")
			{
				print_an_appointment(file, appointments);
			}
			else
			{
				cout << "\nIncorrect input\n";
			}
		}
		n = 0;
		file.close();
	}
}

void make_an_appointment(ifstream& file, vector<appoint>& appointments)
{
	appoint ap;
	int num;

	//Считывание данных из файла, запись в структуру
	file >> num;
	ap.start = num * 24 * 60;// дни в минутах
	file >> num;
	ap.start += num * 60;	// прибавляем часы в минутах
	file.ignore(1);
	file >> num;
	ap.start += num;		// прибавляем минуты
	file >> num;
	ap.finish = ap.start + num;		// прибавляем продолжительность к началу встречи, получаем конец встречи
	file >> num;
	file.ignore(1);
	getline(file, ap.names);

	//Решение о вставке элемента в вектор

	if (appointments.size() == 0)
		appointments.push_back(ap);
	else
	{
		vector<appoint>::iterator it = appointments.begin();
		while (it != appointments.end())
		{
			if (ap.finish <= (*it).start)
			{
				appointments.insert(it, ap);
				return;			//it = appointments.end();
			}
			else if (ap.start >= (*it).finish)
			{
				if (it == appointments.end() - 1)
				{
					appointments.push_back(ap);
					return;		//it = appointments.end();
				}
				else
					it++;

			}
			else //if (ap.finish < (*it).finish)
				it = appointments.end();
			
		}
		print_fail(appointments, ap); /////////////////////////////////////////////////////
		return;	

	}
}


void print_fail(vector<appoint>appointments, appoint ap)
{
	cout << "FAIL\n";

	for(vector<appoint>::iterator it = appointments.begin(); it != appointments.end(); ++it)
	{
		if ((ap.start <= (*it).finish) && (ap.finish >= (*it).start))
			cout << (*it).names << " ";
		if (ap.finish <= (*it).finish)
			it = appointments.end()-1;
	}
	
	cout << endl;
}

void print_an_appointment(ifstream& file, vector<appoint>& appointments)
{
	int num;
	string name;
	int hours;
	int mins;
	int dur;
	//Считываем день и имя
	file >> num;
	file >> name;

	for (vector<appoint>::iterator it = appointments.begin(); it != appointments.end(); ++it)
	{
		if ((int)((*it).start / (24 * 60)) == num)
		{
			hours = ((*it).start % (60 * 24) )/ 60;
			mins = (*it).start % 60;
			dur = (*it).finish - (*it).start;
			if ((*it).names.find(name + " ", 0) != string::npos || (*it).names.find(name, (*it).names.size() - name.size() - 1) != string::npos) // условие позволяет не путать такие имена, как alex и alexandra, etc.
			{
				cout << hours << ":" << mins;	if (mins == 0) cout << mins;
				cout << " " << dur << " " << (*it).names << endl;
			}
		}
	}

}