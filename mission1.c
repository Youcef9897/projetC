#include "mission1.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INF 1000000000

static Sommet *trouverSommetParID(Graphe *graphe, int id) {
    Sommet *s = graphe->listeSommets;

    while (s != NULL) {
        if (s->ID == id) {
            return s;
        }
        s = s->suivant;
    }

    return NULL;
}

void mettreAJourSuspectAleatoire(Graphe *graphe, Suspect *suspect, int idPolice) {
    int id;

    do {
        id = rand() % graphe->nb_sommets;
    } while (id == idPolice);

    suspect->emplacement = trouverSommetParID(graphe, id);
    suspect->suivant = NULL;
}

void mettreAJourPolice(Police *police, Sommet *nouvellePosition) {
    police->emplacement = nouvellePosition;
}

Chemin Dijkstra(Graphe *graphe, Police *police, Suspect *suspect) {
    int n = graphe->nb_sommets;
    double distance[MAX_SOMMETS];
    int precedent[MAX_SOMMETS];
    bool visite[MAX_SOMMETS];

    Chemin chemin;
    chemin.taille = 0;
    chemin.tempsTotal = 0;

    for (int i = 0; i < n; i++) {
        distance[i] = INF;
        precedent[i] = -1;
        visite[i] = false;
    }

    int depart = police->emplacement->ID;
    int arrivee = suspect->emplacement->ID;

    distance[depart] = 0;

    for (int i = 0; i < n; i++) {
        int u = -1;
        double min = INF;

        for (int j = 0; j < n; j++) {
            if (!visite[j] && distance[j] < min) {
                min = distance[j];
                u = j;
            }
        }
        
        if (u == -1) break;
        if (u == arrivee) break;

        visite[u] = true;

        Sommet *sommetU = trouverSommetParID(graphe, u);
        if (sommetU == NULL) continue;

        Arc *arc = sommetU->routes;

        while (arc != NULL) {
            int v = arc->destination->ID;
            double nouveauTemps = distance[u] + arc->temps;

            if (!visite[v] && nouveauTemps < distance[v]) {
                distance[v] = nouveauTemps;
                precedent[v] = u;
            }

            arc = arc->suivant;
        }
    }

    if (distance[arrivee] >= INF) {
        printf("Aucun chemin trouve entre la police et le suspect.\n");
        return chemin;
    }

    int temp[MAX_SOMMETS];
    int count = 0;
    int courant = arrivee;

    while (courant != -1) {
        temp[count++] = courant;
        courant = precedent[courant];
    }

    for (int i = count - 1; i >= 0; i--) {
        chemin.sommets[chemin.taille++] = temp[i];
    }

    chemin.tempsTotal = distance[arrivee];

    return chemin;
}

Chemin AEtoile(Graphe *graphe, Police *police, Suspect *suspect) {
    /*
     * Version simplifiée :
     * Sans coordonnées géographiques, A* n’a pas encore d’heuristique fiable.
     * On utilise donc Dijkstra comme base équivalente.
     */
    return Dijkstra(graphe, police, suspect);
}

Chemin PlusCourtChemin(Chemin dijkstra, Chemin aEtoile) {
    if (aEtoile.tempsTotal > 0 && aEtoile.tempsTotal < dijkstra.tempsTotal) {
        return aEtoile;
    }

    return dijkstra;
}

void afficherChemin(Chemin *chemin, Graphe *graphe) {
    if (chemin->taille == 0) {
        printf("Aucun chemin a afficher.\n");
        return;
    }

    printf("Chemin : ");

    for (int i = 0; i < chemin->taille; i++) {
        Sommet *s = trouverSommetParID(graphe, chemin->sommets[i]);

        if (s != NULL) {
            printf("V%d - %s", s->ID, s->nom);
        }

        if (i < chemin->taille - 1) {
            printf(" -> ");
        }
    }

    printf("\nTemps total : %.2f secondes\n", chemin->tempsTotal);
}   

void simulationDynamiqueMission1(Graphe *graphe, Sommet *basePolice, int nbToursMax) {
    Police police;
    Suspect suspect;

    bool sommetsFinVisites[MAX_SOMMETS] = {false};

    police.emplacement = basePolice;
    police.inventaire = 0;

    printf("\n===== SIMULATION DYNAMIQUE MISSION 1 =====\n");
    printf("Base police : V%d - %s\n",
           police.emplacement->ID,
           police.emplacement->nom);

    for (int tour = 1; tour <= nbToursMax; tour++) {
        printf("\n----- TOUR %d -----\n", tour);

        mettreAJourSuspectAleatoire(graphe, &suspect, police.emplacement->ID);

        printf("Position police : V%d - %s\n",
               police.emplacement->ID,
               police.emplacement->nom);

        printf("Suspect detecte : V%d - %s\n",
               suspect.emplacement->ID,
               suspect.emplacement->nom);

        Chemin chemin = Dijkstra(graphe, &police, &suspect);

        printf("\nChemin calcule avec Dijkstra :\n");
        afficherChemin(&chemin, graphe);

        if (chemin.taille == 0) {
            printf("Aucun chemin possible. Fin de simulation.\n");
            return;
        }

        int dernierID = chemin.sommets[chemin.taille - 1];

        /*
         * Si la destination finale a déjà été atteinte dans un ancien tour,
         * alors le suspect tombe sur une zone déjà connue/surveillée.
         */
        if (sommetsFinVisites[dernierID]) {
            printf("\nCAPTURE PAR MEMOIRE !\n");
            printf("Le sommet V%d avait deja ete atteint dans un ancien parcours.\n", dernierID);
            return;
        }

        Sommet *nouvellePositionPolice = trouverSommetParID(graphe, dernierID);

        if (nouvellePositionPolice == NULL) {
            printf("Erreur : position finale introuvable.\n");
            return;
        }

        /*
         * On enregistre uniquement le dernier sommet atteint.
         */
        sommetsFinVisites[dernierID] = true;

        /*
         * La police recommencera le tour suivant depuis ce dernier sommet.
         */
        mettreAJourPolice(&police, nouvellePositionPolice);

        printf("\nSommet final marque comme visite : V%d\n", dernierID);
        printf("Nouvelle position police : V%d - %s\n",
               police.emplacement->ID,
               police.emplacement->nom);
    }

    printf("\nSimulation terminee : suspect non capture apres %d tours.\n", nbToursMax);
}

