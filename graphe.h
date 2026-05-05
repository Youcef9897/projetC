#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef PROJETC_H_INCLUDED
#define PROJETC_H_INCLUDED
#define MAX_SOMMETS 100
typedef struct Arc Arc;
typedef struct Sommet Sommet;


typedef enum {
    LEGER = 1,                 // Trafic fluide
    NORMAL = 2,                // Trafic moyen
    LOURD = 3                  // Trafic ralenti
} EtatTrafic;


typedef struct Arc Arc;
typedef struct Sommet Sommet;
typedef struct Inventaire Inventaire;


struct Arc {
    int distance;              // Distance entre deux sommets, en mètres
    int vitesseLim;            // Vitesse limite sur cette route, en km/h
    EtatTrafic etatTrafic;     // Etat du trafic : LEGER, NORMAL ou LOURD
    Sommet *destination;       // Sommet d'arrivée de l'arc
    double temps;               // Temps estimé du trajet calculé à partir de la distance, de la vitesse et du trafic
    bool estCouvert;           // Indique si cette route est couverte par une caméra de surveillance
    Arc *suivant;              // Arc suivant dans la liste chaînée des routes du sommet
};


struct Sommet {
    int ID;                    // Identifiant unique du sommet (V0 -> 0, V1 -> 1, etc.)
    char nom[50];              // Nom du lieu ou de l'intersection
    Arc *routes;               // Liste chaînée des arcs sortants depuis ce sommet
    bool CamPlace;             // true si une caméra est placée sur ce sommet
    Sommet *suivant;           // Sommet suivant dans la liste chaînée du graphe
};


typedef struct {
    int sommets[MAX_SOMMETS];  // Tableau contenant les ID des sommets du chemin
    int taille;                // Nombre de sommets dans le chemin
    double tempsTotal;         // Temps total du chemin parcourus en secondes avec l'aglorithme de Dijkstra ou A*
} Chemin;


typedef struct {
    int nb_sommets;            // Nombre total de sommets du graphe
    Sommet *listeSommets;      // Liste chaînée contenant tous les sommets
} Graphe;


typedef struct {
    int inventaire;        // Poids total actuellement transporté (limité par la capacité maximale)
    Sommet *emplacement;   // Position actuelle de la police dans le graphe
    Chemin cheminCourant;  // Chemin optimal calculé pour atteindre le suspect
} Police;


typedef struct {
    Sommet *emplacement; // Position actuelle du suspect dans le graphe
    Sommet *suivant;     // Prochaine position prévue (déplacement simulé)
} Suspect;


struct Inventaire{
    char nom[30];         // Nom de l'objet tactique
    int poids;            // Poids de l'objet en kg (utilisé pour la contrainte du sac)
    int valeurTactique;   // Importance stratégique de l'objet (maximisée par l'algorithme)
    Inventaire *suivant;  // Objet suivant dans la liste chaînée (structure dynamique)
};


// Gestion du graphe
Graphe* creerGraphe(int nb_sommets); 
// Initialise un graphe vide avec un nombre de sommets donné

Sommet* creerSommet(int id, char *nom); 
// Crée un sommet avec un identifiant et un nom

void ajouterArc(Sommet *source, Sommet *destination, int distance, int vitesseLim, int etatTrafic); // Ajoute une route entre deux 
                                                                                                    // sommets avec ses caractéristiques
double calculTemps(Arc *arc); // Calcule le temps de trajet d'un arc selon la distance, la vitesse et le trafic
void afficherArcs(Arc *arcs); // Affiche les arcs sortants d'un sommet
void afficherSommets(Sommet *sommets); // Affiche la liste des sommets du graphe
void afficherGraphe(Graphe *graphe); // Affiche l'ensemble du graphe

void libererGraphe(Graphe *graphe);  // Libère la mémoire utilisée par le graphe

// Mission 1 : plus court chemin
/*
Chemin Dijkstra(Graphe *graphe, Police *police, Suspect *suspect);  // Calcule le plus court chemin entre la police et 
                                                                    // le suspect avec Dijkstra
Chemin AEtoile(Graphe *graphe, Police *police, Suspect *suspect); // Calcule le plus court chemin avec A*
Chemin PlusCourtChemin(Chemin *Dijkstra, Chemin *AEtoile); // Compare deux chemins et retourne celui avec le temps total le plus faible
void mettreAJourSuspect(Graphe *graphe, Suspect *suspect, int idPolice) ; // Met à jour la position du suspect de manière aléatoire, en évitant la position actuelle de la police
void mettreAJourPolice(Police *police, Sommet *nouvellePosition); // Met à jour la position de la police

// Mission 2 : caméras de surveillance
void placerCam(Graphe *g); // Place des caméras sur certains sommets pour couvrir les routes
bool ArcsTousCouverts(Graphe *graphe); // Vérifie si toutes les routes sont couvertes par au moins une caméra

// Mission 3 : inventaire police
void BestFit(Inventaire *inventaire); // Sélectionne les objets tactiques en respectant la limite de poids
void afficherInventaire(Inventaire *inventaire); // Affiche les objets sélectionnés dans l'inventaire
*/
#endif
