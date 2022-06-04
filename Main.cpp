#include <iostream>  //стандартная библиотека
#include <time.h> //случайные числа
#include <stdio.h> //для printf
#include <windows.h> // для HANDLE, курсора, цвета
#include <conio.h>  //для _kbhit
#include "Class.hpp" //подлючаю файл с классами
#include "snail.cpp"

using namespace std;
int main()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //получаем дескриптор консоли
	int key = 0, count = 0;
	bool Pause = false;
	Game g;
	GameSpeed(g);
	WALL_2();
	srand(time(0));
	bool pause = false;
	while (key != 27)
	{
		while (!_kbhit()) //ждет пока нажмем
		{
			if (Pause == true)
			{
				Sleep(1);
				continue;
			}

			switch (Move(g))//движение
			{

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
				GotoXY(64, 9);printf("%c", 24);cout << ":Up" << endl;
				GotoXY(64, 10);printf("%c", 25);cout << ":Down" << endl;
				GotoXY(64, 11);printf("%c", 27);cout << ":Left" << endl;
				GotoXY(64, 12);printf("%c", 26);cout << ":Right" << endl;
				if (count == 50)
				{
					SetColor(White, Black);
					GotoXY(24, 1); cout << "You win" << endl; //Вы выиграли
					_getch();
					return(0);
				}
				break;

			case WALL:

			case END:
				GotoXY(23, 1); printf("You lose\n\n\t\t\t"); //Вы проиграли
				_getch();
				break;
			}

			Sleep(g.pause); //Задержка
		}
		key = _getch();
		//работа кнопок
		if (key == 'P' || key == 'p')
			Pause = !Pause;
		else if (key == 'S' || key == 's')
			SnakeStart();
		else if (key == 'L' || key == 'l')
			Level();
		//работа кнопок движения 
		else if (key == 0 || key == 224)
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
