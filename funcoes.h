#include "pacman.h"
#define HEROI '@'
#define FANTASMA 'F'
#define VAZIO '.'
#define PAREDE_LATERAL '|'
#define PAREDE_HORIZONTAL '-'

void imprime_mapa(MAPA* m);
void libera_mapa(MAPA* m);
void gera_mapa(MAPA* m);
void identifica_mapa(MAPA* m);
void encontra_mapa(MAPA* m, POSICAO* p,char c);
int pode_andar(MAPA*m, int x, int y);
int ta_vazia(MAPA*m, int x, int y);
void andando_mapa(MAPA* m, int xorigem, int yorigem, int xdestino, int ydestino);
