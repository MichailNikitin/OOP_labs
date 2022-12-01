#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <algorithm>
#include <graphics.h>
#include <conio.h>

using namespace std;

class Figure{
   int c; // цвет
   bool visible;

protected:
   int x, y; // базовая точка
   virtual void draw() = 0; //нарисовать

public:
   Figure(int c, int x, int y) : c(c), x(x), y(y), visible(0) {};
//конструктор
   virtual ~Figure() {}; //деструктор
   void move(int x, int y); // сместить фигуру в точку (x,y)
   void setcolor(int c); // установить цвет фигуры
   int getcolor() const{
       return c;
       
   } // получить цвет
   void hide(); // спрятать
   void show(); // показать
   bool isvisible() const{
       return visible;
       
   } // видима
   virtual void area(int &x1, int &y1, int &x2, int &y2) const = 0;
// получить размеры прямоугольной области, содержащей фигуру
};

class Square34 : public Figure{

protected:
   int length; // длина стороны
   int N;// номер сектора
   void draw(); //нарисовать

public:
   Square34(int c, int x, int y, int length, int N) : Figure(c, x,
            y), length(length), N(N) {}; //конструктор
   ~Square34(){
       hide();
       
   } //деструктор
   void area(int &x1, int &y1, int &x2, int &y2) const; //размеры прямоугольной области, содержащей фигуру
   void setsizes(int length); //изменить размер
};

class FillSquare34 : public Square34{

protected:
   int fillColor; // цвет закраски
   void draw(); // рисовать

public:
   FillSquare34(int c, int x, int y, int length, int N, int
                fillColor) : Square34(c, x, y, length, N), fillColor(fillColor) {};
//конструктор
   void setfillcolor(int c);//изменить цвет закраски
};

void Figure::setcolor(int c){
   this->c = c;
   if (visible) draw();
}
void Figure::move(int x, int y){
   bool f = visible;
   if (f) hide();
   this->x = x;
   this->y = y;
   if (f) show();
}
void Figure::hide(){
   if (visible == 0)
       return;
   int x1, y1, x2, y2;
   area(x1, y1, x2, y2);
   setfillstyle(SOLID_FILL, BLACK);
   bar(x1, y1, x2, y2);
   visible = 0;
}
void Figure::show(){
   if (visible == 1)
       return;
   visible = 1;
   draw();
}
void Square34::draw(){
   ::setcolor(getcolor());
   int pos[18];
   pos[0] = x + length / 2;
   pos[1] = y;
   if (N == 4){
      pos[2] = x;
      pos[3] = y;
   }
   else{
      pos[2] = x + length / 2;
      pos[3] = y + length / 2;
   }
   pos[4] = x;
   pos[5] = y + length / 2;
   if (N == 3){
      pos[6] = x;
      pos[7] = y;
   }
   else{
      pos[6] = x - length / 2;
      pos[7] = y + length / 2;
   }
   pos[8] = x - length / 2;
   pos[9] = y;
   if (N == 2){
      pos[10] = x;
      pos[11] = y;
   }
   else{
      pos[10] = x - length / 2;
      pos[11] = y - length / 2;
   }
   pos[12] = x;
   pos[13] = y - length / 2;
   if (N == 1){
      pos[14] = x;
      pos[15] = y;
   }
   else{
      pos[14] = x + length / 2;
      pos[15] = y - length / 2;
   }
   pos[16] = x + length / 2;
   pos[17] = y;
   drawpoly(9, pos);
}
void Square34::area(int &x1, int &y1, int &x2, int &y2) const{
   x1 = x - length / 2;
   x2 = x + length / 2;
   y1 = y - length / 2;
   y2 = y + length / 2;
}
void Square34::setsizes(int length){
   bool vsbl = isvisible();
   if (vsbl) hide();
   this->length = length;
   if (vsbl) show();
}
void FillSquare34::setfillcolor(int c){
   fillColor = c;
   if (isvisible()) draw();
}
void FillSquare34::draw(){
   setfillstyle(SOLID_FILL, fillColor);
   int pos[18];
   pos[0] = x + length / 2;
   pos[1] = y;
   if (N == 4){
      pos[2] = x;
      pos[3] = y;
   }
   else {
      pos[2] = x + length / 2;
      pos[3] = y + length / 2;
   }
   pos[4] = x;
   pos[5] = y + length / 2;
   if (N == 3){
      pos[6] = x;
      pos[7] = y;
   }
   else{
      pos[6] = x - length / 2;
      pos[7] = y + length / 2;
   }
   pos[8] = x - length / 2;
   pos[9] = y;
   if (N == 2){
      pos[10] = x;
      pos[11] = y;
   }
   else{
      pos[10] = x - length / 2;
      pos[11] = y - length / 2;
   }
   pos[12] = x;
   pos[13] = y - length / 2;
   if (N == 1){
      pos[14] = x;
      pos[15] = y;
   }
   else{
      pos[14] = x + length / 2;
      pos[15] = y - length / 2;
   }
   pos[16] = x + length / 2;
   pos[17] = y;
   Square34::draw();
   fillpoly(9, pos);
}

int main(){
   initwindow(1080, 820);
   Figure *figure1 = new Square34(WHITE, 200, 200, 100, 3);
   Figure *figure2 = new FillSquare34(LIGHTBLUE, 700, 150, 200, 3, LIGHTGREEN);
   figure1->show();
   figure2->show();
   getch();
   figure1->hide();
   figure2->hide();
   getch();
   figure1->move(400, 300);
   figure2->move(850, 600);
   figure1->show();
   figure2->show();
   getch();
   figure1->setcolor(LIGHTBLUE);
   figure2->setcolor(WHITE);
// проверяем изменение размеров, обе фигуры меняются
   if (Square34 *r = dynamic_cast<Square34 *>(figure1)) r->setsizes(150);
   if (Square34 *r = dynamic_cast<Square34 *>(figure2)) r->setsizes(300);
   getch();
// проверяем перекраску, первая фигура не должна измениться
   if (FillSquare34 *r = dynamic_cast<FillSquare34 *>(figure1)) r->setfillcolor(LIGHTRED);
   if (FillSquare34 *r = dynamic_cast<FillSquare34 *>(figure2)) r->setfillcolor(LIGHTCYAN);
   figure1->show();
   figure2->show();
   getch();
//проверяем исчезновение с экрана при удалении
   delete figure1;
   delete figure2;
   getch();
   return 0;
}
