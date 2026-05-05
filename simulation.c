#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "simulation.h"
#include "graphe.h"
#include "mission1.h"
#include "mission2.h"
#include "mission3.h"

static Sommet *trouverSommetParIDSimulation(Graphe *graphe, int id) {
    Sommet *s = graphe->listeSommets;

    while (s != NULL) {
        if (s->ID == id) {
            return s;
        }
        s = s->suivant;
    }

    return NULL;
}

static void placerCamerasSurChemin(Graphe *graphe, Chemin *chemin) {
    for (int i = 0; i < chemin->taille; i++) {
        Sommet *s = trouverSommetParIDSimulation(graphe, chemin->sommets[i]);

        if (s != NULL) {
            s->CamPlace = true;
            printf("Camera placee sur : V%d - '%s' par un policier\n", s->ID, s->nom);
        }
    }
}

static bool suspectDetecteParCamera(Suspect *suspect) {
    if (suspect == NULL || suspect->emplacement == NULL) {
        return false;
    }

    return suspect->emplacement->CamPlace;
}

void simulationComplete(Graphe *graphe, Sommet *basePolice, int nbToursMax) {
    if (graphe == NULL || basePolice == NULL) {
        printf("Erreur : graphe ou base police invalide.\n");
        return;
    }

    Police police;
    Suspect suspect;

    police.emplacement = basePolice;
    police.inventaire = 0;

    printf("\n===== SIMULATION COMPLETE FALCON EYE =====\n");
    printf("Base police : V%d - %s\n",
           police.emplacement->ID,
           police.emplacement->nom);

    for (int tour = 1; tour <= nbToursMax; tour++) {
        printf("\n========== TOUR %d ==========\n", tour);

        mettreAJourSuspectAleatoire(graphe, &suspect, police.emplacement->ID);

        printf("Position police : V%d - %s\n",
               police.emplacement->ID,
               police.emplacement->nom);

        printf("Suspect detecte par helicoptere : V%d - %s\n",
               suspect.emplacement->ID,
               suspect.emplacement->nom);

        if (suspectDetecteParCamera(&suspect)) {
            printf("\nCAMERA ACTIVE !\n");
            printf("Le suspect est detecte sur un sommet deja surveille.\n");
            printf("Preparation de l'intervention avec l'inventaire optimal...\n");

            mission3Inventaire();

            printf("\nINTERVENTION TERMINEE : suspect capture.\n");
            return;
        }

        Chemin chemin = Dijkstra(graphe, &police, &suspect);

        printf("\nChemin calcule avec Dijkstra :\n");
        afficherChemin(&chemin, graphe);

        if (chemin.taille == 0) {
            printf("Aucun chemin possible. Fin de simulation.\n");
            return;
        }

        printf("\nPlacement des cameras sur le chemin parcouru :\n");
        placerCamerasSurChemin(graphe, &chemin);

        int dernierID = chemin.sommets[chemin.taille - 1];
        Sommet *nouvellePositionPolice = trouverSommetParIDSimulation(graphe, dernierID);

        if (nouvellePositionPolice == NULL) {
            printf("Erreur : position finale police introuvable.\n");
            return;
        }

        mettreAJourPolice(&police, nouvellePositionPolice);

        printf("\nNouvelle position police : V%d - %s\n",
               police.emplacement->ID,
               police.emplacement->nom);

        printf("Fin du tour %d.\n", tour);
    }

    printf("\nSimulation terminee : suspect non capture apres %d tours.\n", nbToursMax);
}