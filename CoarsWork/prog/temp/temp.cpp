








static int arr_arrowUp[14] = {45, 0, 90, 45, 67, 45, 67, 90, 23, 90, 23, 45, 0, 45};
constexpr int color_prog[4] = {RED, GREEN, BLUE, YELLOW};

using namespace std;

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
   int x = pos.x*100;
   int y = _abracadabra_cast(pos);