#include <iostream>
#include <vector>
#include "Objects.hpp"
#include "graphics.h"

#define POS2CORD(x) 100*x

using namespace std;

vector <Robot *> Robots; // глобальный вектор с роботами
vector <Programm *> Programms; // глобальный вектор с программами

void clearWin() {
   putimage(0, 0, loadBMP("inteface.bmp"), COPY_PUT);
}

void reDraw() { // перерисовка поля
   putimage(0, 0, loadBMP("inteface.bmp"), COPY_PUT);
   for (int i = 0; i < Programms.size(); i++) {
      Programms[i]->draw();
      setcolor(BLACK);
      rectangle(i*122,500, i*122+130, 549);
      setfillstyle(SOLID_FILL, Programms[i]->get_col());
      bar(i*122,500, i*122+130, 549);
   }
   for (int i = 0; i < Robots.size(); i++)
      Robots[i]->draw();
}

void highlightCell(position current_cell) { // выделение ячейки
   setlinestyle(0, 1, 3);
   setcolor(YELLOW);
   rectangle(POS2CORD(current_cell.x), POS2CORD(current_cell.y), POS2CORD(current_cell.x+100), POS2CORD(current_cell.y+100));
}

int n_currect_com = 0;

int main() {
   initwindow(800, 550, "Программа для обучения программированию");
   clearWin();

   position current_cell(0, 0); // позиция текущей клетки

   Field field(WIDTH_I, HEIGHT_J); //создание объекта поля

   Task task("tast_list.txt");
   task.initialize(field, Robots, Programms); //инициализация роботов и программ
   task.prepare_field(field); // подготовка поля с расстановкой объектов
   highlightCell(current_cell); // отображение текущей ячейки
   while (1) {
      
      //выбор текущей клетки
      switch (getch(kbhit())) {
      case KEY_UP:
         reDraw();
         current_cell.y += (current_cell.y == 0) ? 0 : -1;
         highlightCell(current_cell);
         break;
      case KEY_DOWN:
         reDraw();
         current_cell.y += (current_cell.y == HEIGHT_J-1) ? 0 : 1;
         highlightCell(current_cell);
         break;
      case KEY_LEFT:
         reDraw();
         current_cell.x += (current_cell.x == 0) ? 0 : -1;
         highlightCell(current_cell);
         break;
      case KEY_RIGHT:
         reDraw();
         current_cell.x += (current_cell.x == WIDTH_I-1) ? 0 : 1;
         highlightCell(current_cell);
         break;
      
      // отображение программ только определённого цвета
      case '1':
         cout << "Выбрана программа 1"<<endl;
         n_currect_com = 0;
         clearWin();
         highlightCell(current_cell);
         Programms[n_currect_com]->draw();
         for (int i = 0; i < Robots.size(); i++)
            if (Robots[i]->get_color() == Programms[n_currect_com]->get_col()) {
               Robots[i] ->draw();
               setfillstyle(SOLID_FILL, Programms[n_currect_com]->get_col());
               bar(n_currect_com*122,500, n_currect_com*122+130, 549);
            }
         break;
      case '2':
         if (Programms.size() <2)
            break;
         cout << "Выбрана программа 2"<<endl;
         n_currect_com = 1;
         clearWin();
         highlightCell(current_cell);
         Programms[n_currect_com]->draw();
         for (int i = 0; i < Robots.size(); i++)
            if (Robots[i]->get_color() == Programms[n_currect_com]->get_col()) {
               Robots[i] ->draw();
               setfillstyle(SOLID_FILL, Programms[n_currect_com]->get_col());
               bar(n_currect_com*122,500, n_currect_com*122+130, 549);
            }
         break;
      case '3':
         if (Programms.size() <3)
            break;
         cout << "Выбрана программа 3"<<endl;
         n_currect_com = 2;
         clearWin();
         highlightCell(current_cell);
         Programms[n_currect_com]->draw();
         for (int i = 0; i < Robots.size(); i++)
            if (Robots[i]->get_color() == Programms[n_currect_com]->get_col()) {
               Robots[i] ->draw();
               setfillstyle(SOLID_FILL, Programms[n_currect_com]->get_col());
               bar(n_currect_com*122,500, n_currect_com*122+130, 549);
            }
         break;
      case '4':
         if (Programms.size() <4)
            break;
         cout << "Выбрана программа 4"<<endl;
         n_currect_com = 3;
         clearWin();
         highlightCell(current_cell);
         Programms[n_currect_com]->draw();
         for (int i = 0; i < Robots.size(); i++)
            if (Robots[i]->get_color() == Programms[n_currect_com]->get_col()) {
               Robots[i] ->draw();
               setfillstyle(SOLID_FILL, Programms[n_currect_com]->get_col());
               bar(n_currect_com*122,500, n_currect_com*122+130, 549);
            }
         break;
      //выбор комманды
      case KEY_ENTER:

         break;
      // удаление объкта
      case KEY_DELETE:

         break;
      //отмена удаления
      case KEY_BACKSPACE:

         break;
      //закрытие
      case KEY_ESC:
         closegraph();
         return 0;
      }
   }
}