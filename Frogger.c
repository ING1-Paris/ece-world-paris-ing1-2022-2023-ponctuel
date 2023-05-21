//
// Created by Hugo on 10/05/2023.
//
#include "Frogger.h"
BITMAP *buffer, *bufferCollisions, *map, *mapCollisions, *longDarkOak, *darkOak, *smallDarkOak, *longOak, *oak, *smallOak, *longLogCollisions, *logCollisions, *smallLogCollisions, *blue_house, *orange_house, *green_house, *green_frog, *red_frog;
SAMPLE *music;

void delay(int milli_seconds)
{
// Storing start time
clock_t start_time = clock();

// looping till required time is not achieved
while (clock() < start_time + milli_seconds)
;
}

void bitmapLoader(){
    buffer = create_bitmap(640,480);
    if (!buffer)  {
        allegro_message("pas pu creer le buffer");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    clear_bitmap(buffer);


    bufferCollisions = create_bitmap(640,480);
    if (!bufferCollisions)  {
        allegro_message("pas pu creer le bufferCollisions");
        allegro_exit(); exit(EXIT_FAILURE);
    }


    // Chargement de l'image
    map=load_bitmap("../assets/frogger/map.bmp", NULL);
    if (!map)  {
        allegro_message("pas pu trouver/charger la map");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    mapCollisions=load_bitmap("../assets/frogger/collision.bmp", NULL);
    if (!mapCollisions)  {
        allegro_message("pas pu trouver/charger la collision");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    longDarkOak=load_bitmap("../assets/frogger/long_dark_oak_log.bmp",NULL);
    if (!longDarkOak)  {
        allegro_message("pas pu trouver/charger le longDarkOak");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    darkOak=load_bitmap("../assets/frogger/dark_oak_log.bmp",NULL);
    if (!darkOak)  {
        allegro_message("pas pu trouver/charger le darkOak");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    smallDarkOak=load_bitmap("../assets/frogger/small_dark_oak_log.bmp",NULL);
    if (!smallDarkOak)  {
        allegro_message("pas pu trouver/charger le smallDarkOak");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    longOak=load_bitmap("../assets/frogger/long_oak_log.bmp",NULL);
    if (!longOak)  {
        allegro_message("pas pu trouver/charger le longOak");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    oak=load_bitmap("../assets/frogger/oak_log.bmp",NULL);
    if (!oak)  {
        allegro_message("pas pu trouver/charger le oak");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    smallOak=load_bitmap("../assets/frogger/small_oak_log.bmp",NULL);
    if (!smallOak)  {
        allegro_message("pas pu trouver/charger le smallOak");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    longLogCollisions=load_bitmap("../assets/frogger/long_log_collisions.bmp",NULL);
    if (!longLogCollisions)  {
        allegro_message("pas pu trouver/charger le longLogCollisions");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    logCollisions=load_bitmap("../assets/frogger/log_collisions.bmp",NULL);
    if (!logCollisions)  {
        allegro_message("pas pu trouver/charger le logCollisions");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    smallLogCollisions=load_bitmap("../assets/frogger/small_log_collisions.bmp",NULL);
    if (!smallLogCollisions)  {
        allegro_message("pas pu trouver/charger le smallLogCollisions");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    blue_house=load_bitmap("../assets/frogger/blue_house.bmp",NULL);
    if (!blue_house)  {
        allegro_message("pas pu trouver/charger blue_house.bmp");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    orange_house=load_bitmap("../assets/frogger/orange_house.bmp",NULL);
    if (!orange_house)  {
        allegro_message("pas pu trouver/charger orange_house.bmp");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    green_house=load_bitmap("../assets/frogger/green_house.bmp",NULL);
    if (!green_house)  {
        allegro_message("pas pu trouver/charger green_house.bmp");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    green_frog=load_bitmap("../assets/frogger/green_frog.bmp",NULL);
    if (!green_frog)  {
        allegro_message("pas pu trouver/charger green_frog.bmp");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    red_frog=load_bitmap("../assets/frogger/red_frog.bmp",NULL);
    if (!red_frog)  {
        allegro_message("pas pu trouver/charger red_frog.bmp");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    music = load_sample("../assets/frogger/Gerudo-Town.wav");
    if (!music) {
        allegro_message("Impossible de charger le fichier audio\n");
    }
}

void freeBitmap(){
    destroy_bitmap(buffer);
    destroy_bitmap(bufferCollisions);
    destroy_bitmap(map);
    destroy_bitmap(mapCollisions);
    destroy_bitmap(longDarkOak);
    destroy_bitmap(darkOak);
    destroy_bitmap(smallDarkOak);
    destroy_bitmap(longOak);
    destroy_bitmap(oak);
    destroy_bitmap(smallOak);
    destroy_bitmap(longLogCollisions);
    destroy_bitmap(logCollisions);
    destroy_bitmap(smallLogCollisions);
    destroy_bitmap(blue_house);
    destroy_bitmap(orange_house);
    destroy_bitmap(green_house);
    destroy_bitmap(green_frog);
    destroy_bitmap(red_frog);
    destroy_sample(music);
}

Log* createLog(int x, int y, int speed, BITMAP *sprite, BITMAP *colisions){
    Log* log=malloc(sizeof(Log));
    log->x = x;
    log->y = y;
    log->speed = speed; // 1 = droite, -1 = gauche
    log->sprite = sprite; // sprite de la log
    log->colisions = colisions; // sprite des colisions de la log
    printf("log cree\n");
    return log;
}

void drawLog(Log *log){
    stretch_blit(log->sprite, buffer, 0, 0, log->sprite->w, log->sprite->h, log->x, log->y, log->sprite->w/2, log->sprite->h/2);
    stretch_blit(log->colisions, bufferCollisions, 0, 0, log->sprite->w, log->sprite->h, log->x, log->y, log->sprite->w/2, log->sprite->h/2);
}

void moveLog(Log *log, int speed){
    if(speed != 0){
        if(log->x > SCREEN_W){
            log->x = -80;
        }
        if(log->x < -80){
            log->x = SCREEN_W;
        }
        if (speed > 0){
            speed -= 1;
            log->x += 1;
        } else {
            speed += 1;
            log->x -= 1;
        }
        moveLog(log, speed);
        delay(1);
    }
}

Frog* createFrog(int x, int y, BITMAP *sprite){
    Frog *frog = malloc(sizeof(Frog));
    frog->x = x;
    frog->y = y;
    frog->sprite = sprite;
    printf("frog cree\n");
    return frog;
}

void drawFrog(Frog *frog){
    masked_stretch_blit(frog->sprite, buffer, 0, 0, frog->sprite->w, frog->sprite->h, frog->x, frog->y, 16, 16);
}

void moveFrog1(Frog *frog, int cycleJeu){
    if (cycleJeu%4==0){
        if (key[KEY_C]){
            if (key[KEY_W]){
                if (!calculCollisions(frog->x, frog->y-32, bufferCollisions)){
                    frog->y -= 32;
                }
            }
            if (key[KEY_S]){
                if (!calculCollisions(frog->x, frog->y+32, bufferCollisions)){
                    frog->y += 32;
                }
            }
            if (key[KEY_A]){
                if (!calculCollisions(frog->x-32, frog->y, bufferCollisions)){
                    frog->x -= 32;
                }
            }
            if (key[KEY_D]){
                if (!calculCollisions(frog->x+32, frog->y, bufferCollisions)){
                    frog->x += 32;
                }
            }
        }
        else{
            if (key[KEY_W]){
                if (!calculCollisions(frog->x, frog->y-16, bufferCollisions)){
                    frog->y -= 16;
                }
            }
            if (key[KEY_S]){
                if (!calculCollisions(frog->x, frog->y+16, bufferCollisions)){
                    frog->y += 16;
                }
            }
            if (key[KEY_A]){
                if (!calculCollisions(frog->x-16, frog->y, bufferCollisions)){
                    frog->x -= 16;
                }
            }
            if (key[KEY_D]){
                if (!calculCollisions(frog->x+16, frog->y, bufferCollisions)){
                    frog->x += 16;
                }
            }
        }
    }
}


void moveFrog2(Frog *frog, int cycleJeu){
    if (cycleJeu%4==0){
        if (key[KEY_N]){
            if (key[KEY_I]){
                if (!calculCollisions(frog->x, frog->y-32, bufferCollisions)){
                    frog->y -= 32;
                }
            }
            if (key[KEY_K]){
                if (!calculCollisions(frog->x, frog->y+32, bufferCollisions)){
                    frog->y += 32;
                }
            }
            if (key[KEY_J]){
                if (!calculCollisions(frog->x-32, frog->y, bufferCollisions)){
                    frog->x -= 32;
                }
            }
            if (key[KEY_L]){
                if (!calculCollisions(frog->x+32, frog->y, bufferCollisions)){
                    frog->x += 32;
                }
            }
        }
        else{
            if (key[KEY_I]){
                if (!calculCollisions(frog->x, frog->y-16, bufferCollisions)){
                    frog->y -= 16;
                }
            }
            if (key[KEY_K]){
                if (!calculCollisions(frog->x, frog->y+16, bufferCollisions)){
                    frog->y += 16;
                }
            }
            if (key[KEY_J]){
                if (!calculCollisions(frog->x-16, frog->y, bufferCollisions)){
                    frog->x -= 16;
                }
            }
            if (key[KEY_L]){
                if (!calculCollisions(frog->x+16, frog->y, bufferCollisions)){
                    frog->x += 16;
                }
            }
        }
    }
}


int calculCollisions(int x, int y, BITMAP *colisions){
    int color = getpixel(colisions, x+8, y+8);
    if (color == makecol(255, 0, 0)){
        printf("collision\n");
        return 1;
    }
    return 0;
}


int conditionVictoire(Frog *frog){
    if (frog->y < 16){
        return 1;
    }
    return 0;
}


int checkVictoire(Frog *frog1, Frog *frog2){
    if (conditionVictoire(frog1)){
        printf("Victoire du joueur 1\n");
        return 1;
    } else if (conditionVictoire(frog2)){
        printf("Victoire du joueur 2\n");
        return 2;
    }
    return 0;
}


int frogger(){
    printf("load\n");
    bitmapLoader();
    printf("music\n");
    play_sample(music, 255, 128, 1000, 1); // Joue la musique


    printf("create log\n");
    Log log1, log2, log3, log4, log5, log6, log7;
    log1 = *createLog(300, 368, 2, longOak, longLogCollisions);
    log2 = *createLog(0, 288, 2, oak, logCollisions);
    log3 = *createLog(0, 256, 1, smallOak, smallLogCollisions);
    log4 = *createLog(300, 272, -2, longDarkOak, longLogCollisions);
    log5 = *createLog(0, 384, -2, darkOak, logCollisions);
    log6 = *createLog(0, 240, -1, smallDarkOak, smallLogCollisions);
    log7 = *createLog(300, 0, 1, longOak, longLogCollisions);


    printf("create frog\n");
    Frog frog1, frog2;
    frog1 = *createFrog(304, 464, green_frog);
    frog2 = *createFrog(336, 464, red_frog);


    printf("jeu :\n");
    int cycleJeu = 0;
    while (!key[KEY_ESC]){
        blit(map,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
        blit(mapCollisions,bufferCollisions,0,0,0,0,SCREEN_W,SCREEN_H);


        drawLog(&log1);
        drawLog(&log2);
        drawLog(&log3);
        drawLog(&log4);
        drawLog(&log5);
        drawLog(&log6);
        drawLog(&log7);


        moveLog(&log1, log1.speed);
        moveLog(&log2, log2.speed);
        moveLog(&log3, log3.speed);
        moveLog(&log4, log4.speed);
        moveLog(&log5, log5.speed);
        moveLog(&log6, log6.speed);
        moveLog(&log7, log7.speed);


        drawFrog(&frog1);
        drawFrog(&frog2);


        moveFrog1(&frog1, cycleJeu);
        moveFrog2(&frog2, cycleJeu);


        masked_blit(orange_house,buffer,0,0,80,255,SCREEN_W,SCREEN_H);
        masked_blit(green_house,buffer,0,0,350,255,SCREEN_W,SCREEN_H);


        stretch_blit(buffer,screen,0,0,buffer->w,buffer->h,0,0,SCREEN_W,SCREEN_H);
        clear_bitmap(buffer);
        delay(20);
        cycleJeu++;
        if (checkVictoire(&frog1, &frog2) != 0){
            delay(5000);
            stop_sample(music);
            freeBitmap();
            return checkVictoire(&frog1, &frog2);
        }
    }
    stop_sample(music);
    freeBitmap();
}