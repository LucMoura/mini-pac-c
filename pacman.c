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

     switch (direcao) {
        case 'a': proximoy--; break;
        case 'w': proximox--; break;
        case 's': proximox++; break;
        case 'd': proximoy++; break;
        default: return;
    }

    if (proximox < 0 || proximox >= m.linhas) return;
    if (proximoy < 0 || proximoy >= m.colunas) return;

    if (m.matriz[proximox][proximoy] != '.') return;

    m.matriz[proximox][proximoy] = '@';
    m.matriz[heroi.x][heroi.y] = '.';
    heroi.x = proximox;
    heroi.y = proximoy;

}
    

int main(void){
    identifica_mapa(&m);
    encontra_mapa(&m, &heroi, '@');
    m.matriz[heroi.x][heroi.y] = '.';
    do
    {
        imprime_mapa(&m);
        char comando;
        scanf(" %c", &comando);
        move(comando);
    } while (!acabou());

    libera_mapa(&m);
    return 0;
}
