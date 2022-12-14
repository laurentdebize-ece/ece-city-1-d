#include "jeu.h"

int reset_routes;
int afficher_message_reset_routes;

int monnaie = 500000;//initialisation de la monnaie, des habitants, des impôts ainsi que des capacités en eau et électricités dont nous disposons au début de partie
int habitant = 0;
int capa_elec = 0;
int capa_eau = 0;
int impots = 10;
enum {//permet de changer de niveau
    rien = 0,
    elec = 1,
    eau = 2
} monde;
enum {//permet de savoir quelle type de construction le joueur veut construire
    nulle = 0,
    cabane = 1,
    centrale = 2,
    chateau = 3,
    route = 4
} veut_construire;

int communiste;//boutons sur lesquels le joueur peut cliquer s'il se trouve sur le menu
int capitaliste;
int jouer;
int quitter;
int quitter2;
int charger;
int credits;
float timer = 5;

int nbMaisons = 0;//comptent le nombre de maisons de centrales ou de châteaux d'eau posés sur la map
int nbCentrales = 0;
int nbChateaux = 0;
int verificationConstructionMaison = 0;//variables vérifiants si l'on peut construire sur la case du plateau sélectionnée ou non
int verificationConstructionCentral = 0;
int verificationConstructionChateau = 0;
int verificationConstructionRoutes = 0;
bool info = true;//variable concernant l'affichage des informations sur les  différents batiments
int numeroMaisonConnecteChateau = -1;
int compteurMaisonsTrouve = -1;

Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR];//initialisation du plateau ainsi que de 3 tableaux stockant les maisons, château d'eau et centrales
Central chateaux[20];
Central electricite[20];
Maison maison1[100];
souris souris1;


int reset_routes;//variables concernants la modification d'une route
int afficher_message_reset_routes;
int construire_routes;
int dessiner;

void mainJeu() {
    SetTargetFPS(20);
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
    Rectangle parametres = {1000, 700, 225, 60};
    Image ruine;//initialisations des images
    Image terrain_vague;
    Image cabane;
    Image maison;
    Image immeuble;
    Image gratte_ciel;
    Image centrale;
    Image chateau_d_eau;
    Image fond_map;
    //Music musique4 = LoadMusicStream("../Musiques/musique_plateau.mp3");

    terrain_vague = LoadImage(
            "../batiments/Terrain_Vague1.png");//on les assigne ensuite chacune à une variable et on les recupere depuis le fichier "batiments"
    centrale = LoadImage("../batiments/Centrale_electrique_2.png");
    chateau_d_eau = LoadImage("../batiments/Chateau_d_eau.png");

    ruine = LoadImage("../batiments/Ruine.png");
    cabane = LoadImage("../batiments/Cabane.png");
    maison = LoadImage("../batiments/Maison.png");
    immeuble = LoadImage("../batiments/Immeuble.png");
    gratte_ciel = LoadImage("../batiments/Gratte_ciel.png");


    Texture2D texture4 = LoadTextureFromImage(centrale);//images prêtes à être afficher
    Texture2D texture5 = LoadTextureFromImage(chateau_d_eau);
    Texture2D texture6 = LoadTextureFromImage(terrain_vague);

    Texture2D texture3 = LoadTextureFromImage(cabane);
    Texture2D texture8 = LoadTextureFromImage(maison);
    Texture2D texture9 = LoadTextureFromImage(immeuble);
    Texture2D texture10 = LoadTextureFromImage(gratte_ciel);

    //ImageResize(&terrain_vague, 60, 60);

    UnloadImage(centrale);
    UnloadImage(chateau_d_eau);
    UnloadImage(terrain_vague);


    initialiserPlateau(plateau);
    //PlayMusicStream(musique4);
    for (int i = 0; i < 100; ++i) {
        //maison1[i].fileName = "../batiments/Terrain_Vague1.png";
        maison1[i].nbHabitants = 0;
        maison1[i].evolution = 0;
    }


    for (int i = 0; i < 20; i++) {
        chateaux[i].capaciteMax = 5000;
        electricite[i].capaciteMax = 5000;
        chateaux[i].capaciteutilise = 0;
        electricite[i].capaciteutilise = 0;
        for (int j = 0; j < 20; j++) {
            chateaux[i].tabMaisonAlim[j].numMaison = -1;
            electricite[i].tabMaisonAlim[j].numMaison = -1;
        }
    }

    if (charger){
        liresauv("../sauvgarde.txt", plateau,&monnaie ,&capa_eau, &capa_elec, maison1, chateaux, electricite);
        charger = false;
    }

    while (!WindowShouldClose()) {

        //UpdateMusicStream(musique4);
        Vector2 mouse_pos = GetMousePosition();//récupération des coordonées de la souris en temps réel


        BeginDrawing();
        ClearBackground(BLACK);//fond d'écran noir

        chercherCaseDeLaSourie(GetMouseX(), GetMouseY(), &souris1.caseX, &souris1.caseY,
                               &souris1.interieurPlateau);//fonction récupérant les coordonées de la souris en temps réel
        dessinerSourieCurseur(souris1);

        resetTimer(&timer, &monnaie, habitant,
                   impots);//fonction qui réinitialise le timer à chaque cycle de vie de 15 secondes

        timer -= GetFrameTime();
        //evolutionbatiment(&maison1[100], nbMaisons, monnaie);

        dessinerBasePlateau(plateau);//fonction qui dessine le plateau


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
                            if (plateau[souris1.caseY][souris1.caseX].etat == 1) {
                                monnaie += 5;
                            }
                            plateau[souris1.caseY][souris1.caseX].etat = 0;
                        }
                    } else if (reset_routes == false) {
                        plateau[i][j].etat = 1;
                        //rechercheRouteConnecteChateaux(plateau, chateaux, 0, 0,nbChateaux); // ici
                        verificationMaisonNonViables(plateau, maison1, nbMaisons);
                        //rechercheRouteConnecteChateaux(plateau, chateaux, 0, 0, nbChateaux, maison1);
                        //rechercheRouteConnecteChateaux(plateau, chateaux, 0, 0, nbChateaux, maison1, compteurMaisonsTrouve);
                        //rechercheRouteConnecteCentral(plateau, electricite, 0, 0, nbChateaux, maison1);
                    }
                }

                if ((plateau[i][j].batiment >= 100 && monde == 0)) {
                    //DrawTexture(texture3,j * 20 + 20 ,i * 20 + 20,WHITE);
                    DrawTexture(LoadTextureFromImage(LoadImage(maison1[plateau[i][j].batiment - 100].fileName)),
                                j * 20 + 20, i * 20 + 20, WHITE);
                    //DrawTexture(texture6, j * 20 + 20, i * 20 + 20, WHITE);
                }

                for (int k = 0; k < nbMaisons; k++) {
                    if (maison1[k].vivable == 0) {
                        //DrawRectangle(maison1[k].numCaseX * 20 + 20, maison1[k].numCaseY * 20 + 20, 20, 20, BLACK);
                    }
                }
                if (plateau[i][j].etat == 77) {   // test
                    DrawRectangle(plateau[i][j].x, plateau[i][j].y, 20, 20, PURPLE);
                    //DrawRectangle(0, 0, 20, 20, YELLOW);
                }
                if (plateau[i][j].etat == 36) {   // test
                    DrawRectangle(plateau[i][j].x, plateau[i][j].y, 20, 20, YELLOW);
                }
                if (plateau[i][j].batiment == 7 && (monde == 0 || monde == 1)) {
                    DrawTexture(texture4, j * 20 + 20, i * 20 + 20, WHITE);
                    //plateau[i][j].batiment = 0;
                }
                if (plateau[i][j].batiment == 8 && (monde == 0 || monde == 2)) {
                    DrawTexture(texture5, j * 20 + 20, i * 20 + 20, WHITE);
                    //plateau[i][j].batiment = 0;
                } else {

                }
            }
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            if(CheckCollisionPointRec(mouse_pos, parametres)){
                dessiner = !dessiner;
            }
            if (CheckCollisionPointRec(mouse_pos, rec_routes_reset)) {
                afficher_message_reset_routes = !afficher_message_reset_routes;
            }
            if (CheckCollisionPointRec(mouse_pos, rec_yellow)) {
                monde = 1;
            } else if (CheckCollisionPointRec(mouse_pos, rec_blue)) {
                monde = 2;
            }
        }
        if (IsKeyPressed(KEY_ZERO) || IsKeyPressed(KEY_ENTER)) {
            monde = 0;
        }
        if (IsKeyPressed(KEY_ONE)){
            monde = 1;
        }
        if (IsKeyPressed(KEY_TWO)){
            monde = 2;
        }
        if (IsKeyDown(KEY_BACKSPACE)) {
            reset_routes = true;
        } else {
            if (reset_routes == true) {
                reset_routes = false;
            }
        }
        if (CheckCollisionPointRec(mouse_pos, rec_construire_cabane)) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                veut_construire = 1;


            }
        }
        if (CheckCollisionPointRec(mouse_pos, rec_construire_centrale)) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                veut_construire = 2;
            }
        }
        if (CheckCollisionPointRec(mouse_pos, rec_construire_chateau_d_eau)) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                veut_construire = 3;
            }
        }
        if (CheckCollisionPointRec(mouse_pos, rec_construire_route)) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                veut_construire = 4;
            }
        }

        if (veut_construire == 1 && souris1.interieurPlateau &&
            (souris1.caseX + 2 < NB_CASE_LARGEUR && souris1.caseY + 2 < NB_CASE_HAUTEUR)) {
            verificationConstructionMaison = 0;
            DrawTexture(texture6, souris1.caseX * 20 + 20, souris1.caseY * 20 + 20, WHITE);
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && souris1.interieurPlateau && monnaie >= 1000) {
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        if ((plateau[souris1.caseY + j][souris1.caseX + i].etat != 0) ||
                            (souris1.caseX + 3 > NB_CASE_LARGEUR || souris1.caseY + 3 > NB_CASE_HAUTEUR)) {
                            verificationConstructionMaison++;
                        }
                    }
                }
                if (verificationConstructionMaison == 0) {
                    plateau[souris1.caseY][souris1.caseX].batiment = 100 + nbMaisons;   // important
                    for (int i = 0; i < 3; ++i) {
                        for (int j = 0; j < 3; ++j) {
                            maison1[nbMaisons].nbHabitants = 0;
                            maison1[nbMaisons].evolution = 0;
                            plateau[souris1.caseY + j][souris1.caseX + i].etat = 2;
                        }
                    }
                    maison1[nbMaisons].numCaseX = souris1.caseX;
                    maison1[nbMaisons].numCaseY = souris1.caseY;
                    maison1[nbMaisons].vivable = verificationViable(plateau, souris1.caseX,
                                                                    souris1.caseY); //renvoie 1 si viabilité ok
                    maison1[nbMaisons].tempsDuPlacement = 0;
                    nbMaisons++;
                    //(plateau, chateaux, 0, 0, nbChateaux, maison1);
                    //rechercheRouteConnecteChateaux(plateau, chateaux, 0, 0,nbChateaux);             // ici
                    monnaie -= 1000;
                }
            }
        } else if (veut_construire == 2 && souris1.interieurPlateau &&
                   (souris1.caseX + 3 < NB_CASE_LARGEUR && souris1.caseY + 5 < NB_CASE_HAUTEUR)) {
            verificationConstructionCentral = 0;
            DrawTexture(texture4, souris1.caseX * 20 + 20, souris1.caseY * 20 + 20, WHITE);
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && souris1.interieurPlateau && monnaie >= 100000) {
                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 6; ++j) {
                        if ((plateau[souris1.caseY + j][souris1.caseX + i].etat != 0) ||
                            (souris1.caseX + 6 > NB_CASE_LARGEUR || souris1.caseY + 4 > NB_CASE_HAUTEUR)) {
                            verificationConstructionCentral++;
                        }
                    }
                }
                if (verificationConstructionCentral == 0) {
                    plateau[souris1.caseY][souris1.caseX].batiment = 7;
                    for (int i = 0; i < 4; ++i) {
                        for (int j = 0; j < 6; ++j) {
                            plateau[souris1.caseY + j][souris1.caseX + i].etat = 7;
                        }
                    }
                    electricite[nbCentrales].numCaseX = souris1.caseX;
                    electricite[nbCentrales].numCaseY = souris1.caseY;
                    capa_elec += 5000;
                    monnaie -= 100000;
                    nbCentrales++;
                }
            }
        } else if (veut_construire == 3 && souris1.interieurPlateau &&
                   (souris1.caseX + 3 < NB_CASE_LARGEUR && souris1.caseY + 5 < NB_CASE_HAUTEUR)) {
            verificationConstructionChateau = 0;
            DrawTexture(texture5, souris1.caseX * 20 + 20, souris1.caseY * 20 + 20, WHITE);
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && souris1.interieurPlateau && monnaie >= 100000) {
                for (int i = 0; i < 4; ++i) {
                    for (int j = 0; j < 6; ++j) {
                        if ((plateau[souris1.caseY + j][souris1.caseX + i].etat != 0) ||
                            (souris1.caseX + 4 > NB_CASE_LARGEUR || souris1.caseY + 6 > NB_CASE_HAUTEUR)) {
                            verificationConstructionChateau++;
                        }
                    }
                }
                if (verificationConstructionChateau == 0) {
                    plateau[souris1.caseY][souris1.caseX].batiment = 8;
                    for (int i = 0; i < 4; ++i) {
                        for (int j = 0; j < 6; ++j) {
                            plateau[souris1.caseY + j][souris1.caseX + i].etat = 8;
                        }
                    }
                    chateaux[nbChateaux].numCaseX = souris1.caseX;
                    chateaux[nbChateaux].numCaseY = souris1.caseY;
                    monnaie -= 100000;
                    capa_eau += 5000;
                    nbChateaux++;
                    //rechercheRouteConnecteChateaux(plateau, chateaux, 0, 0, nbChateaux, maison1);
                }
            }
        } else if (veut_construire == 4) {
            verificationConstructionRoutes = 0;
            if (plateau[souris1.caseY][souris1.caseX].etat != 1 && plateau[souris1.caseY][souris1.caseX].etat != 0) {
                verificationConstructionRoutes = 1;
            }
            if (verificationConstructionRoutes == 0 && IsMouseButtonDown(MOUSE_BUTTON_LEFT) && monnaie >= 10) {
                if (souris1.interieurPlateau && monde == 0) {
                    if (plateau[souris1.caseY][souris1.caseX].etat == 0) {
                        monnaie -= 10;
                    }
                    plateau[souris1.caseY][souris1.caseX].etat = 1;
                    plateau[souris1.caseY][souris1.caseX].batiment = 0;
                }
            }
        } else if (IsKeyPressed(KEY_SPACE)) {
            veut_construire = nulle;
        }

        afficherInfoBatiments(plateau, souris1, nbChateaux, nbCentrales, maison1, chateaux, electricite);

        DrawText(TextFormat("CaseX :%d", souris1.caseX), 950, 50, 20, WHITE);
        DrawText(TextFormat("CaseY :%d", souris1.caseY), 950, 70, 20, WHITE);

        if (timer <= 1) {//informe le joueur d'un nouveau cycle
            DrawText(TextFormat("Nouveau Cycle"), 180, 280, 80, GREEN);
        }

        dessinerCasesEtages(rec_yellow, rec_blue, mouse_pos);

        dessinerVariables(rec_monnaie, rec_habitant, rec_capa_elec, rec_capa_eau, mouse_pos, monnaie, habitant,
                          capa_elec, capa_eau);//dessine les rectangles initialisés plus haut

        dessinerCasesChoixConstruction(mouse_pos, rec_construire_cabane, rec_routes_reset,rec_construire_centrale, rec_construire_chateau_d_eau,rec_construire_route, dessiner, parametres);
        //dessine les rectangles initialisés plus haut

        afficherEtatMonde(monde, afficher_message_reset_routes);//fonction permettant de changer de niveau

        //rechercheRouteConnecteChateaux(plateau, chateaux, 0, 0,nbChateaux);
        miseajourtimer(maison1, nbMaisons);
        evolutionbatiment(maison1, nbMaisons, &capa_eau, &capa_elec, &habitant, plateau, chateaux, nbChateaux,
                          electricite);//fonction permettant l'évolution des maisons
        // regressionbatiment(maison1,nbMaisons,&habitant,&capa_eau,&capa_elec);
        //evolutionbatiment(maison1, nbMaisons, &capa_eau, &capa_elec, &habitant, plateau, chateaux, nbChateaux, electricite);
        //regressionbatiment(maison1,nbMaisons,&habitant,&capa_eau,&capa_elec);


        dessinertout(timer, souris1);
        EndDrawing();



    }
    sauvegarde("../sauvgarde.txt", plateau,monnaie ,capa_eau, capa_elec, maison1, chateaux, electricite);
    return;
}

int main() {
    mainMenu(&jouer, &quitter, &credits, &communiste, &capitaliste, &quitter2,
             &charger);//main concernant l'ecran de menu
    mainJeu();

    return 0;
}



