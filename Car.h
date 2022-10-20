#pragma once
#include "Transport.h"
#include <iostream>
#include <string>

using namespace std;

class Car : public Transport
{
public:

	
	Car() {
		cout << "Заполните следующие поля:" << endl;

		setMark();
		setModel();
		setEngineCapacity();
		setColor();
		setTransmissionType();
	}

	Car(string *lines) {
		this->mark = lines[1];
		this->model = lines[2];
		this->engineCapacity = stof(lines[3]);
		this->color = lines[4];
		this->transmissionType = lines[5];
	}

	void setEngineCapacity() {
		cout << "Объем двигателя: ";
		cin >> this->engineCapacity;
		cin.ignore();
	}

	void setColor() {
		cout << "Цвет: ";
		getline(cin, this->color);
	}

	void setTransmissionType() {
		cout << "Тип КПП: ";
		cin >> this->transmissionType;
		cin.ignore();
	}

	string* getFieltsSet() {
		string *lines = new string[5]{
			string("Марка: ") + mark,
			string("Модель: ") + model,
			string("Объем двигателя: ") + to_string(engineCapacity),
			string("Цвет: ") + color,
			string("Тип КПП: ") + transmissionType
		};

		return lines;
	}

	string getInfo(bool isActive = false) {
		string prefix = isActive ? "|| " : "";

		string result = prefix + string("Тип: \033[31mАвтомомбиль\033[0m\n");
		string *fieldsSet = getFieltsSet();
		
		for (size_t i = 0; i < 5; i++) {
			result += prefix + fieldsSet[i] + string("\n");
		}

		return result;
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
			setEngineCapacity();
			break;
		case 3:
			setColor();
			break;
		case 4:
			setTransmissionType();
			break;
		default:
			break;
		}
	}

	string serialize() {
		string result = "Car\n";
		result += mark + string("\n");
		result += model + string("\n");
		result += to_string(engineCapacity) + string("\n");
		result += color + string("\n");
		result += transmissionType + string("\n");

		return result;
	}


private:
	float engineCapacity;
	string color;
	string transmissionType;
};

