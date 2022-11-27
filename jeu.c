#include "jeu.h"


int mainMenu(int *jouer, int *quitter, int *credits, int *communiste, int *capitaliste, int *quitter2, int *charger) {//page du menu
    Image menu;//récupération des images
    Image mode;
    Image credit;
    InitWindow(1024, 768, "ECE city");//Création de la fenetre
    InitAudioDevice();
    //Music musique1 = LoadMusicStream("../Musiques/the-simpsons-theme-song.mp3");
    //Music musique2 = LoadMusicStream("../Musiques/URSS.mp3");
    //Music musique3 = LoadMusicStream("../Musiques/usa.mp3");
    SetWindowPosition(50, 50);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    //PlayMusicStream(musique1);
    SetTargetFPS(60);
    MaximizeWindow();
    menu = LoadImage("../menu/menu2.png");//chargement des images
    mode = LoadImage("../menu/mode.png");
    credit = LoadImage("../menu/credits.png");
    ImageDrawPixel(&menu, 0, 0, RAYWHITE);
    ImageResize(&menu, 1920, 1000);
    Texture2D texture = LoadTextureFromImage(menu);
    ImageDrawPixel(&mode, 0, 0, RAYWHITE);
    ImageResize(&mode, 1920, 1000);
    Texture2D texture2 = LoadTextureFromImage(mode);
    ImageDrawPixel(&credit, 0, 0, RAYWHITE);
    ImageResize(&credit, 1920, 1000);
    Texture2D texture3 = LoadTextureFromImage(credit);
    UnloadImage(mode);
    UnloadImage(menu);
    UnloadImage(credit);
    while (!WindowShouldClose()) {
        //UpdateMusicStream(musique1);
        Vector2 mouse_pos = GetMousePosition();
        BeginDrawing();
        DrawTexture(texture, 0, 0, WHITE);
        Rectangle rec_CREDIT = {748, 108, 238, 92};//initialisation des rectangle servants comme boutons
        Rectangle rec_JOUER = {1038, 108, 238, 92};
        Rectangle rec_QUITTER = {1328, 108, 238, 92};
        Rectangle rec_SAUVEGARDE = {9, 30, 245, 99};
        DrawRectangleLinesEx(rec_SAUVEGARDE, 4, CheckCollisionPointRec(mouse_pos, rec_SAUVEGARDE) ? SKYBLUE : GREEN);//desssin des rectangle qui s'allument si on passe la souris dessus
        DrawRectangleLinesEx(rec_CREDIT, 4, CheckCollisionPointRec(mouse_pos, rec_CREDIT) ? SKYBLUE : GREEN);
        DrawRectangleLinesEx(rec_JOUER, 4, CheckCollisionPointRec(mouse_pos, rec_JOUER) ? SKYBLUE : GREEN);
        DrawRectangleLinesEx(rec_QUITTER, 4, CheckCollisionPointRec(mouse_pos, rec_QUITTER) ? SKYBLUE : GREEN);

        if (CheckCollisionPointRec(mouse_pos, rec_JOUER) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {//si on clique sur jouer on ne charge pas une ancienne partie mais on en lance une nouvelle
            *charger = false;
            *jouer = true;

        }
        if (CheckCollisionPointRec(mouse_pos, rec_QUITTER) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {//si on clique sur quitter, c'est la fin de la partie
            *quitter = true;
        }
        if (CheckCollisionPointRec(mouse_pos, rec_CREDIT) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {//si on clique sur credits, les credits apparaissent
            *credits = true;
        }
        if (CheckCollisionPointRec(mouse_pos, rec_SAUVEGARDE) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {//si on clique sur charger on charge la derniere partie
            *charger = true;
            *jouer = true;
        }
        if (*quitter == true) {//si on clique sur quitter la fenetre se ferme
            CloseWindow();
        }
        if (*jouer == true) {//quand on lance une partie, on a le choix entre le mode communiste et capitaliste sur une nouvelle page
            DrawTexture(texture2, 0, 0, WHITE);
            Rectangle rec_COMMUNISTE = {95, 235, 620, 150};
            Rectangle rec_CAPITALISTE = {95, 585, 620, 150};
            DrawRectangleLinesEx(rec_COMMUNISTE, 4, CheckCollisionPointRec(mouse_pos, rec_CREDIT) ? SKYBLUE : WHITE);
            DrawRectangleLinesEx(rec_CAPITALISTE, 4, CheckCollisionPointRec(mouse_pos, rec_JOUER) ? SKYBLUE : WHITE);
            if (CheckCollisionPointRec(mouse_pos, rec_COMMUNISTE)){//selon le rectangle au dessus du quel se trouve la souris, on lance une musique differente
                //PauseMusicStream(musique1);
                //UpdateMusicStream(musique1);
                //PlayMusicStream(musique2);
                //UpdateMusicStream(musique2);
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {//si on clique sur un des boutons, la partie se lance dans le mode choisi
                    *communiste = true;
                    mainJeu();
                }
            }
            else if (CheckCollisionPointRec(mouse_pos, rec_CAPITALISTE) ){
                //PauseMusicStream(musique1);
                //UpdateMusicStream(musique1);
                //PlayMusicStream(musique3);
                //UpdateMusicStream(musique3);
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        *capitaliste = true;
                    mainJeu();
                }
            }
            else {
                //StopMusicStream(musique2);
                //StopMusicStream(musique3);
                //UpdateMusicStream(musique2);
                //UpdateMusicStream(musique3);
                //ResumeMusicStream(musique1);
                //UpdateMusicStream(musique1);
            }
        }
        if (*credits == true) {//affichage de la page des credits
            DrawTexture(texture3, 0, 0, WHITE);
            Rectangle rec_QUITTER2 = {57, 50, 130, 40};
            DrawRectangleLinesEx(rec_QUITTER2, 4, CheckCollisionPointRec(mouse_pos, rec_QUITTER) ? SKYBLUE : WHITE);
            if (CheckCollisionPointRec(mouse_pos, rec_QUITTER2) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                *quitter2 = true;

            }
        }
        if (*quitter2 == true) {
            DrawTexture(texture, 0, 0, WHITE);
            Rectangle rec_CREDIT = {748, 108, 238, 92};
            Rectangle rec_JOUER = {1038, 108, 238, 92};
            Rectangle rec_QUITTER = {1328, 108, 238, 92};
            DrawRectangleLinesEx(rec_CREDIT, 4, CheckCollisionPointRec(mouse_pos, rec_CREDIT) ? SKYBLUE : GREEN);
            DrawRectangleLinesEx(rec_JOUER, 4, CheckCollisionPointRec(mouse_pos, rec_JOUER) ? SKYBLUE : GREEN);
            DrawRectangleLinesEx(rec_QUITTER, 4, CheckCollisionPointRec(mouse_pos, rec_QUITTER) ? SKYBLUE : GREEN);
            if (CheckCollisionPointRec(mouse_pos, rec_JOUER) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                *jouer = true;
                *charger = false;
            }
            if (CheckCollisionPointRec(mouse_pos, rec_QUITTER) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                *quitter = true;

            }
            if (CheckCollisionPointRec(mouse_pos, rec_CREDIT) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                *credits = true;
            }

            if (*quitter == true) {
                CloseWindow();
            }
            if (*jouer == true) {
                DrawTexture(texture2, 0, 0, WHITE);
                Rectangle rec_COMMUNISTE = {95, 235, 620, 150};
                Rectangle rec_CAPITALISTE = {95, 585, 620, 150};
                DrawRectangleLinesEx(rec_COMMUNISTE, 4,
                                     CheckCollisionPointRec(mouse_pos, rec_CREDIT) ? SKYBLUE : WHITE);
                DrawRectangleLinesEx(rec_CAPITALISTE, 4,
                                     CheckCollisionPointRec(mouse_pos, rec_JOUER) ? SKYBLUE : WHITE);
                if (CheckCollisionPointRec(mouse_pos, rec_COMMUNISTE) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    *communiste = true;
                    mainJeu();
                } else if (CheckCollisionPointRec(mouse_pos, rec_CAPITALISTE) &&
                           IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    *capitaliste = true;
                    mainJeu();
                }
            }
        }

        EndDrawing();

    }

    UnloadTexture(texture);
    UnloadTexture(texture2);
    UnloadTexture(texture3);

    CloseWindow();
    return 0;
}


void liresauv(char *nomFichier, Case tab[NB_CASE_HAUTEUR][NB_CASE_LARGEUR], int* argent, int* eau, int* elec, Maison maison1[100], Central chateaux[20], Central electricite[20]) {
    FILE *ifs = fopen(nomFichier, "r");
    fscanf(ifs, "%d", argent);
    fscanf(ifs, "%d", eau);
    fscanf(ifs, "%d", elec);


    for (int i = 0; i < NB_CASE_HAUTEUR; ++i) {
        for (int j = 0; j < NB_CASE_LARGEUR; ++j) {
            fscanf(ifs, "%d", &tab[i][j].etat);
            fscanf(ifs, "%d", &tab[i][j].batiment);
        }
    }
    printf("Fin fonction sauvegarde\n");

    fclose(ifs);
}

void sauvegarde(char *nomFichier, Case tab[NB_CASE_HAUTEUR][NB_CASE_LARGEUR], int argent, int eau, int elec, Maison maison1[100], Central chateaux[20], Central electricite[20]) {
    FILE *ifs = fopen(nomFichier, "w");
    fprintf(ifs, "%d", argent);
    fprintf(ifs, "\n");
    fprintf(ifs, "%d", eau);
    fprintf(ifs, "\n");
    fprintf(ifs, "%d", elec);
    fprintf(ifs, "\n");

    for (int i = 0; i < NB_CASE_HAUTEUR; ++i) {
        for (int j = 0; j < NB_CASE_LARGEUR; ++j) {
            fprintf(ifs, "%d ", (tab[i][j].etat));
            fprintf(ifs, "%d ", (tab[i][j].batiment));
            if (tab[i][j].batiment >= 100){
                fprintf(ifs, "%s", maison1[tab[i][j].batiment - 100].fileName = "../batiments/Terrain_Vague1.png");
            }
            fprintf(ifs, "\n");
        }
    }
    printf("Fin fonction sauvegarde\n");

    fclose(ifs);
}

void resetTimer(float *timer, int *monnaie, int habitant, int impots) {
    if (*timer <= 0) {//quand le timer arrive a 0, on le remet a 15 car un cycle dure 15 secondes
        *timer = 15;
        *monnaie += habitant * (impots);//comme c une fin de cycle, on prélève les impots
    }
}

void chercherCaseDeLaSourie(int x, int y, int *caseX, int *caseY, bool *dansPlateau) {
    if ((x >= 20 && x <= 920) && (y >= 20 && y <= 720)) {//selon les coordonées de la souris, on sait si on est dans la plateau ou non
        *dansPlateau = true;
    } else {
        *dansPlateau = false;
    }
    // ne pas oublie de bien commencer à l'origine du tableau
    int a = 0;
    for (int i = 0; i < NB_CASE_HAUTEUR; i++) {
        for (int j = 0; j < NB_CASE_LARGEUR; j++) {
            if (((x - 20) >= j * LARGEUR_CASE && (x - 20) <= (j + 1) * LARGEUR_CASE) &&
                ((y - 20) >= i * LARGEUR_CASE && (y - 20) < (i + 1) * LARGEUR_CASE)) {
                *caseX = j;
                *caseY = i;
            } else {
                a++;
            }
        }
    }
    if (a == NB_CASE_LARGEUR * NB_CASE_HAUTEUR) {
        *caseX = 0;
        *caseY = 0;
    }

}

void initialiserPlateau(Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR]) {
    for (int i = 0; i < NB_CASE_HAUTEUR; i++) {//a chaque case on donne une longueur et une largeur
        for (int j = 0; j < NB_CASE_LARGEUR; j++) {
            plateau[i][j].largeur = LARGEUR_CASE;
            plateau[i][j].etat = 0;
            plateau[i][j].etatInterdit = 0;
            if (i == 0 && j == 0) {
                plateau[i][j].x = 20;
                plateau[i][j].y = 20;
            } else if (i == 0) {
                plateau[i][j].x = plateau[i][j - 1].x + LARGEUR_CASE;
                plateau[i][j].y = plateau[i][j - 1].y;
            } else {
                plateau[i][j].x = plateau[i - 1][j].x;
                plateau[i][j].y = plateau[i - 1][j].y + LARGEUR_CASE;
            }
            plateau[i][j].verification = 0;
        }
    }
}

void dessinerSourieCurseur(souris souris1) {
    if (souris1.interieurPlateau)
        DrawRectangle(souris1.caseX * 20 + 20, souris1.caseY * 20 + 20, 20, 20, RED);//un carré rouge allume la case sur laquelle la souris se trouve si elle est dans le plateau
}

void dessinerBasePlateau(Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR]) {
    Image terrain_vague;//on recupere l'image qui servira de fond pour le plateau
    terrain_vague = LoadImage("../batiments/fond_map.png");
    ImageResize(&terrain_vague, 20, 20);
    Texture2D texture6 = LoadTextureFromImage(terrain_vague);
    for (int i = 0; i < 35; i++) {//pour chaque case du plateau on incruste cette image et on dessine un carré noir autour histoire de distainguer les différentes cases
        for (int j = 0; j < 45; j++) {
            if (plateau[i][j].etat == 0) {
                DrawTexture(texture6, plateau[i][j].x, plateau[i][j].y, WHITE);
                //DrawRectangle(plateau[i][j].x, plateau[i][j].y, 20,20,GREEN);
                DrawRectangleLines(plateau[i][j].x, plateau[i][j].y, 20, 20, BLACK);
            }
        }
    }
}

void dessinerCasesEtages(Rectangle rec_yellow, Rectangle rec_blue, Vector2 mouse_pos) {//on dessine des rectangles pour les boutons concernant les niveau
    DrawRectangleLinesEx(rec_yellow, 6, CheckCollisionPointRec(mouse_pos, rec_yellow) ? ORANGE : YELLOW);
    DrawRectangleLinesEx(rec_blue, 6, CheckCollisionPointRec(mouse_pos, rec_blue) ? SKYBLUE : BLUE);
    DrawText(TextFormat("Etage elec"), 1020, 117, 25, CheckCollisionPointRec(mouse_pos, rec_yellow) ? ORANGE : YELLOW);
    DrawText(TextFormat("Etage eau"), 1020, 187, 25, CheckCollisionPointRec(mouse_pos, rec_blue) ? SKYBLUE : BLUE);
}

void dessinerVariables(Rectangle rec_monnaie, Rectangle rec_habitant, Rectangle rec_capa_elec, Rectangle rec_capa_eau,
                       Vector2 mouse_pos, int monnaie, int habitant, int capa_elec, int capa_eau) {//même chose pour les compteurs en haut a droite de l'écran
    DrawRectangleLinesEx(rec_monnaie, 4, CheckCollisionPointRec(mouse_pos, rec_monnaie) ? YELLOW : GOLD);
    DrawRectangleLinesEx(rec_habitant, 4, CheckCollisionPointRec(mouse_pos, rec_habitant) ? GREEN : LIME);
    DrawText(TextFormat("%d ECE Flouz", monnaie), 1670, 20, 20,
             CheckCollisionPointRec(mouse_pos, rec_monnaie) ? YELLOW : GOLD);
    DrawText(TextFormat("%d habitants", habitant), 1710, 60, 20,
             CheckCollisionPointRec(mouse_pos, rec_habitant) ? GREEN : LIME);

    DrawRectangleLinesEx(rec_capa_elec, 4, CheckCollisionPointRec(mouse_pos, rec_capa_elec) ? ORANGE : YELLOW);
    DrawRectangleLinesEx(rec_capa_eau, 4, CheckCollisionPointRec(mouse_pos, rec_capa_eau) ? SKYBLUE : BLUE);
    DrawText(TextFormat("Capacite en electricite : %d", capa_elec), 1560, 100, 20,
             CheckCollisionPointRec(mouse_pos, rec_capa_elec) ? ORANGE : YELLOW);
    DrawText(TextFormat("Capacite en eau : %d", capa_eau), 1630, 140, 20,
             CheckCollisionPointRec(mouse_pos, rec_capa_eau) ? SKYBLUE : BLUE);
}

void dessinerCasesChoixConstruction(Vector2 mouse_pos, Rectangle rec_construire_cabane, Rectangle rec_routes_reset,Rectangle rec_construire_centrale, Rectangle rec_construire_chateau_d_eau,Rectangle rec_construire_route, int dessiner, Rectangle parametres) {
    DrawRectangleLinesEx(parametres, 6, CheckCollisionPointRec(mouse_pos, parametres) ? LIGHTGRAY : WHITE);//même chose pour les cases de constructions de batiments et de routes
    DrawText("boite a outils", 1015, 718, 30, CheckCollisionPointRec(mouse_pos, parametres) ? LIGHTGRAY : WHITE);
    if(dessiner){
        DrawRectangleLinesEx(rec_construire_cabane, 5,CheckCollisionPointRec(mouse_pos, rec_construire_cabane) ? RED : BROWN);
        DrawText(TextFormat("Cabane"), 30, 920, 50, CheckCollisionPointRec(mouse_pos, rec_construire_cabane) ? RED : BROWN);

        DrawRectangleLinesEx(rec_routes_reset, 6, CheckCollisionPointRec(mouse_pos, rec_routes_reset) ? LIGHTGRAY : GRAY);
        DrawText(TextFormat("reset route"), 1020, 387, 25,CheckCollisionPointRec(mouse_pos, rec_routes_reset) ? LIGHTGRAY : GRAY);

        DrawRectangleLinesEx(rec_construire_centrale, 5,CheckCollisionPointRec(mouse_pos, rec_construire_centrale) ? ORANGE : YELLOW);
        DrawText(TextFormat("Electricite"), 240, 920, 50,CheckCollisionPointRec(mouse_pos, rec_construire_centrale) ? ORANGE : YELLOW);

        DrawRectangleLinesEx(rec_construire_chateau_d_eau, 5,CheckCollisionPointRec(mouse_pos, rec_construire_chateau_d_eau) ? SKYBLUE : BLUE);
        DrawText(TextFormat("Eau"), 535, 920, 50,CheckCollisionPointRec(mouse_pos, rec_construire_chateau_d_eau) ? SKYBLUE : BLUE);

        DrawRectangleLinesEx(rec_construire_route, 5,CheckCollisionPointRec(mouse_pos, rec_construire_route) ? LIGHTGRAY : GRAY);
        DrawText(TextFormat("Routes"), 655, 920, 50,CheckCollisionPointRec(mouse_pos, rec_construire_route) ? LIGHTGRAY : GRAY);
    }
}

void afficherEtatMonde(int monde, int afficher_message_reset_routes) {
    if (monde != 0) {//selon le niveau dans lequel on se trouve, on affiche des informations pour une meilleure comprehension du joueur
        DrawText(TextFormat("Si vous voulez retourner \nau routes veuillez appuyer \nsur 'ENTER' et '0'"), 1000, 327,
                 10, WHITE);
    }
    if (monde == 1) {
        DrawText(TextFormat("Etage 1, elec"), 1000, 267, 50, YELLOW);
    } else if (monde == 2) {
        DrawText(TextFormat("Etage 2, eau"), 1000, 267, 50, BLUE);
    }
    if (afficher_message_reset_routes) {//pareil si l'on souhaite enlever des routes
        DrawText(TextFormat(
                         "Appuyez sur 'BACKSPACE' \net suivez les instructions \n(verifiez d'avoir des routes)"), 1000,
                 460, 20, WHITE);
    }
}


void dessinertout(float timer, souris souris1) {
    DrawText(TextFormat("timer: %.0f", timer), 840, 0, 20, WHITE);// on dessine le timer en au dessus du plateau qui nous informe du temps restant avant un nouveau cycle
    dessinerSourieCurseur(souris1);
}

void initialiserbatiment(Maison batiment) {

    Image ruine;//on récupère, charge et assigne des variables pour chaque image qui servent à l'affichage des constructions
    Image terrain_vague;
    Image cabane;
    Image maison;
    Image immeuble;
    Image gratte_ciel;
    Image centrale;
    Image chateau_d_eau;

    ruine = LoadImage("../batiments/Ruine.png");
    terrain_vague = LoadImage("../batiments/Terrain_Vague1.png");
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


}
//Centrale : 100 000 ECE-flouz
//- Château d’eau : 100 000 ECE-flouz
//- Route : 10 ECE-flouz par unité de grille

void miseajourtimer(Maison maison1[100], int nbMaisons) {
    for (int i = 0; i < nbMaisons; i++) {
        if (maison1[i].vivable){//si une maison est viable, on lance un timer comptant le temps depuis lequel cette maison est viable ce qui sert pour les évolutions
            maison1[i].tempsDuPlacement += GetFrameTime();
        }
        if (maison1[i].eau < maison1[i].eauNecessaire || maison1[i].electricite < maison1[i].electriciteNecessaire){
            maison1[i].tempsDuPlacement -= GetFrameTime();
        }
    }
}

void evolutionbatiment(Maison maison1[100], int nbMaisons, int *capa_eau, int *capa_elec, int *habitant,
                       Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR], Central chateaux[20], int nbChateaux, Central electricite[20]) {
    for (int i = 0; i < nbMaisons; i++) {
        /*if (maison1[i].tempsDuPlacement > 15) { // Terrain vague : 1000 ECE-flouz
            maison1[i].evolution++;
            maison1[i].tempsDuPlacement = 0;

        }*/
        if (maison1[i].tempsDuPlacement < 15) { // pour chaque niveau d'évolution, on vérifie si le temps de placement et les ressources nécessaires sont suffisantes
            maison1[i].evolution = 0;
            maison1[i].fileName = "../batiments/Terrain_Vague1.png";// on change ensuite d'image et on met à jour les informations sur le batiment
            maison1[i].nbHabitants = 0;
            maison1[i].electriciteNecessaire = 0;//ressources nécessaires pour évoluer au niveau supérieur
            maison1[i].eauNecessaire = 0;
        }
        if (maison1[i].tempsDuPlacement >= 15 && maison1[i].evolution == 0 && maison1[i].eau >= maison1[i].eauNecessaire) {
            maison1[i].evolution = 1;
            maison1[i].fileName = "../batiments/Cabane.png";
            maison1[i].nbHabitants = 10;
            maison1[i].electriciteNecessaire = 10;
            maison1[i].eauNecessaire = 10;
            rechercheRouteConnecteChateaux(plateau, chateaux, 0, 0, nbChateaux, maison1);
            rechercheRouteConnecteCentral(plateau, electricite, 0, 0, nbChateaux, maison1);


            *habitant += 10;
            *capa_elec -= 10;
            *capa_eau -= 10;
        }
        if (maison1[i].tempsDuPlacement >= 30 && maison1[i].tempsDuPlacement < 30 + GetFrameTime()) {
            maison1[i].evolution = 2;
            maison1[i].fileName = "../batiments/Maison.png";
            maison1[i].nbHabitants = 50;
            maison1[i].electriciteNecessaire = 50;
            maison1[i].eauNecessaire = 50;
            rechercheRouteConnecteChateaux(plateau, chateaux, 0, 0, nbChateaux, maison1);
            rechercheRouteConnecteCentral(plateau, electricite, 0, 0, nbChateaux, maison1);

            *habitant += 40;
            *capa_elec -= 40;
            *capa_eau -= 40;
        }
        if (maison1[i].tempsDuPlacement >= 45 && maison1[i].tempsDuPlacement < 45 + GetFrameTime()) {
            maison1[i].evolution = 3;
            maison1[i].fileName = "../batiments/Immeuble.png";
            maison1[i].nbHabitants = 100;
            maison1[i].electriciteNecessaire = 100;
            maison1[i].eauNecessaire = 100;
            rechercheRouteConnecteChateaux(plateau, chateaux, 0, 0, nbChateaux, maison1);
            rechercheRouteConnecteCentral(plateau, electricite, 0, 0, nbChateaux, maison1);

            *habitant += 50;
            *capa_elec -= 50;
            *capa_eau -= 50;
        }
        if (maison1[i].tempsDuPlacement >= 60 && maison1[i].tempsDuPlacement < 60 + GetFrameTime()) {
            maison1[i].evolution = 4;
            maison1[i].fileName = "../batiments/Gratte_ciel.png";
            maison1[i].nbHabitants = 1000;
            maison1[i].electriciteNecessaire = 1000;
            maison1[i].eauNecessaire = 1000;
            rechercheRouteConnecteChateaux(plateau, chateaux, 0, 0, nbChateaux, maison1);
            rechercheRouteConnecteCentral(plateau, electricite, 0, 0, nbChateaux, maison1);

            *habitant += 900;
            *capa_elec -= 900;
            *capa_eau -= 900;
        }

    }
    /* for(int i = 0; i < maison1[i].nbHabitants; i++){
         monnaie = monnaie + 10; //Chaque habitant verse 10 ECE-flouz à chaque fin de cycle de l’habitation qu’il occupe.
     }*/

}

void regressionbatiment(Maison maison1[100], int nbMaisons, int *habitant, int *capa_elec, int *capa_eau) {
    for (int i = 0; i < nbMaisons; i++) {//même chose mais cette fois pour la régression
        if (maison1[i].evolution == 4 && (maison1[i].eau <= 1000 || maison1[i].electricite <= 1000)) {
            maison1[i].evolution = 3;
            maison1[i].nbHabitants = 100;
            habitant -= 900;
            capa_elec += 900;
            capa_eau += 900;
            maison1[i].tempsDuPlacement = 15;
        }
        if (maison1[i].evolution == 3 && (maison1[i].eau <= 100 || maison1[i].electricite <= 100)) {
            maison1[i].evolution = 2;
            maison1[i].nbHabitants = 50;
            habitant -= 50;
            capa_elec += 50;
            capa_eau += 50;
            maison1[i].tempsDuPlacement = 15;
        }
        if (maison1[i].evolution == 2 && (maison1[i].eau <= 50 || maison1[i].electricite <= 50)) {
            maison1[i].evolution = 1;
            maison1[i].nbHabitants = 10;
            habitant -= 40;
            capa_elec += 40;
            capa_eau += 40;
            maison1[i].tempsDuPlacement = 15;
        }
        if (maison1[i].evolution == 1 && (maison1[i].eau <= 10 || maison1[i].electricite <= 10)) {
            maison1[i].evolution = 0;
            maison1[i].nbHabitants = 0;
            habitant -= 10;
            capa_elec += 10;
            capa_eau += 10;
            maison1[i].tempsDuPlacement = 15;
        }
    }
}


void
rechercheCentral(Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR], int x, int y, bool *connecteEau, bool *connecteElec) { // Recherche un chateau d'eau et une centrale d'electricité
    if (!(*connecteEau) || !(*connecteElec)) {  // 2 variables qui vont servir à savoir si on a trouvé les centrales
        for (int i = -1; i < 2; i++) {  // on parcourt tt les cases autour de la case etudiée
            for (int j = -1; j < 2; j++) {
                // recherche de central
                if (!(i == j || i == -j)) { // on ignore les cases en diagonales

                    switch (plateau[y + i][x + j].etat) {
                        case 1 : {  // si on trouve une route
                            plateau[y + i][x + j].etat = 22;    // on change son etat pour car on la decouverte
                            rechercheCentral(plateau, x + j, y + i, connecteEau, connecteElec); // on continue la recherche
                            break;
                        }
                        case 7 : {
                            // on a trouvé une centrale
                            *connecteElec = true;
                            break;
                        }
                        case 8 : {
                            // On a touvé un chateau d'eau
                            *connecteEau = true;
                            break;
                        }
                    }
                }
            }
        }
    }
}

int verificationViable(Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR], int x, int y) {  // fonction qui verifie si une maison est viable on non
    bool connecteEau = false; // 2 variables qui vont servir à savoir si on a trouvé les centrales
    bool connecteElec = false;
    int compteur = 0;   // ce compteur va servir à ignorer les coins
    for (int i = -1; i < 4; i++) {
        for (int j = -1; j < 4; j++) {  // on parcourt tout le tour du terrain
            if (compteur != 0 && compteur != 4 && compteur != 20 && compteur != 24) {
                if (plateau[i + y][j + x].etat == 1) {  // si on trouve une route
                    rechercheCentral(plateau, j + x, i + y, &connecteEau, &connecteElec);   // on cherche les centrales
                }
            }
            compteur++;
        }
    }

    for (int i = 0; i < NB_CASE_HAUTEUR; i++) { // une fois la verification terminée on remet tt les routes à leurs etat d'origine
        for (int j = 0; j < NB_CASE_LARGEUR; j++) {
            if (plateau[i][j].etat == 22)
                plateau[i][j].etat = 1;
        }
    }
    if (connecteElec && connecteEau)   // si on trouve les centrales on renvoit 1 sinon 0
        return 1;
    else
        return 0;
}


void verificationMaisonNonViables(Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR], Maison maison1[100], int nbMaisons) { // fonction qui verifie la viabilite des maisons non viable
    for (int i = 0; i < nbMaisons; i++) {
        if (maison1[i].vivable == 0) {
            maison1[i].vivable = verificationViable(plateau, maison1[i].numCaseX, maison1[i].numCaseY);
        }
    }
}


void rechercheMaison(int *numMaison, Maison maison[100], int x, int y, Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR]) {    // programme qui sert a retrouver le numero d'une maison
    // une fois qu'une maison a été trouvée on cherche la case en haut à gauche
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (*numMaison == -1) { // si on a pas trouvé de maison
                if (plateau[y + i][x + j].etat == 2 && plateau[y + i][x + j].batiment >= 100) { // On a trouvé une maison
                    *numMaison = plateau[y + i][x + j].batiment - 100;  // numMaison devient le numero de la maison trouvée
                    for (int k = 0; k < 3; k++) {   // On change l'etat du plateau ou se situe la maison pour s'assurer que nous l'avons bien verifier avant
                        for (int l = 0; l < 3; l++) {
                            plateau[y + i + k][x + j + l].etat = 34;
                        }
                    }
                }
                if (plateau[y + i][x + j].etat == 2 && plateau[y + i][x + j].batiment < 100) {  // tant que l'on a pas trouvé la case avec l'identitée de la maison
                    plateau[y + i][x + j].etat = 33;
                    rechercheMaison(numMaison, maison, x + j, y + j, plateau);
                }
            }
        }
    }
}


void analyseChateauxEau(Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR], Central *chateaux, int x, int y, Maison maisons[100],
                   int compteurDistance) {  // Programme qui analyse un chemin connecté à un chateau pour trouver les maison connecté un chateau
    int numMaisonTrouve = -1;   // Variable d'un numero de maison connectée à un chateau

    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {  // on regarde tt les cases autour d'une route
            if (i != j && i != -j) {    // On evite les coins
                if (plateau[y + i][x + j].etat == 2) {  // Si on trouve une maison
                    rechercheMaison(&numMaisonTrouve, maisons, x + j, y + i, plateau);  // On cherche son numero
                    if (numMaisonTrouve != -1) { // Si on trouve le numero
                        chateaux->tabMaisonAlim[chateaux->nbMaisonAlim].numMaison = numMaisonTrouve;    // On met à jour un tableau de maison connecté à une central
                        chateaux->tabMaisonAlim[chateaux->nbMaisonAlim].distance = compteurDistance;    // On met à jour la distance entre les 2
                        chateaux->nbMaisonAlim += 1;
                        numMaisonTrouve = -1;   // On remet la variable à zero pour de futur recherche
                    }
                }
                if (plateau[y + i][x + j].etat == 1) {  // Si on trouve une route
                    plateau[y + i][x + j].etat = 22;    // On la marque
                    analyseChateauxEau(plateau, chateaux, x + j, y + i, maisons, compteurDistance + 1); // On poursuit la recherche
                }

            }
        }
    }
}


void rechercheRouteConnecteChateaux(Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR], Central chateaux[20], int x, int y,
                                    int nbChateauEau, Maison maison1[100]) {    // On cherche tt les routes connectées à nos chateaux d'eau afin de pouvoir les parcourir pour trouver des maisons


    for (int nb = 0; nb < nbChateauEau; nb++) { // On étudie tt les chateaux
        x = chateaux[nb].numCaseX;  // On part de la case en haut à gauche du chateau, case de reference
        y = chateaux[nb].numCaseY;
        int compteur = 0;   // Compteur qui va servir à ignorer les coins
        for (int i = -1; i < 5; i++) {
            for (int j = -1; j < 7; j++) {  // On parcourt le terrain du chateau en regardant à coté
                compteur++;
                if (plateau[j + y][i + x].etat == 1 && (compteur != 1 && compteur != 8 && compteur != 41 && compteur != 48)) {  // Si on trouve une route
                    analyseChateauxEau(plateau, &chateaux[nb], x + i, y + j, maison1, 1);   // On va analyser le chemin
                }
            }
        }
        for (int i = 0; i < NB_CASE_HAUTEUR; i++) { // Une fois les routes analysées on les remet à l'etat d'origine
            for (int j = 0; j < NB_CASE_LARGEUR; j++) {
                if (plateau[i][j].etat == 22) {
                    plateau[i][j].etat = 1;
                }
                if (plateau[i][j].etat == 33 || plateau[i][j].etat == 34) {
                    plateau[i][j].etat = 2;
                }
            }
        }
    }


    int PPdistance = 9999; // plus petite distance
    int numMaisonPlusProche = -1;
    for (int i = 0; i < nbChateauEau; i++) {    // on initialise bien tt les maisons à un etat de verification 0 pour pouvoir les marquées une fois qu'on les a analysées
        for (int j = 0; j < 20; j++) {
            chateaux[i].tabMaisonAlim[j].verification = 0;
        }
    }
    // On
    int compteur = 0;
    int sauvNumMaison = -1;
    for (int i = 0; i < nbChateauEau; i++) {    // On étudie tt les chateaux
        while (compteur != chateaux[i].nbMaisonAlim) {  // tant qu'on a pas étudié toutes les maisons connectées au chateau

            for (int j = 0; j < chateaux[i].nbMaisonAlim; j++) {
                if (chateaux[i].tabMaisonAlim[j].verification == 0) {
                    if (chateaux[i].tabMaisonAlim[j].distance < PPdistance) {   // On cherche la maison avec le plus proche du chateau
                        PPdistance = chateaux[i].tabMaisonAlim[j].distance;
                        numMaisonPlusProche = chateaux[i].tabMaisonAlim[j].numMaison;
                        sauvNumMaison = j;
                    }
                }
            }
            PPdistance = 9999;
            chateaux[i].tabMaisonAlim[sauvNumMaison].verification = 1;  // On marque la maison pour ne pas la reetudier


            if (numMaisonPlusProche != -1) {
                if ((chateaux[i].capaciteMax - chateaux[i].capaciteutilise) >=  // On donne les ressources necessaire à la maison la plus proche
                    maison1[numMaisonPlusProche].eauNecessaire - maison1[numMaisonPlusProche].eau) {
                    chateaux[i].capaciteutilise += (maison1[numMaisonPlusProche].eauNecessaire -
                                                    maison1[numMaisonPlusProche].eau);
                    maison1[numMaisonPlusProche].eau = maison1[numMaisonPlusProche].eauNecessaire;
                }
            }
            for (int j = 0; j < chateaux[i].nbMaisonAlim; j++) {    // On incrémente le compteur de maison alimenté
                if (chateaux[i].tabMaisonAlim[j].verification)
                    compteur++;
            }
            if (compteur != chateaux[i].nbMaisonAlim)   // Si le nombre de maisons alimentées n'est pas egale au nombre de maisons connectées on recommence
                compteur = 0;
        }
    }
}



void analyseCentral(Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR], Central *electrivite, int x, int y, Maison maisons[100],
                   int compteurDistance) {  // Meme principe que pour l'eau

    int numMaisonTrouve = -1;

    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if (i != j && i != -j) {
                if (plateau[y + i][x + j].etat == 2) {
                    rechercheMaison(&numMaisonTrouve, maisons, x + j, y + i, plateau);
                    if (numMaisonTrouve != -1) {
                        electrivite->tabMaisonAlim[electrivite->nbMaisonAlim].numMaison = numMaisonTrouve;
                        electrivite->tabMaisonAlim[electrivite->nbMaisonAlim].distance = compteurDistance;
                        electrivite->nbMaisonAlim += 1;
                        numMaisonTrouve = -1;
                    }
                }
                if (plateau[y + i][x + j].etat == 1) {
                    plateau[y + i][x + j].etat = 22;
                    analyseCentral(plateau, electrivite, x + j, y + i, maisons, compteurDistance + 1);
                }

            }
        }
    }
}


void rechercheRouteConnecteCentral(Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR], Central electrivite[20], int x, int y,
                                    int nbCentral, Maison maison1[100]) {



    for (int nb = 0; nb < nbCentral; nb++) {
        x = electrivite[nb].numCaseX;
        y = electrivite[nb].numCaseY;
        int compteur = 0;
        for (int i = -1; i < 5; i++) {
            for (int j = -1; j < 7; j++) {
                compteur++;
                if (plateau[j + y][i + x].etat == 1 &&
                    (compteur != 1 && compteur != 8 && compteur != 41 && compteur != 48)) {
                    analyseCentral(plateau, &electrivite[nb], x + i, y + j, maison1, 1);
                }
            }
        }
        for (int i = 0; i < NB_CASE_HAUTEUR; i++) {
            for (int j = 0; j < NB_CASE_LARGEUR; j++) {
                if (plateau[i][j].etat == 22) {
                    plateau[i][j].etat = 1;
                }
                if (plateau[i][j].etat == 33 || plateau[i][j].etat == 34) {
                    plateau[i][j].etat = 2;
                }
            }
        }
    }

    int PPdistance = 9999; // plus petite distance
    int numMaisonPlusProche = -1;
    for (int i = 0; i < nbCentral; i++) {
        for (int j = 0; j < 20; j++) {
            electrivite[i].tabMaisonAlim[j].verification = 0;
        }
    }

    int compteur = 0;
    int sauvNumMaison = -1;
    for (int i = 0; i < nbCentral; i++) {
        while (compteur != electrivite[i].nbMaisonAlim) {

            for (int j = 0; j < electrivite[i].nbMaisonAlim; j++) {
                if (/*chateaux[i].tabMaisonAlim[j].distance < PPdistance && */
                        electrivite[i].tabMaisonAlim[j].verification ==
                        0) {
                    if (electrivite[i].tabMaisonAlim[j].distance < PPdistance) {
                        PPdistance = electrivite[i].tabMaisonAlim[j].distance;
                        numMaisonPlusProche = electrivite[i].tabMaisonAlim[j].numMaison;
                        sauvNumMaison = j;
                        //chateaux[i].tabMaisonAlim[j].verification = 1;
                    }
                }
            }
            PPdistance = 9999;
            electrivite[i].tabMaisonAlim[sauvNumMaison].verification = 1;

            if (numMaisonPlusProche != -1) {
                if ((electrivite[i].capaciteMax - electrivite[i].capaciteutilise) >=
                    maison1[numMaisonPlusProche].electriciteNecessaire - maison1[numMaisonPlusProche].electricite) {
                    electrivite[i].capaciteutilise += (maison1[numMaisonPlusProche].electriciteNecessaire -
                                                    maison1[numMaisonPlusProche].electricite);
                    maison1[numMaisonPlusProche].electricite = maison1[numMaisonPlusProche].electriciteNecessaire;
                }
            }
            for (int j = 0; j < electrivite[i].nbMaisonAlim; j++) {
                if (electrivite[i].tabMaisonAlim[j].verification)
                    compteur++;
            }
            if (compteur != electrivite[i].nbMaisonAlim)
                compteur = 0;
        }
    }
}


void afficherInfoBatiments(Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR], souris souris1, int nbChateaux, int nbCentrales, Maison maison1[100], Central chateaux[20], Central electricite[20]){

    /**
     * Fonction qui affiche les informations d'un batiment quand on maintient le bouton gauche de la souris dessus
     */



    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) &&
        plateau[souris1.caseY][souris1.caseX].etat == 8) {//informations des chateaux d'eau

        for (int i = 0; i < nbChateaux; i++) {
            DrawText(TextFormat("Châteaux numero %d", i + 1), 1210 + i * 300, 410, 20, WHITE);
            DrawText(TextFormat("Ressources : %d", chateaux[i].ressource), 1210 + i * 300, 500, 20, WHITE);
            DrawText(TextFormat("Capacité maximale : %d", chateaux[i].capaciteMax), 1210 + i * 300, 440, 20, WHITE);
            DrawText(TextFormat("Capacité utilisée : %d", chateaux[i].capaciteutilise), 1210 + i * 300, 470, 20,
                     WHITE);
        }
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) &&
        plateau[souris1.caseY][souris1.caseX].etat == 7) {//informations des centrales électriques

        for (int i = 0; i < nbCentrales; i++) {
            DrawText(TextFormat("Centrale numero %d", i + 1), 1210 + i * 300, 410, 20, WHITE);
            DrawText(TextFormat("Ressources : %d", electricite->ressource), 1210 + i * 300, 500, 20, WHITE);
            DrawText(TextFormat("Capacité maximale : %d", electricite->capaciteMax), 1210 + i * 300, 440, 20,
                     WHITE);
            DrawText(TextFormat("Capacité utilisée : %d", electricite->capaciteutilise), 1210 + i * 300, 470, 20,
                     WHITE);
        }
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && plateau[souris1.caseY][souris1.caseX].batiment >= 100) {//informations de la maison sélectionnée

        DrawText(TextFormat("Maison numéro %d", plateau[souris1.caseY][souris1.caseX].batiment -  100 + 1), 1210, 410, 20, WHITE);
        DrawText(TextFormat("Habitants : %d", maison1[plateau[souris1.caseY][souris1.caseX].batiment -  100].nbHabitants), 1210, 440, 20, WHITE);
        DrawText(TextFormat("Eau : %d", maison1[plateau[souris1.caseY][souris1.caseX].batiment -  100].eau), 1210, 470, 20, WHITE);
        DrawText(TextFormat("Electricité : %d", maison1[plateau[souris1.caseY][souris1.caseX].batiment -  100].electricite), 1210, 500, 20,
                 WHITE);
        DrawText(TextFormat("Eau nécessaire : %d", maison1[plateau[souris1.caseY][souris1.caseX].batiment -  100].eauNecessaire), 1210, 530, 20, WHITE);
        DrawText(TextFormat("Electricité nécessaire : %d", maison1[plateau[souris1.caseY][souris1.caseX].batiment -  100].electriciteNecessaire), 1210,
                 560, 20, WHITE);
        DrawText(TextFormat("Temps viable: %0.f", maison1[plateau[souris1.caseY][souris1.caseX].batiment -  100].tempsDuPlacement), 1210,
                 590, 20, WHITE);

    }
}

