/// \file
/// <summary>
/// Классы
/// </summary>
class Snake  
{ //точки
public:COORD* t;
	  //количество яблок
public:int PCount; 
	  // конструктор для класса
explicit Snake();
};
///Направление змейки
enum control { LEFT, UP, RIGHT, DOWN }; 

///
///Даные - точности: змейки, яблок, передвижение по X и Y, задержка, направление
///
class Game 
{//змейка
public:Snake viper; 
	  //яблоко
public:COORD apple; 
	  
public:int dy;//передвижение
public:int dx;//
	  //задержка
public:int pause; 
	  //направление
public:int route; 
	  //конструктор для класса
explicit Game(); 
};
