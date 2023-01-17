








static int arr_arrowUp[14] = {45, 0, 90, 45, 67, 45, 67, 90, 23, 90, 23, 45, 0, 45};
constexpr int color_prog[4] = {RED, GREEN, BLUE, YELLOW};

using namespace std;

int direct2grad(position){
   if (position.x == 1)
      return 0;
   if (position.y == 1)
      return 90;
   if (position.x == -1)
      return 180;
   if (_abracadabra_cast(position);