/* Prototipo de videojuego en consola
Objetivos:
- Mostrar un mapa fijo en ASCII
- Dibujar al jugador @
- Mover con WASD
- Evitar paredes
- Recoger monedas *
*/

#include <stdio.h>
#include <string.h>

#define ALTO 10
#define ANCHO 20

/*Mapa fijo*/
static const char *MAPA_FIJO[ALTO] = {
    "####################",
    "#.............*....#",
    "#.######.########.#",
    "#.#....#.#......#.#",
    "#.#.##.#.#.####.#.#",
    "#...##...#....#...#",
    "#####.#########.###",
    "#.....#.......#...#",
    "#.#####.#####.###.#",
    "####################"};

static void consola_limpiar_simple(void)
{
    for (int i = 0; i < 40; i++)
        printf("\n");
}

static int es_pared(const char mapa[ALTO][ANCHO + 1], int x, int y)
{
    if (x < 0 || x >= ANCHO || y < 0 || y >= ALTO)
        return 1;

    return mapa[y][x] == '#';
}

static void renderizar(const char mapa[ALTO][ANCHO + 1], int jugador_x, int jugador_y, int pasos, int monedas)
{
    consola_limpiar_simple();

    printf("PASOS: %d | MONEDAS: %d\n\n", pasos, monedas);

    for (int y = 0; y < ALTO; y++)
    {
        for (int x = 0; x < ANCHO; x++)
        {
            if (x == jugador_x && y == jugador_y)
                putchar('@');
            else
                putchar(mapa[y][x]);
        }
        putchar('\n');
    }

    puts("\nControles: W A S D + Enter | Q para salir");
}

int main()
{
    int nx = 0, ny = 0;

    char mapa[ALTO][ANCHO + 1];

    for (int y = 0; y < ALTO; y++)
        strncpy(mapa[y], MAPA_FIJO[y], ANCHO + 1);

    int xJugador = 1;
    int yJugador = 1;

    int pasos = 0;
    int monedas = 0;

    char tecla;

    while (1)
    {
        renderizar(mapa, xJugador, yJugador, pasos, monedas);

        printf(">");
        tecla = ' ';

        if (scanf(" %c", &tecla) != 1)
            break;

        if (tecla == 'q' || tecla == 'Q')
            break;

        int dx = 0, dy = 0;

        if (tecla == 'w' || tecla == 'W')
            dy = -1;
        else if (tecla == 's' || tecla == 'S')
            dy = 1;
        else if (tecla == 'a' || tecla == 'A')
            dx = -1;
        else if (tecla == 'd' || tecla == 'D')
            dx = 1;

        nx = xJugador + dx;
        ny = yJugador + dy;

        if (!es_pared(mapa, nx, ny))
        {
            /* recoger moneda */
            if (mapa[ny][nx] == '*')
            {
                monedas++;
                mapa[ny][nx] = '.';
                printf("¡Moneda recogida!\n");
            }

            xJugador = nx;
            yJugador = ny;
            pasos++;
        }
        else
        {
            puts("¡No puedes atravesar paredes!");
        }
    }

    printf("\nJuego terminado.\n");
    printf("Pasos dados: %d\n", pasos);
    printf("Monedas recogidas: %d\n", monedas);

    return 0;
}