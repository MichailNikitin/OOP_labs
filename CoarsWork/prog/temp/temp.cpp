




#define POS2CORD(x) 100*x

using namespace std;

vector <Robot *> Robots; // глобальный вектор с роботами
vector <Programm *> Programms; // глобальный вектор с программами

int main() {
   initwindow(800, 550, "Программа для обучения программированию");
   putimage(0, 0, loadBMP("inteface.bmp"), COPY_PUT);

   position current_cell(0, 0);

   Field field(WIDTH_I, HEIGHT_J);

   Task task("tast_list.txt");
   task.initialize(field, Robots, Programms);
   task.prepare_field(field);
   setlinestyle(0, 1, 3);
   setcolor(YELLOW);
   rectangle(POS2CORD(current_cell.x), POS2CORD(current_cell.y), POS2CORD(current_cell.x+100), POS2CORD(current_cell.y+100));

   while (1) {
      switch (getch(kbhit())) {
      case KEY_UP:
         reDraw();
         current_cell.y += (current_cell.y == 0) ? 0 : -1;
         setcolor(YELLOW);
         rectangle(POS2CORD(current_cell.x), POS2CORD(current_cell.y), POS2CORD(current_cell.x+100), POS2CORD(current_cell.y+100));
         break;
      case KEY_DOWN:
         reDraw();
         current_cell.y += (current_cell.y == HEIGHT_J-1) ? 0 : 1;
         setcolor(YELLOW);
         rectangle(POS2CORD(current_cell.x), POS2CORD(current_cell.y), POS2CORD(current_cell.x+100), POS2CORD(current_cell.y+100));
         break;
      case KEY_LEFT:
         reDraw();
         current_cell.x += (current_cell.x == 0) ? 0 : -1;
         setcolor(YELLOW);
         rectangle(POS2CORD(current_cell.x), POS2CORD(current_cell.y), POS2CORD(current_cell.x+100), POS2CORD(current_cell.y+100));
         break;
      case KEY_RIGHT:
         reDraw();
         current_cell.x += (current_cell.x == WIDTH_I-1) ? 0 : 1;
         setcolor(YELLOW);
         rectangle(POS2CORD(current_cell.x), POS2CORD(current_cell.y), POS2CORD(current_cell.x+100), POS2CORD(current_cell.y+100));
         break;

      case '1':
         cout << "111111111111111111111111111111111"<<endl;
         break;
      case '2':
         if (_abracadabra_cast(Programms);