#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// structura aferenta unui nod de lista
typedef struct nod {
    char *nume;
    struct nod *next;
    struct nod *prev;
    int numar_nod;
} Nod, *PNod;
// structura aferenta grafului
typedef struct graf {
    Nod **pointers;
} g;
// structura aferenta unui arbore binar de cautare
typedef struct bst_node {
    char nume[100];
    struct bst_node *parent;
    struct bst_node *left;
    struct bst_node *right;
} bst_node_t, *p_bst_node_t;
// structura aferenta unui nod din structura noastra de 
typedef struct el {
    int nr_nod;
    struct el *next;
} El_Que_Stack, *PEl_Que_Stack;
typedef struct QS {
    PEl_Que_Stack front;
    PEl_Que_Stack back;
} Que_Stack, *P_Que_Stack;
// Funcție de inserare recursiva într-un arbore binar de căutare
void insert(bst_node_t **root_ptr, char nume[30]) {
    if ( (*root_ptr) == NULL ) {
      bst_node_t* nod_nou = (bst_node_t*)malloc(sizeof(bst_node_t));
      strcpy(nod_nou->nume, nume);
      nod_nou->left = nod_nou->right = NULL;
      nod_nou->parent = *root_ptr;
      (*root_ptr) = nod_nou;
      return;
    }
    if (strcmp(nume,(*root_ptr)->nume) < 0 )
        insert(&((*root_ptr)->left), nume);
    else
        insert(&((*root_ptr)->right), nume);
}
// Functie ce calculeaza minimul dintre 2 valori
int min(int a, int b) {
    if (a > b)
        return b;
    return a;
}
// Dfs-ul aferent taskului3, construit cu ajutorul pseudocodului oferit. Algoritmul
// Lui tarjan se bazeaza pe gasirea puntilor dintr-un graf.
void dfs_task3(g *graf, int source, int *timp, int *idx, int *low, int *pi, bst_node_t **pom, int *contor) {
    char nume_combinat[100];
    idx[source] = (*timp);
    low[source] = (*timp);
    (*timp) = (*timp) + 1;
    Nod *aux = graf->pointers[source];
    while (aux->next) {
        aux = aux->next;
        if (aux->numar_nod != pi[source]) {
            if (idx[aux->numar_nod] == -1) {
                pi[aux->numar_nod] = source;
                dfs_task3(graf, aux->numar_nod, timp, idx, low, pi, pom, contor);
                low[source] = min(low[aux->numar_nod], low[source]);
                if (low[aux->numar_nod] > idx[source]) {
                    (*contor) = (*contor) + 1;
                    if (strcmp(graf->pointers[source]->nume, graf->pointers[aux->numar_nod]->nume) < 0) {
                        graf->pointers[source]->nume[strcspn(graf->pointers[source]->nume, "\n")] = 0;
                        strcpy(nume_combinat, graf->pointers[source]->nume);
                        strcat(nume_combinat, " ");
                        strcat(nume_combinat, graf->pointers[aux->numar_nod]->nume);
                        strcat(graf->pointers[source]->nume, "\n");
                    }
                    else {
                        graf->pointers[aux->numar_nod]->nume[strcspn(graf->pointers[aux->numar_nod]->nume, "\n")] = 0;
                        strcpy(nume_combinat, graf->pointers[aux->numar_nod]->nume);
                        strcat(nume_combinat, " ");
                        strcat(nume_combinat, graf->pointers[source]->nume);
                        strcat(graf->pointers[aux->numar_nod]->nume, "\n");
                    }
                    insert(pom, nume_combinat);
                    nume_combinat[0] = '\0';
                }
            }
            else {
                low[source] = min(idx[aux->numar_nod], low[source]);
            }
        }
    }
}
// Functie ce insereaza un element in capatul stivei
void push_back(P_Que_Stack q, int value) {
    PEl_Que_Stack nod = (PEl_Que_Stack)malloc(sizeof(El_Que_Stack));
    nod->nr_nod = value;
    nod->next = NULL;
    if (q->front == NULL) {
        q->front = q->back = nod;
    }
    else {
        q->back->next = nod;
        q->back = nod;
    }
}
// Functie ce extrage valoarea primului element din stiva, stergand ulterior acel nod, asigurand
// Mutarea la dreapta a headerului
int pop_front(P_Que_Stack q) {
    struct el *aux = q->front;
    q->front = q->front->next;
    int cp = aux->nr_nod;
    free(aux);
    return cp;
}
// Un bfs recursiv adaptat pentru a calcula cel mai scurt drum posibil. Ideea este
// De a folosi un vector de distante in care, initial, avem valoarea 0 pe pozitia aferenta
// Nodului apelat de graf apelat (distanta la el insusi fiind 0), si -1 pe toate celelalte pozitii.
// Ne folosim de acest vector si pentru a verifica daca un anumit nod a fost vizitat, nemaiavand nevoie
// De clasicul vector de vizitare. Adunam din aproape in aproape 1 de la un nod la celalalt, la final
// Vectorul indicandu-ne pe pozitia X care este distanta de la nodul apelat pana la nodul X.
void bfs_recursive(g *graf, int *dist, P_Que_Stack queue) {
    if (queue->front == NULL)
        return;
    int val = pop_front(queue);
    Nod *aux = graf->pointers[val];
    while (aux->next) {
        aux = aux->next;
        if (dist[aux->numar_nod] == -1) {
            push_back(queue, aux->numar_nod);
            dist[aux->numar_nod] = dist[val] + 1;
        }
    }
    bfs_recursive(graf, dist, queue);
}
// Functie de eliberare a memoriei pentru o lista data ca parametur
void golire_lista(PNod lista) {
    PNod aux = lista;
    while (aux ->next)
        aux = aux->next;
    while (aux != lista) {
        PNod aux2 = aux;
        aux = aux->prev;
        free(aux2);
    }
    free(lista->nume);
    free(lista);
}
// Functie clasica de DFS recursiv pe care o folosim pentru a numara cate noduri contine
// O componenta conexaa
void dfs_recursive(g *graph, int sursa, int *vizitat, int *contor) {
    vizitat[sursa] = 1;
    Nod *aux = graph->pointers[sursa];
    while (aux->next != NULL) {
        aux = aux->next;
        if (vizitat[aux->numar_nod] == 0) {
            (*contor)++;
            dfs_recursive(graph, aux->numar_nod, vizitat, contor);
        }
    }
}
// O parcurgere clasica dfs prin care inseram elementele grafului intr-un arbore
// Binar de cautare pentru a sorta lexicografic numele de actori
void dfs_afisare(g *graph, int sursa, int* vizitat, FILE* foutput, bst_node_t **pom) {
    vizitat[sursa] = 1;
    insert(pom, graph->pointers[sursa]->nume);
    Nod *aux = graph->pointers[sursa];
    while (aux->next != NULL) {
        aux = aux->next;
        if (vizitat[aux->numar_nod] == 0) {
            dfs_afisare(graph, aux->numar_nod, vizitat, foutput, pom);
        }
    }
}
// Functie recurisva de eliberare a memorie intr-un arbore binar de cautare
void remove_tree(bst_node_t **root_ptr) {
    if ((*root_ptr) == NULL)
        return;
    remove_tree(&(*root_ptr)->left);
    remove_tree(&(*root_ptr)->right);
    free((*root_ptr));
}
// Functie de afisare de tip in order a arboreului binar de cautare
void printInorder(bst_node_t *pom, FILE* foutput) {
    if (pom == NULL)
        return;
    printInorder((pom->left), foutput);
    fprintf(foutput, "%s", pom->nume);
    printInorder(pom->right, foutput);
}
// Functie ce verifica daca in lista de adiacenta a nodului 1 se regaseste
// nodul 2, astfel fiind verificata conditia de existenta a muchiei
int verif_muchie(g *graf, int nod1, int nod2) {
    Nod *aux = graf->pointers[nod1];
    while (aux->next) {
        aux = aux->next;
        if (aux->numar_nod == nod2)
            return 1;
    }
    return 0;
}
// Functie ce adauga primul nod de lista intr-o lista initial goala, fixand
// headerul aferent si asigurand realocarea memoriei pentru vectorul de liste
void adaugare_nod(int *capacitate, int *lungime, g *graf, char *nume_actor) {
    Nod* lista_noua = (Nod*)malloc(sizeof(Nod));
    lista_noua->nume = (char*)malloc((strlen(nume_actor) + 2) * (sizeof(char)));
    if ((*capacitate) == (*lungime)) {
        (*capacitate) = (*capacitate) * 2;
        graf->pointers = (Nod**)realloc(graf->pointers,sizeof(Nod*)*(*capacitate));
    }
    lista_noua->next = NULL;
    lista_noua->prev = NULL;
    strcpy(lista_noua->nume, nume_actor);
    graf->pointers[(*lungime)] = lista_noua;
    lista_noua->numar_nod = (*lungime);
    (*lungime) = (*lungime) + 1;
}
// Functie de adaugare a unei ,,muchii" ce consta in adaugarea unui nod
// In lista de adiacenta a celui de-al doilea nod si vice-versa
void adaugare_muchie(int lungime, int vecin, g *graf) {
    Nod* nou= (Nod*)malloc(sizeof(Nod));
    Nod* aux = graf->pointers[lungime];
    while (aux->next != NULL)
        aux = aux->next;
    aux->next = nou;
    nou->prev = aux;
    nou->numar_nod = vecin;
    nou->next = NULL;
    Nod* nou_2 = (Nod*)malloc(sizeof(Nod));
    Nod *aux2 = graf->pointers[vecin];
    while (aux2->next != NULL)
        aux2 = aux2->next;
    aux2->next = nou_2;
    nou_2->prev = aux2;
    nou_2->numar_nod = lungime;
    nou_2->next = NULL;
}
// Functie generala pentru rezolvarea temei, intrunind toate cele 3 taskuri in functie
// De parametrul primit prin parametru ,,logic"
void task(FILE* finput, FILE* foutput, g *graf, int logic) {
    char linie[100];
    int capacitate = 5, lungime = 0, i, j, k, poz_start;
    graf->pointers = (PNod*)malloc(capacitate * sizeof(PNod));
    int nr_filme = atoi(fgets(linie, 100, finput)), nr_actori;
    int *lungime_filme = (int*)malloc(nr_filme * sizeof(int));
    for (i = 0; i < nr_filme; i++) {
        fgets(linie, 100, finput);
        nr_actori = atoi(fgets(linie, 100, finput));
        int *vector_film_curent = (int*)malloc(nr_actori*sizeof(int));
        for (j = 0; j < nr_actori; j++) {
            fgets(linie, 100, finput);
            int logic = 0;
            // Breakul de mai jos ne ajuta sa identificam daca, in cazul in care actorul
            // A mai jucat in vreun film, sa aflam lista de adiacenta corespunzatore acestuia
            for (k = 0; k < lungime; k++) {
                if (strcmp(linie, graf->pointers[k]->nume) == 0) {
                    logic = 1;
                    break;
                }
            }
            // Daca actorul nu a mai jucat in niciun film pana acum
            if (!logic) {
                vector_film_curent[j] = lungime;
                adaugare_nod(&capacitate, &lungime, graf, linie);
                for (poz_start = 0; poz_start < j; poz_start++)
                    adaugare_muchie(lungime - 1, vector_film_curent[poz_start], graf);
            }
            // Daca actorul a mai jucat si in alte filme atunci cream legaturile aferente intre
            // Acesta si celelalte noduri din film, avand grija cu ajutorul functiei verif_muchie
            // Sa nu cream legaturi cu alti actori care au mai aparut in filme
            else {
                vector_film_curent[j] = k;
                for (poz_start = 0; poz_start < j ; poz_start++) {
                    if (verif_muchie(graf, graf->pointers[k]->numar_nod, vector_film_curent[poz_start]) == 0)
                        adaugare_muchie(k, vector_film_curent[poz_start], graf);
                }
            }
        }
        free(vector_film_curent); 
    }
    // Destinat taskului 1
    if (logic == 1) {
        int contor, Max = -1, copie;
        int *viz = (int*)calloc(lungime, sizeof(int));
        // Cu ajutorul unui dfs parcurgem componentele conexe ale grafului pentru a determina
        // Cea mai mare componenta conexa, reinitializand o variabila Max ori de cat ori
        // Gasim o componenta de dimensiune mai mare decat precedentele si retinem intr-o
        // Variabila ,,copie" indexul cu care am apelat dfs-ul pentru componenta respectiva
        for (i = 0; i < lungime; i++) {
            if (viz[i] == 0) {
                contor = 1;
                dfs_recursive(graf, i, viz, &contor);
                if (contor > Max) {
                    Max = contor;
                    copie = i;
                }
            }
        }
        free(viz);
        viz = calloc(lungime, sizeof(int));
        bst_node_t *pom = NULL;
        // Cu ajutorul acestei functii de dfs introducem numele din componenta 
        // Conexa de dimensiune maxima intr-un arbore binar de cautare cu care vom sorta
        // Automat numele in ordine lexicografica
        dfs_afisare(graf, copie, viz, foutput, &pom);
        // Afisam lungimea celei mai mari componente conexe
        fprintf(foutput, "%d\n", Max);
        // Afisam in fisierul de output numele ordonate
        printInorder(pom, foutput);
        free(viz);
        remove_tree(&pom);
    }
    // Destinat taskului 2
    else if (logic == 2) {
        char nume1[100], nume2[100];
        int nr1, nr2;
        fgets(nume1, 100, finput);
        fgets(nume2, 100, finput);
        for (i = 0; i < lungime; i++)
            if (strcmp(graf->pointers[i]->nume, nume1) == 0)
                nr1 = i;
        for (i = 0; i < lungime; i++)
            if (strcmp(graf->pointers[i]->nume, nume2) == 0)
                nr2 = i;
        int *dist = (int*)malloc(lungime * sizeof(int));
        for (i = 0; i < lungime; i++)
            dist[i] = -1;
        P_Que_Stack queue = (P_Que_Stack)malloc(sizeof(Que_Stack));
        queue->front = queue->back = NULL;
        push_back(queue, nr1);
        dist[nr1] = 0;
        // Cu ajutorul acestui bfs modificat calculam distanta de la un nod la toate
        // Celelalte noduri
        bfs_recursive(graf, dist, queue);
        fprintf(foutput, "%d\n", dist[nr2]);
        free(queue);
        free(dist);
    }
    // Destinat taskului 3
    else if (logic == 3) {
        bst_node_t *pom = NULL;
        int timp = 0, contor = 0;
        int *idx = (int*)malloc(lungime * sizeof(int));
        int *low = (int*)malloc(lungime * sizeof(int));
        int *pi = (int *)malloc(lungime * sizeof(int));
        for (i = 0; i < lungime; i++) {
            idx[i] = -1;
            low[i] = __INT_MAX__;
            pi[i] = __INT_MAX__;
        }
        for (i = 0; i < lungime; i++)
            if (idx[i] == -1) {
                dfs_task3(graf, i, &timp, idx, low, pi, &pom, &contor);
            }
        fprintf(foutput, "%d\n", contor);
        printInorder(pom, foutput);
        remove_tree(&pom);
        free(idx);
        free(low);
        free(pi);
    }
    free(lungime_filme);
    for (i = 0; i < lungime; i++) {
        golire_lista(graf->pointers[i]);
    }
    free(graf->pointers);
    free(graf);
}

int main(int argc, char** argv) {
    // Alocam dinamic graful cu care vom lucra si deschidem fisierele de input si de output
    g *graf = (g*)malloc(sizeof(g));
    FILE *finput  = fopen(argv[2], "r");
    FILE *foutput = fopen(argv[3], "w");
    // In functie de argumentul primit in linia de comanda apelam functia aferenta taskului respectiv
    if (strcmp(argv[1], "-c1") == 0)
        task(finput, foutput, graf, 1);
    else if (strcmp(argv[1], "-c2") == 0)
        task(finput, foutput, graf, 2);
    else if (strcmp(argv[1], "-c3") == 0)
        task(finput, foutput, graf, 3);
    // Inchidem fisierele de input si output
    fclose(finput);
    fclose(foutput);
    return 0;
}