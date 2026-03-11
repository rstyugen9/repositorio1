#include "juego.h"
#include "render.h"
#include "entrada.h"
#include <stdio.h>

static int tecla_a_vector(char tecla, int *dx, int *dy){
    *dx = 0;
    *dy = 0;

    if(tecla == 'w' || tecla == 'W'){ *dy = -1; return 1; }
    if(tecla == 's' || tecla == 'S'){ *dy = 1;  return 1; }
    if(tecla == 'a' || tecla == 'A'){ *dx = -1; return 1; }
    if(tecla == 'd' || tecla == 'D'){ *dx = 1;  return 1; }

    return 0;
}

void mostrar_menu(){
    printf("===== MENU =====\n");
    printf("1 - Jugar\n");
    printf("2 - Instrucciones\n");
    printf("3 - Salir\n");
}

void mostrar_instrucciones(){
    printf("INSTRUCCIONES\n");
    printf("W A S D para moverte\n");
    printf("Evita chocar contra paredes\n");
    printf("Q para volver al menu\n");
}

int main(void){

    Juego juego;
    juego_inicializar(&juego);

    while(juego.estado != ESTADO_SALIR){

        if(juego.estado == ESTADO_MENU){

            mostrar_menu();
            char tecla = entrada_leer_tecla();

            if(tecla == '1') juego.estado = ESTADO_JUGANDO;
            else if(tecla == '2') juego.estado = ESTADO_INSTRUCCIONES;
            else if(tecla == '3') juego.estado = ESTADO_SALIR;
        }

        else if(juego.estado == ESTADO_INSTRUCCIONES){

            mostrar_instrucciones();
            entrada_leer_tecla();
            juego.estado = ESTADO_MENU;
        }

        else if(juego.estado == ESTADO_JUGANDO){

            render_juego(&juego);

            char tecla = entrada_leer_tecla();
            juego.ultima_tecla = tecla;

            if(tecla == 'q' || tecla == 'Q'){
                printf("Seguro que quieres salir? (y/n)\n");

                char confirm = entrada_leer_tecla();

                if(confirm == 'y' || confirm == 'Y')
                    juego.estado = ESTADO_MENU;

                continue;
            }

            int dx, dy;

            if(tecla_a_vector(tecla, &dx, &dy))
                juego_intentar_mover(&juego, dx, dy);
            else
                printf("Comando no valido\n");

            // movimiento automático enemigos
            juego_mover_enemigos(&juego);
        }
    }

    return 0;
}