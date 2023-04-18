#include <iostream>
#include <fstream>
#include "tuition.cpp"
using namespace std;

int main()
{
    tuition tui;
	tui.list = tui.createHead();
	tui.readInfoFromFile("classinfo.txt", tui.list);
	while (1)
	{
		tui.makeMenu();
		tui.keyIn();
		system("pause");
		system("cls");
	}

}
