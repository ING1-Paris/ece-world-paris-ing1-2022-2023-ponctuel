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

void afficher_tableau(BITMAP *buffer, int score1, int score2){
    BITMAP * glitch1 = load_bitmap("../assets/menu/ImageGlitch1.bmp",NULL);
    BITMAP * glitch2 = load_bitmap("../assets/menu/ImageGlitch2.bmp",NULL);
    BITMAP * glitch3 = load_bitmap("../assets/menu/ImageGlitch3.bmp",NULL);
    BITMAP * glitch4 = load_bitmap("../assets/menu/ImageGlitch4.bmp",NULL);
    while(!key[KEY_ESC]) {
        clear_bitmap(buffer);
        int alea = rand()%50;
        int posx = rand()%800;
        int posy = rand()%600;
        textprintf_centre_ex(buffer, font, 400, 100, makecol(255, 255, 255), -1, "Score du joueur 1 : %d", score1);
        textprintf_centre_ex(buffer, font, 400, 200, makecol(255, 255, 255), -1, "Score du joueur 2 : %d", score2);
        if(alea == 0){
            blit(glitch1,buffer,0,0,posx,posy,80,82);
        } else if(alea == 1){
            blit(glitch2,buffer,0,0,posx,posy,92,71);
        } else if(alea == 2){
            blit(glitch3,buffer,0,0,posx,posy,92,80);
        } else if(alea == 3){
            blit(glitch4,buffer,0,0,posx,posy,122,101);
        }
        if(score1>score2) {
            textprintf_centre_ex(buffer, font, 400, 300, makecol(255, 255, 255), -1, "Joueur 1 est le vainqueur !");
        } else if(score1<score2) {
            textprintf_centre_ex(buffer, font, 400, 300, makecol(255, 255, 255), -1, "Joueur 2 est le vainqueur !");
        } if(score1==score2) {
            textprintf_centre_ex(buffer, font, 400, 300, makecol(255, 255, 255), -1, "Vous êtes a égalité !");
        }
        blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }
}
int main() {
    printf("%d",2%2);
    initialiation_allegro();
    BITMAP *buffer = create_bitmap(800,600);
    int score1 = 50;
    int score2 = 50;
    int nb_ticket1 = 0;
    int nb_ticket2 = 0;
    int egalite = 1;
    int fin = 0;
    int choix = menu(buffer);
    while (fin !=1) {
        while (egalite == 1) {
            switch (choix) {
                case 1:
                    break;
                case 2:
                    //score1 = frogger();
                    if (score1 == 1) {
                        nb_ticket1++;
                        egalite = 0;
                    } else if (score1 == 2) {
                        nb_ticket2++;
                        egalite = 0;
                    }
                case 3:
                    score1 = guitar_hero();
                    score2 = guitar_hero();
                    if (score1 > score2) {
                        nb_ticket1++;
                        egalite = 0;
                    } else if (score1 < score2) {
                        nb_ticket2++;
                        egalite = 0;
                    } else if (score1 == score2) {
                        egalite = 1;
                        while (!key[KEY_R]) {
                            clear_bitmap(buffer);
                            textprintf_centre_ex(buffer, font, 400, 300, makecol(255, 255, 255), -1,
                                                 "Vous etes a egalite ! Appuyer sur r pour recommencer");
                            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                        }
                    }
            }
        }
        while(1) {
            clear(buffer);
            textprintf_centre_ex(buffer, font, 400, 300, makecol(255, 255, 255), -1,"Voulez-vous arretez ? Appuyer sur a pour non et b pour oui");
            if(key[KEY_B]){
                fin = 1;
                break;
            } else if(key[KEY_Q]) {
                egalite = 1;
                break;
            }
            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        }
    }
    afficher_tableau(buffer,nb_ticket1,nb_ticket2);
    allegro_exit();
    exit(EXIT_SUCCESS);
    return (0);
}END_OF_MAIN();