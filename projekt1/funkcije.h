
#ifndef FUNKCIJE_H
#define FUNKCIJE_H

#define _CRT_SECURE_NO_WARNINGS
#define DATOTEKA "place.txt"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct {
	int id;
	char ime[50];
	float placa;
} Zaposlenik;

typedef enum {
	DODAJ = 1,
	PRIKAZ,
	UREDI,
	OBRISI,
	SORTIRAJ,
	IZLAZ
} Izbornik;

extern int ukupnoDodanih;

inline void ocistiBuffer() {
	while (getchar() != '\n');
}

void dodajZaposlenika();
void prikaziZaposlenike();
void urediZaposlenika();
void obrisiZaposlenika();
void sortirajZaposlenike();

#endif