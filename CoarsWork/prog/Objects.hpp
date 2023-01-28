#ifndef OBJECTS_H
#define OBJECTS_H

#include <fstream>
#include <iostream>
#include <format>
#include <algorithm>
#include <string>
#include <typeinfo>
#include <time.h>
#include <stdlib.h>
#include <sstream>
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

//структура для хранения координат парами
struct position {
   int x, y; // координаты
   position() {x = y = 0;} // конструктор без передаваемых параметров
   position(int new_x, int new_y):x(new_x), y(new_y) {} // конструктор со значениями
   position(const position &pos) {x = pos.x; y = pos.y;} // конструктор копий
   // перегрузка оператора для сравнения
   friend auto operator<=>(const position &, const position &) = default;
};

class Robot {
   IMAGE *img; // картинка робота
   position pos; //текущие  координаты робота;
   position direction; // текущее направление (смещение по координатам) {0, 1}/{1, 0}/{0, -1}/{-1, 0}
   int color; // текущий цвет
   bool allow_change_direction; // разрешено изменять направление?
   bool allow_change_cordinat; // разрешено изменять координаты?
public:
   Robot(IMAGE *img_robot,bool is_allow_change_direction, bool is_allow_change_cordinat); //конструктор
   ~Robot(); //деструктор
   void set_pos(position); // установить координаты
   void set_direction(position); // установить направление
   void set_color(int); // установить цвет
   void set_img(IMAGE *); //установить картинку робота нужного цвета
   int get_color(); // вернуть цвет
   int get_n_color(); // вернуть номер цвета
   bool get_allow_change_cordinat(); // вернуть: разрешено изменять направление?
   bool get_allow_change_direction(); // вернуть: разрешено изменять координаты?
   position get_pos(); // вернуть координаты
   position get_direction(); // вернуть направление
   void change_Field(Field &); // перед выходом из клетки удаление или замена объекта
   void draw(); // отрисовка робота
   bool is_crash(vector <Robot *> &Robots); // столкнулся (набор роботов)?
   bool is_collision(Field &, vector <Robot *> &Robots); // наложение на другие объекты
};

//базовый класс для неподвижных сущностей
class Object {
protected:
   IMAGE *img; // картинка объекта
public:
   Object(IMAGE *); // конструктор
   Object(const Object &obj); // конструктор копий
   ~Object();// деструтор
   virtual void draw(position) = 0; // нарисовать объект
};

// доступный для сбора объект
class Fruit : public Object {
public:
   Fruit(IMAGE *); // конструктор
   ~Fruit(); // деструктор
   void draw(position); // отрисовка фрукта
};

// недоступный для перемещения объект
class Tree : public Object {
public:
   Tree(IMAGE *); // конструктор
   ~Tree(); // деструктор
   void draw(position); // отрисовка дерева
};

// струкура для клетки поля
struct Cell {
   Object *current_object = nullptr; // объект в клетке
   int color = WHITE; // цвет клетки
};

//класс поля
class Field {
   int width, height; // размеры поля
   int count_tree;          // количество деревьев
   int count_fruit;          // количество урожая
   vector<vector<Cell>> fullField; //поле из клеток
public:
   Field(int, int); // конструктор
   void set_obj(Object *, position); // установить объект
   void delete_obj(position); // удалить объект
   void set_color(position, int); // установить цвет
   void set_count_tree(int count_tree); // установить количество деревьев
   void set_count_fruit(int count_fruit); // установить количество фруктов
   int get_count_fruit(); // установить количество фруктов
   void draw(); // отрисовка всех Object на поле
   Object *get_object(position); // получить объект на клетке
   //bool is_there_fruit(); // есть ли фрукты на поле?
};

//класс команд
class Command {
   bool is_allow_change_cordinat; //разрешено изменять координаты?
   bool is_allow_delete; //разрешено удалять?

  friend class Programm; //программа дружественный класс
   
protected:
   IMAGE *img; // изображение команды
   position coord; //координаты команды
public:
   Command(bool, bool, position); // констуктор
   Command(const Command &com); // конструктор копий
   Command() = default; // базовый конструктор
   void set_pos(position); // задать новую позицию команде
   position get_pos();  // вернуть текущую позицию
   bool get_allow_pos(); // разрешено ли изменять положение
   virtual void use(Robot &) = 0; // виртуальный метод воздействие на робота
   virtual void draw(int color) = 0; // виртуальный метод рисования
};

// "Стрелка", меняющая нарпавление
class Arrow : public Command {
   position orientation; // ориентация стрелки
public:
   // конструктор
   Arrow(bool is_allow_change_cordinat, bool is_allow_delete, position coord, position orient);
   void use(Robot &); // воздействие на робота
   void draw(int color) ; // рисование стрелки
};

//"Банка с краской", меняющая цвет робота
class ChangeColor : public Command {
   int color; // новый цвет
public:
   //конструктор
   ChangeColor(bool is_allow_change_cordinat, bool is_allow_delete, position, int color);
   void use(Robot &); // воздействие на робота
   void draw(int color); // рисование банки с краской
};

//"Выход", удаляющий робота
class Exit : public Command {
public:
   // конструктор
   Exit(bool is_allow_change_cordinat, bool is_allow_delete, position);
   void use(Robot &); // воздействие на робота
   void draw(int color);  // рисование выхода
};

// Класс программ, содержащий набор команд одного цвета
class Programm  {
   int color = WHITE; // цвет программы
   vector<Command *> commands ; // вектор команд внутри одной программы
public:
   Programm(int color);     // конструктор
   int get_col();                // вернуть цвет
   void add(Command *);  //  добавление команды
   void draw();                 // отрисовать все команды данной программы
   Command *select(position); // выбрать команду на определенной позиции
   void delete_com(Command *); // удаление команды
   bool is_collision();          // проверка на наложение объектов
};

extern vector <Robot *> Robots; // глобальный вектор с роботами
extern vector <Programm *> Programms; // глобальный вектор с программами
// класс с заданием
class Task {
   string text_task;        // текст задания
   string name_taskFile; // название файла с заданием
   int count_robots;       // количество роботов
   int count_commands;// количество команд
   int count_tree;          // количество деревьев
   int count_fruit;          // количество урожая
public:
   Task(const string);// название файла с заданием
   // инициализация роботов и программ по файлу с заданием
   void initialize(Field &, std::vector <Robot *> &Robots, std::vector <Programm *> &Programms);
   void prepare_field(Field &); // расставить на поле статичные объекты
   bool is_task_completed(Field &, vector <Robot *> &Robots); // задание выполнено?
   string get_text_task(); // вернуть текст задания
   void draw_an_example() {}; // иллюстрирование решения задания (для программы "художника")
};

#endif