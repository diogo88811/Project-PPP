// Diogo Valente Martins

/* 
    Dados acerca do programa e do seu funcionamento:
    Temos os dados necessários a execução do programa em dois ficheiros txt: grades.txt e students.txt
    Previamente temos de executar o programa autónomo txtToBinary.c para podermos ter no programa principal os ficherios de entrada em binário
os ficheiros correspondentes são studentsBinary.bin e gradesBinary.bin
    No programa principal ao executarmos depois de já termos executado o programa txtToBinary.c teremos como saída dois ficheiros PautasBinary.bin
e GeralBinary.bin que nos darão as pautas das respetivas disciplinas e uma pauta geral das pessoas que transitaram de ano.
    Para podermos visualizar os ficheiros que obtivemos como saida temos outro programa autónomo que pelos ficheiros binários obtidos do programa
principal cria ficehiros txt com os resultados esperados do funcionamento do programa principal.

*/
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

int f_emptyApro = SIZEROW - 1;
int f_apro = SIZEROW - 1;

//todas as listas utlizadas este programa
struct student list[SIZEROW];
struct discipline listDisc[SIZEROW];
struct aproved listAprov[SIZEROW];

int main()
{
    //read config.txt 
    FILE *f = fopen("config.txt", "r");
    char line[SIZESTRING];
    char files[1][SIZESTRING];
    while (get_one_line(f, line, SIZESTRING) != EOF)
    {
        char *token = strtok(line, "-");
        strcpy(files[0], token);
        token = strtok(NULL, "-");
        strcpy(files[1], token);
    }
    fclose(f);
    printf("%s\n%s\n", files[0], files[1]);

    iniList();

    getData(files[1]);

    getDataGrades(files[0]);

    //printList();

    iniListGuide();
    insertGuideLines();

    sortGuideLines();

    printListGuide();
    checkWhoPass();
    ordenateListAproved();
    printListAproved();
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
//inicializa as listas de estudantes
void iniList()
{
    //init all numbers with 0 because numbers equal 0 are not alowed
    //init test with 0 because there only are 1 and 2
    for (int i = 0; i < SIZEROW; i++)
    {
        list[i].num = 0;
        list[i].f_emptyGrades = SIZEROW - 1;
        list[i].f_grades = SIZEROW - 1;
        list[i].positiveGrades = -1;
    }
}
//inseres cada estudante na lista
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
//insere as notas de cada estudante no respetivo estudante
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
//buscar informações sobre as notas
int getDataGrades(char *filename)
{

    struct grades grade;

    for (int i = 0; i < SIZEROW; i++)
    {
        FILE *f1 = fopen(filename, "rb");
        if (f1 == NULL)
        {
            printf("File doesn´t exist\n");
            return -1;
        }

        if (list[i].num != 0)
        {

            while (!feof(f1))
            {
                int n = fread(&grade, sizeof(struct grades), 1, f1);
                if (n >= 1)
                {
                    if (list[i].num == grade.num)
                    {
                        insertGrades(i, grade);
                    }
                }
            }
        }
        fclose(f1);
    }
    return 0;
}
//buscar informações sobre os estudantes
int getData(char *filename)
{
    FILE *f = fopen(filename, "rb");
    if (f == NULL)
    {
        printf("File doesn´exist\n");
        return -1;
    }

    struct student stu;
    while (!feof(f))
    {
        int n = fread(&stu, sizeof(struct student), 1, f);
        if (n >= 1)
        {
            insert(stu);
            printf("------> %s     %d\n", stu.name, stu.num);
        }
    }
    fclose(f);
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
//inicializa a lista de ntoas de casa cadeira
int iniListGuide()
{
    for (int i = 0; i < SIZEROW; i++)
    {
        listDisc[i].ini = 0;
    }
    char *arr[] = {"AC", "TI", "SO", "PPP", "AED", "ATD", "IPRP", "CG"};

    for (int i = 0; i < 8; i++)
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

//insere as pautas de todas as cadeiras no ficheiro binario
//PautasBinary.bin
void printListGuide()
{   
    char filename[SIZESTRING];
    printf("Insira o nome do ficheiro de cada cadeira: ");
    scanf("%s",filename);

    FILE *binaryFile = fopen(filename, "wb");

    for (int i = 0; i < SIZEROW; i++)
    {
        if (strlen(listDisc[i].name) != 0)
        {
            //printf("%s\n", listDisc[i].name);
            struct discipline aux = listDisc[i];
            fwrite(&aux, sizeof(struct discipline), 1, binaryFile);
            // for (int k = 0; k < SIZEROW; k++)
            // {
            //     if (listDisc[i].guidelinesList[k].classifi != -1)
            //     {
            //         // struct guidelines aux = listDisc[i].guidelinesList[k];
            //         // fwrite(&aux,sizeof(struct guidelines),1,binaryFile);
            //         printf("\tNAME: %s", listDisc[i].guidelinesList[k].name);
            //         printf("\tGrade: %f\n", listDisc[i].guidelinesList[k].classifi);
            //         // printf("\tNAME: %s",aux.name);
            //         // printf("\tGrade: %f\n",aux.classifi);
            //     }
            // }
        }
    }
    fclose(binaryFile);
}

//insere as pautas
void insertGuideLines()
{
    //criar struct guidelines
    struct guidelines guide;

    for (int k = 0; k < SIZEROW; k++)
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
                    strcpy(guide.name, list[i].name);
                    guide.classifi = med;
                    insertGradesGuideLines(k, guide);
                    //passar a struct e k para oid insertGradesGuideLines()
                }
            }
        }
    }
}

int insertGradesGuideLines(int k, struct guidelines guide)
{

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
//verfica quem passou de ano, obteve aprovacao a 8 ou mais cadeiras
void checkWhoPass()
{
    for (int i = 0; i < SIZEROW; i++)
    {
        int count = 0;
        if (list[i].num != 0)
        {
            for (int k = 0; k < SIZEROW; k++)
            {
                if (strlen(listDisc[k].name) != 0)
                {
                    for (int j = 0; j < SIZEROW; j++)
                    {
                        if (strcmp(list[i].name, listDisc[k].guidelinesList[j].name) == 0)
                        {
                            if (listDisc[k].guidelinesList[j].classifi > 9.5)
                            {
                                count++;
                            }
                        }
                    }
                }
            }
            if (count >= 8)
            {
                //add to a list of students who pass
                insertAproved(list[i]);
            }
            list[i].positiveGrades = count;
            printf("\tNAME: %s -- %d\n", list[i].name, list[i].positiveGrades);
        }
    }
}

//aproved students

//inicializa a lista de estudantes que transitaram de ano
void initListAproved()
{
    for (int i = 0; i < SIZEROW; i++)
    {
        listAprov[i].ini = 0;
    }
}
//insere os estudantes que transitaram de ano
int insertAproved(struct student stuAproved)
{
    if (f_emptyApro != f_apro || listAprov[f_apro].ini == 0)
    { //this list has at least one pos that is empty
        printf("lllllll> %s\n",stuAproved.name);
        listAprov[f_emptyApro].aprov = stuAproved;
        listAprov[f_emptyApro].ini = 1;
        f_emptyApro--;
        if (f_emptyApro < 0)
        {
            f_emptyApro = SIZEROW - 1;
        }
        return 0;
    }
    else
    {
        return 1; // there is no space avaible
    }
}

//ordenas a por ordem alfabetica quem passou de ano
void ordenateListAproved()
{
    for (int i = 0; i < SIZEROW; i++)
    {
        for (int k = i + 1; k < SIZEROW; k++)
        {
            if (strcmp(listAprov[i].aprov.name, listAprov[k].aprov.name) > 0)
            {
                struct aproved temp;
                temp = listAprov[i];
                listAprov[i] = listAprov[k];
                listAprov[k] = temp;
            }
        }
    }
}

//escreve no ficheiro binário a pauta dos alunos que obtiveram aprovaçao
//GradesBinary.txt
void printListAproved()
{   
    char filename[SIZESTRING];
    printf("Insira o nome do ficheiro para pessoas que transitaram de ano: ");
    scanf("%s",filename);
    FILE *bin = fopen(filename, "wb");
    for (int i = 0; i < SIZEROW; i++)
    {
        if (listAprov[i].ini == 1)
        {
            fwrite(&listAprov[i], sizeof(struct aproved), 1, bin);
            printf("---->%s\n", listAprov[i].aprov.name);
        }
    }
}

//sort thhe list by order
void sortGuideLines()
{
    for (int i = 0; i < SIZEROW; i++)
    {
        if (strlen(listDisc[i].name) != 0)
        {
            printf("%s\n", listDisc[i].name);

            for (int k = 0; k < SIZEROW; k++)
            {
                for (int j = k + 1; j < SIZEROW; j++)
                {
                    if (strcmp(listDisc[i].guidelinesList[k].name, listDisc[i].guidelinesList[j].name) > 0)
                    {
                        struct guidelines temp;
                        temp = listDisc[i].guidelinesList[k];
                        listDisc[i].guidelinesList[k] = listDisc[i].guidelinesList[j];
                        listDisc[i].guidelinesList[j] = temp;
                    }
                }
            }
        }
    }
}
