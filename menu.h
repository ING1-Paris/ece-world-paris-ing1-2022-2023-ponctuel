//
// Created by cleme on 18/05/2023.
//

#ifndef PROJET_MENU_H
#define PROJET_MENU_H

#define nombreStructures 5
#define vitessePerso 15
typedef struct{
    int posX,posY;
    int identite;//definit les touches
    int choisit; //dit s'il choisit le mini jeu
    BITMAP* texture;
}t_personnage;
typedef struct{
    int posX,posY;
    BITMAP* texture;
    int action;//en cas de contact avec cette structure, définit quel return sera envoyé
    int vitX,vitY;//vitesse du bâtiment (parce que des bâtiments mobiles sont plus amusants
    int active;//dit si le bâtiment a été enclenché par un joueur
}t_batiment;

t_personnage persos[2];
 BITMAP* fondMenu;
t_batiment opBat(BITMAP * buffer,t_batiment batiment,t_personnage personnages[2]){//ensemble des opérations devant être effectuées par chaque bâtiment à chaque tour de boucle
    int proximite=0;//indique si on est proche d'un joueur
    int texture=1;
    blit(fondMenu,buffer,batiment.posX-40,batiment.posY-40,batiment.posX-40,batiment.posY-40,80,80);
    if(batiment.posX>=SCREEN_W){
        batiment.vitX=-batiment.vitX;
        batiment.vitY+=(rand()%3)-2;
        batiment.posX-=batiment.posX-SCREEN_W;
    }//détection des murs
    else if(batiment.posX<=0){
        batiment.vitX=-batiment.vitX;
        batiment.vitY+=(rand()%3)-2;
        batiment.posX-=batiment.posX;
    }
    if(batiment.posY>=SCREEN_H){
        batiment.vitY=-batiment.vitY;
        batiment.vitX+=(rand()%3)-2;
        batiment.posY-=batiment.posY-SCREEN_H;
    }
    else if(batiment.posY<=0){
        batiment.vitY=-batiment.vitY;
        batiment.vitX+=(rand()%3)-1;
        batiment.posY-=batiment.posY;
    }
    while(batiment.vitX==0 && batiment.vitY==0 || (batiment.vitX*batiment.vitX+batiment.vitY*batiment.vitY)>=20 ){
        batiment.vitX=rand()%5-2;
        batiment.vitY=rand()%5-2;
    }

    batiment.posX+=batiment.vitX;//déplacement
    batiment.posY+=batiment.vitY;


    for(int i=0;i<2;i++){
        proximite=(batiment.posX-personnages[i].posX)*(batiment.posX-personnages[i].posX)
                 +(batiment.posY-personnages[i].posY)*(batiment.posY-personnages[i].posY);
        if(proximite<=25000 && texture){
            texture=0;
        }
        if(proximite<=700 && personnages[i].choisit){
            batiment.active=1;
        }
    }

    masked_blit(batiment.texture,buffer,texture*80,0,batiment.posX-40,batiment.posY-40,80,80);
    return(batiment);
}
t_personnage opPerso(BITMAP *buffer,t_personnage perso){
    blit(fondMenu,buffer,perso.posX-20,perso.posY-20,perso.posX-20,perso.posY-20,40,40);
    if((key[KEY_W] && perso.identite==0 || key[KEY_UP] && perso.identite==1) && perso.posY>=(0+vitessePerso)){
        perso.posY-=vitessePerso;
    }
    if((key[KEY_A] && perso.identite==0 || key[KEY_LEFT] && perso.identite==1)&& perso.posX>=(0+vitessePerso)){
        perso.posX-=vitessePerso;
    }
    if((key[KEY_S] && perso.identite==0 || key[KEY_DOWN] && perso.identite==1)&& perso.posY<=(SCREEN_H-vitessePerso)){
        perso.posY+=vitessePerso;
    }
    if((key[KEY_D] && perso.identite==0 || key[KEY_RIGHT] && perso.identite==1)&& perso.posY<=(SCREEN_W-vitessePerso)){
        perso.posX+=vitessePerso;
    }
    blit(perso.texture,buffer,0,0,perso.posX-20,perso.posY-20,40,40);
    return(perso);
}

int menu(char* nom,int idjoueur){//prend en paramètre le nom du joueur
    BITMAP *buffer= create_bitmap(800,600);
    t_batiment batiments[nombreStructures];
    t_personnage personnages[2];
    for (int i=0;i<nombreStructures;i++){
        batiments[i].posX=rand()%700;
        batiments[i].posY=rand()%300;
        batiments[i].vitX=rand()%5-2;
        batiments[i].vitY=rand()%5-2;
        batiments[i].action=i;
        batiments[i].active=0;
    }//déclaration des bâtiments
    batiments[0].texture =load_bitmap("../assets/menu/snake.bmp", NULL);
    if (!batiments[0].texture) {
        allegro_message("n'a pas pu trouver/charger ../assets/menu/snake.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);

    }batiments[1].texture =load_bitmap("../assets/menu/frogger.bmp", NULL);
    if (!batiments[1].texture) {
        allegro_message("n'a pas pu trouver/charger ../assets/menu/frogger.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);

    }batiments[2].texture =load_bitmap("../assets/menu/guitareHero.bmp", NULL);
    if (!batiments[2].texture) {
        allegro_message("n'a pas pu trouver/charger ../assets/menu/guitareHero.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);

    }batiments[3].texture =load_bitmap("../assets/menu/scores.bmp", NULL);
    if (!batiments[3].texture) {
        allegro_message("n'a pas pu trouver/charger ../assets/menu/scores.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);

    }batiments[4].texture =load_bitmap("../assets/menu/sortie.bmp", NULL);
    if (!batiments[4].texture) {
        allegro_message("n'a pas pu trouver/charger ../assets/menu/sortie.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 2; ++i) {
        personnages[i].posY=450;
        personnages[i].posX=150+450*i;
        personnages[i].identite=i;
    }
    if(idjoueur==0){
        personnages[0].choisit=1;personnages[1].choisit=0;
    }
    else{
        personnages[0].choisit=0;personnages[1].choisit=1;
    }
    personnages[0].texture= load_bitmap("../assets/menu/joueur1.bmp",NULL);
    if (!personnages[0].texture) {
        allegro_message("n'a pas pu trouver/charger ../assets/menu/joueur1.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    personnages[1].texture= load_bitmap("../assets/menu/joueur2.bmp",NULL);
    if (!personnages[1].texture) {
        allegro_message("n'a pas pu trouver/charger ../assets/menu/joueur2.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    fondMenu= load_bitmap("../assets/menu/fond.bmp",NULL);
    if (!fondMenu) {
        allegro_message("n'a pas pu trouver/charger ../assets/menu/fond.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    textprintf_right_ex(fondMenu,font,480,580,makecol(255,255,255),-1,"C'est a %s de choisir un jeu",nom);
    if(idjoueur==0){
        textprintf_right_ex(fondMenu,font,480,490,makecol(255,255,255),-1,"%s est à gauche et utilise ZQSD",nom);
    }
    else{
        textprintf_right_ex(fondMenu,font,480,590,makecol(255,255,255),-1,"%s est à droite et utilise les fleches",nom);
    }
    blit(fondMenu,buffer,0,0,0,0,SCREEN_W,SCREEN_H);

    while(key[KEY_ESC]){
        rest(1);
    }
    while (!key[KEY_ESC]){
        for (int i = 0; i < nombreStructures; ++i) {

            batiments[i]= opBat(buffer,batiments[i],personnages);
            if(batiments[i].active){
                printf("Retour du menu: %d\n",batiments[i].action);
                return(batiments[i].action);
            }
        }
        for (int i = 0; i < 2; ++i) {
            personnages[i]= opPerso(buffer,personnages[i]);
        }
        blit(buffer,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        rest(50);

    }

return(-1);
}



#endif //PROJET_MENU_H
