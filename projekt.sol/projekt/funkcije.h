#ifndef FUNKCIJE_H
#define FUNKCIJE_H

#define DATOTEKA "place.txt"

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
    IZLAZ

} Izbornik;

inline void ocistiBuffer() {

    while (getchar() != '\n');
}

void dodajZaposlenika();
void prikaziZaposlenike();
void urediZaposlenika();
void obrisiZaposlenika();

#endif