#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pacman.h"
#include "funcoes.h"
MAPA m;

void copia_mapa(MAPA* destino, MAPA* origem){
    destino->linhas = origem->linhas;
    destino->colunas = origem->colunas;

    gera_mapa(destino);
    for(int i = 0; i < origem->linhas; i++){
        strcpy(destino->matriz[i], origem->matriz[i]);
    }
}


int movimentacao(MAPA* m, int x, int y){
    return
    pode_andar(m, x, y) && ta_vazia(m, x, y);
}

int encontra_mapa(MAPA* m, POSICAO* p,char c){
    for (int i = 0; i < m->linhas; i++){
        for(int j = 0; j < m->colunas; j++){
            if(m->matriz[i][j] == c){
                p->x = i;
                p->y = j;
                return 1;
            }
        }
    }
}

void andando_mapa(MAPA* m, int xorigem, int yorigem, int xdestino, int ydestino){
        char personagem = m->matriz[xorigem][yorigem];
        m->matriz[xdestino][ydestino] = personagem;
        m->matriz[xorigem][yorigem] = VAZIO;
}


int pode_andar(MAPA* m, int x, int y){
    if (x >= m->linhas || x < 0) return 0;
    if (y >= m->colunas || y < 0) return 0;
    return 1;
}

int ta_vazia(MAPA*m, int x, int y){
    return m->matriz[x][y] == VAZIO;

}

void libera_mapa(MAPA* m){
    for(int i = 0; i < m->linhas; i++){
        free(m->matriz[i]);
    }   
    free(m->matriz);
}

void gera_mapa(MAPA* m){
    m->matriz = malloc(sizeof(char*) * m->linhas);
    for(int i = 0; i < m->linhas; i++){
        m->matriz[i] = malloc(sizeof(char) * (m->colunas + 1)); 
    }
}
void identifica_mapa(MAPA * m){
    FILE* f = fopen("mapa.txt", "r");
    if (f == NULL){
        printf("Erro ao abrir o mapa\n");
        exit(1);
    }
    
    fscanf(f, "%d %d",&( m->linhas),&( m->colunas));
    gera_mapa(m);

    for (int i = 0; i < m->linhas; i++){
        fscanf(f, "%s", m->matriz[i]);
    }
    fclose(f);
}

void imprime_mapa(MAPA* m){
        
   
    for(int i = 0; i < m->linhas; i++){
        for (int j = 0; j < m->colunas; j++){
            printf("%c", m->matriz[i][j]);
        }
        printf("\n");
    }
}
