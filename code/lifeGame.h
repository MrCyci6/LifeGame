#ifndef LIFEGAME_H
#define LIFEGAME_H

#define LENGTH 1000
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int game();
void start(short tab[LENGTH][LENGTH], int size, int type);
int isAlive(const int x, const int y, const short tab[LENGTH][LENGTH], int size);
void generation(const short tab[LENGTH][LENGTH], short newTab[LENGTH][LENGTH], int size);
void printGame(const short tab[LENGTH][LENGTH], int size);
void generateImage(int gen, short tab[LENGTH][LENGTH], int size);
void writeName(int size, int gen, int type);

/*
 *
 * Oral: Doc et Power Point si possible avec schéma
 *
 * Consignes:
 *
 * Situations:
 *  Quels ont été les problèmes
 *  Les solutions possibles
 *  Solution retenue, pourquoi
 *
 *  Fonctionnalité en plus (Tableau dynamique)
 *
 *  départ
 *  Démarche
 *  Arrivé
 *
*/

#endif