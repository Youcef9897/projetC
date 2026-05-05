/*
 * graphe.c - Fonctions de gestion du graphe routier (création, manipulation, affichage)
 *
 * Ce fichier contient les fonctions pour créer, initialiser, manipuler et afficher
 * un graphe orienté représentant un réseau de routes et de villes.
 *
 * Chaque fonction est commentée pour faciliter la compréhension.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graphe.h"


// Créer un graphe orienté avec toutes les routes et les intersections
Graphe *creerGraphe(int nb_sommets) {
    Graphe *g = malloc(sizeof(Graphe));
    if (g == NULL) return NULL; // Vérification de l'allocation mémoire

    g->nb_sommets = nb_sommets;
    g-> listeSommets = NULL; // Initialisation de la liste des sommets
    return g;
    }


// Libère toute la mémoire associée au graphe
void libererGraphe(Graphe *g) {
    if (g == NULL) return;
    Sommet *s = g->listeSommets;
    while (s != NULL) {
        Arc *a = s->routes;
        while (a != NULL) {
            Arc *tmpArc = a;
            a = a->suivant;
            free(tmpArc);
        }
        Sommet *tmpSommet = s;
        s = s->suivant;
        free(tmpSommet);
    }
    free(g);
}


// Crée un sommet avec un identifiant et un nom
Sommet *creerSommet(int id, char *nom){
    Sommet* s = malloc(sizeof(*s));
    s->ID = id;
    strncpy(s->nom, nom, sizeof(s->nom)-1);
    s->nom[sizeof(s->nom)-1] = '\0'; // Assurer la terminaison de la chaîne
    s->routes = NULL;
    s->CamPlace = false;
    s->suivant = NULL;
    return s;
}


void afficherSommets(Sommet *sommets){
    Sommet *s = sommets;
    while (s != NULL) {
        printf("V%d - %s", s->ID, s->nom);
        if (s->CamPlace) {
            printf(" [Caméra]");
        }
        printf("\n");
        s = s->suivant;
    }
}


// Ajoute ou modifie un arc entre deux sommets
void ajouterArc(Sommet *source, Sommet *destination, int distance, int vitesseLim, int etatTrafic){ // Ajoute une route entre deux sommets avec ses caractéristiques
    Arc* a = malloc(sizeof(*a));
    a->distance = distance;
    a->vitesseLim = vitesseLim;
    a->etatTrafic = etatTrafic;
    a->destination = destination;
    a->temps = calculTemps(a);
    a->estCouvert = false;
    a->suivant = source->routes; // Insérer en tête de la liste des arcs sortants
    source->routes = a;
}

void afficherArcs(Arc *arcs){
    Arc *a = arcs;
    while (a != NULL) {
        printf("  -> vers %s (distance: %dm | vitesse: %dkm/h | trafic: %d | temps: %.2fs)\n", a->destination->nom, a->distance, a->vitesseLim, a->etatTrafic, a->temps);
        a = a->suivant; 
    }
}


double calculTemps(Arc *arc){
    if(arc == NULL || arc->vitesseLim <= 0) {
        return -1;
    }
    return ((double)arc->distance * arc->etatTrafic) / (arc->vitesseLim * 1000.0 / 3600.0); // Convertir km/h en m/s et calculer le temps
    }


// Affiche le graphe sous forme de schéma ASCII (toutes les routes existantes)
void afficherGraphe(Graphe *graphe){
    Sommet *s = graphe->listeSommets;
    while (s != NULL) {
        printf("Sommet %d: %s\n", s->ID, s->nom);
        afficherArcs(s->routes);
        s = s->suivant;
    }
}


