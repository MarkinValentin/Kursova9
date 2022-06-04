/// \file
#include <iostream>  ///стандартная библиотека
#include <time.h> ///случайные числа
#include <stdio.h> ///для printf
#include <windows.h> /// для HANDLE, курсора, цвета
#include <conio.h>  ///для _kbhit
#include "Class.hpp" ///Подключения файл с классами
#include "Snail.cpp" ///Подключение файла с основными функциями

using namespace std;

/// 
/// Основная функция
/// 
int main()
{
	//получаем дескриптор консоли
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
	int key = 0, count = 0;
	Game g;
	GameSpeed(g);
	WALL_2();
	srand(time(0));
	while (key != 27)
	{
		//ждет пока нажмем
		while (!_kbhit()) 
		{
			///движение
			switch (Move(g))
			{
			// Вывод надписей справа от поля
			case PLUS:
				++count;
				g.pause -= 1;
				SetColor(LightBlue, Black);
				GotoXY(64, 2);cout << "Info:" << endl;
				GotoXY(64, 3); cout << "Apples:" << count << endl;
				GotoXY(64, 4); cout << "Lenght:" << g.viper.PCount << endl;
				GotoXY(64, 5); cout << "Speed:" << g.pause << endl;
				GotoXY(64, 7); cout << "Controls:" << endl;
				GotoXY(64, 8); cout << "Esc:exit" << endl;
				GotoXY(64, 9); cout << ":Up" << endl;
				GotoXY(64, 10);cout << ":Down" << endl;
				GotoXY(64, 11);cout << ":Left" << endl;
				GotoXY(64, 12);cout << ":Right" << endl;

				// Если выиграли
				if (count == 50)
				{
					SetColor(White, Black);
					GotoXY(24, 1); cout << "You win" << endl; //Вы выиграли
					_getch();
					return(0);
				}
				break;

			// Если проиграли 
			case END:
				GotoXY(23, 1); printf("You lose\n\n\t\t\t"); //Вы проиграли
				_getch();
				break;
			}
			//Задержка
			Sleep(g.pause); 
		}
		// работа кнопок
		key = _getch();
		// работа кнопок движения 
		if (key == 0 || key == 224)
		{
			key = _getch();

			if (key == 72 && g.route != DOWN)
			{
				g.route = UP;
				g.dx = 0;
				g.dy = -1;
			}
			else if (key == 80 && g.route != UP)
			{
				g.route = DOWN;
				g.dx = 0;
				g.dy = 1;
			}
			else if (key == 75 && g.route != RIGHT)
			{
				g.route = LEFT;
				g.dx = -1;
				g.dy = 0;
			}
			else if (key == 77 && g.route != LEFT)
			{
				g.route = RIGHT;
				g.dx = 1;
				g.dy = 0;
			}
		}
	}
}
