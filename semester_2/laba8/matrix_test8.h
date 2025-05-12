#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>

void matrix(int n, int m, int arr[n][m]);
int determinant(int N, int arr[N][N]);
void Kramer(int N, int arr[N][N], int B[N]);

#endif