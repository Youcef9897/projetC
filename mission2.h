#ifndef MISSION2_H
#define MISSION2_H

#include <stdbool.h>
#include "graphe.h"

bool placerUneCamera(Graphe *graphe);
bool ArcsTousCouverts(Graphe *graphe);
void placerCam(Graphe *graphe);
void afficherCameras(Graphe *graphe);

#endif