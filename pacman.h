#ifndef PACMAN_H
#define PACMAN_H
#define CIMA 'w'
#define BAIXO 's'
#define DIREITA 'd'
#define ESQUERDA 'a'
struct mapa{
    char** matriz;
    int linhas, colunas;
};

typedef enum { FACIL, MEDIO, DIFICIL } DIFICULDADE;


typedef struct 
{
    int x, y;
    int custo;
    int heroi_dsitancia;
    int total;
} NO;

typedef struct mapa MAPA;
struct posicao{
    int x, y;
};
typedef struct posicao POSICAO;
void fantasma();
void move(char direcao);
int acabou();
#endif