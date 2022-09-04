#include <iostream>
#include <vector>
#include <random>

/*
15. Объявить массив целых чисел и заполнить его случайными значениями с помощью функций srand() и rand(). Размер массива и диапазон значений его элементов вводятся с клавиатуры. Во всех непрерывных подпоследовательностях положительных чисел заменить на 0 значения тех элементов, значения которых меньше среднего для этой подпоследовательности. Рассматриваемые подпоследовательности не должны являться частью большей подобной подпоследовательности.
*/

int main() {
   srand(time(0));
   int n, A, B, sum, i_start, i_end;
   bool is_pos = false;
   sum = i_end = i_start = 0;
   std::vector <int> arr;

   std::cout<< "input size of arr - ";
   std::cin >>n;
   std::cout<< "input frame of arr - ";
   std::cin >> A >> B;
   arr.resize(n);

   for (int i = 0; i < n; i++) {
      arr[i] = (rand()%(B-A+1)+A);

      if (arr[i] > 0) {
         sum += arr[i];
         //  это первый положительный сгенерированный элемент последовательности?
         if (!is_pos) {
            i_start = i;
            std::cout<< arr[i] << "- start" << std::endl;
            is_pos = true;
            sum = 0;
         }
      }
      else {
         // первый отрицательный элемент после последовательности положительных элементов?
         if (is_pos) {
            i_end = i;
            std::cout<< arr[i] << "- end" << std::endl;
            is_pos = false;
         }
      }

      if (abs(i_start - i_end) > 1 && !is_pos) {
         double med = sum*1.0/(abs(i_start - i_end));
         std::cout << med << "    ";
         for (int j = i_start; j < i_end; j++)
            if (arr[j] < med) {
               std::cout << arr[j] << std::endl;
               arr[j] = 0;
            }
         sum = 0;
      }
      i_end = i_start = 0;
   }

   for (int i = 0; i < n; i++)
      std::cout << arr[i] << " ";

   return 0;
}
