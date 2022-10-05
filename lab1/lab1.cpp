#include <iostream>
#include <format>

class SortSeq{
   int n,//������� ������
   nmax;//������������ ������
   double *mas;//��������� �� ������
public:
   SortSeq();//������ ������������������
   ~SortSeq();//���������� ������
   void add(double x);//�������� �����
   int size();//������� ������
   double get(int i);//�������� ������� ������������������
   void remove(int i);//������� i-�� �������
   void print();//����������� ��������� �������
};
using namespace std;
int main() {
   srand(time(0));
   SortSeq D;

   int count_numbers = rand() % 5+5;
   cout<<format("1.�������� ������������������ {} ��������� �������"
   "� ����������� ��������� �������\n", count_numbers);
   for(int i = 0; i < count_numbers; i ++)
      D.add(rand() % 20 + 1);
   D.print();
   
   cout<<"2.������� ������ ������������������:"<<D.size()<<"\n";
   
   int rand_i4get = rand() % D.size();
   cout<<format("3.������� {} ������� ������������������:", rand_i4get+1)
       <<D.get(rand_i4get)<<"\n";
   
    int rand_i4remove = rand() % D.size();
   cout<<format("4.������ {} ��. ������. � ����������� ��������� �������\n", rand_i4remove+1);
   D.remove(rand_i4remove);
   D.print();
   
   cout<<"5.������ �������������� ������� ������������������:";
       D.remove(D.size()+1);
   return 0;
}


SortSeq::SortSeq() {
   nmax=8;
   n=0;
   mas=new double[nmax];
}
SortSeq::~SortSeq() {
   delete [] mas;
}

void SortSeq::add(double x) {
   if (n == nmax) {
      nmax*= 2;
      double *m = new double[nmax];
      for (int i = 0; i<n; ++i)
         m[i] = mas[i];
      delete [] mas;
      mas = m;
   }
   mas[n++] = x;
   for (int i = n-1; i > 0; i--) {
      if (mas[i] < mas [i-1]) {
         int t = mas[i];
         mas[i] = mas[i-1];
         mas[i-1] = t;
      }
   }
}
int SortSeq::size() {
   return (n);
}
double SortSeq::get(int i) {
   if (i<0 || i>=n) {
      cout<<"�������� ������\n";
      exit(1);
   }
   else
      return (mas[i]);
}

void SortSeq::remove(int i) {
   if (i<0 || i>=n) {
      cout<<"�������� ������\n";
      exit(1);
   }
   else {
      for (int ind = i; ind<n-1; ind++)
         mas[ind] = mas[ind+1];
      n--;
   }
}

void SortSeq::print() {
   for (int i=0; i < n; i++)
      cout<<mas[i]<<" ";
   cout<<"\n";
}
