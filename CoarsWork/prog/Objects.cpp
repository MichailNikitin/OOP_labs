#include "Objects.hpp"

vector <int> color_prog = {RED, GREEN, BLUE, YELLOW, WHITE};
vector<position> places_taken;

using namespace std;

int direct2grad(position direct) {
   if (direct.x == -1)
      return 180;
   if (direct.y == 1)
      return 270;
   if (direct.y == -1)
      return 90;
   else
      return 0;
}

Robot::Robot(IMAGE *image, bool direction, bool cordinat):img(image), allow_change_direction(direction), allow_change_cordinat(cordinat) {}
Robot::~Robot() {freeimage(img);}

void Robot::set_pos(position new_pos) {
   pos = position(new_pos.x, new_pos.y);
}

void Robot::set_direction(position new_direction) {
   direction = position(new_direction.x, new_direction.y);
}
void Robot::set_img(IMAGE* image){ img = image;}

void Robot::set_color(int new_color) {color = new_color;}
int Robot::get_color() {return color;}
int Robot::get_n_color() { return distance(color_prog.begin(), find(color_prog.begin(), color_prog.end(), color));}
position Robot::get_pos() {return pos;}
position Robot::get_direction() {return direction;}

void Robot::change_Field(Field &field) {
   field.delete_obj(pos);
   field.set_count_fruit(field.get_count_fruit()-1);
}

void Robot::draw() {
   int i_color = distance(color_prog.begin(), find(color_prog.begin(), color_prog.end(), color));
   char name_image[7];
   snprintf(name_image, sizeof(name_image), "r%d.bmp",i_color);
   this->img = loadBMP(name_image);
   IMAGE *rotImg = imageturn(img,  direct2grad(direction), WHITE);
   putimage(pos.x*100+5,pos.y*100+5, rotImg, COPY_PUT);
}
bool Robot::is_crash(std::vector <Robot *> &Robots) {
   int n_x =pos.x + direction.x;
   int n_y = pos.y + direction.y;
   if (n_x > WIDTH_I-1 || n_y > HEIGHT_J-1 || n_x < 0 || n_y < 0) {
      return 1;
   }
   for (int i = 0; i < Robots.size(); i++) {
      if (this == Robots[i])
         continue;
      if (n_x == Robots[i]->pos.x && n_y == Robots[i]->pos.y && direction != Robots[i]->direction)
         return 1;
      if (n_x == Robots[i]->pos.x + Robots[i]->direction.x && n_y == Robots[i]->pos.y + Robots[i]->direction.y)
         return 1;
   }
   return 0;
}

bool Robot::is_collision(Field &field, vector <Robot *> &Robots) {
   for (int i = 0; i < Robots.size(); i++) {
      if (this == Robots[i])
         continue;
      if (Robots[i]->get_pos() == this->get_pos())
         return true;
      if (field.get_object(this->get_pos()) != nullptr) {
         return true;
      }
      return this->is_crash(Robots);
   }
   return false;
}

Object::Object(IMAGE *image): img(image) {}
Object::Object(const Object &obj) {img = obj.img;}
Object::~Object() {freeimage(img);}

Fruit::Fruit(IMAGE *image): Object(image) {}
Fruit::~Fruit() {freeimage(img);}

Tree::Tree(IMAGE *image): Object(image) {}
Tree::~Tree() {freeimage(img);}

void Fruit::draw(position pos) {return putimage(pos.x, pos.y, img, COPY_PUT);}

void Tree::draw(position pos) { putimage(pos.x, pos.y, img, COPY_PUT);}

Field::Field(int w, int h):width(w), height(h),  fullField(width, vector<Cell>(height)), count_tree(COUNTTREE), count_fruit(COUNFUITS) {}

void Field::set_count_fruit(int n_fruit){ count_fruit = n_fruit;}

void Field::set_count_tree(int n_tree){ count_tree = n_tree;}

int Field::get_count_fruit(){return count_fruit;}

void Field::set_obj(Object *obj, position pos) { 
   fullField[pos.x][pos.y].current_object = obj;
}

void Field::delete_obj(position pos) { 
   fullField[pos.x][pos.y].current_object = nullptr;
}

void Field::set_color(position pos, int color) {
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
bool Command::get_allow_pos() {return is_allow_change_cordinat;}

Arrow::Arrow(bool is_change_cordinat, bool is_delete, position new_coord, position direction):
   Command(is_change_cordinat, is_delete, new_coord), orientation(direction) {}

ChangeColor::ChangeColor(bool is_change_cordinat, bool is_delete, position new_coord, int color):
   Command(is_change_cordinat, is_delete, new_coord), color(color) {}

Exit::Exit(bool is_change_cordinat, bool is_delete, position new_coord):
   Command(is_change_cordinat, is_delete, new_coord) {}

void Arrow::use(Robot &robot) {
   robot.set_direction(orientation);
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
   IMAGE *rotImg = imageturn(this->img,  (direct2grad(orientation)+270)%360, WHITE);
   putimage(coord.x*100+10,coord.y*100+10, rotImg, COPY_PUT);
}

void ChangeColor::use(Robot &robot) {
   robot.set_color(color);   
}

void ChangeColor::draw(int col) {
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
   putimage(coord.x*100+5, coord.y*100+5, img, COPY_PUT);
}

Programm::Programm(int c): color(c) {}
int Programm::get_col() {return color;}

void Programm::add(Command *command) {
   commands.push_back(command);
}

void Programm::draw() {
   for (int i = 0; i < commands.size(); i ++) {
      commands[i]->draw(color);
   }
}

void Programm::delete_com(Command *com) {
   commands.erase(ranges::find(commands, com));
}

bool Programm::is_collision() {
   for (int i = 0; i < commands.size(); i ++) {
      for (int j = 0; j < commands.size(); j++) {
         if (i != j && commands[i]->get_pos() == commands[j]->get_pos())
            return true;
      }
   }
   return false;
}

Command *Programm::select(position pos) {
   auto it =  find_if(commands.begin(), commands.end(), [pos](Command *com) -> bool {
      return com->get_pos() == pos;});
   if (it != commands.end()) {
      return *it;
   }
   else {
      return nullptr;
   }
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
      
      places_taken.push_back(position(r_x, r_y));

      bool change_direct, change_coord;
      position direct;
      change_direct = (f_change_direct == "да"? true : false);
      change_coord = (f_change_coord == "да"? true : false);

      switch (f_direct) {
      case 0:
         direct = position(1, 0);
         break; // "вправо"
      case 1:
         direct = position(0, -1);
         break; //"вверх"
      case 2:
         direct = position(-1, 0);
         break; //"влево"
      case 3:
         direct = position(0, 1);
         break; //"вниз"

      }
      char name_image[7];
      snprintf(name_image, sizeof(name_image), "r%d.bmp",f_color);
      Robot *new_robot = new Robot(loadBMP(name_image),change_direct, change_coord);
      
      new_robot->set_color(color_prog[f_color]);
      new_robot->set_pos(position(r_x, r_y));
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
            orient = position(0, -1);
            break; //"вверх"
         case 2:
            orient = position(-1, 0);
            break; //"влево"
         case 3:
            orient = position(0, 1);
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
         cout << "Неизвестная команда\n";

      auto it =  find_if(Programms.begin(), Programms.end(), [f_color](Programm *prog) -> bool {
         return prog->get_col() == color_prog[f_color];});


      if (it != Programms.end())
      {
         (*it)->add(command);
      }
      else {
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
      auto it = ranges::find(places_taken, pos_fruit);
      
      if (it == places_taken.end()) {
         n_fruit ++;
         places_taken.push_back(pos_fruit);
         Fruit *fruit =new Fruit(loadBMP("apple.bmp"));
         field.set_obj(fruit, pos_fruit);
      }
   }
   field.set_count_fruit(count_fruit);
   
   for (int n_fruit = 0; n_fruit < count_tree;)
   {
      position pos_tree;
      pos_tree.x = rand() % (WIDTH_I);
      pos_tree.y = rand() % (HEIGHT_J);
      auto it = ranges::find(places_taken, pos_tree);

      if (it == places_taken.end()) {
         n_fruit ++;
         places_taken.push_back(pos_tree);
         field.set_obj(new Tree(loadBMP("tree.bmp")), pos_tree);
      }
   }
   field.set_count_tree(count_tree);
}

string Task::get_text_task() {
   cout<<"text---> "<<text_task<<endl;
   return text_task;
}

bool Task::is_task_completed(Field &field, vector <Robot *> &Robots) {
   if (!field.get_count_fruit() && Robots.empty())
      return 1;
   return 0;
}



