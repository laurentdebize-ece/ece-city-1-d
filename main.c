#include "jeu.h"

enum{
    rien = 0,
    elec = 1,
    eau = 2
}monde;

int communiste;
int capitaliste;
int jouer;
int quitter;
int credits;
float timer = 5;
int monde_eau;
int monde_elec;

Case plateau[NB_CASE_HAUTEUR][NB_CASE_LARGEUR];
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

    while (!WindowShouldClose()) {
        Image ruine;
        Image terrain_vague;
        Image cabane;
        Image maison;
        Image immeuble;
        Image gratte_ciel;
        Image centrale;
        Image chateau_d_eau;

        Vector2 mouse_pos = GetMousePosition();

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
                    DrawRectangle(plateau[i][j].x, plateau[i][j].y, 20, 20, monde == 2 ? BLUE : monde == 1 ? YELLOW : GRAY);
                    DrawRectangleLines(plateau[i][j].x, plateau[i][j].y, 20, 20, WHITE); // creation des routes
                    if(reset_routes == true && monde == 0){
                        DrawText(TextFormat("Cliquer sur la route que \n vous souhaitez retirer"), 1000, 267, 20, WHITE);
                        DrawRectangle(souris1.caseX * 20 + 20, souris1.caseY * 20 + 20, 20, 20, RED);
                        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                            if(construire_routes == true){
                                construire_routes = false;
                            }
                            plateau[souris1.caseY][souris1.caseX].etat = 0;
                        }
                    }
                    else if(reset_routes == false){
                        plateau[i][j].etat = 1;
                    }
                }
            }
        }


        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            construireRoute(souris1, construire_routes, monde, plateau);
        }

        DrawText(TextFormat("CaseX :%d",souris1.caseX),950,50, 20, WHITE);
        DrawText(TextFormat("CaseY :%d",souris1.caseY),950,70, 20, WHITE);

        if (timer <= 1){
            DrawText(TextFormat("Nouveau Cycle"),180,280, 80, GREEN);        }

        dessinerCasesEtages(rec_yellow, rec_blue, mouse_pos);

        DrawRectangleLinesEx(rec_monnaie, 4, CheckCollisionPointRec(mouse_pos, rec_monnaie) ? YELLOW : GOLD);
        DrawRectangleLinesEx(rec_habitant, 4, CheckCollisionPointRec(mouse_pos, rec_habitant) ? GREEN : LIME);
        DrawText(TextFormat("%d ECE Flouz",monnaie), 1670, 20, 20, CheckCollisionPointRec(mouse_pos, rec_monnaie) ? YELLOW : GOLD);
        DrawText(TextFormat("%d habitants",habitant),1710, 60, 20, CheckCollisionPointRec(mouse_pos, rec_habitant) ? GREEN : LIME);

        DrawRectangleLinesEx(rec_capa_elec, 4, CheckCollisionPointRec(mouse_pos, rec_capa_elec) ? ORANGE : YELLOW);
        DrawRectangleLinesEx(rec_capa_eau, 4, CheckCollisionPointRec(mouse_pos, rec_capa_eau) ? SKYBLUE : BLUE);
        DrawText(TextFormat("Capacite en electricite : %d",capa_elec), 1560, 100, 20, CheckCollisionPointRec(mouse_pos, rec_capa_elec) ? ORANGE : YELLOW);
        DrawText(TextFormat("Capacite en eau : %d",capa_eau),1630, 140, 20, CheckCollisionPointRec(mouse_pos, rec_capa_eau) ? SKYBLUE : BLUE);

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

        // cabane = LoadImage("Cabane.png");

        if(CheckCollisionPointRec(mouse_pos, rec_construire_route) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            construire_routes = !construire_routes;
        }
        if(CheckCollisionPointRec(mouse_pos, rec_routes_reset) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            afficher_message_reset_routes = !afficher_message_reset_routes;
        }
        if(IsKeyDown(KEY_BACKSPACE)){
            reset_routes = true;
        }
        else{
            if(reset_routes == true){
                reset_routes = false;
            }
        }
        if (CheckCollisionPointRec(mouse_pos, rec_yellow) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            monde = 1;
        }
        else if (CheckCollisionPointRec(mouse_pos, rec_blue) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            monde = 2;
        }
        else if(IsKeyPressed(KEY_ENTER)){
            monde = 0;
        }
        if(monde != 0){
            DrawText(TextFormat("Si vous voulez retourner \nau routes veuillez appuyer \nsur 'ENTER'"), 1000, 327, 10, WHITE);
        }
        if (monde == 1){
            DrawText(TextFormat("Etage 1, elec"), 1000, 267, 50, YELLOW);
        }
        else if (monde == 2){
            DrawText(TextFormat("Etage 2, eau"), 1000, 267, 50, BLUE);
        }
        if(afficher_message_reset_routes){
            DrawText(TextFormat("Appuyez sur 'BACKSPACE' \net suivez les instructions \n(verifiez d'avoir des routes)"), 1000, 460, 20, WHITE);
        }

        dessinertout(timer);
        EndDrawing();
    }

    sauvegarde("../sauvgarde.txt", plateau);
}

void main(){
    mainMenu(&jouer,&quitter, &credits, &communiste, &capitaliste);
}