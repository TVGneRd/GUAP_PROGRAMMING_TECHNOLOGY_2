#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include <fstream>

using namespace std;

bool isVowel(char needle) {
	char vowelLetters[6] = { 'a','o','u','i','e','y' };

	for (char c : vowelLetters) {
		if (c == needle) return true;
	}

	return false;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	ifstream in("data.txt");

	if (!in.is_open()) {
		cout << "Не удалось открыть файл.";
		return 0;
	}

	char word;
	char prevWord = EOF;

	while ((word = in.get()) && word != EOF) {
		
		if (isVowel(word) && word >= 'a' && word <= 'z' && (prevWord == ' ' || prevWord == '\n' || prevWord == '\t')) {
			cout << (char) (word + 'A' - 'a');
		} else {
			cout << word;
		}

		prevWord = word;
	}
	
	in.close();

	return 0;
}

