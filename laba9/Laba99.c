//вариант 2
#include <stdio.h>
int main() {

int n;
int m;
printf("Введите размер матрицы: \n");
scanf("%d %d", &n, &m);

double matrix[n][m];
printf("Введите элементы матрицы по строкам: \n");
for(int i = 0; i < n; i ++){
    for(int j = 0; j < m; j ++){
        scanf("%lf", &matrix[i][j]);
        
    }
}
//сортируем элементы матрицы по возрастанию
for(int i = 0; i < n; i ++){
    for(int j = 0; j < m; j ++){
        for(int k = j + 1; k < m; k ++){
            if(matrix[i][k] < matrix[i][j]){
                double temp = matrix[i][j];
                matrix[i][j] = matrix[i][k];
                matrix[i][k] = temp;
            }
        }
    }
}
printf("Отсортированная матрица: \n");
for(int i = 0; i < n; i ++){
    for(int j = 0; j < m; j ++){
        printf("%0 .lf", matrix[i][j]);
    }
    printf("\n");
}

//ищем нули в матрице
int zero = 0;
for(int i = 0; i < n; i ++){
    for(int j = 0; j < m; j ++){
        if(matrix[i][j] == 0) {
            zero = 1;
        }
    }
}
if(zero) {
    printf("В матрице есть нули\n");
} else {
    printf("В матрице нет нулей\n");
}
// ищем среднее арифметическое матрицы
double sum = 0;
 for(int i = 0; i < n; i ++){
    for(int j = 0; j < m; j ++){
        sum += matrix[i][j];    
        }
    }
double arithmetic_mean = sum / (n * m);
printf("Среднее арифметическое матрицы: %.3lf\n", arithmetic_mean);

//меняем местами главную и побочную диагональ
if (n == m) {
    for(int i = 0; i < n; i ++){ 
        double temp = matrix[i][i];
        matrix[i][i] = matrix[i][n - i - 1];
        matrix[i][n - i - 1] = temp;
   }
    
printf("Матрица после обмена диагоналей: \n");
for(int i = 0; i < n; i ++){
    for(int j = 0; j < m; j ++){
        printf("%0 .lf", matrix[i][j]);
    }
        printf("\n");
    }
} else {
    printf("Матрицa  должна быть квадратной\n");

}

return 0;
}