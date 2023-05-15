#include <stdio.h>
#include <allegro.h>
#include "Frogger.h"
#include "guitar_hero.h"

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

int menu(BITMAP *buffer){
    int choix = 0;
    while(choix !=1) {
        //clear_to_color(screen,makecol(255, 0, 255));
        clear_to_color(buffer,makecol(0, 0, 0));
        textprintf_centre_ex(buffer, font, 400, 100, makecol(255, 255, 255), -1, "MENU");
        textprintf_centre_ex(buffer, font, 400, 200, makecol(255, 255, 255), -1, "A- SNAKE");
        textprintf_centre_ex(buffer, font, 400, 300, makecol(255, 255, 255), -1, "B - FROGGER");
        textprintf_centre_ex(buffer, font, 400, 400, makecol(255, 255, 255), -1, "C - GUITAR HERO");
        blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        if(key[KEY_A]){
            return 1;
        } else if(key[KEY_B]){
            return 2;
        } else if(key[KEY_C]){
            return 3;
        }
    }
}
int main() {
    initialiation_allegro();
    BITMAP *buffer = create_bitmap(800,600);
    int choix = menu(buffer);
    switch (choix) {
        case 1:
            break;
        case 2:
            frogger();
            break;
        case 3:
            guitar_hero();
            break;
    }
    allegro_exit();
    exit(EXIT_SUCCESS);
    return (0);
}END_OF_MAIN();