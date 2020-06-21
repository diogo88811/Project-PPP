#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"
#define SIZESTRING 200

int main()
{
    converseStudents();
    converseGrades();
    return 1;
}

int converseStudents()
{
    FILE *f = fopen("students.txt", "r");
    if (f == NULL)
    {
        printf("File doesn´exist\n");
        return -1;
    }

    FILE *fb = fopen("studentsBinary.bin", "wb");
    if (fb == NULL)
    {
        printf("Error binary file\n");
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
        fwrite(&stu, sizeof(struct student), 1, fb);
    }

    fclose(f);
    fclose(fb);

    return 0;
}

int converseGrades()
{

    char line[SIZESTRING];
    struct grades grade;

    FILE *f1 = fopen("grades.txt", "r");
    if (f1 == NULL)
    {
        printf("File doesn´t exist\n");
        return -1;
    }

    FILE *fb = fopen("gradesBinary.bin","wb");
    if(fb == NULL)
    {
        printf("error binary file");
        return -1;
    }

    while (get_one_line(f1, line, SIZESTRING) != EOF)
    {
        char *token = strtok(line, "-");
        grade.num = (unsigned int)strtol(token, NULL, 0);
        int count = 0;
        while (token != NULL)
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
                // printf("\t%d\n",grade.num);
                // printf("\t%s\n", grade.discipline);
                // printf("\t%d\n", grade.test);
                // printf("\t%f\n", grade.grade);
                fwrite(&grade,sizeof(struct grades),1,fb);
            }
            count++;
            token = strtok(NULL, "-");
        }
    }

    fclose(f1);
    fclose(fb);
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