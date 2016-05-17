#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wczytaj.h"
#include "flog.h"


/* powieksza tablice struktur z pytaniami*/
int powieksz( plik *p )
   {
   int nwlk = 2*p->wlk;

   pytanie *tmp = malloc( nwlk * sizeof *tmp );
   if( tmp != NULL )
      {
      memcpy( tmp, p->zestaw, p->wlk * sizeof p->zestaw[0] );
      free( p-> zestaw );
      p->zestaw = tmp;
      p->wlk *= 2;
      return 0;
      }
   else
      return 1;
	free( tmp );
   }       


/* wczytuje wczytane z pliku pytania do struktury*/
int wczytaj_pytanie( plik *p, char *opis_pyt )
	{
	if( p->n == p->wlk && powieksz( p ) )
		return 2;
	else
		{
		char *numer= opis_pyt;
		char *tresc= strchr( opis_pyt, ' ' ) + 1;
		*(tresc-1)= '\0';
		p->zestaw[p->n].nr = atoi( numer );
		p->zestaw[p->n].tresc = malloc( strlen( tresc )+1 );
		strcpy( p->zestaw[p->n].tresc, tresc );
		p->n++;
		return 0;
		}
	free( p->zestaw[p->n].tresc );
	}


/* wczytuje plik tekstowy z pytaniami linia po linii */
int wczytaj( plik *p, char *nazwa_pliku )
	{
	FILE *in = fopen( nazwa_pliku, "r" );
	if( !in )
		{
		printf( "\nBlad: Plik %s nie istnieje\n\n", nazwa_pliku );
		log_brak_pliku( nazwa_pliku );
		exit( EXIT_FAILURE );
		}

	char buf[1024]; /* bufor do czytania poszczegolnych linii: 1024 to max dlugosc linii */
	int i = 0;

	while( fgets( buf, 1024, in ) != NULL )
		if( wczytaj_pytanie( p, buf ) != 0 )
			{
			printf( "\nBlad: Brak pamieci po przeczytaniu linii nr %i\n\n", i );
			log_brak_pam( i );
			return EXIT_FAILURE;
			}
		else
			i++;

	fclose( in );
	return EXIT_SUCCESS;
	}
