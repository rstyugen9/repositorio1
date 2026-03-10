#include "juego.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

// Mapa base fijo
static const char *MAPA_FIJO[ALTO] = {
    "###################",
    "#                 #",
    "#  #####          #",
    "#      #          #",
    "#      #   #####  #",
    "#          #      #",
    "#          #      #",
    "#   #####  #      #",
    "#                 #",
    "###################"
};

int juego_es_pared(const Juego *j, int x, int y)
{
    if (x < 0 || x >= ANCHO || y < 0 || y >= ALTO)
        return 1;

    return (j->mapa[y][x] == '#');
}


// Generar trofeo en posición aleatoria
void juego_generar_trofeo(Juego *j)
{
    int x, y;

    do{
        x = 1 + rand() % (ANCHO - 2);
        y = 1 + rand() % (ALTO - 2);
    }
    while (juego_es_pared(j,x,y) || (x == j->jugador_x && y == j->jugador_y));

    j->trofeo_x = x;
    j->trofeo_y = y;
}

void juego_inicializar(Juego *j)
{
    for (int y = 0; y < ALTO; y++){
        strncpy(j->mapa[y], MAPA_FIJO[y], ANCHO);
        j->mapa[y][ANCHO] = '\0';
    }

    j->jugador_x = 1;
    j->jugador_y = 1;

    j->pasos = 0;
    j->choques = 0;
    j->ultima_tecla = '_';
    j->estado = ESTADO_JUGANDO;

    srand(time(NULL));

    j->trofeos_recogidos = 0;

    juego_generar_trofeo(j);
}


void juego_intentar_mover(Juego *j, int dx, int dy)
{
    int nx = j->jugador_x + dx;
    int ny = j->jugador_y + dy;

    if (juego_es_pared(j, nx, ny)){
        j->choques++;
        return;
    }

    j->jugador_x = nx;
    j->jugador_y = ny;
    j->pasos++;

    // Capturar trofeo
    if (j->jugador_x == j->trofeo_x && j->jugador_y == j->trofeo_y){

        j->trofeos_recogidos++;

        if (j->trofeos_recogidos < 10){
            juego_generar_trofeo(j);
        }
        else{
            printf("Trofeo generado en: (%d,%d)\n", j->trofeo_x, j->trofeo_y);
            j->estado = ESTADO_MENU;
        }
    }
}