#include <iostream>
#include <vector>
#include "graphics.h"
#include "Objects.hpp"

#define POS2CORD(x) 100*x

using namespace std;

vector <Robot *> Robots; // глобальный вектор с роботами
vector <Programm *> Programms; // глобальный вектор с программами

int main() {
   initwindow(800, 550, "Программа для обучения программированию");
   putimage(0, 0, loadBMP("inteface.bmp"), COPY_PUT);

   position current_cell(0, 0);

   Field field(WIDTH_I, HEIGHT_J);

   Task task("tast_list.txt", field, Robots, Programms);

   Robots.push_back(new Robot(false, true));
   Robots.emplace_back(new Robot(true, false));

   Programms.emplace_back(new Programm(RED));
   Programms.emplace_back(new Programm(GREEN));
   
   while (1) {
      switch (getch(kbhit())) {
      case KEY_UP:
         current_cell.y += (current_cell.y == 0) ? 0 : -1;
         setcolor(YELLOW);
         rectangle(POS2CORD(current_cell.x), POS2CORD(current_cell.y), current_cell.x+100, current_cell.y+100);
         break;
      case KEY_DOWN:
         current_cell.y += (current_cell.y == HEIGHT_J) ? 0 : 1;
         setcolor(YELLOW);
         rectangle(POS2CORD(current_cell.x), POS2CORD(current_cell.y), POS2CORD(current_cell.x+100), POS2CORD(current_cell.y+100));
         break;
      case KEY_LEFT:
         current_cell.x += (current_cell.x == 0) ? 0 : -1;
         setcolor(YELLOW);
         rectangle(current_cell.x, current_cell.y, current_cell.x+100, current_cell.y+100);
         break;
      case KEY_RIGHT:
         current_cell.x += (current_cell.x == WIDTH_I) ? 0 : 1;
         setcolor(YELLOW);
         rectangle(current_cell.x, current_cell.y, current_cell.x+100, current_cell.y+100);
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