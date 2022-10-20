#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>

#include "utils.cpp"
#include "Garage.h"
#include "Car.h"
#include "Motorcycle.h"
#include "Bus.h"

using namespace std;

Garage garage;

int selectTransport(string status) {

	string *commands = new string[garage.getSize()];

	for (size_t i = 0; i < garage.getSize(); i++) {
		commands[i] = garage.getList()[i]->getInfo();
	}

	int activeLine = 0;

	while (true)
	{
		system("@cls||clear");

		cout << status << endl;

		for (size_t i = 0; i < garage.getSize(); i++)
		{
			cout << garage.getList()[i]->getInfo(activeLine == i);
			cout << endl;
		}

		int command = _getch();
		if (command == 224) command = _getch();

		switch (command)
		{
		case ARROW_DOWN:
			activeLine = (activeLine >= garage.getSize() - 1) ? 0 : activeLine + 1;
			break;

		case ARROW_UP:
			activeLine = (activeLine == 0) ? garage.getSize() - 1 : activeLine - 1;
			break;

		case ARROW_LEFT:
			system("@cls||clear");

			return -1;

		case ARROW_RIGTH:
			system("@cls||clear");

			return activeLine;

		case ENTER:
			system("@cls||clear");
			return activeLine;
		}
	}
}

bool check() {
	if (!garage) return true; // используем перегрузку оператора !

	cout << "\033[34mГараж пуст!\033[0m" << endl;
	cout << endl << "\033[35mНажмите любую клавишу чтобы вернутся в меню\033[0m" << endl;
	_getch();
		
	return false;
}

void showLoop() {
	if (!check()) return;

	for (size_t i = 0; i < garage.getSize(); i++) {
		cout << garage.getList()[i]->getInfo() << endl;
	}

	cout << endl << "\033[35mНажмите любую клавишу чтобы вернутся в меню\033[0m" << endl;

	_getch();
}

void addLoop() {

	string commands[] = {
		"Автомобиль",
		"Мотоцикл",
		"Автобус",
	};

	int command = menu("Выберите тип (< - назад):", commands, sizeof(commands) / sizeof(string));

	switch (command)
	{
	case 0:
		garage.addTransport(new Car());
		break;
	case 1:
		garage.addTransport(new Motorcycle());
		break;
	case 2:
		garage.addTransport(new Bus());
		break;
	default:
		return;
		break;
	}
}

void editLoop() {
	if (!check()) return;

	int number = selectTransport("Выберите объект (< - назад):");
	if (number < 0) return;
	garage.getList()[number]->edit();
}

void removeLoop() {
	if (!check()) return;

	int number = selectTransport("Выберите объект (< - назад):");
	if (number < 0) return;
	garage.removeTransport(number);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string commands[] = {
		"Показать транспорт",
		"Добавить транспорт",
		"Редактировать транспорт",
		"Удалить транспорт",
		"\033[33mСохранить данные\033[0m",
		"\033[32mЗагрузить данные\033[0m",
		"\033[31mВыход\033[0m",
	};

	while (true) {
		string status = string("В гараже: ") + to_string(garage.getSize()) + string(" единиц техники\nМеню:");

		int command = menu(status, commands, sizeof(commands) / sizeof(string));

		switch (command)
		{
		
		case 0:
			showLoop();
			break;

		case 1:
			addLoop();
			break;

		case 2:
			editLoop();
			break;

		case 3:
			removeLoop();
			break;

		case 4:
			if (!check()) continue;
			garage.save();
			break;
		case 5:
			garage.load();
			break;
		case -1:
			break;
		default:
			return 0;
			break;
		}
	}

}

