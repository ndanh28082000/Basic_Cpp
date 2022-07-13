#include "Mylibrary.h"
#include <string>
#include <iostream>

using namespace std;

bool Isunsignedinterger(string str) {
	size_t length = str.length();
	for (size_t i = 0; i < length; i++)
	{
		if (!isdigit(str[i])) return false;
	}
	return true;
}

void Printarray(unsigned int arr[], unsigned int size_array) {
	for (size_t i = 0; i < size_array; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}

bool YNQuestion() {
	string temp = "";
	while (1)
	{
		cout << "XIN MOI HAY NHAP LUA CHON CUA BAN(Y/N): ";
		getline(cin, temp);
		if (temp.length() == 1) {
			switch (temp[0])
			{
			case 'Y':
			case'y':
				return true;
			case 'N':
			case'n':
				return false;
			}
		}
		cout << "KHONG HOP LE, XIN VUI LONG NHAP LAI!";
	}
}

void Selectionsort(unsigned int* arr, unsigned int size_array) {
	size_t i_min;
	for (size_t i = 0; i < size_array - 1; i++)
	{
		i_min = i;
		for (size_t j = i + 1; j < size_array; j++)
		{
			if (arr[j] < arr[i_min])
				i_min = j;
		}
		if (i_min != i)
			swap(arr[i_min], arr[i]);
	}
}

void Bubblesort(unsigned int* arr, unsigned int size_array) {
	for (size_t i = 0; i < size_array - 1; i++)
	{
		for (size_t j = size_array - 1; j > i; j--)
		{
			if (arr[j] < arr[j - 1]) {
				swap(arr[j], arr[j - 1]);
			}
		}
	}
}