#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "funkcije.h"

static int brojDodavanja = 0;
int ukupnoDodanih = 0;

void dodajZaposlenika() {

	brojDodavanja++;
	ukupnoDodanih++;

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
		perror("Greska kod otvaranja datoteke");
		free(z);
		z = NULL;
		return;
	}

	fprintf(fp, "%d %s %.2f\n", z->id, z->ime, z->placa);

	fclose(fp);

	printf("Zaposlenik uspjesno dodan! (Ukupno: %d)\n", ukupnoDodanih);

	free(z);
	z = NULL;
}

void prikaziZaposlenike() {

	Zaposlenik* z = malloc(sizeof(Zaposlenik));

	if (z == NULL) {
		printf("Greska kod alokacije memorije!\n");
		return;
	}

	FILE* fp = fopen(DATOTEKA, "r");

	if (fp == NULL) {
		perror("Greska kod otvaranja datoteke");
		free(z);
		z = NULL;
		return;
	}

	int brojac = 0;

	while (fscanf(fp, "%d %49s %f", &z->id, z->ime, &z->placa) == 3) {

		brojac++;

		printf("\n------------------");
		printf("\nID:    %d", z->id);
		printf("\nIme:   %s", z->ime);
		printf("\nPlaca: %.2f", z->placa);
		printf("\n------------------\n");
	}

	if (feof(fp) && brojac == 0) {
		printf("Nema zaposlenika u evidenciji.\n");
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
		perror("Greska kod datoteke");
		if (fp) fclose(fp);
		if (temp) fclose(temp);
		free(z);
		z = NULL;
		return;
	}

	printf("Unesi ID zaposlenika za uredivanje: ");

	if (scanf("%d", &trazeniID) != 1 || trazeniID <= 0) {
		printf("Pogresan unos ID-a!\n");
		ocistiBuffer();
		fclose(fp);
		fclose(temp);
		free(z);
		z = NULL;
		return;
	}

	while (fscanf(fp, "%d %49s %f", &z->id, z->ime, &z->placa) == 3) {

		if (z->id == trazeniID) {

			pronaden = 1;

			printf("Unesi novo ime: ");
			if (scanf("%49s", z->ime) != 1) {
				printf("Pogresan unos!\n");
				ocistiBuffer();
				fclose(fp);
				fclose(temp);
				free(z);
				z = NULL;
				return;
			}

			printf("Unesi novu placu: ");
			if (scanf("%f", &z->placa) != 1 || z->placa < 0) {
				printf("Pogresan unos!\n");
				ocistiBuffer();
				fclose(fp);
				fclose(temp);
				free(z);
				z = NULL;
				return;
			}
		}

		fprintf(temp, "%d %s %.2f\n", z->id, z->ime, z->placa);
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
		perror("Greska kod datoteke");
		if (fp) fclose(fp);
		if (temp) fclose(temp);
		free(z);
		z = NULL;
		return;
	}

	printf("Unesi ID zaposlenika za brisanje: ");

	if (scanf("%d", &trazeniID) != 1 || trazeniID <= 0) {
		printf("Pogresan unos ID-a!\n");
		ocistiBuffer();
		fclose(fp);
		fclose(temp);
		free(z);
		z = NULL;
		return;
	}

	while (fscanf(fp, "%d %49s %f", &z->id, z->ime, &z->placa) == 3) {

		if (z->id == trazeniID) {
			pronaden = 1;
			continue;
		}

		fprintf(temp, "%d %s %.2f\n", z->id, z->ime, z->placa);
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

void sortirajZaposlenike() {

	
	FILE* fp = fopen(DATOTEKA, "r");

	if (fp == NULL) {
		perror("Greska kod otvaranja datoteke");
		return;
	}

	int n = 0;
	Zaposlenik temp;

	while (fscanf(fp, "%d %49s %f", &temp.id, temp.ime, &temp.placa) == 3) {
		n++;
	}

	rewind(fp);

	if (n == 0) {
		printf("Nema zaposlenika za sortiranje.\n");
		fclose(fp);
		return;
	}

	
	Zaposlenik* niz = malloc(n * sizeof(Zaposlenik));

	if (niz == NULL) {
		printf("Greska kod alokacije memorije!\n");
		fclose(fp);
		return;
	}

	
	int i = 0;
	while (fscanf(fp, "%d %49s %f", &niz[i].id, niz[i].ime, &niz[i].placa) == 3) {
		i++;
	}

	fclose(fp);

	
	int j;
	Zaposlenik pomocni;

	for (i = 0; i < n - 1; i++) {
		for (j = 0; j < n - 1 - i; j++) {
			if (niz[j].placa > niz[j + 1].placa) {
				pomocni = niz[j];
				niz[j] = niz[j + 1];
				niz[j + 1] = pomocni;
			}
		}
	}

	fp = fopen(DATOTEKA, "w");

	if (fp == NULL) {
		perror("Greska kod otvaranja datoteke");
		free(niz);
		niz = NULL;
		return;
	}

	for (i = 0; i < n; i++) {
		fprintf(fp, "%d %s %.2f\n", niz[i].id, niz[i].ime, niz[i].placa);
	}

	fclose(fp);

	free(niz);
	niz = NULL;

	printf("Zaposlenici sortirani po placi uzlazno!\n");
}