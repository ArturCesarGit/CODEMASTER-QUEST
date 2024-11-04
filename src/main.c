/**
 * main.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
 */

#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

// Coordenadas iniciais da letra "P"
int x = 34, y = 12;

void printCharacter(int posX, int posY) {
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(x, y);
    printf(" "); // Limpa a posição anterior
    x = posX;
    y = posY;
    screenGotoxy(x, y);
    printf("P"); // Desenha o caractere "P" na nova posição
}

int main() {
    int ch = 0;
    int newX = x, newY = y;

    screenInit(1);
    keyboardInit();
    timerInit(50);

    printCharacter(x, y);
    screenUpdate();

    while (ch != 10) { // Loop até o usuário pressionar Enter (código 10)
        // Lê a entrada do usuário
        if (keyhit()) {
            ch = readch();

            // Ajusta as coordenadas com base na tecla pressionada
            if (ch == 65) {         // Seta para cima
                newY = y - 1;
            } else if (ch == 66) {  // Seta para baixo
                newY = y + 1;
            } else if (ch == 67) {  // Seta para a direita
                newX = x + 1;
            } else if (ch == 68) {  // Seta para a esquerda
                newX = x - 1;
            }

            // Limita a posição para ficar dentro dos limites da tela
            if (newX < MINX) newX = MINX;
            if (newX > MAXX - 1) newX = MAXX - 1;
            if (newY < MINY) newY = MINY;
            if (newY > MAXY - 1) newY = MAXY - 1;

            // Atualiza a posição e exibe o caractere "P"
            printCharacter(newX, newY);
            screenUpdate();
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}


