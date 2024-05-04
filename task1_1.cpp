#include <iostream>
#include <vector>
#include <locale.h>
#include <map>
#include <fstream>

using namespace std;


const int MAX_VERTICAL_RACK = 5;
const int  MAX_RACK = 20;
const int  MAX_SHELF = 2;
const int MAX_PPRODUCT = 10;
const int MAX_NUMBER_OF_PRODUCTS_IN_STOCKS = 6000;
int counter = 1;


struct stock // склад
{
	string NameProduct;
	int quantity;
	string zone;
	int Rack;//стеллаж
	int Vertical_Rack;// номер вертикального стеллажа
	int shelf;// полка

};

struct Adress
{
	string zone;
	int Rack;//стеллаж
	int Vertical_Rack;// номер вертикального стеллажа
	int shelf;// полка

	bool operator<(const Adress& other) const
	{
		if (zone < other.zone) return true;
		if (zone > other.zone) return false;
		if (Rack < other.Rack) return true;
		if (Rack > other.Rack) return false;
		if (Vertical_Rack < other.Vertical_Rack) return true;
		if (Vertical_Rack > other.Vertical_Rack) return false;
		return shelf < other.shelf;
	}
};

bool IsValidInputAddProduct(string zone, int quantity, int Rack, int  Verticalrack, int shelf)// проверка на ввод допустимых значений
{
	if ((zone == "A" || zone == "B" || zone == "C") && Rack <= MAX_RACK && Verticalrack <= MAX_VERTICAL_RACK && shelf <= MAX_SHELF && quantity <= MAX_PPRODUCT)
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool IsValidAddProduct(vector <stock>& VectorStock, map<Adress, int>& MapAdress, string NameProduct, string zone, int Rack, int VerticalRack, int shelf, int quantity)
{
	for (auto& item : VectorStock)
	{
		//проверка для одного адреса ячейки
		if (item.zone == zone && item.Rack == Rack && item.Vertical_Rack == VerticalRack && item.shelf == shelf)
		{
			// Если есть, то проверяем, что новое количество вместе со старым не превышает 10
			if (MapAdress[{zone, Rack, VerticalRack, shelf}] + quantity <= MAX_PPRODUCT && item.NameProduct == NameProduct)
			{
				MapAdress[{zone, Rack, VerticalRack, shelf}] += quantity;// меняем кол-во товара по адресу
				item.quantity += quantity;
				cout << "\n>>> Product added" << endl;
			}
			else if (MapAdress[{zone, Rack, VerticalRack, shelf}] + quantity <= MAX_PPRODUCT && item.NameProduct != NameProduct)
			{
				MapAdress[{zone, Rack, VerticalRack, shelf}] += quantity;// меняем кол-во товара по адресу
				VectorStock.push_back({ NameProduct,quantity,zone, Rack, VerticalRack, shelf });
				cout << "\n>>> Product added" << endl;
			}
			else
			{
				return false;
			}
		}
		// проверка для одного адреса ячейки

		else// когда другой адрес
		{
			MapAdress[{zone, Rack, VerticalRack, shelf}] += quantity;// меняем кол-во товара по адресу
			VectorStock.push_back({ NameProduct,quantity,zone, Rack, VerticalRack, shelf });
			cout << "\n>>> Product added" << endl;
		}
	}
}

void RemoveProduct(vector <stock>& VectorStock, map<Adress, int>& MapAdress)
{
	int counterForVectorStock = 0;
	// ввод данных и их проверка
	string zone = "\0", NameProduct = "\0";
	int quantity = 0, Rack = 0, VerticalRack = 0, shelf = 0;
	do
	{
		cout << "\n>>> Enter the name product and his quantity(10) \n\n<<< ";
		cin >> NameProduct >> quantity;
		cout << endl;
		cout << ">>> Enter zone(A or B or C), rack(20), vertical rack(5), shelf(2). Example(A 1711)" << endl;

		cout << "\n<<<";
		cin >> zone >> Rack >> VerticalRack >> shelf;
		if (IsValidInputAddProduct(zone, quantity, Rack, VerticalRack, shelf) == false)
		{
			cout << "\n>>> Error. Repeat input" << endl;
		}
	} while (IsValidInputAddProduct(zone, quantity, Rack, VerticalRack, shelf) != true);

	for (auto &i : VectorStock)
	{
		
		if (i.NameProduct == NameProduct && i.zone == zone && i.Rack == Rack && i.Vertical_Rack == VerticalRack && i.shelf == shelf && i.quantity == quantity)
		{
			VectorStock.erase(VectorStock.begin()+ counterForVectorStock);
			MapAdress.erase({zone, Rack, VerticalRack, shelf}); 
		}
		else if (i.NameProduct== NameProduct && quantity < i.quantity)
		{
			i.quantity -= quantity;
			MapAdress[{zone, Rack, VerticalRack, shelf}] -= quantity;
		}
		else
		{
			cout << "\n>>> Ошибка в удалении" << endl;
		}
		counterForVectorStock++;
	}
}

void AddProductInStock(vector <stock>& VectorStock, map<Adress, int>& MapAdress)
{
	// ввод данных и их проверка
	string zone = "\0", NameProduct = "\0";
	int quantity = 0, Rack = 0, VerticalRack = 0, shelf = 0;
	do
	{
		cout << "\n>>> Enter the name product and his quantity(10) \n\n<<< ";
		cin >> NameProduct >> quantity;
		cout << endl;
		cout << ">>> Enter zone(A or B or C), rack(20), vertical rack(5), shelf(2). Example(A 1711)" << endl;

		cout << "\n<<<";
		cin >> zone >> Rack >> VerticalRack >> shelf;
		if (IsValidInputAddProduct(zone, quantity, Rack, VerticalRack, shelf) == false)
		{
			cout << "\n>>> Error. Repeat input" << endl;
		}
	} while (IsValidInputAddProduct(zone, quantity, Rack, VerticalRack, shelf) != true);
	// ввод данных и их проверка
	if (counter == 1)
	{
		VectorStock.push_back({ NameProduct,quantity,zone, Rack, VerticalRack, shelf });
		MapAdress[{zone, Rack, VerticalRack, shelf}] = quantity;// добавляем ключ(структуру) и значение по этому ключу кол-во товаров
		cout << "\n>>> Product added" << endl;

	}
	//Добавление товаров на склад
	if (counter > 1 && IsValidAddProduct(VectorStock, MapAdress, NameProduct, zone, Rack, VerticalRack, shelf, quantity) == false)
	{
		cout << "\n>>> Error.Quantity on this shelf > 10. Repeat input" << endl;
	}
	// добавление товаров на склад
	counter++;
}

void INFO(vector <stock>& VectorStock)
{
	double counterProductsOnZoneA = 0, counterProductsOnZoneB = 0, counterProductsOnZoneC = 0;
	double workLoadStock = 0.0;
	for (auto it : VectorStock)
	{
		if (it.zone == "A")
		{
			counterProductsOnZoneA += it.quantity;
		}
		if (it.zone == "B")
		{
			counterProductsOnZoneB += it.quantity;
		}
		if (it.zone == "C")
		{
			counterProductsOnZoneC += it.quantity;
		}
	}
	workLoadStock = (counterProductsOnZoneA + counterProductsOnZoneB + counterProductsOnZoneC) * 100 / MAX_NUMBER_OF_PRODUCTS_IN_STOCKS;
	cout << "\n>>> Загруженность склада = " << workLoadStock <<"%" << endl;
	cout << "\n>>> Загруженность зоны А = " << (counterProductsOnZoneA * 100 )/ (MAX_RACK * MAX_PPRODUCT * MAX_VERTICAL_RACK * MAX_SHELF)<<"%" << endl;
	cout << "\n>>> Загруженность зоны B = " << (counterProductsOnZoneA * 100) / (MAX_RACK * MAX_PPRODUCT * MAX_VERTICAL_RACK * MAX_SHELF)<<"%" << endl;
	cout << "\n>>> Загруженность зоны C = " << (counterProductsOnZoneA * 100 )/ (MAX_RACK * MAX_PPRODUCT * MAX_VERTICAL_RACK * MAX_SHELF)<<"%" << endl;

	cout << "\n>>> Товары на складе" << endl;
	for (auto i : VectorStock)
	{
			cout << "\n>>> " << i.NameProduct << " " << i.zone << i.Rack << i.Vertical_Rack << i.shelf << " = " << i.quantity << endl;
		
	}
}


int main()
{
	setlocale(LC_ALL, "Rus");

	vector <stock> VectorStock; 
	map<Adress, int> MapAdress;

	char s;
	cout << "\n>>> A - ADD(добавление товара на склад) | R - REMOVE(удаление товара со склада) | I - INFO(информация о загруженности склада)" << endl;

	while (true)
	{
		cout << "\n>>> Выберите функцию" << endl;
		cout << "<<< ";
		cin >> s;
		switch (s)
		{
		case('A'):
			AddProductInStock(VectorStock, MapAdress);
			break;
		case('R'):
			RemoveProduct(VectorStock, MapAdress);
			break;
		case('I'):
			INFO(VectorStock);
			break;
		default:
			return 0;
		}
	}

	return 0;
}