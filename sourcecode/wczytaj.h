#ifndef WCZYTAJ_H
#define WCZYTAJ_H

/* struktura zawieracjaca pytanie */
typedef struct pytanie
   {
   int nr;
   char *tresc;
	} pytanie;


/* struktura zawierajaca informacje o pliku */
typedef struct plik
   {
   pytanie *zestaw;  /* tablica struktur z pytaniami */
   int wlk;          /* pojemność tablicy linie */
   int n;            /* liczba zajętych elementów tablicy linie */
   } plik;

int powieksz( plik *p );

int wczytaj_pytanie( plik *p, char *opis_pyt );

int wczytaj( plik *p, char *nazwa_pliku );

#endif
