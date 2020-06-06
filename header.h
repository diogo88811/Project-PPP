#include <stdio.h>

#define TAM 50
#define SIZEROW 100
struct grades {
    char discipline[TAM];
    int test;
    float grade;
};

struct student {
    char name[TAM];
    int num;
    int f_emptyGrades;
    int f_grades;
    struct grades gradeRow[SIZEROW];
};

struct guidelines {
    char name[TAM];
    float classifi;

};

struct discipline {
    char name[TAM];
    int ini; // variable to initilize the list  
    int f_emptyGuide;
    int f_guide;
    struct guidelines guidelinesList[SIZEROW];
};