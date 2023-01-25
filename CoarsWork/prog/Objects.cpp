#include "Objects.hpp"

constexpr int color_prog[4] = {RED, GREEN, BLUE, YELLOW};
vector<position> places_taken;

using namespace std;

int direct2grad(position direct) {
   if (direct.x == -1)
      return 270;
   if (direct.y == 1)
      return 180;
   if (direct.y == -1)
      return 90;
   else
      return 0;
}

Robot::Robot(IMAGE *image, bool direction, bool cordinat):img(image), allow_change_direction(direction), allow_change_cordinat(cordinat) {}
Robot::~Robot() {freeimage(img);}

void Robot::set_cordinat(position new_pos) {

   pos = position(new_pos.x, new_pos.y);
}

void Robot::set_direction(position new_direction) {
   direction = position(new_direction.x, new_direction.y);
}

void Robot::set_color(int new_color) {color = new_color;}
int Robot::get_color() {return color;}
position Robot::get_cordinat() {return pos;}
position Robot::get_direction() {return direction;}

void Robot::change_Field(Field &Field) {


}

void Robot::draw() {
   IMAGE *rotImg = imageturn(img,  direct2grad(pos), WHITE);
   putimage(pos.x*100+5,pos.y*100+5, rotImg, COPY_PUT);
}
bool Robot::is_crash(std::vector <Robot *> &Robots) {
   //if (
   return 1;
}

Object::Object(IMAGE *image): img(image) {}
Object::Object(const Object &obj) {img = obj.img;}
Object::~Object() {freeimage(img);}

Fruit::Fruit(IMAGE *image): Object(image) {}
Fruit::~Fruit() {freeimage(img);}

Tree::Tree(IMAGE *image): Object(image) {}
Tree::~Tree() {freeimage(img);}

bool Fruit::is_access(Robot &current_robot) {return 1;}
void Fruit::draw(position pos) {return putimage(pos.x, pos.y, img, COPY_PUT);}

bool Tree::is_access(Robot &current_robot) {return 0;}
void Tree::draw(position pos) { putimage(pos.x, pos.y, img, COPY_PUT);}


Field::Field(int w, int h):width(w), height(h),  fullField(width, vector<Cell>(height)) {}

void Field::set_obj(Object *obj, position pos) { // i, j
   fullField[pos.x][pos.y].current_object = obj;
}

void Field::delete_obj(position pos) { // i, j
   fullField[pos.x][pos.y].current_object = nullptr;
}

void Field::set_color(position pos, int color) { // i, j
   fullField[pos.x][pos.y].color = color;
}

Object *Field::get_object(position pos) {
   return fullField[pos.x][pos.y].current_object;
}

void Field::draw() {
   for (int i = 0; i < width; i++) {
      for (int j = 0; j < height; j++) {
         if (fullField[i][j].current_object != nullptr)
            fullField[i][j].current_object->draw(position(i*100+5, j*100+5));
      }
   }
}

Command::Command(bool is_change_cordinat, bool is_delete, position new_coord):
   is_allow_change_cordinat(is_change_cordinat), is_allow_delete(is_delete), coord(new_coord) {}

Command::Command(const Command &com) {
   is_allow_change_cordinat = com.is_allow_change_cordinat;
   is_allow_delete = com.is_allow_delete;
   coord = com.coord;
}
void Command::set_pos(position pos) {
   coord.x = pos.x;
   coord.y = pos.y;
}

position Command::get_pos() {return coord;}

Arrow::Arrow(bool is_change_cordinat, bool is_delete, position new_coord, position direction):
   Command(is_change_cordinat, is_delete, new_coord), orientation(direction) {}

ChangeColor::ChangeColor(bool is_change_cordinat, bool is_delete, position new_coord, int color):
   Command(is_change_cordinat, is_delete, new_coord), color(color) {}

Exit::Exit(bool is_change_cordinat, bool is_delete, position new_coord):
   Command(is_change_cordinat, is_delete, new_coord) {}

void Arrow::use(Robot &robot) {
   robot.set_direction(this->orientation);
}
void Arrow::draw(int col) {

   switch (col) {
   case RED:
      this->img = loadBMP("arrow_red.bmp");
      break;
   case BLUE:
      this->img = loadBMP("arrow_blue.bmp");
      break;
   case GREEN:
      this->img = loadBMP("arrow_green.bmp");
      break;
   case YELLOW:
      this->img = loadBMP("arrow_yellow.bmp");
      break;
   default:
      this->img = loadBMP("arrow_white.bmp");
   }
   IMAGE *rotImg = imageturn(this->img,  direct2grad(orientation), WHITE);
   putimage(coord.x*100+10,coord.y*100+10, rotImg, COPY_PUT);
}

void ChangeColor::use(Robot &robot) {
   robot.set_color(this->color);
}
void ChangeColor::draw(int col) {
   //cout <<"coord = ("<< coord.x <<", "<< coord.y<<")\n";
   setcolor(BLACK);
   setfillstyle(SOLID_FILL, col);
   bar(coord.x*100+25, coord.y*100+10, coord.x*100+75, coord.y*100+90);
   setfillstyle(SOLID_FILL, color);
   fillellipse(coord.x*100+50, coord.y*100+50, 20, 20);
}

void Exit::use(Robot &robot) {
   Robots.erase(ranges::find(Robots, &robot));
}
void Exit::draw(int col) {
   switch (col) {
   case RED:
      this->img = loadBMP("wooden-crate_red.bmp");
      break;
   case BLUE:
      this->img = loadBMP("wooden-crate_blue.bmp");
      break;
   case GREEN:
      this->img = loadBMP("wooden-crate_green.bmp");
      break;
   case YELLOW:
      this->img = loadBMP("wooden-crate_yellow.bmp");
      break;
   default:
      this->img = loadBMP("wooden-crate_white.bmp");
   }
   putimage(coord.x*100+5, coord.x*100+5, img, COPY_PUT);
}

Programm::Programm(int c): color(c) {}
int Programm::get_col() {return color;}

void Programm::add(Command *command) {
   commands.push_back(command);
}

void Programm::draw() {
   for (int i = 0; i < commands.size(); i ++) {
      cout<< "color = " << color << ", ";
      commands[i]->draw(color);
   }
}

void Programm::delete_com(Command *com) {
   commands.erase(ranges::find(commands, com));
}

Command *Programm::select(position pos) {
   auto it =  find_if(commands.begin(), commands.end(), [pos](Command *com) -> bool {
      return com->get_pos() == pos;});
   if (it != commands.end())
      cout << "command is find\n";
   else
      cout << "command is't find\n";

}

Task::Task(const string file_name): name_taskFile(file_name) {}

void Task::initialize(Field &field, vector <Robot *> &Robots,vector <Programm *> &Programms) {
   ifstream file;
   setlocale(LC_ALL, "Russian");
   file.open(name_taskFile);

   getline(file, text_task);

   file >> count_robots >> count_commands;

   cout << text_task << endl;
   cout << count_robots<< " " << count_commands<< endl;

   for (int i = 0; i < count_robots; i++) {
      int r_x, r_y, r_color;
      int f_color, f_direct;
      string f_change_direct, f_change_coord;
      file >> r_x >> r_y;
      file >>f_color >> f_direct;
      file >> f_change_direct >> f_change_coord;
      cout << r_x << " " << r_y << " " << f_color << " "<< f_direct <<" "<< f_change_direct <<" "<< f_change_coord << endl;

      bool change_direct, change_coord;
      position direct;
      change_direct = (f_change_direct == "да"? true : false);
      change_coord = (f_change_coord == "да"? true : false);

      switch (f_direct) {
      case 0:
         direct = position(1, 0);
         break; // "вправ"
      case 1:
         direct = position(0, 1);
         break; //"вверх"
      case 2:
         direct = position(-1, 0);
         break; //"влево"
      case 3:
         direct = position(0, -1);
         break; //"вниз"

      }
      char name_image[7];
      snprintf(name_image, sizeof(name_image), "r%d.bmp",f_color);
      Robot *new_robot = new Robot(loadBMP(name_image),change_direct, change_coord);
      new_robot->set_color(color_prog[f_color]);
      new_robot->set_cordinat(position(r_x, r_y));
      new_robot->set_direction(direct);
      Robots.push_back(new_robot);
   }

   // цикл чтения информации о программах
   for (int i = 0; i < count_commands; i++) {
      string name_com;

      int com_x, com_y;
      int f_color;

      file >> name_com;
      string f_allow_delete, f_change_coord;
      file >>f_color >> com_x >> com_y;
      file >> f_change_coord >> f_allow_delete;

      bool allow_delete = (f_allow_delete == "да"? true : false);
      bool change_coord = (f_change_coord == "да"? true : false);

      cout << name_com  <<   " " << f_color <<" "<< com_x << " " << com_y << " "
           <<  f_change_coord <<" "<< f_allow_delete << " ";

      Command *command;
      places_taken.push_back(position(com_x, com_y));

      if (name_com == "стрелка") {
         int f_orient;
         position orient;
         file >> f_orient;

         cout << f_orient << endl;
         switch (f_orient) {
         case 0:
            orient = position(1, 0);
            break; // "вправo"
         case 1:
            orient = position(0, 1);
            break; //"вверх"
         case 2:
            orient = position(-1, 0);
            break; //"влево"
         case 3:
            orient = position(0, -1);
            break; //"вниз"
         }
         Arrow *arrow = new Arrow(change_coord, allow_delete, position(com_x, com_y), orient);
         command = arrow;
      }
      else if (name_com == "банка_с_краской") {
         int f_change_col;
         file >> f_change_col;

         cout << f_change_col << endl;
         ChangeColor *canOfPaint = new ChangeColor(change_coord, allow_delete, position(com_x, com_y), color_prog[f_change_col]);
         command = canOfPaint;
      }
      else if (name_com == "выход") {
         cout << endl;
         Exit *box = new Exit(change_coord, allow_delete, position(com_x, com_y));
         command = box;
      }
      else
         cout << "Сюда вставить проверку на ошибки\n";

      auto it =  find_if(Programms.begin(), Programms.end(), [f_color](Programm *prog) -> bool {
         return prog->get_col() == color_prog[f_color];});


      if (it != Programms.end())
      {
         cout << "Нашёл" << endl;
         (*it)->add(command);
      }
      else {
         cout << "Не нашёл"  << endl;
         Programm *new_programm = new Programm(color_prog[f_color]);
         new_programm->add(command);
         Programms.push_back(new_programm);
      }
   }

   cout << "Чтение файла завешенно. Закрываем файл\n" << endl;
   file.close();
}

void Task::prepare_field(Field &field) {
   count_fruit = COUNFUITS;
   count_tree = COUNTTREE;
   srand(time(NULL));

   for (int n_fruit = 0; n_fruit < count_fruit;)
   {
      position pos_fruit;
      pos_fruit.x = rand() % (WIDTH_I);
      pos_fruit.y = rand() % (HEIGHT_J);
      auto it = find_if(places_taken.begin(), places_taken.end(),
                        [pos_fruit](position place) -> bool {return (place.x != pos_fruit.x&& place.y != pos_fruit.y);});

      if (it != places_taken.end()) {
         n_fruit ++;
         places_taken.push_back(pos_fruit);
         Fruit *fruit =new Fruit(loadBMP("apple.bmp"));
         field.set_obj(fruit, pos_fruit);
      }
   }
   for (int n_fruit = 0; n_fruit < count_tree;)
   {
      position pos_tree;
      pos_tree.x = rand() % (WIDTH_I-1);
      pos_tree.y = rand() % (HEIGHT_J-1);
      auto it = find_if(places_taken.begin(), places_taken.end(),
                        [pos_tree](position place) -> bool {return (place.x != pos_tree.x&& place.y != pos_tree.y);});

      if (it != places_taken.end()) {
         n_fruit ++;
         places_taken.push_back(pos_tree);
         field.set_obj(new Tree(loadBMP("tree.bmp")), pos_tree);
      }
   }
}

string Task::get_text_task() {
   cout<<"text---> "<<text_task<<endl;
   return text_task;
}



