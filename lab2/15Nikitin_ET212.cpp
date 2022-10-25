#include <iostream>
#include <cmath>
#define _USE_MATH_DEFINES

class Polar {
   double r;
   double phi;
public:
   Polar(double = 1, double = 0);
   Polar &operator+=(const Polar&); //������� ������� �� d �������� ������ ������� �������
   Polar &operator-=(const Polar&); //������� ������� �� d �������� �� ������� �������
   Polar &operator*=(const Polar&);
   Polar &operator/=(const Polar&);



}


int main() {




}

Polar::Polar(double r, double phi){
   this->r = r;
   this->phi = phi%360;
}

Polar &Polar::operator+=(const Polar&d){
   phi = (phi+d.phi)%360;
   return *this;
}

Polar &Polar::operator-=(const Polar&d){
   phi = (phi-d.phi)%360;
   return *this;
}

Polar &Polar::operator*=(const Polar&d){
   r = d.r;
   return *this;
}

Polar &Polar::operator/=(const Polar&d){
   phi = d.phi%360;
   return *this;
}