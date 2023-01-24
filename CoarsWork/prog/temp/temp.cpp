




#define POS2CORD(x) 100*x

using namespace std;

vector <Robot *> Robots; // ���������� ������ � ��������
vector <Programm *> Programms; // ���������� ������ � �����������

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
   for (int i = 0; i < Robots.size(); i++)
      if (Robots[i]->get_color() == Programms[n_currect_com]->get_col()) {
         
         _abracadabra_cast(*(Robots[i]));