#include "juego.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

static const char *MAPA_FIJO[ALTO] = {
"####################",
"#                  #",
"#  #####           #",
"#      #           #",
"#      #   #####   #",
"#          #       #",
"#          #       #",
"#   #####  #       #",
"#                  #",
"####################"
};

// Distancia Manhattan (para decidir si perseguir trofeo o jugador)
static int dist(int x1,int y1,int x2,int y2){
    int dx = x1 - x2; if(dx < 0) dx = -dx;
    int dy = y1 - y2; if(dy < 0) dy = -dy;
    return dx + dy;
}

int juego_es_pared(const Juego *j, int x, int y)
{
    if(x < 0 || x >= ANCHO || y < 0 || y >= ALTO)
        return 1;

    return j->mapa[y][x] == '#';
}

void juego_guardar(Juego *j)
{
    FILE *f = fopen("save.dat","wb");
    if(!f) return;

    fwrite(j,sizeof(Juego),1,f);
    fclose(f);
}

int juego_cargar(Juego *j)
{
    FILE *f = fopen("save.dat","rb");
    if(!f) return 0;

    fread(j,sizeof(Juego),1,f);
    fclose(f);

    return 1;
}

void juego_generar_trofeo(Juego *j)
{
    int x,y;

    do{
        x = 1 + rand() % (ANCHO - 2);
        y = 1 + rand() % (ALTO - 2);
    }
    while(juego_es_pared(j,x,y) ||
          (x == j->jugador_x && y == j->jugador_y));

    j->trofeo_x = x;
    j->trofeo_y = y;
}

void juego_inicializar(Juego *j)
{
    for(int y=0;y<ALTO;y++){
        strncpy(j->mapa[y],MAPA_FIJO[y],ANCHO);
        j->mapa[y][ANCHO] = '\0';
    }

    j->jugador_x = 1;
    j->jugador_y = 1;

    j->pasos = 0;
    j->choques = 0;
    j->ultima_tecla = '_';

    j->estado = ESTADO_MENU;

    srand(time(NULL));

    j->trofeos_recogidos = 0;
    j->vidas = 3;

    juego_generar_trofeo(j);

    for(int i=0;i<MAX_ENEMIGOS;i++){
        j->enemigos_x[i] = -1;
        j->enemigos_y[i] = -1;
        j->enemigos_trofeos[i] = 0;
    }

    // iniciar con 1 enemigo en esquina inferior derecha
    j->num_enemigos = 1;
    j->enemigos_x[0] = ANCHO-2;
    j->enemigos_y[0] = ALTO-2;
}

void juego_intentar_mover(Juego *j,int dx,int dy)
{
    int nx = j->jugador_x + dx;
    int ny = j->jugador_y + dy;

    if(juego_es_pared(j,nx,ny)){
        j->choques++;
        return;
    }

    j->jugador_x = nx;
    j->jugador_y = ny;
    j->pasos++;

    if(j->jugador_x == j->trofeo_x &&
       j->jugador_y == j->trofeo_y){

        j->trofeos_recogidos++;

        if(j->trofeos_recogidos % 5 == 0){
            j->vidas++;
            printf("¡Vida extra!\n");
        }

        if(j->trofeos_recogidos < 20)
            juego_generar_trofeo(j);
        else{
            printf("\n¡GANASTE! Capturaste 20 trofeos\n");
            j->estado = ESTADO_MENU;
        }
    }
}

void juego_mover_enemigos(Juego *j)
{
    for(int i=0;i<j->num_enemigos;i++){

        int dx = 0;
        int dy = 0;

        // Si el trofeo está cerca, el enemigo lo persigue
        if(dist(j->enemigos_x[i], j->enemigos_y[i], j->trofeo_x, j->trofeo_y) <= 6)
        {
            if(j->trofeo_x > j->enemigos_x[i]) dx = 1;
            if(j->trofeo_x < j->enemigos_x[i]) dx = -1;

            if(j->trofeo_y > j->enemigos_y[i]) dy = 1;
            if(j->trofeo_y < j->enemigos_y[i]) dy = -1;
        }
        else
        {
            // comportamiento normal: perseguir jugador
            if(j->jugador_x > j->enemigos_x[i]) dx = 1;
            if(j->jugador_x < j->enemigos_x[i]) dx = -1;

            if(j->jugador_y > j->enemigos_y[i]) dy = 1;
            if(j->jugador_y < j->enemigos_y[i]) dy = -1;
        }

        int nx = j->enemigos_x[i] + dx;
        int ny = j->enemigos_y[i] + dy;

        if(!juego_es_pared(j,nx,ny)){
            j->enemigos_x[i] = nx;
            j->enemigos_y[i] = ny;
        }

        // enemigo captura trofeo
        if(j->enemigos_x[i] == j->trofeo_x &&
           j->enemigos_y[i] == j->trofeo_y){

            printf("Enemigo capturo trofeo\n");

            j->enemigos_trofeos[i]++;

            juego_generar_trofeo(j);
        }

        // reproducción enemigo
        if(j->enemigos_trofeos[i] >= 2 &&
           j->num_enemigos < MAX_ENEMIGOS){

            int nuevo = j->num_enemigos;

            j->enemigos_x[nuevo] = ANCHO-2;
            j->enemigos_y[nuevo] = ALTO-2;
            j->enemigos_trofeos[nuevo] = 0;

            j->num_enemigos++;

            j->enemigos_trofeos[i] = 0;

            printf("Un enemigo se reprodujo\n");
        }

        // colisión con jugador
        if(j->enemigos_x[i] == j->jugador_x &&
           j->enemigos_y[i] == j->jugador_y){

            printf("¡Un enemigo te atrapó!\n");

            j->vidas--;

            if(j->trofeos_recogidos > 0)
                j->trofeos_recogidos--;

            j->jugador_x = 1;
            j->jugador_y = 1;

            if(j->vidas <= 0){
                printf("GAME OVER\n");
                j->estado = ESTADO_MENU;
            }
        }
    }
}