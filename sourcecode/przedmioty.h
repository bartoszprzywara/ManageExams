#ifndef PRZEDMIOTY_H
#define PRZEDMIOTY_H

#include "wczytaj.h"

void dodaj_przedmiot( plik *p, char *nazwa_pliku, char *nowy_przed );

void usun_przedmiot( plik *p, char *nazwa_pliku, int c );

void edytuj_przedmiot( plik *p, char *nazwa_pliku, int c, char *nowa_tresc );

void losuj_wszystko( plik *p, char *nazwa_pliku, int ilosc, char *do_pliku );

#endif
