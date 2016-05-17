#ifndef PYTANIA_H
#define PYTANIA_H

#include "wczytaj.h"

void dodaj( plik *p, char *nazwa_pliku, char *nowe_pyt );

void usun( plik *p, char *nazwa_pliku, int c );

void edytuj( plik *p, char *nazwa_pliku, int c, char *nowa_tresc );

void wypisz( plik *p, char *funkcja, char *nazwa_pliku );

int porownaj (const void *a, const void *b);

void losuj( plik *p, char *nazwa_pliku, int ilosc, char *do_pliku );

#endif
