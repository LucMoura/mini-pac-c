#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pacman.h"
#include "funcoes.h"
#include "ui.h"
MAPA m;
POSICAO heroi;
int tem_pilula = 0;

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

        if(movimentacao(&m, HEROI ,opcoes[posicao][0],opcoes[posicao][1])){
            *xdestino = opcoes[posicao][0];
            *ydestino = opcoes[posicao][1];
            return 1;
        }
    }
    return 0;
}
void colocar_objetivo(MAPA* m){
    m->matriz[m->linhas -1][m->colunas -1] = '*';
}

int verificar_objetivo(MAPA* m, POSICAO heroi){
    if(m->matriz[heroi.x][heroi.y] == '*'){
        printf("Parabéns você ganhou");
        return 1;
    }
    return 0;
}


void fantasma() {
    MAPA copia;
    copia_mapa(&copia, &m);

    for (int i = 0; i < m.linhas; i++) {
        for (int j = 0; j < m.colunas; j++) {
            if (copia.matriz[i][j] == FANTASMA) {
                int xdestino, ydestino;
                encontra_mapa(&m, &heroi, HEROI);
                int encontrou = busca_caminho(&m, i, j, heroi.x, heroi.y, &xdestino, &ydestino);

                if (encontrou) {
                    int movimentos[4][2] = {
                        {i + 1, j}, {i - 1, j},
                        {i, j + 1}, {i, j - 1}
                    };
                    int min_distancia = distancia_heuristica(i, j, heroi.x, heroi.y);
                    int next_x = i, next_y = j;

                    for (int k = 0; k < 4; k++) {
                        int nx = movimentos[k][0];
                        int ny = movimentos[k][1];
                        
                        if (pode_andar(&m, nx, ny) && !is_parede(&m, nx, ny) && !is_personagem(&m, FANTASMA, nx, ny)) {
                            int dist = distancia_heuristica(nx, ny, heroi.x, heroi.y);
                            if (dist < min_distancia) {
                                min_distancia = dist;
                                next_x = nx;
                                next_y = ny;
                            }
                        }
                    }

        
                    if (next_x != i || next_y != j) {
                        andando_mapa(&m, i, j, next_x, next_y);
                    }

                    if (next_x == heroi.x && next_y == heroi.y) {
                        printf("Você perdeu\n");
                        exit(0);
                    }
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

void explode_bomba(){
    if(!tem_pilula) return;
    explode_bomba2(heroi.x, heroi.y, 0, 1, 3);
    explode_bomba2(heroi.x, heroi.y, 0, -1, 3);
    explode_bomba2(heroi.x, heroi.y, 1, 0, 3);
    explode_bomba2(heroi.x, heroi.y, -1, 0, 3);
    tem_pilula = 0;
}

void explode_bomba2(int x, int y, int somax, int somay, int qntd){
    if(qntd == 0) return;

    int novox = x + somax;
    int novoy = y + somay;

    if(!pode_andar(&m, novox, novoy)) return;
    if(is_parede(&m, novox, novoy)) return;

    m.matriz[novox][novoy] = VAZIO;
    explode_bomba2(novox, novoy, somax, somay, qntd-1);
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

    if (!movimentacao(&m, HEROI ,proximox, proximoy)) return;
    if (is_personagem(&m, PILULA, proximox, proximoy)) tem_pilula = 1 ;


    andando_mapa(&m, heroi.x, heroi.y, proximox, proximoy);
    heroi.x = proximox;
    heroi.y = proximoy;

}
    

int main(void){
    identifica_mapa(&m);
    encontra_mapa(&m, &heroi, HEROI);
    do
    {
        printf("Tem pilula: %s\n", (tem_pilula ? "SIM" : "NÃO"));
        imprime_mapa(&m);
        char comando;
        scanf(" %c", &comando);
        move(comando);
        if(comando == BOMBA) explode_bomba(heroi.x, heroi.y, 4);
        fantasma();
    } while (!acabou());

    libera_mapa(&m);
    return 0;
}
