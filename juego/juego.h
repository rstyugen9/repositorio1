#ifndef JUEGO_H
#define JUEGO_H
#define MAX_ENEMIGOS 3

//Definir dimensiones fijas del mapa para la sesion
#define ALTO 10
#define ANCHO 20

//Definir estructura utilitaria para almacenar estado del juego
typedef enum {
    ESTADO_MENU,
    ESTADO_JUGANDO,
    ESTADO_INSTRUCCIONES,
    ESTADO_SALIR
} EstadoJuego;

typedef struct {
    char mapa[ALTO][ANCHO+1]; // +1 para la terminacion nula
    int jugador_x;
    int jugador_y;
    int pasos;

    int choques;
    char ultima_tecla;
    EstadoJuego estado;

    int trofeo_x;
    int trofeo_y;
    int trofeos_recogidos;

    int vidas;

    int enemigos_x[MAX_ENEMIGOS];
    int enemigos_y[MAX_ENEMIGOS];


} Juego;

//Funciones para inicializar y actualizar el juego
void juego_inicializar(Juego *j);

void juego_intentar_mover(Juego *j, int dx, int dy);

void juego_mover_enemigos(Juego *j);

int juego_es_pared(const Juego *j, int x, int y);

#endif // JUEGO_H
