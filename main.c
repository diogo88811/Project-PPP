// Diogo Valente Martins 

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

#define SIZESTRING 200

int f_empty = SIZEROW - 1;
int f_student = SIZEROW - 1;

int f_emptyDisc = SIZEROW - 1;
int f_disc = SIZEROW - 1;

struct student list[SIZEROW];
struct discipline listDisc[SIZEROW];

//read input files .txt to the respective list
void iniList();
void printList();
int getData();
int getDataGrades();
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


int main()
{
    iniList();

    getData();

    getDataGrades();

    //printList();

    iniListGuide();
    insertGuideLines();

    printListGuide();
    checkWhoPass();
    return 0;
}

//read input files .txt to the respective list
void printList()
{
    for (int i = 0; i < SIZEROW; i++)
    {
        if (list[i].num != 0)
            printf("%s - %d\n", list[i].name, list[i].num);
        for (int j = 0; j < SIZEROW; j++)
        {
            if (list[i].gradeRow[j].test != 0)
            {
                printf("\t %s \n", list[i].gradeRow[j].discipline);
                printf("\t %d \n", list[i].gradeRow[j].test);
                printf("\t %f \n", list[i].gradeRow[j].grade);
            }
        }
    }
}

void iniList()
{
    //init all numbers with 0 because numbers equal 0 are not alowed
    //init test with 0 because there only are 1 and 2
    for (int i = 0; i < SIZEROW; i++)
    {
        list[i].num = 0;
        list[i].f_emptyGrades = SIZEROW - 1;
        list[i].f_grades = SIZEROW - 1;
    }
}

int insert(struct student stu)
{
    if (f_empty != f_student || list[f_student].num == 0)
    { //this list has at least one pos that is empty
        list[f_empty] = stu;
        for (int j = 0; j < SIZEROW; j++)
        {
            list[f_empty].gradeRow[j].test = 0;
        }
        f_empty--;
        if (f_empty < 0)
        {
            f_empty = SIZEROW - 1;
        }
        return 0;
    }
    else
    {
        return 1; // there is no space avaible
    }
}

int insertGrades(int i, struct grades grade)
{
    if (list[i].f_emptyGrades != list[i].f_grades || list[i].gradeRow[list[i].f_grades].test == 0)
    { //this list has at least one pos that is empty
        list[i].gradeRow[list[i].f_emptyGrades] = grade;
        list[i].f_emptyGrades--;
        if (list[i].f_emptyGrades < 0)
        {
            list[i].f_emptyGrades = SIZEROW - 1;
        }
        return 0;
    }
    else
    {
        return 1; // there is no space avaible
    }
}

int getDataGrades()
{

    char line[SIZESTRING];
    struct grades grade;

    for (int i = 0; i < SIZEROW; i++)
    {
        if (list[i].num != 0)
        {
            FILE *f1 = fopen("grades.txt", "r");
            if (f1 == NULL)
            {
                printf("File doesn´exist\n");
                return -1;
            }

            while (get_one_line(f1, line, SIZESTRING) != EOF)
            {

                char *token = strtok(line, "-");
                int num = (unsigned int)strtol(token, NULL, 0);
                int count = 0;
                while (token != NULL)
                {
                    if (list[i].num == num)
                    {
                        if (count == 1)
                        {
                            strcpy(grade.discipline, token);
                        }
                        else if (count == 2)
                        {
                            grade.test = (unsigned int)strtol(token, NULL, 0);
                        }
                        else if (count == 3)
                        {
                            grade.grade = atof(token);
                            // printf("\t%s\n",grade.discipline);
                            // printf("\t%d\n",grade.test);
                            // printf("\t%f\n",grade.grade);
                            insertGrades(i, grade);
                        }
                    }

                    count++;
                    token = strtok(NULL, "-");
                }
            }

            fclose(f1);
        }
    }
    return 0;
}

int getData()
{
    FILE *f = fopen("students.txt", "r");
    if (f == NULL)
    {
        printf("File doesn´exist\n");
        return -1;
    }

    char line[SIZESTRING];
    struct student stu;
    while (get_one_line(f, line, SIZESTRING) != EOF)
    {
        char *token = strtok(line, "-");
        strcpy(stu.name, token);
        token = strtok(NULL, "-");
        stu.num = (unsigned int)strtol(token, NULL, 0);
        insert(stu);
    }

    return 0;
}

int get_one_line(FILE *fich, char *linha, int lim)

{
    int c, i;
    i = 0;
    while (isspace(c = fgetc(fich)))
        ;
    if (c != EOF)
    {
        if (!iscntrl(c))
            linha[i++] = c;
    }
    else
        return c;

    for (; i < lim - 1;)
    {
        c = fgetc(fich);
        if (c == EOF)
            return c;
        if (c == '\n')
            break;
        if (!iscntrl(c))
            linha[i++] = c;
    }
    linha[i] = 0;
    while ((c != EOF) && (c != '\n'))
        c = fgetc(fich);
    return c;
}

//create guidelines list and start making the guidelines

int iniListGuide()
{
    for (int i = 0; i < SIZEROW; i++)
    {
        listDisc[i].ini = 0;
    }
    char *arr[] = {"AC", "TI", "SO"};

    for (int i = 0; i < 3; i++)
    {
        if (f_emptyDisc != f_disc || listDisc[f_disc].ini == 0)
        { //this list has at least one pos that is empty
            strcpy(listDisc[f_emptyDisc].name, arr[i]);
            listDisc[f_emptyDisc].f_emptyGuide = SIZEROW - 1;
            listDisc[f_emptyDisc].f_guide = SIZEROW - 1;
            listDisc[f_emptyDisc].ini = 1;
            for (int j = 0; j < SIZEROW; j++)
            {
                listDisc[f_emptyDisc].guidelinesList[j].classifi = -1;
            }
            f_emptyDisc--;
            if (f_emptyDisc < 0)
            {
                f_emptyDisc = SIZEROW - 1;
            }
        }
    }

    return 0;
}

void printListGuide()
{   
    for (int i = 0; i < SIZEROW; i++)
    {
        if (strlen(listDisc[i].name) != 0)
        {
            printf("%s\n", listDisc[i].name);

            for(int k = 0; k < SIZEROW ; k++){
                if(listDisc[i].guidelinesList[k].classifi != -1)
                {
                    printf("\tNAME: %s",listDisc[i].guidelinesList[k].name);
                    printf("\tGrade: %f\n",listDisc[i].guidelinesList[k].classifi);
               }
            }
        }
    }
}

void insertGuideLines()
{
    //criar struct guidelines
    struct guidelines guide;
    
    for (int k = 0;k <  SIZEROW; k++)
    {
        if (listDisc[k].ini != 0)
        {   
                for (int i = 0; i < SIZEROW; i++)
            {
                float med = 0;
                int flag = 0;
                for (int j = 0; j < SIZEROW; j++)
                {
                    if (list[i].gradeRow[j].test != 0)
                    {
                        // printf("\t %s \n", list[i].gradeRow[j].discipline);
                        // printf("\t %d \n", list[i].gradeRow[j].test);
                        // printf("\t %f \n", list[i].gradeRow[j].grade);
                        if (strcmp(listDisc[k].name, list[i].gradeRow[j].discipline) == 0)
                        {
                            med += list[i].gradeRow[j].grade;
                            flag = 1;
                        }
                    }
                }
                if (flag == 1)
                {   
                    med = med / 2;
                    strcpy(guide.name,list[i].name);
                    guide.classifi = med;
                    insertGradesGuideLines(k,guide);
                    //passar a struct e k para oid insertGradesGuideLines()
                }
            }
        }
    }
}

int insertGradesGuideLines(int k, struct guidelines guide ){

    if (listDisc[k].f_emptyGuide != listDisc[k].f_guide || listDisc[k].guidelinesList[listDisc[k].f_guide].classifi == -1)
    { //this list has at least one pos that is empty 
        listDisc[k].guidelinesList[listDisc[k].f_emptyGuide] = guide;
        listDisc[k].f_emptyGuide--;
        if (listDisc[k].f_emptyGuide < 0)
        {   
            listDisc[k].f_emptyGuide = SIZEROW - 1;
        }
        return 0;
    }
    else
    {
        return 1; // there is no space avaible
    }
}

//check if a student has been succesful

void checkWhoPass(){
    for(int i = 0; i < SIZEROW ; i++){
        int count  = 0;
        if (list[i].num != 0)
        {
            for(int k = 0; k < SIZEROW ; k++){
                if(strlen(listDisc[k].name) != 0){
                    for(int j = 0; j < SIZEROW; j++)
                    {
                        if(strcmp(list[i].name,listDisc[k].guidelinesList[j].name) == 0 ){
                            if(listDisc[k].guidelinesList[j].classifi > 9.5){
                                count++;
                            }
                        }
                    }
                }
            }
            printf("\tNAME: %s -- %d\n",list[i].name,count);
        }
    }
}

