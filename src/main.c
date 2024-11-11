#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   // Para sleep (delay)
#include <time.h>     // Para srand e rand
#include <string.h>   // Para manipulação de strings

// Bibliotecas personalizadas
#include "screen.h"   // Para manipulação da tela
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
    printf("   \\ |_____|//   \n");
    printf("      | | |      \n");
    printf("     /  |  \\     \n");
    printf("    /   |   \\    \n");
    printf("   | /\\ | /\\ |   \n");
    printf("   |/  \\|/  \\|   \n");
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

    printf("Bem-vindo à missão **CODEMASTER-QUEST**!\n\n");

    printf("Você é um astronauta da NASA, convocado para uma missão ultrassecreta.\n");
    printf("Sua jornada começa no misterioso planeta C, onde desafios inesperados aguardam\n");
    printf("a sua coragem e inteligência. Para seguir em frente, você precisará navegar por esse\n");
    printf("território desconhecido, superando tudo o que se interpuser entre você e sua nave.\n\n");

    printf("Prepare-se para uma aventura épica, onde cada passo é crucial. O destino do seu futuro está\n");
    printf("em suas mãos.Sua jornada até o planeta Java exige astúcia, coragem (bote coragem nisso) e habilidade.\n\n");

    printf("Instruções de controle:\n");
    printf(" - Use as teclas:\n");
    printf("   'W' para mover para cima\n");
    printf("   'A' para mover para a esquerda\n");
    printf("   'S' para mover para baixo\n");
    printf("   'D' para mover para a direita\n\n");

    printf("Você está pronto para começar sua jornada?\n");
    printf("Aperte ENTER para começar!\n");
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

int x = 25, y = 15;  // Posição inicial do jogador

// ** Mapas corrigidos para ter as portas nas mesmas coordenadas **
char map[MAP_HEIGHT][MAP_WIDTH] = {
    "##################################################",
    "#                                                #",
    "#  Qual eh o maior planeta do sistema solar?     #",
    "#    Porta 1 = Jupiter                           #",
    "#    Porta 2 = Saturno                           #",
    "#    Porta 3 = Marte                             #",
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
    "#                                                #",
    "##################################################"
};
char map_2[MAP_HEIGHT][MAP_WIDTH] = {
    "##################################################",
    "#                                                #",
    "#  Quantas luas tem Saturno?                     #",
    "#    Porta 1 = 82                                #",
    "#    Porta 2 = 62                                #",
    "#    Porta 3 = 72                                #",
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

char map_3[MAP_HEIGHT][MAP_WIDTH] = {
    "##################################################",
    "#                                                #",
    "#  Qual eh o nome da primeira nave               #",
    "#  tripulada a pousar na Lua?                    #",
    "#                                                #",
    "#  Porta 1 = Vostok 1                            #",
    "#  Porta 2 = Apolo 11                            #",
    "#  Porta 3 = Soyuz                               #",
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
    "##################################################"
};


// Função para exibir o mapa com base no nível atual
// Função para exibir o mapa com base no nível atual
void display_map(int level) {
    screenClear();
    char (*current_map)[MAP_WIDTH];

    // Escolher o mapa com base no nível
    if (level == 1) {
        current_map = map;
    } else if (level == 2) {
        current_map = map_2;
    } else if (level == 3) {
        current_map = map_3;
    }

    // Exibe o mapa
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (i == y && j == x) {
                printf("%c", PLAYER);  // Desenha o jogador
            } else {
                printf("%c", current_map[i][j]);
            }
        }
        printf("\n");
    }
    screenUpdate();
}

// Variável para rastrear o nível atual
int current_level = 1;

// Função para verificar se a posição é válida (não ultrapassando barreiras)
int isValidMove(int new_x, int new_y) {
    char (*current_map)[MAP_WIDTH] = (current_level == 1) ? map : map_2;
    return current_map[new_y][new_x] != '#';  // Verifica se a posição não é uma barreira
}

void checkDoor() {
    if (current_level == 1) {
        // Porta 1 da fase 1
        if (x == 7 && y == 7) {  // Porta 1, número 1
            printf("Você escolheu a Porta 1: Júpter\n");
            sleep(2);  // Delay para visualização da resposta
            current_level = 2;  // Transição para o próximo nível
            x = 25; y = 15;  // Resetando a posição do jogador para a inicial
            display_map(current_level);  // Atualiza o mapa
        }
        // Porta 2 da fase 1
        else if (x == 24 && y == 7) {  // Porta 2, número 2
            printf("Você escolheu a Porta 2: Saturno\n");
        }
        // Porta 3 da fase 1
        else if (x == 41 && y == 7) {  // Porta 3, número 3
            printf("Você escolheu a Porta 3: Marte\n");
        }
    }
    else if (current_level == 2) {
        // Porta 1 da fase 2
        if (x == 7 && y == 7) {  // Porta 1, número 1
            printf("Você escolheu a Porta 1: 82\n");
            sleep(2);  // Delay para visualização da resposta
            current_level = 3;  // Transição para o próximo nível
            x = 25; y = 15;  // Resetando a posição do jogador para a inicial
            display_map(current_level);  // Atualiza o mapa
        }
        // Porta 2 da fase 2
        else if (x == 24 && y == 7) {  // Porta 2, número 2
            printf("Você escolheu a Porta 2: 62\n");
        }
        // Porta 3 da fase 2
        else if (x == 41 && y == 7) {  // Porta 3, número 3
            printf("Você escolheu a Porta 3: 72\n");
        }
    }
    else if (current_level == 3) {
        // Porta 1 da fase 3
        if (x == 7 && y == 9) {  // Porta 1, número 1
            printf("Você escolheu a Porta 1 Vostok 1\n");
        }
        // Porta 2 da fase 3
        else if (x == 24 && y == 9) {  // Porta 2, número 2
            printf("Você escolheu a Porta 2: Apolo 11\n");
        }
        // Porta 3 da fase 3
        else if (x == 41 && y == 9) {  // Porta 3, número 3
            printf("Você escolheu a Porta 3: Soyus\n");
        }
    }
}

// Função para mover o jogador
void move_player(int direction) {
    int new_x = x, new_y = y;

    if (direction == 65 && y > 1) {          // Cima
        new_y = y - 1;
    } else if (direction == 66 && y < MAP_HEIGHT - 3) { // Ajuste na verificação para o limite inferior
        new_y = y + 1;
    } else if (direction == 67 && x < MAP_WIDTH - 2) {  // Direita
        new_x = x + 1;
    } else if (direction == 68 && x > 1) {   // Esquerda
        new_x = x - 1;
    }

    if (isValidMove(new_x, new_y)) {
        x = new_x;
        y = new_y;
    }
}

// Função principal
int main() {
    // Exibe a tela inicial
    displayStartScreen();
    getchar();  // Aguarda o usuário apertar ENTER

    // Animação do foguete
    for (int i = 10; i >= 1; i--) {
        clearScreen();
        drawStars();
        drawPlanets();
        drawRocket(i);
        sleep(1); // Substituição de usleep por sleep com 1 segundo de pausa
    }

    // Mensagem final após animação
    displayFinalMessage();
    sleep(2);  // Aguarda um pouco antes de iniciar o jogo

    // Inicializações de tela, teclado e temporizador
    screenInit(1);
    keyboardInit();
    timerInit(30000);

    // Mensagem para verificar se a inicialização foi bem-sucedida
    printf("Tela e entrada de teclado inicializadas, aguardando movimentação...\n");

    // Exibe o mapa inicial
    display_map(current_level);

    int ch = 0;
    while (1) {
        // Verifica se há entrada de teclado
        if (keyhit()) {
            ch = readch();
            move_player(ch);

            // Exibe o mapa correto com base no nível atual
            display_map(current_level);
            checkDoor();
        } else {
            // Mensagem de depuração caso o loop não entre na parte de movimentação
            sleep(0.1);  // Diminui a carga do processador com um pequeno delay
        }
    }

    return 0;
}
