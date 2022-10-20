#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

#include "Transport.h"
#include "Car.h"
#include "Motorcycle.h"
#include "Bus.h"

using namespace std;

class Garage
{
public:


	Garage() {
	}

	void addTransport(Transport *transport) {
		Transport **newList = new Transport*[listSize + 1];
		
		for (int i = 0; i < listSize; i++) {
			newList[i] = list[i];
		}

		newList[listSize++] = transport;

		delete []list;
		list = newList;
	}

	void removeTransport(int number) {
		Transport **newList = new Transport*[listSize - 1];

		int index = 0;
		for (int i = 0; i < listSize; i++) {
			if (i == number) continue;

			newList[index] = list[index];
			index++;
		}

		delete[] list;
		list = newList;
		listSize--;
	}

	void save() {
		ofstream out;

		out.open("data.txt");

		if (out.is_open())
		{
			for (size_t i = 0; i < listSize; i++) {
				out << list[i]->serialize() << "\n";
			}
			cout << "Сохранено!";
		} else {
			cout << "Не удалось открыть файл!";

		}
		
		out.close();

		cout << endl << "\033[35mНажмите любую клавишу чтобы вернутся в меню\033[0m" << endl;
		_getch();
	}
	
	void load() {

		string line;

		ifstream in("data.txt");

		try
		{
			if (!in.is_open()) throw std::runtime_error("Не удалось открыть файл.");

			int numberOfLines = count(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>(), '\n'); // считаем количесвто строк в файле
			if (numberOfLines <= 0 || numberOfLines % 7 != 0) throw std::runtime_error("Файл поврежден!");

			in.seekg(0);

			int lineNum = 0;
			Transport **newList = new Transport*[(int) numberOfLines / 7];
			string lines[7];

			while (getline(in, line))
			{
				string str = line;

				lines[(lineNum++) % 7] = str; 
				
				int pos = lineNum / 7 - 1;

				if (lineNum % 7 == 0) {
					if (string("Car") == lines[0]) newList[pos] = new Car(lines);
					else if (string("Bus") == lines[0]) newList[pos] = new Bus(lines);
					else if (string("Motorcycle") == lines[0]) newList[pos] = new Motorcycle(lines);
					else throw std::runtime_error("Не известный тип транспорта");
				}
			}

			delete[]list;

			list = newList;
			listSize = (int)numberOfLines / 7;

			cout << "Загружено!";
		} 
		catch (std::runtime_error err)
		{
			cout << err.what() << endl;
		}
		catch (...)
		{
			cout << "Неизвестная ошибка!";
		}

		in.close(); 

		cout << endl << "\033[35mНажмите любую клавишу чтобы вернутся в меню\033[0m" << endl;
		_getch();

	}

	Transport** getList() {
		return list;
	}

	size_t getSize() {
		return listSize;
	}

	friend const bool operator! (Garage& garage)
	{
		return (bool) garage.getSize();
	}

private:
	Transport** list = {};
	size_t listSize = 0;
};


