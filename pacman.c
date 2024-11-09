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

void imprime_mapa(){
        
   
    for(int i = 0; i < linhas; i++){
        for (int j = 0; j < colunas; j++){
            printf("%c", mapa[i][j]);
        }
        printf("\n");
    }
}

int acabou(){
    return 0;
}

void move(char direcao){
    int x, y;

    for (int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            if(mapa[i][j] == '@'){
                x = i;
                y = j;
                break;
            }
        }
    }

    switch (direcao)
    {
        case 'a':{
            mapa[x][y-1] = '@';
            break;
        }
        case 'w':{
            mapa[x-1][y] = '@';
            break;
        }
        case 's':{
            mapa[x+1][y] = '@';
            break;
        }
        case 'd':{
            mapa[x][y+1] = '@';
            break;
        }
}
    mapa[x][y] = '.';
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
