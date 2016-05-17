#ifndef FLOG_H
#define FLOG_H

void wyswietl_czas();

void log_wyp_pyt( char *nazwa_pliku );
void log_dod_pyt( char *nazwa_pliku );
void log_usu_pyt( char *nazwa_pliku );
void log_edy_pyt( int nr, char *nazwa_pliku );
void log_wyl_pyt( int ilosc, char *nazwa_pliku, char *do_pliku );
void log_wyp_prz( char *nazwa_pliku );
void log_dod_prz( char *nazwa_pliku );
void log_usu_prz( char *nazwa_pliku );
void log_edy_prz( int nr, char *nazwa_pliku );
void log_wyl_prz( int ilosc, char *nazwa_pliku, char *do_pliku );
void log_wyb_help();
void log_brak_arg();
void log_malo_arg( char *nazwa_funkcji );
void log_brak_fun( char *nazwa_funkcji );
void log_brak_pliku( char *nazwa_pliku );
void log_brak_pam( int i );
void log_brak_pytania( char *nazwa_pliku, int nr );
void log_brak_przedm( char *nazwa_pliku, int nr );
void log_malo_pytan( char *nazwa_pliku, int ilosc );
void log_zero_pytan( int ilosc );
void log_malo_przedm( int ilosc );

#endif
