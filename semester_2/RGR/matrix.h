#ifndef MATRIX_H
#define MATRIX_H

#define EPSILON 1e-10
#define MAX_SIZE 100

double** memory_matrix(int n, int m);
void free_matrix(int n, double **matrix);
double** read_matrix(const char *filename, int *n);
void print_matrix(int n, double **matrix);
void print_matrix_isx(int n, double **matrix);
double** inverse_matrix(int n, double **matrix, int *error);
void verify_inverse(int n, double **A, double **A_inv);

#endif