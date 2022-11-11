#include "jeu.h"



int mainMenu(int* jouer, int* quitter, int* credits, int* communiste, int* capitaliste) {

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
    ImageResize(&menu,1920,1000);
    Texture2D texture = LoadTextureFromImage(menu);
    ImageDrawPixel(&mode, 0, 0, RAYWHITE);
    ImageResize(&mode,1920,1000);
    Texture2D texture2 = LoadTextureFromImage(mode);
    UnloadImage(mode);
    UnloadImage(menu);
    while (!WindowShouldClose()) {
        Vector2 mouse_pos = GetMousePosition();
        BeginDrawing();
        DrawTexture(texture, 0,0, WHITE);
        Rectangle rec_CREDIT = {748, 108, 238, 92};
        Rectangle rec_JOUER = {1038, 108, 238, 92};
        Rectangle rec_QUITTER = {1328, 108, 238, 92};
        DrawRectangleLinesEx(rec_CREDIT, 4, CheckCollisionPointRec(mouse_pos, rec_CREDIT) ?  SKYBLUE: GREEN);
        DrawRectangleLinesEx(rec_JOUER, 4, CheckCollisionPointRec(mouse_pos, rec_JOUER) ? SKYBLUE : GREEN);
        DrawRectangleLinesEx(rec_QUITTER, 4, CheckCollisionPointRec(mouse_pos, rec_QUITTER) ? SKYBLUE : GREEN);

        if (CheckCollisionPointRec(mouse_pos, rec_JOUER) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            *jouer = true;
        }
        if (CheckCollisionPointRec(mouse_pos, rec_QUITTER) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            *quitter = true;
        }
        else if (CheckCollisionPointRec(mouse_pos, rec_CREDIT) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            *credits = true;
        }

        if (*quitter == true){
            CloseWindow();
        }
        if (*jouer == true){
            DrawTexture(texture2, 0,0, WHITE);
            Rectangle rec_COMMUNISTE = {95, 235, 620, 150};
            Rectangle rec_CAPITALISTE = {95, 585, 620, 150};
            DrawRectangleLinesEx(rec_COMMUNISTE, 4, CheckCollisionPointRec(mouse_pos, rec_CREDIT) ?  SKYBLUE: WHITE);
            DrawRectangleLinesEx(rec_CAPITALISTE, 4, CheckCollisionPointRec(mouse_pos, rec_JOUER) ? SKYBLUE : WHITE);
            if (CheckCollisionPointRec(mouse_pos, rec_COMMUNISTE) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                *communiste = true;
                mainJeu();
            }
            else if (CheckCollisionPointRec(mouse_pos, rec_CAPITALISTE) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
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


void sauvegarde(char *nomFichier, Case tab[NB_CASE_HAUTEUR][NB_CASE_LARGEUR]) {
    //FILE *ifs = fopen("../sauvgarde.txt", "w");
    int filedesc = open(nomFichier, O_WRONLY | O_APPEND);
    FILE *ifs = fopen(nomFichier, "w");
    //write(filedesc, "Begin :\n", 7);



    for (int i = 0; i < NB_CASE_HAUTEUR; ++i) {
        for (int j = 0; j < NB_CASE_LARGEUR; ++j) {
            fprintf(ifs, "%d ", (tab[i][j].etat));
        }
        fprintf(ifs, "\n");
    }
    printf("Fin fonction\n");

    fclose(ifs);
}

void liresauv(char *nomFichier, Case tab[NB_CASE_HAUTEUR][NB_CASE_LARGEUR]){

}

void resetTimer(int* timer){
    if (*timer <= 0) {
        *timer = 15;
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

void construireRoute(souris souris1, int construire_routes, int monde, Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR]){
    if (souris1.interieurPlateau && construire_routes == true && monde == 0) {
        plateau[souris1.caseY][souris1.caseX].etat = 1;
    }
}


void initialiserPlateau(Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR]){
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
        }
    }
}

void dessinerSourieCurseur(souris souris1){
    if (souris1.interieurPlateau)
        DrawRectangle(souris1.caseX * 20 + 20, souris1.caseY * 20 + 20, 20, 20, RED);
}

void dessinerBasePlateau(Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR]){
    for (int i = 0; i < 35; i++) {
        for (int j = 0; j < 45; j++) {
            if (plateau[i][j].etat == 0) {
                DrawRectangleLines(plateau[i][j].x, plateau[i][j].y, 20, 20, WHITE);

            }
        }
    }
}

void dessinerCasesEtages(Rectangle rec_yellow, Rectangle rec_blue, Vector2 mouse_pos){
    DrawRectangleLinesEx(rec_yellow, 6, CheckCollisionPointRec(mouse_pos, rec_yellow) ? ORANGE : YELLOW);
    DrawRectangleLinesEx(rec_blue, 6, CheckCollisionPointRec(mouse_pos, rec_blue) ? SKYBLUE : BLUE);
    DrawText(TextFormat("Etage elec"), 1020, 117, 25, CheckCollisionPointRec(mouse_pos, rec_yellow) ? ORANGE : YELLOW);
    DrawText(TextFormat("Etage eau"),1020, 187, 25, CheckCollisionPointRec(mouse_pos, rec_blue) ? SKYBLUE : BLUE);
}

void dessinertout(int timer){
    DrawText(TextFormat("timer: %.0f", timer), 840, 0, 20, WHITE);
}