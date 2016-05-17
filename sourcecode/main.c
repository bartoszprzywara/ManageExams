#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "wczytaj.h"
#include "pytania.h"
#include "przedmioty.h"
#include "flog.h"


/* wypisuje pomoc dla uzytkownika */
void help( char *npr )
	{
	printf ( "\n"
				" 1. WYLICZ:\n\t%s wylicz /*lub wypisz*/ <nazwa_przedmiotu>\n"
				" 2. DODAJ:\n\t%s dodaj <nazwa_przedmiotu> <tresc_pytania>\n"
				" 3. USUN:\n\t%s usun <nazwa_przedmiotu> <numer_pytania>\n"
				" 4. EDYTUJ:\n\t%s edytuj <nazwa_przedmiotu> <numer_pytania>\n"
				"\t\t\t\t\t    <nowa_tresc>\n"
				" 5. LOSUJ:\n\t%s losuj <nazwa_przedmiotu> <liczba_pytan>\n"
				"\t\t\t\t\t    <nazwa_pliku_docelowego>\n"
				" 6. WYLICZ PRZEDMIOTY:\n\t%s wylicz_przedmioty /*lub wypisz_przedmioty*/\n"
				"\t\t\t\t\t    <nazwa_spisu>\n"
				" 7. DODAJ PRZEDMIOT:\n\t%s dodaj_przedmiot <nazwa_spisu> <nazwa_przedmiotu>\n"
				" 8. USUN PRZEDMIOT:\n\t%s usun_przedmiot <nazwa_spisu> <numer_przedmiotu>\n"
				" 9. EDYTUJ PRZEDMIOT:\n\t%s edytuj_przedmiot <nazwa_spisu> <numer_przedmiotu>\n"
				"\t\t\t\t\t   <nowa_nazwa_pytania>\n"
				"10. LOSUJ WSZYSTKO:\n\t%s losuj_wszystko <nazwa_spisu> <liczba_pytan>\n"
				"\t\t\t\t\t    <nazwa_pliku_docelowego>\n"
				"\n\tUWAGA: przy wpisywaniu wieloczlonowych nazw plikow lub\n"
				"\ttresci pytan nalezy zamiast spacji uzywac znaku \"_\" .\n"
				"\n", npr, npr, npr, npr, npr, npr, npr, npr, npr, npr );
	log_wyb_help();
	}


/* (funkcja main) */
int main( int argc, char **argv )
	{
	if( argc<2 )
		{
		printf( "\nBlad: Uruchomiono program bez argumentow.\nPomoc: %s help\n\n", argv[0] );
		log_brak_arg();
		return EXIT_FAILURE;
		}

	else if( argc == 2 && strcmp( argv[1], "help" ) )
		{
		if( !strcmp( argv[1], "wylicz" ) || !strcmp( argv[1], "wypisz" ) || !strcmp( argv[1], "dodaj" ) ||
			 !strcmp( argv[1], "usun" ) || !strcmp( argv[1], "edytuj" ) ||	!strcmp( argv[1], "losuj" ) ||
			 !strcmp( argv[1], "wylicz_przedmioty" ) || !strcmp( argv[1], "wypisz_przedmioty" ) ||
			 !strcmp( argv[1], "dodaj_przedmiot" ) || !strcmp( argv[1], "usun_przedmiot" ) ||
			 !strcmp( argv[1], "edytuj_przedmiot" ) || !strcmp( argv[1], "losuj_wszystko" ) )
				{
				printf( "\nBlad: Zbyt malo argumentow dla operacji %s.\nPomoc: %s help\n\n", argv[1], argv[0] );
				log_malo_arg( argv[1] );
				}
		else
				{
				printf( "\nBlad: Operacja %s nie istnieje.\nPomoc: %s help\n\n", argv[1], argv[0] );
				log_brak_fun( argv[1] );
				}
		return EXIT_FAILURE;
		}

	else if( !strcmp( argv[1], "help" ) )
		{
		help( argv[0] );
		return EXIT_FAILURE;
		}

	plik *p = malloc( sizeof *p );  /* inicjacja malego kontenera */
	if( p != NULL )
		{
		if( (p->zestaw = malloc( 2 * sizeof * p->zestaw )) == NULL )
			{
			free( p->zestaw );
			perror( "malloc" );
			exit( EXIT_FAILURE );
			}
		p->wlk = 2;
		p->n = 0;
		}

	char nazwa[strlen( argv[2] )];
	strcpy( nazwa, argv[2] );
	char *plik = strcat( nazwa, ".txt" );
	char baza[1024] = "baza/";
	char *nazwa_p = strcat( baza, plik );

	wczytaj( p, nazwa_p );

	/* wybieranie funkcji za pomoca argv[1] */
	if( !strcmp( argv[1], "wypisz" ) || !strcmp( argv[1], "wylicz" ) ||
		 !strcmp( argv[1], "wypisz_przedmioty" ) || !strcmp( argv[1], "wylicz_przedmioty" ) )
		wypisz( p, argv[1], nazwa_p );
	else if( !strcmp( argv[1], "dodaj" ) )
		{
		if( argc==4 )
			dodaj( p, nazwa_p, argv[3] );
		else if( ( argc>2 && argc<4 ) || argc>4 )
			{
			printf( "\nBlad: Zbyt malo argumentow dla operacji %s.\nPomoc: %s help\n\n", argv[1], argv[0] );
			log_malo_arg( argv[1] );
			return EXIT_FAILURE;
			}
		}
	else if( !strcmp( argv[1], "usun" ) )
		{
		if( argc==4 )
			usun( p, nazwa_p, atoi( argv[3] ) );
		else if( ( argc>2 && argc<4 ) || argc>4 )
			{
			printf( "\nBlad: Zbyt malo argumentow dla operacji %s.\nPomoc: %s help\n\n", argv[1], argv[0] );
			log_malo_arg( argv[1] );
			return EXIT_FAILURE;
			}
		}
	else if( !strcmp( argv[1], "edytuj" ) )
		{
		if( argc==5 )
			edytuj( p, nazwa_p, atoi( argv[3] ), argv[4] );
		else if( ( argc>2 && argc<5 ) || argc>5 )
			{
			printf( "\nBlad: Zbyt malo argumentow dla operacji %s.\nPomoc: %s help\n\n", argv[1], argv[0] );
			log_malo_arg( argv[1] );
			return EXIT_FAILURE;
			}
		}
	else if( !strcmp( argv[1], "losuj" ) )
		{
		if( argc==5 )
			losuj( p, nazwa_p, atoi( argv[3] ), argv[4] );
		else if( ( argc>2 && argc<5 ) || argc>5 )
			{
			printf( "\nBlad: Zbyt malo argumentow dla operacji %s.\nPomoc: %s help\n\n", argv[1], argv[0] );
			log_malo_arg( argv[1] );
			return EXIT_FAILURE;
			}
		}
	else if( !strcmp( argv[1], "dodaj_przedmiot" ) )
		{
		if( argc==4 )
			dodaj_przedmiot( p, nazwa_p, argv[3] );
		else if( ( argc>2 && argc<4 ) || argc>4 )
			{
			printf( "\nBlad: Zbyt malo argumentow dla operacji %s.\nPomoc: %s help\n\n", argv[1], argv[0] );
			log_malo_arg( argv[1] );
			return EXIT_FAILURE;
			}
		}
	else if( !strcmp( argv[1], "usun_przedmiot" ) )
		{
		if( argc==4 )
			usun_przedmiot( p, nazwa_p, atoi( argv[3] ) );
		else if( ( argc>2 && argc<4 ) || argc>4 )
			{
			printf( "\nBlad: Zbyt malo argumentow dla operacji %s.\nPomoc: %s help\n\n", argv[1], argv[0] );
			log_malo_arg( argv[1] );
			return EXIT_FAILURE;
			}
		}
	else if( !strcmp( argv[1], "edytuj_przedmiot" ) )
		{
		if( argc==5 )
			edytuj_przedmiot( p, nazwa_p, atoi( argv[3] ), argv[4] );
		else if( ( argc>2 && argc<5 ) || argc>5 )
			{
			printf( "\nBlad: Zbyt malo argumentow dla operacji %s.\nPomoc: %s help\n\n", argv[1], argv[0] );
			log_malo_arg( argv[1] );
			return EXIT_FAILURE;
			}
		}
	else if( !strcmp( argv[1], "losuj_wszystko" ) )
		{
		if( argc==5 )
			losuj_wszystko( p, nazwa_p, atoi( argv[3] ), argv[4] );
		else if( ( argc>2 && argc<5 ) || argc>5 )
			{
			printf( "\nBlad: Zbyt malo argumentow dla operacji %s.\nPomoc: %s help\n\n", argv[1], argv[0] );
			log_malo_arg( argv[1] );
			return EXIT_FAILURE;
			}
		}
	else
		{
		printf( "\nBlad: Operacja %s nie istnieje.\nPomoc: %s help\n\n", argv[1], argv[0] );
		log_brak_fun( argv[1] );
		exit( EXIT_FAILURE );
		}
	/* koniec wybierania funkcji */

	free( p );
	return EXIT_SUCCESS;
	}
