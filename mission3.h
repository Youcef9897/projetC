#ifndef MISSION3_H
#define MISSION3_H

#define CAPACITE_MAX 40
#define NB_OBJETS 8

typedef struct {
    char nom[50];
    int poids;
    int valeurTactique;
    int selectionne;
} ObjetTactique;

void mission3Inventaire(void);

#endif