#include <iostream>
#include <vector>
#include <locale.h>

using namespace std;


const int MAX_VERTICAL_RACK = 5;
const int  MAX_RACK = 20;
const int  MAX_SHELF =  2;
const int MAX_PPRODUCT = 10;
const int MAX_NUMBER_OF_PRODUCTS_IN_STOCKS = 6000;


struct stock // склад
{
	string NameProduct;
	int quantity;
	string zone;
	int Rack;//стеллаж
	int Vertical_Rack;// номер вертикального стеллажа
	int shelf;// полка

};

bool IsValidInputAddProduct(string zone,int quantity, int Rack, int  Verticalrack, int shelf)// проверка на ввод допустимых значений
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

bool IsValidAddProduct(vector <stock>& VectorZoneA, vector <stock>& VectorZoneB, vector <stock>& VectorZoneC, string NameProduct,string zone,int Rack,int VerticalRack,int shelf, int quantity)
{
	
	for (auto& item : VectorZoneA)
	{
		if (item.zone == zone && item.Rack == Rack && item.Vertical_Rack == VerticalRack && item.shelf == shelf)
		{
			// Если есть, то проверяем, что новое количество вместе со старым не превышает 10
			if (item.quantity + quantity <= MAX_PPRODUCT)
			{
				item.quantity += quantity;
			}
			else
			{
				return false;
			}
		}
	}

	for (auto& item : VectorZoneB)
	{
		if (item.zone == zone && item.Rack == Rack && item.Vertical_Rack == VerticalRack && item.shelf == shelf)
		{
			if (item.quantity + quantity <= MAX_PPRODUCT)
			{
				item.quantity += quantity;
			}
			else
			{
				return false;
			}
		}
	}

	for (auto& item : VectorZoneC)
	{
		if (item.zone == zone && item.Rack == Rack && item.Vertical_Rack == VerticalRack && item.shelf == shelf)
		{
			if (item.quantity + quantity <= MAX_PPRODUCT)
			{
				item.quantity += quantity;
			}
			else
			{
				return false;
			}
		}
	}

}



void AddProductInStock(vector <stock>& VectorZoneA,vector <stock> &VectorZoneB,vector <stock> &VectorZoneC)
{
	// ввод данных и их проверка
	string zone = "\0", NameProduct = "\0";
	int quantity= 0, Rack = 0, VerticalRack = 0, shelf = 0;

	do
	{
		cout << "\n>>> Enter the name product and his quantity(10) \n\n<<< ";
		cin >> NameProduct >> quantity;
		cout << endl;
		cout << ">>> Enter zone(A or B or C), rack(20), vertical rack(5), shelf(2). Example(A 1711)" << endl;

		cout << "\n<<<";
		cin >> zone  >> Rack >> VerticalRack >> shelf;
		if (IsValidInputAddProduct(zone, quantity,Rack, VerticalRack, shelf) == false)
		{
			cout << "\n>>> Error. Repeat input" << endl;
		}
		else
		{
			cout << "\n>>> Product added\n" << endl;
		}
	} while (IsValidInputAddProduct(zone, quantity,Rack, VerticalRack, shelf) != true);
	// ввод данных и их проверка
	
	//Добавление товаров на склад
	if (zone == "A" && IsValidAddProduct(VectorZoneA,VectorZoneB, VectorZoneC,NameProduct,  zone, Rack,  VerticalRack,  shelf, quantity) == false)
	{
		VectorZoneA.push_back({ NameProduct,quantity,zone, Rack, VerticalRack, shelf });
	}
	if (zone == "B" && IsValidAddProduct(VectorZoneA, VectorZoneB, VectorZoneC, NameProduct, zone, Rack, VerticalRack, shelf, quantity) == false)
	{
		VectorZoneB.push_back({ NameProduct,quantity,zone, Rack, VerticalRack, shelf });
	}
	if (zone == "C" && IsValidAddProduct(VectorZoneA, VectorZoneB, VectorZoneC, NameProduct, zone, Rack, VerticalRack, shelf, quantity) == false)
	{
		VectorZoneC.push_back({ NameProduct,quantity,zone, Rack, VerticalRack, shelf });
	}
	// добавление товаров на склад
}



int main()
{
	setlocale(LC_ALL, "Rus");

	vector <stock> VectorZoneA;
	vector <stock> VectorZoneB;
	vector <stock> VectorZoneC;
	int i = 0;
	while (true)
	{
		
		AddProductInStock(VectorZoneA, VectorZoneB, VectorZoneC);
		for (auto i : VectorZoneA)
		{
			cout <<"\n" << i.NameProduct << " " << i.zone << i.Rack << i.Vertical_Rack << i.shelf << " = " << i.quantity << endl;
		}
		for (auto i : VectorZoneB)
		{
			cout <<"\n" << i.NameProduct << " " << i.zone << i.Rack << i.Vertical_Rack << i.shelf << " = " << i.quantity << endl;
		}for (auto i : VectorZoneC)
		{
			cout <<"\n" << i.NameProduct << " " << i.zone << i.Rack << i.Vertical_Rack << i.shelf << " = " << i.quantity << endl;
		}
	}
	


	return 0;
}