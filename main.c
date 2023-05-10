#include <stdio.h>
#include <allegro.h>
#include "Frogger.h"
void initialiation_allegro(){
    allegro_init(); // appel obligatoire (var.globales, recup. infos syst�me ...)
    install_keyboard(); //pour utiliser le clavier
    install_mouse(); //pour utiliser la souris
    //pour choisir la profondeur de couleurs (8,16,24 ou 32 bits)
    set_color_depth(desktop_color_depth()); //ici�: identique � celle du bureau
    //s�lection du mode graphique
    // avec choix d'un driver+mode+r�solution de l'�cran
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,800,600,0,0)!=0)
    {
        // message et sortie de prog. si �chec
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}
BITMAP* buffer;
BITMAP* tete,*queue,*fond;
void snake(){
    buffer=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(buffer);

    // Chargement de l'image
    tete=load_bitmap("tete_s.bmp",NULL);
    if (!tete)  {
        allegro_message("pas pu trouver/charger tete_s.bmp");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    queue=load_bitmap("queue_s.bmp",NULL);
    if (!queue)  {
        allegro_message("pas pu trouver/charger queue_s.bmp");
        allegro_exit(); exit(EXIT_FAILURE);

    }fond=load_bitmap("fond_s.bmp",NULL);
    if (!fond)  {
        allegro_message("pas pu trouver/charger fond_s.bmp");
        allegro_exit(); exit(EXIT_FAILURE);
    }


    blit(fond,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    while (!key[KEY_ESC]){
    }
}
int main() {
    initialiation_allegro();
    //snake();
    frogger();
    return (0);
}END_OF_MAIN();