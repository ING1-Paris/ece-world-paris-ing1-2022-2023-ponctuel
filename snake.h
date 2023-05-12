//
// Created by cleme on 12/05/2023.
//

#ifndef PROJET_SNAKE_H
#define PROJET_SNAKE_H

#define VITSNAKE 5

BITMAP *buffer;
BITMAP *tete_s, *queue_s, *fond_s;
typedef struct Queue {
    int posX, posY;//la position à laquelle il est affiché
    int cadX, cadY;//la position dans le cadrier
    struct Queue *suivant;
} t_queue;
typedef struct {
    int posX, posY;//la position à laquelle il est affiché
    int cadX, cadY;//la position dans le cadrier
    int direct, futDirect;//la direction actuelle et la prochaine
    t_queue *suivant;
} t_tete;

void effacerQueue(t_queue *maillon) {
    blit(fond_s, buffer, maillon->posX, maillon->posY, maillon->posX, maillon->posY, 50, 50);
    if (maillon->suivant) {
        effacerQueue(maillon->suivant);
    }
}
void effacerSerpent(t_tete *tete) {
    blit(fond_s, buffer, tete->posX, tete->posY, tete->posX, tete->posY, 50, 50);
    if (tete->suivant) {
        effacerQueue(tete->suivant);
    }
}
void afficherQueue(t_queue *maillon) {
    masked_blit(queue_s, buffer, 0, 0, maillon->posX, maillon->posY, 50, 50);
    if (maillon->suivant) {
        afficherQueue(maillon->suivant);
    }
}
void afficherSerpent(t_tete *tete) {
    masked_blit(tete_s, buffer, 0, 0, tete->posX, tete->posY, 50, 50);
    if (tete->suivant) {
        afficherQueue(tete->suivant);
    }
}
void pasQueue(t_queue *maillon, int futCadx, int futCady) {
    //printf("actuel: %d %d , Futur: %d %d \n",maillon->cadX,maillon->cadY,futCadx,futCady);
    if (maillon->cadX > futCadx){
        maillon->posX--;
        //printf("  gauche  ");
    }
    else if (maillon->cadX < futCadx) {
        maillon->posX++;
        //printf(" droite ");
    }
    else if (maillon->cadY < futCady) {
        maillon->posY++;
        //printf(" bas ");
    }
    else  if(maillon->cadY > futCady){
        maillon->posY--;
        //printf(" haut ");
    }
    if (maillon->suivant) {
        pasQueue(maillon->suivant, maillon->cadX, maillon->cadY);
    }
}
void actCaseQueue(t_queue *maillon, int X, int Y){
    if(maillon->suivant){
        actCaseQueue(maillon->suivant,maillon->cadX,maillon->cadY);
    }
    maillon->cadX=X;
    maillon->cadY=Y;
}
void pasSerpent(t_tete *tete) {//déplacement d'un pixel
    switch (tete->direct) {
        case (1): {
            tete->posX--;
            break;
        }
        case (2): {
            tete->posX++;
            break;
        }
        case (3): {
            tete->posY--;
            break;
        }
        case (4): {
            tete->posY++;
            break;
        }

    }
    if (tete->suivant) pasQueue(tete->suivant, tete->cadX , tete->cadY);
}
void caseSerpent(t_tete *tete) {
    for (int i = 0; i < 50; ++i) {
        effacerSerpent(tete);
        pasSerpent(tete);
        afficherSerpent(tete);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(VITSNAKE);
        if(key[KEY_RIGHT] && (tete->direct!=1)){
            tete->futDirect=2;
        }
        else if(key[KEY_LEFT] && (tete->direct!=2)){
            tete->futDirect=1;
        }
        else if(key[KEY_UP] && (tete->direct!=4)){
            tete->futDirect=3;
        }
        else if(key[KEY_DOWN] && (tete->direct!=3)){
            tete->futDirect=4;
        }
    }
    //printf("Le serpent est en %d %d, la queue est en %d %d\n",tete->cadX,tete->cadY,tete->suivant->cadX,tete->suivant->cadY);
    if(tete->suivant){
        actCaseQueue(tete->suivant,tete->cadX,tete->cadY);
    }
    switch (tete->direct) {
        case (1): {
            tete->cadX--;
            break;
        }
        case (2): {
            tete->cadX++;
            break;
        }
        case (3): {
            tete->cadY--;
            break;
        }
        case (4): {
            tete->cadY++;
            break;
        }

    }
    tete->direct=tete->futDirect;
}

void viderQueue(t_queue* maillon){
    if(maillon->suivant){printf("liberation de %d\n",maillon->suivant); viderQueue(maillon->suivant);}
    free(maillon);
}
void viderSerpent(t_tete* tete){
    if(tete->suivant) viderQueue(tete->suivant);
    free(tete);
}

void ajouterQueueQ(t_queue* maillon){
    printf("ajouterQueueq\n");
    if(maillon->suivant) ajouterQueueQ(maillon->suivant);
    else{
        printf("pasQueueici\n");
        maillon->suivant= malloc(sizeof(t_queue));
        maillon->suivant->cadY=maillon->cadY;
        maillon->suivant->cadX=maillon->cadX;
        maillon->suivant->posX=maillon->posX;
        maillon->suivant->posY=maillon->posY;
        maillon->suivant->suivant=NULL;
        printf("creation de queue en %d %d (%d %d)\n",maillon->suivant->cadX,maillon->suivant->cadY,maillon->suivant->posX,maillon->suivant->posY);
        //printf("source: %d %d (%d %d)",maillon->cadX,maillon->cadY)
    }
}
void ajouterQueue(t_tete* serpent){
    printf("ajouterQueue\n");
    if(serpent->suivant) ajouterQueueQ(serpent->suivant);
    else{
        serpent->suivant= malloc(sizeof(t_queue));
        serpent->suivant->cadY=serpent->cadY;
        serpent->suivant->cadX=serpent->cadX;
        serpent->suivant->posX=serpent->cadX;
        serpent->suivant->posY=serpent->posY;
        serpent->suivant->suivant=NULL;
    }
}

void snake() {
    buffer = create_bitmap(SCREEN_W, SCREEN_H);

    // Chargement de l'image
    tete_s = load_bitmap("../images/tete_s.bmp", NULL);
    if (!tete_s) {
        allegro_message("n'a pas pu trouver/charger ../images/tete_s.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    queue_s = load_bitmap("../images/queue_s.bmp", NULL);
    if (!queue_s) {
        allegro_message("n'a pas pu trouver/charger ../images/queue_s.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);

    }
    fond_s = load_bitmap("../images/fond_s.bmp", NULL);
    if (!fond_s) {
        allegro_message("n'a pas pu trouver/charger ../images/fond_s.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    blit(fond_s, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

    t_tete *serpent = malloc(sizeof(t_tete));
    serpent->posY = 50;
    serpent->posX = 150;
    serpent->cadY=0;
    serpent->cadX=0;
    serpent->direct = 2;
    serpent->futDirect=2;
    serpent->suivant=malloc(sizeof (t_queue));
    serpent->suivant->posY=50;
    serpent->suivant->posX=150;
    serpent->suivant->cadX=0;
    serpent->suivant->cadY=0;
    serpent->suivant->suivant=NULL;
    ajouterQueue(serpent);

    while (!key[KEY_ESC]) {
        caseSerpent(serpent);
        rest(VITSNAKE);
        if(key[KEY_R]){
            ajouterQueue(serpent);
        }
    }
    viderSerpent(serpent);

}
#endif //PROJET_SNAKE_H
