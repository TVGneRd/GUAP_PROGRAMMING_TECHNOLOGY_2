#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>

#include "utils.cpp"
#include "Keeper.h"
#include "Note.h"

using namespace std;

Keeper keeper;

int selectTransport(string status) {

	string *commands = new string[keeper.getSize()];

	keeper.printHead();

	for (size_t i = 0; i < keeper.getSize(); i++) {
		commands[i] = keeper.getList()[i]->toString();
	}

	int activeLine = 0;

	while (true)
	{
		system("@cls||clear");

		cout << status << endl;

		keeper.sort();

		for (size_t i = 0; i < keeper.getSize(); i++)
		{
			if (activeLine == i) cout << "\033[36m";
			cout << keeper.getList()[i]->toString();
			cout << "\033[0m" << endl;
		}

		int command = _getch();
		if (command == 224) command = _getch();

		switch (command)
		{
		case ARROW_DOWN:
			activeLine = (activeLine >= keeper.getSize() - 1) ? 0 : activeLine + 1;
			break;

		case ARROW_UP:
			activeLine = (activeLine == 0) ? keeper.getSize() - 1 : activeLine - 1;
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
	if (!keeper) return true; // используем перегрузку оператора !

	cout << "\033[34mЗаметок еще нет\033[0m" << endl;
	cout << endl << "\033[35mНажмите любую клавишу чтобы вернутся в меню\033[0m" << endl;
	cin.get();
		
	return false;
}

void showLoop() {
	if (!check()) return;

	keeper.sort();
	keeper.printHead();

	for (size_t i = 0; i < keeper.getSize(); i++) {
		cout << keeper.getList()[i]->toString() << endl;
	}

	cout << endl << "\033[35mНажмите любую клавишу чтобы вернутся в меню\033[0m" << endl;

	cin.get();
}

void searchLoop() {
	if (!check()) return;

	int counter = 0;
	int mounth;

	cout << "Введите месяц: ";
	cin >> mounth;
	cin.get();

	keeper.sort();
	keeper.printHead();

	for (size_t i = 0; i < keeper.getSize(); i++) {
		int currentMounth = keeper.getList()[i]->getBithday()[1];
		if (currentMounth == mounth) {
			cout << keeper.getList()[i]->toString() << endl;
			counter++;
		}
	}

	if (!counter) {
		system("@cls||clear");
		cout << endl << "\033[31mНичего не найдено =(\033[0m" << endl;

	}

	cout << endl << "\033[35mНажмите любую клавишу чтобы вернутся в меню\033[0m" << endl;

	cin.get();
}

void editLoop() {
	if (!check()) return;

	int number = selectTransport("Выберите объект (< - назад):");
	if (number < 0) return;
	keeper.getList()[number]->edit();
}

void removeLoop() {
	if (!check()) return;

	int number = selectTransport("Выберите объект (< - назад):");
	if (number < 0) return;
	keeper.removeNote(number);
}

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string commands[] = {
		"Показать заметки",
		"Добавить заметку",
		"Найти заметку",
		"Редактировать заметку",
		"Удалить заметку",
		"\033[33mСохранить данные\033[0m",
		"\033[32mЗагрузить данные\033[0m",
		"\033[31mВыход\033[0m",
	};

	while (true) {
		string status = string("У вас: ") + to_string(keeper.getSize()) + string(" заметок.\nМеню:");

		int command = menu(status, commands, sizeof(commands) / sizeof(string));

		switch (command)
		{
		
		case 0:
			showLoop();
			break;

		case 1:
			keeper.addNote(new Note());
			break;
		case 2:
			searchLoop();
			break;
		case 3:
			editLoop();
			break;

		case 4:
			removeLoop();
			break;

		case 5:
			if (!check()) continue;
			keeper.save();
			break;
		case 6:
			keeper.load();
			break;
		case -1:
			break;
		default:
			return 0;
			break;
		}
	}

}

