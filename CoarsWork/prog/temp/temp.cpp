




#define POS2CORD(x) 100*x

using namespace std;

vector <Robot *> Robots; // ���������� ������ � ��������
vector <Programm *> Programms; // ���������� ������ � �����������

void clearWin() {
   putimage(0, 0, loadBMP("inteface.bmp"), COPY_PUT);
}

void reDraw() { // ����������� ����
   putimage(0, 0, loadBMP("inteface.bmp"), COPY_PUT);
   for (int i = 0; i < Programms.size(); i++){
      Programms[i]->draw();
      setfillstyle(SOLID_FILL, _abracadabra_cast(*(Programms[i]));