#include <iostream>
#include <math.h>

#define TO_GR acos(-1)/180

using namespace std;

class Polar {
   double r, phi;//������ � ����

public:
   Polar(double r, double phi) : r(recur_angle(r)), phi(recur_angle(phi)) {};//�����������

   Polar operator + (double,    
   Polar &operator+=(double d);//���������� �������� +=
   Polar &operator-=(double d);//���������� �������� -=
   Polar &operator*=(double d);//���������� �������� *=
   Polar &operator/=(double d);//���������� �������� /=
   bool operator!();//���������� �������� !
   friend bool operator==(const Polar p1, const Polar p2)
   { return (p1.r == p2.r && p1.phi == p2.phi); }//���������� �������� ==
   friend istream &operator>>(istream &, Polar &); // ���������� �������� >>
   friend ostream &operator<<(ostream &, const Polar &); //���������� �������� <<

   double getLength() const {return r;}; //������
   double getAngle() const {return phi;}; //����
   double recur_angle(double);
};

double Polar::recur_angle(double angle) {
   double grad;
   double modGrad = modf(angle,&grad);
   return int(grad)%360+modGrad;
}

Polar &Polar:: operator +=(double angle) {
   phi = recur_angle(phi+angle);
   return *this;
}

Polar &Polar:: operator -=(double angle) {
      phi = recur_angle(phi-angle);
   return *this;
}

Polar &Polar:: operator *=(double d) {
   r *= d;
   return *this;
}

Polar &Polar:: operator /=(double d) {
   r /= d;
   return *this;
}

istream &operator>>(istream &i, Polar &p) {
   char c;
   return i >> p.r >> c >> p.phi;
}

ostream &operator<<(ostream &o, const Polar &p) {
   return o << p.r << '@' << p.phi;
}

inline bool operator != (const Polar p1, const Polar p2) {
   return !(p1 == p2);
}

inline Polar operator * (double d, Polar p1) {
   return p1 *= d;
}

bool Polar:: operator!() {
   return r == 0;
}

inline Polar operator + (Polar p1, Polar p2) {

   double angl1 = p1.getAngle() * TO_GR;
   double angl2 = p2.getAngle() * TO_GR;
   double res_x = p1.getLength() * cos(angl1) + p2.getLength() * cos(angl2);
   double res_y = p1.getLength() * sin(angl1) + p2.getLength() * sin(angl2);
   double r = sqrt(res_x * res_x + res_y * res_y);
   double phi = atan2(res_y, res_x) / acos(-1) * 180.0;

   Polar res(r, phi);

   return res;
}

inline Polar operator - (Polar p1, Polar p2) {
   double angl1 = p1.getAngle() * TO_GR;
   double angl2 = p2.getAngle() *TO_GR;
   double res_x = p1.getLength() * cos(angl1) - p2.getLength() * cos(angl2);
   double res_y = p1.getLength() * sin(angl1) - p2.getLength() * sin(angl2);
   double r = sqrt(res_x * res_x + res_y * res_y);
   double phi = atan2(res_y, res_x) / acos(-1) * 180.0;

   Polar res(r, phi);

   return res;
}

int main() {
   setlocale(LC_ALL, "ru");

   Polar vec1(5, 62);
   Polar vec2(12, 30);

   cout << "�����\n";
   cout << "vec1 = "<< vec1 << " vec2 = " << vec2<< "\n";
   cout << "���� vec2\n";
   cout << "vec2 = ";
   cin >> vec2;
   cout << "�������� �������� !vec2\n";
   cout << " !" << vec2 << " = " << !vec2 << "\n";
   cout << "�������� �������� vec1 == vec2\n";
   cout << vec1 << " == " << vec2 << " = " << (vec1 == vec2) << "\n";
   cout << "�������� �������� vec1 != vec2\n";
   cout << vec1 << " != " << vec2 << " = " << (vec1 != vec2) << "\n";
   cout << "�������� �������� vec2 += d\n";
   cout << vec2 << " += " << 15 << " = ";
   cout << (vec2 += 15) << "\n";
   cout << "�������� �������� vec2 -= d\n";
   cout << vec2 << " -= " << 10 << " = ";
   cout << (vec2 -= 10) << "\n";
   cout << "�������� �������� vec2 *= d\n";
   cout << vec2 << " *= " << 3 << " = ";
   cout << (vec2 *= 3) << "\n";
   cout << "�������� �������� vec2 /= d\n";
   cout << vec2 << " /= " << 2 << " = ";
   cout << (vec2 /= 2) << "\n";
   cout << "�������� �������� d* vec2\n";
   cout << 2 << " * " << vec2 << " = ";

   Polar vec3 = 2 * vec2;

   cout << vec3 << "\n";
   cout << "�������� �������� vec1+vec2\n";
   cout << vec1 << " + " << vec2 << " = ";

   vec3 = vec1 + vec2;

   cout << vec3 << "\n";
   cout << "�������� �������� vec1-vec2\n";
   cout << vec1 << " - " << vec2 << " = ";

   vec3 = vec1 - vec2;

   cout << vec3 << "\n";
   return 0;
}
