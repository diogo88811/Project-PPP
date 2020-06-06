// FIFO em lista circular
//João Gabriel Silva 2020-03-18
#include <stdio.h>

#define TAMFILA 10 /* maximo de mensagens em espera */

int prim_vazia;
int prim_mens;


struct mensagem {
    char destino[50];
    char origem[50];
    unsigned char dados[1024];
};

struct mensagem fila[TAMFILA];

int colocar(struct mensagem mens);

struct mensagem retirar(void);

int main() {
    int i;
    struct mensagem mens1 = {"Rua Sta. Apolonia Lisboa", "Rua do Castro, Coimbra",
                             "Desejo-vos uma quarentena muito agradável. Abraços, Manuel Francisco"};
    struct mensagem mens2;

    prim_vazia=TAMFILA-1;
    prim_mens=TAMFILA-1;


    for (i = 0; i < TAMFILA; i++)
        fila[i].destino[0] = 0;

    for (i = 0; i < TAMFILA + 1; i++)
        if (colocar(mens1) != 0)
            printf("Erro na colocação\n");
        else
            printf("Colocação com sucesso\n");

    mens2 = retirar();
    if (mens2.destino[0] == 0)
        printf("Fila estava vazia\n");
    else
        printf("Mens retirada com sucesso: %s\n", mens2.destino);
    for (i = 0; i < 3; i++)
        if (colocar(mens1) != 0)
            printf("Erro na colocação\n");
        else
            printf("Colocação com sucesso\n");

    for (i = 0; i < TAMFILA + 1; i++) {
        mens2 = retirar();
        if (mens2.destino[0] == 0)
            printf("Fila estava vazia\n");
        else
            printf("Mens retirada com sucesso: %s\n", mens2.destino);
    }


    return 0;
}

int colocar(struct mensagem mens) {
    if (prim_vazia != prim_mens ||
        fila[prim_mens].destino[0]==0) {
        //fila contém pelo menos uma posição vazia
        fila[prim_vazia] = mens;
        prim_vazia --;
        if (prim_vazia <0) prim_vazia = TAMFILA-1;
        return 0;
    }
    else // não há espaço
        return 1;
}

struct mensagem retirar(void) {
    struct mensagem primeira = fila[prim_mens];
    if (prim_mens != prim_vazia ||
        fila[prim_mens].destino[0]!=0) {
        //fila contém pelo menos uma mensagem
        fila[prim_mens].destino[0] = 0;
        prim_mens--;
        if (prim_mens <0) prim_mens = TAMFILA-1;
    }
    return primeira;
}


