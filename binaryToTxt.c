#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "header.h"

void conversao();

int main()
{
    conversao();
    return 0;
}

void conversao()
{
    FILE *bin = fopen("PautasBinary.bin", "rb");
    FILE *conv = fopen("Pautas.txt", "w");

    fprintf(conv,"\t\t\tPautas das cadeiras:\n");
    struct discipline aux;
    struct aproved aux1;
    while (!feof(bin))
    {
        int n = fread(&aux, sizeof(struct discipline), 1, bin);
        if (n >= 1){
            printf("%s\n",aux.name);
            fprintf(conv,"%s\n",aux.name);
            for (int k = 0; k < SIZEROW; k++)
            {
                if (aux.guidelinesList[k].classifi != -1)
                {

                    // printf("\tNAME: %s", aux.guidelinesList[k].name);
                    // printf("\tGrade: %f\n", aux.guidelinesList[k].classifi);
                    fprintf(conv,"\t%s\t%f\n",aux.guidelinesList[k].name,aux.guidelinesList[k].classifi);

                }
            }
        }
    }

    fclose(bin);
    fclose(conv);

    FILE *bin1 = fopen("GeralBinary.bin","rb");
    FILE *conv1 = fopen("Geral.txt","w");

    fprintf(conv,"\tAlunos que transitaram de ano:\n\n");

     while (!feof(bin1))
    {
        int n = fread(&aux1, sizeof(struct aproved), 1, bin1);
        if (n >= 1){
            fprintf(conv1,"%s\n",aux1.aprov.name);
        }
    }

    fclose(bin1);
    fclose(conv1);
}