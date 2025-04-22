#ifndef STUDENT_H
#define STUDENT_H

#define N 10
struct Student {
    char name[64];
    int math;
    int phy;
    int inf;
    int total;
};

struct Student addStudent(char name[], int math, int phy, int inf);
void printStudentInfo(struct Student student);
void selectSort(struct Student students[], int n);
void CountingSort(struct Student students[], int n);

#endif