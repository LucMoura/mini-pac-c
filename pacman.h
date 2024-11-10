#ifndef PACMAN_H
#define PACMAN_H
struct mapa{
    char** matriz;
    int linhas, colunas;
};

typedef struct mapa MAPA;
struct posicao{
    int x, y;
};
typedef struct posicao POSICAO;

void move(char direcao);
int acabou();
#endif