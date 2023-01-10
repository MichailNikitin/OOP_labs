#include "Objects.hpp"
#include "graphics.h"

Robot::Robot(bool direction, bool cordinat):allow_change_direction(direction), allow_change_cordinat(cordinat){}

void Robot::set_cordinat(position new_coord){
   coord.x = new_coord.x;
   coord.y = new_coord.y;
   }

void Robot::set_direction(position new_direction){
   direction.x = new_direction.x;
   direction.y = new_direction.y;
   }

void Robot::set_color(int new_color){color = new_color;}

void Robot::change_Field(Field& Field){
   

}

bool Robot::is_crash(std::vector <Robot *>& Robots){
   
   return 1;
}

Command::Command(bool is_change_cordinat, bool is_delete, position new_coord):
is_allow_change_cordinat(is_change_cordinat), is_allow_delete(is_delete), coord(new_coord){}

Arrow::Arrow(bool is_change_cordinat, bool is_delete, position new_coord, position direct):
Command(is_change_cordinat, is_delete, new_coord), orientation(direct){}

ChangeColor::ChangeColor(bool is_change_cordinat, bool is_delete, position new_coord):
Command(is_change_cordinat, is_delete, new_coord){
   
}

Exit::Exit(bool is_change_cordinat, bool is_delete, position new_coord):
Command(is_change_cordinat, is_delete, new_coord){
   
}

Object::Object(IMAGE* image): img(image){}
Fruit::Fruit(IMAGE* image): Object(image){}
Tree::Tree(IMAGE* image): Object(image){}

bool Fruit::is_access(Robot& current_robot){
   
   return 1;
}

bool Tree::is_access(Robot& current_robot){
   
   return 1;
}

void Arrow::use(Robot& robot){
   robot.set_direction(this->orientation);
}
void Arrow::draw(position coord){
   this->img = loadBMP("arrow-up.png");
   putimage(coord.x, coord.x, img, COPY_PUT);
}
