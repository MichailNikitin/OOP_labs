#include <iostream>
#include <vector>
#include "graphics.h"
#include "interface.h"
#include "Objects.hpp"

using namespace std;

vector <Robot *> Robots; // глобальный вектор с роботами
vector <Programm *> Programms; // глобальный вектор с программами

int main() {
   initwindow(800, 650, "Программа для обучения программированию");
   putimage(0, 0, loadBMP("inteface.bmp"), COPY_PUT);
   
   position current_cell(0, 0); 
   
   Field field(WIDTH_I, HEIGHT_J);
   
   //Task task("tast_list.txt", field, Robots, Programms);
   Robots.resize(2);
   Robots.emplace_back(new Robot(false, true));
   Robots.emplace_back(new Robot(true, false));
   
   Programms.resize(2);
   Programms.emplace_back(new Programm(RED));
   Programms.emplace_back(new Programm(GREEN));
   
   while (1) {
      switch (getch(kbhit())) {
      case KEY_UP:
         //current_cell = current_cell
         break;
      case KEY_DOWN:

         break;
      case KEY_LEFT:

         break;
      case KEY_RIGHT:

         break;
      case KEY_ENTER:

         break;
      case KEY_DELETE:

         break;
      case KEY_BACKSPACE:

         break;
      case KEY_ESC:
         closegraph();
         return 0;
      }
   }
}