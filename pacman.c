#include <stdio.h>
#include <stdlib.h>
#include "pacman.h"
struct mapa m;


void libera_mapa(){
    for(int i = 0; i < m.linhas; i++){
        free(m.matriz[i]);
    }   
    free(m.matriz);
}


void gera_mapa(){
    m.matriz = malloc(sizeof(char*) * m.linhas);
    for(int i = 0; i < m.linhas; i++){
        m.matriz[i] = malloc(sizeof(char) * (m.colunas + 1)); 
    }
}
void identifica_mapa(){
    FILE* f = fopen("mapa.txt", "r");
    if (f == NULL){
        printf("Erro ao abrir o mapa\n");
        exit(1);
    }
    
    fscanf(f, "%d %d", &m.linhas, &m.colunas);
    gera_mapa();

    for (int i = 0; i < m.linhas; i++){
        fscanf(f, "%s", m.matriz[i]);
    }
    fclose(f);
}

void imprime_mapa(){
        
   
    for(int i = 0; i < m.linhas; i++){
        for (int j = 0; j < m.colunas; j++){
            printf("%c", m.matriz[i][j]);
        }
        printf("\n");
    }
}

int acabou(){
    return 0;
}

void move(char direcao){
    int x, y;

    for (int i = 0; i < m.linhas; i++){
        for(int j = 0; j < m.colunas; j++){
            if(m.matriz[i][j] == '@'){
                x = i;
                y = j;
                break;
            }
        }
    }

    switch (direcao)
    {
        case 'a':{
            m.matriz[x][y-1] = '@';
            break;
        }
        case 'w':{
            m.matriz[x-1][y] = '@';
            break;
        }
        case 's':{
            m.matriz[x+1][y] = '@';
            break;
        }
        case 'd':{
            m.matriz[x][y+1] = '@';
            break;
        }
}
    m.matriz[x][y] = '.';
}

int main(void){
    libera_mapa();
    do
        {
        identifica_mapa();
        char comando;
        scanf("%c", &comando);
        move(comando);

            imprime_mapa();
    } while (!acabou());

    return 0;
}
