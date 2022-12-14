#pragma once
#include "Transport.h"
#include <iostream>
#include <string>

using namespace std;

class Motorcycle : public Transport
{
public:

	Motorcycle() {
		cout << "????????? ????????? ????:" << endl;

		setMark();
		setModel();
		setEngineCapacity();
		setEnginePower();
		setTerrainType();
	}

	Motorcycle(string *lines) {
		this->mark = lines[1];
		this->model = lines[2];
		this->engineCapacity = stof(lines[3]);
		this->enginePower = stof(lines[4]);
		this->terrainType = lines[5];
	}

	void setEngineCapacity() {
		cout << "????? ?????????: ";
		cin >> this->engineCapacity;
		cin.ignore();
	}

	void setEnginePower() {
		cout << "???????? ?????????: ";
		cin >> this->enginePower;
		cin.ignore();
	}

	void setTerrainType() {
		cout << "??? ?????????: ";
		getline(cin, this->terrainType);
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
			setEnginePower();
			break;
		case 4:
			setTerrainType();
			break;
		default:
			break;
		}
	}

	string* getFieltsSet() {
		string *lines = new string[5] {
			string("?????: ") + mark,
			string("??????: ") + model,
			string("????? ?????????: ") + to_string(engineCapacity),
			string("???????? ?????????: ") + to_string(enginePower),
			string("??? ?????????: ") + terrainType,
		};

		return lines;
	}

	string getInfo(bool isActive = false) {
		string prefix = isActive ? "|| " : "";

		string result = prefix + string("???: \033[34m????????\033[0m\n");
		string *fieldsSet = getFieltsSet();

		for (size_t i = 0; i < 5; i++) {
			result += prefix + fieldsSet[i] + string("\n");
		}

		return result;
	}

	string serialize() {
		string result = "Motorcycle\n";
		result += mark + string("\n");
		result += model + string("\n");
		result += to_string(engineCapacity) + string("\n");
		result += to_string(enginePower) + string("\n");
		result += terrainType + string("\n");

		return result;
	}

private:
	float engineCapacity;
	float enginePower;
	string terrainType;
};

