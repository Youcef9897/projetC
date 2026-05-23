# Falcon Eye - Projet C / Théorie des Graphes

## Présentation du projet

Falcon Eye est un projet développé en langage C dans le cadre du cours de théorie des graphes.

Le projet modélise une ville sous forme de graphe orienté représentant un réseau urbain de surveillance et d’intervention policière.

Les sommets représentent des lieux importants de la ville (places, parcs, intersections) et les arcs représentent les routes entre ces lieux.

Chaque route possède :
- une distance ;
- une vitesse limite ;
- un état du trafic ;
- un temps estimé de parcours.

Le projet combine :
- théorie des graphes ;
- algorithmes de plus court chemin ;
- optimisation ;
- programmation dynamique ;
- simulation interactive ;
- interface graphique avec Raylib.


# Fonctionnalités principales

## Mission 1 : poursuite police / suspect

Simulation dynamique d’une poursuite entre une voiture de police et un suspect.

Fonctionnement :
1. Le suspect apparaît sur un sommet aléatoire ;
2. L’algorithme de Dijkstra calcule le plus court chemin ;
3. La police suit le chemin optimal ;
4. La position de la police est mise à jour à chaque tour.

Algorithmes utilisés :
- Dijkstra ;


## Mission 2 : placement des caméras

Cette mission permet de couvrir les routes du graphe grâce à des caméras de surveillance.

Principe :
- Une route est considérée surveillée si au moins un des deux sommets possède une caméra.
- L’algorithme choisit progressivement les meilleurs sommets afin de couvrir un maximum de routes.

Objectif :
- Minimiser le nombre de caméras ;
- Maximiser la couverture du réseau routier.


## Mission 3 : inventaire tactique

Cette mission utilise un algorithme de sac à dos dynamique.

Objectif :
- Sélectionner les meilleurs équipements tactiques ;
- Respecter une capacité maximale de 40 kg ;
- Maximiser la valeur tactique totale.

Objets disponibles :
- bandes à pointes ;
- drone tactique ;
- brouilleur de signal ;
- trousse médicale ;
- gaz lacrymogène ;
- scanner portable ;
- etc.

Algorithme utilisé :
- Programmation dynamique (problème du Knapsack / sac à dos).


## Simulation complète

La simulation complète combine les trois missions.

Déroulement :
1. La police poursuit le suspect ;
2. Des caméras sont placées progressivement sur les sommets parcourus ;
3. Si la position finale du suspect correspond à une zone déjà surveillée, le suspect est repéré ;
4. L’inventaire optimal est préparé ;
5. Une intervention finale est déclenchée ;
6. Le suspect est capturé.

Cette simulation relie :
- poursuite dynamique ;
- surveillance urbaine ;
- optimisation tactique.


# Structure du projet
.
├── main.c
├── graphe.h
├── graphe.c
├── mission1.h
├── mission1.c
├── mission2.h
├── mission2.c
├── mission3.h
├── mission3.c
├── simulation.h
├── simulation.c
├── affichage.h
├── affichage.c
├── Makefile
└── README.md

# Représentation du graphe

Le graphe est représenté par : des listes chaînées ; des structures dynamiques. 

Structure Sommet : 

Chaque sommet contient : un identifiant ; un nom ; une liste de routes sortantes ; un état de surveillance caméra.

Structure Arc : Chaque arc contient : une distance ; une vitesse limite ; un état du trafic ; un temps de parcours ; un sommet destination.

Calcul du temps de trajet : temps = distance × trafic / vitesse

Le trafic influence directement la durée du trajet : LEGER ; NORMAL ; LOURD.

Interface graphique : Une interface graphique a été développée avec Raylib.

Fonctionnalités : affichage du graphe ; affichage des routes ; animation des chemins calculés ; visualisation des caméras ; simulation complète interactive.

Code couleur :
- Violet : police ;
- Rouge : suspect ;
- Vert : caméra ;
- Orange : chemin optimal ;
- Gris : route normale.

Compilation :
Le projet utilise une compilation modulaire avec Makefile.
- Compilation : make
- Exécution : ./falcon_eye
- Nettoyage : make clean

Bibliothèques utilisées : 
Le projet utilise : le langage C ; Raylib ; la bibliothèque mathématique standard ;
les listes chaînées ; la programmation dynamique.

Bibliothèques liées : -lraylib -lm -lpthread -ldl -lrt -lX11

Menu principal :

Le programme propose un menu console :

1. Afficher les sommets
2. Afficher le graphe complet
3. Mission 1 : poursuite police / suspect
4. Mission 2 : placement des caméras
5. Mission 3 : inventaire de la police
6. Simulation complète
7. Affichage graphique
0. Quitter

Concepts de théorie des graphes utilisés :

Le projet utilise plusieurs notions importantes : graphes orientés ; listes d’adjacence ; plus court chemin ; couverture de sommets ; optimisation combinatoire ; programmation dynamique ; simulation dynamique.
