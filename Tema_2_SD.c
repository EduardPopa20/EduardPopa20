#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// Structura de tip arbore cu campuri diferite in functie de
// Taskul pe care il rezolvam
typedef struct arbore {
    // task3
    int inaltime_arbore_t3;
    int are_valoare;
    int valoare;
    int final;
    int frunza;
    int nivel;
    // task1 + task2 + task3
    int dim_fii;
    // task1 + task2
    int tabla[3][3];
    char TF;
    int logic_inceput;
    int logic;
    struct arbore **fii;
    struct arbore *parent;
} arb, *p_arb;
// Functia de verificare a finalitatii jocului de X si O
int verificare(int matr[3][3]) {
    if (matr[0][0] == matr[1][1] && matr[1][1] == matr[2][2] && (matr[0][0] == 1 || matr[0][0] == 0))
        return 1;
    if (matr[0][2] == matr[1][1] && matr[1][1] == matr[2][0] && (matr[0][2] == 1 || matr[0][2] == 0))
        return 1;
    if (matr[0][0] == matr[0][1] && matr[0][1] == matr[0][2] && (matr[0][0] == 1 || matr[0][0] == 0))
        return 1;
    if (matr[1][0] == matr[1][1] && matr[1][1] == matr[1][2] && (matr[1][0] == 1 || matr[1][0] == 0))
        return 1;
    if (matr[2][0] == matr[2][1] && matr[2][1] == matr[2][2] && (matr[2][0] == 1 || matr[2][0] == 0))
        return 1;
    if (matr[0][0] == matr[1][0] && matr[1][0] == matr[2][0] && (matr[0][0] == 1 || matr[0][0] == 0))
        return 1;
    if (matr[0][1] == matr[1][1] && matr[1][1] == matr[2][1] && (matr[0][1] == 1 || matr[0][1] == 0))
        return 1;
    if (matr[0][2] == matr[1][2] && matr[1][2] == matr[2][2] && (matr[0][2] == 1 || matr[0][2] == 0))
        return 1;
    return 0;
}
// Functie de afisare a unei table la o anumita pozitie
void printare_task1_tabla(arb* arbore, FILE* fout, int tab) {
    int i;
    for (i = 0; i < tab; i++)
        fprintf(fout, "%c", 9);
    if (arbore->tabla[0][0] == 0)
        fprintf(fout, "%c ", 'O');
    else if (arbore->tabla[0][0] == 1)
        fprintf(fout, "%c ", 'X');
    else fprintf(fout, "%c ", '-');
    if (arbore->tabla[0][1] == 0)
        fprintf(fout, "%c ", 'O');
    else if (arbore->tabla[0][1] == 1)
        fprintf(fout, "%c ", 'X');
    else fprintf(fout, "%c ", '-');
    if (arbore->tabla[0][2] == 0)
        fprintf(fout, "%c\n", 'O');
    else if (arbore->tabla[0][2] == 1)
        fprintf(fout, "%c\n", 'X');
    else fprintf(fout, "%c\n", '-');
    for (i = 0; i < tab; i++)
        fprintf(fout, "%c", 9);
    if (arbore->tabla[1][0] == 0)
        fprintf(fout, "%c ", 'O');
    else if (arbore->tabla[1][0] == 1)
        fprintf(fout, "%c ", 'X');
    else fprintf(fout, "%c ", '-');
    if (arbore->tabla[1][1] == 0)
        fprintf(fout, "%c ", 'O');
    else if (arbore->tabla[1][1] == 1)
        fprintf(fout, "%c ", 'X');
    else fprintf(fout, "%c ", '-');
    if (arbore->tabla[1][2] == 0)
        fprintf(fout, "%c\n", 'O');
    else if (arbore->tabla[1][2] == 1)
        fprintf(fout, "%c\n", 'X');
    else fprintf(fout, "%c\n", '-');
    for (i = 0; i < tab; i++)
        fprintf(fout, "%c", 9);
    if (arbore->tabla[2][0] == 0)
        fprintf(fout, "%c ", 'O');
    else if (arbore->tabla[2][0] == 1)
        fprintf(fout, "%c ", 'X');
    else fprintf(fout, "%c ", '-');
    if (arbore->tabla[2][1] == 0)
        fprintf(fout, "%c ", 'O');
    else if (arbore->tabla[2][1] == 1)
        fprintf(fout, "%c ", 'X');
    else fprintf(fout, "%c ", '-');
    if (arbore->tabla[2][2] == 0)
        fprintf(fout, "%c\n", 'O');
    else if (arbore->tabla[2][2] == 1)
        fprintf(fout, "%c\n", 'X');
    else fprintf(fout, "%c\n", '-');
    fprintf(fout, "%c", '\n');
}
// Functia de afisare recursiva pentru taskul1 ce se foloseste de functia
// De afisare a tablei de mai sus
void printare_task1(arb* arbore, FILE* f, int tab) {
    int i;
    for (i = 0; i < arbore->dim_fii; i++) {
        int x = tab + 1;
        printare_task1_tabla(arbore->fii[i], f, x);
        printare_task1(arbore->fii[i], f, x);
    }
}
void printare_task2(arb* arbore, FILE* f, int tab) {
    int i;
    if (arbore->parent == NULL)
        fprintf(f, "%c\n", arbore->TF);
    for (i = 0; i < arbore->dim_fii; i++) {
        int x = tab + 1;
        int j;
        for (j = 0; j < x; j++)
            fprintf(f, "%c", 9);
        fprintf(f, "%c\n", arbore->fii[i]->TF);
        printare_task2(arbore->fii[i], f, x);
    }
}
void golire(arb* tree) {
    //printf("%d ", tree->dim_fii);
    int i;
    for (i = 0; i < tree->dim_fii; i++) {
        golire(tree->fii[i]);
    }
    if (tree->fii != NULL)
        free(tree->fii);
    free(tree);
}
// Functie de adaugare 
void adaugare(arb* tree, int logic, FILE* f) { 
    int i;
    // Parcurgem toti fii nodului dat ca parametru
    for (i = 1; i <= tree->dim_fii; i++) {    
        int j, k = 0, contor = 0;
        for (j = 0; j <= 2; j++)
            for (k = 0; k <= 2; k++) {
                if (tree->tabla[j][k] == 2)
                    contor++;
                // Noi trebuie sa marcam un camp ce reprezinta „-” in „X” sau „O” treptat,
                // De atatea ori cati fii sunt si diferit in functie de numarul fiului la care ne aflam.
                // (Daca nu, se va umple de X sau O tabla noastra din start si nu vom avea generarea de
                // tip backtracking pe care ne-o dorim)
                if (contor == i) {
                    arb* nod = (arb*)malloc(sizeof(arb));
                    nod->fii = (struct arbore**)malloc((tree->dim_fii + 5)*sizeof(struct arbore*));
                    nod->parent = tree;
                    tree->fii[i-1] = nod;
                    int a, b;
                    // Adaugam tabla si avem grija sa schimbam campul unde am mutat
                    for (a = 0; a <= 2; a++)
                        for(b = 0; b <= 2; b++)
                            nod->tabla[a][b] = tree->tabla[a][b];
                    nod->tabla[j][k] = logic;
                    int contor2 = 0;
                    // Numaram cate liniute avem in tabla actualizata
                    for (j = 0; j <= 2; j++)
                        for (k = 0; k <= 2; k++)
                            if (nod->tabla[j][k] == 2)
                                contor2++;
                    if (verificare(nod->tabla) == 1)
                        nod->dim_fii = 0;
                    else
                        nod->dim_fii = contor2;
                    nod->logic_inceput = nod->parent->logic_inceput;
                    int logic2;
                    if (logic == 1)
                        logic2 = 0;
                    else
                        logic2 = 1;
                    nod->logic = logic2;
                    adaugare(nod, logic2, f);
                }
        } 
    }
}
void task2(arb* arbore) {
    int i;
    // Daca ne aflam pe nivel terminal, verificam cine a avut ultima mutare si daca 
    // Tabla a ajuns castigatoare, facand atribuirile aferente
    if (arbore->dim_fii == 0) {
        if (arbore->logic != arbore->logic_inceput && verificare(arbore->tabla) == 1) {
            arbore->TF = 'T';
        }
        else
            arbore->TF = 'F';
        return;
    }
    // Mergem in adancime
    for (i = 0; i < arbore->dim_fii; i++)
        task2(arbore->fii[i]);
    // In functie de cine muta, aplicam Min sau Max
    if (arbore->logic_inceput != arbore->logic) {
        int var = 1, i;
        for (i = 0; i < arbore->dim_fii; i++)
            if (arbore->fii[i]->TF == 'F')
                var = 0;
        if (var == 1)
            arbore->TF = 'T';
        else 
            arbore->TF = 'F';
    }
    else {
        int var = 0;
        for (i = 0; i < arbore->dim_fii; i++)
            if (arbore->fii[i]->TF == 'T')
                var = 1;
        if (var == 1)
            arbore->TF = 'T';
        else 
            arbore->TF = 'F';
    }
}
void citire_task3(arb* arbore, FILE* f) {
    if (arbore->frunza == 1) {
        return;
    }
    // Daca ne aflam pe un nod terminal pentru generarea la care ne aflam, trebuie sa 
    // Il „marcam” ca fiind non-terminal si sa ii atribuim fii aferenti, marcandu-i pe acestia
    // La randul lor
    if (arbore->final == 1) {
        arbore->final = 0;
        arbore->fii = (struct arbore**)malloc((arbore->dim_fii+1)*sizeof(struct arbore*));
        int j;
        char s[10];
        for (j = 0; j < arbore->dim_fii; j++) {
            fscanf(f, "%s", s);
            arb *nod = (arb*)malloc(sizeof(arb));
            if (s[0] == '(') {
                nod->dim_fii = (atoi)(s+1);
                nod->parent = arbore;
                arbore->fii[j] = nod;
                nod->final = 1;
                nod->frunza = 0;
                nod->fii = NULL;
                nod->are_valoare = 0;
                nod->nivel = nod->parent->nivel+1;
            }
            else if (s[0] == '[') {
                nod->dim_fii = 0;
                nod->frunza = 1;
                nod->valoare = (atoi)(s+1);
                nod->parent = arbore;
                arbore->fii[j] = nod;
                nod->fii = NULL;
                nod->are_valoare = 1;
                nod->nivel = nod->parent->nivel+1;
            }
        }
        return;
    }
    // Mergem in adancime pana la ultimul strat aferent generarii la care ne aflam
    int k;
    for (k = 0; k < arbore->dim_fii; k++) {
        citire_task3(arbore->fii[k], f);
    }
}
void task3(arb* arbore) {
    // Daca ajungem pe frunze ne intoarcem
    if (arbore->are_valoare == 1) // Se putea folosi si arbore->frunza == 1;
        return;
    int i;  
    // Ne ducem in adancime
    for (i = 0; i < arbore->dim_fii; i++)
        task3(arbore->fii[i]);
    // Daca ne aflam deasupra unui nivel pe care exista valori stocate in noduri,
    // Verificam daca muta Min sau Max si calculam minimul sau maximul fiilor, atribuindu-l
    // Nodului parinte, in functie de caz.
    if (arbore->nivel % 2 == 1) {
        int max = arbore->fii[0]->valoare, j;
        for (j = 1; j < arbore->dim_fii; j++)
            if (arbore->fii[j]->valoare > max)
                max = arbore->fii[j]->valoare;
        arbore->valoare = max;
        arbore->are_valoare = 1;
    }
    else {
        int min = arbore->fii[0]->valoare, j;
        for (j = 1; j < arbore->dim_fii; j++)
            if (arbore->fii[j]->valoare < min)
                min = arbore->fii[j]->valoare;
        arbore->valoare = min;
        arbore->are_valoare = 1;
    }
}
// Functie de afisare pentru task3
void printare_task3(arb* arbore, FILE* f, int tab) {
    if (arbore->parent == NULL) {
        fprintf(f, "%d\n", arbore->valoare);
    }
    int i;
    for (i = 0; i < arbore->dim_fii; i++) {
        int x = tab + 1;
        int j;
        for (j = 0; j < x; j++)
            fprintf(f, "%c", 9);
        fprintf(f, "%d\n", arbore->fii[i]->valoare);
        printare_task3(arbore->fii[i], f, x);
    }
}
int main(int argc, char** argv) {
    int logic = 0, i = 0, j = 0, tab = 0;
    arb* arbore = (arb*)malloc(sizeof(arb));
    arbore->parent = NULL;
    FILE* finput = fopen(argv[2], "r");
    FILE* fout = fopen(argv[3], "w");
    // Daca primim ca argument in linia de comanda „-c1” sau „-c2” va trebui sa
    // Consturim tabla initiala ce se afla in nodul root al arboreului si sa retinem
    // Intr-un camp de tip intreg, numarul fiilor acestuia. De asemenea, trebuie sa
    // Pastram intr-o variabila logica daca mutam cu jucatorul X(1) sau cu jucatorul O(0).
    if (strcmp(argv[1], "-c1") == 0  || strcmp(argv[1], "-c2") == 0) {
        arbore->dim_fii = 0;
        int ch = fgetc(finput);
        // Daca logic = 1 mutam cu X, daca este 0 mutam cu O
        if (ch ==  88)
            logic = 1;
        // Citim tabla din input si o atribuim nodului root
        while ( (ch = fgetc(finput)) != EOF) {
            if (ch == 79)
                arbore->tabla[i][j] = 0;
            else if (ch == 88)
                arbore->tabla[i][j] = 1;
            else if (ch == 45)
                arbore->tabla[i][j] = 2;
            if (ch == 79 || ch == 88 || ch == 45) {
                j++;
                if (j == 3) {
                    j = 0;
                    i++;
                }
            }
        }
        // Incrementam o variabila de tip int de fiecare data cand intalnim caracterul
        // „-”, reprezentat in matricea noastra de valoarea 2. Astfel, numarul de liniute
        // Corespunde numarului de mutari posibile din scenariul urmator, adica numarul
        // De fii pe care il va avea rootul.
        for (i = 0; i <= 2; i++)
            for (j = 0; j <= 2; j++)
                if (arbore->tabla[i][j] == 2)
                    arbore->dim_fii++;
        // Alocam memorie dinamic pentru vectorul de fii.
        arbore->fii = (struct arbore**)malloc(sizeof(struct arbore*)*(arbore->dim_fii));
        // Aceasta variabila este aceeasi pentru toate nodurile din arbore si ne ajuta sa ne dam seama
        // Cine muta la orice pas, astfel trebuie doar sa verificam daca variabila logic de la pasul respectiv
        // Corespunde jucatorului cu care jucam noi.
        arbore->logic_inceput = arbore->logic = logic;
    }
    // In functie de argumentul primit in linia de comanda apelam functiile de adaugare si de 
    // Printare aferente.
    if (strcmp(argv[1], "-c1") == 0) {
        adaugare(arbore, logic, fout);
        printare_task1_tabla(arbore, fout, 0);
        printare_task1(arbore, fout, tab);
    }
    else if (strcmp(argv[1], "-c2") == 0) {
        adaugare(arbore, logic, fout);
        task2(arbore);
        printare_task2(arbore, fout, 0);
    }
    else {
        char s[10];
        fscanf(finput, "%s", s);
        arbore->inaltime_arbore_t3 = (atoi)(s);
        fscanf(finput, "%s", s);
        arbore->dim_fii = (atoi)(s+1);
        arbore->final = 1;
        arbore->frunza = 0;
        arbore->are_valoare = 0;
        arbore->nivel = 1;
        int l;
        // Vom genera rand pe rand nivelurile din arbore astfel vom apela iterativ functia
        // De atatea ori cu cat este egalal inaltimea arborelui.
        for (l = 0; l < arbore->inaltime_arbore_t3; l++)  
            citire_task3(arbore, finput);
        // Vom genera recursiv toate valorile din fiecare nod de arbore.
        task3(arbore);
        printare_task3(arbore, fout, 0);
    }
    // Golim memoria si inchidem fisierele de input si output
    golire(arbore);
    fclose(finput);
    fclose(fout);
    return 0;
}
