#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "pytania.h"
#include "flog.h"

#define ASCII__ 95
#define ASCII_SPACE 32


/* dodaje nowe pytanie */
void dodaj( plik *p, char *nazwa_pliku, char *nowe_pyt )
	{
	FILE *out = fopen ( nazwa_pliku, "w" );
	int i;

	for( i=0; i<strlen( nowe_pyt ); ++i )
		if( nowe_pyt[i] == ASCII__ )
			nowe_pyt[i] = ASCII_SPACE;

	for( i=0; i<p->n; i++ )
		fprintf( out, "%d %s", p->zestaw[i].nr, p->zestaw[i].tresc );
	fprintf( out, "%d %s\n", i+1, nowe_pyt );

	fclose( out );
	log_dod_pyt( nazwa_pliku );
	}


/* usuwa wybrane pytanie */
void usun( plik *p, char *nazwa_pliku, int c )
	{
	if( c < 1 || c > p->n )
		{
		printf( "\nBlad: W pliku %s nie istnieje pytanie o numerze %d\n\n", nazwa_pliku, c );
		log_brak_pytania( nazwa_pliku, c );
		exit( EXIT_FAILURE );
		}

	FILE *out = fopen ( nazwa_pliku, "w" );
	int i;

	for( i=0; i < (c-1); i++ )
		fprintf( out, "%d %s", p->zestaw[i].nr, p->zestaw[i].tresc );
	for( i=c; i < p->n; i++ )
		fprintf( out, "%d %s", p->zestaw[i-1].nr, p->zestaw[i].tresc );

	fclose( out );
	log_usu_pyt( nazwa_pliku );
	}


/* edytuje wybrane pytanie */
void edytuj( plik *p, char *nazwa_pliku, int c, char *nowa_tresc )
	{
	if( c < 1 || c > p->n )
		{
		printf( "\nBlad: W pliku %s nie istnieje pytanie o numerze %d\n\n", nazwa_pliku, c );
		log_brak_pytania( nazwa_pliku, c );
		exit( EXIT_FAILURE );
		}

	FILE *out = fopen ( nazwa_pliku, "w" );
	int i;

	for( i=0; i<strlen( nowa_tresc ); ++i )
		if( nowa_tresc[i] == ASCII__ )
			nowa_tresc[i] = ASCII_SPACE;

	char *zamien = strcat( nowa_tresc, "\n" );
	p->zestaw[c-1].tresc = zamien;

	for( i=0; i<p->n; i++ )
		fprintf( out, "%d %s", p->zestaw[i].nr, p->zestaw[i].tresc );

	fclose( out );
	log_edy_pyt( c-1, nazwa_pliku );
	}


/* wypisuje na ekranie pytania z pliku */
void wypisz( plik *p, char *funkcja, char *nazwa_pliku )
	{
	int i;
	for( i=0; i<p->n; i++ )
		printf( "%d %s", p->zestaw[i].nr, p->zestaw[i].tresc );
	printf( "\n" );

	if( !strcmp( funkcja, "wypisz" ) || !strcmp( funkcja, "wylicz" ) )
		log_wyp_pyt( nazwa_pliku);
	else if( !strcmp( funkcja, "wypisz_przedmioty" ) || !strcmp( funkcja, "wylicz_przedmioty" ) )
		log_wyp_prz( nazwa_pliku );
	}


int porownaj( const void *a, const void *b )
	{
	return ( *( int* )a - *( int* )b );
	}


/* losuje podana ilosc pytan z wybranego przedmiotu */
void losuj( plik *p, char *nazwa_pliku, int ilosc, char *do_pliku )
	/*	kazda struktura ma swoj indeks w tablicy struktur -> losowanie bez powtorzen
		kilku liczb z zakresu wielkosci tej tablicy -> wylosowane liczby to indeksy
		struktur -> wylosowane struktury te zapisywane sa nastepnie do pliku */
	{
	if( ilosc > p->n )
		{
		printf( "\nBlad: Nie mozna wylosowac %d pytan.\nPlik %s zawiera mniej niz %d pytan\n\n", ilosc, nazwa_pliku, ilosc );
		log_malo_pytan( nazwa_pliku, ilosc );
		exit( EXIT_FAILURE );
		}
	if( ilosc < 1 )
		{
		printf( "\nBlad: Nie mozna wylosowac %d pytan.\nNalezy wylosowac przynajmniej jedno pytanie\n\n", ilosc );
		log_zero_pytan( ilosc );
		exit( EXIT_FAILURE );
		}

	char baza[1024] = "baza/";
	char *do_p = strcat( baza, do_pliku );

	FILE *out = fopen ( do_p, "w" );
	int wylosowane[ilosc];
	int i, j;
	srand( time( 0 ) );

	for( i=0; i<ilosc; i++)
		{
		wylosowane[i] = ( rand()%( p->n ) );
		for( j=0; j<i; j++)
			if( wylosowane[i] == wylosowane[j] )
				i--;
		}
	qsort( wylosowane, ilosc, sizeof( int ), porownaj );

	for( i=0; i<ilosc; i++ )
		{
		printf( "%d %s", i+1, p->zestaw[wylosowane[i]].tresc );
		fprintf( out, "%d %s", i+1, p->zestaw[wylosowane[i]].tresc );
		}

	fclose( out );
	log_wyl_pyt( ilosc, nazwa_pliku, do_pliku );
	}
