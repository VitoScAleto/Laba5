#include <iostream>
#include <vector>
#include <map>
#include <vector>
#include <locale.h>
#include <random>
#include <algorithm>

using namespace std;

struct QUEUE 
{
	char Tallon;
	int NumberTallon;
	int Time;
}; 


int GetRandomNumber(int min, int max)
{
	random_device rd;//random_device, который является источником недетерминированных случайных чисел.
	//Затем мы используем это устройство для заполнения генератора std::minstd_rand. Затем функция генератора() используется для генерации случайного числа
	minstd_rand generator(rd());

	uniform_int_distribution<int> distribution(min, max);// функция destribition для задания диапозона значений
	int random_number = distribution(generator);
	return random_number;
}



int main()
{
	setlocale(LC_ALL, "Rus");

	map <int, vector<QUEUE>> MapQueue;

	int QuantityWindows = 0;
	string Command = "\0";
	int Time = 0;
	int i = 0, i1 = 1;
	

	cout << ">>> Введите кол-во окон\n<<<";
	cin >> QuantityWindows;
	
	while (true)// пока не введем destribute
	{
		cout << "<<<";
		cin >> Command;
		if (Command == "DESTRIBUTE") break;
		cin >> Time;
		// для первоначального заполнения(заполянем все окна по порядку)
		if (Command == "ENQUEUE" && i < QuantityWindows)
		{
			MapQueue[i] = { { 'T',GetRandomNumber(100, 999),Time} };
			i++;
		}
		// для перовначального заполнения
		// для последующего заполения
		if (Command == "ENQUEUE")
		{
			
		}
		//для последующего заполнения
	}




	for (auto i : MapQueue)
	{
		cout << ">>> Окно " << i1<<" : ";
		for (auto& item : i.second)
		{
			cout << item.Tallon << item.NumberTallon << endl;
		}
		i1++;
	}
}