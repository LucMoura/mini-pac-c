#include <stdio.h>
#include <stdlib.h>
#include "pacman.h"
#include "funcoes.h"
MAPA m;

void encontra_mapa(MAPA* m, POSICAO* p,char c){
    for (int i = 0; i < m->linhas; i++){
        for(int j = 0; j < m->colunas; j++){
            if(m->matriz[i][j] == c){
                p->x = i;
                p->y = j;
                return;
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
