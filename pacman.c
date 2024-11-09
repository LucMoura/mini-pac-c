#include <stdio.h>
#include <stdlib.h>

char** mapa;
int linhas, colunas;

void libera_mapa(){
    for(int i = 0; i < linhas; i++){
        free(mapa[i]);
    }   
    free(mapa);
}

void gera_mapa(){
    mapa = malloc(sizeof(char*) * linhas);
    for(int i = 0; i < linhas; i++){
        mapa[i] = malloc(sizeof(char) * (colunas + 1)); 
    }
}

void identifica_mapa(){
    FILE* f = fopen("mapa.txt", "r");
    if (f == NULL){
        printf("Erro ao abrir o mapa\n");
        exit(1);
    }
    
    fscanf(f, "%d %d", &linhas, &colunas);
    gera_mapa();

    for (int i = 0; i < linhas; i++){
        fscanf(f, "%s", mapa[i]);
    }
    fclose(f);
}

int main(void){
    identifica_mapa();
   
    for(int i = 0; i < linhas; i++){
        for (int j = 0; j < colunas; j++){
            printf("%c", mapa[i][j]);
        }
        printf("\n");
    }

    libera_mapa();
    return 0;
}
