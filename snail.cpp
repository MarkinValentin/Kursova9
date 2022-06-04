/// \file
#include <iostream>  ///стандартная библиотека
#include <time.h> ///случайные числа
#include <stdio.h> ///для printf
#include <windows.h> /// для HANDLE, курсора, цвета
#include <conio.h>  ///для _kbhit
#include "Class.hpp" ///подлючаю файл с классами

using namespace std;
/// <summary>
/// Вывод цветного текста в консоль
/// </summary>
HANDLE hConsole;

///HANDLE hStdout, hStdin;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

/// 
/// Функция помещает курсор текстового экрана в точку с координатами х,у.
/// 
void GotoXY(int X, int Y)
{
	COORD coord = { X, Y };
	SetConsoleCursorPosition(hStdOut, coord);
}
/// 
/// Выбор цвета
/// 
enum ConsoleColor
{
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};
/// 
/// Функция выбора цвета
/// 
void SetColor(ConsoleColor text, ConsoleColor background)
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
///Функция разброса яблок
void PlusApple(Game& g) 
{
	int i, x, y;
	int n = g.viper.PCount;
	do
	{
		x = rand() % 56 + 3; //
		y = rand() % 19 + 3; //кординаты яблока
		for (i = 0; i < n; i++)
		{
			if (x == g.viper.t[i].X && y == g.viper.t[i].Y) // проверка на то, чтобы яблоко не появилось на змее
				break;
		}
	} while (i < n);
	g.apple.X = x; //
	g.apple.Y = y; //запоминаем позицию яблока
	SetConsoleCursorPosition(hConsole, g.apple); //переносим курсор в эту позицию
	SetConsoleTextAttribute(hConsole, 0x0c); //цвет яблока  
	printf("%c", 4); //рисуем яблоко 
}

/// Функция старта змейки: ее координат и скорости
void GameSpeed(Game& g) 
{
	system("cls");
	g.viper.PCount = 3; //начальная длина змеи в точках
	g.viper.t = new COORD[3];//создали точки
	for (int i = 0; i < 3; i++)
	{
		g.viper.t[i].X = 20 + i;
		g.viper.t[i].Y = 20;
	}
	g.dx = 1;
	g.dy = 0;
	g.pause = 100;//скорость передвижения змеи
	PlusApple(g);//появление яблока
}
/// <summary>
/// Вывод надписей
/// </summary>
void Level()
{
	GotoXY(10, 10);cout << "You will never win" << endl; //НАДПИСЬ: Вы никогда не выиграете
	GotoXY(10, 11);cout << "if you are not careful!" << endl; //НАДПИСЬ: если не будете бдительны!
}
/// <summary>
/// Вывод сообщения о задании
/// </summary>
void SnakeStart()
{
	GotoXY(10, 15);cout << "Task: Collect 50 apples!" << endl; //НАДПИСЬ: Задание: Собери 50 яблок!
}
/// <summary>
/// Вывод всей информации, отображаемой в меню справа от поля
/// </summary>
void WALL_2() 
{
	SetColor(LightBlue, Black);
	//НАДПИСЬ: Игра Змейка Маркина Валентина
	GotoXY(20, 0);cout << "Snake game by Valentin Markin" << endl;  
	//Данные
	GotoXY(64, 2);cout << "Info:" << endl; 
	//Яблок
	GotoXY(64, 3);cout << "Apples:0" << endl;
	//Длина
	GotoXY(64, 4); cout << "Lenght:3" << endl; 
	//Скорость
	GotoXY(64, 5); cout << "Speed:0" << endl; 
	//Управление
	GotoXY(64, 7); cout << "Controls:" << endl; 
	//Выход
	GotoXY(64, 8); cout << "Esc:Exit" << endl; 
	//Вверх
	GotoXY(64, 9);cout << ":Up" << endl;
	//Вниз 
	GotoXY(64, 10);cout << ":Down" << endl;  
	//Влево
	GotoXY(64, 11);cout << ":Left" << endl; 
	//Вправо
	GotoXY(64, 12);cout << ":Right" << endl; 

	{SetColor(LightMagenta, Black);
	//Рисуем верхнюю горизонтальную линию-стенку
	GotoXY(2, 2); 
	int m = 0;
	for (m = 0; m < 60; m++)
	{
		printf("*");
	}}
	{
		//Рисуем нижнюю горизонтальную линию-стенку
		GotoXY(2, 24); 
		int m = 0;
		for (m = 0; m < 60;m++)
		{
			printf("*");
		}
	}
	{	//Рисуем левую вертикальную линию-стенку
		for (int i = 3; i < 24; i++) {
			GotoXY(2, i); cout << "*" << endl;
		}
	}
	{   //Рисуем правую вертикальную линию-стенку
		for (int i = 3; i < 24; i++) {
			GotoXY(61, i); cout << "*" << endl;
		}
	}
}

enum { END, WALL, PLUS, MOVE };
///Функция которая двигает и рисует
int Move(Game& g)
{
	int& n = g.viper.PCount;
	COORD head = g.viper.t[n - 1]; //голова
	COORD tail = g.viper.t[0]; //хвост
	COORD next;
	next.X = head.X + g.dx;
	next.Y = head.Y + g.dy; //проверка следующей точки по направлению

	if (next.X < 3 || next.Y < 3 || next.X > 60 || next.Y > 23)//не уперлась ли в стену?
		return WALL;

	if (n > 4)
	{
		for (int i = 0; i < n; i++)
			if (next.X == g.viper.t[i].X && next.Y == g.viper.t[i].Y) //не наехали ли на себя?
				return END;
	}

	if (next.X == g.apple.X && next.Y == g.apple.Y)
	{
		COORD* temp = new COORD[++n];
		for (int i = 0; i < n; i++)
			temp[i] = g.viper.t[i];
		temp[n - 1] = next;
		delete[] g.viper.t;
		g.viper.t = temp;

		SetConsoleCursorPosition(hConsole, head);
		SetConsoleTextAttribute(hConsole, 0x0a); //закрашиваем яблоко, которое съели 
		printf("*");
		SetConsoleCursorPosition(hConsole, next);
		SetConsoleTextAttribute(hConsole, 0x0a);
		printf("%c", 1);
		PlusApple(g);
		return PLUS;
	}

	for (int i = 0; i < n - 1; i++)
		g.viper.t[i] = g.viper.t[i + 1];
	g.viper.t[n - 1] = next;
	SetConsoleCursorPosition(hConsole, tail);//закрашиваем хвостик
	printf(" ");

	SetConsoleCursorPosition(hConsole, head);
	SetConsoleTextAttribute(hConsole, 0x0a);//красим хвост змеи в зелений цвет
	printf("*");
	SetConsoleCursorPosition(hConsole, next);
	SetConsoleTextAttribute(hConsole, 0x0f); //красим курсор в белый цвет (голову змеи) 
	printf("%c", 1);

	return MOVE;
}
