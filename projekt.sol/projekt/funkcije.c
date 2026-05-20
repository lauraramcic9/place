#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funkcije.h"

static int brojDodavanja = 0;

void dodajZaposlenika() {

    brojDodavanja++;

    Zaposlenik* z = malloc(sizeof(Zaposlenik));

    if (z == NULL) {

        printf("Greska kod alokacije memorije!\n");
        return;
    }

    printf("Unesi ID: ");

    if (scanf("%d", &z->id) != 1 || z->id <= 0) {

        printf("Pogresan unos ID-a!\n");

        ocistiBuffer();

        free(z);
        z = NULL;

        return;
    }

    printf("Unesi ime: ");

    if (scanf("%49s", z->ime) != 1) {

        printf("Pogresan unos imena!\n");

        ocistiBuffer();

        free(z);
        z = NULL;

        return;
    }

    printf("Unesi placu: ");

    if (scanf("%f", &z->placa) != 1 || z->placa < 0) {

        printf("Pogresan unos place!\n");

        ocistiBuffer();

        free(z);
        z = NULL;

        return;
    }

    FILE* fp = fopen(DATOTEKA, "a");

    if (fp == NULL) {

        printf("Greska kod otvaranja datoteke!\n");

        free(z);
        z = NULL;

        return;
    }

    fprintf(fp,
        "%d %s %.2f\n",
        z->id,
        z->ime,
        z->placa);

    fclose(fp);

    printf("Zaposlenik uspjesno dodan!\n");

    free(z);
    z = NULL;
}

void prikaziZaposlenike() {

    Zaposlenik* z = calloc(1, sizeof(Zaposlenik));

    if (z == NULL) {

        printf("Greska kod alokacije memorije!\n");
        return;
    }

    FILE* fp = fopen(DATOTEKA, "r");

    if (fp == NULL) {

        printf("Datoteka ne postoji!\n");

        free(z);
        z = NULL;

        return;
    }

    while (fscanf(fp,
        "%d %49s %f",
        &z->id,
        z->ime,
        &z->placa) != EOF) {

        printf("\n------------------");
        printf("\nID: %d", z->id);
        printf("\nIme: %s", z->ime);
        printf("\nPlaca: %.2f", z->placa);
        printf("\n------------------\n");
    }

    fclose(fp);

    free(z);
    z = NULL;
}

void urediZaposlenika() {

    int trazeniID;
    int pronaden = 0;

    Zaposlenik* z = malloc(sizeof(Zaposlenik));

    if (z == NULL) {

        printf("Greska kod alokacije memorije!\n");
        return;
    }

    FILE* fp = fopen(DATOTEKA, "r");
    FILE* temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {

        printf("Greska kod datoteke!\n");

        free(z);
        z = NULL;

        return;
    }

    printf("Unesi ID zaposlenika za uredivanje: ");

    if (scanf("%d", &trazeniID) != 1 || trazeniID <= 0) {

        printf("Pogresan unos ID-a!\n");

        fclose(fp);
        fclose(temp);

        free(z);
        z = NULL;

        ocistiBuffer();

        return;
    }

    while (fscanf(fp,
        "%d %49s %f",
        &z->id,
        z->ime,
        &z->placa) != EOF) {

        if (z->id == trazeniID) {

            pronaden = 1;

            printf("Unesi novo ime: ");

            if (scanf("%49s", z->ime) != 1) {

                printf("Pogresan unos imena!\n");

                fclose(fp);
                fclose(temp);

                free(z);
                z = NULL;

                ocistiBuffer();

                return;
            }

            printf("Unesi novu placu: ");

            if (scanf("%f", &z->placa) != 1 || z->placa < 0) {

                printf("Pogresan unos place!\n");

                fclose(fp);
                fclose(temp);

                free(z);
                z = NULL;

                ocistiBuffer();

                return;
            }
        }

        fprintf(temp,
            "%d %s %.2f\n",
            z->id,
            z->ime,
            z->placa);
    }

    fclose(fp);
    fclose(temp);

    remove(DATOTEKA);
    rename("temp.txt", DATOTEKA);

    if (pronaden) {

        printf("Podaci uspjesno uredeni!\n");
    }
    else {

        printf("Zaposlenik nije pronaden!\n");
    }

    free(z);
    z = NULL;
}

void obrisiZaposlenika() {

    int trazeniID;
    int pronaden = 0;

    Zaposlenik* z = malloc(sizeof(Zaposlenik));

    if (z == NULL) {

        printf("Greska kod alokacije memorije!\n");
        return;
    }

    FILE* fp = fopen(DATOTEKA, "r");
    FILE* temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {

        printf("Greska kod datoteke!\n");

        free(z);
        z = NULL;

        return;
    }

    printf("Unesi ID zaposlenika za brisanje: ");

    if (scanf("%d", &trazeniID) != 1 || trazeniID <= 0) {

        printf("Pogresan unos ID-a!\n");

        fclose(fp);
        fclose(temp);

        free(z);
        z = NULL;

        ocistiBuffer();

        return;
    }

    while (fscanf(fp,
        "%d %49s %f",
        &z->id,
        z->ime,
        &z->placa) != EOF) {

        if (z->id == trazeniID) {

            pronaden = 1;
            continue;
        }

        fprintf(temp,
            "%d %s %.2f\n",
            z->id,
            z->ime,
            z->placa);
    }

    fclose(fp);
    fclose(temp);

    remove(DATOTEKA);
    rename("temp.txt", DATOTEKA);

    if (pronaden) {

        printf("Zaposlenik uspjesno obrisan!\n");
    }
    else {

        printf("Zaposlenik nije pronaden!\n");
    }

    free(z);
    z = NULL;
}