//
// Created by Hugo on 10/05/2023.
//
#include "Frogger.h"
BITMAP *buffer, *background, *frog, *trunk, *grass, *water;
PALETTE palette;
void frogger(){
    buffer = create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(buffer);
    // Chargement de l'image
    background=load_bitmap("../assets/frogger/grass_block_top.bmp", NULL);
    if (!background)  {
        allegro_message("pas pu trouver/charger le background");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    frog=load_bitmap("../assets/frogger/frog.bmp",NULL);
    if (!frog)  {
        allegro_message("pas pu trouver/charger la frog");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    trunk=load_bitmap("../assets/frogger/dark_oak_log.bmp",NULL);
    if (!trunk)  {
        allegro_message("pas pu trouver/charger le trunk");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    grass=load_bitmap("../assets/frogger/grass_block_top.bmp",NULL);
    if (!grass)  {
        allegro_message("pas pu trouver/charger grass.bmp");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    water=load_bitmap("../assets/frogger/water.bmp",NULL);
    if (!water)  {
        allegro_message("pas pu trouver/charger water.bmp");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    blit(background,screen,0,0,1920,1200,SCREEN_W,SCREEN_H);
    while (!key[KEY_ESC]){
    }
    allegro_exit();
    exit(EXIT_SUCCESS);
}


