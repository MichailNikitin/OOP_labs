




#define POS2CORD(x) 100*x

using namespace std;

vector <Robot *> Robots; // глобальный вектор с роботами
vector <Programm *> Programms; // глобальный вектор с программами

void clearWin() {
   putimage(0, 0, loadBMP("inteface.bmp"), COPY_PUT);
}

void reDraw() { // перерисовка поля
   putimage(0, 0, loadBMP("inteface.bmp"), COPY_PUT);
   for (int i = 0; i < Programms.size(); i++){
      Programms[i]->draw();
      setfillstyle(SOLID_FILL, _abracadabra_cast(*(Programms[i]));