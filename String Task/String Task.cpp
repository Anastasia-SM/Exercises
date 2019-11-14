
#include <iostream>
#include <string>
using namespace std;

// На вводе строка "AAABBDCCCFFFFFFFFFFFWWKKDA"
// Вывести строку в формате "A3B2DC3F11W2K2DA" - вывод символов с подсчетом количества идущих подряд одинаковых символов
int main()
{

	
	string s = "AAABBDCCCFFFFFFFFFFFWWKKDA";
	string sub;
	//getline(cin, s);
	int i = 0, i0 = 0, k = 1;

	while (i < s.length())
	{

		while (s[i] == s[i + 1])
			i++;
		k = i - i0 + 1;
		if (k > 1)
		{
			sub = s.substr(i + 1);
			s.resize(i0 + 1);
			s += to_string(k) + sub;
			//cout << s << endl;
			i0++;
			i0 += k / 10;
		}
		i0++;

		i = i0;
	}
	cout << s << endl;
	return 0;
}
