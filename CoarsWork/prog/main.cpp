#include <iostream>
#include <vector>
#include "Objects.hpp"
#include "graphics.h"

#define POS2CORD(x) 100*x

using namespace std;

vector <Robot *> Robots; // ���������� ������ � ��������
vector <Programm *> Programms; // ���������� ������ � �����������

Field field(WIDTH_I, HEIGHT_J); //�������� ������� ����


void clearWin() {
   putimage(0, 0, loadBMP("inteface.bmp"), COPY_PUT);
}

void put_text(string text_task) {
   setbkcolor(NO_COLOR);
   setcolor(BLACK);
   const char *cstr = text_task.c_str();
   settextstyle(GOTHIC_FONT, HORIZ_DIR, 12);
   outtextxy(510, 60, cstr);
}

void reDraw(string text_task) { // ����������� ����
   clearWin(); // ������������ ������ ���
   // ������� ����� �������
   put_text(text_task);
   
   field.draw();
   // ������������ ���������� � �������
   for (int i = 0; i < Programms.size(); i++) {
      Programms[i]->draw();
      setcolor(BLACK);
      int heightB = 125;
      rectangle(i*heightB,500, i*heightB+122, 549);
      setfillstyle(SOLID_FILL, Programms[i]->get_col());
      bar(i*heightB,500, i*heightB+122, 549);
   }
   for (int i = 0; i < Robots.size(); i++)
      Robots[i]->draw();
}

void highlightCell(position current_cell) { // ��������� ������
   setlinestyle(0, 1, 3);
   setcolor(YELLOW);
   rectangle(POS2CORD(current_cell.x), POS2CORD(current_cell.y), POS2CORD(current_cell.x+100), POS2CORD(current_cell.y+100));
}


void drawCurrectProg(int n_currect_com, position current_cell) {
   clearWin();
   highlightCell(current_cell);
   Programms[n_currect_com]->draw();
   field.draw();
   for (int i = 0; i < Robots.size(); i++)
      if (Robots[i]->get_color() == Programms[n_currect_com]->get_col()) {1
         Robots[i]->draw();
         int heightB = 125;
         setcolor(BLACK);
         rectangle(n_currect_com*heightB,500, n_currect_com*heightB+122, 549);
         setfillstyle(SOLID_FILL, Programms[n_currect_com]->get_col());
         bar(n_currect_com*heightB,500, n_currect_com*heightB+122, 549);
      }
}


int n_currect_com = 0;

int main() {
   initwindow(800, 550, "��������� ��� �������� ����������������");
   clearWin();

   position current_cell(0, 0); // ������� ������� ������

   Task task("tast_list.txt");

   task.initialize(field, Robots, Programms); //������������� ������� � ��������
   string text_task = task.get_text_task(); // ��������� ������ �������
   task.prepare_field(field); // ���������� ���� � ������������ ��������
   highlightCell(current_cell); // ����������� ������� ������
   while (1) {

      //����� ������� ������
      switch (getch(kbhit())) {
      case KEY_UP:
         reDraw(text_task);
         current_cell.y += (current_cell.y == 0) ? 0 : -1;
         highlightCell(current_cell);
         break;
      case KEY_DOWN:
         reDraw(text_task);
         current_cell.y += (current_cell.y == HEIGHT_J-1) ? 0 : 1;
         highlightCell(current_cell);
         break;
      case KEY_LEFT:
         reDraw(text_task);
         current_cell.x += (current_cell.x == 0) ? 0 : -1;
         highlightCell(current_cell);
         break;
      case KEY_RIGHT:
         reDraw(text_task);
         current_cell.x += (current_cell.x == WIDTH_I-1) ? 0 : 1;
         highlightCell(current_cell);
         break;

      // ����������� �������� ������ ������������ �����
      case '1':
         cout << "������� ��������� 1"<<endl;
         n_currect_com = 0;
         drawCurrectProg(n_currect_com, current_cell);
         put_text(text_task);
         break;
      case '2':
         if (Programms.size() <2)
            break;
         cout << "������� ��������� 2"<<endl;
         n_currect_com = 1;
         drawCurrectProg(n_currect_com, current_cell);
         put_text(text_task);
         break;
      case '3':
         if (Programms.size() <3)
            break;
         cout << "������� ��������� 3"<<endl;
         n_currect_com = 2;
         drawCurrectProg(n_currect_com, current_cell);
         put_text(text_task);
         break;
      case '4':
         if (Programms.size() <4)
            break;
         cout << "������� ��������� 4"<<endl;
         n_currect_com = 3;
         drawCurrectProg(n_currect_com, current_cell);
         put_text(text_task);
         break;
      //����� ��������
      case KEY_ENTER:
         
         break;
      // �������� ������
      case KEY_DELETE:

         break;
      // ������ ���������
      case KEY_TAB:
         // ����������� �������
         for (int i = 0; i < Robots.size(); i++){
            position new_pos = Robots[i]->get_cordinat();
            new_pos.x += Robots[i]->get_direction().x;
            new_pos.y += Robots[i]->get_direction().y;
            Robots[i]->set_cordinat(new_pos);
            Robots[i]->draw();
            reDraw(text_task);
         }
      break;
      //������ ��������
      case KEY_BACKSPACE:

         break;
      //��������
      case KEY_ESC:
         closegraph();
         return 0;
      }
   }
}