#include <stdio.h>
#include <stdlib.h>
#include "pacman.h"
#include "funcoes.h"
MAPA m;
POSICAO heroi;

void fantasma(){
    for (int i = 0; i < m.linhas; i++){
        for(int j = 0; j < m.colunas; j++){
            if(m.matriz[i][j] == FANTASMA){
                if(pode_andar(&m, i, j+1)){
                    andando_mapa(&m,i, j, i, j + 1);
                }
            }
        }
    }
}


int acabou(){
    return 0;
}

void move(char direcao){
    int proximox = heroi.x;
    int proximoy = heroi.y;

     switch (direcao) {
        case ESQUERDA: proximoy--; break;
        case CIMA: proximox--; break;
        case BAIXO: proximox++; break;
        case DIREITA: proximoy++; break;
        default: return;
    }

    if (!pode_andar(&m, proximox, proximoy)) return;
    if (!ta_vazia(&m,proximox,proximoy)) return;

    andando_mapa(&m, heroi.x, heroi.y, proximox, proximoy);
    heroi.x = proximox;
    heroi.y = proximoy;

}
    

int main(void){
    identifica_mapa(&m);
    encontra_mapa(&m, &heroi, HEROI);
    do
    {
        imprime_mapa(&m);
        char comando;
        scanf(" %c", &comando);
        move(comando);
        fantasma();
    } while (!acabou());

    libera_mapa(&m);
    return 0;
}
