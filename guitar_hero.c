#include "guitar_hero.h"

typedef struct {
    int posx;
    float posy;
}t_touche;

int choix_difficulte(BITMAP *image){
    clear_bitmap(image);
    int choix = 0;
    while(choix !=1) {
        textprintf_centre_ex(image, font, 400, 100, makecol(255, 255, 255), -1, "MENU");
        textprintf_centre_ex(image, font, 400, 200, makecol(255, 255, 255), -1, "1- MODE FACILE");
        textprintf_centre_ex(image, font, 400, 300, makecol(255, 255, 255), -1, "2- MODE MOYEN");
        textprintf_centre_ex(image, font, 400, 400, makecol(255, 255, 255), -1, "3- MODE DIFFICILE");
        blit(image,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        if(key[KEY_1_PAD]){
            return 1;
        } else if(key[KEY_2_PAD]){
            return 2;
        } else if(key[KEY_3_PAD]){
            return 3;
        }

    }
}
void Guitar_hero(BITMAP *image){
    t_touche *touche1 = malloc(sizeof (t_touche));
    t_touche *touche2 = malloc(sizeof(t_touche));
    t_touche *touche3 = malloc(sizeof(t_touche));
    t_touche *touche4 = malloc(sizeof(t_touche));
    t_touche *touche5 = malloc(sizeof(t_touche));
    int l = (SCREEN_W / 6);
    float i = 1;
    int score = 0;
    int alea = rand()%800;
    touche1->posy = -alea;
    alea = rand()%800;
    touche2->posy = -alea;
    alea = rand()%800;
    touche3->posy = -alea;
    alea = rand()%800;
    touche4->posy = -alea;
    alea = rand()%800;
    touche5->posy = -alea;
    int etat_prec_touche1 = 0;
    int etat_prec_touche2 = 0;
    int etat_prec_touche3 = 0;
    int etat_prec_touche4 = 0;
    int etat_prec_touche5 = 0;
    int etat_perfect1 = 0;
    int etat_perfect2 = 0;
    int etat_perfect3 = 0;
    int etat_perfect4 = 0;
    int etat_perfect5 = 0;
    float vitesse = 0;
    if(choix_difficulte(image) == 1){
        vitesse = 0.00005;
    } else if(choix_difficulte(image) == 2){
        vitesse = 0.0005;
    } else if(choix_difficulte(image) == 3){
        vitesse = 0.005;
    }
    while(!key[KEY_TAB]) {
        clear_bitmap(image);
        touche1->posx = l;
        touche1->posy = touche1->posy + 0.250*i;
        touche2->posx = l*2;
        touche2->posy = touche2->posy + 0.250*i;
        touche3->posx = l*3;
        touche3->posy = touche3->posy + 0.250*i;
        touche4->posx = l*4;
        touche4->posy = touche4->posy + 0.250*i;
        touche5->posx = l*5;
        touche5->posy = touche5->posy + 0.250*i;
        if(i<=6) {
            i += 0.0005;
        }
        circlefill(image, l, SCREEN_H - 100, 30, makecol(0, 255, 0));
        circlefill(image, l * 2, SCREEN_H - 100, 30, makecol(255, 0, 0));
        circlefill(image, l * 3, SCREEN_H - 100, 30, makecol(255, 255, 0));
        circlefill(image, l * 4, SCREEN_H - 100, 30, makecol(0, 0, 255));
        circlefill(image, l * 5, SCREEN_H - 100, 30, makecol(255, 128, 0));
        circlefill(image, l, SCREEN_H - 100, 15, makecol(0, 0, 0));
        circlefill(image, l * 2, SCREEN_H - 100, 15, makecol(0, 0, 0));
        circlefill(image, l * 3, SCREEN_H - 100, 15, makecol(0, 0, 0));
        circlefill(image, l * 4, SCREEN_H - 100, 15, makecol(0, 0, 0));
        circlefill(image, l * 5, SCREEN_H - 100, 15, makecol(0, 0, 0));
        for (int y = 1; y < 6; y++) {
            line(image, l * y, 0, l * y, SCREEN_H - 100, makecol(255, 255, 255));
        }
        circlefill(image, touche1->posx, touche1->posy, 30, makecol(0, 255, 0));
        circlefill(image, touche2->posx, touche2->posy, 30, makecol(255, 0, 0));
        circlefill(image, touche3->posx, touche3->posy, 30, makecol(255, 255, 0));
        circlefill(image, touche4->posx, touche4->posy, 30, makecol(0, 0, 255));
        circlefill(image, touche5->posx, touche5->posy, 30, makecol(255, 128, 0));
        if (key[KEY_Q]) {
            if(touche1->posy <= SCREEN_H - 70 && touche1->posy >= SCREEN_H - 130 && etat_prec_touche1 == 0){
                etat_perfect1 = 1;
                etat_perfect2 = 0;
                etat_perfect3 = 0;
                etat_perfect4 = 0;
                etat_perfect5 = 0;
                touche1->posy = -rand() % 800;
                score += 50;
            }
            etat_prec_touche1 = 1;
        }
        else{
            etat_prec_touche1 = 0;
        }
        if (touche1->posy >= SCREEN_H - 70) {
            textprintf_ex(image, font, l, 550, makecol(0, 255, 0), -1, "LOUPE");
        }
        if (key[KEY_W]) {
            if(touche2->posy <= SCREEN_H - 70 && touche2->posy >= SCREEN_H - 130 && etat_prec_touche2 == 0) {
                etat_perfect2 = 1;
                touche2->posy = -rand() % 800;
                score += 50;
            }
            etat_prec_touche2 = 1;
        } else {
            etat_prec_touche2 = 0;
        }
        if (touche2->posy >= SCREEN_H - 70) {
            textprintf_ex(image, font, l * 2, 550, makecol(255, 0, 0), -1, "LOUPE");
        }
        if (key[KEY_E]) {
            if(touche3->posy <= SCREEN_H - 70 && touche3->posy >= SCREEN_H - 130 && etat_prec_touche3 == 0){
                etat_perfect3 = 1;
                etat_perfect2 = 0;
                etat_perfect1 = 0;
                etat_perfect4 = 0;
                etat_perfect5 = 0;
                touche3->posy = -rand() % 800;
                score += 50;
            }
            etat_prec_touche3 = 1;
        } else {
            etat_prec_touche3 = 0;
        }
        if (touche3->posy >= SCREEN_H - 70) {
            textprintf_ex(image, font, l * 3, 550, makecol(255, 255, 0), -1, "LOUPE");
        }
        if (key[KEY_R]) {
            if(touche4->posy <= SCREEN_H - 70 && touche4->posy >= SCREEN_H - 130 && etat_prec_touche4 == 0) {
                etat_perfect4 = 1;
                etat_perfect2 = 0;
                etat_perfect3 = 0;
                etat_perfect1 = 0;
                etat_perfect5 = 0;
                touche4->posy = -rand() % 800;
                score += 50;
            }
            etat_prec_touche4 = 1;
        } else{
            etat_prec_touche4 = 0;
        }if (touche4->posy >= SCREEN_H - 70) {
            textprintf_ex(image, font, l * 4, 550, makecol(0, 0, 255), -1, "LOUPE");
        }
        if (key[KEY_T]) {
            if(touche5->posy <= SCREEN_H - 70 && touche5->posy >= SCREEN_H - 130 && etat_prec_touche5 == 0) {
                etat_perfect5 = 1;
                etat_perfect2 = 0;
                etat_perfect3 = 0;
                etat_perfect4 = 0;
                etat_perfect1 = 0;
                touche5->posy = -rand() % 800;
                score += 50;
            }
            etat_prec_touche5 = 1;
        } else{
            etat_prec_touche5 = 0;
        }if (touche5->posy >= SCREEN_H - 70) {
            textprintf_ex(image, font, l * 5, 550, makecol(255, 128, 0), -1, "LOUPE");
        }
        if (touche1->posy >= SCREEN_H + 30) {
            touche1->posy = 0;
            break;
        }
        if (touche2->posy >= SCREEN_H + 30) {
            touche2->posy = 0;
            break;
        }
        if (touche3->posy >= SCREEN_H + 30) {
            touche3->posy = 0;
            break;
        }
        if (touche4->posy >= SCREEN_H + 30) {
            touche4->posy = 0;
            break;
        }
        if (touche5->posy >= SCREEN_H + 30) {
            touche5->posy = 0;
            break;
        }
        if(etat_perfect1 == 1 ){
            textprintf_ex(image,font,20,500, makecol(0,255,0),-1,"PERFECT");
        } else if(etat_perfect2 == 1){
            textprintf_ex(image,font,20,500, makecol(255,0,0),-1,"PERFECT");
        } else if(etat_perfect3 == 1){
            textprintf_ex(image,font,20,500, makecol(255,255,0),-1,"PERFECT");
        } else if(etat_perfect4 == 1){
            textprintf_ex(image,font,20,500, makecol(0,0,255),-1,"PERFECT");
        } else if(etat_perfect5 == 1){
            textprintf_ex(image,font,20,500, makecol(255,128,0),-1,"PERFECT");
        }
        textprintf_ex(image,font,20,300, makecol(255,255,255),-1,"Score : %d",score);
        blit(image,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }
    free(touche1);
    free(touche2);
    free(touche3);
    free(touche4);
    free(touche5);
    allegro_exit();
}

int guitar_hero() {
    srand(time(NULL));
    BITMAP *image = create_bitmap(800, 600);
    show_mouse(screen);
    while (!key[KEY_ESC]) {
        Guitar_hero(image);
    }
    return 0;
}