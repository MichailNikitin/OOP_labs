





using namespace std;

vector <Robot *> Robots; // ���������� ������ � ��������
vector <Programm *> Programms; // ���������� ������ � �����������

int main() {
   initwindow(800, 550, "��������� ��� �������� ����������������");
   putimage(0, 0, loadBMP("inteface.bmp"), COPY_PUT);

   position current_cell(0, 0);

   Field field(WIDTH_I, HEIGHT_J);

   //Task task("tast_list.txt", field, Robots, Programms);

   _abracadabra_cast(Robots);