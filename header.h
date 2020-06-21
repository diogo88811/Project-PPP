#include <stdio.h>

#define TAM 50
#define SIZEROW 100
struct grades {
    char discipline[TAM];
    int test;
    float grade;
    int num;
};

struct student {
    char name[TAM];
    int num;
    int f_emptyGrades;
    int f_grades;
    int positiveGrades;
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


struct aproved {
    struct student aprov;
    int ini;
};


//read input files .txt to the respective list
void iniList();
void printList();
int getData(char *filename);
int getDataGrades(char *filename);
int insert(struct student stu);
int insertGrades(int i, struct grades grade);
int get_one_line(FILE *fich, char *linha, int lim);

//create guidelines list and start making the guidelines
int iniListGuide();
void printListGuide();
void insertGuideLines();
int insertGradesGuideLines(int k, struct guidelines guide);

//check if a student has been succesful
void checkWhoPass();

//sort thhe list by order 
void sortGuideLines();

//aproved students
void initListAproved();
int insertAproved(struct student stuAproved);
void printListAproved();
void ordenateListAproved();