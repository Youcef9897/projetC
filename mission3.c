#include <stdio.h>
#include "mission3.h"

#define CAPACITE_MAX 40
#define NB_OBJETS 8

void mission3Inventaire(void) {
    ObjetTactique objets[NB_OBJETS] = {
        {"Bandes a pointes", 12, 85, 0},
        {"Barriere portable", 20, 70, 0},
        {"Drone tactique", 5, 90, 0},
        {"Brouilleur de signal", 10, 60, 0},
        {"Trousse medicale", 3, 30, 0},
        {"Gaz lacrymogene Lanceur", 8, 50, 0},
        {"Robuste Treuil", 15, 40, 0},
        {"Scanner Portable", 2, 25, 0}
    };

    int dp[NB_OBJETS + 1][CAPACITE_MAX + 1] = {0};

    for (int i = 1; i <= NB_OBJETS; i++) {
        for (int w = 0; w <= CAPACITE_MAX; w++) {
            if (objets[i - 1].poids <= w) {
                int prendre = objets[i - 1].valeurTactique
                            + dp[i - 1][w - objets[i - 1].poids];

                int nePasPrendre = dp[i - 1][w];

                dp[i][w] = (prendre > nePasPrendre) ? prendre : nePasPrendre;
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    int w = CAPACITE_MAX;
    int poidsTotal = 0;

    for (int i = NB_OBJETS; i > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            objets[i - 1].selectionne = 1;
            poidsTotal += objets[i - 1].poids;
            w -= objets[i - 1].poids;
        }
    }

    printf("\n===== MISSION 3 : INVENTAIRE POLICE =====\n");
    printf("Capacite maximale : %d kg\n\n", CAPACITE_MAX);

    printf("Objets selectionnes :\n");

    for (int i = 0; i < NB_OBJETS; i++) {
        if (objets[i].selectionne) {
            printf("- %s | %d kg | valeur tactique : %d\n",
                   objets[i].nom,
                   objets[i].poids,
                   objets[i].valeurTactique);
        }
    }

    printf("\nPoids total : %d / %d kg\n", poidsTotal, CAPACITE_MAX);
    printf("Valeur tactique totale : %d\n", dp[NB_OBJETS][CAPACITE_MAX]);
    printf("Poids restant : %d kg\n", CAPACITE_MAX - poidsTotal);
}