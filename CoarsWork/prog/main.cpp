#include "Objects.hpp"

using namespace std;

vector <Robot *> Robots; // глобальный вектор с роботами
vector <Programm *> Programms; // глобальный вектор с программами

Field field(WIDTH_I, HEIGHT_J); //создание объекта поля

//очистка окна
void clearWin() {
   putimage(0, 0, loadBMP("inteface.bmp"), COPY_PUT);
}

//вставка текста задания
void put_text(string text_task) {
   setbkcolor(NO_COLOR);
   setcolor(BLACK);
   vector <string> text_write;
   string word;
   stringstream s(text_task);
   while (s >> word) text_write.push_back(word);
   int lenght = 0, j=0;
   lenght += textwidth(text_write[0].c_str())+textwidth(" ");
   outtextxy(510, 60, text_write[0].c_str());
   for (int i=1; i<text_write.size(); i++) {
      lenght+=textwidth(" ");
      if (lenght<280) {
         outtextxy(510+lenght, 60+j*(textheight("T")+5), text_write[i].c_str());
         lenght += textwidth(text_write[i].c_str())+textwidth(" ");
      }
      else {
         lenght = 0;
         j++;
         outtextxy(510+lenght, 60+j*(textheight("T")+5), text_write[i].c_str());
         lenght += textwidth(text_write[i].c_str())+textwidth(" ");
      }
   }
}

//отрисовка индикатора выбранной программы в нижней панели
void drawBarCurrectProg(int i) {
   setcolor(BLACK);
   int heightB = 125;
   rectangle(i*heightB,500, i*heightB+122, 549);
   setfillstyle(SOLID_FILL, Programms[i]->get_col());
   bar(i*heightB,501, i*heightB+122, 549);
}

// перерисовка всех элементов во время выполнения программы роботами
void reDraw(string text_task) {
   clearWin(); // отрисовка заднего фона
   // вывод текста задания
   put_text(text_task);
   // перерисовка объектов на поле
   field.draw();
   // отрисовка программмы и роботов
   for (int i = 0; i < Programms.size(); i++) {
      Programms[i]->draw();
      drawBarCurrectProg(i);
   }
   for (int i = 0; i < Robots.size(); i++)
      Robots[i]->draw();
}

// выделение ячейки
void highlightCell(position current_cell) {
   setlinestyle(0, 1, 3);
   setcolor(YELLOW);
   rectangle(100*current_cell.x, 100*current_cell.y, 100*current_cell.x+100, 100*current_cell.y+100);
}

//отрисовка текущей программы
void drawCurrectProg(int n_currect_com, position current_cell) {
   clearWin();
   Programms[n_currect_com]->draw();
   field.draw();
   drawBarCurrectProg(n_currect_com);
   for (int i = 0; i < Robots.size(); i++)
      if (Robots[i]->get_color() == Programms[n_currect_com]->get_col()) {
         Robots[i]->draw();
      }
}

int n_currect_com = 0; // номер текущей программы

int main() {
   initwindow(800, 550, "Программа для обучения программированию");
   clearWin();

   position current_cell(0, 0); // позиция текущей клетки

   Task task("tast_list.txt"); // сохранение названия файла с заданием
   task.prepare_field(field); // подготовка поля с расстановкой объектов
restart:
   task.initialize(field, Robots, Programms); //инициализация роботов и программ
   string text_task = task.get_text_task(); // получение текста задания
   highlightCell(current_cell); // отображение текущей ячейки
   while (1) {
      //выбор текущей клетки
fixing:
      switch (getch()) {
      case KEY_UP: {
            drawCurrectProg(n_currect_com, current_cell);
            current_cell.y += (current_cell.y == 0) ? 0 : -1;
            highlightCell(current_cell);
            put_text(text_task);
            break;
         }
      case KEY_DOWN: {
            drawCurrectProg(n_currect_com, current_cell);
            current_cell.y += (current_cell.y == HEIGHT_J-1) ? 0 : 1;
            highlightCell(current_cell);
            put_text(text_task);
            break;
         }
      case KEY_LEFT: {
            drawCurrectProg(n_currect_com, current_cell);
            current_cell.x += (current_cell.x == 0) ? 0 : -1;
            highlightCell(current_cell);
            put_text(text_task);
            break;
         }
      case KEY_RIGHT: {
            drawCurrectProg(n_currect_com, current_cell);
            current_cell.x += (current_cell.x == WIDTH_I-1) ? 0 : 1;
            highlightCell(current_cell);
            put_text(text_task);
            break;
         }
      // отображение программ только определённого цвета
      case '1': {
            cout << "Выбрана программа 1"<<endl;
            n_currect_com = 0;
            drawCurrectProg(n_currect_com, current_cell);
            put_text(text_task);
            break;
         }
      case '2':
         if (Programms.size() <2)
            break;
         cout << "Выбрана программа 2"<<endl;
         n_currect_com = 1;
         drawCurrectProg(n_currect_com, current_cell);
         put_text(text_task);
         break;
      case '3': {
            if (Programms.size() <3)
               break;
            cout << "Выбрана программа 3"<<endl;
            n_currect_com = 2;
            drawCurrectProg(n_currect_com, current_cell);
            put_text(text_task);
            break;
         }
      case '4': {
            if (Programms.size() <4)
               break;
            cout << "Выбрана программа 4"<<endl;
            n_currect_com = 3;
            drawCurrectProg(n_currect_com, current_cell);
            put_text(text_task);
            break;
         }
      //выбор команды или робота
      case KEY_ENTER: {
            Command *com = Programms[n_currect_com]->select(current_cell);
            if (com != nullptr && com->get_allow_pos()) {
               while (1) {
                  switch (getch()) {
                  case KEY_UP: {
                        current_cell.y += (current_cell.y == 0) ? 0 : -1;
                        com->set_pos(current_cell);
                        drawCurrectProg(n_currect_com, current_cell);
                        put_text(text_task);
                        highlightCell(current_cell);
                        break;
                     }
                  case KEY_DOWN: {
                        current_cell.y += (current_cell.y == HEIGHT_J-1) ? 0 : 1;
                        com->set_pos(current_cell);
                        drawCurrectProg(n_currect_com, current_cell);
                        put_text(text_task);
                        highlightCell(current_cell);
                        break;
                     }
                  case KEY_LEFT: {
                        current_cell.x += (current_cell.x == 0) ? 0 : -1;
                        com->set_pos(current_cell);
                        drawCurrectProg(n_currect_com, current_cell);
                        put_text(text_task);
                        highlightCell(current_cell);
                        break;
                     }
                  case KEY_RIGHT: {
                        current_cell.x += (current_cell.x == WIDTH_I-1) ? 0 : 1;
                        com->set_pos(current_cell);
                        drawCurrectProg(n_currect_com, current_cell);
                        put_text(text_task);
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
                  if (current_cell == Robots[i]->get_pos()) {
                     while (1) {
                        switch (getch()) {
                        case KEY_UP: {
                              current_cell.y += (current_cell.y == 0) ? 0 : -1;
                              Robots[i]->set_pos(current_cell);
                              drawCurrectProg(n_currect_com, current_cell);
                              put_text(text_task);
                              highlightCell(current_cell);
                              break;
                           }
                        case KEY_DOWN: {
                              current_cell.y += (current_cell.y == HEIGHT_J-1) ? 0 : 1;
                              Robots[i]->set_pos(current_cell);
                              drawCurrectProg(n_currect_com, current_cell);
                              put_text(text_task);
                              highlightCell(current_cell);
                              break;
                           }
                        case KEY_LEFT: {
                              current_cell.x += (current_cell.x == 0) ? 0 : -1;
                              Robots[i]->set_pos(current_cell);
                              drawCurrectProg(n_currect_com, current_cell);
                              put_text(text_task);
                              highlightCell(current_cell);
                              break;
                           }
                        case KEY_RIGHT: {
                              current_cell.x += (current_cell.x == WIDTH_I-1) ? 0 : 1;
                              Robots[i]->set_pos(current_cell);
                              drawCurrectProg(n_currect_com, current_cell);
                              put_text(text_task);
                              highlightCell(current_cell);
                              break;
                           }

                        case 'w': {
                              Robots[i]->set_direction(position(0, -1));
                              drawCurrectProg(n_currect_com, current_cell);
                              put_text(text_task);
                              highlightCell(current_cell);
                              break;
                           }
                        case 'a': {
                              Robots[i]->set_direction(position(-1, 0));
                              drawCurrectProg(n_currect_com, current_cell);
                              put_text(text_task);
                              highlightCell(current_cell);
                              break;
                           }
                        case 's': {
                              Robots[i]->set_direction(position(0, 1));
                              drawCurrectProg(n_currect_com, current_cell);
                              put_text(text_task);
                              highlightCell(current_cell);
                              break;
                           }
                        case 'd': {
                              Robots[i]->set_direction(position(1, 0));
                              drawCurrectProg(n_currect_com, current_cell);
                              put_text(text_task);
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
      // удаление объекта
      case KEY_DELETE: {
            Command *com = Programms[n_currect_com]->select(current_cell);
            if (com != nullptr) {
               Programms[n_currect_com]->delete_com(com);
               drawCurrectProg(n_currect_com, current_cell);
            }
            break;
         }
      // запуск программы
      case KEY_TAB: {
            while (1) {
               for (int i = 0; i < Robots.size(); i++) {
                  position n_pos_rob = position(Robots[i]->get_pos().x + Robots[i]->get_direction().x, Robots[i]->get_pos().y + Robots[i]->get_direction().y);
                  if (Robots[i]->is_crash(Robots) ||(field.get_object(n_pos_rob) != nullptr) && typeid(*field.get_object(n_pos_rob)) == typeid(Tree)) {
                     clearWin();
                     put_text("Столкновение! Повторите попытку ещё раз!");
                     delay(3000);

                     Robots.clear();
                     Programms.clear();
                     goto restart;
                  }
               }
               // перемещение роботов
               for (int i = 0; i < Robots.size(); i++) {
                  auto r = Robots[i];
                  position new_pos = r->get_pos();
                  new_pos.x += r->get_direction().x;
                  new_pos.y += r->get_direction().y;
                  r->set_pos(new_pos);
                  r->draw();

                  if (field.get_object(r->get_pos()) != nullptr) {
                     if (typeid(* field.get_object(r->get_pos())) == typeid(Fruit)) {
                        r->change_Field(field);
                     }
                  }
                  int colorRobot = r->get_color() ;
                  int colorIndexRobot = r->get_n_color() ;
                  int colorProgramm = Programms[r->get_n_color()]->get_col() ;

                  for (int n_prog = 0; n_prog < Programms.size(); n_prog++)
                     if (r->get_color() == Programms[n_prog]->get_col()) {
                        Command *com = Programms[n_prog]->select(r->get_pos());
                        if (com != nullptr) {
                           com->use(*r);
                        }
                     }
                  reDraw(text_task);
               }

               if (task.is_task_completed(field, Robots)) {
                  clearWin();
                  put_text("Поздравлем! Задание выполненно! Продолжайте совершенствовать свои навыки в программировании, чтобы потом написать такую же увлекательную игру");
                  delay(3000);
                  Robots.clear();
                  Programms.clear();
                  goto restart;
               }
               
               delay(1000);
            }
            break;
         }
      // возврат в изначальное состояние
      case KEY_BACKSPACE: {
            Robots.clear();
            Programms.clear();
            task.initialize(field, Robots, Programms);
            drawCurrectProg(n_currect_com, current_cell);
            put_text(text_task);
            highlightCell(current_cell);
         }
         break;
      //закрытие
      case KEY_ESC:
         closegraph();
         return 0;
      }
   }
}