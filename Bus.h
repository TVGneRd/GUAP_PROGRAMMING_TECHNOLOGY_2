#pragma once
#include "Transport.h"
#include <iostream>
#include <string>

using namespace std;

class Bus : public Transport
{
public:


	Bus() {
		cout << "Заполните следующие поля:" << endl;

		setMark();
		setModel();
		setSeats();
		setMaxSeats();
		setEndPoint();
	}

	Bus(string *lines) {
		this->mark = lines[1];
		this->model = lines[2];
		this->seats = stoi(lines[3]);
		this->maxSeats = stoi(lines[4]);
		this->endPoint = lines[5];
	}

	void setSeats() {
		cout << "Количество сидячих пассажирских мест: ";
		cin >> this->seats;
		cin.ignore();
	}

	void setMaxSeats() {
		cout << "Общее количество пассажирских мест: ";
		cin >> this->maxSeats;
		cin.ignore();
	}

	void setEndPoint() {
		cout << "Конечный пункт: ";
		getline(cin, this->endPoint);
	}

	void editFiled(int fieldNumber) {
		switch (fieldNumber)
		{
		case 0:
			setMark();
			break;
		case 1:
			setModel();
			break;
		case 2:
			setSeats();
			break;
		case 3:
			setMaxSeats();
			break;
		case 4:
			setEndPoint();
			break;
		default:
			break;
		}
	}

	string* getFieltsSet() {
		string *lines = new string[5]{
			string("Марка: ") + mark,
			string("Модель: ") + model,
			string("Количество сидячих пассажирских мест: ") + to_string(seats),
			string("Общее количество пассажирских мест: ") + to_string(maxSeats),
			string("Конечный пункт: ") + endPoint,
		};

		return lines;
	}

	string getInfo(bool isActive = false) {
		string prefix = isActive ? "|| " : "";

		string result = prefix + string("Тип: \033[35mАвтобус\033[0m\n");

		string *fieldsSet = getFieltsSet();

		for (size_t i = 0; i < 5; i++) {
			result += prefix + fieldsSet[i] + string("\n");
		}

		return result;
	}


	string serialize() {
		string result = "Bus\n";
		result += mark + string("\n");
		result += model + string("\n");
		result += to_string(seats) + string("\n");
		result += to_string(maxSeats) + string("\n");
		result += endPoint + string("\n");

		return result;
	}

private:
	int seats;
	int maxSeats;
	string endPoint;
};

