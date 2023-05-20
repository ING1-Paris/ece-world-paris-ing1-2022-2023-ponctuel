//
// Created by Hugo on 10/05/2023.
//

#ifndef PONCTUEL_FROGGER_H
#define PONCTUEL_FROGGER_H
#include <stdio.h>
#include <allegro.h>
#include <time.h>

typedef struct Log{
int x;
int y;
int speed;
BITMAP *sprite;
BITMAP *colisions;
}Log;

typedef struct Frog{
int x;
int y;
BITMAP *sprite;
}Frog;


void bitmapLoader();
void freeBitmap();
Log* createLog(int x, int y, int speed, BITMAP *sprite, BITMAP *colisions);
void drawLog(Log *log);
void moveLog(Log *log, int speed);
Frog* createFrog(int x, int y, BITMAP *sprite);
void drawFrog(Frog *frog);
void moveFrog(Frog *frog);
int frogger();

#endif //PONCTUEL_FROGGER_H
