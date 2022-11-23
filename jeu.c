#include "jeu.h"


int mainMenu(int *jouer, int *quitter, int *credits, int *communiste, int *capitaliste) {

    Image menu;
    Image mode;
    InitWindow(1024, 768, "ECE city");
    SetWindowPosition(50, 50);
    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(60);
    MaximizeWindow();
    menu = LoadImage("../menu/menu.png");
    mode = LoadImage("../menu/mode.png");
    ImageDrawPixel(&menu, 0, 0, RAYWHITE);
    ImageResize(&menu, 1920, 1000);
    Texture2D texture = LoadTextureFromImage(menu);
    ImageDrawPixel(&mode, 0, 0, RAYWHITE);
    ImageResize(&mode, 1920, 1000);
    Texture2D texture2 = LoadTextureFromImage(mode);
    UnloadImage(mode);
    UnloadImage(menu);
    while (!WindowShouldClose()) {
        Vector2 mouse_pos = GetMousePosition();
        BeginDrawing();
        DrawTexture(texture, 0, 0, WHITE);
        Rectangle rec_CREDIT = {748, 108, 238, 92};
        Rectangle rec_JOUER = {1038, 108, 238, 92};
        Rectangle rec_QUITTER = {1328, 108, 238, 92};
        DrawRectangleLinesEx(rec_CREDIT, 4, CheckCollisionPointRec(mouse_pos, rec_CREDIT) ? SKYBLUE : GREEN);
        DrawRectangleLinesEx(rec_JOUER, 4, CheckCollisionPointRec(mouse_pos, rec_JOUER) ? SKYBLUE : GREEN);
        DrawRectangleLinesEx(rec_QUITTER, 4, CheckCollisionPointRec(mouse_pos, rec_QUITTER) ? SKYBLUE : GREEN);

        if (CheckCollisionPointRec(mouse_pos, rec_JOUER) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            *jouer = true;
        }
        if (CheckCollisionPointRec(mouse_pos, rec_QUITTER) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            *quitter = true;
        } else if (CheckCollisionPointRec(mouse_pos, rec_CREDIT) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            *credits = true;
        }

        if (*quitter == true) {
            CloseWindow();
        }
        if (*jouer == true) {
            DrawTexture(texture2, 0, 0, WHITE);
            Rectangle rec_COMMUNISTE = {95, 235, 620, 150};
            Rectangle rec_CAPITALISTE = {95, 585, 620, 150};
            DrawRectangleLinesEx(rec_COMMUNISTE, 4, CheckCollisionPointRec(mouse_pos, rec_CREDIT) ? SKYBLUE : WHITE);
            DrawRectangleLinesEx(rec_CAPITALISTE, 4, CheckCollisionPointRec(mouse_pos, rec_JOUER) ? SKYBLUE : WHITE);
            if (CheckCollisionPointRec(mouse_pos, rec_COMMUNISTE) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                *communiste = true;
                mainJeu();
            } else if (CheckCollisionPointRec(mouse_pos, rec_CAPITALISTE) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                *capitaliste = true;
                mainJeu();
            }

        }

        EndDrawing();

    }
    UnloadTexture(texture);
    UnloadTexture(texture2);

    CloseWindow();
    return 0;
}


void liresauv(char *nomFichier, Case tab[NB_CASE_HAUTEUR][NB_CASE_LARGEUR]) {
    FILE *ifs = fopen(nomFichier, "r");

    for (int i = 0; i < NB_CASE_HAUTEUR; ++i) {
        for (int j = 0; j < NB_CASE_LARGEUR; ++j) {
            fscanf(ifs, "%d", &tab[i][j].etat);
        }
    }
    printf("Fin fonction sauvegarde\n");

    fclose(ifs);
}

void sauvegarde(char *nomFichier, Case tab[NB_CASE_HAUTEUR][NB_CASE_LARGEUR]) {
    FILE *ifs = fopen(nomFichier, "w");
    for (int i = 0; i < NB_CASE_HAUTEUR; ++i) {
        for (int j = 0; j < NB_CASE_LARGEUR; ++j) {
            fprintf(ifs, "%d ", (tab[i][j].etat));
        }
        fprintf(ifs, "\n");
    }
    printf("Fin fonction sauvegarde\n");

    fclose(ifs);
}

void resetTimer(float *timer, int* monnaie, int habitant, int impots) {
    if (*timer <= 0) {
        *timer = 15;
        *monnaie += habitant * (impots);
    }
}

void chercherCaseDeLaSourie(int x, int y, int *caseX, int *caseY, bool *dansPlateau) {
    if ((x >= 20 && x <= 920) && (y >= 20 && y <= 720)) {
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
    for (int i = 0; i < NB_CASE_HAUTEUR; i++) {
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
            plateau[i][j].verification=0;
        }
    }
}

void dessinerSourieCurseur(souris souris1) {
    if (souris1.interieurPlateau)
        DrawRectangle(souris1.caseX * 20 + 20, souris1.caseY * 20 + 20, 20, 20, RED);
}

void dessinerBasePlateau(Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR]) {
    Image terrain_vague;
    terrain_vague = LoadImage("../batiments/fond_map.png");
    ImageResize(&terrain_vague,20,20);
    Texture2D  texture6 = LoadTextureFromImage(terrain_vague);
    for (int i = 0; i < 35; i++) {
        for (int j = 0; j < 45; j++) {
            if (plateau[i][j].etat == 0) {
                DrawTexture(texture6,plateau[i][j].x,plateau[i][j].y,WHITE);
                DrawRectangleLines(plateau[i][j].x, plateau[i][j].y, 20, 20, BLACK);
            }
        }
    }
}

void dessinerCasesEtages(Rectangle rec_yellow, Rectangle rec_blue, Vector2 mouse_pos) {
    DrawRectangleLinesEx(rec_yellow, 6, CheckCollisionPointRec(mouse_pos, rec_yellow) ? ORANGE : YELLOW);
    DrawRectangleLinesEx(rec_blue, 6, CheckCollisionPointRec(mouse_pos, rec_blue) ? SKYBLUE : BLUE);
    DrawText(TextFormat("Etage elec"), 1020, 117, 25, CheckCollisionPointRec(mouse_pos, rec_yellow) ? ORANGE : YELLOW);
    DrawText(TextFormat("Etage eau"), 1020, 187, 25, CheckCollisionPointRec(mouse_pos, rec_blue) ? SKYBLUE : BLUE);
}

void dessinerVariables(Rectangle rec_monnaie, Rectangle rec_habitant, Rectangle rec_capa_elec, Rectangle rec_capa_eau,
                       Vector2 mouse_pos, int monnaie, int habitant, int capa_elec, int capa_eau) {
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

void dessinerCasesChoixConstruction(Vector2 mouse_pos, Rectangle rec_construire_cabane, Rectangle rec_routes_reset,
                                    Rectangle rec_construire_centrale, Rectangle rec_construire_chateau_d_eau,
                                    Rectangle rec_construire_route) {
    DrawRectangleLinesEx(rec_construire_cabane, 5, CheckCollisionPointRec(mouse_pos, rec_construire_cabane) ? RED : BROWN);
    DrawText(TextFormat("Cabane"), 30, 920, 50, CheckCollisionPointRec(mouse_pos, rec_construire_cabane) ? RED : BROWN);

    DrawRectangleLinesEx(rec_routes_reset, 6, CheckCollisionPointRec(mouse_pos,rec_routes_reset) ? LIGHTGRAY : GRAY);
    DrawText(TextFormat("reset route"), 1020, 387, 25, CheckCollisionPointRec(mouse_pos, rec_routes_reset) ? LIGHTGRAY : GRAY);

    DrawRectangleLinesEx(rec_construire_centrale, 5, CheckCollisionPointRec(mouse_pos, rec_construire_centrale) ? ORANGE : YELLOW);
    DrawText(TextFormat("Electricite"), 240, 920, 50, CheckCollisionPointRec(mouse_pos, rec_construire_centrale) ? ORANGE : YELLOW);

    DrawRectangleLinesEx(rec_construire_chateau_d_eau, 5, CheckCollisionPointRec(mouse_pos, rec_construire_chateau_d_eau) ? SKYBLUE : BLUE);
    DrawText(TextFormat("Eau"), 535, 920, 50, CheckCollisionPointRec(mouse_pos, rec_construire_chateau_d_eau) ? SKYBLUE : BLUE);

    DrawRectangleLinesEx(rec_construire_route, 5, CheckCollisionPointRec(mouse_pos, rec_construire_route) ? LIGHTGRAY : GRAY);
    DrawText(TextFormat("Routes"),655,920,50, CheckCollisionPointRec(mouse_pos,rec_construire_route) ? LIGHTGRAY : GRAY);
}

void afficherEtatMonde(int monde, int afficher_message_reset_routes){
    if (monde != 0) {
        DrawText(TextFormat("Si vous voulez retourner \nau routes veuillez appuyer \nsur 'ENTER'"), 1000, 327,
                 10, WHITE);
    }
    if (monde == 1) {
        DrawText(TextFormat("Etage 1, elec"), 1000, 267, 50, YELLOW);
    } else if (monde == 2) {
        DrawText(TextFormat("Etage 2, eau"), 1000, 267, 50, BLUE);
    }
    if (afficher_message_reset_routes) {
        DrawText(TextFormat(
                         "Appuyez sur 'BACKSPACE' \net suivez les instructions \n(verifiez d'avoir des routes)"), 1000,
                 460, 20, WHITE);
    }
}


void dessinertout(float timer, souris souris1) {
    DrawText(TextFormat("timer: %.0f", timer), 840, 0, 20, WHITE);
    dessinerSourieCurseur(souris1);
}

void initialiserbatiment(Maison batiment){

    Image ruine;
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

void miseajourtimer(Maison maison1[100], int nbMaisons){
   for(int i = 0; i < nbMaisons; i ++){
       if(maison1[i].vivable)
           maison1[i].tempsDuPlacement += GetFrameTime();
   }
}

void evolutionbatiment(Maison maison1[100], int nbMaisons, int* capa_eau, int *capa_elec, int *habitant) {
    for(int i = 0; i < nbMaisons; i ++) {
        if (maison1[i].tempsDuPlacement < 15) { // Terrain vague : 1000 ECE-flouz
            maison1[i].evolution = 0;
            maison1[i].fileName = "../batiments/Terrain_Vague1.png";
            maison1[i].nbHabitants = 0;
        }
        if (maison1[i].tempsDuPlacement >= 15 && maison1[i].tempsDuPlacement < 15 + GetFrameTime()){
            maison1[i].evolution = 1;
            maison1[i].fileName = "../batiments/Cabane.png";
            maison1[i].nbHabitants = 10;
            maison1[i].electriciteNecessaire = 10;
            maison1[i].eauNecessaire = 10;
            *habitant += 10;
            *capa_elec -= 10;
            *capa_eau -= 10;
        }
        if (maison1[i].tempsDuPlacement >= 30 && maison1[i]. tempsDuPlacement < 30 + GetFrameTime()){
            maison1[i].evolution = 2;
            maison1[i].fileName = "../batiments/Maison.png";
            maison1[i].nbHabitants = 50;
            maison1[i].electriciteNecessaire = 50;
            maison1[i].eauNecessaire = 50;
            *habitant += 40;
            *capa_elec -= 40;
            *capa_eau -= 40;
        }
        if (maison1[i].tempsDuPlacement >= 45 && maison1[i].tempsDuPlacement < 45 + GetFrameTime()){
            maison1[i].evolution = 3;
            maison1[i].fileName = "../batiments/Immeuble.png";
            maison1[i].nbHabitants = 100;
            maison1[i].electriciteNecessaire = 100;
            maison1[i].eauNecessaire = 100;
            *habitant += 50;
            *capa_elec -= 50;
            *capa_eau -= 50;
        }
        if(maison1[i].tempsDuPlacement >= 60 && maison1[i].tempsDuPlacement < 60 + GetFrameTime()){
            maison1[i].evolution = 4;
            maison1[i].fileName = "../batiments/Gratte_ciel.png";
            maison1[i].nbHabitants = 1000;
            maison1[i].electriciteNecessaire = 1000;
            maison1[i].eauNecessaire = 1000;
            *habitant += 900;
            *capa_elec -= 900;
            *capa_eau -= 900;
        }

    }
   /* for(int i = 0; i < maison1[i].nbHabitants; i++){
        monnaie = monnaie + 10; //Chaque habitant verse 10 ECE-flouz à chaque fin de cycle de l’habitation qu’il occupe.
    }*/

}
void regressionbatiment(Maison maison1[100], int nbMaisons, int* habitant, int* capa_elec, int* capa_eau) {
    for(int i = 0; i < nbMaisons; i ++) {
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
    /*for(int i = 0; i < maison1[i].nbHabitants; i++){
        monnaie = monnaie + 10; //Chaque habitant verse 10 ECE-flouz à chaque fin de cycle de l’habitation qu’il occupe.
    }*/
}


void rechercheCentral(Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR], int x, int y, bool* connecteEau, bool* connecteElec){
    if(!(*connecteEau) || !(*connecteElec)){
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                // recherche de central
                if (!(i == j || i == -j)) {

                switch (plateau[y + i][x + j].etat) {
                    case 1 : {
                        plateau[y + i][x + j].etat = 22;
                        rechercheCentral(plateau, x + j, y + i, connecteEau, connecteElec);
                        break;
                    }
                    case 7 : {
                        // on a trouvé une centrale
                        *connecteElec = true;
                        break;
                    }
                    case 8 : {
                        *connecteEau = true;
                        break;
                    }
                }
            }
            }
        }
    }
}

int verificationViable(Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR], int x, int y){
    bool connecteEau = false;
    bool connecteElec = false;
    int compteur = 0;
    for (int i = -1; i < 4; i++) {
        for (int j = -1; j < 4; j++) {
            if (compteur!=0 && compteur != 4 && compteur !=20 && compteur !=24){
                if(plateau[i+y][j+x].etat==1){
                    rechercheCentral(plateau, j+x, i+y, &connecteEau, &connecteElec);
                }
            }
            compteur++;
        }
    }

    for (int i = 0; i < NB_CASE_HAUTEUR; i++) {
        for (int j = 0; j < NB_CASE_LARGEUR; j++) {
            if (plateau[i][j].etat == 22)
                plateau[i][j].etat = 1;
        }
    }
    if(connecteElec && connecteEau)
        return 1;
    else
        return 0;
}


void verificationMaisonNonViables(Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR], Maison maison1[100], int nbMaisons){
    for (int i = 0; i < nbMaisons; i++) {
        if (maison1[i].vivable == 0){
            maison1[i].vivable = verificationViable(plateau, maison1[i].numCaseX, maison1[i].numCaseY);
            //DrawRectangle(maison1[i].numCaseX * 20 + 20, maison1[i].numCaseY * 20 + 20, 20,20,GREEN);
        }
    }
}