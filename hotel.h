#ifndef HOTEL_H
#define HOTEL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CAMERE     100
#define MAX_REZERVARI  100

#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define RESET   "\033[0m"

struct Camera {
    char tip[20];
    float pret;
    char status[20];
};

struct Rezervare {
    char tipCamera[20];
    int nrPersoane;
    char perioada[30];
    float pretTotal;
};

void citesteCamereDinFisier(void);
void salveazaRezervare(struct Rezervare r);
void meniuPrincipal(void);
void camereDisponibile(void);
void cautaCamere(void);
void rezervaCamere(void);
void verificaDetaliiRezervare(void);
void anulareRezervare(void);
int  valideazaNumarPersoane(int nr);
void citesteData(char *data, int lungime);

#endif
