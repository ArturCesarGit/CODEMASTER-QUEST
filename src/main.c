#include <stdio.h>
#include <stdlib.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

// Definindo dimensões do mapa
#define MAP_WIDTH 50   // Largura do mapa
#define MAP_HEIGHT 30  // Altura do mapa

// Definindo os símbolos no mapa
#define EMPTY ' '
#define PLAYER 'P'

// Coordenadas iniciais do jogador
int x = 25, y = 15;  // O jogador começa no meio do mapa

// Mapa representado como matriz de strings
char map[MAP_HEIGHT][MAP_WIDTH] = {
    "##################################################",  // Linha 0
    "#                                                #",  // Linha 1
    "#  Qual eh a capital do Brasil?                  #",  // Linha 2 
    "#                                                #",  // Linha 3
    "#  Porta 1 = Brasilia                            #",  // Linha 4 
    "#  Porta 2 = Paris                               #",  // Linha 5 
    "#  Porta 3 = Londres                             #",  // Linha 6 
    "#                                                #",  // Linha 7
    "#                                                #",  // Linha 8
    "#     [1]              [2]              [3]      #",  // Linha 9 
    "#                                                #",  // Linha 10
    "#                                                #",  // Linha 11
    "#                                                #",  // Linha 12
    "#                                                #",  // Linha 13
    "#                                                #",  // Linha 14
    "#                                                #",  // Linha 15
    "#                                                #",  // Linha 16
    "#                                                #",  // Linha 17
    "#                                                #",  // Linha 18
    "#                                                #",  // Linha 19
    "#                                                #",  // Linha 20
    "#                                                #",  // Linha 21
    "#                                                #",  // Linha 22
    "#                                                #",  // Linha 23
    "#                                                #",  // Linha 24
    "##################################################"   // Linha 25 
};

// Função para exibir o mapa
void display_map() {
    screenClear();
    // Desenha o mapa linha por linha
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (i == y && j == x) {
                printf("%c", PLAYER); // Desenha o jogador
            } else {
                printf("%c", map[i][j]); // Desenha o que está no mapa
            }
        }
        printf("\n");
    }

    screenUpdate();
}

// Função para verificar se o jogador entrou em uma porta
void checkDoor() {
    if (y == 9) {  // Verifica se o jogador está na linha das portas
        if (x >= 7 && x <= 8) {  // Porta 1 
            printf("Parabéns! Você escolheu a resposta correta: Brasília.\n");
            printf("Você continua o jogo.\n");
            return;  // Continua o jogo
        } else if (x >= 15 && x <= 16) {  // Porta 2 
            printf("Você escolheu a resposta errada: Paris.\n");
            printf("Fim do jogo.\n");
            exit(0); // Encerra o programa
        } else if (x >= 23 && x <= 24) {  // Porta 3 
            printf("Você escolheu a resposta errada: Londres.\n");
            printf("Fim do jogo.\n");
            exit(0); 
        }
    }
}

void move_player(int direction) {
    int new_x = x, new_y = y;

    // Determina a nova posição com base na direção
    if (direction == 65 && y > 1) {         // Seta para cima
        new_y = y - 1;
    } else if (direction == 66 && y < MAP_HEIGHT - 2) { // Seta para baixo
        new_y = y + 1;
    } else if (direction == 67 && x < MAP_WIDTH - 2) { // Seta para a direita
        new_x = x + 1;
    } else if (direction == 68 && x > 1) {  // Seta para a esquerda
        new_x = x - 1;
    }

    // Atualiza a posição do jogador
    x = new_x;
    y = new_y;
}

int main() {
    int ch = 0;

    screenInit(1);
    keyboardInit();
    timerInit(30000); // Tempo de 30 segundos para responder

    // Exibe o mapa
    display_map();

    // Controle de movimento do jogador
    while (1) {
        if (keyhit()) {
            ch = readch();

            // Move o jogador com as setas
            move_player(ch);

            // Atualiza a tela
            display_map();

            // Verifica se o jogador entrou em uma porta
            checkDoor();
        }
    }

    return 0;
}
