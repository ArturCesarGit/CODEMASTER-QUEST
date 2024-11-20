#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <time.h>     
#include <string.h>  


#include "screen.h"   
#include "keyboard.h" 
#include "timer.h"    

struct Score {
    char name[50];          
    int pontos;             
    struct Score *next;     
};
void inserirOrdenadoESalvar(const char* arquivo, char* name, int *pontos) {
    struct Score* head = NULL;
    struct Score* atual = NULL;
    struct Score* novoScore = NULL;

    
    FILE* file = fopen(arquivo, "r");
    if (file) {
        char tempName[50];
        int tempPontos;

        
        while (fscanf(file, "%s %d", tempName, &tempPontos) == 2) {
            struct Score* novo = (struct Score*)malloc(sizeof(struct Score));
            strcpy(novo->name, tempName);
            novo->pontos = tempPontos;
            novo->next = NULL;

            if (!head || head->pontos < tempPontos) {
                novo->next = head;
                head = novo;
            } else {
                atual = head;
                while (atual->next && atual->next->pontos >= tempPontos) {
                    atual = atual->next;
                }
                novo->next = atual->next;
                atual->next = novo;
            }
        }
        fclose(file);
    }

    
    novoScore = (struct Score*)malloc(sizeof(struct Score));
    strcpy(novoScore->name, name);
    novoScore->pontos = *pontos;  
    novoScore->next = NULL;

    
    if (!head || head->pontos < *pontos) {
        novoScore->next = head;
        head = novoScore;
    } else {
        atual = head;
        while (atual->next && atual->next->pontos >= *pontos) {
            atual = atual->next;
        }
        novoScore->next = atual->next;
        atual->next = novoScore;
    }

    
    file = fopen(arquivo, "w");
    if (!file) {
        perror("Erro ao abrir o arquivo para escrita");
        return;
    }

    atual = head;
    while (atual) {
        fprintf(file, "%s %d\n", atual->name, atual->pontos);
        struct Score* temp = atual;
        atual = atual->next;
        free(temp); 
    }
    fclose(file);
    printf("Scoreboard atualizado e salvo em '%s'.\n", arquivo);
}

void clearScreen() {
    printf("\033[H\033[J"); 
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
    printf("\033[%d;10H", y_position); 
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
    printf("\033[%d;%dH", y_position, x_position); 
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


void drawRunway() {
    printf("\033[23;0H"); 
    for (int i = 0; i < 80; i++) {
        printf("=");
    }
}

void displayWinMessage(int *pontos, char *name, char arquivo[15]) {
    clearScreen();
    drawStars(); 
    drawPlanets();

    for (int i = 1; i <= 5; i++) {  
        clearScreen();  
        drawStars();    
        drawPlanets(); 
        drawRocketLanding(35, i);  
        drawRunway();  
        sleep(1);       
    }

    clearScreen();
    drawStars();
    drawPlanets();
    drawRocketLanding(35, 5);  
    drawRunway();  
    printf("\n\n");
    printf("\tO SEU FOGUETE TEM RÉ!\n");
    printf("\tPARABÉNS, VOCÊ COMPLETOU SUA MISSÃO E CHEGOU AO PLANETA JAVA!\n");
    sleep(3); 

    printf("\nEncerrando o jogo...\n");
    inserirOrdenadoESalvar(arquivo,name,pontos);
    sleep(1);  
    exit(0);   
}



void displaySystemError(int *pontos, char *name, char arquivo[15]) {
    clearScreen();
    keyboardDestroy(); 

    for (int i = 0; i < 5; i++) {
        clearScreen();
        drawStars(); 
        drawPlanets(); 

        if (i == 0) {
            drawRocket(10);  
            printf("\033[10;10H");
            printf("PANE NO SISTEMA\n");
        }
        
        else if (i == 1) {
            clearScreen();
            drawStars();
            drawPlanets();
            
            
            printf("\033[8;10H");
            printf("       |        \n"); 
            printf("      / \\       \n");
            printf("     /   \\      \n");
            printf("    | O O |     \n");
            printf("    |  O  |     \n");
            printf("    | O O |     \n");
            printf("    |     |     \n");

            
            printf("\033[10;10H");
            printf("   /|-----|\\    \n");
            printf("  / |  X  | \\   \n");  
            printf(" |  |  X  |  |  \n");
            printf(" |  |  X  |  |  \n");
            printf("  \\ |_|//   \n");

           
            printf("\033[14;10H");
            printf("     | X |      \n");
            printf("    /  |  \\     \n");
            printf("   /   |   \\    \n");

            printf("\033[10;10H");
            printf("ERRO! TOPO SEPARADO!\n");

            sleep(1); 
            clearScreen();
        }
        
        else if (i == 2) {
            clearScreen();
            drawStars();
            drawPlanets();
            
            
            printf("\033[8;10H");
            printf("       |        \n");
            printf("      / \\       \n");
            printf("     /   \\      \n");
            printf("    | X X |     \n");  
            printf("    |  X  |     \n");
            printf("    | X X |     \n");

           
            printf("\033[10;10H");
            printf("   /|-----|\\    \n");
            printf("  / |  X  | \\   \n");
            printf(" |  |  X  |  |  \n");
            printf(" |  |  X  |  |  \n");
            printf("  \\ |_|//   \n");

            
            printf("\033[14;10H");
            printf("     | X |      \n");

            printf("\033[10;10H");
            printf("FALHA CRÍTICA! CAUDA PERDIDA!\n");

            sleep(1);
            clearScreen();
        }
        
        else if (i == 3) {
            clearScreen();
            drawStars();
            drawPlanets();
            
            
            printf("\033[8;10H");
            printf("       |        \n");
            printf("      / \\       \n");
            printf("     /   \\      \n");
            printf("    | X X |     \n");
            printf("    |  X  |     \n");
            printf("    | X X |     \n");

            
            printf("\033[10;10H");
            printf("   /|--X--|\\    \n");
            printf("  / |  X  | \\   \n");
            printf(" |  |  X  |  |  \n");
            printf(" |  |  X  |  |  \n");
            printf("  \\ |--X--|//   \n");

            
            printf("\033[14;10H");
            printf("     | X |      \n");

            printf("\033[10;10H");
            printf("DANOS EXTREMOS! NAVE A PONTO DE EXPLOSÃO!\n");

            sleep(1); 
            clearScreen();
        }
        
        else if (i == 4) {
            clearScreen();
            drawStars();
            drawPlanets();
            
            
            printf("\033[8;10H");
            printf("       |        \n");
            printf("      / \\       \n");
            printf("     /   \\      \n");
            printf("    | X X |     \n");
            printf("    |  X  |     \n");
            printf("    | X X |     \n");

            
            printf("\033[10;10H");
            printf("   /|--X--|\\    \n");
            printf("  / |  X  | \\   \n");
            printf(" |  |  X  |  |  \n");
            printf(" |  |  X  |  |  \n");
            printf("  \\ |--X--|//   \n");

           
            printf("\033[14;10H");
            printf("     | X |      \n");

            printf("\033[10;10H");
            printf("NAVE DESTRUÍDA! FIM DE MISSÃO!\n");

            sleep(2);  
        }

        sleep(1); 
    }

    
    printf("\033[13;10H");
    printf("SISTEMA CRÍTICO! REINICIANDO...\n");
    sleep(3);
    printf("\033[?25h");  
    screenClear();  
    inserirOrdenadoESalvar(arquivo,name,pontos);
    exit(0); 
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

    printf("Bem-vindo à missão CODEMASTER-QUEST!\n\n");

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


#define MAP_WIDTH 50
#define MAP_HEIGHT 30
#define EMPTY ' '
#define PLAYER "\033[1;35m\u0D9E\033[0m"  
#define WALL_COLOR "\033[1;35m█\033[0m"

int x = 25, y = 15;  


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
#define MAX_TENTATIVAS 5  


void IntroducaoMinijogo1() {
    printf("\n");
    printf("Resposta errada Agente... \n");
    printf("Não acredito que você não sabe que Jupiter e o maior planeta do sistema solar...\n");
    printf("Agora tente recuperar o foco da missão passando por esse desafio!\n");
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

            (void)grade[i][j]; 
        }
        printf("\n");
    }
    printf("\n");
}

int coordenadaRepetida(int tentativas[][2], int tentativaX, int tentativaY, int numTentativas) {
    for (int i = 0; i < numTentativas; i++) {
        if (tentativas[i][0] == tentativaX && tentativas[i][1] == tentativaY) {
            return 1;
        }
    }
    return 0;
}

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
#define ASTEROIDES_MAX 25
#define TEMPO_LIMITE 30
#define NUM_ASTEROIDES 5
#define META_PONTOS 50
#define TEMPO_MAXIMO 60000 


#define WALL_COLOR "\033[1;35m█\033[0m"
#define ASTEROIDE_COLOR "\033[38;5;214m⬤\033[0m"

struct Nave {
    int x;
    int y;
    int colisao;  
};

struct Asteroide {
    int x;
    int y;
    int ativo;  
};

struct Tiro {
    int x;
    int y;
    int ativo; 
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
    struct Nave nave = {LARGURA_TELA / 2, ALTURA_TELA - 2, 0};
    struct Asteroide asteroides[ASTEROIDES_MAX];
    int numAsteroides = 0;
    srand(time(NULL));

    keyboardInit();
    screenInit(0);

    printf("Olhe para frente… O que é isso?\n");
    printf("Uma nuvem de meteoros gigantescos! Eles estão se aproximando rapidamente, com uma velocidade assustadora. ");
    printf("O espaço ao seu redor começa a se iluminar com explosões. Não há mais tempo!\n");
    printf("Se você não se mover agora, não haverá mais nada que você possa fazer para evitar a destruição.\n");
    printf("O caminho à frente está sendo engolido pelos destroços espaciais, e o caos está apenas começando.\n");
    printf("Cada segundo que passa é uma luta pela sobrevivência. Cada movimento pode ser o último… Se você errar, será o fim.\n");
    printf("Mas… o que fazer agora? A resposta está nas suas mãos.\n");
    printf("O destino está por um fio, e você é a última linha de defesa. Não olhe para trás, a frente é a única direção que importa agora.\n");
    printf("Eles estão vindo…\n\n");
    printf("Instruções de controle:\n");
    printf(" - Use as teclas:\n");
    printf("   '↑' para mover para cima\n");
    printf("   '←' para mover para a esquerda\n");
    printf("   '↓' para mover para baixo\n");
    printf("   '→' para mover para a direita\n\n");
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

void desenharTela2(struct Nave *nave, struct Asteroide asteroides[], struct Tiro tiros[], int numTiros, int pontos, int tempoRestante) {
    char mapa[ALTURA_TELA + 2][LARGURA_TELA + 2];

    for (int i = 0; i < ALTURA_TELA + 2; i++) {
        for (int j = 0; j < LARGURA_TELA + 2; j++) {
            mapa[i][j] = ' ';
        }
    }

    
    for (int i = 0; i < ALTURA_TELA + 2; i++) {
        for (int j = 0; j < LARGURA_TELA + 2; j++) {
            if (i == 0 || i == ALTURA_TELA + 1 || j == 0 || j == LARGURA_TELA + 1) {
                mapa[i][j] = '#';
            }
        }
    }

    mapa[nave->y + 1][nave->x + 1] = '^';

    for (int i = 0; i < NUM_ASTEROIDES; i++) {
        if (asteroides[i].ativo) {
            mapa[asteroides[i].y + 1][asteroides[i].x + 1] = 'O';
        }
    }

    for (int i = 0; i < numTiros; i++) {
        if (tiros[i].ativo) {
            mapa[tiros[i].y + 1][tiros[i].x + 1] = '|';
        }
    }

    screenClear();
    printf("Pontos: %d | Tempo Restante: %d segundos | Colisões Restantes: %d\n", pontos, tempoRestante / 1000, 2 - nave->colisao);

    for (int i = 0; i < ALTURA_TELA + 2; i++) {
        for (int j = 0; j < LARGURA_TELA + 2; j++) {
            if (mapa[i][j] == '#') {
                printf(WALL_COLOR); 
            } else {
                printf("%c", mapa[i][j]);
            }
        }
        printf("\n");
    }
}

void moverAsteroides(struct Asteroide asteroides[], int numAsteroides) {
    static int contadorMovimento = 0;
    contadorMovimento++;

    int frequenciaMovimento = 5; 

    if (contadorMovimento >= frequenciaMovimento) {
        for (int i = 0; i < numAsteroides; i++) {
            if (asteroides[i].ativo) {
                asteroides[i].y++;
                if (asteroides[i].y >= ALTURA_TELA) {
                    asteroides[i].y = 0;
                    asteroides[i].x = rand() % LARGURA_TELA;
                }
            } else {
                asteroides[i].x = rand() % LARGURA_TELA;
                asteroides[i].y = rand() % (ALTURA_TELA / 2);
                asteroides[i].ativo = 1;
            }
        }
        contadorMovimento = 0;
    }
}

void inicializarAsteroides(struct Asteroide asteroides[], int *numAsteroides) {
    for (int i = 0; i < NUM_ASTEROIDES; i++) {
        asteroides[i].x = rand() % LARGURA_TELA;
        asteroides[i].y = rand() % (ALTURA_TELA / 2); 
        asteroides[i].ativo = 1;
    }
    *numAsteroides = NUM_ASTEROIDES;
}

void dispararTiro(struct Nave *nave, struct Tiro tiros[], int *numTiros) {
    if (*numTiros < LARGURA_TELA * ALTURA_TELA) {
        tiros[*numTiros].x = nave->x;
        tiros[*numTiros].y = nave->y - 1;
        tiros[*numTiros].ativo = 1;
        (*numTiros)++;
    }
}

void moverTiros(struct Tiro tiros[], int *numTiros) {
    for (int i = 0; i < *numTiros; i++) {
        if (tiros[i].ativo) {
            tiros[i].y--;
            if (tiros[i].y < 0) {
                tiros[i].ativo = 0;
            }
        }
    }
}

int verificarColisoes2(struct Asteroide asteroides[], struct Tiro tiros[], int numAsteroides, int *numTiros, struct Nave *nave) {
    int pontos = 0;

    for (int i = 0; i < *numTiros; i++) {
        if (tiros[i].ativo) {
            for (int j = 0; j < numAsteroides; j++) {
                if (asteroides[j].ativo && tiros[i].x == asteroides[j].x && tiros[i].y == asteroides[j].y) {
                    asteroides[j].ativo = 0; 
                    tiros[i].ativo = 0;     
                    pontos += 10;           
                }
            }
        }
    }

    for (int i = 0; i < numAsteroides; i++) {
        if (asteroides[i].ativo && nave->x == asteroides[i].x && nave->y == asteroides[i].y) {
            nave->colisao++;               
            asteroides[i].ativo = 0;       
            if (nave->colisao >= 2) {     
                return -1;
            }
        }
    }

    return pontos;
}


int AtirarAsteroides() {
    struct Nave nave = {LARGURA_TELA / 2, ALTURA_TELA - 1, 0};
    struct Asteroide asteroides[NUM_ASTEROIDES];
    struct Tiro tiros[LARGURA_TELA * ALTURA_TELA];
    int numTiros = 0, pontos = 0, tempoRestante = TEMPO_MAXIMO;
    int numAsteroides = 0;

    srand(time(NULL));
    inicializarAsteroides(asteroides, &numAsteroides);

    screenClear();
    keyboardInit();
    timerInit(50);

    
    printf("Atenção, Agente!\n\n");
    printf("Essa é sua última chance de concluir a missao...\n");
    printf("Esperavamos que você não precisasse passar por isso, mas temos a certeza que convocamos o agente certo para essa missão!\n");
    printf("Você está no comando da nave espacial com uma arma super poderosa, e a sua missão não poderia ser mais crítica.\n");
    printf("Uma tempestade de asteroides circulares se aproxima da sua rota e é sua responsabilidade sobreviver ao caos e destruir\n");
    printf("o maior número possível de rochas espaciais antes que sua nave seja destruída. O espaço está cheio de perigos\n");
    printf("e você deve estar rápido e preciso.\n\n");
    
    printf("Instruções de controle:\n");
    printf(" - Use as teclas '←' e '→' para mover sua nave para a esquerda e para a direita.\n");
    printf(" - Pressione 'Espaço' para disparar tiros contra os asteroides.\n");
    printf(" - Evite os asteroides a todo custo, pois qualquer colisão pode ser fatal.\n");
    printf(" - Alem de desviar, Você PRECISA destruir os ateroides para finalizar a sua missão\n\n");

    printf("Você tem um tempo limitado para completar sua tarefa, então seja ágil. Lembre-se, CADA SEGUNDO CONTA ");
    printf("e a sobrevivência do universo depende de você!\n\n");

    printf("Pressione ENTER para começar sua missão.\n");
    limparBuffer(); 
    readch(); 

    
    while (tempoRestante > 0) {
        tempoRestante -= 50;

        desenharTela2(&nave, asteroides, tiros, numTiros, pontos, tempoRestante);

        if (keyhit()) {
            char comando = readch();
            if (comando == 27) {
                comando = readch();
                if (comando == 91) {
                    comando = readch();
                    if (comando == 68 && nave.x > 0) {
                        nave.x--;
                    } else if (comando == 67 && nave.x < LARGURA_TELA - 1) {
                        nave.x++;
                    }
                }
            } else if (comando == ' ') {
                dispararTiro(&nave, tiros, &numTiros);
            }
        }

        moverAsteroides(asteroides, numAsteroides);
        moverTiros(tiros, &numTiros);

        int resultado = verificarColisoes2(asteroides, tiros, NUM_ASTEROIDES, &numTiros, &nave);
        if (resultado == -1) {
            printf("Você perdeu após 2 colisões! Game Over!\n");
            break;
        }
        pontos += resultado;

        if (pontos >= META_PONTOS) {
            printf("Parabéns! Você atingiu a meta de %d pontos! Você venceu!\n", META_PONTOS);
            break;
        }

        usleep(50000); 
    }

    timerDestroy();

    return pontos >= META_PONTOS ? 1 : 0;
}

void display_map(int level) {
    screenClear();
    char (*current_map)[MAP_WIDTH];

    if (level == 1) {
        current_map = map;
    } else if (level == 2) {
        current_map = map_2;
    } else if (level == 3) {
        current_map = map_3;
    }

    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (i == y && j == x) {
                printf("%s", PLAYER);  
            } else if (current_map[i][j] == '#') {
                printf("%s", WALL_COLOR); 
            } else {
                printf("%c", current_map[i][j]); 
            }
        }
        printf("\n");
    }
    screenUpdate();
}

int current_level = 1;

int isValidMove(int new_x, int new_y) {
    char (*current_map)[MAP_WIDTH] = (current_level == 1) ? map : map_2;
    return current_map[new_y][new_x] != '#'; 
}

void checkDoor(int *pontos, char *name, char arquivo[15]) {
    if (current_level == 1) {
        if (x == 7 && y == 7) {  
            printf("Você escolheu a Porta 1: Júpiter\n");
            *pontos += 60; 
            sleep(2);  
            current_level = 2;  
            x = 25; y = 15;  
            display_map(current_level);  
        }
        else if (x == 24 && y == 7) {  
            printf("Você escolheu a Porta 2: Saturno\n");
            keyboardDestroy();
            int acertou = jogarBatalhaNave();
            keyboardInit();
            if (acertou == 1) {
                *pontos += 50;  
                current_level = 2;
                x = 25; y = 15;
                display_map(current_level);
            } else {
                displaySystemError(pontos, name, arquivo);  
            }
        }
        else if (x == 41 && y == 7) {  
            printf("Você escolheu a Porta 3: Marte\n");
            keyboardDestroy();
            int acertou = jogarBatalhaNave();
            keyboardInit();
            if (acertou == 1) {
                *pontos += 50;  
                current_level = 2;
                x = 25, y = 15;
                display_map(current_level);
            } else {
                displaySystemError(pontos, name, arquivo);
            }
        }
    }
    else if (current_level == 2) {
        if (x == 7 && y == 7) {  
            printf("Você escolheu a Porta 1: 82\n");
            *pontos += 60;  
            sleep(2);  
            current_level = 3;  
            x = 25; y = 15;  
            display_map(current_level);  
        }
        else if (x == 24 && y == 7) {  
            printf("Você escolheu a Porta 2: 62\n");
            keyboardDestroy();
            int result = DesviarAsteroides();
            keyboardInit();
            if (result == 1) {
                *pontos += 50; 
                current_level = 3;
                x = 25; y = 15;
                display_map(current_level);
            } else {
                displaySystemError(pontos, name, arquivo);
            }
        }
        else if (x == 41 && y == 7) {  
            printf("Você escolheu a Porta 3: 72\n");
            keyboardDestroy();
            int result = DesviarAsteroides();
            keyboardInit();
            if (result == 1) {
                *pontos += 50; 
                current_level = 3;
                x = 25; y = 15;
                display_map(current_level);
            } else {
                displaySystemError(pontos, name, arquivo);
            }
        }
    }
    else if (current_level == 3) {
        if (x == 7 && y == 9) {  
            printf("Você escolheu a Porta 1: Vostok 1\n");
            keyboardDestroy();
            int result = AtirarAsteroides();
            keyboardInit();
            if (result == 1) {
                *pontos += 50; 
                displayWinMessage(pontos, name, arquivo);
                exit(0);
            } else {
                displaySystemError(pontos, name, arquivo);
            }
        }
        else if (x == 24 && y == 9) {  
            printf("Você escolheu a Porta 2: Apolo 11\n");
            *pontos += 60; 
            sleep(2);
            displayWinMessage(pontos, name, arquivo);
            exit(0);
        }
        else if (x == 41 && y == 9) {  
            printf("Você escolheu a Porta 3: Soyuz\n");
            keyboardDestroy();
            int result = AtirarAsteroides();
            keyboardInit();
            if (result == 1) {
                *pontos += 50;  
                displayWinMessage(pontos, name, arquivo);
                exit(0);
            } else {
                displaySystemError(pontos, name, arquivo);
            }
        }
    }
}

void move_player(int direction) {
    int new_x = x, new_y = y;

    if (direction == 65 && y > 1) {          
        new_y = y - 1;
    } else if (direction == 66 && y < MAP_HEIGHT - 3) { 
        new_y = y + 1;
    } else if (direction == 67 && x < MAP_WIDTH - 2) {  
        new_x = x + 1;
    } else if (direction == 68 && x > 1) {  
        new_x = x - 1;
    }

    if (isValidMove(new_x, new_y)) {
        x = new_x;
        y = new_y;
    }
}

int main() {
    char arquivo[] = "top_scores.txt";
    char name[20];
    printf("\n\nBem-vindo, Agente.\n\n");
    printf("Você foi selecionado pela Organização 'C' para uma missão ultrassecreta de extrema importância.\n");
    printf("A operação que você está prestes a iniciar está além de qualquer coisa que você possa imaginar.\n");
    printf("O destino da humanidade depende de seu sucesso. No entanto, antes de começar, precisamos saber quem você é.\n");
    printf("digite seu nome ou o seu vulgo para sua jornada iniciar: ");
    scanf("%s", name);
    int pontos = 0;
    displayStartScreen();
    getchar(); 

    for (int i = 5; i >= 1; i--) {
        clearScreen();
        drawStars();
        drawPlanets();
        drawRocket(i);
        sleep(1); 
    }

    displayFinalMessage();
    sleep(2); 
    screenInit(1);
    keyboardInit();
    timerInit(30000);
    display_map(current_level);

    int ch = 0;
    while (1) {
        if (keyhit()) {
            ch = readch();
            move_player(ch);
            display_map(current_level);
            checkDoor(&pontos, name, arquivo);
        } else {
            sleep(0.1);
        }
  }

return 0;
}
