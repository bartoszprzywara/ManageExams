#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "przedmioty.h"
#include "pytania.h"
#include "flog.h"

#define ASCII__ 95
#define ASCII_SPACE 32


/* dodaje nowy przedmiot */
void dodaj_przedmiot( plik *p, char *nazwa_pliku, char *nowy_przed )
	{
	FILE *out = fopen ( nazwa_pliku, "w" );
	int i;
	for( i=0; i<strlen( nowy_przed ); ++i )
		if( nowy_przed[i] == ASCII__ )
			nowy_przed[i] = ASCII_SPACE;

	for( i=0; i <p->n; i++ )
		fprintf( out, "%d %s", p->zestaw[i].nr, p->zestaw[i].tresc );
	fprintf( out, "%d %s\n", i+1, nowy_przed );
	fclose( out );

	char *zamien = strcat( nowy_przed, ".txt" );

	for( i=0; i<strlen( nowy_przed ); ++i )
		if( nowy_przed[i] == ASCII_SPACE )
			nowy_przed[i] = ASCII__;

	char baza[1024] = "baza/";
	char *nowy_p = strcat( baza, zamien );

	FILE *nowy = fopen ( nowy_p, "w" );
	fclose( nowy );
	log_dod_prz( nazwa_pliku );
	}


/* usuwa wybrany przedmiot */
void usun_przedmiot( plik *p, char *nazwa_pliku, int c )
	{
	if( c < 1 || c > p->n )
		{
		printf( "\nBlad: W pliku %s nie istnieje przedmiot o numerze %d\n\n", nazwa_pliku, c );
		log_brak_przedm( nazwa_pliku, c );
		exit( EXIT_FAILURE );
		}

	FILE *out = fopen ( nazwa_pliku, "w" );
	int i;
	int dlugosc = strlen( p->zestaw[c-1].tresc );

	char skroc[dlugosc];
	for( i=0; i<dlugosc; i++ )
		skroc[i] = '\0';

	strncpy( skroc, p->zestaw[c-1].tresc, dlugosc-1 );
	char *zamien = strcat( skroc, ".txt" );

	for( i=0; i<strlen( zamien ); ++i )
		if( zamien[i] == ASCII_SPACE )
			zamien[i] = ASCII__;

	for( i=0; i <(c-1); i++ )
		fprintf( out, "%d %s", p->zestaw[i].nr, p->zestaw[i].tresc );
	for( i= c; i < p->n; i++ )
		fprintf( out, "%d %s", p->zestaw[i-1].nr, p->zestaw[i].tresc );

	char baza[1024] = "baza/";
	char *nazwa_p = strcat( baza, zamien );

	remove( nazwa_p );

	fclose( out );
	log_usu_prz( nazwa_pliku );
	}

/* edytuje wybrany przedmiot */
void edytuj_przedmiot( plik *p, char *nazwa_pliku, int c, char *nowa_tresc )
	{
	if( c < 1 || c > p->n )
		{
		printf( "\nBlad: W pliku %s nie istnieje przedmiot o numerze %d\n\n", nazwa_pliku, c );
		log_brak_przedm( nazwa_pliku, c );
		exit( EXIT_FAILURE );
		}

	int i;
	char nowa_t[strlen( nowa_tresc )];
	strcpy( nowa_t, nowa_tresc );

	char *nowa_nazwa = strcat( nowa_tresc, ".txt" );
	int dlugosc = strlen( p->zestaw[c-1].tresc );
	char skroc[dlugosc];

	for( i=0; i<dlugosc; i++ )
		skroc[i] = '\0';

	strncpy( skroc, p->zestaw[c-1].tresc, dlugosc-1 );
	char *stara_nazwa = strcat( skroc, ".txt" );

	for( i=0; i<strlen( stara_nazwa ); ++i )
		if( stara_nazwa[i] == ASCII_SPACE )
			stara_nazwa[i] = ASCII__;

	char baza_s[1024] = "baza/";
	char baza_n[1024] = "baza/";
	char *stara_n = strcat( baza_s, stara_nazwa );
	char *nowa_n = strcat( baza_n, nowa_nazwa );

	rename( stara_n, nowa_n );

	FILE *out = fopen ( nazwa_pliku, "w" );

	for( i=0; i<strlen( nowa_t ); ++i )
		if( nowa_t[i] == ASCII__ )
			nowa_t[i] = ASCII_SPACE;

	char *zamien = strcat( nowa_t, "\n" );
	p->zestaw[c-1].tresc = zamien;

	for( i=0; i <p->n; i++ )
		fprintf( out, "%d %s", p->zestaw[i].nr, p->zestaw[i].tresc );

	fclose( out );
	log_edy_prz( c-1, nazwa_pliku );
	}


/* losuje podana ilosc pytan ze wszystkich przedmiotow */
void losuj_wszystko( plik *p, char *nazwa_pliku, int ilosc, char *do_pliku )
	/*	kazda struktura ma swoj indeks w tablicy struktur -> losowanie bez powtorzen
		kilku liczb z zakresu wielkosci tej tablicy -> wylosowane liczby to indeksy
		struktur -> wylosowane struktury te zapisywane sa nastepnie do pliku */
	{
	int i, j;
	int dlugosc[p->n];
	char skroc[p->n][1024];
	char baza[p->n][1024];
	char *zamien[p->n];
	char *przedmioty[p->n];

	/* przygotowanie nazw plikow */
	for( i=0; i<p->n; i++ )
		dlugosc[i] = strlen( p->zestaw[i].tresc );

	for( i=0; i<p->n; i++ )
		for( j=0; j<1024; j++ )
			skroc[i][j] = '\0';

	for( i=0; i<p->n; i++ )
		strncpy( skroc[i], p->zestaw[i].tresc, dlugosc[i]-1 );

	for( i=0; i<p->n; i++ )
		zamien[i] = strcat( skroc[i], ".txt" );

	for( i=0; i<p->n; i++ )
		for( j=0; j<strlen(zamien[i]); ++j )
			if( zamien[i][j] == ASCII_SPACE )
				zamien[i][j] = ASCII__;

	for( i=0; i<p->n; i++ )
		for( j=0; j<1024; j++ )
			baza[i][j] = '\0';

	for( i=0; i<p->n; i++ )
		{
		baza[i][0] = 'b';
		baza[i][1] = 'a';
		baza[i][2] = 'z';
		baza[i][3] = 'a';
		baza[i][4] = '/';
		}

	for( i=0; i<p->n; i++ )
		przedmioty[i] = strcat( baza[i], zamien[i] );


	/* wczytanie wszystkich plikow */
	plik *a = malloc( sizeof *a );
	if( a != NULL )
		{
		if( ( a->zestaw = malloc( 2 * sizeof * a->zestaw ) ) == NULL )
			{
			free( a->zestaw );
			perror( "malloc" );
			exit( EXIT_FAILURE );
			}
		a->wlk = 2;
		a->n = 0;
		}

	for( i=0; i<p->n; i++ )
		wczytaj( a, przedmioty[i] );

	/* losowanie ze wszystkich plikow */
	if( ilosc > a->n )
		{
		printf( "\nBlad: Nie mozna wylosowac %d pytan.\nPliki z pytaniami zawieraja lacznie mniej niz %d pytan\n\n", ilosc, ilosc );
		log_malo_przedm( ilosc );
		exit( EXIT_FAILURE );
		}
	if( ilosc < 1 )
		{
		printf( "\nBlad: Nie mozna wylosowac %d pytan.\nNalezy wylosowac przynajmniej jedno pytanie\n\n", ilosc );
		log_zero_pytan( ilosc );
		exit( EXIT_FAILURE );
		}

	char baza2[1024] = "baza/";
	char *do_p = strcat( baza2, do_pliku );

	FILE *out = fopen ( do_p, "w" );
	int wylosowane[ilosc];

	srand( time( 0 ) );

	for( i=0; i<ilosc; i++)
		{
		wylosowane[i] = ( rand()%( a->n ) );
		for( j=0; j<i; j++)
			if( wylosowane[i] == wylosowane[j] )
				i--;
		}
	qsort( wylosowane, ilosc, sizeof( int ), porownaj );

	for( i=0; i<ilosc; i++ )
		{
		printf( "%d %s", i+1, a->zestaw[wylosowane[i]].tresc );
		fprintf( out, "%d %s", i+1, a->zestaw[wylosowane[i]].tresc );
		}

	fclose( out );
	log_wyl_prz( ilosc, nazwa_pliku, do_pliku );
	}
