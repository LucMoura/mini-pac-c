#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pacman.h"
#include "funcoes.h"
MAPA m;



int distancia_heuristica(int x1, int y1, int x2, int y2){
    return abs(x1 - x2) + abs(y1 - y2);
}

void copia_mapa(MAPA* destino, MAPA* origem){
    destino->linhas = origem->linhas;
    destino->colunas = origem->colunas;

    gera_mapa(destino);
    for(int i = 0; i < origem->linhas; i++){
        strcpy(destino->matriz[i], origem->matriz[i]);
    }
}


int movimentacao(MAPA* m,char personagem,int x, int y){
    return
    pode_andar(m, x, y) && !is_parede(m, x, y) && !is_personagem(m, personagem, x ,y);
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

int is_parede(MAPA*m, int x, int y){
    return m->matriz[x][y] == PAREDE_LATERAL || m->matriz[x][y] == PAREDE_HORIZONTAL;
}

int is_personagem(MAPA*m, char personagem ,int x, int y){
    return m->matriz[x][y] == personagem;
}

void andando_mapa(MAPA* m, int xorigem, int yorigem, int xdestino, int ydestino){
    if(m->matriz[xdestino][ydestino] == VAZIO){
        char personagem = m->matriz[xorigem][yorigem];
        m->matriz[xdestino][ydestino] = personagem;
        m->matriz[xorigem][yorigem] = VAZIO;
    }
}


int pode_andar(MAPA* m, int x, int y){
    if (x >= m->linhas || x < 0) return 0;
    if (y >= m->colunas || y < 0) return 0;
    return 1;
}

int ta_vazia(MAPA*m, int x, int y){
    return m->matriz[x][y] == VAZIO;

}

int busca_caminho(MAPA* m, int xf, int yf, int xh, int yh, int* xdestino, int* ydestino){
    NO abertos[1000];
    int na_abertos = 0;
    int fechados[100][100] = {0};

    abertos[na_abertos++] = (NO){xf, yf, 0, distancia_heuristica(xf, yf, xh, yh), 0};

    while (na_abertos > 0){
        int menor = 0;
        for(int i = 1; i < na_abertos; i++){
            if(abertos[i].total < abertos[menor].total){
                menor = i;
            }
        }

        NO atual = abertos [menor];
        abertos[menor] = abertos [--na_abertos];

        if (atual.x == xh && atual.y == yh){
            *xdestino = atual.x;
            *ydestino = atual.y;
            return 1;
        }

        fechados[atual.x][atual.y] = 1;

        int movimentos[4][2] = {
            {atual.x + 1, atual.y}, {atual.x -1, atual.y},
            {atual.x, atual.y + 1}, {atual.x, atual.y -1}
        };

        for (int i = 0; i < 4; i++){
            int nx = movimentos[i][0];
            int ny = movimentos[i][1];
            
            if (!movimentacao(m, FANTASMA, nx, ny)) continue;
            if (fechados[nx][ny]) continue;

            int novo_custo = atual.custo + 1;
            int heuristica = distancia_heuristica(nx, ny, xh, yh);

            abertos[na_abertos++] = (NO){nx, ny, novo_custo, heuristica, novo_custo + heuristica};
            }
        
        }
        return 0;
    }


void libera_mapa(MAPA* m){
    for(int i = 0; i < m->linhas; i++){
        free(m->matriz[i]);
    }   
    free(m->matriz);
}

void gera_mapa(MAPA* m){
    m->matriz = malloc(sizeof(char*) * m->linhas);
    if(m->matriz == NULL){
        printf("Erro ao alocar a memória para o mapa");
    }
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

DIFICULDADE selecionar_dificuldade() {
    int escolha;
    printf("Selecione a dificuldade:\n");
    printf("1 - Fácil\n");
    printf("2 - Médio\n");
    printf("3 - Difícil\n");
    scanf("%d", &escolha);
    
    switch(escolha) {
        case 1: return FACIL;
        case 2: return MEDIO;
        case 3: return DIFICIL;
        default:
            printf("Opção inválida! Selecionando a dificuldade média.\n");
            return MEDIO;
    }
}

