#ifndef OBJECTS_H
#define OBJECTS_H
#include <vector>
#include <string>
#include "graphics.h"

#define WIDTH_I 5
#define HEIGHT_J 5
#define COUNFUITS 2
#define COUNTTREE 1


using namespace std;

class Robot;
class Robots;
class Object;
struct Cell;
class Field;
class Сommand;
class Programm;
class Task;

struct position {
   int x, y;
   position() {x = y = 0;}
   position(int new_x, int new_y):x(new_x), y(new_y) {}
   position(const position &pos) {x = pos.x;y = pos.y;}
};

class Robot {
   IMAGE *img; // картинка робота
   position pos; //текущие  координаты робота;
   position direction; // текущее направление(смещение по координатам) {0, 1}/{1, 0}/{0, -1}/{-1, 0}
   int color; // текущий цвет
   bool allow_change_direction; // разрешено изменять направление?
   bool allow_change_cordinat; // разрешено изменять координаты?
public:
   Robot(IMAGE *img_robot,bool is_allow_change_direction, bool is_allow_change_cordinat); //allow_change_direction, allow_change_cordinat
   ~Robot();
   void set_cordinat(position); // установить координаты
   void set_direction(position); // установить направление
   void set_color(int); // установить цвет
   int get_color(); // вернуть цвет
   void change_Field(Field &); // перед выходом из клетки удаление или замена объекта
   void draw();
private:
   bool is_crash(vector <Robot *> &Robots); // столкнулся(набор роботов)?
};

class Object {
protected:
   IMAGE *img; // картинка объекта
public:
   Object(IMAGE *);
   Object(const Object &obj); // Конструктор копий
   ~Object();
   virtual bool is_access(Robot &) = 0; // проверка клетки на доступность для робота
};

class Fruit : public Object {
public:
   Fruit(IMAGE *);
   Fruit(const Fruit &obj); // Конструктор копий
   ~Fruit();
   bool is_access(Robot &);
};

class Tree : public Object {
public:
   Tree(IMAGE *);
   Tree(const Tree &obj); // Конструктор копий
   ~Tree();
   bool is_access(Robot &);
};

struct Cell {
   Object *current_object = nullptr; // объект в клетке
   int color = WHITE;
};

class Field {
   int width, height; // размеры поля
   vector<vector<Cell>> fullField; //поле из клеток
public:
   Field(int, int); // width, height
   position coord2pos(int, int); // x, y
   void set_obj(Object *, position); // установить объект
   void delete_obj(position); // удалить объект
   void set_color(position, int); // установить цвет
   void draw();
   Object *get_object(position); // получить объкт на клетке
};

class Command {
   bool is_allow_change_cordinat; //разрешено изменять координаты?
   bool is_allow_delete; //разрешено удалять?

   friend class Programm;

protected:
   IMAGE *img;
   position coord;
public:
   Command(bool, bool, position); //is_allow_change_cordinat, is_allow_delete,  x, y
   Command(const Command &com); // Конструктор копий
   Command() = default; // Конструктор копий
   void set_pos(position);
   virtual void use(Robot &) = 0;
   virtual void draw(int color) = 0; 
};

// "Стрелка", меняющая нарпавление
class Arrow : public Command {
   position orientation;
public:
   // разрешение на пермещение и удаление, позиция расположения, позимещения изменения направления
   Arrow(bool is_allow_change_cordinat, bool is_allow_delete, position coord, position orient);
   void use(Robot &);
   void draw(int color) ;
};

//"Банка с краской", меняющая цвет робота
class ChangeColor : public Command {
   int color;
public:
   ChangeColor(bool is_allow_change_cordinat, bool is_allow_delete, position, int color);
   void use(Robot &);
   void draw(int color);
};

//"Выход", удаляющий робота
class Exit : public Command {
public:
   Exit(bool is_allow_change_cordinat, bool is_allow_delete, position);
   void use(Robot &);
   void draw(int color); 
};

class Programm  {
   int color = WHITE;
   vector<Command *> commands ;
public:
   Programm(int color); // color
   int get_col();
   void add(Command *);
   void draw();
   Command *select(position); // i, j
};

extern vector <Robot*> Robots; // глобальный вектор с роботами
extern vector <Programm*> Programms; // глобальный вектор с программами

class Task {
   string text_task; // текст задания
   string name_taskFile;
   int count_robots;
   int count_commands;
   int count_tree;
   int count_fruit;
   // инициализация всех компанентов согласно заданию
public:
   Task(const string);// название файла с заданием
   void initialize(Field &, std::vector <Robot *> &Robots, std::vector <Programm *> &Programms);
   void prepare_field(Field &);
   bool is_task_completed(Field &, vector <Robot *> &Robots); // проверка на выполненность
   void draw_an_example() {}; // иллюстрирование решения задания(для художника)
};

#endif