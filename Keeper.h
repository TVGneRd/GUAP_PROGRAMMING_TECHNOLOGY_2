#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>

#include "Note.h"

using namespace std;

class Keeper
{
public:

	Keeper() {
	}

	void addNote(Note *transport) {
		Note **newList = new Note*[listSize + 1];
		
		for (int i = 0; i < listSize; i++) {
			newList[i] = list[i];
		}

		newList[listSize++] = transport;

		delete []list;
		list = newList;
	}

	void removeNote(int number) {
		Note **newList = new Note*[listSize - 1];

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

	void sort() {
		Note* temp;

		for (size_t i = 0; i < listSize - 1; i++)
		{
			for (size_t j = i + 1; j < listSize; j++)
			{
				int cmp = _stricmp(list[i]->getName().c_str(), list[j]->getName().c_str());
				if (_stricmp(list[i]->getName().c_str(), list[j]->getName().c_str()) > 0) {
					temp = list[i];
					list[i] = list[j];
					list[j] = temp;
				}
			}
		}
	}

	void save() {
		ofstream out;

		out.open("data.txt");

		if (out.is_open())
		{
			for (size_t i = 0; i < listSize; i++) {
				out << *list[i];
			}
			cout << "Сохранено!";
		} else {
			cout << "Не удалось открыть файл!";

		}
		
		out.close();

		cout << endl << "\033[35mНажмите любую клавишу чтобы вернутся в меню\033[0m" << endl;
		cin.get();
	}
	
	void load() {

		string line;

		ifstream in("data.txt");

		try
		{
			const int strNums = 6;

			if (!in.is_open()) throw std::runtime_error("Не удалось открыть файл.");

			int numberOfLines = count(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>(), '\n'); // считаем количесвто строк в файле
			if (numberOfLines <= 0 || numberOfLines % strNums != 0) throw std::runtime_error("Файл поврежден!");

			in.seekg(0);

			int lineNum = 0;
			Note **newList = new Note*[(int) numberOfLines / strNums];
			string lines[strNums];

			while (getline(in, line))
			{
				string str = line;

				lines[(lineNum++) % strNums] = str;
				
				int pos = lineNum / strNums - 1;

				if (lineNum % strNums == 0) {
					newList[pos] = new Note(lines);
				}
			}

			delete[]list;

			list = newList;
			listSize = (int)numberOfLines / strNums;

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
		cin.get();

	}

	void printHead() {
		cout << "\033[47;30m" << setw(36) << "ФИО" << setw(30) << "Телефон" << setw(16) << "День рождения" << "\033[0m" << endl;
	}

	Note** getList() {
		return list;
	}

	size_t getSize() {
		return listSize;
	}

	friend const bool operator! (Keeper& keeper)
	{
		return (bool) keeper.getSize();
	}

private:
	Note** list = {};
	size_t listSize = 0;
};


