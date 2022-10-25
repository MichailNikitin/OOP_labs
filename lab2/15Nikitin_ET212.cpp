#include <iostream>
#include <cmath>
#define _USE_MATH_DEFINES

class Polar {
   double r;
   double phi;
public:
   Polar(double = 1, double = 0);
   Polar &operator+=(const Polar &); //������� ������� �� d �������� ������ ������� �������
   Polar &operator-=(const Polar &); //������� ������� �� d �������� �� ������� �������
   Polar &operator*=(const Polar &); //���������� ������� � d ���
   Polar &operator/=(const Polar &); //���������� ������� � d ���
   friend bool operator==(const Polar &, const Polar &); //���������� �������� ==
   friend bool operator!=(const Polar &, const Polar &); //���������� �������� !=
   bool operator!()const {return (a==0);}//���������� �������� !
   friend istream &operator>>(istream &, Polar &);//���������� ��������  >>
   friend ostream &operator<<(ostream &, const Polar &);// ���������� ��������  <<
   double getLength() const {return r}; // ������
   double getAngle() const {return phi}; // ����
}


int main() {




}

Polar::Polar(double r, double phi) {
   this->r = r;
   this->phi = phi%360;
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

bool operator==(const Polar &x, const Polar &y) {
   return ((x.a==x.b&&y.a==y.b);
}

bool operator!=(const Polar &x, const Polar &y) {
   return !(x==y);
}
