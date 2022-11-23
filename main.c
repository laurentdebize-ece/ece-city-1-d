#include "jeu.h"
int reset_routes;
int afficher_message_reset_routes;

int monnaie = 500000;
int habitant = 0;
int capa_elec = 0;
int capa_eau = 0;
int impots = 10;
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
int nbMaisons = 0;
int nbCentrales = 0;
int nbChateaux = 0;
int verificationConstructionMaison = 0;
bool veutConstruireCabane = false;
int verificationConstructionCentral = 0;
bool veutConstruireCentral = false;
int verificationConstructionChateau = 0;
bool veutConstruireChateau = false;
int verificationConstructionRoutes = 0;


Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR];
Central chateaux[20];
Central electricite[20];
Maison maison1[100];
souris souris1;



int reset_routes;
int afficher_message_reset_routes;
int construire_routes;

void rechercheChateauxEau(Case** plateau, Central* tableauChateaux){
    int nbChateauxTrouve = 0;
    for (int i = 0; i < NB_CASE_HAUTEUR; ++i) {
        for (int j = 0; j < NB_CASE_LARGEUR; ++j) {
            if(plateau[i][j].batiment == 8){
                tableauChateaux[nbChateauxTrouve].numCaseX = j;
                tableauChateaux[nbChateauxTrouve].numCaseY = i;
                tableauChateaux[nbChateauxTrouve].capaciteMax;
            }
        }
    }
}

void rechercheMaison(int* numMaison, Maison maison[100], int x, int y, int nbMaisons) {
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++){
            if(plateau[y+i][x+j].etat == 2 && plateau[y+i][x+j].batiment >=100){
                plateau[y+i][x+j].etat = 34;
                *numMaison = plateau[y+i][x+j].batiment - 100;
                return;
            }
            if(plateau[y+i][x+j].etat == 2 && plateau[y+i][x+j].batiment <100){
                plateau[y+i][x+j].etat = 33;
                rechercheMaison(numMaison, maison, x+j, y+j, nbMaisons);
            }
        }
    }
}


void analyseChateauxEau(Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR], Central chateaux, int x, int y, Maison maisons[100]){
    int numMaisonTrouve;
    int test;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (plateau[y+i][x+j].etat == 1){
                plateau[y+i][x+j].etat = 22;
                analyseChateauxEau(plateau, chateaux,x+j, y+i, maisons);
            }
            if (plateau[y+i][x+j].etat == 2){
                rechercheMaison(&numMaisonTrouve, maisons, x+j, y+i, nbMaisons);
                //plateau[maisons[numMaisonTrouve].numCaseY][maisons[numMaisonTrouve].numCaseX].etat = 33;
                //chateaux.capaciteutilise += maison[numMaisonTrouve].eauNecessaire;
            }
        }
    }
}

void rechercheRouteConnecteChateaux(Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR], Central chateaux[20],int x, int y, int nbChateauEau, Maison maisons[100]){
    int compteur;
    for (int nb = 0; nb < nbChateauEau; nb++) {
        x = chateaux[nb].numCaseX;
        y = chateaux[nb].numCaseY;
        compteur = 0;
        for (int i = - 1; i < 5; i++) {
            for (int j = -1; j < 7; j++) {
                compteur++;
                if (plateau[j+y][i+x].etat == 1 && (compteur != 1 && compteur!= 8 && compteur != 41 && compteur!= 48)){
                    //DrawRectangle((i+x)*20 + 20, (j+y)*20 + 20, 20, 20, BLUE);
                    analyseChateauxEau(plateau, chateaux[nbChateauEau], x+i, y+j, maisons);
                    //nbChateauEau++;
                }
            }
        }
    }
    for (int i = 0; i < NB_CASE_HAUTEUR; i++) {
        for (int j = 0; j < NB_CASE_LARGEUR; j++){
            if(plateau[i][j].etat == 22){
                plateau[i][j].etat = 1;
            }
            if(plateau[i][j].etat == 33){
                //plateau[i][j].etat = 2;
            }
        }
    }
}




void mainJeu() {
    SetTargetFPS(60);
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
    Rectangle aire_de_jeu = {20, 20, 45 * 20, 35 * 20};

    Image ruine;
    Image terrain_vague;
    Image cabane;
    Image maison;
    Image immeuble;
    Image gratte_ciel;
    Image centrale;
    Image chateau_d_eau;
    Image fond_map;

    ruine = LoadImage("../batiments/Ruine.png");
    terrain_vague = LoadImage("../batiments/Terrain_Vague1.png");
    cabane = LoadImage("../batiments/Cabane.png");
    maison = LoadImage("../batiments/Maison.png");
    immeuble = LoadImage("../batiments/Immeuble.png");
    gratte_ciel = LoadImage("../batiments/Gratte_ciel.png");
    centrale = LoadImage("../batiments/Centrale_electrique_2.png");
    chateau_d_eau = LoadImage("../batiments/Chateau_d_eau.png");
    fond_map = LoadImage("../batiments/fond_map.png");

    Texture2D texture3 = LoadTextureFromImage(cabane);
    Texture2D texture4 = LoadTextureFromImage(centrale);
    Texture2D texture5 = LoadTextureFromImage(chateau_d_eau);
    Texture2D texture6 = LoadTextureFromImage(terrain_vague);
    Texture2D texture7 = LoadTextureFromImage(fond_map);
    Texture2D texture8 = LoadTextureFromImage(ruine);
    Texture2D texture9 = LoadTextureFromImage(maison);
    Texture2D texture10 = LoadTextureFromImage(immeuble);
    Texture2D texture11 = LoadTextureFromImage(gratte_ciel);
    //ImageResize(&terrain_vague, 60, 60);


    UnloadImage(cabane);
    UnloadImage(centrale);
    UnloadImage(chateau_d_eau);
    UnloadImage(terrain_vague);
    UnloadImage(ruine);
    UnloadImage(maison);
    UnloadImage(immeuble);
    UnloadImage(gratte_ciel);


    initialiserPlateau(plateau);

    for (int i = 0; i < 100; ++i) {
        maison1[i].fileName = "../batiments/Terrain_Vague1.png";
        maison1[i].nbHabitants = -1;
        maison1[i].evolution = -1;
    }
    //liresauv("../sauvgarde.txt", plateau);


    while (!WindowShouldClose()) {


        Vector2 mouse_pos = GetMousePosition();




        BeginDrawing();
        ClearBackground(BLACK);

        chercherCaseDeLaSourie(GetMouseX(), GetMouseY(), &souris1.caseX, &souris1.caseY, &souris1.interieurPlateau);
        dessinerSourieCurseur(souris1);

        resetTimer(&timer, &monnaie, habitant, impots);

        timer -= GetFrameTime();
        //evolutionbatiment(&maison1[100], nbMaisons, monnaie);

        dessinerBasePlateau(plateau);

        for (int i = 0; i < 100; ++i) {
            switch (maison1[i].evolution) {
                case 0 : {
                    maison1[i].fileName = "../batiments/Terrain_Vague1.png";
                    break;
                }
                case 1 : {
                    maison1[i].fileName = "../batiments/Cabane.png";
                    break;
                }
                case 2 : {
                    maison1[i].fileName = "../batiments/Maison.png";
                    break;
                }
                case 3 : {
                    maison1[i].fileName = "../batiments/Immeuble.png";
                    break;
                }
                case 4 : {
                    maison1[i].fileName = "../batiments/Gratte_ciel.png";
                    break;
                }

            }
        }

        for (int i = 0; i < 35; i++) {
            for (int j = 0; j < 45; j++) {

                if (plateau[i][j].etat == 1) {
                    DrawRectangle(plateau[i][j].x, plateau[i][j].y, 20, 20,
                                  monde == 2 ? BLUE : monde == 1 ? YELLOW : GRAY);
                    DrawRectangleLines(plateau[i][j].x, plateau[i][j].y, 20, 20, BLACK); // creation des routes
                    if (reset_routes == true && monde == 0 && plateau[souris1.caseY][souris1.caseX].etat != 2 &&
                        plateau[souris1.caseY][souris1.caseX].etat != 7 &&
                        plateau[souris1.caseY][souris1.caseX].etat != 8) {
                        DrawText(TextFormat("Cliquer sur la route que \n vous souhaitez retirer"), 1000, 267, 20,
                                 WHITE);
                        DrawRectangle(souris1.caseX * 20 + 20, souris1.caseY * 20 + 20, 20, 20, RED);
                        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                            if (veut_construire == 4) {
                                veut_construire = 0;
                            }
                            plateau[souris1.caseY][souris1.caseX].etat = 0;
                        }
                    } else if (reset_routes == false) {
                        plateau[i][j].etat = 1;
                        //rechercheRouteConnecteChateaux(plateau, chateaux, 0, 0,nbChateaux); // ici
                        verificationMaisonNonViables(plateau, maison1, nbMaisons);
                        rechercheRouteConnecteChateaux(plateau,chateaux, 0, 0, nbChateaux, maison1);

                    }
                }

                if ((plateau[i][j].batiment >= 100 && monde == 0)) {
                    //DrawTexture(texture3,j * 20 + 20 ,i * 20 + 20,WHITE);
                    DrawTexture(LoadTextureFromImage(LoadImage(maison1[plateau[i][j].batiment - 100].fileName)),
                                j * 20 + 20, i * 20 + 20, WHITE);
                }
                for (int k = 0; k < nbMaisons; k++) {
                    if(maison1[k].vivable==0){
                        DrawRectangle(maison1[k].numCaseX*20 + 20, maison1[k].numCaseY*20 + 20, 20,20, BLACK);
                    }
                }
                if(plateau[i][j].etat == 33){   // test
                    //DrawRectangle(plateau[i][j].x, plateau[i][j].y, 20, 20, PURPLE);
                    //DrawRectangle(0, 0, 20, 20, YELLOW);
                }
                if(plateau[i][j].etat == 34){   // test
                    DrawRectangle(plateau[i][j].x, plateau[i][j].y, 20, 20, YELLOW);
                }
                    if (plateau[i][j].batiment == 7 && (monde == 0 || monde == 1)) {
                        DrawTexture(texture4, j * 20 + 20, i * 20 + 20, WHITE);
                    }
                    if (plateau[i][j].batiment == 8 && (monde == 0 || monde == 2)) {
                        DrawTexture(texture5, j * 20 + 20, i * 20 + 20, WHITE);
                    } else {

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
        if (IsKeyPressed(KEY_ENTER)) {
            monde = 0;
            maison1[0].evolution++; // ligne test
        }
        if (IsKeyDown(KEY_BACKSPACE)) {
            reset_routes = true;
            maison1[0].evolution--; // ligne test
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
            DrawTexture(texture6,souris1.caseX * 20 + 20,souris1.caseY * 20 + 20,WHITE);
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)  && souris1.interieurPlateau && monnaie >= 1000) {
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        if ((plateau[souris1.caseY+j][souris1.caseX+i].etat != 0) || (souris1.caseX+3>NB_CASE_LARGEUR || souris1.caseY+3>NB_CASE_HAUTEUR)){
                            verificationConstructionMaison++;
                        }
                    }
                }
                if(verificationConstructionMaison == 0){
                    plateau[souris1.caseY][souris1.caseX].batiment = 100 + nbMaisons;   // important
                    for (int i = 0; i < 3; ++i) {
                        for (int j = 0; j < 3; ++j) {
                            maison1[nbMaisons].nbHabitants = 0;
                            maison1[nbMaisons].evolution = 0;
                            plateau[souris1.caseY+j][souris1.caseX+i].etat = 2;
                        }
                    }
                    maison1[nbMaisons].numCaseX = souris1.caseX;
                    maison1[nbMaisons].numCaseY = souris1.caseY;
                    maison1[nbMaisons].vivable = verificationViable(plateau, souris1.caseX ,souris1.caseY); //renvoie 1 si viabilité ok
                    maison1[nbMaisons].tempsDuPlacement = 0;
                    nbMaisons++;
                    //rechercheRouteConnecteChateaux(plateau, chateaux, 0, 0,nbChateaux);             // ici
                    monnaie -= 1000;
                    habitant += 10;



                }
            }
        }

        else if (veut_construire == 2 && souris1.interieurPlateau && (souris1.caseX + 3 < NB_CASE_LARGEUR && souris1.caseY + 5 < NB_CASE_HAUTEUR)){
            verificationConstructionCentral = 0;
            DrawTexture(texture4,souris1.caseX * 20 + 20,souris1.caseY * 20 + 20,WHITE);
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)  && souris1.interieurPlateau && monnaie >= 100000) {
                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 6; ++j) {
                        if ((plateau[souris1.caseY+j][souris1.caseX+i].etat != 0) || (souris1.caseX+6>NB_CASE_LARGEUR || souris1.caseY+4>NB_CASE_HAUTEUR)){
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
                    capa_elec += 5000;
                    monnaie -= 100000;
                    nbCentrales++;
                }
            }
        }
        else if (veut_construire == 3 && souris1.interieurPlateau && (souris1.caseX + 3 < NB_CASE_LARGEUR && souris1.caseY + 5 < NB_CASE_HAUTEUR)){
            verificationConstructionChateau = 0;
            DrawTexture(texture5,souris1.caseX * 20 + 20,souris1.caseY * 20 + 20,WHITE);
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && souris1.interieurPlateau && monnaie >= 100000) {
                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 6; ++j) {
                        if ((plateau[souris1.caseY+j][souris1.caseX+i].etat != 0) || (souris1.caseX+4>NB_CASE_LARGEUR || souris1.caseY+6>NB_CASE_HAUTEUR)){
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
                    chateaux[nbChateaux].numCaseX = souris1.caseX;
                    chateaux[nbChateaux].numCaseY = souris1.caseY;
                    monnaie -= 100000;
                    capa_eau += 5000;
                    nbChateaux++;
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
        else if(IsKeyPressed(KEY_SPACE)){
            veut_construire = nulle;
        }

            DrawText(TextFormat("CaseX :%d", souris1.caseX), 950, 50, 20, WHITE);
            DrawText(TextFormat("CaseY :%d", souris1.caseY), 950, 70, 20, WHITE);

            if (timer <= 1) {
                DrawText(TextFormat("Nouveau Cycle"), 180, 280, 80, GREEN);
            }

            dessinerCasesEtages(rec_yellow, rec_blue, mouse_pos);

            dessinerVariables(rec_monnaie, rec_habitant, rec_capa_elec, rec_capa_eau, mouse_pos, monnaie, habitant,
                              capa_elec, capa_eau);


            dessinerCasesChoixConstruction(mouse_pos, rec_construire_cabane, rec_routes_reset,
                                           rec_construire_centrale, rec_construire_chateau_d_eau,
                                           rec_construire_route);


            afficherEtatMonde(monde, afficher_message_reset_routes);


            //rechercheRouteConnecteChateaux(plateau, chateaux, 0, 0,nbChateaux);

        for(int i = 0 ; i < nbMaisons ; i ++) {
            if(maison1[i].vivable) {
                maison1[i].tempsDuPlacement += GetFrameTime();
                if (maison1[i].tempsDuPlacement >= 15){
                    maison1[i].tempsDuPlacement = 0;
                    maison1[i].evolution++;
                }


            }
        }

        DrawText(TextFormat("%.0f", maison1[0].tempsDuPlacement), 1000, 650, 30, WHITE);
        DrawText(TextFormat("%.0f", maison1[1].tempsDuPlacement), 1100, 650, 30, WHITE);
        dessinertout(timer, souris1);
        EndDrawing();
    }
    sauvegarde("../sauvgarde.txt", plateau);
}
int main() {
    mainMenu(&jouer, &quitter, &credits, &communiste, &capitaliste);

    return 0;
}

