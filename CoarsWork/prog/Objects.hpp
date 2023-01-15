#ifndef OBJECTS_H
#define OBJECTS_H
#include <vector>
#include <string>
#include "graphics.h"

#define WIDTH_I 5
#define HEIGHT_J 5

class Robot;
class Robots;
class Object;
struct Cell;
class Field;
class �ommand;
class Programm;
class Task;

struct position {
   int x, y;
};

class Robot {
   IMAGE *img; // �������� ������
   position coord; //�������  ���������� ������;
   position direction; // ������� �����������(�������� �� �����������) {0, 1}/{1, 0}/{0, -1}/{-1, 0}
   int color; // ������� ����
   bool allow_change_direction; // ��������� �������� �����������?
   bool allow_change_cordinat; // ��������� �������� ����������?
public:
   Robot(bool, bool); //allow_change_direction, allow_change_cordinat
   ~Robot() = default;
   void set_cordinat(position); // ���������� ����������
   void set_direction(position); // ���������� �����������
   void set_color(int); // ���������� ����
   void change_Field(Field &); // ����� ������� �� ������ �������� ��� ������ �������
private:
   bool is_crash(std::vector <Robot *> &Robots); // ����������(����� �������)?
};

class Object {
   IMAGE *img; // �������� �������
public:
   Object(IMAGE *);
   //~Object();
   virtual bool is_access(Robot &) = 0; // �������� ������ �� ����������� ��� ������
};

class Fruit : public Object {
public:
   Fruit(IMAGE *);
   //~Fruit();
   bool is_access(Robot &);
};

class Tree : public Object {
public:
   Tree(IMAGE *);
   //~Tree();
   bool is_access(Robot &);
};

struct Cell {
   Object *current_object = nullptr; // ������ � ������
   int color = COLOR(255, 255, 255);
};

class Field {
   int width, height; // ������� ����
   std::vector<std::vector<Cell>> field; //���� �� ������
public:
   Field(int, int); // width, height
   position coord2pos(int, int); // x, y
   void set_obj(Object *, position); // ���������� ������
   void delete_obj(position); // ������� ������
   void set_color(position, int); // ���������� ����
   Object *get_object(position); // �������� ����� �� ������
};

class Command {
   position coord;
   bool is_allow_change_cordinat; //��������� �������� ����������?
   bool is_allow_delete; //��������� �������?

   friend class Programm;

protected:
   IMAGE *img;
public:
   Command(bool, bool, position); //is_allow_change_cordinat, is_allow_delete,  x, y
   virtual void use(Robot &) = 0;
   virtual void draw(position) = 0; // x, y
};

// "�������", �������� �����������
class Arrow : public Command {
   position orientation;
public:
   // ���������� �� ���������� � ��������, ������� ������������, ����������� ��������� �����������
   Arrow(bool, bool, position, position);
   void use(Robot &);
   void draw(position) ; // x, y
};

//"����� � �������", �������� ���� ������
class ChangeColor : public Command {
   int color;
public:
   ChangeColor(bool, bool, position);
   void use(Robot &);
   void draw(position); // x, y
};

//"�����", ��������� ������
class Exit : public Command {
public:
   Exit(bool, bool, position);
   void use(Robot &);
   void draw(position); // x, y
};

class Programm {
   int color = 255;
   std::vector<Command> commands ;
public:
   Programm(int); // color
   int get_col();
   void add(Command *);
   void draw(position);
   Command* select(position); // i, j
};

class Task {
   std::string text_task; // ����� �������
   int count_robots;
   int count_programms;
   
   // ������������� ���� ����������� �������� �������
public:
   Task(const std::string, Field &, std::vector <Robot *> &, std::vector <Programm *>&);// �������� ����� � ��������
   bool is_task_completed(Field &, std::vector <Robot *> &Robots); // �������� �� �������������
   void draw_an_example() {}; // ��������������� ������� �������(��� ���������)
};

#endif