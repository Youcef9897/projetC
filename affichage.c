#include "raylib.h"
#include "graphe.h"
#include "mission1.h"
#include "mission2.h"
#include "mission3.h"
#include "simulation.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_POS 60

#define RAYON 22
#define TAILLE_V_SOMMET 20
#define TAILLE_NOM_VILLE 18
#define TAILLE_TEMPS_ARC 17

#define EPAISSEUR_ARC_NORMAL 2.5f
#define EPAISSEUR_ARC_COUVERT 3.5f
#define EPAISSEUR_ARC_CHEMIN 6.0f

#define COULEUR_POLICE PURPLE

typedef enum {
    VIEW_MENU,
    VIEW_GRAPHE,
    VIEW_MISSION1,
    VIEW_MISSION2,
    VIEW_MISSION3,
    VIEW_SIMULATION
} ViewMode;


typedef enum {
    SIM_PARCOURS,
    SIM_REPERE,
    SIM_INVENTAIRE,
    SIM_RETOUR_BASE,
    SIM_CAPTURE
} EtatSimulation;

static EtatSimulation etatSim = SIM_PARCOURS;

static bool sommetsSurveilles[MAX_POS] = {false};
static bool sommetsAvantTour[MAX_POS] = {false};

static bool simulationInitialisee = false;
static int numeroTour = 1;

static Chemin cheminRetourBase;
static int etapeRetourBase = 0;

static void nouveauTourSimulation(Graphe *g);
static void resetSimulationComplete(Graphe *g);

static Vector2 positions[MAX_POS];

static int policeID = 0;
static int suspectID = -1;
static Chemin cheminActuel;
static int etapeChemin = 0;
static double dernierTemps = 0;

static bool mission2DejaLancee = false;
static int cameraCouranteID = 0;

/* ========================= */
/* OUTILS */
/* ========================= */

static Sommet *trouverSommetParIDAffichage(Graphe *g, int id) {
    Sommet *s = g->listeSommets;

    while (s != NULL) {
        if (s->ID == id) return s;
        s = s->suivant;
    }

    return NULL;
}

static void initialiserPositions(Graphe *g) {
    (void)g;

    int w = GetScreenWidth();
    int h = GetScreenHeight();

    float left = 90;
    float top = 110;

    float mapW = w - 430;
    float mapH = h - 190;

    positions[0]  = (Vector2){left + mapW * 0.50f, top + mapH * 0.54f};
    positions[1]  = (Vector2){left + mapW * 0.50f, top + mapH * 0.40f};
    positions[2]  = (Vector2){left + mapW * 0.36f, top + mapH * 0.54f};
    positions[3]  = (Vector2){left + mapW * 0.64f, top + mapH * 0.54f};
    positions[4]  = (Vector2){left + mapW * 0.50f, top + mapH * 0.68f};
    positions[5]  = (Vector2){left + mapW * 0.36f, top + mapH * 0.40f};

    positions[6]  = (Vector2){left + mapW * 0.64f, top + mapH * 0.40f};
    positions[7]  = (Vector2){left + mapW * 0.22f, top + mapH * 0.54f};
    positions[8]  = (Vector2){left + mapW * 0.22f, top + mapH * 0.40f};
    positions[9]  = (Vector2){left + mapW * 0.36f, top + mapH * 0.68f};
    positions[10] = (Vector2){left + mapW * 0.22f, top + mapH * 0.68f};
    positions[11] = (Vector2){left + mapW * 0.64f, top + mapH * 0.68f};

    positions[12] = (Vector2){left + mapW * 0.22f, top + mapH * 0.26f};
    positions[13] = (Vector2){left + mapW * 0.78f, top + mapH * 0.68f};
    positions[14] = (Vector2){left + mapW * 0.78f, top + mapH * 0.40f};
    positions[15] = (Vector2){left + mapW * 0.78f, top + mapH * 0.26f};
    positions[16] = (Vector2){left + mapW * 0.78f, top + mapH * 0.54f};
    positions[17] = (Vector2){left + mapW * 0.78f, top + mapH * 0.82f};

    positions[18] = (Vector2){left + mapW * 0.36f, top + mapH * 0.82f};
    positions[19] = (Vector2){left + mapW * 0.50f, top + mapH * 0.82f};
    positions[20] = (Vector2){left + mapW * 0.64f, top + mapH * 0.82f};
    positions[21] = (Vector2){left + mapW * 0.22f, top + mapH * 0.82f};
    positions[22] = (Vector2){left + mapW * 0.64f, top + mapH * 0.26f};
    positions[23] = (Vector2){left + mapW * 0.50f, top + mapH * 0.26f};

    positions[24] = (Vector2){left + mapW * 0.92f, top + mapH * 0.64f};
    positions[25] = (Vector2){left + mapW * 0.92f, top + mapH * 0.82f};
    positions[26] = (Vector2){left + mapW * 0.08f, top + mapH * 0.12f};
    positions[27] = (Vector2){left + mapW * 0.50f, top + mapH * 0.12f};
    positions[28] = (Vector2){left + mapW * 0.36f, top + mapH * 0.16f};
    positions[29] = (Vector2){left + mapW * 0.22f, top + mapH * 0.12f};
}

static Rectangle bouton(float x, float y, float w, float h, const char *texte) {
    Rectangle r = {x, y, w, h};
    Color c = CheckCollisionPointRec(GetMousePosition(), r) ? LIGHTGRAY : RAYWHITE;

    DrawRectangleRounded(r, 0.15f, 8, c);
    DrawRectangleRoundedLines(r, 0.15f, 1, DARKGRAY);
    DrawText(texte, x + 18, y + 13, 20, BLACK);

    return r;
}

static void resetAffichageSimulation(Graphe *g) {
    policeID = 0;
    suspectID = -1;
    etapeChemin = 0;
    dernierTemps = GetTime();
    cheminActuel.taille = 0;
    cheminActuel.tempsTotal = 0;
    mission2DejaLancee = false;

    Sommet *s = g->listeSommets;

    while (s != NULL) {
        s->CamPlace = false;

        Arc *a = s->routes;
        while (a != NULL) {
            a->estCouvert = false;
            a = a->suivant;
        }

        s = s->suivant;
    }
}

static void panneauInfo(void) {
    int w = GetScreenWidth();

    DrawRectangle(w - 340, 0, 340, GetScreenHeight(), Fade(LIGHTGRAY, 0.35f));
    DrawLine(w - 340, 0, w - 340, GetScreenHeight(), GRAY);
}

static void legende(void) {
    int w = GetScreenWidth();
    int x = w - 315;
    int y = 80;

    DrawText("LEGENDE", x, y, 24, DARKBLUE);

    DrawCircle(x + 12, y + 50, 10, COULEUR_POLICE);
    DrawText("Police", x + 35, y + 40, 18, BLACK);

    DrawCircle(x + 12, y + 85, 10, RED);
    DrawText("Suspect", x + 35, y + 75, 18, BLACK);

    DrawCircle(x + 12, y + 120, 10, GREEN);
    DrawText("Camera", x + 35, y + 110, 18, BLACK);

    DrawLineEx((Vector2){x, y + 160}, (Vector2){x + 25, y + 160}, 5, ORANGE);
    DrawText("Chemin Dijkstra", x + 35, y + 150, 18, BLACK);

    DrawLineEx((Vector2){x, y + 200}, (Vector2){x + 25, y + 200}, 3, LIGHTGRAY);
    DrawText("Route normale", x + 35, y + 190, 18, BLACK);
}

static void resetSimulationComplete(Graphe *g) {
    policeID = 0;
    suspectID = -1;
    etapeChemin = 0;
    numeroTour = 1;
    etatSim = SIM_PARCOURS;
    simulationInitialisee = true;

    cheminActuel.taille = 0;
    cheminActuel.tempsTotal = 0;

    for (int i = 0; i < MAX_POS; i++) {
        sommetsSurveilles[i] = false;
        sommetsAvantTour[i] = false;
    }

    Sommet *s = g->listeSommets;
    while (s != NULL) {
        s->CamPlace = false;

        Arc *a = s->routes;
        while (a != NULL) {
            a->estCouvert = false;
            a = a->suivant;
        }

        s = s->suivant;
    }

    nouveauTourSimulation(g);
}

/* ========================= */
/* DESSIN GRAPHE */
/* ========================= */

static bool arcDansChemin(int id1, int id2) {
    for (int i = 0; i < etapeChemin && i < cheminActuel.taille - 1; i++) {
        if (cheminActuel.sommets[i] == id1 &&
            cheminActuel.sommets[i + 1] == id2) {
            return true;
        }
    }

    return false;
}

static void dessinerTitreCarte(const char *mission) {
    int w = GetScreenWidth();

    DrawRectangle(0, 0, w - 340, 95, Fade(RAYWHITE, 0.95f));
    DrawText("VILLE DE LA PLATA", 40, 18, 30, DARKBLUE);
    DrawText(mission, 40, 55, 22, DARKGRAY);
}

static void dessinerArcsSimple(Graphe *g) {
    Sommet *s = g->listeSommets;

    while (s != NULL) {
        Arc *arc = s->routes;

        while (arc != NULL) {
            int id1 = s->ID;
            int id2 = arc->destination->ID;

            DrawLineEx(positions[id1], positions[id2],
                       EPAISSEUR_ARC_NORMAL, LIGHTGRAY);

            Vector2 milieu = {
                (positions[id1].x + positions[id2].x) / 2.0f,
                (positions[id1].y + positions[id2].y) / 2.0f
            };

            char txt[32];
            sprintf(txt, "%.0fs", arc->temps);

            int largeur = MeasureText(txt, TAILLE_TEMPS_ARC);

            DrawRectangle(milieu.x - largeur / 2 - 3,
                          milieu.y - TAILLE_TEMPS_ARC / 2 - 2,
                          largeur + 6,
                          TAILLE_TEMPS_ARC + 4,
                          Fade(RAYWHITE, 0.85f));

            DrawText(txt,
                     milieu.x - largeur / 2,
                     milieu.y - TAILLE_TEMPS_ARC / 2,
                     TAILLE_TEMPS_ARC,
                     DARKGRAY);

            arc = arc->suivant;
        }

        s = s->suivant;
    }
}

static void dessinerArcsMission(Graphe *g) {
    Sommet *s = g->listeSommets;

    while (s != NULL) {
        Arc *arc = s->routes;

        while (arc != NULL) {
            int id1 = s->ID;
            int id2 = arc->destination->ID;

            Color couleur = LIGHTGRAY;
            float epaisseur = EPAISSEUR_ARC_NORMAL;

            if (arc->estCouvert) {
                couleur = GREEN;
                epaisseur = EPAISSEUR_ARC_COUVERT;
            }

            if (arcDansChemin(id1, id2)) {
                couleur = ORANGE;
                epaisseur = EPAISSEUR_ARC_CHEMIN;
            }

            DrawLineEx(positions[id1], positions[id2], epaisseur, couleur);

            Vector2 milieu = {
                (positions[id1].x + positions[id2].x) / 2.0f,
                (positions[id1].y + positions[id2].y) / 2.0f
            };

            char txt[32];
            sprintf(txt, "%.0fs", arc->temps);

            int largeur = MeasureText(txt, TAILLE_TEMPS_ARC);

            DrawRectangle(milieu.x - largeur / 2 - 3,
                          milieu.y - TAILLE_TEMPS_ARC / 2 - 2,
                          largeur + 6,
                          TAILLE_TEMPS_ARC + 4,
                          Fade(RAYWHITE, 0.85f));

            DrawText(txt,
                     milieu.x - largeur / 2,
                     milieu.y - TAILLE_TEMPS_ARC / 2,
                     TAILLE_TEMPS_ARC,
                     DARKGRAY);

            arc = arc->suivant;
        }

        s = s->suivant;
    }
}

static void dessinerSommetsSimples(Graphe *g) {
    Sommet *s = g->listeSommets;

    while (s != NULL) {
        Color couleur = SKYBLUE;

        DrawCircleV(positions[s->ID], RAYON + 5, Fade(couleur, 0.25f));
        DrawCircleV(positions[s->ID], RAYON, couleur);
        DrawCircleLines(positions[s->ID].x, positions[s->ID].y, RAYON, BLACK);

        char idTxt[16];
        sprintf(idTxt, "V%d", s->ID);

        int idLargeur = MeasureText(idTxt, TAILLE_V_SOMMET);
        DrawText(idTxt,
                 positions[s->ID].x - idLargeur / 2,
                 positions[s->ID].y - TAILLE_V_SOMMET / 2,
                 TAILLE_V_SOMMET,
                 BLACK);

        int nomLargeur = MeasureText(s->nom, TAILLE_NOM_VILLE);
        DrawText(s->nom,
                 positions[s->ID].x - nomLargeur / 2,
                 positions[s->ID].y + RAYON + 8,
                 TAILLE_NOM_VILLE,
                 BLACK);

        s = s->suivant;
    }
}

static void dessinerSommetsMission(Graphe *g) {
    Sommet *s = g->listeSommets;

    while (s != NULL) {
        Color couleur = SKYBLUE;

        if (s->CamPlace) couleur = GREEN;
        if (s->ID == policeID) couleur = COULEUR_POLICE;
        if (s->ID == suspectID) couleur = RED;

        DrawCircleV(positions[s->ID], RAYON + 5, Fade(couleur, 0.25f));
        DrawCircleV(positions[s->ID], RAYON, couleur);
        DrawCircleLines(positions[s->ID].x, positions[s->ID].y, RAYON, BLACK);

        char idTxt[16];
        sprintf(idTxt, "V%d", s->ID);

        int idLargeur = MeasureText(idTxt, TAILLE_V_SOMMET);
        DrawText(idTxt,
                 positions[s->ID].x - idLargeur / 2,
                 positions[s->ID].y - TAILLE_V_SOMMET / 2,
                 TAILLE_V_SOMMET,
                 BLACK);

        int nomLargeur = MeasureText(s->nom, TAILLE_NOM_VILLE);
        DrawText(s->nom,
                 positions[s->ID].x - nomLargeur / 2,
                 positions[s->ID].y + RAYON + 8,
                 TAILLE_NOM_VILLE,
                 BLACK);

        s = s->suivant;
    }
}

static void dessinerGrapheSimple(Graphe *g) {
    dessinerArcsSimple(g);
    dessinerSommetsSimples(g);
}

static void dessinerGrapheMission(Graphe *g) {
    dessinerArcsMission(g);
    dessinerSommetsMission(g);
}

/* ========================= */
/* MENU */
/* ========================= */

static void dessinerMenu(void) {
    int w = GetScreenWidth();

    DrawText("FALCON EYE", w / 2 - 130, 80, 46, DARKBLUE);
    DrawText("Interface graphique de simulation", w / 2 - 180, 135, 24, DARKGRAY);

    bouton(w / 2 - 220, 220, 440, 55, "1. Afficher le graphe complet");
    bouton(w / 2 - 220, 295, 440, 55, "2. Mission 1 : poursuite");
    bouton(w / 2 - 220, 370, 440, 55, "3. Mission 2 : cameras");
    bouton(w / 2 - 220, 445, 440, 55, "4. Mission 3 : inventaire");
    bouton(w / 2 - 220, 520, 440, 55, "5. Simulation complete");
    bouton(w / 2 - 220, 620, 440, 55, "0. Quitter");
}

static void retourBouton(ViewMode *view, Graphe *g) {
    int h = GetScreenHeight();

    Rectangle r = bouton(40, h - 80, 170, 50, "Retour");

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
        CheckCollisionPointRec(GetMousePosition(), r)) {
        resetAffichageSimulation(g);
        *view = VIEW_MENU;
    }
}

/* ========================= */
/* MISSION 1 */
/* ========================= */

static void preparerMission1(Graphe *g) {
    Police police;
    Suspect suspect;

    Sommet *base = trouverSommetParIDAffichage(g, policeID);
    if (base == NULL) return;

    police.emplacement = base;
    police.inventaire = 0;

    mettreAJourSuspectAleatoire(g, &suspect, policeID);
    suspectID = suspect.emplacement->ID;

    cheminActuel = Dijkstra(g, &police, &suspect);

    etapeChemin = 0;
    dernierTemps = GetTime();
}

static void tourSuivant(Graphe *g, bool poserCamera) {
    if (cheminActuel.taille > 0) {
        policeID = cheminActuel.sommets[cheminActuel.taille - 1];
    }

    etapeChemin = 0;
    suspectID = -1;
    cheminActuel.taille = 0;
    cheminActuel.tempsTotal = 0;

    preparerMission1(g);

    if (poserCamera) {
        Sommet *s = trouverSommetParIDAffichage(g, policeID);
        if (s != NULL) {
            s->CamPlace = true;
        }
    }
}

static void boutonTourSuivant(Graphe *g, bool poserCamera) {
    int x = GetScreenWidth() - 315;
    int y = 570;

    Rectangle r = bouton(x, y, 230, 50, "Tour suivant");

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
        CheckCollisionPointRec(GetMousePosition(), r)) {
        tourSuivant(g, poserCamera);
    }
}

static void afficherMission1(Graphe *g) {
    dessinerTitreCarte("MISSION 1 : POURSUITE POLICE / SUSPECT");
    DrawText("Animation du plus court chemin calcule avec Dijkstra", 40, 75, 20, DARKGRAY);

    if (GetTime() - dernierTemps > 0.8 &&
        etapeChemin < cheminActuel.taille - 1) {
        etapeChemin++;
        dernierTemps = GetTime();
    }

    if (cheminActuel.taille > 0 &&
        etapeChemin >= cheminActuel.taille - 1) {
        policeID = cheminActuel.sommets[cheminActuel.taille - 1];
    }

    dessinerGrapheMission(g);

    panneauInfo();
    legende();

    int x = GetScreenWidth() - 315;
    int y = 340;

    DrawText("MISSION 1", x, y, 24, DARKBLUE);
    DrawText(TextFormat("Police : V%d", policeID), x, y + 40, 18, COULEUR_POLICE);
    DrawText(TextFormat("Suspect : V%d", suspectID), x, y + 70, 18, RED);
    DrawText(TextFormat("Temps : %.2f s", cheminActuel.tempsTotal), x, y + 100, 18, BLACK);
    DrawText(TextFormat("Etape : %d / %d", etapeChemin, cheminActuel.taille - 1), x, y + 130, 18, BLACK);

    DrawText("ESPACE : relancer", x, y + 180, 18, DARKGRAY);

    boutonTourSuivant(g, false);

    if (IsKeyPressed(KEY_SPACE)) {
        preparerMission1(g);
    }
}

/* ========================= */
/* MISSION 2 */
/* ========================= */

static void afficherMission2(Graphe *g) {
    dessinerTitreCarte("MISSION 2 : PLACEMENT DES CAMERAS");
    DrawText("Les sommets verts representent les intersections surveillees.", 40, 75, 20, DARKGRAY);

    if (!mission2DejaLancee) {
    mission2DejaLancee = true;
    cameraCouranteID = 0;
    dernierTemps = GetTime();
    }

    if (GetTime() - dernierTemps > 0.8 && !ArcsTousCouverts(g)) {
    placerUneCamera(g);
    dernierTemps = GetTime();
}

    dessinerGrapheMission(g);
    panneauInfo();
    legende();

    int x = GetScreenWidth() - 315;
    int y = 340;
    int nb = 0;

    Sommet *s = g->listeSommets;

    while (s != NULL) {
        if (s->CamPlace) nb++;
        s = s->suivant;
    }

    DrawText("MISSION 2", x, y, 24, DARKGREEN);
    DrawText(TextFormat("Cameras placees : %d", nb), x, y + 45, 18, BLACK);
    DrawText("Objectif :", x, y + 90, 18, DARKGRAY);
    DrawText("couvrir les routes", x, y + 120, 18, BLACK);
    DrawText("avec peu de cameras.", x, y + 150, 18, BLACK);
}

/* ========================= */
/* MISSION 3 */
/* ========================= */

static void afficherMission3(void) {
    dessinerTitreCarte("MISSION 3 : INVENTAIRE POLICE");
    DrawText("Objectif : maximiser la valeur tactique sans depasser 40 kg.", 40, 80, 22, DARKGRAY);

    DrawRectangle(80, 150, 620, 420, Fade(LIGHTGRAY, 0.35f));
    DrawRectangleLines(80, 150, 620, 420, DARKGRAY);

    DrawText("Materiel selectionne par sac a dos dynamique :", 110, 180, 22, BLACK);

    DrawText("- Bandes a pointes       12 kg   valeur 85", 130, 230, 20, BLACK);
    DrawText("- Drone tactique          5 kg   valeur 90", 130, 265, 20, BLACK);
    DrawText("- Brouilleur de signal   10 kg   valeur 60", 130, 300, 20, BLACK);
    DrawText("- Trousse medicale        3 kg   valeur 30", 130, 335, 20, BLACK);
    DrawText("- Gaz lacrymogene         8 kg   valeur 50", 130, 370, 20, BLACK);
    DrawText("- Scanner portable        2 kg   valeur 25", 130, 405, 20, BLACK);

    DrawText("Poids total : 40 / 40 kg", 110, 480, 22, DARKBLUE);
    DrawText("Valeur tactique totale : 340", 110, 515, 22, DARKGREEN);

    panneauInfo();

    int x = GetScreenWidth() - 315;
    int y = 110;

    DrawText("MISSION 3", x, y, 24, DARKPURPLE);
    DrawText("Algorithme :", x, y + 45, 18, DARKGRAY);
    DrawText("Sac a dos dynamique", x, y + 75, 18, BLACK);
    DrawText("Capacite : 40 kg", x, y + 120, 18, BLACK);
    DrawText("Resultat optimal", x, y + 160, 18, DARKGREEN);
}

/* ========================= */
/* SIMULATION COMPLETE */
/* ========================= */

static void sauvegarderSurveillanceAvantTour(void) {
    for (int i = 0; i < MAX_POS; i++) {
        sommetsAvantTour[i] = sommetsSurveilles[i];
    }
}

static void nouveauTourSimulation(Graphe *g) {
    sauvegarderSurveillanceAvantTour();

    if (cheminActuel.taille > 0) {
        policeID = cheminActuel.sommets[cheminActuel.taille - 1];
    }

    Police police;
    Suspect suspect;

    police.emplacement = trouverSommetParIDAffichage(g, policeID);
    police.inventaire = 0;

    if (police.emplacement == NULL) return;

    mettreAJourSuspectAleatoire(g, &suspect, policeID);
    suspectID = suspect.emplacement->ID;

    cheminActuel = Dijkstra(g, &police, &suspect);

    etapeChemin = 0;
    dernierTemps = GetTime();
}

static void afficherSimulationComplete(Graphe *g) {
    dessinerTitreCarte("SIMULATION COMPLETE Falcon Eye");
    DrawText("Mission 1 + cameras -> detection finale -> inventaire -> transport -> capture",
             40, 80, 20, DARKGRAY);

    if (!simulationInitialisee) {
        resetSimulationComplete(g);
    }

    if (etatSim == SIM_PARCOURS) {

        if (GetTime() - dernierTemps > 0.8 &&
            etapeChemin < cheminActuel.taille - 1) {

            etapeChemin++;

            int id = cheminActuel.sommets[etapeChemin];

            Sommet *s = trouverSommetParIDAffichage(g, id);
            if (s != NULL) {
                s->CamPlace = true;
                sommetsSurveilles[id] = true;
            }

            dernierTemps = GetTime();
        }

        if (cheminActuel.taille > 0 &&
            etapeChemin >= cheminActuel.taille - 1) {

            policeID = cheminActuel.sommets[cheminActuel.taille - 1];

            /*
             * Condition correcte :
             * on capture seulement si la POSITION FINALE DU SUSPECT
             * était déjà surveillée AVANT ce tour.
             */
            if (suspectID >= 0 && sommetsAvantTour[suspectID]) {
                etatSim = SIM_REPERE;
                dernierTemps = GetTime();
            } else {
                numeroTour++;
                nouveauTourSimulation(g);
            }
        }
    }

    else if (etatSim == SIM_REPERE) {
        DrawText("CAMERA ACTIVE : le suspect est sur une zone deja surveillee.",
                 40, 120, 22, RED);

        if (GetTime() - dernierTemps > 1.5) {
            etatSim = SIM_INVENTAIRE;
            dernierTemps = GetTime();
        }
    }

    else if (etatSim == SIM_INVENTAIRE) {
        DrawText("MISSION 3 : preparation de l'inventaire optimal...",
                 40, 120, 22, DARKPURPLE);

        DrawText("Materiel charge : bandes, drone, brouilleur, trousse, gaz, scanner.",
                 40, 155, 20, DARKGRAY);

        if (GetTime() - dernierTemps > 2.0) {
            Police policeBase;
            Suspect suspectFinal;

            policeBase.emplacement = trouverSommetParIDAffichage(g, 0);
            policeBase.inventaire = 0;

            suspectFinal.emplacement = trouverSommetParIDAffichage(g, suspectID);

            if (policeBase.emplacement != NULL && suspectFinal.emplacement != NULL) {
                cheminRetourBase = Dijkstra(g, &policeBase, &suspectFinal);
                etapeRetourBase = 0;
                dernierTemps = GetTime();
                etatSim = SIM_RETOUR_BASE;
            } else {
                etatSim = SIM_CAPTURE;
                dernierTemps = GetTime();
            }
        }
    }

    else if (etatSim == SIM_RETOUR_BASE) {
        DrawText("TRANSPORT DU MATERIEL : trajet de V0 vers la position du suspect.",
                 40, 120, 22, DARKBLUE);

        if (GetTime() - dernierTemps > 0.8 &&
            etapeRetourBase < cheminRetourBase.taille - 1) {

            etapeRetourBase++;
            dernierTemps = GetTime();
        }

        if (cheminRetourBase.taille > 0 &&
            etapeRetourBase >= cheminRetourBase.taille - 1) {

            etatSim = SIM_CAPTURE;
            dernierTemps = GetTime();
        }
    }

    else if (etatSim == SIM_CAPTURE) {
        DrawText("INTERVENTION TERMINEE : voleur attrape.",
                 40, 120, 26, RED);
    }

    dessinerGrapheMission(g);

    panneauInfo();
    legende();

    int x = GetScreenWidth() - 315;
    int y = 340;

    DrawText("SIMULATION", x, y, 24, MAROON);
    DrawText(TextFormat("Tour : %d", numeroTour), x, y + 45, 18, BLACK);
    DrawText(TextFormat("Police : V%d", policeID), x, y + 75, 18, COULEUR_POLICE);
    DrawText(TextFormat("Suspect : V%d", suspectID), x, y + 105, 18, RED);
    DrawText(TextFormat("Etape chemin : %d", etapeChemin), x, y + 135, 18, BLACK);

    if (etatSim == SIM_PARCOURS) {
        DrawText("Etat : poursuite + pose cameras", x, y + 180, 18, BLACK);
    } else if (etatSim == SIM_REPERE) {
        DrawText("Etat : suspect repere par camera", x, y + 180, 18, RED);
    } else if (etatSim == SIM_INVENTAIRE) {
        DrawText("Etat : inventaire optimal", x, y + 180, 18, DARKPURPLE);
    } else if (etatSim == SIM_RETOUR_BASE) {
        DrawText("Etat : transport du materiel", x, y + 180, 18, DARKBLUE);
    } else if (etatSim == SIM_CAPTURE) {
        DrawText("Etat : capture terminee", x, y + 180, 18, RED);
    }

    Rectangle r = bouton(x, y + 250, 230, 50, "Recommencer");

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
        CheckCollisionPointRec(GetMousePosition(), r)) {
        resetSimulationComplete(g);
    }
}

/* ========================= */
/* FONCTION PRINCIPALE */
/* ========================= */

void lancerAffichageGraphique(Graphe *g) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(GetMonitorWidth(0), GetMonitorHeight(0), "Falcon Eye - Interface graphique");

    ToggleFullscreen();

    SetTargetFPS(60);

    initialiserPositions(g);

    ViewMode view = VIEW_MENU;

    while (!WindowShouldClose()) {
        Vector2 souris = GetMousePosition();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (view == VIEW_MENU) {
            dessinerMenu();

            int w = GetScreenWidth();

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (CheckCollisionPointRec(souris, (Rectangle){w / 2 - 220, 220, 440, 55})) {
                    resetAffichageSimulation(g);
                    view = VIEW_GRAPHE;
                }
                else if (CheckCollisionPointRec(souris, (Rectangle){w / 2 - 220, 295, 440, 55})) {
                    resetAffichageSimulation(g);
                    preparerMission1(g);
                    view = VIEW_MISSION1;
                }
                else if (CheckCollisionPointRec(souris, (Rectangle){w / 2 - 220, 370, 440, 55})) {
                    resetAffichageSimulation(g);
                    view = VIEW_MISSION2;
                }
                else if (CheckCollisionPointRec(souris, (Rectangle){w / 2 - 220, 445, 440, 55})) {
                    resetAffichageSimulation(g);
                    view = VIEW_MISSION3;
                }
                else if (CheckCollisionPointRec(souris, (Rectangle){w / 2 - 220, 520, 440, 55})) {
                    resetAffichageSimulation(g);
                    preparerMission1(g);
                    view = VIEW_SIMULATION;
                }
                else if (CheckCollisionPointRec(souris, (Rectangle){w / 2 - 220, 620, 440, 55})) {
                    break;
                }
            }
        }

        else if (view == VIEW_GRAPHE) {
            dessinerTitreCarte("GRAPHE COMPLET");
            dessinerGrapheSimple(g);
            panneauInfo();
            legende();
            retourBouton(&view, g);
        }

        else if (view == VIEW_MISSION1) {
            afficherMission1(g);
            retourBouton(&view, g);
        }

        else if (view == VIEW_MISSION2) {
            afficherMission2(g);
            retourBouton(&view, g);
        }

        else if (view == VIEW_MISSION3) {
            afficherMission3();
            retourBouton(&view, g);
        }

        else if (view == VIEW_SIMULATION) {
            afficherSimulationComplete(g);
            retourBouton(&view, g);
        }

        EndDrawing();
    }

    CloseWindow();
}