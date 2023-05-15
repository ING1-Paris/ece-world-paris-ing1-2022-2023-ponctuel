//
// Created by Hugo on 10/05/2023.
//
#include "Frogger.h"
BITMAP *buffer, *buffer2, *background, *dirt, *frog, *darkOak, *strippedSpruceLogTop, *grass, *water;
PALETTE palette;
SAMPLE *music;

void bitmapLoader(){
    buffer = create_bitmap(SCREEN_W,SCREEN_H*2);
    buffer2 = create_bitmap(SCREEN_W,SCREEN_H*2);
    clear_bitmap(buffer);
    // Chargement de l'image
    dirt=load_bitmap("../assets/frogger/coarse_dirt.bmp", NULL);
    if (!dirt)  {
        allegro_message("pas pu trouver/charger la dirt");
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

void frogger(){
    bitmapLoader();
    play_sample(music, 255, 128, 1000, 0);
    /*for (int i = 0; i < SCREEN_W / 32 + 1; ++i) {
        blit(dirt,screen,i*32,0,(i+1)*32,32,32,32);
    }*/
    while (!key[KEY_ESC]){
        stretch_blit(dirt,buffer,0,0,512,512,0,0,SCREEN_W,SCREEN_H);
        for (int i = 0; i < SCREEN_H/(SCREEN_W/5*2); ++i) {
            if(i%2==0){
                //blit(darkOak,buffer,0,0,SCREEN_W/5,i*(SCREEN_W/5),SCREEN_W/5,SCREEN_W/5);
                stretch_blit(darkOak,buffer,0,0,512,512,SCREEN_W/5,i*(SCREEN_W/5*2),SCREEN_W/5,SCREEN_W/5);
            }
            else{
                //blit(strippedSpruceLogTop,buffer,0,0,SCREEN_W/5,i*(SCREEN_W/5),SCREEN_W/5,SCREEN_W/5);
                stretch_blit(darkOak,buffer,0,0,512,512,SCREEN_W/5,(i+1)*(SCREEN_W/5*2),SCREEN_W/5,SCREEN_W/5);
            }
        }
        blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        clear_bitmap(buffer);
    }
}