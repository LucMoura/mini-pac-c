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
                break;
            }
        }
    }
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
