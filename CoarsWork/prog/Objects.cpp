#include <fstream>
#include <iostream>
#include "graphics.h"
#include "interface.h"
#include "Objects.hpp"

using namespace std;

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

Object::Object(IMAGE* image): img(image){}
//~Object::Object(){delete img;}
Fruit::Fruit(IMAGE* image): Object(image){}
//~Fruit::Fruit(){delete img;}
Tree::Tree(IMAGE* image): Object(image){}
//~Fruit::Fruit(){delete img;}

bool Fruit::is_access(Robot& current_robot){
   return 1;
}

bool Tree::is_access(Robot& current_robot){
   return 0;
}

Field::Field(int w, int h):width(w), height(h){
   //vector<vector<Cell>> field(width, vector<Cell>(height));
}

position Field::coord2pos(int x, int y){
   position current_pos;
   current_pos.x = x/100;
   current_pos.y = y/100;
   return current_pos;
}

void Field::set_obj(Object* obj, position pos){ // i, j
   field[pos.x][pos.y].current_object = obj;
}

void Field::delete_obj(position pos){ // i, j
   delete field[pos.x][pos.y].current_object;
}

void Field::set_color(position pos, int color){ // i, j
   field[pos.x][pos.y].color = color;
}

Object* Field::get_object(position pos){
   return field[pos.x][pos.y].current_object;
}

Command::Command(bool is_change_cordinat, bool is_delete, position new_coord):
is_allow_change_cordinat(is_change_cordinat), is_allow_delete(is_delete), coord(new_coord){}

Arrow::Arrow(bool is_change_cordinat, bool is_delete, position new_coord, position direction):
Command(is_change_cordinat, is_delete, new_coord){}

ChangeColor::ChangeColor(bool is_change_cordinat, bool is_delete, position new_coord):
Command(is_change_cordinat, is_delete, new_coord){}

Exit::Exit(bool is_change_cordinat, bool is_delete, position new_coord):
Command(is_change_cordinat, is_delete, new_coord){}

void Arrow::use(Robot& robot){
   robot.set_direction(this->orientation);
}
void Arrow::draw(position coord){
   setcolor(BLACK);
   drawpoly(14, arr_arrowUp);
}

void ChangeColor::use(Robot& robot){
   robot.set_color(this->color);
}
void ChangeColor::draw(position coord){
   circle(coord.x+50, coord.y+50, 40);
}

void Exit::use(Robot& robot){
   int a;
}
void Exit::draw(position coord){
   this->img = loadBMP("wooden-crate.png");
   putimage(coord.x, coord.x, img, COPY_PUT);
}

Programm::Programm(int c): color(c){}

int Programm::get_col(){return color;}

void Programm::add(Command * command){ // , bool change_coord, bool is_delete, position pos
   commands.emplace_back(command); 
}

Task::Task(const string file_name, Field &current_Field, vector <Robot *>&Robots,vector <Programm *>&Programms){
   ifstream file;
   setlocale (LC_ALL,"Russian");
   file.open(file_name);
   file >> text_task;
   file >> count_robots >> count_programms;
   
   cout << text_task << endl;
   cout << count_robots<< " " << count_programms;
   
/*   
   for (int i = 0; i < count_robots; i++){
      int r_x, r_y;
      string direct;
      bool change_direct, change_coord;
      file >> r_x >> r_y;
      file >> direct;
      file >> change_direct >> change_coord;
      Robots.emplace_back(new Robot(false, true));
}
*/
   
   file.close();
}



