/* 
 * FITXER: Definicions.c
 *
 * Aquest fitxer conté:
 *    1.- Llibreries
 *    2.- Desenvolupament de totes les funcions
 * 
 * Està relacionat amb el fitxer Declaracions.h mitjançant una llibreria.
 *
 */

// ------------------------------- Llibreries -------------------------------

#include "Declaracions.h"

/* Conté totes les llibreries, definicions, estructures de dades i declaracions
de funcions que necessitarem pel programa. */


// ------------------------------- Funcions --------------------------------
/* La funció date_and_time la farem servir per a imprimir per pantalla, en 
la capçalera del final, juntament amb els resultats, la data i la hora de la 
execució del joc de Hanoi. */
void date_and_time(){
    
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    printf ("%s", asctime (timeinfo) );
    
}

/* La funció Buscar_disc la farem servir per a buscar el disc que hem de moure
a continuació, un cop realitzat el moviment anterior. */
int Buscar_disc(int towerorg, int *w[NTOWERS], int disc){
    
    int d;
    d = disc - 1;
    
    while((d >= 0)&&(w[towerorg][d] == 0)){
        d--;
    }
    
    return d;
}

/* La funció get_command_line la farem servir per a imprimir en la capçalera 1
tots els components de la command line que ha introduït l'usuari. */
void get_command_line(int argc, char**argv, int *nd, char **output, char **codi_op, char **nom_fx){
    
    int i = 0, wrd = 0, j = 0, size = 1, max = 10, z = 0, nbr = 0, col = 0, fil = 0;
    char **p, num[max];
    
    p = argv;
    
    for(i = 0; p[i] != '\0' ; i++){
        fil++;
       for(j = 0; p[i][j] != '\0'; j++){
            col++;
       }
    }
    
    char *line[fil];
    
    for(i = 0; i < fil; i++){
        line[i]=(char *)calloc(col,sizeof(char));
        if (line[i] == NULL){
            printf("Error: problemes de memòria");
            exit(0);
        }
    }
    i = 0; 
    j = 0;
    for(i = 0; p[i] != '\0' ; i++){
        for(j = 0; p[i][j] != '\0'; j++){
            line[i][j] = p[i][j];
        }
    }
    i = 0; 
    j = 0;
    
    for(i = 0; i < fil; i++){
        for(wrd = 0; wrd < col ; wrd++){
           if(line[i][wrd] == '-'){
                if(line[i][wrd+1] == 'd'){
                    strcpy(num, line[i+1]);
                    if(num[0] == '\0'){
                        *nd = 0;
                    }else{
                        *nd = atoi(num);
                    }
                }
                if(line[i][wrd+1] == 'f'){
                   j = 0;
                   while(line[i+1][j] != '\0'){
                       size++;
                       j++;
                   }
                   j = 0;
                   *nom_fx = (char *)malloc((size+1)*sizeof(char));
                   for(z = 0; z < size+1; z++){
                       (*nom_fx)[z] = line[i+1][j];
                       j++;
                   }
                }
                if(line[i][wrd+1] == 'o'){
                   j = 0;
                   *codi_op = (char *)malloc(strlen(line[i+1])+2);
                   for(z = 0; z < strlen(line[i+1])+ 1; z++){
                       (*codi_op)[z] = line[i+1][j];
                       j++;
                   }
                }
            }else if(line[i][wrd] == '/'){
                *output = (char *)malloc(sizeof(argv[nbr])+1);
                strcpy(*output, argv[nbr]);
                wrd = wrd + strlen(argv[nbr]);
            } 
        }   
    }
}

/* La funció save_state la farem servir per a guardar els estats dels 
moviments a l'struct sCap. */
void save_state(sState *Sts, int *w[NTOWERS], int disc, int m, int towerorg, int towerdest, int ptwr, int depth){
    
    int i, j;
    char twrs[N] = {'A', 'B', 'C'};
    
    Sts[m].move = m;
    Sts[m].prof = depth;
    
    if(towerorg == 0){
        Sts[m].twrorg = twrs[0];
    }else if(towerorg == 1){
        Sts[m].twrorg = twrs[1];
    }else if(towerorg == 2){
        Sts[m].twrorg = twrs[2];
    }
    
    if(towerdest == 0){
        Sts[m].twrdest = twrs[0];
    }else if(towerdest == 1){
        Sts[m].twrdest = twrs[1];
    }else if(towerdest == 2){
        Sts[m].twrdest = twrs[2];
    }
    
    if(m == 0){
        Sts[m].disc = 0;
    }else{
        Sts[m].disc = w[towerdest][ptwr];
    }
    
    for(i = 0; i < NTOWERS; i++){
        for(j = 0; j < disc; j++){
            Sts[m].v[i][j] = w[i][j];
        }      
    }
}

/* La funció resize_states la farem servir per a donar-li, a cada moviment
que es du a terme, la mida de la matriu dins de l'struct. */
void resize_sts(sState *Sts, int Size_Sts, int disc, int m){
    
    int i;
    
    for(i = 0; i < NTOWERS; i++){
        Sts[m].v[i] = (int*)calloc(disc,sizeof(int));
        if (Sts[m].v[i] == NULL){
            printf("Error: problemes de memòria");
            exit(0);
        }
    }
    
}

/* La funció ini_mem la farem servir per a inicialitzar la memòria dinàmica. */
void ini_mem(sState **Sts, int *w[NTOWERS], int nd, int Size_Sts){
    
    int i, m = 0;
    
    for(i = 0; i < NTOWERS; i++){
        w[i] = (int*)calloc(nd,sizeof(int));
        if (w[i] == NULL){
            printf("Error: problemes de memòria");
            exit(0);
        }
    }
    
    *Sts = (sState*)malloc(Size_Sts);
    
}

/* La funció move la farem servir per a moure els diferents discs des de la
torre/pilar origen fins la torre/pilar destí, passant per la auxiliar i, és clar, 
seguint les normes establertes pel joc. */
void move(int towerorg, int towerdest, sState **Sts, int *w[NTOWERS], int *m, int size, int Size_Sts, int disc, int depth){
    
    int postwr = 0, pdisc = 0;
    
    *m = *m + 1; // Augmenta el nombre de moviment
    size = *m + 1; // Augmenta la mida de l'estat
    pdisc = Buscar_disc(towerorg, w, disc);
    postwr = Buscar_disc(towerdest, w, disc) + 1;
    
    w[towerdest][postwr] = w[towerorg][pdisc];
    w[towerorg][pdisc] = 0;
    
    *Sts = (sState *)realloc(*Sts, size*Size_Sts);
    resize_sts(*Sts, Size_Sts, disc, *m);
    save_state(*Sts, w, disc, *m, towerorg, towerdest, postwr, depth);    
}

/* La funció ini_sts la farem servir per a inicialitzar els estats. */
void ini_sts(int nd, sState **Sts, int *w[NTOWERS], int m, int depth){
    
    int i;
    
    for(i = 0; i < NTOWERS; i++){
        (*Sts)->v[i] = (int*)calloc(nd,sizeof(int));
        if ((*Sts)->v[i] == NULL){
            printf("Error: problemes de memòria");
            exit(0);
        }
    }
    save_state(*Sts, w, nd, m, 0, 0, 0, depth);
    
}

/* La funció ini_matrix la farem servir per a inicialitzar la matriu. */
void ini_matrix(int *w[NTOWERS], int nd){
    
    int i, j, disc = nd; 
    
    for(i = 0; i < NTOWERS; i++){
        for(j = 0; j < nd; j++){
            if(i == 0){
                w[i][j] = disc;
                disc--;
            }else{
                w[i][j] = 0;
            }
        }
    }
}

/* La funció hanoi ens venia predeterminada amb l'enunciat de la pràctica
i la utilitzarem per a moure els discos segons les normes del joc. 
La hem modificat per a adaptar-la a les necessitats de la nostra pràctica. */
void hanoi(int nd, int towerorg, int towerdest, int toweraux, sState **Sts, int *w[NTOWERS], int *m, int size, int Size_Sts, int discs, int depth){
    
    depth++;
    if(nd == 1){
        move(towerorg, towerdest, Sts, w, m, size, Size_Sts, discs, depth);
    }else{
        hanoi(nd - 1, towerorg, toweraux, towerdest, Sts, w, m, size, Size_Sts, discs, depth);
        move(towerorg, towerdest, Sts, w, m, size, Size_Sts, discs, depth);
        hanoi(nd - 1, toweraux, towerdest, towerorg, Sts, w, m, size, Size_Sts, discs, depth);
    }
    
}

/* La funció imprimir_move la farem servir per a imprimir els moviments, tant 
de forma textual com de forma gràfica. */
void imprimir_move(sState *Sts, int move, int disc){
    
    int i, j, nd = disc, ntwr = 0, k, maxlength, heigh = disc - 1; 
    printf("Move count %d  Rec Depth %d: it moves disc %d from T%c to T%c", Sts[move].move, 
            Sts[move].prof, Sts[move].disc, Sts[move].twrorg, Sts[move].twrdest); 
    printf("\n");
    
    
    for(i = disc - 1; i >= 0; i--){
            printf("H %d ", heigh); // Altura de les torres
       for(ntwr = 0; ntwr < NTOWERS; ntwr++){
            for(k = 0; k < nd - Sts[move].v[ntwr][i]; k++){
                printf("."); // Espais en blanc corresponent als discs
            }
            for(j = 0; j < Sts[move].v[ntwr][i]; j++){
                printf("*"); // Discs
            }
            printf("| |"); // Pilars
            for(j = 0; j < Sts[move].v[ntwr][i]; j++){
                printf("*"); // Discs
            }
            for(k = 0; k < nd - Sts[move].v[ntwr][i]; k++){
                printf("."); // Espais en blanc corresponent als discs
            }
            printf(" "); // Espais en blanc entre discs
        } 
       printf("\n");
       heigh--;
    } 
    
    maxlength = 6*disc + 15;
    for(i = 0; i < maxlength; i++){
       if(i >= 4){
           printf("%c", '-'); // Terra on es posen els tres pilars
        }else{
           printf(" "); // Espai entre la informació de la altura i l'inici de les torres
        }   
    }
    printf("\n");
    for(j = 0; j < maxlength; j++){
        if(j == disc + 5){
            printf("%c", 'A'); // Indica quin és el pilar A
        }else if(j == 3*disc + 9){
            printf("%c", 'B'); // Indica quin és el pilar B
        }else if(j == 5*disc + 13){
            printf("%c", 'C'); // Indica quin és el pilar C
        }else{
            printf(" "); // Separació entre les tres lletres
        }  
    }
}

/* La funció ini_cap la farem servir per a inicialitzar les capçaleres que
hem d'imprimir a l'inici i al final del joc. */
void ini_cap(sCap **Cap, int Size_cap, int moves, char *nom_fx, char *output, char *codi_op, int discs){
    
    int i = 0, j;
    char *nom;
    
    if(nom_fx == NULL){
        *Cap = (sCap*)malloc(Size_cap);
        (*Cap)[i].Nom = (char *)malloc(strlen("stdout")+1);
        strcpy((*Cap)[i].Nom, "stdout");
        (*Cap)[i].C_op = (char *)malloc(strlen("-")+1);
        strcpy((*Cap)[i].C_op, "-");
    }else{
        *Cap = (sCap*)malloc(Size_cap + strlen(nom_fx));
        (*Cap)[i].Nom = (char*) malloc(strlen(nom_fx)+1);
        nom = (char*)malloc(strlen(nom_fx)) + 5*sizeof(char);
        sprintf(nom, "%s.txt", nom_fx);
       
        strcpy((*Cap)[i].Nom, nom);
       
        (*Cap)[i].C_op = (char*) malloc(strlen(codi_op));
        
        for(j = 0; j < strlen(codi_op)+1; j++){
           (*Cap)[i].C_op[j] = codi_op[j];
        } 
    }
    
    (*Cap)[i].NMov = moves;
    (*Cap)[i].Nd = discs;
    (*Cap)[i].Ntwrs = NTOWERS;
    (*Cap)[i].Out_pth = (char*) malloc(strlen(output));
    strcpy((*Cap)[i].Out_pth, output);
    
}

/* La funció imprimir_cap1 la farem servir per a imprimir la capçalera inicial,
prèvia a la impressió dels moviments. */
void imprimir_cap1(sCap *Cap){
    printf("==============================================\n");
    printf("Command Line entered : %s\n", Cap->Out_pth);
    printf("\nNumber of Towers   : %d\n", Cap->Ntwrs);
    printf("Number of Discs    : %d\n", Cap->Nd);
    printf("Output filename    : %s\n\n", Cap->Nom);
    printf("INIT Time          : ");
        date_and_time();
    printf("==============================================\n");
}

/* La funció imprimir_cap2 la farem servir per a imprimir la capçalera final,
a continuació de la impressió dels moviments. */
void imprimir_cap2(sCap *Cap){
    printf("==============================================\n");
    printf("Number of Towers   : %d\n", Cap->Ntwrs);
    printf("Number of Discs    : %d\n", Cap->Nd);
    printf("Output filename    : %s\n", Cap->Nom);
    printf("Total Number Moves : %d", Cap->NMov);
    printf("\n\nEND Time           : ");
        date_and_time();
    printf("==============================================\n");
}

/* La funció imprimir_all_sts la farem servir per a imprimir tots els
estats del joc, és a dir, cada moviment realitzat, juntament amb les
capçaleres definides a les línies anteriors. */
void imprimir_all_sts(sState *Sts, int m, sCap *Cap, int disc){
    
    int i;
    
    imprimir_cap1(Cap);
    printf("\n");
    for(i = 0; i <= m; i++){
       imprimir_move(Sts, i, disc);
       printf("\n\n");
    }
    printf("\n");
    imprimir_cap2(Cap);
}

/* La funció imprimir_sts_user la farem servir per a imprimir només
els estats que ha demanat l'usuari en la fase interactiva. */
void imprimir_sts_user(sState *Sts, int m, int disc){
    
    int NumMov;
    
    printf("Para mover %d discos se han necesitado %d movimientos.\n", disc, m);
    printf("A continuación, el programa le irá pidiendo el número del movimiento que desee visualizar por pantalla.\n");
    printf("Cuando desee parar de visualizar movimientos intoduzca el 0.\n");
    printf("¿Qué movimiento desea viusalizar?\n");
    scanf("%d", &NumMov);
   
    while((NumMov > m)){
        printf("No ha introducido un número de movimiento posible.\n");
        printf("Vuelva a intentarlo, por favor: ");
        scanf("%d", &NumMov);
    }
    
    while(NumMov != 0){
        imprimir_move(Sts, NumMov, disc);
        printf("\n\n");
        printf("Y ahora, ¿qué movimiento desea viusalizar?\n");
        scanf("%d", &NumMov);
        while((NumMov > m)){
            printf("No ha introducido un número de movimiento posible.\n");
            printf("Vuelva a intentarlo, por favor: ");
            scanf("%d", &NumMov);
        }
    }
    printf("Muy bien, esperemos que haya entendido el funcionamiento de hanoi.\n");
    printf("Muchas gracias, vuelva siempre que lo desee.");
    
}

/* La funció imprimir_move_fitxer fa el mateix que la funció imprimir_move,
amb la salvedat que, aquest cop, en comptes d'imprimir per pantalla, imprimeix
directament en fitxer. */
void imprimir_move_fitxer(FILE *f, sState *Sts, int move, int disc){
    
    int i = 0, j, nd = disc, ntwr = 0, k, maxlength, heigh = disc - 1;
    
    fprintf(f, "Move count %d  Rec Depth %d: it moves disc %d from T%c to T%c", Sts[move].move, 
            Sts[move].prof, Sts[move].disc, Sts[move].twrorg, Sts[move].twrdest); 
    fprintf(f, "\n");
    
    
    for(i = disc - 1; i >= 0; i--){
            fprintf(f, "H %d ", heigh);
       for(ntwr = 0; ntwr < NTOWERS; ntwr++){
            for(k = 0; k < nd - Sts[move].v[ntwr][i]; k++){
                fprintf(f, ".");
            }
            for(j = 0; j < Sts[move].v[ntwr][i]; j++){
                fprintf(f, "*");
            }
            fprintf(f, "| |");
            for(j = 0; j < Sts[move].v[ntwr][i]; j++){
                fprintf(f, "*");
            }
            for(k = 0; k < nd - Sts[move].v[ntwr][i]; k++){
                fprintf(f, ".");
            }
            fprintf(f, " ");
        } 
       fprintf(f, "\n");
       heigh--;
    } 
    
    maxlength = 6*disc + 15;
    for(i = 0; i < maxlength; i++){
       if(i >= 4){
           fprintf(f, "%c", '-');
        }else{
           fprintf(f, " ");
        }   
    }
    fprintf(f, "\n");
    for(j = 0; j < maxlength; j++){
        if(j == disc + 5){
            fprintf(f, "%c", 'A');
        }else if(j == 3*disc + 9){
            fprintf(f, "%c", 'B');
        }else if(j == 5*disc + 13){
            fprintf(f, "%c", 'C');
        }else{
            fprintf(f, " ");
        }  
    }
}

/* La funció date_and_time_fitxer fa el mateix que la funció date_and_time,
amb la salvedat que, aquest cop, en comptes d'imprimir per pantalla, imprimeix
directament en fitxer. */
void date_and_time_fitxer(FILE *f){
    
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    fprintf (f, "%s", asctime (timeinfo) );
    
}

/* La funció imprimir_cap1_fitxer fa el mateix que la funció imprimir_cap1, però
en aquest cas la farem servir per a imprimir la capçalera inicial en un fitxer. */
void imprimir_cap1_fitxer(FILE *f, sCap *Cap){
    fprintf(f, "==============================================\n");
    fprintf(f, "Command Line entered : %s\n", Cap->Out_pth);
    fprintf(f, "\nNumber of Towers   : %d\n", Cap->Ntwrs);
    fprintf(f, "Number of Discs    : %d\n", Cap->Nd);
    fprintf(f, "Output filename    : %s\n", Cap->Nom);
    fprintf(f, "File operation code: %s\n", Cap->C_op);
    fprintf(f, "INIT Time          : ");
         date_and_time_fitxer(f);
    fprintf(f, "==============================================\n");
}

/* La funció imprimir_cap2_fitxer fa el mateix que la funció imprimir_cap2, però
en aquest cas la farem servir per a imprimir la capçalera final en un fitxer. */
void imprimir_cap2_fitxer(FILE *f, sCap *Cap){
    fprintf(f, "==============================================\n");
    fprintf(f, "Number of Towers   : %d\n", Cap->Ntwrs);
    fprintf(f, "Number of Discs    : %d\n", Cap->Nd);
    fprintf(f, "Output filename    : %s\n", Cap->Nom);
    fprintf(f, "File operation code: %s\n", Cap->C_op);
    fprintf(f, "Total Number Moves : %d\n", Cap->NMov);
    fprintf(f, "\n\nEND Time           : ");
         date_and_time_fitxer(f);
    fprintf(f, "==============================================\n");
}

/* La funció imprimir_fitxer la farem servir per imprimir la informació en un fitxer. */
void imprimir_fitxer(sState *Sts, int m, sCap *Cap, int disc){
    
    struct dirent *pDirent;
    DIR *pDir;
    FILE *f;
    int Max = 256, i = 0;
    char nom_fix[Max];
    
	// Obrir directori "Proves", on es guardaran els fitxers
    pDir = opendir("Proves");
    if(pDir == NULL){
        printf("ERROR. No s'ha pogut obrir el directori.\n");
    }
    
	// Obrir el fitxer necessari dins del directori "Proves"
    sprintf(nom_fix, "Proves/%s", Cap[i].Nom);
    f = fopen(nom_fix, Cap[i].C_op);
    if(pDir == NULL){
        printf("ERROR. No s'ha pogut obrir el fitxer.\n");
    }
    
    imprimir_cap1_fitxer(f, Cap); // Imprimeix capçalera incial
    fprintf(f, "\n");
    
	// Imprimeix cada moviment
    for(i = 0; i <= m; i++){
        imprimir_move_fitxer(f, Sts, i, disc);
        fprintf(f, "\n");
    }
    
    fprintf(f, "\n");
    imprimir_cap2_fitxer(f, Cap); // Imprimeix capçalera final
    fprintf(f, "\n\n");
    
	// Tanca el directori i tanca el fitxer
    closedir(pDir);
    fclose(f);
}

/* La funcio free_mem la utilitzarem per a alliberar la memoria dinamica
un cop acabada la realitzacio del joc. */
void free_mem(sState **Sts, int *w[NTOWERS], sCap **Cap, int moves){
    
    int i, j;
    
    for(j = 0; j < moves; j++){
       for(i = 0; i < NTOWERS; i++){
            free((*Sts)[j].v[i]);
       } 
    }
    
    free(*Sts);
    *Sts = NULL;
    
    for(i = 0; i < NTOWERS; i++){
        free(w[i]);
    } 
    
    free(*Cap);
    
}