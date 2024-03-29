// ������� �15
#include <iostream>
#include <vector>
#include <stdlib.h>

/*
15. �������� ������ ����� ����� � ��������� ��� ���������� ���������� � ������� ������� srand() � rand(). ������ ������� � �������� �������� ��� ��������� �������� � ����������. �� ���� ����������� ���������������������� ������������� ����� �������� �� 0 �������� ��� ���������, �������� ������� ������ �������� ��� ���� ���������������������. ��������������� ��������������������� �� ������ �������� ������ ������� �������� ���������������������.
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

   for (int i = 0; i < n; ++i) {
      arr[i] = (rand()%(B-A+1)+A);
      std::cout<< arr[i] << " ";
      if (arr[i] > 0) {
         //  ��� ������ ������������� ��������������� ������� ������������������?
         if (!is_pos) {
            i_start = i;
            is_pos = true;
            sum = 0;
         }
         sum += arr[i];
      }
      else {
         // ������ ������������� ������� ����� ������������������ ������������� ���������?
         if (is_pos) {
            i_end = i;
            is_pos = false;
         }
      }
	// ����� �� ����� �� ������������� ��������
      if (i == n-1 && is_pos){
         is_pos = false;
         i_end = i+1;
      }
      
      if (abs(i_start - i_end) > 1 && !is_pos) {
         double med = sum*1.0/(abs(i_start - i_end));

         for (int j = i_start; j < i_end; j++)
            if (arr[j] < med)
               arr[j] = 0;
         i_end = i_start = 0;
      }

   }
   std::cout << std::endl;

   for (int i = 0; i < n; i++)
      std::cout << arr[i] << " ";

   return 0;
}
