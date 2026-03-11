#include "render.h"
#include "consola.h"
#include <stdio.h>

void render_juego(const Juego *j){

    consola_limpiar_simple();

    printf("Pasos: %d\n", j->pasos);
    printf("Posicion: (%d,%d)\n", j->jugador_x, j->jugador_y);
    printf("Ultima tecla: %c\n", j->ultima_tecla);
    printf("Choques: %d\n", j->choques);

    printf("Vidas: %d\n", j->vidas);
    printf("Trofeos: %d / 20\n\n", j->trofeos_recogidos);

    if (j->choques > 0)
        printf("Advertencia: chocaste contra una pared!\n\n");

    for(int y = 0; y < ALTO; y++){

        for(int x = 0; x < ANCHO; x++){

            if(x == j->jugador_x && y == j->jugador_y){
                putchar('@');
                continue;
            }

            int enemigo = 0;

            for(int i = 0; i < MAX_ENEMIGOS; i++){
                if(x == j->enemigos_x[i] && y == j->enemigos_y[i]){
                    putchar('E');
                    enemigo = 1;
                    break;
                }
            }

            if(enemigo) continue;

            if(x == j->trofeo_x && y == j->trofeo_y)
                putchar('T');
            else
                putchar(j->mapa[y][x]);
        }

        putchar('\n');
    }

    puts("\nControles: W A S D para mover, Q para salir");
}