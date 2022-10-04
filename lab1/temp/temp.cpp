


class DSortSeq{
   int n,
//текущий размер
   nmax;
//максимальный размер
   double *mas;
//указатель на массив
public:
   DSortSeq();//пуста€ последовательность
   ~DSortSeq();//деструктор класса
   void add(double x);//добавить число
   int size();//текущий размер
   double get(int i);//получить элемент последовательности
   void remove(int i);//удалить i-ый элемент
   void print();//распечатать состо€ние объекта
};
using namespace std;
int main() {
   DSortSeq D;
   int count_numbers = 7
   cout<<format("«аполним последовательность {} случаными числами и распечатаем состо€ние объекта\n", count_numbers);
   for(int i = 0; i < count_numbers; i ++){
      _abracadabra_cast(D);