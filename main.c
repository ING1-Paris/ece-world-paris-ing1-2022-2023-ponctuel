#include <stdio.h>
#include <allegro.h>
#include "snake.h"

void initialiation_allegro() {
    allegro_init(); // appel obligatoire (var.globales, recup. infos syst�me ...)
    install_keyboard(); //pour utiliser le clavier
    install_mouse(); //pour utiliser la souris
    //pour choisir la profondeur de couleurs (8,16,24 ou 32 bits)
    set_color_depth(desktop_color_depth()); //ici�: identique � celle du bureau
    //s�lection du mode graphique
    // avec choix d'un driver+mode+r�solution de l'�cran
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0) != 0) {
        // message et sortie de prog. si �chec
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}

/* PARTIE SNAKE*/



int main() {

    initialiation_allegro();
    snake();
    allegro_exit();
    return (0);
}

END_OF_MAIN();


