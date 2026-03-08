#include "juego.h"
#include "render.h"
#include "entrada.h"
#include <stdio.h>

// Funcion auxiliar para convertir una tecla a desplazamiento
static int tecla_a_vector(char tecla, int *dx, int *dy){
    *dx = 0;
    *dy = 0;

    if(tecla == 'w' || tecla == 'W'){
        *dy = -1; return 1;
    } else if(tecla == 's' || tecla == 'S'){
        *dy = 1;  return 1;
    } else if(tecla == 'a' || tecla == 'A'){
        *dx = -1; return 1;
    } else if(tecla == 'd' || tecla == 'D'){
        *dx = 1;  return 1;
    }
    return 0; // Tecla no reconocida
}

// ====== Funciones del menu ======
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

            if(tecla == '1'){
                juego.estado = ESTADO_JUGANDO;
            }
            else if(tecla == '2'){
                juego.estado = ESTADO_INSTRUCCIONES;
            }
            else if(tecla == '3'){
                juego.estado = ESTADO_SALIR;
            }
        }

        else if(juego.estado == ESTADO_INSTRUCCIONES){
            mostrar_instrucciones();
            entrada_leer_tecla(); // esperar tecla
            juego.estado = ESTADO_MENU;
        }

        else if(juego.estado == ESTADO_JUGANDO){

            render_juego(&juego);

            char tecla = entrada_leer_tecla();
            juego.ultima_tecla = tecla;

            if(tecla == 'q' || tecla == 'Q'){
                printf("Seguro que quieres salir? (y/n)\n");
                char confirm = entrada_leer_tecla();

                if(confirm == 'y' || confirm == 'Y'){
                    juego.estado = ESTADO_MENU;
                }
                continue;
            }

            int dx, dy;

            if(tecla_a_vector(tecla, &dx, &dy)){
                juego_intentar_mover(&juego, dx, dy);
            }
            else{
                printf("Comando no valido\n");
            }
        }
    }

    return 0;
}