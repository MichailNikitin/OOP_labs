










static int arr_arrowUp[16] = {45, 0, 90, 45, 67, 45, 67, 90, 23, 90, 23, 45, 0, 45, 45, 0};
constexpr int color_prog[4] = {RED, GREEN, BLUE, YELLOW};

using namespace std;

int direct2grad(position direct) {
   if (direct.y == 1)
      return 90;
   if (direct.x == -1)
      return 180;
   if (direct.y == -1)
      return 270;
   else
      return 0;
}

bool find_command_in_prog(Programm *prog, int color) {
   if (prog->get_col() == color)
      return true;
   return false;
}


Robot::Robot(IMAGE *image, bool direction, bool cordinat):img(image), allow_change_direction(direction), allow_change_cordinat(cordinat) {}
Robot::~Robot() {freeimage(img);}

void Robot::set_cordinat(position new_pos) {
   pos.x = new_pos.x;
   pos.y = new_pos.y;
}

void Robot::set_direction(position new_direction) {
   direction.x = new_direction.x;
   direction.y = new_direction.y;
}

void Robot::set_color(int new_color) {color = new_color;}

void Robot::change_Field(Field &Field) {


}

void Robot::draw() {
   IMAGE *rotImg = imageturn(img,  direct2grad(pos), WHITE);
   putimage(pos.x*100+5,pos.y*100+5, rotImg, COPY_PUT);
}
bool Robot::is_crash(std::vector <Robot *> &Robots) {

   return 1;
}

Object::Object(IMAGE *image): img(image) {}
Object::~Object() {freeimage(img);}
Fruit::Fruit(IMAGE *image): Object(image) {}
Fruit::~Fruit() {freeimage(img);}
Tree::Tree(IMAGE *image): Object(image) {}
Tree::~Tree() {freeimage(img);}

bool Fruit::is_access(Robot &current_robot) {
   return 1;
}

bool Tree::is_access(Robot &current_robot) {
   return 0;
}

Field::Field(int w, int h):width(w), height(h) {
   //vector<vector<Cell>> field(width, vector<Cell>(height));
}

position Field::coord2pos(int x, int y) {
   position current_pos;
   current_pos.x = x/100;
   current_pos.y = y/100;
   return current_pos;
}

void Field::set_obj(Object *obj, position pos) { // i, j
   field[pos.x][pos.y].current_object = obj;
}

void Field::delete_obj(position pos) { // i, j
   delete field[pos.x][pos.y].current_object;
}

void Field::set_color(position pos, int color) { // i, j
   field[pos.x][pos.y].color = color;
}

Object *Field::get_object(position pos) {
   return field[pos.x][pos.y].current_object;
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

Arrow::Arrow(bool is_change_cordinat, bool is_delete, position new_coord, position direction):
   Command(is_change_cordinat, is_delete, new_coord), orientation(direction) {}

ChangeColor::ChangeColor(bool is_change_cordinat, bool is_delete, position new_coord, int color):
   Command(is_change_cordinat, is_delete, new_coord), color(color) {}

Exit::Exit(bool is_change_cordinat, bool is_delete, position new_coord):
   Command(is_change_cordinat, is_delete, new_coord) {}

void Arrow::use(Robot &robot) {
   robot.set_direction(this->orientation);
}
void Arrow::draw() {
   setcolor(BLACK);
   _abracadabra_cast(*(img));