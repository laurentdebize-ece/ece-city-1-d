#include "jeu.h"

enum{
    rien = 0,
    elec = 1,
    eau = 2
}monde;
enum{
    nulle = 0,
    cabane = 1,
    centrale = 2,
    chateau = 3,
    route = 4
}veut_construire;

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
int verificationConstructionRoutes = 0;


Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR];
Maison maison1[100];
souris souris1;



int reset_routes;
int afficher_message_reset_routes;

int monnaie = 500000000;
int habitant = 1000000;
int capa_elec = 1000000;
int capa_eau = 1000000;


void mainJeu() {
    SetTargetFPS(1000);
    Rectangle rec_yellow = {1000, 100, 180, 60};
    Rectangle rec_blue = {1000, 170, 180, 60};
    Rectangle rec_monnaie = {1660, 15, 240, 30};
    Rectangle rec_habitant = {1700, 55, 200, 30};
    Rectangle rec_capa_elec = {1550, 95, 350, 30};
    Rectangle rec_capa_eau = {1620, 135, 280, 30};
    Rectangle rec_construire_cabane = {20,915,200,55};
    Rectangle rec_construire_centrale = {230,915,285,55};
    Rectangle rec_construire_chateau_d_eau = {525,915,110,55};
    Rectangle rec_construire_route = {645,915,200,55};
    Rectangle rec_routes_reset = {1000, 370, 180, 60};
    Rectangle aire_de_jeu = {20,20,45*20,35*20};

    Image ruine;
    Image terrain_vague;
    Image cabane;
    Image maison;
    Image immeuble;
    Image gratte_ciel;
    Image centrale;
    Image chateau_d_eau;

    ruine = LoadImage("../batiments/Ruine.png");
    terrain_vague = LoadImage("../batiments/Terrain_vague.png");
    cabane = LoadImage("../batiments/Cabane.png");
    maison = LoadImage("../batiments/Maison.png");
    immeuble = LoadImage("../batiments/Immeuble.png");
    gratte_ciel = LoadImage("../batiments/Gratte_ciel.png");
    centrale = LoadImage("../batiments/Centrale_electrique_2.png");
    chateau_d_eau = LoadImage("../batiments/Chateau_d_eau.png");

    Texture2D texture3 = LoadTextureFromImage(cabane);
    Texture2D texture4 = LoadTextureFromImage(centrale);
    Texture2D texture5 = LoadTextureFromImage(chateau_d_eau);
    Texture2D texture6 = LoadTextureFromImage(ruine);
    Texture2D texture7 = LoadTextureFromImage(terrain_vague);
    Texture2D texture8 = LoadTextureFromImage(maison);
    Texture2D texture9 = LoadTextureFromImage(immeuble);
    Texture2D texture10 = LoadTextureFromImage(gratte_ciel);

    UnloadImage(cabane);
    UnloadImage(centrale);
    UnloadImage(chateau_d_eau);
    UnloadImage(terrain_vague);
    UnloadImage(ruine);
    UnloadImage(maison);
    UnloadImage(immeuble);
    UnloadImage(gratte_ciel);


    initialiserPlateau(plateau);
    //liresauv("../sauvgarde.txt", plateau);


    while (!WindowShouldClose()) {


        Vector2 mouse_pos = GetMousePosition();




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
                    DrawRectangle(plateau[i][j].x, plateau[i][j].y, 20, 20,monde == 2 ? BLUE : monde == 1 ? YELLOW : GRAY);
                    DrawRectangleLines(plateau[i][j].x, plateau[i][j].y, 20, 20, BLACK); // creation des routes
                    if (reset_routes == true && monde == 0 && plateau[souris1.caseY][souris1.caseX].etat != 2 && plateau[souris1.caseY][souris1.caseX].etat != 7 && plateau[souris1.caseY][souris1.caseX].etat != 8) {
                        DrawText(TextFormat("Cliquer sur la route que \n vous souhaitez retirer"), 1000, 267, 20,WHITE);
                        DrawRectangle(souris1.caseX * 20 + 20, souris1.caseY * 20 + 20, 20, 20, RED);
                        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                            if (veut_construire == 4) {
                                veut_construire = 0;
                            }
                            plateau[souris1.caseY][souris1.caseX].etat = 0;
                        }
                    }
                    else if (reset_routes == false) {
                        plateau[i][j].etat = 1;
                    }
                }
                if(plateau[i][j].etat == 2){
                    //DrawRectangle(plateau[i][j].x, plateau[i][j].y, 20, 20, RED);
                }
                if(plateau[i][j].batiment == 1){
                    DrawTexture(texture3,j * 20 + 20 ,i * 20 + 20,WHITE);
                }
                else if(plateau[i][j].batiment == 7){
                    DrawTexture(texture4,j * 20 + 20 ,i * 20 + 20,WHITE);
                }
                else if(plateau[i][j].batiment == 8){
                    DrawTexture(texture5,j * 20 + 20 ,i * 20 + 20,WHITE);
                }
                else{

                }
            }
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {


            if (CheckCollisionPointRec(mouse_pos, rec_routes_reset)) {
                afficher_message_reset_routes = !afficher_message_reset_routes;
            }

            if (CheckCollisionPointRec(mouse_pos, rec_yellow)) {
                monde = 1;
            } else if (CheckCollisionPointRec(mouse_pos, rec_blue)) {
                monde = 2;
            }
        }
        if (IsKeyPressed(KEY_ENTER)) {   // peut etre le deplacé en dehors parceque faut appuyer sur la souris pour que ça marche
            monde = 0;
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
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                veut_construire = 1;
            }
        }
        if (CheckCollisionPointRec(mouse_pos, rec_construire_centrale)) {
            //DrawRectangle(0,0,50,50,RED);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                veut_construire = 2;
            }
        }
        if (CheckCollisionPointRec(mouse_pos, rec_construire_chateau_d_eau)) {
            //DrawRectangle(0,0,50,50,RED);
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                veut_construire = 3;
               }
        }
        if (CheckCollisionPointRec(mouse_pos, rec_construire_route)){
            //DrawRectangle(0,0,50,50,RED);
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                veut_construire = 4;
            }
        }
        if (veut_construire == 1 && souris1.interieurPlateau && (souris1.caseX + 2 < NB_CASE_LARGEUR && souris1.caseY + 2 < NB_CASE_HAUTEUR )){
            verificationConstructionMaison = 0;
            DrawTexture(texture3,souris1.caseX * 20 + 20,souris1.caseY * 20 + 20,WHITE);
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)  && souris1.interieurPlateau) {
                for (int i = -1; i < 4; ++i) {
                    for (int j = -1; j < 4; ++j) {
                        if ((plateau[souris1.caseY+j][souris1.caseX+i].etat != 0 && plateau[souris1.caseY+j][souris1.caseX+i].etat != 1) || (souris1.caseX+3>NB_CASE_LARGEUR || souris1.caseY+3>NB_CASE_HAUTEUR)){
                            verificationConstructionMaison++;
                        }
                    }
                }
                if(verificationConstructionMaison == 0){
                    plateau[souris1.caseY][souris1.caseX].batiment = 1;
                    for (int i = 0; i < 3; ++i) {
                        for (int j = 0; j < 3; ++j) {
                            plateau[souris1.caseY+j][souris1.caseX+i].etat = 2;
                        }
                    }
                }
            }
        }
        else if (veut_construire == 2 && souris1.interieurPlateau && (souris1.caseX + 3 < NB_CASE_LARGEUR && souris1.caseY + 5 < NB_CASE_HAUTEUR)){
            verificationConstructionCentral = 0;
            DrawTexture(texture4,souris1.caseX * 20 + 20,souris1.caseY * 20 + 20,WHITE);
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)  && souris1.interieurPlateau) {
                for (int i = -1; i < 5; ++i) {
                    for (int j = -1; j < 7; ++j) {
                        if ((plateau[souris1.caseY+j][souris1.caseX+i].etat != 0 && plateau[souris1.caseY+j][souris1.caseX+i].etat != 1) || (souris1.caseX+6>NB_CASE_LARGEUR || souris1.caseY+4>NB_CASE_HAUTEUR)){
                            verificationConstructionCentral++;
                        }
                    }
                }
                if(verificationConstructionCentral==0){
                    plateau[souris1.caseY][souris1.caseX].batiment = 7;
                    for (int i = 0; i < 4; ++i) {
                        for (int j = 0; j < 6; ++j) {
                            plateau[souris1.caseY+j][souris1.caseX+i].etat = 7;
                        }
                    }
                }
            }
        }
        else if (veut_construire == 3 && souris1.interieurPlateau && (souris1.caseX + 3 < NB_CASE_LARGEUR && souris1.caseY + 5 < NB_CASE_HAUTEUR)){
            verificationConstructionChateau = 0;
            DrawTexture(texture5,souris1.caseX * 20 + 20,souris1.caseY * 20 + 20,WHITE);
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && souris1.interieurPlateau) {
                for (int i = -1; i < 5; ++i) {
                    for (int j = -1; j < 7; ++j) {
                        if ((plateau[souris1.caseY+j][souris1.caseX+i].etat != 0 && plateau[souris1.caseY+j][souris1.caseX+i].etat != 1) || (souris1.caseX+4>NB_CASE_LARGEUR || souris1.caseY+6>NB_CASE_HAUTEUR)){
                            verificationConstructionChateau++;
                        }
                    }
                }
                if(verificationConstructionChateau == 0){
                    plateau[souris1.caseY][souris1.caseX].batiment = 8;
                    for (int i = 0; i < 4; ++i) {
                        for (int j = 0; j < 6; ++j) {
                            plateau[souris1.caseY+j][souris1.caseX+i].etat = 8;
                        }
                    }
                }
            }
        }
        else if(veut_construire == 4){
            verificationConstructionRoutes = 0;
            if(plateau[souris1.caseY][souris1.caseX].etat != 1 && plateau[souris1.caseY][souris1.caseX].etat != 0){
                verificationConstructionRoutes = 1;
            }
            if(verificationConstructionRoutes == 0 && IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                if (souris1.interieurPlateau && monde == 0) {
                    plateau[souris1.caseY][souris1.caseX].etat = 1;
                    plateau[souris1.caseY][souris1.caseX].batiment = 0;
                }
            }
        }
        else{

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

        dessinertout(timer, souris1);
        EndDrawing();
        }
    sauvegarde("../sauvgarde.txt", plateau);
}


int main() {
    mainMenu(&jouer, &quitter, &credits, &communiste, &capitaliste);

    return 0;
}