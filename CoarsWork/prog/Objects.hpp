#include <vector>

#ifndef OBJECTS_H
#define OBJECTS_H

class Robot {
   int i, j; //�������  ���������� ������;
   int direction; // ������� �����������
   int color; // ������� ����
   bool allow_change_direction; // ��������� �������� �����������?
   bool allow_change_cordinat; // ��������� �������� ����������?
   Robot(bool, bool); //allow_change_direction, allow_change_cordinat
public:
   void set_cordinat(int, int); // ���������� ����������
   void set_direction(int); // ���������� �����������
   void set_color(int); // ���������� ����
   void change_fild(Fild); // ����� ������� �� ������ �������� ��� ������ �������
private:
   bool is_crash(); // ����������(����� �������)?
}

class Robots {
   int count_robots; // ���������� �������
   Robot *arrRobot = new Robot[count_robots];
   void add_robot(Robot); // �������� ������
   void revove_robot(Robot); // ������� ������
}

class Object {
   enum type = {FRUIT, TREE}; // �������� ��������: ������ ��� �����, ������� - �����������
   Object(type);
public:
   bool is_access(Robot) // �������� ������ �� ����������� ��� ������
}

class Cell {
   int i, j; // ���������� ������
   Object correct_object; // ������ � ������
   Cell();
public:
   void set_obj(Object); // ���������� ������
   void set_color(int); // ���������� ����
   Object get_object(); // �������� ����� �� ������
}

class Fild {
   int width, height; // ������� ����
   Fild(int, int); // width, height
   Cell **arrCell = new Cell[width][height]; //���� �� ������
}

class �ommand {
   bool is_allow_change_cordinat; //��������� �������� ����������?
   bool is_allow_delete; //��������� �������?
   Command(bool, bool);
public:
   virtual void use(Robot) = 0;
}

// "�������", �������� �����������
class Arrow : public Command {
   void use(Robot);
}

//"����� � �������", �������� ���� ������
class ChangeColor : public Command {
   void use(Robot);
}
//"�����", ��������� ������
class Exit : public Command {
   void use(Robot);
}

class Programm {
   int color = 255;
   Command correct _command;
   Programm(Arrow, int); // Arrow, color
   Programm(ChangeColor, int);
   Programm(Exit, int);
}

class Programms {
   int count_programms; // ���������� ���������
   Programms(int); //count_programms
   Programm *arrRobot = new Programm[count_robots];
   void add_programm(Programm); // �������� ������
   void revove_programm(Programm); // ������� ������
}

class Task {
   Fild correct_fild; 
   Robots correct_robots;
   Programms correct_programms;
   std::string text_task;
   
   void initialize(Fild, Robots, Programms); // ������������� ���� ����������� �������� �������
   void prepare(& Fild); // ���������� ��������� �� ����
   bool is_task_completed(Fild, Robots); // �������� �� ������������� 
   void draw_an_example() = 0; // ��������������� ������� �������(��� ���������)
}

#endif