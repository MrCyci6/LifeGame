#include "lifeGame.h"

/*
 * @brief: Main function of Life game
 * @params: none
 * @utility: Start game and user interface
 * @return: exit code (int)
*/
int game() {
    // Create boards
    short tab1[LENGTH][LENGTH] = {0};
    short tab2[LENGTH][LENGTH] = {0};
    int generations = 0, size = 50, startType = 0; // Init params

    // UI
    printf("\x1b[2J"); // clear
    printf("\x1b[%d;%dH", 0, 0); // pos at top
    printf("\x1b[%dm", 33); // yellow
    printf(".____    ._________________________   ________    _____      _____  ___________\n" // title
           "|    |   |   \\_   _____/\\_   _____/  /  _____/   /  _  \\    /     \\ \\_   _____/\n"
           "|    |   |   ||    __)   |    __)_  /   \\  ___  /  /_\\  \\  /  \\ /  \\ |    __)_ \n"
           "|    |___|   ||     \\    |        \\ \\    \\_\\  \\/    |    \\/    Y    \\|        \\\n"
           "|_______ \\___|\\___  /   /_______  /  \\______  /\\____|__  /\\____|__  /_______  /\n"
           "        \\/        \\/            \\/          \\/         \\/         \\/        \\/ \n\n");
    printf("\x1b[%dm", 37); // white

    do {
        printf("\x1b[%dmQuel taille doit avoir la grille : \x1b[%dm", 32, 35);
        scanf("%d", &size);
    } while(size < 1 || size > LENGTH); // Get board size

    printf("\x1b[%dmCombien de génération voulez-vous générer : \x1b[%dm", 32, 35);
    scanf("%d", &generations); // Get number of generation

    do {
        printf("\x1b[%dmType de départ:\n\x1b[%dm 1 - Aléatoire\n 2 - Glider\n 3 - Canon à glider\n 4 - Code personnalisé\n\x1b[%dmQuel type de départ voulez-vous utiliser : \x1b[%dm",
               32, 34, 32, 35);
        scanf("%d", &startType);
    } while(startType > 4 || startType < 1); // Get start board type

    printf("\x1b[%dm", 37); // white

    start(tab1, size, startType);

    printf("\n\x1b[%dmGenerating Images.ppm...\n", 33);
    for(int i = 0; i < generations; i++) {
        //usleep(300000);
        // Check if the generation is even, then switch between 2 boards for save change
        if(i%2 == 0) {
            generation(tab1, tab2, size);
            generateImage(i, tab2, size);
            //printGame(tab2, size);
        } else {
            generation(tab2, tab1, size);
            generateImage(i, tab1, size);
            //printGame(tab1, size);
        }
    }

    printf("Generating GIF suffix...\n");
    writeName(size, generations, startType);
    printf("Generating GIF...\n\x1b[%dm", 37);

    return 1;
}

/*
 * @brief: Initialize game board
 * @params: tab (game board), size (LENGTHxWIDTH of board), type (type of start)
 * @utility: Select start determinate by user
 * @return: none
*/
void start(short tab[LENGTH][LENGTH], int size, int type) {

    if(type == 1) {
        // RANDOM
        srand(time(NULL));
        for(int x = 0; x < size; x++) {
            for(int y = 0; y < size; y++) {
                tab[x][y] = rand() % 2; // Randomly determine whether the cell is alive or not
            }
        }
    } else if(type == 2) {
        // GLIDER
        tab[5][5] = 1;
        tab[6][6] = 1;
        tab[7][4] = 1;
        tab[7][5] = 1;
        tab[7][6] = 1;

    } else if(type == 3) {
        // GLIDER LAUNCHER
        tab[5][1] = 1;
        tab[5][2] = 1;
        tab[6][1] = 1;
        tab[6][2] = 1;
        tab[5][11] = 1;
        tab[6][11] = 1;
        tab[7][11] = 1;
        tab[4][12] = 1;
        tab[8][12] = 1;
        tab[3][13] = 1;
        tab[9][13] = 1;
        tab[3][14] = 1;
        tab[9][14] = 1;
        tab[6][15] = 1;
        tab[4][16] = 1;
        tab[8][16] = 1;
        tab[5][17] = 1;
        tab[6][17] = 1;
        tab[7][17] = 1;
        tab[6][18] = 1;
        tab[3][21] = 1;
        tab[4][21] = 1;
        tab[5][21] = 1;
        tab[3][22] = 1;
        tab[4][22] = 1;
        tab[5][22] = 1;
        tab[2][23] = 1;
        tab[6][23] = 1;
        tab[1][25] = 1;
        tab[2][25] = 1;
        tab[6][25] = 1;
        tab[7][25] = 1;
        tab[3][35] = 1;
        tab[4][35] = 1;
        tab[3][36] = 1;
        tab[4][36] = 1;
    } else {
        int x = 0, y = 0;
        printf("Veuillez renseigner vos coordonnées sous la forme x y (-1 -1 pour arreter) : \n");
        // Get and set new coords determinate by user, only if it in board's width, length
        do {
            scanf("%d %d", &x, &y);
            if(x > size || y > size) { // check if coords is higher than board size
                printf("\x1b[%dmVous devez renseigner des coordonnées comprise dans la grille ! %dx%d\n\x1b[%dm", 31, size, size, 37);
            } else {
                tab[x][y] = 1;
            }
        } while((x > 0 || y > 0)); // stop if coords equals -1 or less
    }
}

/*
 * @brief: Change game board
 * @params: tab (init game board), newTab (game board that has been modified), size (LENGTHxWIDTH of board)
 * @utility: Create a generation cycle for game advancement
 * @return: none
*/
void generation(const short tab[LENGTH][LENGTH], short newTab[LENGTH][LENGTH], int size) {
    for(int x = 0; x < size; x++) {
        for(int y = 0; y < size; y++) {
            newTab[x][y] = isAlive(x, y, tab, size); // set cell alive or not with rules function
        }
    }
}

/*
 * @brief: Rules function
 * @params: tab (game board), size (LENGTHxWIDTH of board), type (type of start)
 * @utility: Master function of game, determinate rules. determinate if cell are still alive or not
 * @return: 1 for alive or 0 for dead (int)
*/
int isAlive(const int x, const int y, const short tab[LENGTH][LENGTH], int size) {
    int neighbour = 0; // init neighbour number at 0

    for(int i = x-1; i <= x+1; i++) {
        for(int j = y-1; j <= y+1; j++) {
            if(i >= 0 && j >= 0 && i < size && j < size) {
                if(tab[i][j] == 1) neighbour++; // increment number size if neighbour is alive
            }
        }
    }

    if(tab[x][y] == 0) {
        return neighbour == 3; // if the cell is dead and has 3 neighbours, it is born
    } else if(tab[x][y] == 1) {
        neighbour--; // remove self cell
        return neighbour == 2 || neighbour == 3; //if the cell is already alive and it has 2 or 3 neighbours it remains alive
    } else {
        return 0; // otherwise it's dead
    }
}

/*
 * @brief: Debug print function
 * @params: tab (game board), size (LENGTHxWIDTH of board)
 * @utility: debug specific generation of game by printing it on console
 * @return: none
*/
void printGame(const short tab[LENGTH][LENGTH], int size) {
    printf(" ");
    for(int x = 0; x < size; x++) {
        printf("---");
    }
    printf("\n");

    for(int x = 0; x < size; x++) {
        printf("|");
        for(int y = 0; y < size; y++) {
            printf(" %c ", tab[x][y] ? '+' : ' '); // print + if cell is alive
        }
        printf("|\n");
    }

    printf(" ");
    for(int x = 0; x < size; x++) {
        printf("---");
    }
    printf("\n");
}

/*
 * @brief: Generating pbm files
 * @params: gen (number of the generation), tab (game board), size (LENGTHxWIDTH of board)
 * @utility: Create ImageX.pbm file attach to specific generation
 * @return: none
*/
void generateImage(int gen, short tab[LENGTH][LENGTH], int size) {
    FILE* monFichier;
    char name[30];

    sprintf(name, "./images/Image%d.pbm", gen+1000); // Set image name from generation number
                                                                  // +1000 due to ImageMagick bug on conversion

    monFichier = fopen(name, "w"); // open pbm file
    if ( monFichier != NULL ) {

        fprintf( monFichier, "P1\n");
        fprintf( monFichier, "%d %d\n", size, size);

        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++) {
                fprintf(monFichier, "%d ", tab[i][j]); // set 0 for dead cells and 1 for alive cells
            }
            fprintf(monFichier, "\n");
        }
    }
}

/*
 * @brief: Generate gif suffix
 * @params: size (LENGTHxWIDTH of board), gen (number of generation), type (type of start)
 * @utility: Determinate suffix of final gif and write it on suffix.txt
 * @return: none
*/
void writeName(int size, int gen, int type) {
    char name[750];
    sprintf(name, "%dx%d_%d_%s", size, size, gen, type == 1 ? "random" : (type == 2 ? "glider" : (type == 3 ? "glider_launcher" : (type == 4 ? "custom" : "none"))));

    FILE* monFichier;
    monFichier = fopen("suffix.txt", "w");
    if ( monFichier != NULL ) {
        fprintf(monFichier,"%s", name); // write in suffix.txt suffix of final gif: LENGTHxWIDTH_GENERATIONS_START
    }

    // supposed to launch the GIF conversion script, but it bug
    /*char cmd[750];
    sprintf(cmd, "./makeGif.sh %dx%d_%d_%s", size, size, gen, type == 1 ? "random" : (type == 2 ? "glider" : (type == 3 ? "glider_launcher" : (type == 4 ? "custom" : "none"))));
    int result = system(cmd);
    if(result == 0) {
        printf("\x1b[%dmGIF generated successfully : results/LifeGame_Result_%dx%d_%d_%s.gif\n", 32, size, size, gen, type == 1 ? "random" : (type == 2 ? "glider" : (type == 3 ? "glider_launcher" : (type == 4 ? "custom" : "none"))));
    } else {
        printf("\x1b[%dmError while generate gif\n", 31);
    }*/
}