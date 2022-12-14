#ifndef OBJECTS_H
#define OBJECTS_H
#include <vector>
#include <string>
#include "graphics.h"

class Robot;
class Robots;
class Object;
struct Cell;
class Field;
class ?ommand;
class Programm;
class Task;

std::vector <Robot *> Robots; // ?????????? ?????? ? ????????
std::vector <Programm *> Programms; // ?????????? ?????? ? ???????????

struct position {
   int x, y;
};

class Robot {
   IMAGE *img; // ???????? ??????
   position coord; //???????  ?????????? ??????;
   position direction; // ??????? ???????????(???????? ?? ???????????) {0, 1}/{1, 0}/{0, -1}/{-1, 0}
   int color; // ??????? ????
   bool allow_change_direction; // ????????? ???????? ????????????
   bool allow_change_cordinat; // ????????? ???????? ???????????
   Robot(bool, bool); //allow_change_direction, allow_change_cordinat
public:
   void set_cordinat(position); // ?????????? ??????????
   void set_direction(position); // ?????????? ???????????
   void set_color(int); // ?????????? ????
   void change_Field(Field &); // ????? ??????? ?? ?????? ???????? ??? ?????? ???????
private:
   bool is_crash(std::vector <Robot *> &Robots); // ??????????(????? ???????)?
};

class Object {
   IMAGE *img; // ???????? ???????
public:
   Object(IMAGE *);
   virtual bool is_access(Robot &) = 0; // ???????? ?????? ?? ??????????? ??? ??????
};

class Fruit : public Object {
public:
   Fruit(IMAGE *);
   bool is_access(Robot &);
};

class Tree : public Object {
   Tree(IMAGE *);
   bool is_access(Robot &);
};

struct Cell {
   Object *current_object = nullptr; // ?????? ? ??????
   int color = COLOR(255, 255, 255);
};

class Field {
   int width, height; // ??????? ????
   Cell **field ; //???? ?? ??????
public:
   Field(int, int); // width, height
   void set_obj(Object *, position); // ?????????? ??????
   void delete_obj(position); // ??????? ??????
   void set_color(position, int); // ?????????? ????
   Object *get_object(position); // ???????? ????? ?? ??????
};

class Command {

   position coord;
   bool is_allow_change_cordinat; //????????? ???????? ???????????
   bool is_allow_delete; //????????? ????????

   friend class Programm;
protected:
   IMAGE *img;

public:
   Command(bool, bool, position); //is_allow_change_cordinat, is_allow_delete,  x, y
   virtual void use(Robot &) = 0;
   virtual void draw(position) = 0; // x, y
};

// "???????", ???????? ???????????
class Arrow : public Command {
   position orientation;
public:
   // ?????????? ?? ?????????? ? ????????, ??????? ????????????, ??????????? ????????? ???????????
   Arrow(bool, bool, position, position);
   void use(Robot &);
   void draw(position) ; // x, y
};

//"????? ? ???????", ???????? ???? ??????
class ChangeColor : public Command {
public:
   ChangeColor(bool, bool, position);
   void use(Robot &);
   void draw(position); // x, y
};

//"?????", ????????? ??????
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
   void add(Command *);
   void draw(position);
   Command *select(position); // i, j
};

class Task {
   Field current_Field;
   std::string text_task; // ????? ???????
   // ????????????? ???? ??????????? ???????? ???????
   void initialize(Field &, std::vector <Robot *> &Robots, std::vector <Programm *> &Programms);
   void prepare(Field &); // ?????????? ????????? ?? ????
   bool is_task_completed(Field &, std::vector <Robot *> &Robots); // ???????? ?? ?????????????
   void draw_an_example() {}; // ??????????????? ??????? ???????(??? ?????????)
};

#endif