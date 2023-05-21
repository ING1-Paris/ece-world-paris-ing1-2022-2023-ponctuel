#include <stdio.h>
#include <allegro.h>
#include "Frogger.h"
#include "guitar_hero.h"
#include "menu.h"
#include "snake.h"

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
    //pour charger les musiques
    install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,NULL);
    srand(time(NULL));
}

int menu_bis(BITMAP *buffer){
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

void* fhigh_score(BITMAP * buffer,FILE * high_s,int ticket,int tab[10]){
    int remp;
    for(int i=0;i<10;i++){
        fscanf(high_s,"%d\n",&tab[i]);
    }
    for(int i=0;i<10;i++){
        if(ticket > tab[i]){
            remp = tab[i];
            tab[i] = ticket;
            return fhigh_score(buffer,high_s,remp,tab);
        }
    }
    rewind(high_s);
    for(int i=0;i<10;i++){
        fprintf(high_s,"\n%d\n",tab[i]);
    }
    while(!key[KEY_ESC]) {
        clear(buffer);
        for(int y=0;y<2;y++) {
            for (int i = 0; i < 5; i++) {
                textprintf_centre_ex(buffer, font, 400*y+200, 120 * i + 60, makecol(255, 255, 255), -1, "%d - %d",y*5 + i + 1,
                                     tab[y*5+i]);
            }
        }
        blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }
}

int main() {
    initialiation_allegro();
    FILE* high_score = fopen("./high_score.txt","r+");
    if(high_score == NULL){
        printf("Erreur d'ouverture fichier high_score");
    }
    BITMAP *buffer = create_bitmap(800,600);
    int score1 = 50;
    int score2 = 50;
    int nb_ticket1 = 0;
    int nb_ticket2 = 0;
    int egalite = 1;
    int fin = 0;
    int hs[10];
    int ticket;
    int choix;
    int joueur = 1;
    char joueur1[10];
    char joueur2[10];
    printf("Quel est le nom du premier joueur ?\n");
    scanf("%s",joueur1);
    printf("Quel est le nom du second joueur ?\n");
    scanf("%s",joueur2);
    while (fin !=1) {
        egalite = 1;
        printf("Egalite : %d\n",egalite);
        printf("fin : %d\n",fin);
        if(joueur == 1) {
            joueur = 2;
            choix = menu(joueur1, 0);
        } else if(joueur == 2) {
            joueur = 1;
            choix = menu(joueur2, 1);
        } else {
            return 1000;
        }
        printf("Choix : %d\n",choix);
        while (egalite == 1) {
            switch (choix) {
                case 0:
                    score1 = snake();
                    score2 = snake();
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
                    printf("Egalite : %d\n", egalite);
                    printf("fin : %d\n", fin);
                    printf("Choix : %d\n", choix);
                    break;
                case 1:
                    score1 = frogger();
                    if (frogger() == 1) {
                        nb_ticket1++;
                        egalite = 0;
                    } else if (frogger() == 2) {
                        nb_ticket2++;
                        egalite = 0;
                    } else {
                        while (key[KEY_R]) {
                            egalite = 1;
                            clear(buffer);
                            textprintf_centre_ex(buffer, font, 400, 300, makecol(255, 255, 255), -1,
                                                 "Problème du jeu veuillez appuyer sur r pour recommncer");
                            blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                        }
                    }
                    printf("Egalite : %d\n", egalite);
                    printf("fin : %d\n", fin);
                    printf("Choix : %d\n", choix);
                    break;
                case 2:
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
                    printf("Egalite : %d\n", egalite);
                    printf("fin : %d\n", fin);
                    printf("Choix : %d\n", choix);
                    break;
                case 3:
                    egalite = 0;
                    if (nb_ticket1 > nb_ticket2) {
                        ticket = nb_ticket1;
                    } else if (nb_ticket1 < nb_ticket2) {
                        ticket = nb_ticket2;
                    } else if (nb_ticket1 == nb_ticket2) {
                        ticket = nb_ticket1;
                    }
                    rewind(high_score);
                    fhigh_score(buffer, high_score, ticket, hs);
                    for (int i = 0; i < 10; i++) {
                        printf("%d\n", hs[i]);
                    }
                    rewind(high_score);
                    printf("Egalite : %d\n", egalite);
                    printf("fin : %d\n", fin);
                    printf("Choix : %d\n", choix);
                    break;
                case 4:
                    printf("Coucou1\n");
                    egalite = 0;
                    printf("Coucou2\n");
                    fin = 1;
                    printf("Coucou3\n");
                    printf("Egalite : %d\n", egalite);
                    printf("fin : %d\n", fin);
                    printf("Choix : %d\n", choix);
                    break;
                default:
                    printf("ERREUR LORS DE LA MODIFICATION DU CHOIX\n");
                    egalite = 0;
            }
        }
    }
    afficher_tableau(buffer,nb_ticket1,nb_ticket2);
    allegro_exit();
    fclose(high_score);
    high_score = NULL;/*
    int a = 0;
    a = menu("Jules",1);
    printf("%d\n",a);*/
    exit(EXIT_SUCCESS);
    return (0);
}END_OF_MAIN();
