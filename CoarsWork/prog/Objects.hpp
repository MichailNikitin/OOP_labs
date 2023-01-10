#ifndef OBJECTS_H
#define OBJECTS_H
#include <vector>
#include <string>
#include "graphics.h"

class Robot;
class Robots;
class Object;
class Cell;
class Fild;
class Сommand;
class Programm;
class Task;

std::vector <Robot *> Robots; // глобальный вектор с роботами
std::vector <Programm *> Programms; // глобальный вектор с программами

class Robot {
   int i, j; //текущие  координаты робота;
   int direction[2]; // текущее направление {0, 1}/{1, 0}/{0, -1}/{-1, 0}
   int color; // текущий цвет
   bool allow_change_direction; // разрешено изменять направление?
   bool allow_change_cordinat; // разрешено изменять координаты?
   Robot(bool, bool); //allow_change_direction, allow_change_cordinat
public:
   void set_cordinat(int, int); // установить координаты
   void set_direction(int); // установить направление
   void set_color(int); // установить цвет
   void change_fild(Fild&); // перед выходом из клетки удаление или замена объекта
private:
   bool is_crash(Robots&); // столкнулся(набор роботов)?
};

class Object {
   public:
   Object(int);
   virtual bool is_access(Robot&) = 0; // проверка клетки на доступность для робота
};

class Fruit : public Object{
   bool is_access(Robot&);
};

class Tree : public Object{
   bool is_access(Robot&);
};

struct Cell {
   Object* current_object = nullptr; // объект в клетке
   int color = COLOR(255, 255, 255);
};

class Fild {
   int width, height; // размеры поля

   Cell **Fild ; //поле из клеток
   public:
      Fild(int, int); // width, height
      void set_obj(Object*, int, int); // установить объект
      void delete_obj(int, int); // удалить объект
   void set_color(int, int, int); // установить цвет
   Object* get_object(int, int); // получить объкт на клетке
};

class Сommand {
   int i, j;
   bool is_allow_change_cordinat; //разрешено изменять координаты?
   bool is_allow_delete; //разрешено удалять?
   
   friend class Programm;
public:
   Command(bool, bool, int, int); //is_allow_change_cordinat, is_allow_delete, 
   virtual void use(Robot &) = 0;
   virtual void draw(int, int) = 0; // x, y
};

// "Стрелка", меняющая нарпавление
class Arrow : public Command {
   public:
   Arrow(bool, bool, int, int);
   void use(Robot&);
   void draw(int, int) ; // x, y
};

//"Банка с краской", меняющая цвет робота
class ChangeColor : public Command {
   void use(Robot&);
   void draw(int, int); // x, y
};

//"Выход", удаляющий робота
class Exit : public Command {
   void use(Robot&);
   void draw(int, int); // x, y
};

class Programm {
   int color = 255;
   vector<Command> commands ;
public:
   Programm(int); // color
   void add(Command*);
   void draw(int, int);
   Command* select(int, int); // i, j
};

class Task {
   Fild correct_fild;
   std::string text_task; // текст задания

   void initialize(Field&, ); // инициализация всех компанентов согласно заданию
   void prepare(Field&); // размещение предметов на поле
   bool is_task_completed(Fild); // проверка на выполненность
   void draw_an_example() = 0; // иллюстрирование решения задания(для художника)
};

#endif