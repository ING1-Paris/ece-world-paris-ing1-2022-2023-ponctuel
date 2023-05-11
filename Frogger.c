//
// Created by Hugo on 10/05/2023.
//
#include "Frogger.h"
BITMAP* buffer, *background, *frog, *trunk, *grass, *water;
PALETTE palette;
void frogger(){
    buffer = create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(buffer);
    char* bg_filename = "grass_block_top.bmp";

    // Chargement de l'image
    background=load_bitmap(bg_filename,palette);
    if (!background)  {
        allegro_message("pas pu trouver/charger %s", bg_filename);
        allegro_exit(); exit(EXIT_FAILURE);
    }
    frog=load_bitmap("src/Frogger/frog.bmp",NULL);
    if (!frog)  {
        allegro_message("pas pu trouver/charger frog.bmp");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    trunk=load_bitmap("src/Frogger/dark_oak_log.bmp",NULL);
    if (!trunk)  {
        allegro_message("pas pu trouver/charger trunk.bmp");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    grass=load_bitmap("src/Frogger/grass_block_top.bmp",NULL);
    if (!grass)  {
        allegro_message("pas pu trouver/charger grass.bmp");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    water=load_bitmap("src/Frogger/water.bmp",NULL);
    if (!water)  {
        allegro_message("pas pu trouver/charger water.bmp");
        allegro_exit(); exit(EXIT_FAILURE);
    }


    blit(background,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    while (!key[KEY_ESC]){
    }
}


