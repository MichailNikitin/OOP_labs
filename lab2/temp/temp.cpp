

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
\\
Polar &Polar::operator+=(const Polar&d){
   phi = _abracadabra_cast(d);