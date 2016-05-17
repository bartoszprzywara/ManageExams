#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "flog.h"


/* wsywietla aktualny czas w odpowiednim formacie */
void wyswietl_czas()
	{
	time_t czas = time(0);
	struct tm *czas_strukt = localtime( &czas );
	FILE *out = fopen ( "log.txt", "a" );

	if( czas_strukt->tm_mday < 10 )
		fprintf( out, "0%d.", czas_strukt->tm_mday );
	else
		fprintf( out, "%d.", czas_strukt->tm_mday );

	if( czas_strukt->tm_mon+1 < 10 )
		fprintf( out, "0%d.", czas_strukt->tm_mon+1 );
	else
		fprintf( out, "%d.", czas_strukt->tm_mon+1 );

	fprintf( out, "%dr. ", czas_strukt->tm_year+1900 );

	if( czas_strukt->tm_hour < 10 )
		fprintf( out, "0%d:", czas_strukt->tm_hour );
	else
		fprintf( out, "%d:", czas_strukt->tm_hour );

	if( czas_strukt->tm_min < 10 )
		fprintf( out, "0%d:", czas_strukt->tm_min );
	else
		fprintf( out, "%d:", czas_strukt->tm_min );

	if( czas_strukt->tm_sec < 10 )
		fprintf( out, "0%d", czas_strukt->tm_sec );
	else
		fprintf( out, "%d", czas_strukt->tm_sec );

	fprintf( out, "  " );
	fclose( out );
	}


/* funckje zapisujace odpowiednie logi do pliku log.txt */
void log_wyp_pyt( char *nazwa_pliku )
	{
	wyswietl_czas();
	FILE *out = fopen ( "log.txt", "a" );
	fprintf( out, "Wypisano pytania z pliku %s na ekran\n", nazwa_pliku );
	fclose( out );
	}

void log_dod_pyt( char *nazwa_pliku )
	{
	wyswietl_czas();
	FILE *out = fopen ( "log.txt", "a" );
	fprintf( out, "Dodano nowe pytanie do pliku %s\n", nazwa_pliku );
	fclose( out );
	}

void log_usu_pyt( char *nazwa_pliku )
	{
	wyswietl_czas();
	FILE *out = fopen ( "log.txt", "a" );
	fprintf( out, "Usunieto pytanie z pliku %s\n", nazwa_pliku );
	fclose( out );
	}

void log_edy_pyt( int nr, char *nazwa_pliku )
	{
	wyswietl_czas();
	FILE *out = fopen ( "log.txt", "a" );
	fprintf( out, "Edytowano pytanie o numerze %d w pliku %s\n", nr+1, nazwa_pliku );
	fclose( out );
	}

void log_wyl_pyt( int ilosc, char *nazwa_pliku, char *do_pliku )
	{
	wyswietl_czas();
	FILE *out = fopen ( "log.txt", "a" );
	fprintf( out, "Wylosowano %d pytan z pliku %s i zapisano je do pliku %s\n", ilosc, nazwa_pliku, do_pliku );
	fclose( out );
	}

void log_wyp_prz( char *nazwa_pliku )
	{
	wyswietl_czas();
	FILE *out = fopen ( "log.txt", "a" );
	fprintf( out, "Wypisano przedmioty z pliku %s na ekran\n", nazwa_pliku );
	fclose( out );
	}

void log_dod_prz( char *nazwa_pliku )
	{
	wyswietl_czas();
	FILE *out = fopen ( "log.txt", "a" );
	fprintf( out, "Dodano nowy przedmiot do pliku %s\n", nazwa_pliku );
	fclose( out );
	}

void log_usu_prz( char *nazwa_pliku )
	{
	wyswietl_czas();
	FILE *out = fopen ( "log.txt", "a" );
	fprintf( out, "Usunieto przedmiot z pliku %s\n", nazwa_pliku );
	fclose( out );
	}

void log_edy_prz( int nr, char *nazwa_pliku )
	{
	wyswietl_czas();
	FILE *out = fopen ( "log.txt", "a" );
	fprintf( out, "Edytowano przedmiot o numerze %d w pliku %s\n", nr+1, nazwa_pliku );
	fclose( out );
	}

void log_wyl_prz( int ilosc, char *nazwa_pliku, char *do_pliku )
	{
	wyswietl_czas();
	FILE *out = fopen ( "log.txt", "a" );
	fprintf( out, "Wylosowano %d pytan ze wszystkich plikow wymienionych w %s i zapisano je do pliku %s\n",
		ilosc, nazwa_pliku, do_pliku );
	fclose( out );
	}

void log_wyb_help()
	{
	wyswietl_czas();
	FILE *out = fopen ( "log.txt", "a" );
	fprintf( out, "Wybrano opcje \"Help\"\n" );
	fclose( out );
	}

void log_brak_arg()
	{
	wyswietl_czas();
	FILE *out = fopen ( "log.txt", "a" );
	fprintf( out, "Blad: Uruchomiono program bez argumentow\n" );
	fclose( out );
	}

void log_malo_arg( char *nazwa_funkcji )
	{
	wyswietl_czas();
	FILE *out = fopen ( "log.txt", "a" );
	fprintf( out, "Blad: Podano zbyt malo argumentow dla operacji %s\n", nazwa_funkcji );
	fclose( out );
	}

void log_brak_fun( char *nazwa_funkcji )
	{
	wyswietl_czas();
	FILE *out = fopen ( "log.txt", "a" );
	fprintf( out, "Blad: Wybrano nieprawidlowa operacje %s\n", nazwa_funkcji );
	fclose( out );
	}

void log_brak_pliku( char *nazwa_pliku )
	{
	wyswietl_czas();
	FILE *out = fopen ( "log.txt", "a" );
	fprintf( out, "Blad: Podany plik do wczytania %s nie istneje\n", nazwa_pliku );
	fclose( out );
	}

void log_brak_pam( int nr )
	{
	wyswietl_czas();
	FILE *out = fopen ( "log.txt", "a" );
   fprintf( out, "Blad: Brak pamieci po przeczytaniu linii nr %i\n", nr );
	fclose( out );
	}

void log_brak_pytania( char *nazwa_pliku, int nr )
	{
	wyswietl_czas();
	FILE *out = fopen ( "log.txt", "a" );
   fprintf( out, "Blad: W pliku %s nie istnieje pytanie o numerze %d\n", nazwa_pliku, nr );
	fclose( out );
	}

void log_brak_przedm( char *nazwa_pliku, int nr )
	{
	wyswietl_czas();
	FILE *out = fopen ( "log.txt", "a" );
   fprintf( out, "Blad: W pliku %s nie istnieje przedmiot o numerze %d\n", nazwa_pliku, nr );
	fclose( out );
	}

void log_malo_pytan( char *nazwa_pliku, int ilosc )
	{
	wyswietl_czas();
	FILE *out = fopen ( "log.txt", "a" );
	fprintf( out, "Blad: Nie mozna wylosowac %d pytan. Plik %s zawiera mniej niz %d pytan\n",
		ilosc, nazwa_pliku, ilosc );
	fclose( out );
	}

void log_zero_pytan( int ilosc )
	{
	wyswietl_czas();
	FILE *out = fopen ( "log.txt", "a" );
	fprintf( out, "Blad: Nie mozna wylosowac %d pytan. Nalezy wylosowac przynajmniej jedno pytanie\n", ilosc );
	fclose( out );
	}

void log_malo_przedm( int ilosc )
	{
	wyswietl_czas();
	FILE *out = fopen ( "log.txt", "a" );
	fprintf( out, "Blad: Nie mozna wylosowac %d pytan. Pliki z pytaniami zawieraja lacznie mniej niz %d pytan\n",
		ilosc, ilosc );
	fclose( out );
	}
