#pragma once
#include "Transport.h"
#include <iostream>
#include <string>

using namespace std;

class Bus : public Transport
{
public:


	Bus() {
		cout << "????????? ????????? ????:" << endl;

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
		cout << "?????????? ??????? ???????????? ????: ";
		cin >> this->seats;
		cin.ignore();
	}

	void setMaxSeats() {
		cout << "????? ?????????? ???????????? ????: ";
		cin >> this->maxSeats;
		cin.ignore();
	}

	void setEndPoint() {
		cout << "???????? ?????: ";
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
			string("?????: ") + mark,
			string("??????: ") + model,
			string("?????????? ??????? ???????????? ????: ") + to_string(seats),
			string("????? ?????????? ???????????? ????: ") + to_string(maxSeats),
			string("???????? ?????: ") + endPoint,
		};

		return lines;
	}

	string getInfo(bool isActive = false) {
		string prefix = isActive ? "|| " : "";

		string result = prefix + string("???: \033[35m???????\033[0m\n");

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

