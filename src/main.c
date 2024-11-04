#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

#define MAX_QUESTIONS 10
#define MAX_LENGTH 100

typedef struct {
    char question[MAX_LENGTH];
    char options[3][MAX_LENGTH];
    int correct_option; // Índice da opção correta (0, 1 ou 2)
} Question;

// Coordenadas iniciais da letra "P" (posição do jogador)
int x = 20, y = 12;

// Coordenadas das portas e limites para interação
const int door1_x = 15, door2_x = 40, door3_x = 65;
const int door_width = 10; // Largura das portas
const int door_y = 16;     // Linha das portas

void display_question(Question *q) {
    screenClear();
    printf("Pergunta: %s\n", q->question);
    printf("Pressione as setas para mover e entre em uma porta para responder.\n\n");
    
    // Desenha as portas com as alternativas
    printf("+-----------+    +-----------+    +-----------+\n");
    printf("|    Porta 1|    |    Porta 2|    |    Porta 3|\n");
    printf("| %s |    | %s |    | %s |\n",
           q->options[0], q->options[1], q->options[2]);
    printf("+-----------+    +-----------+    +-----------+\n");

    screenUpdate();
}

void load_questions(Question *questions, int *num_questions) {
    strcpy(questions[0].question, "Qual é a capital da França?");
    strcpy(questions[0].options[0], "Paris");
    strcpy(questions[0].options[1], "Londres");
    strcpy(questions[0].options[2], "Berlim");
    questions[0].correct_option = 0;

    *num_questions = 1; // Para o exemplo, apenas uma pergunta
}

void printCharacter() {
    screenSetColor(CYAN, DARKGRAY);
    screenGotoxy(x, y);
    printf("P"); // Desenha o caractere "P" na posição atual
    screenUpdate();
}

int main() {
    int ch = 0;
    Question questions[MAX_QUESTIONS];
    int num_questions = 0;

    load_questions(questions, &num_questions);
    screenInit(1);
    keyboardInit();
    timerInit(50);

    display_question(&questions[0]); // Exibe a pergunta
    printCharacter(); // Mostra o jogador inicialmente

    while (1) {
        if (keyhit()) {
            ch = readch();

            // Move o jogador com as setas
            if (ch == 65 && y > 1) {         // Seta para cima
                y--;
            } else if (ch == 66 && y < 20) { // Seta para baixo
                y++;
            } else if (ch == 67 && x < 80) { // Seta para a direita
                x++;
            } else if (ch == 68 && x > 1) {  // Seta para a esquerda
                x--;
            }

            screenClear();
            display_question(&questions[0]);
            printCharacter();

            // Verifica se o jogador está em uma das portas
            if (y == door_y) {
                int answer = -1;

                // Verifica se o jogador está na posição de uma das portas
                if (x >= door1_x && x <= door1_x + door_width) {
                    answer = 0; // Porta 1
                } else if (x >= door2_x && x <= door2_x + door_width) {
                    answer = 1; // Porta 2
                } else if (x >= door3_x && x <= door3_x + door_width) {
                    answer = 2; // Porta 3
                }

                if (answer != -1) {
                    screenClear();
                    if (answer == questions[0].correct_option) {
                        printf("Correto!\n");
                    } else {
                        printf("Incorreto! Tente novamente.\n");
                    }

                    // Pausa para mostrar o resultado antes de sair
                    printf("Pressione qualquer tecla para sair...\n");
                    while (!keyhit()) {
                        // Espera o usuário pressionar uma tecla
                    }
                    break; // Encerra o jogo
                }
            }

            screenUpdate();
        }
    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();

    return 0;
}



//cd ~/CODEMASTER-QUEST/src
//gcc -I../include main.c keyboard.c screen.c timer.c -o codemaster_quest
