#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "funkcije.h"

int main() {

    int izbor;

    do {

        printf("\n===== EVIDENCIJA PLACA =====\n");

        printf("1. Dodaj zaposlenika\n");
        printf("2. Prikazi zaposlenike\n");
        printf("3. Uredi zaposlenika\n");
        printf("4. Obrisi zaposlenika\n");
        printf("5. Izlaz\n");

        printf("Odaberi opciju: ");

        if (scanf("%d", &izbor) != 1) {

            printf("Pogresan unos!\n");

            ocistiBuffer();

            izbor = 0;
            continue;
        }

        switch (izbor) {

        case DODAJ:
            dodajZaposlenika();
            break;

        case PRIKAZ:
            prikaziZaposlenike();
            break;

        case UREDI:
            urediZaposlenika();
            break;

        case OBRISI:
            obrisiZaposlenika();
            break;

        case IZLAZ:
            printf("Program zatvoren.\n");
            break;

        default:
            printf("Pogresan unos!\n");
        }

    } while (izbor != IZLAZ);

    return 0;
}