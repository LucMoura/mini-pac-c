#include "pacman.h"
#define HEROI '@'
#define FANTASMA 'F'
#define OBJETIVO '*'
#define VAZIO '.'
#define PAREDE_LATERAL '|'
#define PAREDE_HORIZONTAL '-'
#define PILULA 'P'

void libera_mapa(MAPA* m);
void gera_mapa(MAPA* m);
void identifica_mapa(MAPA* m);
int encontra_mapa(MAPA* m, POSICAO* p,char c);
int pode_andar(MAPA*m, int x, int y);
int ta_vazia(MAPA*m, int x, int y);
void copia_mapa(MAPA* destino, MAPA* origem);
void andando_mapa(MAPA* m, int xorigem, int yorigem, int xdestino, int ydestino);
int movimentacao(MAPA* m, char personagem, int x, int y);
int is_parede(MAPA*m, int x, int y);
int is_personagem(MAPA* m, char personagem, int x, int y);
int busca_caminho(MAPA* m, int xf, int yf, int xh, int yh, int* xdestino, int* ydestino);
int distancia_heuristica(int x1, int y1, int x2, int y2);
void explode_bomba();
void explode_bomba2(int x, int y, int somax, int somay, int qntd);
