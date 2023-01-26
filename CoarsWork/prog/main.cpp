#include "Objects.hpp"

using namespace std;

vector <Robot *> Robots; // ���������� ������ � ��������
vector <Programm *> Programms; // ���������� ������ � �����������

Field field(WIDTH_I, HEIGHT_J); //�������� ������� ����

//������� ����
void clearWin() {
   putimage(0, 0, loadBMP("inteface.bmp"), COPY_PUT);
}

//������� ������ �������
void put_text(string text_task) {
   setbkcolor(NO_COLOR);
   setcolor(BLACK);
   const char *cstr = text_task.c_str();
   settextstyle(GOTHIC_FONT, HORIZ_DIR, 12);
   outtextxy(510, 60, cstr);
}

//��������� ���������� ��������� ��������� � ������ ������
void drawBarCurrectProg(int i) {
   setcolor(BLACK);
   int heightB = 125;
   rectangle(i*heightB,500, i*heightB+122, 549);
   setfillstyle(SOLID_FILL, Programms[i]->get_col());
   bar(i*heightB,501, i*heightB+122, 549);
}

// ����������� ���� ��������� �� ����� ���������� ��������� ��������
void reDraw(string text_task) {
   clearWin(); // ������������ ������ ���
   // ������� ����� �������
   put_text(text_task);
   //���������� �������� �� ����
   field.draw();
   // ������������ ���������� � �������
   for (int i = 0; i < Programms.size(); i++) {
      Programms[i]->draw();
      drawBarCurrectProg(i);
   }
   for (int i = 0; i < Robots.size(); i++)
      Robots[i]->draw();
}

// ��������� ������
void highlightCell(position current_cell) {
   setlinestyle(0, 1, 3);
   setcolor(YELLOW);
   rectangle(100*current_cell.x, 100*current_cell.y, 100*current_cell.x+100, 100*current_cell.y+100);
}

//�������� ������� ���������
void drawCurrectProg(int n_currect_com, position current_cell) {
   clearWin();
   Programms[n_currect_com]->draw();
   field.draw();
   for (int i = 0; i < Robots.size(); i++)
      if (Robots[i]->get_color() == Programms[n_currect_com]->get_col()) {
         Robots[i]->draw();
         drawBarCurrectProg(n_currect_com);
      }
}

int n_currect_com = 0; //����� ������� ���������

int main() {
   initwindow(800, 550, "��������� ��� �������� ����������������");
   clearWin();

   position current_cell(0, 0); // ������� ������� ������

   Task task("tast_list.txt"); // ���������� �������� ����� � ��������
   task.prepare_field(field); // ���������� ���� � ������������ ��������
restart:
   task.initialize(field, Robots, Programms); //������������� ������� � ��������
   string text_task = task.get_text_task(); // ��������� ������ �������
   highlightCell(current_cell); // ����������� ������� ������
   while (1) {
      //����� ������� ������
fixing:
      switch (getch()) {
      case KEY_UP: {
            drawCurrectProg(n_currect_com, current_cell);
            current_cell.y += (current_cell.y == 0) ? 0 : -1;
            highlightCell(current_cell);
            break;
         }
      case KEY_DOWN: {
            drawCurrectProg(n_currect_com, current_cell);
            current_cell.y += (current_cell.y == HEIGHT_J-1) ? 0 : 1;
            highlightCell(current_cell);
            break;
         }
      case KEY_LEFT: {
            drawCurrectProg(n_currect_com, current_cell);
            current_cell.x += (current_cell.x == 0) ? 0 : -1;
            highlightCell(current_cell);
            break;
         }
      case KEY_RIGHT: {
            drawCurrectProg(n_currect_com, current_cell);
            current_cell.x += (current_cell.x == WIDTH_I-1) ? 0 : 1;
            highlightCell(current_cell);
            break;
         }
      // ����������� �������� ������ ������������ �����
      case '1': {
            cout << "������� ��������� 1"<<endl;
            n_currect_com = 0;
            drawCurrectProg(n_currect_com, current_cell);
            put_text(text_task);
            break;
         }
      case '2':
         if (Programms.size() <2)
            break;
         cout << "������� ��������� 2"<<endl;
         n_currect_com = 1;
         drawCurrectProg(n_currect_com, current_cell);
         put_text(text_task);
         break;
      case '3': {
            if (Programms.size() <3)
               break;
            cout << "������� ��������� 3"<<endl;
            n_currect_com = 2;
            drawCurrectProg(n_currect_com, current_cell);
            put_text(text_task);
            break;
         }
      case '4': {
            if (Programms.size() <4)
               break;
            cout << "������� ��������� 4"<<endl;
            n_currect_com = 3;
            drawCurrectProg(n_currect_com, current_cell);
            put_text(text_task);
            break;
         }
      //����� �������� ��� ������
      case KEY_ENTER: {
            Command *com = Programms[n_currect_com]->select(current_cell);
            if (com != nullptr && com->get_allow_pos()) {
               while (1) {
                  switch (getch()) {
                  case KEY_UP: {
                        current_cell.y += (current_cell.y == 0) ? 0 : -1;
                        com->set_pos(current_cell);
                        drawCurrectProg(n_currect_com, current_cell);
                        highlightCell(current_cell);
                        break;
                     }
                  case KEY_DOWN: {
                        current_cell.y += (current_cell.y == HEIGHT_J-1) ? 0 : 1;
                        com->set_pos(current_cell);
                        drawCurrectProg(n_currect_com, current_cell);
                        highlightCell(current_cell);
                        break;
                     }
                  case KEY_LEFT: {
                        current_cell.x += (current_cell.x == 0) ? 0 : -1;
                        com->set_pos(current_cell);
                        drawCurrectProg(n_currect_com, current_cell);
                        highlightCell(current_cell);
                        break;
                     }
                  case KEY_RIGHT: {
                        current_cell.x += (current_cell.x == WIDTH_I-1) ? 0 : 1;
                        com->set_pos(current_cell);
                        drawCurrectProg(n_currect_com, current_cell);
                        highlightCell(current_cell);
                        break;
                     }
                  case KEY_ENTER: {
                        if (!Programms[n_currect_com]->is_collision())
                           goto fixing;
                        break;
                     }
                  }
               }
            }
            else {
               for (int i = 0; i < Robots.size(); i++) {
                  if (current_cell == Robots[i]->get_cordinat()) {
                     while (1) {
                        switch (getch()) {
                        case KEY_UP: {
                              current_cell.y += (current_cell.y == 0) ? 0 : -1;
                              Robots[i]->set_cordinat(current_cell);
                              drawCurrectProg(n_currect_com, current_cell);
                              highlightCell(current_cell);
                              break;
                           }
                        case KEY_DOWN: {
                              current_cell.y += (current_cell.y == HEIGHT_J-1) ? 0 : 1;
                              Robots[i]->set_cordinat(current_cell);
                              drawCurrectProg(n_currect_com, current_cell);
                              highlightCell(current_cell);
                              break;
                           }
                        case KEY_LEFT: {
                              current_cell.x += (current_cell.x == 0) ? 0 : -1;
                              Robots[i]->set_cordinat(current_cell);
                              drawCurrectProg(n_currect_com, current_cell);
                              highlightCell(current_cell);
                              break;
                           }
                        case KEY_RIGHT: {
                              current_cell.x += (current_cell.x == WIDTH_I-1) ? 0 : 1;
                              Robots[i]->set_cordinat(current_cell);
                              drawCurrectProg(n_currect_com, current_cell);
                              highlightCell(current_cell);
                              break;
                           }
                        case KEY_ENTER: {
                              if (!Robots[i]->is_collision(field, Robots))
                                 goto fixing;
                              break;
                           }
                        }
                     }
                  }
               }
            }
            break;
         }
      // �������� ������
      case KEY_DELETE: {
            Command *com = Programms[n_currect_com]->select(current_cell);
            if (com != nullptr) {
               Programms[n_currect_com]->delete_com(com);
               drawCurrectProg(n_currect_com, current_cell);
            }
            break;
         }
      // ������ ���������
      case KEY_TAB: {

            for (int i = 0; i < Robots.size(); i++) {
               position n_pos_rob = position(Robots[i]->get_cordinat().x + Robots[i]->get_direction().x, Robots[i]->get_cordinat().y + Robots[i]->get_direction().y);
               if (Robots[i]->is_crash(Robots) || typeid(field.get_object(n_pos_rob)) == typeid(Tree)) {
                  put_text("������������!");
                  delay(3000);
                  clearWin();
                  Robots.clear();
                  Programms.clear();
                  goto restart;
               }
            }
            // ����������� �������
            for (int i = 0; i < Robots.size(); i++) {
               auto r = Robots[i];
               position new_pos = r->get_cordinat();
               new_pos.x += r->get_direction().x;
               new_pos.y += r->get_direction().y;
               r->set_cordinat(new_pos);
               r->draw();
               if (typeid(field.get_object(r->get_cordinat())) == typeid(Fruit)) {
                  field.delete_obj(r->get_cordinat());
                  field.draw();
               }
               Command *com = Programms[r->get_color()]->select(current_cell);
               if (com != nullptr)
                  com->use(*r);

               reDraw(text_task);
            }

            break;
         }
      // ������� � ����������� ���������
      case KEY_BACKSPACE: {
            Robots.clear();
            Programms.clear();
            task.initialize(field, Robots, Programms);
            drawCurrectProg(n_currect_com, current_cell);
            highlightCell(current_cell);
         }
         break;
      //��������
      case KEY_ESC:
         closegraph();
         return 0;
      }
   }
}