#include "Objects.hpp"
//#include "graphics.h"

Robot::Robot(bool direction, bool cordinat):allow_change_direction(direction), allow_change_cordinat(cordinat){}

void Robot::set_cordinat(int new_x, int new_y){i = new_x; j = new_y;}

void Robot::set_direction(int new_direction){direction = new_direction;}

void Robot::set_color(int new_color){color = new_color;}

void Robot::change_fild(Fild& fild){
   

}

bool Robot::is_crash(){
   
   
}

Object::Object(int ){
   
   
}

bool Object::is_access(Robot correct_robot){
   
   
}

