#ifndef MISSION1_H
#define MISSION1_H

#include "graphe.h"

void mettreAJourSuspectAleatoire(Graphe *graphe, Suspect *suspect, int idPolice);
void mettreAJourPolice(Police *police, Sommet *nouvellePosition);

Chemin Dijkstra(Graphe *graphe, Police *police, Suspect *suspect);
Chemin AEtoile(Graphe *graphe, Police *police, Suspect *suspect);
Chemin PlusCourtChemin(Chemin dijkstra, Chemin aEtoile);
void simulationDynamiqueMission1 (Graphe *graphe, Sommet *basePolice, int nbToursMax);
void afficherChemin(Chemin *chemin, Graphe *graphe);

#endif