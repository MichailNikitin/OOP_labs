





using namespace std;

vector <Robot *> Robots; // глобальный вектор с роботами
vector <Programm *> Programms; // глобальный вектор с программами

int main() {
   initwindow(800, 550, "Программа для обучения программированию");
   putimage(0, 0, loadBMP("inteface.bmp"), COPY_PUT);

   position current_cell(0, 0);

   Field field(WIDTH_I, HEIGHT_J);

   //Task task("tast_list.txt", field, Robots, Programms);

   _abracadabra_cast(Robots);