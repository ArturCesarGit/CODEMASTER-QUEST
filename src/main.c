#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // Para usleep (delay)
#include <time.h>    // Para srand e rand
#include <string.h>  // Para manipulação de strings

// Bibliotecas personalizadas
#include "screen.h"  // Para manipulação da tela
#include "keyboard.h" // Para manipulação do teclado
#include "timer.h"    // Para manipulação de temporizadores

// ** Funções relacionadas à animação do foguete **
void clearScreen() {
    printf("\033[H\033[J");  // Limpa a tela
}

void drawStars() {
    int i, j;
    int width = 80;
    int height = 24;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            if (rand() % 50 == 0) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void drawPlanets() {
    int planets[5][2] = {
        {15, 5}, {40, 10}, {60, 15}, {25, 18}, {70, 8}
    };

    for (int i = 0; i < 5; i++) {
        printf("\033[%d;%dH", planets[i][1], planets[i][0]);
        printf("O");
    }
}

void drawRocket(int y_position) {
    printf("\033[%d;10H", y_position); // Mover para a linha especificada
    printf("                 \n");
    printf("        |        \n");
    printf("       / \\       \n");
    printf("      /   \\      \n");
    printf("     | O O |     \n");
    printf("     |  O  |     \n");
    printf("     | O O |     \n");
    printf("     |     |     \n");
    printf("    /|-----|\\    \n");
    printf("   / |     | \\   \n");
    printf("  |  |     |  |  \n");
    printf("  |  |     |  |  \n");
    printf("  |  |     |  |  \n");
    printf("   \\|_|/   \n");
    printf("      | | |      \n");
    printf("     /  |  \\     \n");
    printf("    /   |   \\    \n");
    printf("   |    |    |   \n");
    printf("   |    |    |   \n");
}

void displayStartScreen() {
    clearScreen();
    printf("\n\n\n");
    printf("   CCCCC  OOO   DDDD   EEEEE   M   M   AAAAA   SSSSS  TTTTT  EEEEE  RRRRR   \n");
    printf("  C      O   O  D   D  E       MM MM  A     A  S        T    E      R    R  \n");
    printf("  C      O   O  D   D  EEEE    M M M  AAAAAAA  SSSSS    T    EEEE   RRRRR   \n");
    printf("  C      O   O  D   D  E       M   M  A     A      S    T    E      R  R    \n");
    printf("   CCCCC  OOO   DDDD   EEEEE   M   M  A     A  SSSSS    T    EEEEE  R   R   \n");
    printf("\n");
    printf("                Aperte ENTER para começar!               \n");
}

void displayFinalMessage() {
    clearScreen();
    printf("\n");
    printf("Sua jornada espacial acaba de começar!\n");
}

// ** Funções relacionadas ao mapa e ao jogador **
#define MAP_WIDTH 50
#define MAP_HEIGHT 30
#define EMPTY ' '
#define PLAYER 'P'

int x = 25, y = 15;

char map[MAP_HEIGHT][MAP_WIDTH] = {
    "##################################################",
    "#                                                #",
    "#  Qual eh a capital do Brasil?                  #",
    "#                                                #",
    "#  Porta 1 = Brasilia                            #",
    "#  Porta 2 = Paris                               #",
    "#  Porta 3 = Londres                             #",
    "#                                                #",
    "#                                                #",
    "#     [1]              [2]              [3]      #",
    "#                                                #",
    "#                                                #",
    "#                                                #",
    "#                                                #",
    "#                                                #",
    "#                                                #",
    "#                                                #",
    "#                                                #",
    "#                                                #",
    "#                                                #",
    "#                                                #",
    "#                                                #",
    "#                                                #",
    "#                                                #",
    "##################################################"
};

void display_map() {
    screenClear();
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (i == y && j == x) {
                printf("%c", PLAYER);
            } else {
                printf("%c", map[i][j]);
            }
        }
        printf("\n");
    }
    screenUpdate();
}

void checkDoor() {
    if (y == 9) {
        if (x >= 7 && x <= 8) {
            printf("Parabéns! Você escolheu a resposta correta: Brasília.\n");
            printf("Você continua o jogo.\n");
        } else if (x >= 15 && x <= 16) {
            printf("Você escolheu a resposta errada: Paris.\nFim do jogo.\n");
            exit(0);
        } else if (x >= 23 && x <= 24) {
            printf("Você escolheu a resposta errada: Londres.\nFim do jogo.\n");
            exit(0);
        }
    }
}

void move_player(int direction) {
    int new_x = x, new_y = y;

    if (direction == 65 && y > 1) {
        new_y = y - 1;
    } else if (direction == 66 && y < MAP_HEIGHT - 2) {
        new_y = y + 1;
    } else if (direction == 67 && x < MAP_WIDTH - 2) {
        new_x = x + 1;
    } else if (direction == 68 && x > 1) {
        new_x = x - 1;
    }

    x = new_x;
    y = new_y;
}

// ** Função principal para execução do jogo **
int main() {
    displayStartScreen();
    getchar();

    for (int i = 20; i >= 1; i--) {
        clearScreen();
        drawStars();
        drawPlanets();
        drawRocket(i);
        usleep(500000);
    }

    displayFinalMessage();
    usleep(2000000);

    screenInit(1);
    keyboardInit();
    timerInit(30000);

    display_map();

    int ch = 0;
    while (1) {
        if (keyhit()) {
            ch = readch();
            move_player(ch);
            display_map();
            checkDoor();
        }
    }

    return 0;
}
