#include "juego.h"
#include "render.h"
#include "entrada.h"
#include <stdio.h>

static int tecla_a_vector(char tecla,int *dx,int *dy){

    *dx = 0;
    *dy = 0;

    if(tecla=='w'||tecla=='W'){*dy=-1;return 1;}
    if(tecla=='s'||tecla=='S'){*dy=1;return 1;}
    if(tecla=='a'||tecla=='A'){*dx=-1;return 1;}
    if(tecla=='d'||tecla=='D'){*dx=1;return 1;}

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
    printf("P para pausar\n");
}

int main(){

    Juego juego;

    juego_inicializar(&juego);

    while(juego.estado != ESTADO_SALIR){

        if(juego.estado == ESTADO_MENU){

            mostrar_menu();

            char t = entrada_leer_tecla();

            if(t=='1') juego.estado = ESTADO_JUGANDO;
            if(t=='2') juego.estado = ESTADO_INSTRUCCIONES;
            if(t=='3') juego.estado = ESTADO_SALIR;
        }

        else if(juego.estado == ESTADO_INSTRUCCIONES){

            mostrar_instrucciones();

            entrada_leer_tecla();

            juego.estado = ESTADO_MENU;
        }

        else if(juego.estado == ESTADO_JUGANDO){

            render_juego(&juego);

            char tecla = entrada_leer_tecla();

            if(tecla=='p'||tecla=='P'){
                printf("\nPAUSA: [C] Continuar [G] Guardar [L] Cargar [Q] Salir\n");
                juego.estado = ESTADO_PAUSA;
                continue;
            }

            int dx,dy;

            if(tecla_a_vector(tecla,&dx,&dy))
                juego_intentar_mover(&juego,dx,dy);

                
                

            juego_mover_enemigos(&juego);
        }

        else if(juego.estado == ESTADO_PAUSA){

            char t = entrada_leer_tecla();

            if(t=='c'||t=='C')
                juego.estado = ESTADO_JUGANDO;

            if(t=='g'||t=='G')
                juego_guardar(&juego);

            if(t=='l'||t=='L'){
                if(juego_cargar(&juego))
                    juego.estado = ESTADO_PAUSA;
            }

            if(t=='q'||t=='Q')
                juego.estado = ESTADO_MENU;
        }
    }

    return 0;
}
