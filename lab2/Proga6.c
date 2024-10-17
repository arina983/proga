#include <stdio.h>
int main() {
// #define N 5
int A [2];
int B [2];
int C [2];
A[0] = 3;
A[1] = 5;
B[0] = 7;
B[1] = 9;

for(int i = 0; i < 2; i++ ) {
    C[i] == A[i] + B[i]; 
    }

float max_real = A[0];
for(int i = 0; i < 2; i += 2) {
    if(A[i] > max_real) {
        max_real = A[i];
    }
}
  
float imaginary = B[1];
   for(int i = 1; i < 2; i +=2) {
       if(B[i] < 0 ) {
        imaginary++;
       } 
   } 

float sum_real = 0, sum_imag = 0;
for(int i = 0; i < 2; i ++) {
    if(i % 2 ==0) {
        sum_real += C[i]; 
    }
    else {
         sum_imag += C[i];
    }
}
double avg = (sum_real + sum_imag) / 2;

printf("Максимальная реальная часть в массиве A: %.2f\n", max_real);
printf("Количество мнимых частей, меньше 0 в массиве В: %.2f\n", imaginary);
printf("Cреднее арифметическое элементов массива С: %.2f\n", avg );


}


