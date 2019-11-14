#include <iostream>
#include <vector>

//Задание: Дан массив чисел. Вывести все возможные сочетания элементов массива, которые в сумме дают 10;

using namespace std;
void sum10(vector <int> a, int sum, vector <int> res, bool &fl);
void printsum10(vector <int> a);
void printv(vector <int> v);
int main()
{
	vector <int> a ;
	int n;
	// ввод n
	cin >> n;
	a.resize(n);
	// ввод массива из n  чисел
	for (int i = 0; i < n; i++)
		cin>>a[i];
	// вывод массива из n  чисел
	printv(a);
	// операция вывода всех сочетаний чисел массива, которые в сумме дают 10
	printsum10(a);

	return 0;
}

void printv(vector <int> v)
{
	cout << endl;
	for (int i = 0; i < v.size(); i++)
		cout << v[i] << " ";
}

void sum10(vector <int> a, int sum, vector <int> res, bool& fl)
{
	if (sum == 10)			// условие выхода из рекурсии (1)
	{
		printv(res);
		fl = true;
		return;
	}

	if (a.size() == 0)//|| sum > 10)	// условие выхода из рекурсии (2)
		return;
	// Сумму элементов считаем, начиная с последнего элемента
	int n = *(a.end() - 1);
	a.pop_back();
	//Прибавляем предыдущий элемент к сумме
	sum = sum + n;
	res.push_back(n);
	sum10(a, sum, res, fl);
	//Пропускаем предыдущий элемент
	sum = sum - n;
	res.pop_back();
	sum10(a, sum, res, fl);
}
void printsum10(vector <int> a)
{
 	int sum = 0;
	bool fl = false;
	vector <int> res(0);
	cout << "\nElements that sum up to 10: ";
	sum10(a, sum, res, fl);
	if (fl== false)
		cout << "elements not found.";
}

