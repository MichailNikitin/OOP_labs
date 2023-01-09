

#ifndef OBJECTS_H
#define OBJECTS_H
#include <vector>
#include <string>

class Robot;
class Robots;
class Object;
class Cell;
class Fild;
class Сommand;
class Programm;
class Task;

enum type = {FRUIT, TREE}; // варианты объектов: фрукты для сбора, деревья - препядствия

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
   bool is_crash(); // столкнулся(набор роботов)?
};

class Robots {
   static const int count_robots; // количество роботов
   std::vector <Robot*> arrRobots;
   Robots(count_robots);
      public:
      Robot get_robot(int);
      void add_robot(Robot); // добавить робота
      void revove_robot(Robot); // удалить робота
};

class Object {
   int correct_type; // варианты объектов: фрукты для сбора, деревья - препядствия
   Object(int);
public:
   bool is_access(Robot); // проверка клетки на доступность для робота
};

class Cell {
   int i, j; // координаты клетки
   Object correct_object; // объект в клетке
   Cell();
public:
   void set_obj(Object); // установить объект
   void delete_obj();
   void set_color(int); // установить цвет
   Object get_object(); // получить объкт на клетке
};

class Fild {
   int width, height; // размеры поля
   Fild(int, int); // width, height
   Cell **arrCell = new Cell[width][height]; //поле из клеток
};

class Сommand {
   bool is_allow_change_cordinat; //разрешено изменять координаты?
   bool is_allow_delete; //разрешено удалять?
   Command(bool, bool);
public:
   virtual void use(Robot) = 0;
};

// "Стрелка", меняющая нарпавление
class Arrow : public Command {
   void use(Robot);
};

//"Банка с краской", меняющая цвет робота
class ChangeColor : public Command {
   void use(Robot);
};
//"Выход", удаляющий робота
class Exit : public Command {
   void use(Robot);
};

class Programm {
   int color = 255;
   Command correct_command;
   Programm(Arrow, int); // Arrow, color
   Programm(ChangeColor, int);
   Programm(Exit, int);
};

class Programms {
   int count_programms; // количество программу
   Programms(int); //count_programms
   Programm *arrRobot = new Programm[count_robots];
   void add_programm(Programm); // добавить робота
   void revove_programm(Programm); // удалить робота
};

class Task {
   Fild correct_fild;
   Robots correct_robots;
   Programms correct_programms;
   std::string text_task;

   void initialize(Fild, Robots, Programms); // инициализация всех компанентов согласно заданию
   void prepare(& Fild); // размещение предметов на поле
   bool is_task_completed(Fild, Robots); // проверка на выполненность
   void draw_an_example() = 0; // иллюстрирование решения задания(для художника)
};

#endif