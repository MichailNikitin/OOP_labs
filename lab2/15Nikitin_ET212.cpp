#include <iostream>
#include <cmath>
#define _USE_MATH_DEFINES
using namespace std;
class Polar {
   double r;
   double phi;
public:
   Polar(double = 1, double = 0);
   Polar &operator+=(const Polar &); //поворот вектора на d градусов против часовой стрелке
   Polar &operator-=(const Polar &); //поворот вектора на d градусов по часовой стрелке
   Polar &operator*=(const Polar &); //увеличение вектора в d раз
   Polar &operator/=(const Polar &); //уменьшение вектора в d раз
   friend bool operator==(const Polar &, const Polar &); //перегрузка операции ==
   friend bool operator!=(const Polar &, const Polar &); //перегрузка операции !=
   bool operator!()const {return (r==0);}//перегрузка операции !
   friend istream &operator>>(istream &, Polar &);//перегрузка операции  >>
   friend ostream &operator<<(ostream &, const Polar &);// перегрузка операции  <<
   double getLength() const {return r;}; // радиус
   double getAngle() const {return phi;}; // угол
};


int main() {
Polar v1(1, 90), v2(0.5, 120), v3(5, 520);
return 0;
}

Polar::Polar(double r, double phi) {
   this->r = r;
   double b;
   int a = (int)modf(phi, *b);
   this->phi = a%360+b;
}

Polar &Polar::operator+=(const Polar &d) {
   phi = (phi+d.phi)%360;
   return *this;
}

Polar &Polar::operator-=(const Polar &d) {
   phi = (phi-d.phi)%360;
   return *this;
}

Polar &Polar::operator*=(const Polar &d) {
   r = d.r;
   return *this;
}

Polar &Polar::operator/=(const Polar &d) {
   phi = d.phi%360;
   return *this;
}

Polar operator+(Polar x, Polar y) {
   return x+=y;
}

Polar operator-(Polar x, Polar y) {
   return x-=y;
}

bool operator==(const Polar &x, const Polar &y) {
   return ((x.r==y.r&&y.phi==y.phi);
}

bool operator!=(const Polar &x, const Polar &y) {
   return !(x==y);
   
   istream &operator>>(istream &s, Rational &p) {
   char c;
   return s>>p.r>>c>>p.phi;
}
ostream &operator<<(ostream &s, const Rational &p) {
   return s<<p.r <<"@"<<p.phi;
}


