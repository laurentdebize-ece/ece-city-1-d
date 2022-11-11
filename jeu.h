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
    int x, y;
    int caseX, caseY;
    bool interieurPlateau;
} souris;


typedef struct {
    Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR];
} Gen;


/////////////////////////////// Main ////////////////////////////////////////////
int mainMenu(int *jouer, int *quitter, int *credits, int *communiste, int *capitaliste);

void mainJeu();


void construireRoute(souris souris1, int construire_routes, int monde, Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR]);

////////////////////////////// Timer ///////////////////////////////////////////////
void resetTimer(float *timer);

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

void dessinerVariables(Rectangle rec_monnaie, Rectangle rec_habitant, Rectangle rec_capa_elec, Rectangle rec_capa_eau,
                       Vector2 mouse_pos, int monnaie, int habitant, int capa_elec, int capa_eau);

void dessinerCasesChoixConstruction(Vector2 mouse_pos, Rectangle rec_construire_cabane, Rectangle rec_routes_reset,
                                    Rectangle rec_construire_centrale, Rectangle rec_construire_chateau_d_eau,
                                    Rectangle rec_construire_route);

void afficherEtatMonde(int monde, int afficher_message_reset_routes);

void dessinertout(float timer);

#endif //BAC_A_SABLE_1_D_JEU_H
