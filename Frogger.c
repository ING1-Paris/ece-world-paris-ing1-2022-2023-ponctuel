//
// Created by Hugo on 10/05/2023.
//
#include "Frogger.h"
BITMAP *buffer, *map, *collision, *background, *dirt, *frog, *darkOak, *strippedSpruceLogTop, *grass, *water, *blue_house, *orange_house, *green_house;
SAMPLE *music;

void bitmapLoader(){
    buffer = create_bitmap(640,480);
    clear_bitmap(buffer);
    // Chargement de l'image
    dirt=load_bitmap("../assets/frogger/coarse_dirt.bmp", NULL);
    if (!dirt)  {
        allegro_message("pas pu trouver/charger la dirt");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    map=load_bitmap("../assets/frogger/map.bmp", NULL);
    if (!map)  {
        allegro_message("pas pu trouver/charger la map");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    collision=load_bitmap("../assets/frogger/collision.bmp", NULL);
    if (!collision)  {
        allegro_message("pas pu trouver/charger la collision");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    frog=load_bitmap("../assets/frogger/frog.bmp",NULL);
    if (!frog)  {
        allegro_message("pas pu trouver/charger la frog");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    darkOak=load_bitmap("../assets/frogger/dark_oak_log.bmp",NULL);
    if (!darkOak)  {
        allegro_message("pas pu trouver/charger le darkOak");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    strippedSpruceLogTop= load_bitmap("../assets/frogger/stripped_spruce_log_top.bmp", NULL);
    if (!strippedSpruceLogTop)  {
        allegro_message("pas pu trouver/charger le strippedSpruceLogTop");
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
    music = load_sample("../assets/frogger/Gerudo-Town.wav");
    if (!music) {
        allegro_message("Impossible de charger le fichier audio\n");
    }
}

void freeBitmap(){
    destroy_bitmap(buffer);
    destroy_bitmap(background);
    destroy_bitmap(frog);
    destroy_bitmap(darkOak);
    destroy_bitmap(strippedSpruceLogTop);
    destroy_bitmap(grass);
    destroy_sample(music);
}

int frogger(){
    printf("load\n");
    bitmapLoader();
    printf("music\n");
    play_sample(music, 255, 128, 1000, 0);
    printf("jeu\n");
    while (!key[KEY_ESC]){
        blit(map,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
        masked_blit(orange_house,buffer,0,0,80,255,SCREEN_W,SCREEN_H);
        masked_blit(green_house,buffer,0,0,350,255,SCREEN_W,SCREEN_H);
        stretch_blit(buffer,screen,0,0,buffer->w,buffer->h,0,0,SCREEN_W,SCREEN_H);
        clear_bitmap(buffer);
    }
    stop_sample(music);
}