








static int arr_arrowUp[14] = {45, 0, 90, 45, 67, 45, 67, 90, 23, 90, 23, 45, 0, 45};
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

bool find_command_in_prog(Programm* prog, int color){
   if (_abracadabra_cast(*(prog));