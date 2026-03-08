#ifndef JUEGO_H
#define JUEGO_H

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

} Juego;

//Funciones para inicializar y actualizar el juego
void juego_inicializar(Juego *j);

void juego_intentar_mover(Juego *j, int dx, int dy);

int juego_es_pared(const Juego *j, int x, int y);

#endif // JUEGO_H
