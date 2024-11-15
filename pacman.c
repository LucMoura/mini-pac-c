#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pacman.h"
#include "funcoes.h"
MAPA m;
POSICAO heroi;

int direcao_fantasma(int xatual, int yatual, int* xdestino, int* ydestino){
    int opcoes[4][2]={
        {xatual, yatual + 1},
        {xatual, yatual -1},
        {xatual + 1, yatual},
        {xatual - 1, yatual}
    };
    srand(time(0));
    for(int i = 0; i < 11; i++){
        int posicao = rand() %4;

        if(movimentacao(&m, opcoes[posicao][0],opcoes[posicao][1])){
            *xdestino = opcoes[posicao][0];
            *ydestino = opcoes[posicao][1];
            return 1;
        }
    }
    return 0;
}


void fantasma(){
    MAPA copia;

    copia_mapa(&copia, &m);

    for (int i = 0; i < m.linhas; i++){
        for(int j = 0; j < m.colunas; j++){
            if(copia.matriz[i][j] == FANTASMA){
                int xdestino, ydestino;
                int encontrou = direcao_fantasma(i, j, &xdestino, &ydestino);
                if(encontrou){
                    andando_mapa(&m, i, j, xdestino, ydestino);
                }
                if(movimentacao(&m, i, j+1)){
                    andando_mapa(&m,i, j, i, j + 1);
                    return;
                }
            }
        }
    }
    libera_mapa(&copia);
}


int acabou(){
    POSICAO posicao;
    int heroi_mapa = encontra_mapa(&m, &posicao, HEROI);
    return !heroi_mapa;
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

    if (!movimentacao(&m, proximox, proximoy)) return;


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
