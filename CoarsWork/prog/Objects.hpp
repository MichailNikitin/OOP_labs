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
class �ommand;
class Programm;
class Task;

struct position {
   int x, y;
   position() {x = y = 0;}
   position(int new_x, int new_y):x(new_x), y(new_y) {}
   position(const position &pos) {x = pos.x;y = pos.y;}
};

class Robot {
   IMAGE *img; // �������� ������
   position pos; //�������  ���������� ������;
   position direction; // ������� �����������(�������� �� �����������) {0, 1}/{1, 0}/{0, -1}/{-1, 0}
   int color; // ������� ����
   bool allow_change_direction; // ��������� �������� �����������?
   bool allow_change_cordinat; // ��������� �������� ����������?
public:
   Robot(IMAGE *img_robot,bool is_allow_change_direction, bool is_allow_change_cordinat); //allow_change_direction, allow_change_cordinat
   ~Robot();
   void set_cordinat(position); // ���������� ����������
   void set_direction(position); // ���������� �����������
   void set_color(int); // ���������� ����
   int get_color(); // ������� ����
   void change_Field(Field &); // ����� ������� �� ������ �������� ��� ������ �������
   void draw();
private:
   bool is_crash(vector <Robot *> &Robots); // ����������(����� �������)?
};

class Object {
protected:
   IMAGE *img; // �������� �������
public:
   Object(IMAGE *);
   Object(const Object &obj); // ����������� �����
   ~Object();
   virtual bool is_access(Robot &) = 0; // �������� ������ �� ����������� ��� ������
};

class Fruit : public Object {
public:
   Fruit(IMAGE *);
   Fruit(const Fruit &obj); // ����������� �����
   ~Fruit();
   bool is_access(Robot &);
};

class Tree : public Object {
public:
   Tree(IMAGE *);
   Tree(const Tree &obj); // ����������� �����
   ~Tree();
   bool is_access(Robot &);
};

struct Cell {
   Object *current_object = nullptr; // ������ � ������
   int color = WHITE;
};

class Field {
   int width, height; // ������� ����
   vector<vector<Cell>> fullField; //���� �� ������
public:
   Field(int, int); // width, height
   position coord2pos(int, int); // x, y
   void set_obj(Object *, position); // ���������� ������
   void delete_obj(position); // ������� ������
   void set_color(position, int); // ���������� ����
   void draw();
   Object *get_object(position); // �������� ����� �� ������
};

class Command {
   bool is_allow_change_cordinat; //��������� �������� ����������?
   bool is_allow_delete; //��������� �������?

   friend class Programm;

protected:
   IMAGE *img;
   position coord;
public:
   Command(bool, bool, position); //is_allow_change_cordinat, is_allow_delete,  x, y
   Command(const Command &com); // ����������� �����
   Command() = default; // ����������� �����
   void set_pos(position);
   virtual void use(Robot &) = 0;
   virtual void draw(int color) = 0; 
};

// "�������", �������� �����������
class Arrow : public Command {
   position orientation;
public:
   // ���������� �� ���������� � ��������, ������� ������������, ����������� ��������� �����������
   Arrow(bool is_allow_change_cordinat, bool is_allow_delete, position coord, position orient);
   void use(Robot &);
   void draw(int color) ;
};

//"����� � �������", �������� ���� ������
class ChangeColor : public Command {
   int color;
public:
   ChangeColor(bool is_allow_change_cordinat, bool is_allow_delete, position, int color);
   void use(Robot &);
   void draw(int color);
};

//"�����", ��������� ������
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

extern vector <Robot*> Robots; // ���������� ������ � ��������
extern vector <Programm*> Programms; // ���������� ������ � �����������

class Task {
   string text_task; // ����� �������
   string name_taskFile;
   int count_robots;
   int count_commands;
   int count_tree;
   int count_fruit;
   // ������������� ���� ����������� �������� �������
public:
   Task(const string);// �������� ����� � ��������
   void initialize(Field &, std::vector <Robot *> &Robots, std::vector <Programm *> &Programms);
   void prepare_field(Field &);
   bool is_task_completed(Field &, vector <Robot *> &Robots); // �������� �� �������������
   void draw_an_example() {}; // ��������������� ������� �������(��� ���������)
};

#endif