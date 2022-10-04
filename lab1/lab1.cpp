#include <iostream>
#include <format>

class DSortSeq{
   int n,
//текущий размер
   nmax;
//максимальный размер
   double *mas;
//указатель на массив
public:
   DSortSeq();//пустая последовательность
   ~DSortSeq();//деструктор класса
   void add(double x);//добавить число
   int size();//текущий размер
   double get(int i);//получить элемент последовательности
   void remove(int i);//удалить i-ый элемент
   void print();//распечатать состояние объекта
};
using namespace std;
int main() {
   srand(time(0));
   DSortSeq D;

   int count_numbers = 7;
   cout<<format("Заполним последовательность {} случаными числами"
   "и распечатаем состояние объекта\n", count_numbers);
   for(int i = 0; i < count_numbers; i ++)
      D.add(rand() % 10 + 1);
   D.print();
   
   cout<<"Текущий размер последовательности:"<<D.size()<<"\n";
   
   cout<<"Получим третий элемент последовательности:"
       <<D.get(3)<<"\n";
   
   cout<<"Удалим 1 эл. послед. и распечатаем состояние объекта\n";
   D.remove(1);
   D.print();
   
   cout<<"Удалим несуществующий элемент последовательности:";
       D.remove(D.size()+1);
   return 0;
}


DSortSeq::DSortSeq() {
   nmax=8;
   n=0;
   mas=new double[nmax];
}
DSortSeq::~DSortSeq() {
   delete [] mas;
}

void DSortSeq::add(double x) {
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
int DSortSeq::size() {
   return (n);
}
double DSortSeq::get(int i) {
   if (i<0 || i>=n) {
      cout<<"Неверный индекс\n";
      exit(1);
   }
   else
      return (mas[i]);
}

void DSortSeq::remove(int i) {
   if (i<0 || i>=n) {
      cout<<"Неверный индекс\n";
      exit(1);
   }
   else {
      for (int ind = i; ind<n-1; ind++)
         mas[ind] = mas[ind+1];
      n--;
   }
}

void DSortSeq::print() {
   for (int i=0; i < n; i++)
      cout<<mas[i]<<" ";
   cout<<"\n";
}
