#include <iostream>
#include "graphics.h"
#include <vector>
#include "Objects.hpp"

std::vector <Robot *> Robots; // глобальный вектор с роботами
std::vector <Programm *> Programms; // глобальный вектор с программами

int main() {
   initwindow(800, 650, "Программа для обучения программированию");
   putimage(0, 0, loadBMP("inteface.bmp"), COPY_PUT);
   
   
   
   
   
   
   while (1) {
      switch (getch(kbhit())) {
      case KEY_UP:

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