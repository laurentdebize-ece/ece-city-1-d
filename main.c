#include "jeu.h"

enum {
    rien = 0,
    elec = 1,
    eau = 2
} monde;

int communiste;
int capitaliste;
int jouer;
int quitter;
int credits;
float timer = 5;
int monde_eau;
int monde_elec;
int nbMaisons;
int verificationConstructionMaison = 0;
bool veutConstruireCabane = false;
int verificationConstructionCentral = 0;
bool veutConstruireCentral = false;
int verificationConstructionChateau = 0;
bool veutConstruireChateau = false;


Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR];
Maison maison1[100];
souris souris1;



int reset_routes;
int afficher_message_reset_routes;
int construire_routes;

int monnaie = 500000000;
int habitant = 1000000;
int capa_elec = 1000000;
int capa_eau = 1000000;


void mainJeu() {

    initialiserPlateau(plateau);
    //liresauv("../sauvgarde.txt", plateau);

    while (!WindowShouldClose()) {


        Vector2 mouse_pos = GetMousePosition();

        Rectangle rec_yellow = {1000, 100, 180, 60};
        Rectangle rec_blue = {1000, 170, 180, 60};
        Rectangle rec_monnaie = {1660, 15, 240, 30};
        Rectangle rec_habitant = {1700, 55, 200, 30};
        Rectangle rec_capa_elec = {1550, 95, 350, 30};
        Rectangle rec_capa_eau = {1620, 135, 280, 30};
        Rectangle rec_construire_cabane = {20, 915, 200, 55};
        Rectangle rec_construire_centrale = {230, 915, 285, 55};
        Rectangle rec_construire_chateau_d_eau = {525, 915, 110, 55};
        Rectangle rec_construire_route = {645, 915, 200, 55};
        Rectangle rec_routes_reset = {1000, 370, 180, 60};

        BeginDrawing();
        ClearBackground(BLACK);

        chercherCaseDeLaSourie(GetMouseX(), GetMouseY(), &souris1.caseX, &souris1.caseY, &souris1.interieurPlateau);
        dessinerSourieCurseur(souris1);

        resetTimer(&timer);

        timer -= GetFrameTime();

        dessinerBasePlateau(plateau);

        for (int i = 0; i < 35; i++) {
            for (int j = 0; j < 45; j++) {

                if (plateau[i][j].etat == 1) {
                    DrawRectangle(plateau[i][j].x, plateau[i][j].y, 20, 20,
                                  monde == 2 ? BLUE : monde == 1 ? YELLOW : GRAY);
                    DrawRectangleLines(plateau[i][j].x, plateau[i][j].y, 20, 20, WHITE); // creation des routes
                    if (reset_routes == true && monde == 0) {
                        DrawText(TextFormat("Cliquer sur la route que \n vous souhaitez retirer"), 1000, 267, 20,
                                 WHITE);
                        DrawRectangle(souris1.caseX * 20 + 20, souris1.caseY * 20 + 20, 20, 20, RED);
                        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                            if (construire_routes == true) {
                                construire_routes = false;
                            }
                            plateau[souris1.caseY][souris1.caseX].etat = 0;
                        }
                    } else if (reset_routes == false) {
                        plateau[i][j].etat = 1;
                    }
                }
                if(plateau[i][j].etat == 2){
                    DrawRectangle(plateau[i][j].x, plateau[i][j].y, 20, 20, RED);
                }
                if(plateau[i][j].batiment == 1){
                    //afficher l'image
                }
                if(plateau[i][j].etat == 7){
                    DrawRectangle(plateau[i][j].x, plateau[i][j].y, 20, 20, YELLOW);
                }
                if(plateau[i][j].etat == 8){
                    DrawRectangle(plateau[i][j].x, plateau[i][j].y, 20, 20, BLUE);
                }
            }

        }


        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            construireRoute(souris1, construire_routes, monde, plateau);

            if (CheckCollisionPointRec(mouse_pos, rec_construire_route)) {
                construire_routes = !construire_routes;
            }
            if (CheckCollisionPointRec(mouse_pos, rec_routes_reset)) {
                afficher_message_reset_routes = !afficher_message_reset_routes;
            }

            if (CheckCollisionPointRec(mouse_pos, rec_yellow)) {
                monde = 1;
            } else if (CheckCollisionPointRec(mouse_pos, rec_blue)) {
                monde = 2;
            } else if (IsKeyPressed(KEY_ENTER)) {   // peut etre le deplacé en dehors parceque faut appuyer sur la souris pour que ça marche
                monde = 0;
            }

        }
        if (IsKeyDown(KEY_BACKSPACE)) {
            reset_routes = true;
        } else {
            if (reset_routes == true) {
                reset_routes = false;
            }
        }

        if (CheckCollisionPointRec(mouse_pos, rec_construire_cabane)) {
            //DrawRectangle(0,0,50,50,RED);
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                if(veutConstruireCabane)
                    veutConstruireCabane = false;
                else
                    veutConstruireCabane = true;

                veutConstruireChateau = false;
                veutConstruireCentral = false;
            }

        }
        if (veutConstruireCabane){
            verificationConstructionMaison = 0;
            DrawRectangle(0,0,50,50,RED);
            if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)  && souris1.interieurPlateau) {
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        if ((plateau[souris1.caseY+j][souris1.caseX+i].etat != 0) || (souris1.caseX+3>NB_CASE_LARGEUR || souris1.caseY+3>NB_CASE_HAUTEUR)){
                            verificationConstructionMaison++;
                        }
                    }
                }
                if(verificationConstructionMaison==0){
                    plateau[souris1.caseY][souris1.caseX].batiment = 1;
                    for (int i = 0; i < 3; ++i) {
                        for (int j = 0; j < 3; ++j) {
                            plateau[souris1.caseY+j][souris1.caseX+i].etat = 2;
                        }
                    }
                }
            }
        }

        if (CheckCollisionPointRec(mouse_pos, rec_construire_centrale)) {
            //DrawRectangle(0,0,50,50,RED);
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                if(veutConstruireCentral)
                    veutConstruireCentral = false;
                else
                    veutConstruireCentral = true;

                veutConstruireChateau = false;
                veutConstruireCabane = false;

            }

        }
        if (veutConstruireCentral){
            verificationConstructionCentral = 0;
            DrawRectangle(50,0,50,50,YELLOW);
            if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)  && souris1.interieurPlateau) {
                for (int i = 0; i < 6; ++i) {
                    for (int j = 0; j < 4; ++j) {
                        if ((plateau[souris1.caseY+j][souris1.caseX+i].etat != 0) || (souris1.caseX+6>NB_CASE_LARGEUR || souris1.caseY+4>NB_CASE_HAUTEUR)){
                            verificationConstructionCentral++;
                        }
                    }
                }
                if(verificationConstructionCentral==0){
                    plateau[souris1.caseY][souris1.caseX].batiment = 7;
                    for (int i = 0; i < 6; ++i) {
                        for (int j = 0; j < 4; ++j) {
                            plateau[souris1.caseY+j][souris1.caseX+i].etat = 7;
                        }
                    }
                }
            }
        }

        if (CheckCollisionPointRec(mouse_pos, rec_construire_chateau_d_eau)) {
            //DrawRectangle(0,0,50,50,RED);
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                if(veutConstruireChateau)
                    veutConstruireChateau = false;
                else
                    veutConstruireChateau = true;

                veutConstruireCabane = false;
                veutConstruireCentral = false;
            }

        }
        if (veutConstruireChateau){
            verificationConstructionChateau = 0;
            DrawRectangle(100,0,50,50,BLUE);
            if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && souris1.interieurPlateau) {
                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 6; ++j) {
                        if ((plateau[souris1.caseY+j][souris1.caseX+i].etat != 0) || (souris1.caseX+4>NB_CASE_LARGEUR || souris1.caseY+6>NB_CASE_HAUTEUR)){
                            verificationConstructionChateau++;
                        }
                    }
                }
                if(verificationConstructionChateau==0){
                    plateau[souris1.caseY][souris1.caseX].batiment = 8;
                    for (int i = 0; i < 4; ++i) {
                        for (int j = 0; j < 6; ++j) {
                            plateau[souris1.caseY+j][souris1.caseX+i].etat = 8;
                        }
                    }
                }
            }
        }






        DrawText(TextFormat("CaseX :%d", souris1.caseX), 950, 50, 20, WHITE);
        DrawText(TextFormat("CaseY :%d", souris1.caseY), 950, 70, 20, WHITE);

        if (timer <= 1) {
            DrawText(TextFormat("Nouveau Cycle"), 180, 280, 80, GREEN);
        }

        dessinerCasesEtages(rec_yellow, rec_blue, mouse_pos);

        dessinerVariables(rec_monnaie, rec_habitant, rec_capa_elec, rec_capa_eau, mouse_pos, monnaie, habitant,
                          capa_elec, capa_eau);


        dessinerCasesChoixConstruction( mouse_pos,  rec_construire_cabane,  rec_routes_reset,
                                        rec_construire_centrale,  rec_construire_chateau_d_eau,
                                        rec_construire_route);




        afficherEtatMonde(monde, afficher_message_reset_routes);

        dessinertout(timer);
        EndDrawing();
        }
    sauvegarde("../sauvgarde.txt", plateau);
}


int main() {
    mainMenu(&jouer, &quitter, &credits, &communiste, &capitaliste);

    return 0;
}