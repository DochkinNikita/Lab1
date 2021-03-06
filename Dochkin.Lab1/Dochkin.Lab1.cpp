#include <iostream>
#include <fstream>
#include <ctime>
using namespace std;

float* MemoryForArray(int count);
int SizeFile();
void OutputArray(int size, float *arr);
void AddElements(float *&arr, int &size, int index, float number);
void AddElementsAfter(float *&arr, int &size, float check_num, float number);
void DeleteElements(float *&arr, int &size, int index);
void DeleteGivenElements(float *&arr, int &size, float number);

int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	int choice = 0, size, index;
	float number, check_num;
	size = SizeFile();
	float *arr = MemoryForArray(size);
	cout << "Кол-во элементов в массиве: " << size << endl;
	cout << "Элементы массива: ";
	OutputArray(size, arr);
	do
	{
		cout << "1) Добавить элемент в конец массива" << endl
			 << "2) Добавить элемент в начало массива" << endl
			 << "3) Добавить элемент на k-ую позицию в массиве" << endl
			 << "4) Удалить последний элемент массива" << endl
			 << "5) Удалить первый элемент массива" << endl
			 << "6) Удалить k-ый элемент массива" << endl
			 << "7) Добавить элемент массива после первого встреченного элемента с заданным значением" << endl
			 << "8) Удалить все элементы массива с заданным значением" << endl
			 << "0) Выход" << endl;
		cout << endl << "Выберите действие: ";
		cin >> choice;
		cout << endl;
		switch (choice)
		{
		case 1:
			cout << "Задайте число, которое будет добавляться: ";
			cin >> number;
			cout << endl;
			AddElements(arr, size, size, number);
			break;
		case 2:
			cout << "Задайте число, которое будет добавляться: ";
			cin >> number;
			cout << endl;
			AddElements(arr, size, 0, number);
			break;
		case 3:
			cout << "Задайте число, которое будет добавляться: ";
			cin >> number;
			cout << "Задайте индекс изменяемого элемента: ";
			cin >> index;
			cout << endl;
			AddElements(arr, size, index, number);
			break;
		case 4:
			DeleteElements(arr, size, size - 1);
			break;
		case 5:
			DeleteElements(arr, size, 0);
			break;
		case 6:
			cout << "Задайте индекс удаляемого элемента: ";
			cin >> index;
			cout << endl;
			DeleteElements(arr, size, index);
			break;
		case 7:
			cout << "Задайте число, которое будет добавляться: ";
			cin >> number;
			cout << "Задайте число после которого будет добавлено другое число: ";
			cin >> check_num;
			cout << endl;
			AddElementsAfter(arr, size, check_num, number);
			break;
		case 8:
			cout << "Задайте число, которое нужно удалить: ";
			cin >> number;
			cout << endl;
			DeleteGivenElements(arr, size, number);
			break;
		default:
			if (choice != 0)
			{
				cout << "Такого действия нет " << endl << endl;
			}
			break;
		}
	} while (choice != 0);
	delete[] arr;
	arr = nullptr;
	return 0;
}

float *MemoryForArray(int size)
{
	float* arr = new float[size];
	ifstream f("Array.txt");
	for (int i = 0; i < size; i++)
	{
		f >> arr[i];
	}
	f.close();
	return arr;
}

void AddElements(float*& arr, int& size, int index, float number)
{
	bool exit = 0;
	if (index < 0 || index > size + 1)
	{
		exit = 0;
	}
	else
	{
		float* buff = new float[size + 1];
		for (int i = 0; i < index; i++)
		{
			buff[i] = arr[i];
		}
		buff[index] = number;
		for (int i = index + 1; i < size + 1; i++)
		{
			buff[i] = arr[i - 1];
		}
		exit = 1;
		delete[] arr;
		arr = buff;
		size ++;
	}
	if (exit == 0)
	{
		cout << "Ошибка: Вы вышли за пределы массива " << endl << endl;
	}
	else
	{
		OutputArray(size, arr);
		cout << "Действие выполнено" << endl << endl;
	}
}

void DeleteElements(float*& arr, int& size, int index)
{
	bool exit = 0;
	if (index < 0 || index >= size)
	{
		exit = 0;
	}
	else
	{
		float* buff = new float[size - 1];
		for (int i = 0; i < index; i++)
		{
			buff[i] = arr[i];
		}
		for (int i = index; i < size; i++)
		{
			buff[i] = arr[i + 1];
		}
		exit = 1;
		delete[] arr;
		arr = buff;
		size --;
	}
	if (exit == 0)
	{
		cout << "Ошибка: Вы вышли за пределы массива" << endl << endl;
	}
	else
	{
		OutputArray(size, arr);
		cout << "Действие выполнено" << endl << endl;
	}
}

void AddElementsAfter(float*& arr, int& size, float check_num, float number)
{
	bool exit = 0;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == check_num)
		{
			int index = 0;
			float* buff = new float[size + 1];
			for (int i = 0, j = 0; i < size; i++, j++)
			{
				buff[j] = arr[i];
				if (arr[i] == check_num)
				{
					buff[j + 1] = number;
					break;
				}
				index++;
			}
			for (; index < size; index++)
			{
				buff[index + 2] = arr[index + 1];
			}
			exit = 1;
			delete[] arr;
			arr = buff;
			size ++;
			break;
		}
	}
	if (exit == 0)
	{
		cout << "Такой цифры в массиве нет" << endl << endl;
	}
	else
	{
		OutputArray(size, arr);
		cout << "Действие выполнено" << endl << endl;
	}
}

void DeleteGivenElements(float *&arr, int &size, float number)
{
	int count = 0;
	bool exit = 0;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == number)
		{
			float* buff = new float[size];
			for (int i = 0, j = 0; i < size; i++, j++)
			{
				buff[j] = arr[i];
				if (arr[i] == number)
				{
					while (arr[i] == arr[i + 1])
					{
						i++;
						count++;
					}
					buff[j] = arr[i + 1];
					count++;
					i++;
				}
			}
			size -= count;
			exit = 1;
			delete[] arr;
			arr = buff;
			break;
		}
	}
	if (exit == 0)
	{
		cout << "Такой цифры в массиве нет " << endl << endl;
	}
	else
	{
		OutputArray(size, arr);
		cout << "Действие выполнено " << endl << endl;
	}
}

int SizeFile()
{
	ifstream f("Array.txt");
	float check;
	int count = 0;
	while (f >> check)
	{
		count++;
	}
	if (count == 0)
	{
		cout << "Файл пуст или отсутсвует " << endl;
		exit(0);
	}
	else return count;
}

void OutputArray(int size, float *arr)
{
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl << endl;
}