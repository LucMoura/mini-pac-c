void liberamapa();
void gera_mapa();
void identifica_mapa();
void move(char direcao);
int acabou();
void imprime_mapa();

struct mapa{
    char** matriz;
    int linhas, colunas;
};
