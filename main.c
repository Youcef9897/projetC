#include <stdio.h>
#include "raylib.h"
#include "graphe.h"
#include "mission1.h"
#include "mission2.h"
#include "mission3.h"
#include "simulation.h"
#include "affichage.h"
#include <time.h>


void afficherMenuPrincipal() {
    printf("\n===== MENU FALCON EYE =====\n");
    printf("1. Afficher les sommets\n");
    printf("2. Afficher le graphe complet\n");
    printf("3. Mission 1 : poursuite police / suspect\n");
    printf("4. Mission 2 : placement des caméras\n");
    printf("5. Mission 3 : inventaire de la police\n");
    printf("6. Simulation complete\n");
    printf("7. Affichage graphique\n");
    printf("0. Quitter\n");
    printf("Votre choix : ");
}


void menuMission1(Graphe *g, Sommet *basePolice) {
    simulationDynamiqueMission1(g, basePolice, 10); // Simuler 10 tours de poursuite
}


int main() {

    printf("===== TEST DU GRAPHE FALCON EYE =====\n\n");

    Graphe *g = creerGraphe(30); // Création d'un graphe avec 30 sommets (places)

    Sommet *v0  = creerSommet(0, "Plaza Mariano Moreno");
    Sommet *v1  = creerSommet(1, "Plaza General San ");
    Sommet *v2  = creerSommet(2, "Plaza Juan J. Paso");
    Sommet *v3  = creerSommet(3, "Plaza Maximo Paz");
    Sommet *v4  = creerSommet(4, "Plaza Islas Malvinas");
    Sommet *v5  = creerSommet(5, "Plaza Italia");
    Sommet *v6  = creerSommet(6, "Plaza Dardo Rocha");
    Sommet *v7  = creerSommet(7, "Plaza Manuel Belgrano");
    Sommet *v8  = creerSommet(8, "Plaza General Olazabal");
    Sommet *v9  = creerSommet(9, "Plaza Miguel de Azcuenaga");  
    Sommet *v10 = creerSommet(10, "Plaza General Martin Miguel");
    Sommet *v11 = creerSommet(11, "Plaza Valentin Alsina");
    Sommet *v12 = creerSommet(12, "Plaza Adolfo Alsina");
    Sommet *v13 = creerSommet(13, "Plaza Sarmiento");
    Sommet *v14 = creerSommet(14, "Plaza Espana");
    Sommet *v15 = creerSommet(15, "Plaza Domingo Matheu");
    Sommet *v16 = creerSommet(16, "Parque Saavedra");
    Sommet *v17 = creerSommet(17, "Parque Juan J. Castelli");
    Sommet *v18 = creerSommet(18, "Plaza 19 de Noviembre");
    Sommet *v19 = creerSommet(19, "Parque Juan Vucetich");
    Sommet *v20 = creerSommet(20, "Plaza Juan domingo Peron");
    Sommet *v21 = creerSommet(21, "Parque Manuel Alberti");
    Sommet *v22 = creerSommet(22, "Plaza Hipolito Yrigoyen");
    Sommet *v23 = creerSommet(23, "Plaza Rivadavia");
    Sommet *v24 = creerSommet(24, "Meridiano V");
    Sommet *v25 = creerSommet(25, "Cementerio Municipal");
    Sommet *v26 = creerSommet(26, "Hipodromo");
    Sommet *v27 = creerSommet(27, "Jardin Zoologico");
    Sommet *v28 = creerSommet(28, "Estadio Unico");
    Sommet *v29 = creerSommet(29, "Estacion FFCC Roca");

    /* Chaînage des sommets dans le graphe */
    g->listeSommets = v0;
    v0->suivant = v1;
    v1->suivant = v2;
    v2->suivant = v3;
    v3->suivant = v4;
    v4->suivant = v5;
    v5->suivant = v6;
    v6->suivant = v7;
    v7->suivant = v8;
    v8->suivant = v9;
    v9->suivant = v10;
    v10->suivant = v11;
    v11->suivant = v12;
    v12->suivant = v13;
    v13->suivant = v14;
    v14->suivant = v15;
    v15->suivant = v16;
    v16->suivant = v17;
    v17->suivant = v18;
    v18->suivant = v19;
    v19->suivant = v20;
    v20->suivant = v21;
    v21->suivant = v22;
    v22->suivant = v23;
    v23->suivant = v24;
    v24->suivant = v25;
    v25->suivant = v26;
    v26->suivant = v27;
    v27->suivant = v28;
    v28->suivant = v29;
    v29->suivant = NULL;

// Ajout des arcs (routes) entre les sommets (places)

// les connextions autour de la place centrale (V0) : double sens
// V0 <-> V1 : Plaza General San Martin
ajouterArc(v0, v1, 800, 60, NORMAL);
ajouterArc(v1, v0, 800, 60, NORMAL);

// V0 <-> V4 : Plaza Islas Malvinas
ajouterArc(v0, v4, 900, 50, NORMAL);
ajouterArc(v4, v0, 900, 50, NORMAL);

// V0 <-> V2 : Plaza Juan J. Paso
ajouterArc(v0, v2, 750, 50, NORMAL);
ajouterArc(v2, v0, 750, 50, NORMAL);

// V0 <-> V3 : Plaza Maximo Paz
ajouterArc(v0, v3, 900, 50, NORMAL);
ajouterArc(v3, v0, 900, 50, NORMAL);

// V0 <-> V5 : Plaza Italia
ajouterArc(v0, v5, 1000, 60, NORMAL);
ajouterArc(v5, v0, 1000, 60, NORMAL);

// V0 <-> V6 : Plaza Dardo Rocha
ajouterArc(v0, v6, 600, 40, NORMAL);
ajouterArc(v6, v0, 600, 40, NORMAL);

// V0 <-> V11 : Plaza Valentin Alsina
ajouterArc(v0, v11, 800, 50, NORMAL);
ajouterArc(v11, v0, 800, 50, NORMAL);

// V0 <-> V9 : Plaza Miguel de Azcuenaga
ajouterArc(v0, v9, 950, 50, NORMAL);
ajouterArc(v9, v0, 950, 50, NORMAL);



// les connexions autour de la place V1 : double sens
// v1 <-> V6 : Plaza Dardo Rocha
ajouterArc(v1, v6, 600, 40, NORMAL);
ajouterArc(v6, v1, 600, 40, NORMAL);

// v1 <-> v5 : Plaza Italia
ajouterArc(v1, v5, 800, 50, NORMAL);
ajouterArc(v5, v1, 800, 50, NORMAL);

// V1 <-> V23 : Plaza Rivadavia
ajouterArc(v1, v23, 1000, 60, NORMAL);
ajouterArc(v23, v1, 1000, 60, NORMAL);


// les connexions autour de la place V2 : double sens
// V2 <-> V7 : Plaza Manuel Belgrano
ajouterArc(v2, v7, 650, 50, NORMAL);
ajouterArc(v7, v2, 650, 50, NORMAL);

// V2 <-> V9 : Plaza Miguel de Azcuenaga
ajouterArc(v2, v9, 800, 50, NORMAL);
ajouterArc(v9, v2, 800, 50, NORMAL);


// les connexions autour de la place V3 : double sens
// V3 <-> V11 : Plaza Valentin Alsina
ajouterArc(v3, v11, 850, 50, NORMAL);
ajouterArc(v11, v3, 850, 50, NORMAL);

// V3 <-> V16 : Parque Saavedra
ajouterArc(v3, v16, 1200, 60, NORMAL);
ajouterArc(v16, v3, 1200, 60, NORMAL);

// les connexions autour de la place V4 : double sens
// V4 <-> V11 : Plaza Valentin Alsina
ajouterArc(v4, v11, 850, 50, NORMAL);
ajouterArc(v11, v4, 850, 50, NORMAL);

// V4 <-> V9 : Plaza Miguel de Azcuenaga
ajouterArc(v4, v9, 700, 50, NORMAL);
ajouterArc(v9, v4, 700, 50, NORMAL);

// V4 <-> V19 : Plaza Hipolito Yrigoyen
ajouterArc(v4, v19, 1000, 50, NORMAL);
ajouterArc(v19, v4, 1000, 50, NORMAL);


// les connexions autour de la place V5 : double sens
// V5 <-> V7 : Plaza Manuel Belgrano
ajouterArc(v5, v7, 750, 50, NORMAL);
ajouterArc(v7, v5, 750, 50, NORMAL);

// V5 <-> V23 : Plaza Rivadavia
ajouterArc(v5, v23, 1000, 50, NORMAL);
ajouterArc(v23, v5, 1000, 50, NORMAL);

// V5 <-> V12 : Plaza Adolfo Alsina
ajouterArc(v5, v12, 850, 50, NORMAL);
ajouterArc(v12, v5, 850, 50, NORMAL);

// V5 <-> V8 : Plaza Olazabal
ajouterArc(v5, v8, 650, 50, NORMAL);
ajouterArc(v8, v5, 650, 50, NORMAL);


// les connexions autour de la place V6 : double sens
// V6 <-> V16 : Parque Saavedra
ajouterArc(v6, v16, 900, 50, NORMAL);
ajouterArc(v16, v6, 900, 50, NORMAL);

// V6 <-> V14 : Plaza Espana
ajouterArc(v6, v14, 700, 40, NORMAL);
ajouterArc(v14, v6, 700, 40, NORMAL);

// V6 <-> V15 : Plaza Domingo Matheu
ajouterArc(v6, v15, 1100, 50, NORMAL);
ajouterArc(v15, v6, 1100, 50, NORMAL);

// V6 <-> V23 : Plaza Rivadavia
ajouterArc(v6, v23, 850, 50, NORMAL);
ajouterArc(v23, v6, 850, 50, NORMAL);


// les connexions autour de la place V7 : double sens
// V7 <-> V9 : Plaza Miguel de Azcuenaga
ajouterArc(v7, v9, 650, 50, NORMAL);
ajouterArc(v9, v7, 650, 50, NORMAL);

// V7 <-> V10 : Plaza General Martin Miguel de Guemes
ajouterArc(v7, v10, 800, 50, NORMAL);
ajouterArc(v10, v7, 800, 50, NORMAL);

// V7 <-> V8 : Plaza General Olazabal
ajouterArc(v7, v8, 550, 40, NORMAL);
ajouterArc(v8, v7, 550, 40, NORMAL);


// les connexions autour de la place V8 : double sens
// V8 <-> V12 : Plaza Adolfo Alsina
ajouterArc(v8, v12, 700, 50, NORMAL);
ajouterArc(v12, v8, 700, 50, NORMAL);


// les connexions autour de la place V9 : double sens
// V9 <-> V19 : Plaza Hipolito Yrigoyen
ajouterArc(v9, v19, 800, 50, NORMAL);
ajouterArc(v19, v9, 800, 50, NORMAL);

// V9 <-> V18 : Plaza 19 de Noviembre
ajouterArc(v9, v18, 1100, 50, NORMAL);
ajouterArc(v18, v9, 1100, 50, NORMAL);

// V9 <-> V21 : Parque Alberti
ajouterArc(v9, v21, 1200, 60, NORMAL);
ajouterArc(v21, v9, 1200, 60, NORMAL);


// les connexions autour de la place V10 : double sens
// V10 <-> V21 : Parque Manuel Alberti
ajouterArc(v10, v21, 1000, 60, NORMAL);
ajouterArc(v21, v10, 1000, 60, NORMAL);


// les connexions autour de la place V11 : double sens
// V11 <-> V20 : Plaza Juan Domingo Peron
ajouterArc(v11, v20, 800, 50, NORMAL);
ajouterArc(v20, v11, 800, 50, NORMAL);

// V11 <-> V17 : Parque Juan J. Castelli
ajouterArc(v11, v17, 600, 40, NORMAL);
ajouterArc(v17, v11, 600, 40, NORMAL);

// V11 <-> V13 : Plaza Sarmiento
ajouterArc(v11, v13, 700, 50, NORMAL);
ajouterArc(v13, v11, 700, 50, NORMAL);

// V11 <-> V19 : Parque Juan Vucetich
ajouterArc(v11, v19, 1100, 60, NORMAL);
ajouterArc(v19, v11, 1100, 60, NORMAL);


// les connexions autour de la place V12 : double sens
// V12 <-> V23 : Plaza Rivadavia
ajouterArc(v12, v23, 900, 50, NORMAL);
ajouterArc(v23, v12, 900, 50, NORMAL);

// V12 <-> V29 : Estacion FFCC Roca
ajouterArc(v12, v29, 1300, 60, NORMAL);
ajouterArc(v29, v12, 1300, 60, NORMAL);


// les connexions autour de la place V13 : double sens
// V13 <-> V16 : liaison urbaine proche vers Parque Saavedra
ajouterArc(v13, v16, 700, 50, NORMAL);
ajouterArc(v16, v13, 700, 50, NORMAL);

// V13 <-> V17 : liaison plus directe vers Parque Castelli
ajouterArc(v13, v17, 800, 50, NORMAL);
ajouterArc(v17, v13, 800, 50, NORMAL);

// V13 <-> V24 : liaison plus longue vers Meridiano V
ajouterArc(v13, v24, 1200, 60, NORMAL);
ajouterArc(v24, v13, 1200, 60, NORMAL);


// les connexions autour de la place V14 : double sens
// V14 <-> V16 : Parque Saavedra
ajouterArc(v14, v16, 650, 50, NORMAL);
ajouterArc(v16, v14, 650, 50, NORMAL);

// V14 <-> V15 : Plaza Domingo Matheu
ajouterArc(v14, v15, 800, 50, NORMAL);
ajouterArc(v15, v14, 800, 50, NORMAL);


// les connexions autour de la place V15 : double sens
// V15 <-> V22 : Plaza Hipolito Yrigoyen
ajouterArc(v15, v22, 900, 50, NORMAL);
ajouterArc(v22, v15, 900, 50, NORMAL);


// les connexions autour de la place V17 : double sens
// V17 <-> V20 : Plaza Juan Domingo Peron
ajouterArc(v17, v20, 750, 50, NORMAL);
ajouterArc(v20, v17, 750, 50, NORMAL);

// V17 <-> V25 : Cementerio Municipal
ajouterArc(v17, v25, 1400, 60, NORMAL);
ajouterArc(v25, v17, 1400, 60, NORMAL);


// les connexions autour de la place V18 : double sens
// V18 <-> V21 : Parque Manuel Alberti
ajouterArc(v18, v21, 1100, 50, NORMAL);
ajouterArc(v21, v18, 1100, 50, NORMAL);

// V18 <-> V19 : Plaza Hipolito Yrigoyen
ajouterArc(v18, v19, 800, 50, NORMAL);
ajouterArc(v19, v18, 800, 50, NORMAL);


// les connexions autour de la place V20 : double sens
// V20 <-> V19 : Plaza Hipolito Yrigoyen
ajouterArc(v20, v19, 700, 50, NORMAL);
ajouterArc(v19, v20, 700, 50, NORMAL);


// les connexions autour de la place V21 : double sens
// V21 <-> V28 : Estadio Unico
ajouterArc(v21, v28, 1600, 60, NORMAL);
ajouterArc(v28, v21, 1600, 60, NORMAL);


// les connexions autour de la place V22 : double sens
// V22 <-> V23 : Plaza Rivadavia
ajouterArc(v22, v23, 850, 50, NORMAL);
ajouterArc(v23, v22, 850, 50, NORMAL);

// les connexions autour de la place V24 : double sens
// V24 <-> V25 : Cementerio Municipal
ajouterArc(v24, v25, 1500, 60, NORMAL);
ajouterArc(v25, v24, 1500, 60, NORMAL);

// les connexions autour de la place V26 : double sens
// V26 <-> V29 : Estacion FFCC Roca
ajouterArc(v26, v29, 900, 50, NORMAL);
ajouterArc(v29, v26, 900, 50, NORMAL);

// les connexions autour de la place V27 : double sens
// V27 <-> V29 : Estacion FFCC Roca
ajouterArc(v27, v29, 600, 40, NORMAL);
ajouterArc(v29, v27, 600, 40, NORMAL);


int choix;

do {
    afficherMenuPrincipal();
    scanf("%d", &choix);

    switch (choix) {
        case 1:
            printf("\n===== AFFICHAGE DES SOMMETS =====\n");
            afficherSommets(g->listeSommets);
            break;

        case 2:
            printf("\n===== AFFICHAGE DU GRAPHE COMPLET =====\n");
            afficherGraphe(g);
            break;

        case 3:
            menuMission1(g, v0); // V0 = base police
            break;

        case 4:
            placerUneCamera(g);
            afficherCameras(g);
            break;
        
        case 5:
            mission3Inventaire();
            break;

        case 6:
            simulationComplete(g, v0, 10);
            break;

        case 7:
            lancerAffichageGraphique(g);
            break;

        case 0:
            printf("\nFermeture du programme...\n");
            break;

        default:
            printf("\nChoix invalide.\n");
    }

} while (choix != 0);

libererGraphe(g);

return 0;
}


