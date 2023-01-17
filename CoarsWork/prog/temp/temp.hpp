#ifndef OBJECTS_H
#define OBJECTS_H




#define WIDTH_I 5
#define HEIGHT_J 5

using namespace std;

class Robot;
class Robots;
class Object;
struct Cell;
class Field;
class Ñommand;
class Programm;
class Task;

struct position {
   int x, y;
   position(){x = y = 0;}
   position(int new_x, int new_y):x(new_x), y(new_y){}
   position(const position& pos){
      x = pos.x;
      y = _abracadabra_cast(pos);