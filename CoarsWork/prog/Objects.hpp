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
class �ommand;
class Programm;
class Task;

std::vector <Robot *> Robots; // ���������� ������ � ��������
std::vector <Programm *> Programms; // ���������� ������ � �����������

class Robot {
   int i, j; //�������  ���������� ������;
   int direction[2]; // ������� ����������� {0, 1}/{1, 0}/{0, -1}/{-1, 0}
   int color; // ������� ����
   bool allow_change_direction; // ��������� �������� �����������?
   bool allow_change_cordinat; // ��������� �������� ����������?
   Robot(bool, bool); //allow_change_direction, allow_change_cordinat
public:
   void set_cordinat(int, int); // ���������� ����������
   void set_direction(int); // ���������� �����������
   void set_color(int); // ���������� ����
   void change_fild(Fild&); // ����� ������� �� ������ �������� ��� ������ �������
private:
   bool is_crash(Robots&); // ����������(����� �������)?
};

class Object {
   public:
   Object(int);
   virtual bool is_access(Robot&) = 0; // �������� ������ �� ����������� ��� ������
};

class Fruit : public Object{
   bool is_access(Robot&);
};

class Tree : public Object{
   bool is_access(Robot&);
};

struct Cell {
   Object* current_object = nullptr; // ������ � ������
   int color = COLOR(255, 255, 255);
};

class Fild {
   int width, height; // ������� ����

   Cell **Fild ; //���� �� ������
   public:
      Fild(int, int); // width, height
      void set_obj(Object*, int, int); // ���������� ������
      void delete_obj(int, int); // ������� ������
   void set_color(int, int, int); // ���������� ����
   Object* get_object(int, int); // �������� ����� �� ������
};

class �ommand {
   int i, j;
   bool is_allow_change_cordinat; //��������� �������� ����������?
   bool is_allow_delete; //��������� �������?
   
   friend class Programm;
public:
   Command(bool, bool, int, int); //is_allow_change_cordinat, is_allow_delete, 
   virtual void use(Robot &) = 0;
   virtual void draw(int, int) = 0; // x, y
};

// "�������", �������� �����������
class Arrow : public Command {
   public:
   Arrow(bool, bool, int, int);
   void use(Robot&);
   void draw(int, int) ; // x, y
};

//"����� � �������", �������� ���� ������
class ChangeColor : public Command {
   void use(Robot&);
   void draw(int, int); // x, y
};

//"�����", ��������� ������
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
   std::string text_task; // ����� �������

   void initialize(Field&, ); // ������������� ���� ����������� �������� �������
   void prepare(Field&); // ���������� ��������� �� ����
   bool is_task_completed(Fild); // �������� �� �������������
   void draw_an_example() = 0; // ��������������� ������� �������(��� ���������)
};

#endif