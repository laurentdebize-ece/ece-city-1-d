#ifndef BAC_A_SABLE_1_D_JEU_H
#define BAC_A_SABLE_1_D_JEU_H

#include <stdio.h>
#include <raylib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

#define NB_CASE_HAUTEUR 35
#define NB_CASE_LARGEUR 45
#define LARGEUR_CASE 20


typedef struct {
    int x, y;
    int largeur;
    int etat;
    int etatInterdit;
} Case;

typedef struct {
    int x,y;
    int caseX, caseY;
    bool interieurPlateau;
} souris;




typedef struct {
    Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR];
}Gen;


/////////////////////////////// Main ////////////////////////////////////////////
int mainMenu(int* jouer, int* quitter, int* credits, int* communiste, int* capitaliste);
void mainJeu();


void construireRoute(souris souris1, int construire_routes, int monde, Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR]);
////////////////////////////// Timer ///////////////////////////////////////////////
void resetTimer(int* timer);

////////////////////////////// Initialisation /////////////////////////////////////////
void initialiserPlateau(Case tab[NB_CASE_HAUTEUR][NB_CASE_LARGEUR]);

///////////////////////////// Sauvegarde ///////////////////////////////////////////
void sauvegarde(char *nomFichier, Case tab[NB_CASE_HAUTEUR][NB_CASE_LARGEUR]);
void liresauv(char *nomFichier, Case tab[NB_CASE_HAUTEUR][NB_CASE_LARGEUR]);




//////////////////////////// Sourie ////////////////////////////////////////////////
void chercherCaseDeLaSourie(int x, int y, int *caseX, int *caseY, bool *dansPlateau);





//////////////////////////// Affichage ////////////////////////////////////////////////////

void dessinerSourieCurseur(souris souris1);
void dessinerBasePlateau(Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR]);
void dessinerCasesEtages(Rectangle rec_yellow, Rectangle rec_blue, Vector2 mouse_pos);
void dessinertout(int timer);

#endif //BAC_A_SABLE_1_D_JEU_H
