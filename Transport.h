#pragma once

#include <string>

#include "utils.cpp"

using namespace std;

class Transport
{
public: 


	virtual string getInfo(bool isActive = false) = 0;
	virtual string serialize() = 0;
	virtual string* getFieltsSet() = 0;
	virtual void editFiled(int fieldNumber) = 0;

	void edit(){

		while (true)
		{
			string* commands = getFieltsSet();

			int line = menu("�������� ����: (< - ���������)", commands, 5);
			if (line < 0) return;
			editFiled(line);
		}
	}

	void setMark() {
		cout << "�����: ";
		getline(cin, this->mark);

	}

	void setModel() {
		cout << "������: ";
		getline(cin, this->model);
	}

protected:
	string mark;
	string model;
private:

};

