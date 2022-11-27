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
    int batiment;
    int verification;
} Case;

typedef struct {
    int x, y;
    int caseX, caseY;
    bool interieurPlateau;
} souris;


typedef struct {
    Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR];
} Gen;

typedef struct {
    char *fileName;
    int numCaseX, numCaseY;
    float tempsDuPlacement;
    int nbHabitants;
    bool vivable;
    int eau, electricite;
    int eauNecessaire, electriciteNecessaire;
    int evolution;
    int prix;
    int distanceChateau;
    int distanceCentral;
    int numBatiment;
} Maison;


typedef struct {
    int numMaison;
    int ressourcesAlim;
    int distance;
    int verification;
} MaisonAlim;

typedef struct {
    char *fileName;
    int numCaseX, numCaseY;
    int ressource;
    int capaciteMax;
    int capaciteutilise;
    int nbMaisonAlim;
    MaisonAlim tabMaisonAlim[20];
    int prix;
} Central;


/////////////////////////////// Main ////////////////////////////////////////////
int mainMenu(int *jouer, int *quitter, int *credits, int *communiste, int *capitaliste, int *quitter2, int *charger);

void mainJeu();

////////////////////////////// Timer ///////////////////////////////////////////////
void resetTimer(float *timer, int *monnaie, int habitant, int impots);

////////////////////////////// Initialisation /////////////////////////////////////////
void initialiserPlateau(Case tab[NB_CASE_HAUTEUR][NB_CASE_LARGEUR]);

///////////////////////////// Sauvegarde ///////////////////////////////////////////
void sauvegarde(char *nomFichier, Case tab[NB_CASE_HAUTEUR][NB_CASE_LARGEUR], int argent, int eau, int elec, Maison maison1[100], Central chateaux[20], Central electricite[20]);

void liresauv(char *nomFichier, Case tab[NB_CASE_HAUTEUR][NB_CASE_LARGEUR], int* argent, int* eau, int* elec, Maison maison1[100], Central chateaux[20], Central electricite[20]);


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
                                    Rectangle rec_construire_route, int dessiner, Rectangle parametres);

void afficherEtatMonde(int monde, int afficher_message_reset_routes);

void dessinertout(float timer, souris souris1);

void miseajourtimer(Maison maisons1[100], int nbMaisons);


void initialiserbatiment(Maison maison);

void evolutionbatiment(Maison maison1[100], int nbMaisons, int *capa_eau, int *capa_elec, int *habitant, Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR], Central chateaux[20], int nbChateaux, Central electricite[20]);

void regressionbatiment(Maison maison1[100], int nbMaisons, int *habitant, int *capa_elec, int *capa_eau);

void rechercheCentral(Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR], int x, int y, bool *connecteEau, bool *connecteElec);

int verificationViable(Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR], int x, int y);

void verificationMaisonNonViables(Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR], Maison maison1[100], int nbMaisons);

void rechercheMaison(int *numMaison, Maison maison[100], int x, int y, Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR]);

void analyseChateauxEau(Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR], Central *chateaux, int x, int y, Maison maisons[100],
                   int compteurDistance);

void rechercheRouteConnecteChateaux(Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR], Central chateaux[20], int x, int y,
                                    int nbChateauEau, Maison maison1[100]);

void analyseCentral(Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR], Central *central, int x, int y, Maison maisons[100],int compteurDistance);

void rechercheRouteConnecteCentral(Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR], Central central[20], int x, int y,
                                   int nbChateauEau, Maison maison1[100]);

void afficherInfoBatiments(Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR], souris souris1, int nbChateaux, int nbCentrales, Maison maison1[100], Central chateaux[20], Central electricite[20]);

#endif //BAC_A_SABLE_1_D_JEU_H
