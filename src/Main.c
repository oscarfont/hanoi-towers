/* 
 * FITXER: Main.c
 *
 * Aquest fitxer conte:
 *    1.- Llibreries
 *    2.- Funcio principal main
 * 
 * Està relacionat amb el fitxer Declaracions.h mitjançant una llibreria.
 *
 */

// ------------------------------- Llibreries -------------------------------

#include "Declaracions.h"
 
/* Conté totes les llibreries, definicions, estructures de dades i declaracions
de funcions que necessitarem pel programa. */


// ---------------------------------- Main ----------------------------------

int main(int argc, char**argv) {
    
    // Declaració de totes les variables que necessitarem
    int nd = 0, moves = 0, *matrix[NTOWERS], size = 1, Size_Sts, disc, depth = 0,
            Size_cap = 0, Size_min_nf = 7;
    char *output = NULL, *codi_op = NULL, *nom_fx = NULL;
    sState *Sts = NULL;
    sCap *Cap;
    
    // Crida de la funcio get_command_line
    get_command_line(argc, argv, &nd, &output, &codi_op, &nom_fx);
    // Càlcul de la mida de la capçalera
    Size_cap = sizeof(sCap) + Size_min_nf + strlen(output);

    // *** AQUI COMENÇA EL JOC DEL HANOI ***

    // Si el nombre de discos és 0:
    if(nd == 0){
        nd = NDISCS;
        disc = nd;
        Size_Sts = sizeof(sState) + nd*NTOWERS*sizeof(int);
        ini_mem(&Sts, matrix, nd, Size_Sts);
        ini_matrix(matrix, nd);
        ini_sts(nd, &Sts, matrix, moves, depth);
        hanoi(nd, 0, 1, 2, &Sts, matrix, &moves, size, Size_Sts, disc, depth);
        if(nom_fx == NULL){
            ini_cap(&Cap, Size_cap, moves, nom_fx, output, codi_op, disc);
            imprimir_all_sts(Sts, moves, Cap, disc);
            imprimir_sts_user(Sts, moves, disc);
        }else{ 
            if(codi_op == NULL){
               codi_op = (char*) malloc(strlen("ap")+1);
               strcpy(codi_op, "ap");
               ini_cap(&Cap, Size_cap, moves, nom_fx, output, codi_op, disc);
               imprimir_fitxer(Sts, moves, Cap, disc);
               imprimir_all_sts(Sts, moves, Cap, disc);
               imprimir_sts_user(Sts, moves, disc);
            }else{
               ini_cap(&Cap, Size_cap, moves, nom_fx, output, codi_op, disc);
               imprimir_fitxer(Sts, moves, Cap, disc);
               imprimir_all_sts(Sts, moves, Cap, disc);
               imprimir_sts_user(Sts, moves, disc); 
            }
        }
	// Si el nombre de discos és diferent de 0:
    }else{
        disc = nd;
        Size_Sts = sizeof(sState) + nd*NTOWERS*sizeof(int);
        ini_mem(&Sts, matrix, nd, Size_Sts);
        ini_matrix(matrix, nd);
        ini_sts(nd, &Sts, matrix, moves, depth);
        hanoi(nd, 0, 1, 2, &Sts, matrix, &moves, size, Size_Sts, disc, depth);
        if(nom_fx == NULL){
            ini_cap(&Cap, Size_cap, moves, nom_fx, output, codi_op, disc);
            imprimir_all_sts(Sts, moves, Cap, disc);
            imprimir_sts_user(Sts, moves, disc);
        }else{ 
            if(codi_op == NULL){
               codi_op = (char*) malloc(strlen("ap")+1);
               strcpy(codi_op, "ap");
               ini_cap(&Cap, Size_cap, moves, nom_fx, output, codi_op, disc);
               imprimir_fitxer(Sts, moves, Cap, disc);
               imprimir_all_sts(Sts, moves, Cap, disc);
               imprimir_sts_user(Sts, moves, disc);
            }else{
               ini_cap(&Cap, Size_cap, moves, nom_fx, output, codi_op, disc);
               imprimir_fitxer(Sts, moves, Cap, disc);
               imprimir_all_sts(Sts, moves, Cap, disc);
               imprimir_sts_user(Sts, moves, disc); 
            }
        }
    }

    // *** AQUI ACABA EL JOC DEL HANOI ***

    // Alliberem memòria per a finalitzar la execució:
    free_mem(&Sts, matrix, &Cap, moves);
    
    free(nom_fx);
    free(codi_op);
    free(output);
    
    return (0);
}