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
    printf("   \\ |_|//   \n");
    printf("      | | |      \n");
    printf("     /  |  \\     \n");
    printf("    /   |   \\    \n");
    printf("   | /\\ | /\\ |   \n");
    printf("   |/  \\|/  \\|   \n");
}



void drawRocketLanding(int x_position, int y_position) {
    printf("\033[%d;%dH", y_position, x_position);  // Posiciona o foguete
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
    printf("   \\ |_|//   \n");
    printf("      | | |      \n");
    printf("     /  |  \\     \n");
    printf("    /   |   \\    \n");
    printf("   | /\\ | /\\ |   \n");
    // Aqui está a linha corrigida para que o foguete fique acima do chão
    printf("   |/  \\|/  \\|   \n");
}

// Função para desenhar a pista de pouso (parte branca)
void drawRunway() {
    printf("\033[23;0H");  // Coloca o cursor na linha 23, do início
    for (int i = 0; i < 80; i++) {
        printf("=");
    }
}

void displayWinMessage() {
    clearScreen();
    drawStars();  // Desenha as estrelas no fundo

    // Desenha os planetas (opcional)
    drawPlanets();

    // Simula o foguete indo de cima para baixo, como se fosse de ré
    for (int i = 1; i <= 5; i++) {  // Começa na linha 1 e vai até a linha 15
        clearScreen();  // Limpa a tela a cada novo quadro
        drawStars();    // Reexibe as estrelas
        drawPlanets();  // Reexibe os planetas
        drawRocketLanding(35, i);  // Desenha o foguete indo para baixo
        drawRunway();  // Desenha a pista de pouso
        sleep(1);       // Pausa de 1 segundo entre cada movimento
    }

    // Exibe a mensagem de vitória após o foguete pousar
    clearScreen();
    drawStars();
    drawPlanets();
    drawRocketLanding(35, 5);  // Foguete pousado na linha 15 (base do foguete na linha 23)
    drawRunway();  // Desenha a pista de pouso
    printf("\n\n");
    printf("\tO SEU FOGUETE TEM RÉ!\n");
    printf("\tPARABÉNS, VOCÊ COMPLETOU SUA MISSÃO E CHEGOU AO PLANETA JAVA!\n");
    sleep(3); // Exibe a mensagem por alguns segundos

    // Finaliza o jogo
    printf("\nEncerrando o jogo...\n");
    sleep(1);  // Pausa rápida antes de encerrar
    exit(0);   // Encerra o programa com código 0 (sucesso)
}



void displaySystemError() {
    clearScreen();

    // Desabilitar a leitura de teclado enquanto a animação estiver rodando
    keyboardDestroy();  // Desativa a leitura de teclado

    // Animação de falha no sistema, nave se separando
    for (int i = 0; i < 5; i++) {
        clearScreen();
        drawStars();  // Exibe o fundo estrelado
        drawPlanets(); // Exibe os planetas

        // Primeira etapa: Nave intacta
        if (i == 0) {
            drawRocket(10);  // Desenha a nave intacta
            printf("\033[10;10H");
            printf("PANE NO SISTEMA\n");
        }
        // Segunda etapa: Topo da nave começa a se separar
        else if (i == 1) {
            clearScreen();
            drawStars();
            drawPlanets();
            
            // A nave começa a se separar
            printf("\033[8;10H");
            printf("       |        \n");  // Desenha o topo da nave
            printf("      / \\       \n");
            printf("     /   \\      \n");
            printf("    | O O |     \n");
            printf("    |  O  |     \n");
            printf("    | O O |     \n");
            printf("    |     |     \n");

            // Corpo da nave com 'X'
            printf("\033[10;10H");
            printf("   /|-----|\\    \n");
            printf("  / |  X  | \\   \n");  // Corpo danificado com 'X'
            printf(" |  |  X  |  |  \n");
            printf(" |  |  X  |  |  \n");
            printf("  \\ |_|//   \n");

            // Cauda separando
            printf("\033[14;10H");
            printf("     | X |      \n");
            printf("    /  |  \\     \n");
            printf("   /   |   \\    \n");

            printf("\033[10;10H");
            printf("ERRO! TOPO SEPARADO!\n");

            sleep(1); // Pausa para o efeito de separação
            clearScreen();
        }
        // Terceira etapa: Corpo da nave se separando, cauda já se foi
        else if (i == 2) {
            clearScreen();
            drawStars();
            drawPlanets();
            
            // Topo da nave ainda está lá, mas o corpo continua danificado
            printf("\033[8;10H");
            printf("       |        \n");
            printf("      / \\       \n");
            printf("     /   \\      \n");
            printf("    | X X |     \n");  // Corpo da nave com mais 'X'
            printf("    |  X  |     \n");
            printf("    | X X |     \n");

            // Corpo da nave com 'X' e danificado
            printf("\033[10;10H");
            printf("   /|-----|\\    \n");
            printf("  / |  X  | \\   \n");
            printf(" |  |  X  |  |  \n");
            printf(" |  |  X  |  |  \n");
            printf("  \\ |_|//   \n");

            // A cauda já desapareceu
            printf("\033[14;10H");
            printf("     | X |      \n");

            printf("\033[10;10H");
            printf("FALHA CRÍTICA! CAUDA PERDIDA!\n");

            sleep(1); // Pausa para o efeito de separação
            clearScreen();
        }
        // Quarta etapa: Corpo da nave quase todo destruído
        else if (i == 3) {
            clearScreen();
            drawStars();
            drawPlanets();
            
            // O topo da nave ainda está lá, mas o corpo continua danificado
            printf("\033[8;10H");
            printf("       |        \n");
            printf("      / \\       \n");
            printf("     /   \\      \n");
            printf("    | X X |     \n");
            printf("    |  X  |     \n");
            printf("    | X X |     \n");

            // O corpo quase desapareceu
            printf("\033[10;10H");
            printf("   /|--X--|\\    \n");
            printf("  / |  X  | \\   \n");
            printf(" |  |  X  |  |  \n");
            printf(" |  |  X  |  |  \n");
            printf("  \\ |--X--|//   \n");

            // A cauda não está mais visível
            printf("\033[14;10H");
            printf("     | X |      \n");

            printf("\033[10;10H");
            printf("DANOS EXTREMOS! NAVE A PONTO DE EXPLOSÃO!\n");

            sleep(1); // Pausa para o efeito de separação
            clearScreen();
        }
        // Quinta etapa: Nave totalmente destruída, partes soltas
        else if (i == 4) {
            clearScreen();
            drawStars();
            drawPlanets();
            
            // Corpo da nave destruído
            printf("\033[8;10H");
            printf("       |        \n");
            printf("      / \\       \n");
            printf("     /   \\      \n");
            printf("    | X X |     \n");
            printf("    |  X  |     \n");
            printf("    | X X |     \n");

            // O corpo agora está completamente destruído
            printf("\033[10;10H");
            printf("   /|--X--|\\    \n");
            printf("  / |  X  | \\   \n");
            printf(" |  |  X  |  |  \n");
            printf(" |  |  X  |  |  \n");
            printf("  \\ |--X--|//   \n");

            // A cauda se desintegrou completamente
            printf("\033[14;10H");
            printf("     | X |      \n");

            printf("\033[10;10H");
            printf("NAVE DESTRUÍDA! FIM DE MISSÃO!\n");

            sleep(2);  // Pausa antes de reiniciar a interação ou nível
        }

        sleep(1);  // Pausa para o efeito de cada "quebra"
    }

    // Após a animação, exibe mensagem de "reiniciando" e aguarda
    printf("\033[13;10H");
    printf("SISTEMA CRÍTICO! REINICIANDO...\n");
    sleep(3);

    // Após a animação terminar, o programa simplesmente se encerra
    // Isso impede qualquer interação subsequente
    printf("\033[?25h");  // Torna o cursor visível novamente
    screenClear();  // Limpa a tela final

    // Destrói o terminal e encerra o programa sem permitir novas interações
    exit(0);  // Finaliza o programa, sem permitir que o jogador interaja até reiniciar manualmente
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

    printf("Bem-vindo à missão *CODEMASTER-QUEST*!\n\n");

    printf("Você é um astronauta de uma organização chamada 'C' e foi convocado para uma missão ultrassecreta.\n");
    printf("Sua jornada começa no misterioso planeta HASKELL, onde desafios inesperados aguardam\n");
    printf("a sua coragem e inteligência. Seu destino final será o planeta JAVA, onde descobrimos ter uma tecnologia alienígena que destruiria toda a galáxia se parar nas mãos erradas.\n");
    printf("Para seguir em frente, você precisará navegar por esse território desconhecido, superando tudo o que se interpuser entre você e sua nave.\n\n");

    printf("Prepare-se para uma aventura épica, onde cada passo é crucial. O destino do futuro da galáxia está\n");
    printf("em suas mãos. Sua jornada até o planeta Java exige astúcia, coragem (bote coragem nisso) e habilidade (até demais)\n");
    printf("BOA SORTE, AGENTE\n\n");

    printf("Instruções de controle:\n");
    printf(" - Use as teclas:\n");
    printf("   '↑' para mover para cima\n");
    printf("   '←' para mover para a esquerda\n");
    printf("   '↓' para mover para baixo\n");
    printf("   '→' para mover para a direita\n\n");

    printf("Para selecionar uma porta, basta ficar em cima dela por alguns segundos\n");
    printf("Nao se preocupe com outros botoes inicialmente.\n\n");

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
#define PLAYER "\033[1;35m\u0D9E\033[0m"  // Boneco com a mesma cor da parede
#define WALL_COLOR "\033[1;35m█\033[0m"

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
#define TAMANHO_GRADE 5
#define MAX_TENTATIVAS 5  // Número máximo de tentativas

// Função para exibir a introdução do jogo
void IntroducaoMinijogo1() {
    printf("\n");
    printf("Bem-vindo ao jogo de Adivinhação Espacial!\n");
    printf("Agente, sua missão foi descoberta por uma organização inimiga chamada Python.\n");
    printf("Eles querem ser a primeira organização a chegar no planeta Java e tomar o controle de tudo.\n");
    printf("A nave inimiga está escondida em um dos pontos de uma matriz 5x5. Sua tarefa é localizá-la e destruí-la\n");
    printf("antes que eles encontrem você. A pressão está alta, agente. Eles sabem onde você está!\n");
    printf("Você tem %d tentativas para encontrá-los e garantir sua vitória, antes que seja tarde demais.\n", MAX_TENTATIVAS);
    printf("Boa sorte na sua jornada, agente.\n");
    printf("\n");
    printf("As coordenadas vão de 0 a 4 (tanto para X quanto para Y).\n");
    printf("Digite as coordenadas X (horizontal) e depois Y (vertical) para tentar encontrar a nave inimiga.\n");
}

// Função para exibir a grade
void exibirMatriz(int grade[TAMANHO_GRADE][TAMANHO_GRADE], int tentativas[][2], int numTentativas, int tentativaX, int tentativaY, int coordenadaX, int coordenadaY, int acerto) {
    printf("\nGrade do Sistema Solar:\n");
    for (int i = 0; i < TAMANHO_GRADE; i++) {
        for (int j = 0; j < TAMANHO_GRADE; j++) {
            int tentado = 0;
            for (int t = 0; t < numTentativas; t++) {
                if (tentativas[t][0] == i && tentativas[t][1] == j) {
                    tentado = 1;
                    break;
                }
            }

            if (acerto && i == coordenadaX && j == coordenadaY) {
                printf("[N] ");
            } else if (tentado && !(i == tentativaX && j == tentativaY)) {
                printf("[X] ");
            } else if (i == tentativaX && j == tentativaY) {
                printf("[A] ");
            } else {
                printf("[ ] ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Função para verificar se uma coordenada já foi tentada
int coordenadaRepetida(int tentativas[][2], int tentativaX, int tentativaY, int numTentativas) {
    for (int i = 0; i < numTentativas; i++) {
        if (tentativas[i][0] == tentativaX && tentativas[i][1] == tentativaY) {
            return 1;
        }
    }
    return 0;
}

// Função para fornecer dicas de localização
void Dicas(int tentativaX, int tentativaY, int coordenadaX, int coordenadaY) {
    if (tentativaX < coordenadaX) {
        printf("O X da nave inimiga é maior que o X que você digitou.\n");
    } else if (tentativaX > coordenadaX) {
        printf("O X da nave inimiga é menor que o X que você digitou.\n");
    } else {
        printf("Você acertou o X da nave inimiga!\n");
    }

    if (tentativaY < coordenadaY) {
        printf("O Y da nave inimiga é maior que o Y que você digitou.\n");
    } else if (tentativaY > coordenadaY) {
        printf("O Y da nave inimiga é menor que o Y que você digitou.\n");
    } else {
        printf("Você acertou o Y da nave inimiga!\n");
    }
}

// Função principal do jogo de adivinhação
int jogarBatalhaNave() {
    screenClear();
    int coordenadaX, coordenadaY;
    int tentativaX, tentativaY;
    int grade[TAMANHO_GRADE][TAMANHO_GRADE] = {0};
    int tentativas[25][2];
    int numTentativas = 0;
    int acertou = 0;

    srand(time(NULL));
    coordenadaX = rand() % TAMANHO_GRADE;
    coordenadaY = rand() % TAMANHO_GRADE;

    IntroducaoMinijogo1();

    while (numTentativas < MAX_TENTATIVAS) {
        exibirMatriz(grade, tentativas, numTentativas, tentativaX, tentativaY, coordenadaX, coordenadaY, acertou);
        printf("Você tem %d tentativas restantes.\n", MAX_TENTATIVAS - numTentativas);
        printf("Digite as coordenadas (X, Y) para tentar localizar a nave inimiga: ");
        
        if (scanf("%d %d", &tentativaX, &tentativaY) != 2) {
            printf("Coordenadas não estão no formato correto! Tente novamente no formato X Y.\n");
            while (getchar() != '\n');
            continue;
        }

        if (tentativaX < 0 || tentativaX >= TAMANHO_GRADE || tentativaY < 0 || tentativaY >= TAMANHO_GRADE) {
            printf("Coordenadas fora dos limites da grade! Por favor, tente novamente.\n");
            continue;
        }

        if (coordenadaRepetida(tentativas, tentativaX, tentativaY, numTentativas)) {
            printf("Você já tentou essa coordenada antes! Escolha outra.\n");
            continue;
        }

        tentativas[numTentativas][0] = tentativaX;
        tentativas[numTentativas][1] = tentativaY;
        numTentativas++;

        if (tentativaX == coordenadaX && tentativaY == coordenadaY) {
            acertou = 1;
            printf("Parabéns, você localizou a nave inimiga em (%d, %d)!\n", coordenadaX, coordenadaY);
            printf("Você acertou em %d tentativas.\n", numTentativas);
            exibirMatriz(grade, tentativas, numTentativas, tentativaX, tentativaY, coordenadaX, coordenadaY, acertou);
            printf("Parabéns, você conquistou o item 'Laser Ultra Poderoso'!\n");
            break;
        } else {
            Dicas(tentativaX, tentativaY, coordenadaX, coordenadaY);
        }

        if (numTentativas >= MAX_TENTATIVAS) {
            printf("Você esgotou suas tentativas! A nave inimiga estava em (%d, %d).\n", coordenadaX, coordenadaY);
        }
    }
    return acertou;
}
#define LARGURA_TELA 50
#define ALTURA_TELA 20
#define ASTEROIDES_MAX 15
#define TEMPO_LIMITE 30

#define WALL_COLOR "\033[1;35m█\033[0m"
#define ASTEROIDE_COLOR "\033[38;5;214m⬤\033[0m"

struct Nave {
    int x;
    int y;
};

struct Asteroide {
    int x;
    int y;
};

void limparBuffer() {
    while (getchar() != '\n');
}

void desenharTela(struct Nave *nave, struct Asteroide asteroides[], int numAsteroides, int tempoRestante) {
    screenClear();
    screenHideCursor();

    printf("Tempo: %d segundos\n", tempoRestante);

    for (int i = 0; i < LARGURA_TELA; i++) printf(WALL_COLOR);
    printf("\n");

    for (int y = 1; y < ALTURA_TELA - 1; y++) {
        for (int x = 0; x < LARGURA_TELA; x++) {
            if (x == 0 || x == LARGURA_TELA - 1) {
                printf(WALL_COLOR);
            } else if (x == nave->x && y == nave->y) {
                printf("🚀");
                x++;
            } else {
                int asteroidePresente = 0;
                for (int i = 0; i < numAsteroides; i++) {
                    if (asteroides[i].x == x && asteroides[i].y == y) {
                        printf(ASTEROIDE_COLOR);
                        asteroidePresente = 1;
                        break;
                    }
                }
                if (!asteroidePresente) printf(" ");
            }
        }
        printf("\n");
    }

    for (int i = 0; i < LARGURA_TELA; i++) printf(WALL_COLOR);
    printf("\n");

    screenUpdate();
}

void moverNave(struct Nave *nave) {
    if (keyhit()) {
        int tecla = readch();
        if (tecla == 68 && nave->x > 1) {
            nave->x--;
        } else if (tecla == 67 && nave->x < LARGURA_TELA - 3) {
            nave->x++;
        }
    }
}

void atualizarAsteroides(struct Asteroide asteroides[], int *numAsteroides, int *contadorAsteroides) {
    if (*contadorAsteroides % 6 == 0) {
        for (int i = 0; i < *numAsteroides; i++) {
            asteroides[i].y++;
            if (asteroides[i].y >= ALTURA_TELA - 1) {
                for (int j = i; j < *numAsteroides - 1; j++) {
                    asteroides[j] = asteroides[j + 1];
                }
                (*numAsteroides)--;
                i--;
            }
        }
    }

    if (*numAsteroides < ASTEROIDES_MAX && rand() % 100 < 5) {
        asteroides[*numAsteroides].x = rand() % (LARGURA_TELA - 2) + 1;
        asteroides[*numAsteroides].y = 1;
        (*numAsteroides)++;
    }

    (*contadorAsteroides)++;
}

int verificarColisao(struct Nave *nave, struct Asteroide asteroides[], int numAsteroides) {
    for (int i = 0; i < numAsteroides; i++) {
        if (nave->x == asteroides[i].x && nave->y == asteroides[i].y) {
            return 1;
        }
    }
    return 0;
}

int DesviarAsteroides() {
    struct Nave nave = {LARGURA_TELA / 2, ALTURA_TELA - 2};
    struct Asteroide asteroides[ASTEROIDES_MAX];
    int numAsteroides = 0;
    srand(time(NULL));

    keyboardInit();
    screenInit(0);

    printf("Pressione ENTER para começar...\n");
    limparBuffer();
    readch();

    int jogoRodando = 1;
    int tempoRestante = TEMPO_LIMITE;
    time_t inicioTempo = time(NULL);
    int contadorAsteroides = 0;

    while (jogoRodando) {
        int tempoAtual = (int)(time(NULL) - inicioTempo);
        tempoRestante = TEMPO_LIMITE - tempoAtual;

        if (tempoRestante <= 0) {
            screenDestroy();
            keyboardDestroy();
            return 1;
        }

        desenharTela(&nave, asteroides, numAsteroides, tempoRestante);
        atualizarAsteroides(asteroides, &numAsteroides, &contadorAsteroides);
        moverNave(&nave);

        if (verificarColisao(&nave, asteroides, numAsteroides)) {
            screenDestroy();
            keyboardDestroy();
            return 0;
        }

        usleep(50000);
    }


    return 0;
}

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
                printf("%s", PLAYER);  // Desenha o jogador
            } else if (current_map[i][j] == '#') {
                printf("%s", WALL_COLOR);  // Desenha a parede em roxo brilhante
            } else {
                printf("%c", current_map[i][j]);  // Desenha os demais caracteres normalmente
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
            printf("Você escolheu a Porta 1: Júpiter\n");
            sleep(2);  // Delay para visualização da resposta
            current_level = 2;  // Transição para o próximo nível
            x = 25; y = 15;  // Resetando a posição do jogador para a inicial
            display_map(current_level);  // Atualiza o mapa
        }
        // Porta 2 da fase 1
        else if (x == 24 && y == 7) {  // Porta 2, número 2
            printf("Você escolheu a Porta 2: Saturno\n");
            keyboardDestroy();
            int acertou = jogarBatalhaNave();
            keyboardInit();
            if (acertou == 1){
                current_level = 2;
                x = 25; y = 15;
                display_map(current_level);
            }
            else{
                displaySystemError();
            }
        }
        // Porta 3 da fase 1
        else if (x == 41 && y == 7) {  
            printf("Você escolheu a Porta 3: Marte\n");
            keyboardDestroy();
            int acertou = jogarBatalhaNave();
            keyboardInit();
            if (acertou == 1){
                current_level = 2;
                x = 25, y = 15;
                display_map(current_level);
            }
            else{
                displaySystemError();
            }
            
        }
    }
    else if (current_level == 2) {
        // Porta 1 da fase 2
        if (x == 7 && y == 7) {  
            printf("Você escolheu a Porta 1: 82\n");
            sleep(2);  // Delay para visualização da resposta
            current_level = 3;  // Transição para o próximo nível
            x = 25; y = 15;  // Resetando a posição do jogador para a inicial
            display_map(current_level);  // Atualiza o mapa
        }
        // Porta 2 da fase 2
        else if (x == 24 && y == 7) {  
            printf("Você escolheu a Porta 2: 62\n");
            keyboardDestroy();
            int result = DesviarAsteroides();
            keyboardInit();
            if(result == 1){
                current_level = 3;
                x = 25;y = 15;
                display_map(current_level);

            }else{
                displaySystemError();
            }
        }
        // Porta 3 da fase 2
        else if (x == 41 && y == 7) {  
            printf("Você escolheu a Porta 3: 72\n");
            keyboardDestroy();
            int result = DesviarAsteroides();
            keyboardInit();
            if(result == 1){
                current_level = 3;
                x = 25;y = 15;
                display_map(current_level);

            }else{
                displaySystemError();
            }
        }
    }
    else if (current_level == 3) {
        // Porta 1 da fase 3
        if (x == 7 && y == 9) {  // Porta 1, número 1
            printf("Você escolheu a Porta 1 Vostok 1\n");
            displaySystemError();
        }
        // Porta 2 da fase 3
        else if (x == 24 && y == 9) {  // Porta 2, número 2
            printf("Você escolheu a Porta 2: Apolo 11\n");
            sleep(2);
            displayWinMessage();
            exit(0);

        }
        // Porta 3 da fase 3
        else if (x == 41 && y == 9) {  // Porta 3, número 3
            printf("Você escolheu a Porta 3: Soyus\n");
            displaySystemError();
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
    for (int i = 5; i >= 1; i--) {
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
    
   return 0;
}
