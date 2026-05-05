#include <stdio.h>
#include <stdbool.h>
#include "mission2.h"

static bool arcEstCouvert(Sommet *source, Arc *arc) {
    return source->CamPlace || arc->destination->CamPlace;
}


bool ArcsTousCouverts(Graphe *graphe) {
    Sommet *s = graphe->listeSommets;

    while (s != NULL) {
        Arc *arc = s->routes;

        while (arc != NULL) {
            if (!arcEstCouvert(s, arc)) {
                return false;
            }

            arc = arc->suivant;
        }

        s = s->suivant;
    }

    return true;
}

static int compterArcsNonCouverts(Sommet *s) {
    int compteur = 0;
    Arc *arc = s->routes;

    while (arc != NULL) {
        if (!arcEstCouvert(s, arc)) {
            compteur++;
        }

        arc = arc->suivant;
    }

    return compteur;
}

void placerCam(Graphe *graphe) {
    printf("\n===== MISSION 2 : PLACEMENT DES CAMERAS =====\n");

    while (!ArcsTousCouverts(graphe)) {
        Sommet *meilleurSommet = NULL;
        int maxArcs = -1;

        Sommet *s = graphe->listeSommets;

        while (s != NULL) {
            if (!s->CamPlace) {
                int nb = compterArcsNonCouverts(s);

                if (nb > maxArcs) {
                    maxArcs = nb;
                    meilleurSommet = s;
                }
            }

            s = s->suivant;
        }

        if (meilleurSommet == NULL || maxArcs <= 0) {
            break;
        }

        meilleurSommet->CamPlace = true;

        printf("Camera placee sur : V%d - %s\n",
               meilleurSommet->ID,
               meilleurSommet->nom);
    }

    if (ArcsTousCouverts(graphe)) {
        printf("\nToutes les routes sont couvertes par au moins une camera.\n");
    } else {
        printf("\nAttention : certaines routes ne sont pas couvertes.\n");
    }
}

void afficherCameras(Graphe *graphe) {
    printf("\n===== CAMERAS PLACEES =====\n");

    Sommet *s = graphe->listeSommets;
    int compteur = 0;

    while (s != NULL) {
        if (s->CamPlace) {
            printf("Camera %d : V%d - %s\n",
                   compteur + 1,
                   s->ID,
                   s->nom);
            compteur++;
        }

        s = s->suivant;
    }

    printf("\nNombre total de cameras : %d\n", compteur);
}