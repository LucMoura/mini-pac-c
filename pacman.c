#include <stdio.h>
#include <stdlib.h>
#include "pacman.h"
#include "funcoes.h"
MAPA m;
POSICAO heroi;


int acabou(){
    return 0;
}

void move(char direcao){
    int proximox = heroi.x;
    int proximoy = heroi.y;


    m.matriz[heroi.x][heroi.y] = '.';
    switch (direcao)
    {
        case 'a':{
            proximoy--;
            break;
        }
        case 'w':{
            proximox--;
            break;
        }
        case 's':{
            proximox++;
            break;
        }
        case 'd':{
            proximoy++;
            break;
        }
        default:{
            return;
        }
}

}

int main(void){

    encontra_mapa(&m, &heroi, '@');
    do
        {
        identifica_mapa(&m);
        char comando;
        scanf("%c", &comando);
        move(comando);

            imprime_mapa(&m);
    } while (!acabou());
    libera_mapa(&m);
    return 0;
}
