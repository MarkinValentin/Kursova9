#include <iostream>  //стандартная библиотека
#include <time.h> //случайные числа
#include <stdio.h> //для printf
#include <windows.h> // для HANDLE, курсора, цвета
#include <conio.h>  //для _kbhit
#include "Colour.cpp"// подключаю файл с цветами
#include "Class.cpp" //подлючаю файл с классами

using namespace std;

HANDLE hConsole;
//HANDLE hStdout, hStdin;
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

void GotoXY(int X, int Y)
{
	COORD coord = { X, Y };
	SetConsoleCursorPosition(hStdOut, coord);
}


void SetColor(ConsoleColor text, ConsoleColor background)
{
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void PlusApple(Game& g) //Функция разброса яблок
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


void GameSpeed(Game& g) // Функция старта змейки: ее координат и скорости
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
void Level()
{
	GotoXY(10, 10);cout << "You will never win" << endl; //НАДПИСЬ: Вы никогда не выиграете
	GotoXY(10, 11);cout << "if you are not careful!" << endl; //НАДПИСЬ: если не будете бдительны!
}
void SnakeStart()
{
	GotoXY(10, 15);cout << "Task: Collect 50 apples!" << endl; //НАДПИСЬ: Задание: Собери 50 яблок!
}
void WALL_2() //Вся информация, отображаемая в меню справа от поля
{
	SetColor(LightBlue, Black);
	GotoXY(20, 0);cout << "Snake game by Valentin Markin" << endl;  //НАДПИСЬ: Игра Змейка Маркина Валентина
	GotoXY(64, 2);cout << "Info:" << endl; //Данные
	GotoXY(64, 3);cout << "Apples:0" << endl; //Яблок
	GotoXY(64, 4); cout << "Lenght:3" << endl; //Длина
	GotoXY(64, 5); cout << "Speed:0" << endl; //Скорость
	GotoXY(64, 7); cout << "Controls:" << endl; //Управление
	GotoXY(64, 8); cout << "Esc:Exit" << endl; //Выход
	GotoXY(64, 9);printf("%c", 24);cout << ":Up" << endl; //Вверх
	GotoXY(64, 10);printf("%c", 25);cout << ":Down" << endl;   //Вниз
	GotoXY(64, 11);printf("%c", 27);cout << ":Left" << endl;  //Влево
	GotoXY(64, 12);printf("%c", 26);cout << ":Right" << endl; //Вправо
	{SetColor(LightMagenta, Black);

	GotoXY(2, 2); //Рисуем верхнюю горизонтальную линию-стенку
	int m = 0;
	for (m = 0; m < 60; m++)
	{
		printf("*");
	}}
	{
		GotoXY(2, 24); //Рисуем нижнюю горизонтальную линию-стенку
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

//Функция которая двигает и рисует
enum { END, WALL, PLUS, MOVE };
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
