#include <iostream>
#include <cmath>
#define TO_GR 180.0*acos(-1)
using namespace std;

class Polar {
   double r;
   double phi;
public:
   Polar(double = 1, double = 0);
   Polar &operator+=(double); //поворот вектора на d градусов против часовой стрелке
   Polar &operator-=(double); //поворот вектора на d градусов по часовой стрелке
   Polar &operator*=(double); //увеличение вектора в d раз
   Polar &operator/=(double); //уменьшение вектора в d раз
   friend bool operator==(const Polar &, const Polar &); //перегрузка операции ==
   friend bool operator!=(const Polar &, const Polar &); //перегрузка операции !=
   bool operator!()const {return (r==0);}//перегрузка операции !
   friend istream &operator>>(istream &, Polar &);//перегрузка операции  >>
   friend ostream &operator<<(ostream &, const Polar &);// перегрузка операции  <<
   double getLength() const {return r;}; // получить радиус
   double getAngle() const {return phi;}; // получить  угол
   double recur_angle(double);
};


int main() {
   setlocale(LC_ALL, "ru");
    
    Polar x(8, 32);
    Polar y(10, 30);
    
    cout << "¬ывод\n";
    cout << "x = "<< x << " y = " << y<< "\n";
    cout << "¬вод y\n";
    cout << "y = ";
    cin >> y;
    cout << "ѕроверка операции !y\n";
    cout << " !" << y << " = " << !y << "\n";
    cout << "ѕроверка операции x == y\n";
    cout << x << " == " << y << " = " << (x == y) << "\n";
    cout << "ѕроверка операции x != y\n";
    cout << x << " != " << y << " = " << (x != y) << "\n";
    cout << "ѕроверка операции y += d\n";
    cout << y << " += " << 15 << " = ";
    cout << (y += 15) << "\n";
    cout << "ѕроверка операции y -= d\n";
    cout << y << " -= " << 20 << " = ";
    cout << (y -= 20) << "\n";
    cout << "ѕроверка операции y *= d\n";
    cout << y << " *= " << 3 << " = ";
    cout << (y *= 3) << "\n";
    cout << "ѕроверка операции y /= d\n";
    cout << y << " /= " << 2 << " = ";
    cout << (y /= 2) << "\n";
    cout << "ѕроверка операции d* y\n";
    cout << 2 << " * " << y << " = ";
    
    Polar buf = 2 * y;
    
    cout << buf << "\n";
    cout << "ѕроверка операции x+y\n";
    cout << x << " + " << y << " = ";
    
    Polar z = x + y;
    
    cout << z << "\n";
    cout << "ѕроверка операции x-y\n";
    cout << x << " - " << y << " = ";
    
    Polar e = x - y;
    
    cout << e << "\n";
    return 0;
}

double Polar::recur_angle(double angle){
   double grad;
   double modGrad = modf(angle,&grad);
   return int(grad)%360+modGrad;
}

Polar::Polar(double r, double phi): r(r), phi(recur_angle(phi)) {}

Polar &Polar::operator+=(double angle) {
   phi+= angle;
   phi = recur_angle(phi);
   return *this;
}

Polar &Polar::operator-=(double angle) {
   phi-= d.phi;
   phi = recur_angle(phi);
   return *this;
}

Polar &Polar::operator*=(double d) {
   r *= d;
   return *this;
}

Polar &Polar::operator/=(double d) {
   if(d == 0)
      cout << "ƒеление на 0"; 
   else
      r /= d;
   return *this;
}

inline Polar operator + (Polar &p1, Polar &p2){ //x+y
    double angl1 = p1.getAngle()/ 180.0 * PI ;
    double angl2 = p2.getAngle()/ 180.0 * PI ;
    double x1 = p1.getLength() * cos(angl1);
    double y1 = p1.getLength() * sin(angl1);
    double x2 = p2.getLength() * cos(angl2);
    double y2 = p2.getLength() * sin(angl2);
    double x3 = x1 + x2;
    double y3 = y1 + y2;
    double r = sqrt(x3 * x3 + y3 * y3);
    double phi = atan2(y3, x3) / acos(-1) * 180.0;
    
    Polar p3(r, phi);
    
    return p3;
}

inline Polar operator - (Polar &p1, Polar &p2) { //x-y
    double angl1 = p1.getAngle() * acos(-1) / 180.0;
    double angl2 = p2.getAngle() * acos(-1) / 180.0;
    double x1 = p1.getLength() * cos(angl1);
    double y1 = p1.getLength() * sin(angl1);
    double x2 = p2.getLength() * cos(angl2);
    double y2 = p2.getLength() * sin(angl2);
    double x3 = x1 - x2;
    double y3 = y1 - y2;
    double r = sqrt(x3 * x3 + y3 * y3);
    double phi = atan2(y3, x3) / acos(-1) * 180.0;
    
    Polar p3(r, phi);
    
    return p3;
}

bool operator==(const Polar &v1, const Polar &v2) {
   return (x.r==y.r&&y.phi==y.phi);
}

bool operator!=(const Polar &v1, const Polar &v2) {
   return !(x==y);
}

bool Polar:: operator!(){
    return r == 0;
}

istream &operator>>(istream &s, Polar &v) {
   char c;
   
   return s>>v.r>>c>>v.phi;
}
ostream &operator<<(ostream &s, const Polar &p) {
   return s<<v.r <<"@"<<v.phi;
}
