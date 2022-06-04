class Snake  // структура змейка 
{
public:COORD* t; //точки
public:int PCount; //количество яблок
};
enum control { LEFT, UP, RIGHT, DOWN }; //направление змейки
class Game //даные-точности: змейки, яблок, передвижение по X и Y, задержка, направление
{
public:Snake viper; //змейка
public:COORD apple; //яблоко
public:int dx, dy; //передвижение
public:int pause; //задержка
public:int route; //направление
};
