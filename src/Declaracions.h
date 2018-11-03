/* 
 * FITXER: Declaracions.h
 *
 * Aquest fitxer conté:
 *    1.- Llibreries
 *    2.- Definicions
 *    3.- Estructures de dades
 *    4.- Declaracions de funcions
 * 
 * El contingut d'aquest fitxer està definit en els altres dos fitxers:
 * Definicions.c i Main.c.
 *
 */

// ------------------------------- Llibreries -------------------------------

#include <stdio.h>      // General.
#include <string.h>     // Tipus de variables, cadenes i arrays de caràcters.
#include <stdlib.h>     // Tipus de variables, cadenes i funcions generals.
#include <dirent.h>     // Funcions per treballar amb directoris i fitxers.
#include <time.h>       // Funcions que manipulen la data i el temps.

// ------------------------------ Definicions -------------------------------

#define NDISCS 3     // Número predeterminat de discos. L'usuari el pot canviar.
#define NTOWERS 3    // Número predeterminat de torres/pilars. No es pot canviar.
#define N 3


// -------------------------- Estructures de dades --------------------------

/* La estructura sState és la que utilitzarem per a realitzar la matriu 
necessària a l'hora de dur a terme el joc.*/
typedef struct{
    int move;         // Nombre del moviment
    int disc;         // Nombre del disc
    char twrorg;      // Torre origen
    char twrdest;     // Torre destí
    int prof;         // Profunditat
    int *v[NTOWERS];  // Vector amb el nombre de torres
}sState;

/* La estructura sCap emmagatzema diferents dades: el nombre de torres (que 
sempre serà 3), el nombre de discos (que el decideix l'usuari i, en cas que 
aquest no introdueixi res, el programa prendrà com defecte el nombre 3), el 
nombre de moviments en què es realitza el hanoi escollit, el nom del fitxer,
el codi d'operació del fitxer i la ruta de sortida d'aquest. */
typedef struct{
  int Ntwrs;        // Nombre de torres
  int Nd;           // Nombre de discos
  int NMov;         // Nombre de moviments
  char *Nom;        // Nom fitxer
  char *C_op;       // Codi Operacio fitxer
  char *Out_pth;    // Ruta de sortida
}sCap;


// -------------------------------- Funcions --------------------------------

int Buscar_disc(int towerorg, int *w[NTOWERS], int disc);
void get_command_line(int argc, char**argv, int *nd, char **output, char **codi_op, char **nom_fx);
void date_and_time();
void save_state(sState *Sts, int *w[NTOWERS], int disc, int m, int towerorg, int towerdest, int ptwr, int depth);
void move(int towerorg, int towerdest, sState **Sts, int *w[NTOWERS], int *m, int size, int Size_Sts, int disc, int depth);
void ini_mem(sState **Sts, int *w[NTOWERS], int nd, int Size_Sts);
void resize_sts(sState *Sts, int Size_Sts, int nd, int m);
void ini_sts(int nd, sState **Sts, int *w[NTOWERS], int m, int depth);
void ini_matrix(int *w[NTOWERS], int nd);
void hanoi(int nd, int towerorg, int towerdest, int toweraux, sState **Sts, int *w[NTOWERS], int *m, int size, int Size_Sts, int discs, int depth);
void imprimir_move(sState *Sts, int move, int disc);
void ini_cap(sCap **Cap, int Size_cap, int moves, char *nom_fx, char *output, char *codi_op, int discs);
void imprimir_cap1(sCap *Cap);
void imprimir_cap2(sCap *Cap);
void imprimir_all_sts(sState *Sts, int m, sCap *Cap, int disc);
void imprimir_sts_user(sState *Sts, int m, int disc);
void imprimir_move_fitxer(FILE *f, sState *Sts, int move, int disc);
void date_and_time_fitxer(FILE *f);
void imprimir_cap1_fitxer(FILE *f, sCap *Cap);
void imprimir_cap2_fitxer(FILE *f, sCap *Cap);
void imprimir_fitxer(sState *Sts, int m, sCap *Cap, int disc);
void free_mem(sState **Sts, int *w[NTOWERS], sCap **Cap, int moves);
