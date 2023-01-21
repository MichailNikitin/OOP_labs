#include <fstream>
#include <iostream>
#include <format>
#include "graphics.h"
#include <algorithm>
#include <string>
#include "Objects.hpp"
#include <typeinfo>



static int arr_arrowUp[16] = {45, 0, 90, 45, 67, 45, 67, 90, 23, 90, 23, 45, 0, 45, 45, 0};
constexpr int color_prog[4] = {RED, GREEN, BLUE, YELLOW};

using namespace std;

int direct2grad(position direct) {
   if (direct.y == 1)
      return 90;
   if (direct.x == -1)
      return 180;
   if (direct.y == -1)
      return 270;
   else
      return 0;
}

bool find_command_in_prog(Programm *prog, int color) {
   if (prog->get_col() == color)
      return true;
   return false;
}


Robot::Robot(IMAGE *image, bool direction, bool cordinat):img(image), allow_change_direction(direction), allow_change_cordinat(cordinat) {}
Robot::~Robot() {freeimage(img);}

void Robot::set_cordinat(position new_pos) {
   pos.x = new_pos.x;
   pos.y = new_pos.y;
}

void Robot::set_direction(position new_direction) {
   direction.x = new_direction.x;
   direction.y = new_direction.y;
}

void Robot::set_color(int new_color) {color = new_color;}

void Robot::change_Field(Field &Field) {


}

void Robot::draw() {
   IMAGE *rotImg = imageturn(img,  direct2grad(pos), WHITE);
   putimage(pos.x*100+5,pos.y*100+5, rotImg, COPY_PUT);
}
bool Robot::is_crash(std::vector <Robot *> &Robots) {

   return 1;
}

Object::Object(IMAGE *image): img(image) {}
Object::~Object() {freeimage(img);}
Fruit::Fruit(IMAGE *image): Object(image) {}
Fruit::~Fruit() {freeimage(img);}
Tree::Tree(IMAGE *image): Object(image) {}
Tree::~Tree() {freeimage(img);}

bool Fruit::is_access(Robot &current_robot) {
   return 1;
}

bool Tree::is_access(Robot &current_robot) {
   return 0;
}

Field::Field(int w, int h):width(w), height(h) {
   //vector<vector<Cell>> field(width, vector<Cell>(height));
}

position Field::coord2pos(int x, int y) {
   position current_pos;
   current_pos.x = x/100;
   current_pos.y = y/100;
   return current_pos;
}

void Field::set_obj(Object *obj, position pos) { // i, j
   field[pos.x][pos.y].current_object = obj;
}

void Field::delete_obj(position pos) { // i, j
   delete field[pos.x][pos.y].current_object;
}

void Field::set_color(position pos, int color) { // i, j
   field[pos.x][pos.y].color = color;
}

Object *Field::get_object(position pos) {
   return field[pos.x][pos.y].current_object;
}

Command::Command(bool is_change_cordinat, bool is_delete, position new_coord):
   is_allow_change_cordinat(is_change_cordinat), is_allow_delete(is_delete), coord(new_coord) {}

Command::Command(const Command &com) {
   is_allow_change_cordinat = com.is_allow_change_cordinat;
   is_allow_delete = com.is_allow_delete;
   coord = com.coord;
}
void Command::set_pos(position pos) {
   coord.x = pos.x;
   coord.y = pos.y;
}

Arrow::Arrow(bool is_change_cordinat, bool is_delete, position new_coord, position direction):
   Command(is_change_cordinat, is_delete, new_coord), orientation(direction) {}

ChangeColor::ChangeColor(bool is_change_cordinat, bool is_delete, position new_coord, int color):
   Command(is_change_cordinat, is_delete, new_coord), color(color) {}

Exit::Exit(bool is_change_cordinat, bool is_delete, position new_coord):
   Command(is_change_cordinat, is_delete, new_coord) {}

void Arrow::use(Robot &robot) {
   robot.set_direction(this->orientation);
}
void Arrow::draw() {
   setcolor(BLACK);
   /*
      for(int i = 0; i < 15; i++){
         arr_arrowUp[i] += (coord.x * 100);
         arr_arrowUp[i+1] += (coord.y * 100);
      }
      drawpoly(8, arr_arrowUp);
      */
   rectangle(coord.x*100, coord.y*100, coord.x*100+50, coord.y*100+50);
}

void ChangeColor::use(Robot &robot) {
   robot.set_color(this->color);
}
void ChangeColor::draw() {
   setcolor(RED);
   circle(coord.x+50, coord.y+50, 40);
}

void Exit::use(Robot &robot) {
   Robots.erase(ranges::find(Robots, &robot));
}
void Exit::draw() {
   this->img = loadBMP("wooden-crate.png");
   putimage(coord.x, coord.x, img, COPY_PUT);
}

Programm::Programm(int c): color(c) {}

int Programm::get_col() {return color;}

void Programm::add(Command *command) {  // , bool change_coord, bool is_delete, position pos
   commands.push_back(command);
}

void Programm::draw() {
   for (int i = 0; i < commands.size(); i ++)
      commands[i]->draw();
}

Task::Task(const string file_name): name_taskFile(file_name) {}

void Task::initialize(Field &current_Field, vector <Robot *> &Robots,vector <Programm *> &Programms) {
   ifstream file;
   setlocale(LC_ALL, "Russian");
   file.open(name_taskFile);

   getline(file, text_task);
   file >> count_robots >> count_commands;

   cout << text_task << endl;
   cout << count_robots<< " " << count_commands<< endl;

   for (int i = 0; i < count_robots; i++) {
      int r_x, r_y, r_color;
      int f_color, f_direct;
      string f_change_direct, f_change_coord;
      file >> r_x >> r_y;
      file >>f_color >> f_direct;
      file >> f_change_direct >> f_change_coord;
      cout << r_x << " " << r_y << " " << f_color << " "<< f_direct <<" "<< f_change_direct <<" "<< f_change_coord << endl;

      bool change_direct, change_coord;
      position direct;
      change_direct = (f_change_direct == "да"? true : false);
      change_coord = (f_change_coord == "да"? true : false);

      switch (f_direct) {
      case 0:
         direct = position(1, 0);
         break; // "вправ"
      case 1:
         direct = position(0, 1);
         break; //"вверх"
      case 2:
         direct = position(-1, 0);
         break; //"влево"
      case 3:
         direct = position(0, -1);
         break; //"вниз"

      }
      char name_image[7];
      snprintf(name_image, sizeof(name_image), "r%d.bmp",f_color);
      Robot new_robot(loadBMP(name_image),change_direct, change_coord);
      new_robot.set_color(color_prog[f_color]);
      new_robot.set_cordinat(position(r_x, r_y));
      new_robot.set_direction(direct);
      new_robot.draw();
      Robots.push_back(&new_robot);
   }
   /*
   Arrow arrow1(true, false, position(1, 2), position(0, 1));
   Arrow arrow2(true, false, position(1, 2), position(0, 1));
   ChangeColor canOfPaint(true, false, position(1, 2), RED);
   Exit box(true, false, position(1, 2));
   Programm program(RED);
   program.add(&arrow1);
   program.add(&arrow2);
   Programms.push_back(&program);
   Programms[0]->draw();
   */

   // цикл чтения информации о программах
   for (int i = 0; i < count_commands; i++) {
      string name_com;
      //Arrow commandArrow;
      int com_x, com_y;
      int f_color;
      //position orient;
      file >> name_com;
      string f_allow_delete, f_change_coord;
      file >>f_color >> com_x >> com_y;
      file >> f_change_coord >> f_allow_delete;

      bool allow_delete = (f_allow_delete == "да"? true : false);
      bool change_coord = (f_change_coord == "да"? true : false);

      cout << name_com  <<   " " << f_color <<" "<< com_x << " " << com_y << " "
           <<  f_change_coord <<" "<< f_allow_delete << " ";

      Command *command;

      if (name_com == "стрелка") {
         int f_orient;
         position orient;
         file >> f_orient;

         cout << f_orient << endl;
         switch (f_orient) {
         case 0:
            orient = position(1, 0);
            break; // "вправo"
         case 1:
            orient = position(0, 1);
            break; //"вверх"
         case 2:
            orient = position(-1, 0);
            break; //"влево"
         case 3:
            orient = position(0, -1);
            break; //"вниз"
         }
         Arrow arrow(change_coord, allow_delete, position(com_x, com_y), orient);
         command = &arrow;
      }

      if (name_com == "банка_с_краской") {
         int f_change_col;
         file >> f_change_col;

         cout << f_change_col << endl;
         ChangeColor canOfPaint(change_coord, allow_delete, position(com_x, com_y), color_prog[f_change_col]);
         command = &canOfPaint;
      }

      if (name_com == "выход") {
         cout << endl;
         Exit box(change_coord, allow_delete, position(com_x, com_y));
         command = &box;
      }
      else
         cout << "Сюда вставить проверку на ошибки\n";

      auto it =  find_if(Programms.begin(), Programms.end(), [f_color](Programm *prog) -> bool {
         cout <<"цвет ---"<< prog->get_col()<<"--- цвет2 ---"<< color_prog[f_color] << endl;
         return prog->get_col() == color_prog[f_color];});


      //   cout << "Iterator "<< typeid(*it).name() << endl;

      if (it != Programms.end())
      {
         cout << "Нашёл" << endl;

         cout << "Iterator "<< (*it)->get_col() << endl;
         (*it)->add(command);
      }
      else {
         cout << "Не нашёл"  << endl;
         Programm *new_programm = new Programm(color_prog[f_color]);
         new_programm->add(command);
         /*   if (name_com == "стрелка") {
               new_programm.add(&arrow);
            }
            else if(name_com == "банка_с_краской"){
            new_programm.add(&canOfPaint);
            }
            else if(name_com == "выход"){
              new_programm.add(&box);
            }
         */
         Programms.push_back(new_programm);
         for (unsigned int i = 0; i < Programms.size(); i++)
         {
            cout <<"цвет ---control---"<< Programms[i]->get_col() << endl;
         }

      }
   }

   //for (int i = 0; i < Programms.size(); i++)
   //Programms[i].draw();



   cout << "Чтение файла завешенно. Закрываем файл\n" << endl;
   file.close();
}




