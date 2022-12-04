#include <vector>

#ifndef MYCLASS_H
#define MYCLASS_H

class Robot {
   int x, y // координаты робота;
   int direction; // текущее направление
   int color;
public:
   void set_cordinat();
   void set_direction();
   void set_color;
   void change_fild(Fild);
private:
   bool allow_change_direction();
   bool allow_ change_cordinat();
   bool is_ crash();
}

class Object {

public:
   bool is_ access(Robot) // проверка клетки на доступность для робота
}

class Cell {
   int i, j; // номер клетки
   Object correct_obj;
public:
   void set_obj(Object);
}

class Fild {
   int width, высота; // размеры поля
   Cell[] arrCell = new 


}



#endif