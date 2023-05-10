#include <stdio.h>
#include <allegro.h>
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

/* PARTIE SNAKE*/
BITMAP* buffer;
BITMAP* tete_s,*queue_s,*fond_s;
typedef struct Queue{
    int posX,posY;//la position à laquelle il est affiché
    int cadX,cadY;//la position dans le cadrier
    struct Queue* suivant;
}t_queue;
typedef struct{
    int posX,posY;//la position à laquelle il est affiché
    int cadX,cadY;//la position dans le cadrier
    int direct,futDirect;//la direction actuelle et la prochaine
    t_queue* suivant;
}t_tete;
void effacerQueue(t_queue* maillon){
    blit(fond_s,buffer,maillon->posX,maillon->posY,maillon->posX,maillon->posY,25,25);
    if(maillon->suivant){
        effacerQueue(maillon->suivant);
    }
}
void effacerSerpent(t_tete* tete){
    blit(fond_s,buffer,tete->posX,tete->posY,tete->posX,tete->posY,25,25);
    if(tete->suivant){
        effacerQueue(tete->suivant);
    }
}
void afficherQueue(t_queue* maillon){
    blit(queue_s,buffer,0,0,maillon->posX,maillon->posY,25,25);
    if(maillon->suivant){
        afficherQueue(maillon->suivant);
    }
}
void afficherSerpent(t_tete* tete){
    blit(queue_s,buffer,0,0,tete->posX,tete->posY,25,25);
    if(tete->suivant){
        afficherQueue(tete->suivant);
    }
}
void pasQueue(t_queue* maillon, int futCadx,int futCady){
    if(maillon->cadX>futCadx) maillon->posX--;
    else if(maillon->cadX<futCadx) maillon->posX++;
    else if(maillon->cadY<futCady) maillon->posY++;
    else maillon->posY--;
    if(maillon->suivant){
        pasQueue(maillon->suivant,maillon->cadX,maillon->cadY);
    }
}
void pasSerpent(t_tete* tete){//déplacement d'un pixel
    switch(tete->direct){
        case(1):{
            tete->posX--;
            if(tete->suivant) pasQueue(tete->suivant,tete->cadX-1,tete->cadY);
            break;
        }
        case(2):{
            tete->posX++;
            if(tete->suivant) pasQueue(tete->suivant,tete->cadX+1,tete->cadY);
            break;
        }
        case(3):{
            tete->posY--;
            if(tete->suivant) pasQueue(tete->suivant,tete->cadX,tete->cadY-1);
            break;
        }
        case(4):{
            tete->posY++;
            if(tete->suivant) pasQueue(tete->suivant,tete->cadX,tete->cadY+1);
            break;
        }

    }
}

void snake(){
    buffer=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(buffer);

    // Chargement de l'image
    tete_s=load_bitmap("../images/tete_s.bmp",NULL);
    if (!tete_s)  {
        allegro_message("n'a pas pu trouver/charger ../images/tete_s.bmp");
        allegro_exit(); exit(EXIT_FAILURE);
    }
    queue_s=load_bitmap("../images/queue_s.bmp",NULL);
    if (!queue_s)  {
        allegro_message("n'a pas pu trouver/charger ../images/queue_s.bmp");
        allegro_exit(); exit(EXIT_FAILURE);

    }
    fond_s=load_bitmap("../images/fond_s.bmp",NULL);
    if (!fond_s)  {
        allegro_message("n'a pas pu trouver/charger ../images/fond_s.bmp");
        allegro_exit(); exit(EXIT_FAILURE);
    }



    blit(fond_s,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    while (!key[KEY_ESC]){
    }
}
int main() {
    initialiation_allegro();
    snake();
    allegro_exit();
    return (0);
}END_OF_MAIN();


