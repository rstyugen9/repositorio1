#ifndef JUEGO_H
#define JUEGO_H

#include <stdio.h>

#define ALTO 10
#define ANCHO 20
#define MAX_ENEMIGOS 5

typedef enum {
    ESTADO_MENU,
    ESTADO_JUGANDO,
    ESTADO_PAUSA,
    ESTADO_INSTRUCCIONES,
    ESTADO_SALIR
} EstadoJuego;

typedef struct {
    char mapa[ALTO][ANCHO+1];

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
    int enemigos_trofeos[MAX_ENEMIGOS];

    int num_enemigos;

} Juego;

void juego_inicializar(Juego *j);
void juego_intentar_mover(Juego *j, int dx, int dy);
void juego_mover_enemigos(Juego *j);

void juego_guardar(Juego *j);
int juego_cargar(Juego *j);

int juego_es_pared(const Juego *j, int x, int y);

#endif