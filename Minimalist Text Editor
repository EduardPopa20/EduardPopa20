#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// S    T    I     V      A
// ----------------------Structura stiva;
// Structura ce-mi permite sa retin numarul liniei si al coloanei
// La care se afla cursoru, in timp real
typedef struct pozitie {
    int linie;
    int coloana;
} Poz;
// Structura ce reprezinta stiva cu nodurile aferent, noduri ce pot contine
// Diferite siruri, pozitii sau litere in functie de comanda 
typedef struct el_stiva {
    char litera;
    char* sir_memorat;
    char* sir_memorat2;
    Poz* pozitii;
    char* comanda;
    struct el_stiva *next;
} Stiva, *PStiva;
// ---------------------- O P E R A T I I     S T I V A
// Operatie de adaugare in stiva ce aloca memorie dinamic campurilor necesare
// In functie de comanda avuta, in caz contrar se apeleaza cu parametri speciali
// Pentru a sti cand sa nu alocam memorie dinamic campului respectiv
PStiva adaugareStiva(PStiva s, char *comanda_mem, char* sir_m,
                    char* sir_m2, char litera_mem, Poz* pozitie_mem) {
    PStiva p = (Stiva*)malloc(sizeof(Stiva));
    p->comanda = (char*)malloc(sizeof(char)*(strlen(comanda_mem)+1));
    strcpy(p->comanda, comanda_mem);
    if (strcmp(sir_m, "artificiu ingineresc") != 0) {
        p->sir_memorat = (char*)malloc((strlen(sir_m)+1)*sizeof(char));
        strcpy(p->sir_memorat, sir_m);
    }
    else 
        p->sir_memorat = NULL;
    if (strcmp(sir_m2, "ingineresc artificiu") != 0) {
        p->sir_memorat2 = (char*)malloc((strlen(sir_m2) + 1)*sizeof(char));
        strcpy(p->sir_memorat2, sir_m2);
    }
    else
        p->sir_memorat2 = NULL;
    if (litera_mem != '1')
        p->litera = litera_mem;
    if (pozitie_mem->linie != -1) {
        p->pozitii = (Poz*)malloc(sizeof(Poz));
        p->pozitii->linie = pozitie_mem->linie;
        p->pozitii->coloana = pozitie_mem->coloana;
    }
    else
        p->pozitii = NULL;
    // Daca stiva este nula fixam headerul stivei pe primul element de adaugat
    if ( s == NULL) {
        p->next = NULL;
        s = p;
    }
    // Daca stiva nu este nula atunci fixam legatura din elementul adaugat si
    // Nodul unde pointeaza headerul stivei, schimband ulterior headerul
    else {
        p->next = s;
        s = p;
    }
    return s;
}
// Functie ce elimina un element din stiva, aceasta functionand pe acelasi principiu
// De verificare a parametrilor speciali sau concreti si eliberand memoria doar unde e nevoie
PStiva eliminare_el_stiva(PStiva s, char *comanda_mem, char* sir_m, 
                          char* sir_m2, char litera_mem, Poz* pozitie_mem) {
    Stiva* aux;
    aux = s;
    s = aux->next;
    free(aux->comanda);
    if (strcmp(sir_m, "artificiu ingineresc") != 0) {
        free(aux->sir_memorat);
    }
    if (strcmp(sir_m2, "ingineresc artificiu") != 0)
        free(aux->sir_memorat2);
    if (pozitie_mem->linie != -2)
        free(aux->pozitii);
    free(aux);
    return s;
}
// L   I    S   T    A        D    U    B    L    A
//---------------------- Structuri lista dubla
typedef struct nod {
    char caracter;
    struct nod *next;
    struct nod *prev;
} Nod, *PNod;
// Structura unde retin headerul listei duble, un pointer spre ultimul element din lista
// Si cursorul care se misca in timp real pe elementul dorit
typedef struct cap {
    PNod inceput;
    PNod sfarsit;
    PNod cursor;
} Capete;
//---------------------- Operatii Lista Dubla
void initCapete(Capete* capete) {
    capete->inceput = capete->sfarsit = capete->cursor = NULL;
}
// Functie de adaugare a unui nod in lista ce cuprinde cele 3 situatii specifice
// ( adaugat la inceput, in mijlocul listei sau la finalul acesteia )
void adaugareInLista(Capete* cap, Poz* pozitii, char litera) {
    Nod* nod_nou = (Nod*)malloc(sizeof(Nod));
    if (cap->inceput == NULL) {
        // De mentionat ca am utilizat o santinela in lista mea dubla pentru
        // A putea sa-mi fie mai usor sa pointez spre un nod anume in momentul in care
        // Cursorul meu se afla pe linia 1, coloana 0 ( astfel imi sunt facilitate 
        // operatiile pe cazuri speciale ( eg: backspace la inceput de lista nu face nimic)
        Nod* santinela = (Nod*)malloc(sizeof(Nod));
        santinela->prev = NULL;
        cap->inceput = cap->sfarsit = cap->cursor = nod_nou;
        nod_nou->next = NULL;
        nod_nou->caracter = litera;
        santinela->next = nod_nou;
        nod_nou->prev = santinela;
        pozitii->coloana++;
        return;
    }
    else if (cap->cursor == cap->sfarsit) {
        nod_nou->next = NULL;
        nod_nou->prev = cap->sfarsit;
        cap->sfarsit->next = nod_nou;
        cap->sfarsit = nod_nou;
        nod_nou->caracter = litera;
        cap->cursor = nod_nou;
        if (nod_nou->caracter == 10) {
            pozitii->linie++;
            pozitii->coloana = 0;
        }
        else 
            pozitii->coloana++;
        return;
    }
    else if (cap->cursor->next != NULL) {
        nod_nou->next = cap->cursor->next;
        nod_nou->prev = cap->cursor;
        cap->cursor->next->prev = nod_nou;
        cap->cursor->next = nod_nou;
        cap->cursor = nod_nou;
        nod_nou->caracter = litera;
        pozitii->coloana++;
        return;
    }
}
void afisareListaDubla(Capete* capete) {
    Nod* p = capete->inceput;
    if (p == NULL) 
        printf("Lista este vida\n");
    else
        while (p != NULL) {
            p = p->next;
        }
}

void golireLista(Capete* capete) {
    while(capete->sfarsit != capete->inceput) {
        Nod* p = capete->sfarsit;
        capete->sfarsit = p->prev;
        free(p);
    }
    if (capete->sfarsit->prev != NULL)
        // Aici eliberez santinela
        free(capete->sfarsit->prev);
    free(capete->sfarsit);
}
// Am declarat antetele functiilor inaintea implementarii pentru a nu exista
// Conflicte de ordine
char Operatie_Backspace(Capete* cap, Poz* pozitii);
void Operatie_ReverseBackspace(Capete* cap, Poz* pozitii, char litera);
char* Operatie_DL(Capete* cap, Poz* pozitii, int param);
Poz* Operatie_go_line(Capete* cap, int parametru, Poz* pozitii);
Poz* Operatie_go_to_char(Capete* cap, Poz* pozitii, int param1, int param2);
char Operatie_d(Capete* cap, Poz* pozitii);
void Operatie_RE_RA(Capete* capete, Poz* pozitii, char* cuvant_vechi, char* cuvant_nou, int param);
void Operatie_DW_DA(Capete* capete, Poz* pozitii, char* cuvant_vechi, int param);
// O   P   E   R   A   T   I   I

//---------------------- S  A  L  V  A  R  E 
// Functia de salvare copiaza lista principala de lucru intr-o lista auxiliara,
// Aceasta din urma fiind mereu golita inainte de reapelarea functiei save
void Operatie_Salvare(Capete* cap, Capete* aux) {
    aux->inceput = NULL;
    if (aux->inceput == NULL) {
        Nod* nod_nou = (Nod*)malloc(sizeof(Nod));
        aux->inceput = aux->cursor = aux->sfarsit = nod_nou;
        nod_nou->next = nod_nou->prev = NULL;
        nod_nou->caracter = cap->inceput->caracter;
    }
    Nod* p = aux->inceput;
    Nod* q = cap->inceput->next;
    while (q!= NULL) {
        Nod* nod_nou1 = (Nod*)malloc(sizeof(Nod));
        nod_nou1->caracter = q->caracter;
        nod_nou1->next = NULL;
        nod_nou1->prev = p;
        aux->sfarsit = nod_nou1;
        p->next = nod_nou1;
        p = nod_nou1; 
        q = q->next;
    }
}
//----------------- B  A  C  K  S  P  A  C  E            F  U  N  C  T  I  I
// Acopera cazuri speciale cum ar fi: linia 1 coloana 0, B nu face nimic ;
// Suntem pe primul element sau pe ultimul element ; suntem pe inceputul unei linii
// si trebuie sa facem grija la modificarea celor 2 int-uri care retin pozitia
char Operatie_Backspace(Capete* cap, Poz* pozitii) {
    if (pozitii->linie == 1 && pozitii->coloana == 0)
        return '0';
    char litera = cap->cursor->caracter;
    Nod* cursor_aux = cap->cursor;
    if (pozitii->linie > 1 && pozitii->coloana == 0) {
        if (cap->cursor == cap->sfarsit) {
            cursor_aux = cap->sfarsit;
            cap->sfarsit = cursor_aux->prev;
            cap->cursor = cursor_aux->prev;
            free(cursor_aux);
            cap->cursor->next = NULL;
            return litera;
        }
        else {
            cursor_aux->prev->next = cursor_aux->next;
            cursor_aux->next->prev = cursor_aux->prev;
            cap->cursor = cursor_aux->prev;
            free(cursor_aux);
        }
        Nod* p = cap->inceput;
        int l = 1, c = 1;
        while (p != cap->cursor) {
            p = p->next;
            if (p->caracter == 10) {
                c = 0;
                l++;
            }
            else
                c++;
        }
        pozitii->linie = l;
        pozitii->coloana = c;
        return litera;
    }
    if (cap->cursor == cap->sfarsit) {
        cursor_aux = cap->sfarsit;
        cap->sfarsit = cursor_aux->prev;
        cap->cursor = cursor_aux->prev;
        free(cursor_aux);
        cap->cursor->next = NULL;
        pozitii->coloana--;
        return litera;
    }
    if (pozitii->linie == 1 && pozitii->coloana == 1) {
         cursor_aux = cap->inceput;
        cap->cursor = cursor_aux->prev;
        cap->inceput = cursor_aux->next;
        cursor_aux->prev->next = cursor_aux->next;
        cursor_aux->next->prev = cursor_aux->prev;
        free(cursor_aux);
        pozitii->coloana--;
        return litera;
    }
    else {
        cap->cursor = cursor_aux->prev;
        cursor_aux->prev->next = cursor_aux->next;
        cursor_aux->next->prev = cursor_aux->prev;
        free(cursor_aux);
        pozitii->coloana--;
        return litera;
    }
}
// Complementara functiei Backspace care acopera aceleasi cazuri, pe scurt 
// Adauga un nod in lista
void Operatie_ReverseBackspace(Capete* cap, Poz* pozitii, char litera) {
    Nod* nod_nou = (Nod*)malloc(sizeof(Nod));
    if (pozitii->linie == 1 && pozitii->coloana == 0 && litera == '0')
        return;
    else if (pozitii->linie == 1 && pozitii->coloana == 0 && litera != '0') {
        nod_nou->prev = cap->cursor;
        nod_nou->next = cap->inceput;
        cap->cursor->next = nod_nou;
        cap->inceput->prev = nod_nou;
        cap->inceput = nod_nou;
        cap->cursor = nod_nou;
        nod_nou->caracter = litera;
        pozitii->coloana++;
    }
    else if (cap->cursor == cap->sfarsit) {
        nod_nou->prev = cap->cursor;
        nod_nou->next = NULL;
        cap->cursor->next = nod_nou;
        cap->cursor = nod_nou;
        cap->sfarsit = nod_nou;
        nod_nou->caracter = litera;
        pozitii->coloana++;
    }
    else if (litera == 10) {
        nod_nou->prev = cap->cursor;
        nod_nou->next = cap->cursor->next;
        cap->cursor->next->prev = nod_nou;
        cap->cursor->next = nod_nou;
        cap->cursor = nod_nou;
        nod_nou->caracter = litera;
        pozitii->coloana = 0;
        pozitii->linie++;
    }
    else {
        nod_nou->prev = cap->cursor;
        nod_nou->next = cap->cursor->next;
        cap->cursor->next->prev = nod_nou;
        cap->cursor->next = nod_nou;
        cap->cursor = nod_nou;
        nod_nou->caracter = litera;
        pozitii->coloana++;
    }
}
//-----------------------  D    L             F   U   N   C   T   I   I
char* Operatie_DL(Capete* cap, Poz* pozitii, int param) {
    char* sir = (char*)malloc(20*sizeof(char));
    Poz* x, *y;
    // Intai apelam functia go_line pentru a putea sa ne pozitionam la inceputul
    // liniei ce urmeaza sa fie stearsa
    // Daca se primeste parametrul -1 atunci trebuie sa stergem linia curenta
    // Si ne asiguram sa fim la inceputul ei
    if (param == -1) {
        x = Operatie_go_line(cap, pozitii->linie, pozitii);
        free(x);
    }
    // Altfel ne ducem pe linia data ca parametru prin param
    else {
        x = Operatie_go_line(cap, param, pozitii);
        free(x);
    }
    // De-a lungul tratarii cazurilor speciale ne asiguram ca structura ce retine
    // Pozitiile liniei si coloanei cursorului sa fie actualizate corect
    Nod* p = cap->inceput;
    int linie = 1, coloana = 1, i = 0;
    while (p != cap->sfarsit) {
        p = p->next;
        if (p->caracter == 10) {
            linie++;
            coloana = 0;
        }
        else
            coloana++;
    }
    // Cazul special cand ne aflam pe linia 1 si, fata de celelalte linii, nu putem sa 
    // Stergem acel \n ramas intrucat nu avem un \n ramas
    if (pozitii->linie == 1) {
        while (cap->cursor->next->caracter != 10) {
            char c = Operatie_d(cap, pozitii);
            sir[i] = c;
            i++;
        }
        sir[i] = '\0';
        pozitii->coloana++;
        cap->cursor = cap->cursor->next;
        Operatie_Backspace(cap, pozitii);
        y = Operatie_go_line(cap, pozitii->linie + 1, pozitii);
        free(y);
        pozitii->linie++;
        return sir;
    }
    // Daca nu ne aflam pe ultima linie
    else if (pozitii->linie != linie) {
        while (cap->cursor->next->caracter != 10) {
            char c = Operatie_d(cap, pozitii);
            sir[i++] = c;
        }
        sir[i] = '\0';
        Operatie_Backspace(cap, pozitii);
        y = Operatie_go_line(cap, pozitii->linie, pozitii);
        free(y);
        pozitii->linie++;
        return sir;
    }
    // Daca ne aflam pe ultima linie
    else {
        while (cap->cursor->next != NULL) {
            char c = Operatie_d(cap, pozitii);
            sir[i++] = c;
        }
        sir[i] = '\0';
        Operatie_Backspace(cap, pozitii);
        y = Operatie_go_line(cap, pozitii->linie, pozitii);
        free(y);
        pozitii->linie++;
        return sir;
    }
}
//-----------------  G  O       L  I  N  E        F  U  N  C  T  I  I
Poz* Operatie_go_line(Capete* cap, int parametru, Poz* pozitii) {
    Poz* copie_pozitii = (Poz*)malloc(sizeof(pozitii));
    // Retinem pozitia initiala a cursorului pentru a sti unde sa ne
    // Intoarcem dam de undo
    copie_pozitii->linie = pozitii->linie;
    copie_pozitii->coloana = pozitii->coloana;
    // Daca trebuie sa mergem pe linia 1 atunci trebuie sa pozitionam
    // Cursorul pe santinela
    if (parametru == 1) {
        cap->cursor = cap->inceput->prev;
        pozitii->linie = 1;
        pozitii->coloana = 0;
    }
    // Altfel pornim parcurgerea de la inceputul listei pana ajungem cu indicii de
    // Pozitie pe linia data ca parametru, respectiv coloana 0
    else {
        pozitii->linie = 1;
        pozitii->coloana = 1;
        cap->cursor = cap->inceput;
        while (pozitii->linie != parametru) {
            cap->cursor = cap->cursor->next;
            if (cap->cursor->caracter == 10) {
                pozitii->linie++;
                pozitii->coloana = 0;
            }
            else
                pozitii->coloana++;
        }
    }
    return copie_pozitii;
}
//----------------- G  O      T  O     C  H  A  R       F U N C T I I
Poz* Operatie_go_to_char(Capete* cap, Poz* pozitii, int param1, int param2) {
    Poz* copie_pozitii = (Poz*)malloc(sizeof(Poz));
    copie_pozitii->linie = pozitii->linie;
    copie_pozitii->coloana = pozitii->coloana;
    if (param2 == 1 && param1 == 0) {
        cap->cursor = cap->inceput->prev;
        pozitii->linie = 1;
        pozitii->coloana = 0;
        return copie_pozitii;
    }
    // Conventional apelez functia cu param2 = -2 daca trebuie sa ne miscam doar pe
    // Linia la care ne aflam deja
    if (param2 == -2) {
        cap->cursor = cap->inceput;
        int cl = 1, cc = 1;
        // Trebuie sa tratez cazul in care functia se apeleaza pentru valori
        // Invalide ale coloanei ( cand linia mea nu contine coloane cat cere comanda si
        // atunci ma pozitionez pe ultima coloana posibila din linie)
        while (cl != pozitii->linie || cc != 0) {
            cap->cursor = cap->cursor->next;
            if (cap->cursor->caracter == 10) {
                cl++;
                cc = 0;
            }
            else
                cc++;
        }
        while (cap->cursor->next->caracter != 10) {
            cc++;
            cap->cursor = cap->cursor->next;
        }
        // Verificam cazul mentionat mai sus. Daca cc-ul care va indica valoarea ultimei
        // Coloane de pe linie este chiar si acum mai mic decat parametrul, este clar ca
        // Nu ne putem permuta mai la dreapta si trebuie sa ramane pe ultima coloana posibila
        if (cc < param1) {
            pozitii->linie = cl;
            pozitii->coloana = cc;
            return copie_pozitii;
        }
        // Daca insa parametrul este chiar mai mic decat ultima coloana atunci, bineinteles,
        // Ne mutam pe coloana data ca parametru
        else {
            while (cc != param1) {
                cc--;
                cap->cursor = cap->cursor->prev;
            }
            pozitii->linie = cl;
            pozitii->coloana = cc;
            return copie_pozitii;
        }
    }
    // Cazul in care ni se specifica linia la care trebuie sa ne mutam pe un anumit caracter
    // Si aceasta nu este cea pe care ne aflam deja. Procedam analog tratand cazul special
    // De mai sus
    if (param2 != -2) {
        cap->cursor = cap->inceput;
        int cl = 1, cc = 1;
        while (cl != param2 || cc != 0) {
            cap->cursor = cap->cursor->next;
            if (cap->cursor->caracter == 10) {
                cl++;
                cc = 0;
            }
            else
                cc++;
        }
        while (cap->cursor->next->caracter != 10) {
            cc++;
            cap->cursor = cap->cursor->next;
        }
        if (cc < param1) {
            pozitii->linie = cl;
            pozitii->coloana = cc;
            return copie_pozitii;
        }
        else {
            while (cc != param1) {
                cc--;
                cap->cursor = cap->cursor->prev;
            }
            pozitii->linie = cl;
            pozitii->coloana = cc;
            return copie_pozitii;
        }
    }
    return copie_pozitii;
}
//----------------- D        C   H   A   R          F   U   N   C   T   I   I
// Doar ne mutam cu un nod mai la dreapta pentru a putea sa-l sterge, apeland backspace
char Operatie_d(Capete* cap, Poz* pozitii) {
    char litera;
    if (cap->cursor->next != NULL) {
        cap->cursor = cap->cursor->next;
        pozitii->coloana++;
    }
    litera = Operatie_Backspace(cap, pozitii);
    return litera;
}
//----------------- R  E   +   R  W       F   U   N   C   T   I   I
void Operatie_RE_RA(Capete* p, Poz* pozitii, char* cuvant_vechi, char* cuvant_nou, int param) {
    // Daca se da ca parametru un int de valoare 1 atunci stim ca trebuie sa facem o singura
    // Inlocuire/ Stergere
    if (param == 1) {
        // Salvam pozitia initiala cursorului
        int copie_linie = pozitii->linie, copie_coloana = pozitii->coloana;
        char string[10];
        // Avem nevoie de acest pointer pe care-l vom pozitiona pe santinela unde stim
        // sigur ca nu se poate pierde nici macar cand trebuie sa stergem primu nod din lista,
        // ulterior parcurgand cu acesta lista pana ajungem la pozitia initiala salvata mai sus
        Nod* cc = p->inceput->prev;
        // Incepem sa parcurgem lista cu cursorul original, avand grija sa modificam si pozitia
        // Acestuia reprezentata de cele 2 int-uri
        while (p->cursor->next) {
            p->cursor = p->cursor->next;
            if (p->cursor->caracter == 10) {
                pozitii->linie++;
                pozitii->coloana = 0;
            }
            else
                pozitii->coloana++;
            // Daca gasim un nod ce contine prima litera din cuvaantul nostru de inlocuit/sters
            // Incercam sa construim un sir static in care vedem cum arata cuvantul format pe acea
            // Portiune din lista, de lungime egala cu cuvantul dat ca parametru
            if (cuvant_vechi[0] == p->cursor->caracter) {
                int i = 0;
                string[i++] = p->cursor->caracter;
                Nod* pp = p->cursor;
                int j, l;
                for (j = 1; j < strlen(cuvant_vechi); j++) {
                    p->cursor = p->cursor->next;
                    string[i++] = p->cursor->caracter;
                }
                pozitii->coloana = pozitii->coloana + strlen(cuvant_vechi) - 1;
                string[i] = '\0';
                // In cazul in care cuvantul creat este identic cu cel ce trebuie sters/inlocuit
                // Atunci efectuam modificarile necesare ( la RE/RA trebuie sa stergem un numar de
                // caractere egal cu lungimea cuvantului vechi dupa care sa adaugam in ordinea corecta
                // numarul de litere al cuvantului nou dat ca parametru)
                if (strcmp(cuvant_vechi, string) == 0) {
                    for (j = 0; j < strlen(cuvant_vechi); j++)
                        Operatie_Backspace(p, pozitii);
                    for (l = 0; l < strlen(cuvant_nou); l++)
                        Operatie_ReverseBackspace(p, pozitii, cuvant_nou[l]);
                    string[0] = '\0';
                    int w = 1, col = 0;
                    while ( w != copie_linie || col != copie_coloana) {
                        cc = cc->next;
                        if (cc->caracter == 10) {
                            w++;
                            col = 0;
                        }
                        else
                            col++;
                    }
                    p->cursor = cc;
                    pozitii->coloana = copie_coloana;
                    pozitii->linie = copie_linie;
                    return;
                }
                // Daca sirul construit nu a fost identic cu cuvantul de sters/inlocuit
                // Atunci trebuie sa avem grija sa ne repozitionam cu cursorul inapoi pe litera
                // Care s-a identificat cu prima litera a cuvantului vechi si sa ne intoarcem si cu
                // Pozitiile celor 2 int-uri ( mai exact al coloanei ).
                else {
                    i = 0;
                    string[0] = '\0';
                    pozitii->coloana = pozitii->coloana - strlen(cuvant_vechi) + 1;
                    p->cursor = pp;
                } 
            }
        }
    }
    // Daca se da ca parametru un int de valoare diferita de 1 atunci stim ca trebuie 
    // sa facem inlocuiri/stergeri pana la finalul listei
    else {
        // Se procedeaza analog ca mai sus cu singura diferenta ca nu dam return; dupa prima
        // Operatie efectuata
        int copie_linie = pozitii->linie, copie_coloana = pozitii->coloana;
        char string[10];
        Nod* cc = p->inceput->prev;
        p->cursor = p->inceput->prev;
        pozitii->linie = 1; pozitii->coloana = 0;
        while (p->cursor->next) {
            p->cursor = p->cursor->next;
            if (p->cursor->caracter == 10) {
                pozitii->linie++;
                pozitii->coloana = 0;
            }
            else
                pozitii->coloana++;
            if (cuvant_vechi[0] == p->cursor->caracter) {
                int i = 0, j, l;
                string[i++] = p->cursor->caracter;
                Nod* pp = p->cursor;
                for (j = 1; j < strlen(cuvant_vechi); j++) {
                    p->cursor = p->cursor->next;
                    string[i++] = p->cursor->caracter;
                }
                pozitii->coloana = pozitii->coloana + strlen(cuvant_vechi) - 1;
                string[i] = '\0';
                if (strcmp(cuvant_vechi, string) == 0) {
                    for (j = 0; j < strlen(cuvant_vechi); j++) 
                        Operatie_Backspace(p, pozitii);
                    for (l = 0; l < strlen(cuvant_nou); l++)
                        Operatie_ReverseBackspace(p, pozitii, cuvant_nou[l]);
                    string[0] = '\0';
                }
                else {
                i = 0;
                string[0] = '\0';
                pozitii->coloana = pozitii->coloana - strlen(cuvant_vechi) + 1;
                p->cursor = pp;
                } 
            }
        }
        int w = 1, col = 0;
        while ( w != copie_linie || col != copie_coloana) {
            cc = cc->next;
            if (cc->caracter == 10) {
                w++;
                col = 0;
            }
            else
                col++;
        }
        p->cursor = cc;
        pozitii->coloana = copie_coloana;
        pozitii->linie = copie_linie;
    }
}
//----------------- D   W   +  D   A         F   U   N   C   T   I   I
// Functia se asemeana aproape in totalitate cu cea de RE+RA cu singura diferenta ca
// Nu mai apelam acele ReverseBackspaceuri pentru a pune un cuvant nou
void Operatie_DW_DA(Capete* p, Poz* pozitii, char* cuvant_vechi, int param) {
    if (param == 1) {
        int copie_linie = pozitii->linie, copie_coloana = pozitii->coloana;
        char string[10];
        Nod* cc = p->inceput->prev;
        while (p->cursor->next) {
            p->cursor = p->cursor->next;
            if (p->cursor->caracter == 10) {
                pozitii->linie++;
                pozitii->coloana = 0;
            }
            else
                pozitii->coloana++;
            if (cuvant_vechi[0] == p->cursor->caracter) {
                int i = 0;
                string[i++] = p->cursor->caracter;
                Nod *pp = p->cursor;
                int j;
                for (j = 1; j < strlen(cuvant_vechi); j++) {
                    p->cursor = p->cursor->next;
                    string[i++] = p->cursor->caracter;
                }
                pozitii->coloana = pozitii->coloana + strlen(cuvant_vechi) - 1;
                string[i] = '\0';
                if (strcmp(cuvant_vechi, string) == 0) {
                    for (j = 0; j < strlen(cuvant_vechi); j++)
                        Operatie_Backspace(p, pozitii);
                    if (p->cursor != p->inceput){
                        if (p->cursor->caracter == 10 && p->cursor->next->caracter == 10){
                            Operatie_Backspace(p, pozitii);
                        }
                    }
                    string[0] = '\0';
                    int w = 1,  col = 0;
                    while ( w != copie_linie || col != copie_coloana) {
                        cc = cc->next;
                        if (cc->caracter == 10) {
                            w++;
                            col = 0;
                        }
                        else
                            col++;
                    }
                    p->cursor = cc;
                    pozitii->coloana = copie_coloana;
                    pozitii->linie = copie_linie;
                    cc = NULL;
                    return;
                }
                else {
                    i = 0;
                    string[0] = '\0';
                    pozitii->coloana = pozitii->coloana - strlen(cuvant_vechi) + 1;
                    p->cursor = pp;
                } 
            }
        }
    }
    else {
        int copie_linie = pozitii->linie, copie_coloana = pozitii->coloana;
        char string[10];
        Nod* cc = p->inceput->prev;
        p->cursor = p->inceput->prev;
        pozitii->linie = 1; pozitii->coloana = 0;
        while (p->cursor->next) {
            p->cursor = p->cursor->next;
            if (p->cursor->caracter == 10) {
                pozitii->linie++;
                pozitii->coloana = 0;
            }
            else
                pozitii->coloana++;
            if (cuvant_vechi[0] == p->cursor->caracter) {
                int i = 0;
                string[i++] = p->cursor->caracter;
                Nod* pp = p->cursor;
                int j;
                for (j = 1; j < strlen(cuvant_vechi); j++) {
                    p->cursor = p->cursor->next;
                    string[i++] = p->cursor->caracter;
                }      
                pozitii->coloana = pozitii->coloana + strlen(cuvant_vechi) - 1;
                string[i] = '\0';
                if (strcmp(cuvant_vechi, string) == 0) {
                    for (j = 0; j < strlen(cuvant_vechi); j++) {
                        Operatie_Backspace(p, pozitii);
                    }
                    if (p->cursor != p->inceput->prev)
                        if (p->cursor->caracter == 10 && p->cursor->next->caracter == 10)
                            Operatie_Backspace(p, pozitii);
                    string[0] = '\0';
                    i = 0;
                }
                else {
                i = 0;
                string[0] = '\0';
                pozitii->coloana = pozitii->coloana - strlen(cuvant_vechi) + 1;
                p->cursor = pp;
                } 
            }
        }
        int w = 1, col = 0;
        while ( w != copie_linie || col != copie_coloana) {
            cc = cc->next;
            if (cc->caracter == 10) {
                w++;
                col = 0;
            }
            else
                col++;
        }
        p->cursor = cc;
        pozitii->coloana = copie_coloana;
        pozitii->linie = copie_linie;
        cc = NULL;
    }
}

int main(int argc, char** argv) {
    //----------------- Declarari variabile
    char litera_speciala = '2', sir_special[50]  = "artificiu ingineresc";
    char c, sir_auxiliar[100], sir_auxiliar2[100], sir_special2[50] = "ingineresc artificiu", sir[50],
        sir_auxiliar3[200], sir_auxiliar4[100];
    int ch, i = 0, x, k, contor = 0, contor1 = 0, m = 0, contor_endline = 0;
    char *param1, *param2, *s = NULL, *ss = NULL;
    // char* comanda1 = NULL;
    //----------------  Declarari Nod + Capete
    Poz* pozitie_speciala = (Poz*)malloc(sizeof(Poz));
    pozitie_speciala->linie = -1;
    pozitie_speciala->coloana = 0;
    Poz* pozitii = (Poz*)malloc(sizeof(Poz));
    pozitii->linie = 1; pozitii->coloana = 0;
    Capete* capete = (Capete*)malloc(sizeof(Capete));
    Capete* capete1 = (Capete*)malloc(sizeof(Capete));
    initCapete(capete);
    initCapete(capete1);
    //----------------- Declarari Stive
    Stiva* stiva_undo = NULL;
    Stiva* stiva_redo = NULL;
    //----------------- Citire
    FILE *f = fopen("editor.in", "r");
    // Incepem sa citim fisierul de input caracter cu caracter pana la finalul acestuia
    while ( (ch = fgetc(f)) != EOF) {
        // Daca dam de caracterul „:” atunci stim ca intram in modul de inserare
        // Comenzi si trebuie sa schimbam modul de citire din litera cu litera in
        // Rand cu rand
        if ( ch == 58 ) {
            fgets(sir, 100 ,f);
            strcpy(sir_auxiliar,sir);
            contor1++;
            // Acest contor ne indica daca suntem la prima inserare de text din fisier
            // Care mereu e garant ca nu se va sterge prin undo si nu trebuie sa facem nimic
            // In aceasta situatie
            if (contor1 == 1) {
                m = 0;
                sir_auxiliar3[0] = '\0';
            }
            // Daca suntem deja la a 2-a inserare de text atunci trebuie sa salvam in stiva de undo
            // Secventa de text adaugata la acel pas astfel incat, daca dam de undo, sa stim ce anume
            // Sa stergeme
            else {
                // Acest contor acopera cazul in care, daca se adauga o linie in mijlocul textului,
                // Aceasta nu trebuei sa contina \n de la final, asigurandu-ne sa-l stergem.
                // Daca se adauga mai multe inii nu facem nimic in legatura cu \n de la final
                if (contor_endline == 1) {
                    Operatie_Backspace(capete, pozitii);
                    m--;
                }
                sir_auxiliar3[m] = '\0';
                // Adaugam in lista de undo comanda „:i” si bucata de text adaugata
                stiva_undo = adaugareStiva(stiva_undo, sir_auxiliar, sir_auxiliar3, sir_special2, litera_speciala, pozitie_speciala);
                sir_auxiliar3[0] = '\0';
                m = 0;
                contor_endline = 0;
            }
            sir_auxiliar[0] = '\0';
            // Citim linie cu linie comenzile pana la final de fisier si, in caz ca dam iar de
            // „:i”, atunci trebuie sa iesim din aceasta citire iterativa linie-cu-linie cu un break
            while( fgets(sir, 100, f) != NULL )   {
                 // Identificam comanda aferenta si efectuam operatiile necesare in functie de aceasta,
                // Avand grija sa adaugam in stiva de unde numele comenzii si, in functie de caz,
                // Pozitia anterioara/ O litera de salvat/ Un sir de salvat/ Doua cuvinte de salvat
                // ( aceasta din urma in cazul re/ra)
                if (strcmp(sir, "q\n") == 0) { 
                    // Dacam da de quit atunci afisam in fisierul de output ultima versiune a listei
                    // salvate, aceasta fiind reprezentata de lista auxiliara pe care
                    // o actualizam mereu
                    FILE *f2 = fopen("editor.out", "w");
                    capete1->cursor = capete1->inceput;
                    while(capete1->cursor->next) {
                        fprintf(f2, "%c", capete1->cursor->caracter);
                        capete1->cursor = capete1->cursor->next;
                    }
                    fprintf(f2, "%c", '\n');
                    // Acest while goleste stiva de undo in caz ca raman comenzi asupra carora
                    // Nu s-a aplicat undo
                    while (stiva_undo) {
                        if (strcmp(stiva_undo->comanda, ":i\n") == 0 || strcmp(stiva_undo->comanda, ":i \n") == 0) {
                            strcpy(sir_auxiliar, stiva_undo->comanda);
                            strcpy(sir_auxiliar2, stiva_undo->sir_memorat);
                            s = stiva_undo->sir_memorat;
                            stiva_undo = eliminare_el_stiva(stiva_undo, sir_auxiliar, s, sir_special2, litera_speciala, pozitie_speciala);
                            sir_auxiliar[0] = '\0';
                            sir_auxiliar2[0] = '\0';
                        }   
                        else if (strcmp(stiva_undo->comanda, "b\n" ) == 0)
                            stiva_undo = eliminare_el_stiva(stiva_undo, stiva_undo->comanda, sir_special, sir_special2, litera_speciala, pozitie_speciala);
                        else if (strncmp(stiva_undo->comanda, "dl", 2) == 0) {
                            strcpy(sir_auxiliar, stiva_undo->comanda);
                            s = stiva_undo->sir_memorat;
                            stiva_undo = eliminare_el_stiva(stiva_undo, sir_auxiliar, s, sir_special2, litera_speciala, pozitie_speciala);
                            sir_auxiliar[0] = '\0';
                        }
                        else if (strncmp(stiva_undo->comanda, "gl", 2) == 0) {
                            strcpy(sir_auxiliar, stiva_undo->comanda);
                            stiva_undo = eliminare_el_stiva(stiva_undo, sir_auxiliar, sir_special, sir_special2, litera_speciala, stiva_undo->pozitii);
                            sir_auxiliar[0] = '\0';
                        }
                        else if (strncmp(stiva_undo->comanda, "gc", 2) == 0) {
                            strcpy(sir_auxiliar, stiva_undo->comanda);
                            stiva_undo =  eliminare_el_stiva(stiva_undo, sir_auxiliar, sir_special, sir_special2, litera_speciala, stiva_undo->pozitii);
                            sir_auxiliar[0] = '\0';
                        }
                        else if (strcmp(stiva_undo->comanda, "d\n") == 0) {
                            strcpy(sir_auxiliar, stiva_undo->comanda);
                            stiva_undo = eliminare_el_stiva(stiva_undo, sir_auxiliar, sir_special, sir_special2, litera_speciala, pozitie_speciala);
                            sir_auxiliar[0] = '\0';
                        }
                        else if (strncmp(stiva_undo->comanda, "d ", 2) == 0) {
                            strcpy(sir_auxiliar, stiva_undo->comanda);
                            strcpy(sir_auxiliar, stiva_undo->sir_memorat);
                            param1 = strtok(stiva_undo->comanda, " ");
                            param1 = strtok(NULL, " \n");
                            stiva_undo = eliminare_el_stiva(stiva_undo, sir_auxiliar, stiva_undo->sir_memorat, sir_special2, litera_speciala, pozitie_speciala); 
                            sir_auxiliar[0] = '\0';
                            sir_auxiliar2[0] = '\0';
                        }
                        else if (strncmp(stiva_undo->comanda, "re", 2) == 0)
                            stiva_undo = eliminare_el_stiva(stiva_undo, stiva_undo->comanda, stiva_undo->sir_memorat, stiva_undo->sir_memorat2, litera_speciala, pozitie_speciala);
                        else if (strncmp(stiva_undo->comanda, "ra", 2) == 0) 
                            stiva_undo = eliminare_el_stiva(stiva_undo, stiva_undo->comanda, stiva_undo->sir_memorat, stiva_undo->sir_memorat2, litera_speciala, pozitie_speciala);
                        else if (strncmp(stiva_undo->comanda, "dw", 2) == 0) { 
                            strcpy(sir_auxiliar, stiva_undo->comanda);
                            strcpy(sir_auxiliar2, stiva_undo->sir_memorat);
                            stiva_undo = eliminare_el_stiva(stiva_undo, sir_auxiliar, sir_auxiliar2, sir_special2, litera_speciala, pozitie_speciala);
                            sir_auxiliar[0] = '\0';
                            sir_auxiliar2[0] = '\0';
                        }
                        else if (strncmp(stiva_undo->comanda, "da", 2) == 0) {
                            ss = stiva_undo->sir_memorat;
                            param1 = stiva_undo->comanda;
                            stiva_undo = eliminare_el_stiva(stiva_undo, param1, ss, sir_special2, litera_speciala, pozitie_speciala);
                        }
                    }
                    while(stiva_redo != NULL) {
                        // Acest while goleste stiva de redo in caz ca raman comenzi asupra carora
                        // Nu s-a aplicat redo
                        if (strcmp(stiva_redo->comanda, "b\n") == 0)
                            stiva_redo = eliminare_el_stiva(stiva_redo, stiva_redo->comanda, sir_special, sir_special2, litera_speciala, pozitie_speciala);
                        else if (strncmp(stiva_redo->comanda, "dl", 2) == 0)
                            stiva_redo = eliminare_el_stiva(stiva_redo, stiva_redo->comanda, sir_special, sir_special2, litera_speciala, pozitie_speciala);   
                        else if (strcmp(stiva_redo->comanda, ":i\n") == 0 || strcmp(stiva_redo->comanda, ":i \n") == 0)
                            stiva_redo = eliminare_el_stiva(stiva_redo, stiva_redo->comanda, stiva_redo->sir_memorat, sir_special2, litera_speciala, pozitie_speciala);
                        else if (strncmp(stiva_redo->comanda, "gl", 2) == 0)
                            stiva_redo = eliminare_el_stiva(stiva_redo, stiva_redo->comanda, sir_special, sir_special2, litera_speciala, pozitie_speciala);
                        else if (strncmp(stiva_redo->comanda, "gc", 2) == 0)
                            stiva_redo = eliminare_el_stiva(stiva_redo, stiva_redo->comanda, sir_special, sir_special2, litera_speciala, pozitie_speciala);
                        else if (strncmp(stiva_redo->comanda, "d ", 2) == 0)
                            stiva_redo = eliminare_el_stiva(stiva_redo, stiva_redo->comanda, sir_special, sir_special2, litera_speciala, stiva_redo->pozitii);
                        else if (strcmp(stiva_redo->comanda, "d\n") == 0)
                            stiva_redo = eliminare_el_stiva(stiva_redo, stiva_redo->comanda, sir_special, sir_special2, litera_speciala, stiva_redo->pozitii);
                        else if (strncmp(stiva_redo->comanda, "re", 2) == 0)
                            stiva_redo = eliminare_el_stiva(stiva_redo, stiva_redo->comanda, stiva_redo->sir_memorat, stiva_redo->sir_memorat2, litera_speciala, stiva_redo->pozitii);
                        else if (strncmp(stiva_redo->comanda, "ra", 2) == 0)
                            stiva_redo = eliminare_el_stiva(stiva_redo, stiva_redo->comanda, stiva_redo->sir_memorat, stiva_redo->sir_memorat2, litera_speciala, stiva_redo->pozitii);
                        else if (strncmp(stiva_redo->comanda, "dw", 2) == 0)
                            stiva_redo = eliminare_el_stiva(stiva_redo, stiva_redo->comanda, stiva_redo->sir_memorat, sir_special2, litera_speciala, stiva_redo->pozitii);
                        else if (strncmp(stiva_redo->comanda, "da", 2) == 0)
                            stiva_redo = eliminare_el_stiva(stiva_redo, stiva_redo->comanda, stiva_redo->sir_memorat, sir_special2, litera_speciala, stiva_redo->pozitii);
                    } 
                    // Golim stivele, listele, structurile de pozitii si inchidem cele 2 fisiere
                    // De input si de output
                    golireLista(capete);
                    golireLista(capete1);
                    free(pozitii);
                    free(pozitie_speciala);
                    free(capete);
                    free(capete1);
                    fclose(f);
                    fclose(f2);
                    exit(0);
                }
                // Dacam dam de save avem grija sa salvam ultima varianta a listei in cea
                // Auxiliara. Daca este prima salvare, lista auxiliara nu este creata si deci
                // Doar salvam in ea. Daca sunt salvari multiple, trebuie sa o golim si dupa sa
                // Adaugam iar
                if (strcmp(sir, "s\n") == 0) {
                    contor ++;
                    if (contor == 1)
                        Operatie_Salvare(capete, capete1);
                    else {
                        golireLista(capete1);
                        Operatie_Salvare(capete, capete1);
                    }
                }
                if (strcmp(sir, "b\n") == 0) {
                    c = Operatie_Backspace(capete, pozitii);
                    stiva_undo = adaugareStiva(stiva_undo, sir, sir_special, sir_special2, c,pozitie_speciala);
                }
                if (strncmp(sir, "dl", 2) == 0) {
                    strcpy(sir_auxiliar, sir);
                    param1 = strtok(sir, " ");
                    param1 = strtok(NULL, " ,\n");
                    if (param1 == NULL) {
                        s = Operatie_DL(capete, pozitii, pozitii->linie);
                        stiva_undo = adaugareStiva(stiva_undo, sir_auxiliar, s, sir_special2, litera_speciala, pozitie_speciala);
                        free(s);
                    }
                    else {
                        s = Operatie_DL(capete, pozitii, atoi(param1));
                        stiva_undo = adaugareStiva(stiva_undo, sir_auxiliar, s, sir_special2, litera_speciala, pozitie_speciala);
                        free(s);
                    }
                    sir_auxiliar[0] = '\0';
                }
                if (strncmp(sir, "gl", 2) == 0) {
                    strcpy(sir_auxiliar, sir);
                    param1 = strtok(sir, " ");
                    param1 = strtok(NULL, " ");
                    Poz* x = Operatie_go_line(capete, atoi(param1), pozitii);
                    stiva_undo = adaugareStiva(stiva_undo, sir_auxiliar, sir_special, sir_special2, litera_speciala, x);
                    free(x);
                    sir_auxiliar[0] = '\0';
                }
                if (strncmp(sir, "gc", 2) == 0) {
                    strcpy(sir_auxiliar, sir);
                    param1 = strtok(sir, " ");
                    param1 = strtok(NULL, " ");
                    param2 = strtok(NULL, " \n");
                    if (param2 == NULL) {
                        Poz* x = Operatie_go_to_char(capete, pozitii, atoi(param1), -2);
                        stiva_undo = adaugareStiva(stiva_undo, sir_auxiliar, sir_special, sir_special2, litera_speciala, x);
                        free(x);
                    }
                    else {
                        Poz* x = Operatie_go_to_char(capete, pozitii, atoi(param1), atoi(param2));
                        stiva_undo = adaugareStiva(stiva_undo, sir_auxiliar, sir_special, sir_special2, litera_speciala, x);
                        free(x);
                    }
                    sir_auxiliar[0] = '\0';
                }
                if ( (strncmp(sir, "d ", 2) == 0)) {
                    strcpy(sir_auxiliar, sir);
                    param1 = strtok(sir, " ");
                    param1 = strtok(NULL, " ,\n");
                    x = atoi(param1);
                    while (x) {
                        c = Operatie_d(capete, pozitii);
                        sir_auxiliar2[i++] = c;
                        x--;
                    }
                    sir_auxiliar2[i] = '\0';
                    stiva_undo = adaugareStiva(stiva_undo, sir_auxiliar, sir_auxiliar2, sir_special2, litera_speciala, pozitie_speciala );
                    i = 0;
                    sir_auxiliar2[0] = '\0';
                    sir_auxiliar[0] = '\0';
                }
                if (strcmp(sir, "d\n") == 0) {
                    strcpy(sir_auxiliar, sir);
                    c = Operatie_d(capete, pozitii);
                    stiva_undo = adaugareStiva(stiva_undo, sir_auxiliar, sir_special, sir_special2, c, pozitie_speciala);
                    sir_auxiliar[0] = '\0';
                }
                if (strncmp(sir, "re", 2) == 0) {
            
                    strcpy(sir_auxiliar, sir);
                    param1 = strtok(sir, " ");
                    param1 = strtok(NULL, " ");
                    param2 = strtok(NULL, " ,\n");
                    Operatie_RE_RA(capete, pozitii, param1, param2, 1);
                    stiva_undo = adaugareStiva(stiva_undo, sir_auxiliar, param1, param2, litera_speciala, pozitie_speciala);
                    sir_auxiliar[0] = '\0';
                }
                if (strncmp(sir, "ra", 2) == 0) {
                    strcpy(sir_auxiliar, sir);
                    param1 = strtok(sir, " ");
                    param1 = strtok(NULL, " ");
                    param2 = strtok(NULL, " ,\n");
                    Operatie_RE_RA(capete, pozitii, param1, param2, -1);
                    stiva_undo = adaugareStiva(stiva_undo, sir_auxiliar, param1, param2, litera_speciala, pozitie_speciala);
                    sir_auxiliar[0] = '\0';
                }
                if (strncmp(sir, "dw", 2) == 0) {
                    strcpy(sir_auxiliar, sir);
                    param1 = strtok(sir, " ");
                    param1 = strtok(NULL, " ,\n");
                    Operatie_DW_DA(capete, pozitii, param1, 1);
                    stiva_undo = adaugareStiva(stiva_undo, sir_auxiliar, param1, sir_special2, litera_speciala, pozitie_speciala);
                    sir_auxiliar[0] = '\0';
                }
                if (strncmp(sir, "da", 2) == 0) {
                    strcpy(sir_auxiliar, sir);
                    param1 = strtok(sir, " ");
                    param1 = strtok(NULL, " ,\n");
                    Operatie_DW_DA(capete, pozitii, param1, -1);
                    stiva_undo = adaugareStiva(stiva_undo, sir_auxiliar, param1, sir_special2, litera_speciala, pozitie_speciala);
                    sir_auxiliar[0] = '\0';
                }
                if (strcmp(sir, "::i\n") == 0 || strcmp(sir, "::i \n") == 0)
                    break;
//----------------- D   A  M ----------------- D   E----------------- U   N   D   O -----------------
                // Daca dam de undo atunci trebuie sa luam elementul din varful stivei de undo si
                // Sa verificam ce comanda contine, incercand sa facem operatia inversa. De asemenea, 
                // Trebuie sa avem in vedere sa eliminam nodul din stiva de undo si sa adaugam un
                // Nod in cea de redo in care sa memoram comanda si, dupa caz, pozitii/siruri/litere
                if (strcmp(sir, "u\n") == 0 && stiva_undo != NULL) {
                    if (strcmp(stiva_undo->comanda, "b\n") == 0) {
                        strcpy(sir_auxiliar, stiva_undo->comanda);
                        Operatie_ReverseBackspace(capete, pozitii, stiva_undo->litera);
                        c = stiva_undo->litera;
                        stiva_redo = adaugareStiva(stiva_redo, sir_auxiliar, sir_special, sir_special2, litera_speciala, pozitie_speciala);
                        stiva_undo = eliminare_el_stiva(stiva_undo, sir_auxiliar, sir_special, sir_special2, c, pozitie_speciala);
                        sir_auxiliar[0] = '\0';
                    }
                    else if (strcmp(stiva_undo->comanda, ":i\n") == 0 || strcmp(stiva_undo->comanda, ":i \n") == 0) {
                        strcpy(sir_auxiliar, stiva_undo->comanda);
                        strcpy(sir_auxiliar2, stiva_undo->comanda);
                        strcpy(sir_auxiliar3, stiva_undo->sir_memorat);
                        strcpy(sir_auxiliar4, stiva_undo->sir_memorat);
                        x = strlen(sir_auxiliar3);
                        stiva_undo = eliminare_el_stiva(stiva_undo, sir_auxiliar, sir_auxiliar3, sir_special2, litera_speciala, pozitie_speciala);
                        stiva_redo = adaugareStiva(stiva_redo, sir_auxiliar2, sir_auxiliar4, sir_special2, litera_speciala, pozitie_speciala);
                        while (x) {
                            Operatie_Backspace(capete, pozitii);
                            x--;
                        }
                        sir_auxiliar[0] = '\0';
                        sir_auxiliar2[0] = '\0';
                        sir_auxiliar3[0] = '\0';
                        sir_auxiliar4[0] = '\0';
                    }
                    else if (strncmp(stiva_undo->comanda, "dl", 2) == 0) {
                        strcpy(sir_auxiliar, stiva_undo->comanda);
                        Operatie_ReverseBackspace(capete,pozitii, '\n');
                        for (k = 0; k < strlen(stiva_undo->sir_memorat); k++)
                            Operatie_ReverseBackspace(capete, pozitii, stiva_undo->sir_memorat[k]);
                        stiva_redo = adaugareStiva(stiva_redo, sir_auxiliar, sir_special, sir_special2, litera_speciala, pozitie_speciala);
                        stiva_undo = eliminare_el_stiva(stiva_undo, sir_auxiliar, sir_special, sir_special2, litera_speciala, pozitie_speciala);
                        sir_auxiliar[0] = '\0';
                    }
                    else if (strncmp(stiva_undo->comanda, "gl", 2) == 0) {
                        strcpy(sir_auxiliar, stiva_undo->comanda);
                        //Poz* x = Operatie_go_to_char(capete, pozitii, stiva_undo->pozitii->coloana, stiva_undo->pozitii->linie);
                        stiva_redo = adaugareStiva(stiva_redo, sir_auxiliar, sir_special, sir_special2, litera_speciala, pozitie_speciala);
                        stiva_undo = eliminare_el_stiva(stiva_undo, sir_auxiliar, sir_special, sir_special2, litera_speciala, stiva_undo->pozitii);
                        //free(x);
                        sir_auxiliar[0] = '\0';
                    }
                    else if (strncmp(stiva_undo->comanda, "gc", 2) == 0) {
                        strcpy(sir_auxiliar, stiva_undo->comanda);
                        Poz* x = Operatie_go_to_char(capete, pozitii, stiva_undo->pozitii->coloana, stiva_undo->pozitii->linie);
                        stiva_undo = eliminare_el_stiva(stiva_undo, sir_auxiliar, sir_special, sir_special2, litera_speciala, stiva_undo->pozitii);
                        free(x);
                        stiva_redo = adaugareStiva(stiva_redo, sir_auxiliar, sir_special, sir_special2, litera_speciala, pozitie_speciala);
                        sir_auxiliar[0] = '\0';
                    }
                    else if (strncmp(stiva_undo->comanda, "d ", 2) == 0) {
                        int copie = pozitii->coloana;
                        Poz* copie_poz = (Poz*)malloc(sizeof(Poz));
                        copie_poz->linie = pozitii->linie;
                        strcpy(sir_auxiliar, stiva_undo->comanda);
                        strcpy(sir_auxiliar2, stiva_undo->sir_memorat);
                        param1 = strtok(stiva_undo->comanda, " ");
                        param1 = strtok(NULL, " ");
                        x = atoi(param1);
                        i = 0;
                        while (x) {
                            Operatie_ReverseBackspace(capete, pozitii, sir_auxiliar2[i++]);
                            x--;
                            copie++;
                        }
                        copie_poz->coloana = copie;
                        stiva_redo = adaugareStiva(stiva_redo, sir_auxiliar, sir_special, sir_special2, litera_speciala, copie_poz);
                        stiva_undo = eliminare_el_stiva(stiva_undo, sir_auxiliar, sir_auxiliar2, sir_special2, litera_speciala, pozitie_speciala); 
                        sir_auxiliar2[0] = '\0';
                        sir_auxiliar[0] = '\0';
                        i = 0;
                        free(copie_poz);
                    }
                    else if (strcmp(stiva_undo->comanda, "d\n") == 0) {
                        Poz* copie_poz2 = (Poz*)malloc(sizeof(Poz));
                        strcpy(sir_auxiliar, stiva_undo->comanda);
                        Operatie_ReverseBackspace(capete, pozitii, stiva_undo->litera);
                        copie_poz2->linie = pozitii->linie;
                        copie_poz2->coloana = pozitii->coloana;
                        stiva_undo = eliminare_el_stiva(stiva_undo, sir_auxiliar, sir_special, sir_special2, litera_speciala, pozitie_speciala);
                        stiva_redo = adaugareStiva(stiva_redo, sir_auxiliar, sir_special, sir_special2, litera_speciala, copie_poz2);
                        sir_auxiliar[0] = '\0';
                        free(copie_poz2);
                    }
                    else if (strncmp(stiva_undo->comanda, "re", 2) == 0) {
                        strcpy(sir_auxiliar, stiva_undo->comanda);
                        strcpy(sir_auxiliar2, stiva_undo->sir_memorat);
                        strcpy(sir_auxiliar3, stiva_undo->sir_memorat2);
                        Operatie_RE_RA(capete, pozitii, stiva_undo->sir_memorat, stiva_undo->sir_memorat2, 1);
                        stiva_redo = adaugareStiva(stiva_redo, stiva_undo->comanda, stiva_undo->sir_memorat, stiva_undo->sir_memorat2, litera_speciala, pozitie_speciala);
                        stiva_undo = eliminare_el_stiva(stiva_undo, param1, ss, s, litera_speciala, pozitie_speciala);
                        sir_auxiliar[0] = '\0';
                        sir_auxiliar2[0] = '\0';
                        sir_auxiliar3[0] = '\0';
                    }
                    else if (strncmp(stiva_undo->comanda, "ra", 2) == 0) {
                        strcpy(sir_auxiliar, stiva_undo->comanda);
                        strcpy(sir_auxiliar2, stiva_undo->sir_memorat);
                        strcpy(sir_auxiliar3, stiva_undo->sir_memorat2);
                        Operatie_RE_RA(capete, pozitii, sir_auxiliar2, sir_auxiliar3, -1);
                        stiva_redo = adaugareStiva(stiva_redo, sir_auxiliar, sir_auxiliar2, sir_auxiliar3, litera_speciala, pozitie_speciala);
                        stiva_undo = eliminare_el_stiva(stiva_undo, sir_auxiliar, sir_auxiliar2, sir_auxiliar3, litera_speciala, pozitie_speciala);
                        sir_auxiliar[0] = '\0';
                        sir_auxiliar2[0] = '\0';
                        sir_auxiliar3[0] = '\0';
                    }
                    else if (strncmp(stiva_undo->comanda, "dw", 2) == 0) {
                        strcpy(sir_auxiliar, stiva_undo->comanda);
                        strcpy(sir_auxiliar2, stiva_undo->sir_memorat);
                        Operatie_DW_DA(capete, pozitii, stiva_undo->sir_memorat, 1);
                        stiva_redo = adaugareStiva(stiva_redo, sir_auxiliar, sir_auxiliar2, sir_special2, litera_speciala, pozitie_speciala);
                        stiva_undo = eliminare_el_stiva(stiva_undo, sir_auxiliar, sir_auxiliar2, sir_special2, litera_speciala, pozitie_speciala);
                        sir_auxiliar[0] = '\0';
                        sir_auxiliar2[0] = '\0';
                    }   
                    else if (strncmp(stiva_undo->comanda, "da", 2) == 0) {
                        strcpy(sir_auxiliar, stiva_undo->comanda);
                        strcpy(sir_auxiliar2, stiva_undo->sir_memorat);
                        Operatie_DW_DA(capete, pozitii, stiva_undo->sir_memorat, -1);
                        stiva_redo = adaugareStiva(stiva_redo, stiva_undo->comanda, stiva_undo->sir_memorat, stiva_undo->sir_memorat2, litera_speciala, pozitie_speciala);
                        stiva_undo = eliminare_el_stiva(stiva_undo, sir_auxiliar, sir_auxiliar2, sir_special2, litera_speciala, pozitie_speciala);
                        sir_auxiliar[0] = '\0';
                        sir_auxiliar2[0] = '\0';
                    }
                }
//----------------- D   A  M ----------------- D   E----------------- R   E   D   O -----------------
                // Daca intalnim un redo atunci trebuie sa verificam ce comanda contine nodul
                // Din varful stivei de redo si sa efectuam operatia initiala, aferenta.
                // Trebuie sa avem grija sa eliminam nodul respectiv dupa ce am efecutat operatia.
                if (strcmp(sir, "r\n") == 0) {
                    if (strcmp(stiva_redo->comanda, "b\n") == 0) {
                        Operatie_Backspace(capete, pozitii);
                        param1 = stiva_redo->comanda;
                        c = stiva_redo->litera;
                        eliminare_el_stiva(stiva_redo, param1, sir_special, sir_special2, c, pozitie_speciala);
                    }
                    else if (strcmp(stiva_redo->comanda, ":i\n") == 0 || strcmp(stiva_redo->comanda, ":i \n") == 0) {
                        strcpy(sir_auxiliar, stiva_redo->comanda);
                        strcpy(sir_auxiliar2, stiva_redo->sir_memorat);
                        x = strlen(sir_auxiliar2);
                        int contor3 = 0;
                        while (x) {
                            Operatie_ReverseBackspace(capete, pozitii, sir_auxiliar2[contor3++]);
                            x--;
                        }
                        afisareListaDubla(capete);
                        sir_auxiliar2[0] = '\0';
                        sir_auxiliar[0] = '\0';
                    }
                    else if (strncmp(stiva_redo->comanda, "dl", 2) == 0) {
                        param1 = strtok(stiva_redo->comanda, " ");
                        param1 = strtok(NULL, " ");
                        ss = stiva_redo->comanda;
                        if (param1 == NULL) {
                            s = Operatie_DL(capete, pozitii, pozitii->linie);
                            stiva_redo = eliminare_el_stiva(stiva_redo, ss, sir_special, sir_special2, litera_speciala, pozitie_speciala);
                            free(s);
                        }
                        else {
                            s = Operatie_DL(capete, pozitii, atoi(param1));
                            stiva_redo = eliminare_el_stiva(stiva_redo, ss, sir_special, sir_special2, litera_speciala, pozitie_speciala);
                            free(s);
                        }
                    }
                    else if (strncmp(stiva_redo->comanda, "gl", 2) == 0) {
                        strcpy(sir_auxiliar, stiva_redo->comanda);
                        param1 = strtok(stiva_redo->comanda, " ");
                        param1 = strtok(NULL, " ");
                        Poz* x = Operatie_go_line(capete, atoi(param1), pozitii);
                        stiva_redo = eliminare_el_stiva(stiva_redo, sir_auxiliar, sir_special, sir_special2, litera_speciala, pozitie_speciala);
                        free(x);
                        sir_auxiliar[0] = '\0';
                    }
                    else if (strncmp(stiva_redo->comanda, "gc", 2) == 0) {
                        strcpy(sir_auxiliar, stiva_redo->comanda);
                        param1 = strtok(stiva_redo->comanda, " ");
                        param1 = strtok(NULL, " ");
                        param2 = strtok(NULL, " \n");
                        if (param2 == NULL) {
                            Poz* x = Operatie_go_to_char(capete, pozitii, atoi(param2), -2);
                            stiva_redo = eliminare_el_stiva(stiva_redo,sir_auxiliar, sir_special, sir_special2, litera_speciala, pozitie_speciala);
                            free(x);
                        }
                        else {
                            Poz* x = Operatie_go_to_char(capete, pozitii, atoi(param2) , atoi(param1));
                            stiva_redo = eliminare_el_stiva(stiva_redo, sir_auxiliar, sir_special, sir_special2, litera_speciala, pozitie_speciala);
                            free(x);
                        }
                        sir_auxiliar[0] = '\0';
                    }
                    else if ((strncmp(stiva_redo->comanda, "d ", 2) == 0)) {
                        strcpy(sir_auxiliar, stiva_redo->comanda);
                        Poz* o = Operatie_go_to_char(capete, pozitii, stiva_redo->pozitii->coloana, stiva_redo->pozitii->linie);
                        param1 = strtok(stiva_redo->comanda, " ");
                        param1 = strtok(NULL, " ");
                        x = atoi(param1);
                        while (x) {
                            c = Operatie_Backspace(capete, pozitii);
                            x--;
                        }
                        stiva_redo = eliminare_el_stiva(stiva_redo, sir_auxiliar, sir_special, sir_special2, litera_speciala, o);
                        sir_auxiliar[0] = '\0';
                        free(o);
                    }
                    else if (strcmp(stiva_redo->comanda, "d\n") == 0) {
                        strcpy(sir_auxiliar, stiva_redo->comanda);
                        Poz* o = Operatie_go_to_char(capete, pozitii, stiva_redo->pozitii->coloana, stiva_redo->pozitii->linie);
                        c = Operatie_Backspace(capete, pozitii);
                        stiva_redo = eliminare_el_stiva(stiva_redo, sir_auxiliar, sir_special, sir_special2, litera_speciala, o);
                        free(o);
                        sir_auxiliar[0] = '\0';
                    }
                    else if (strncmp(stiva_redo->comanda, "re", 2) == 0) {
                        strcpy(sir_auxiliar, stiva_redo->comanda);
                        param1 = strtok(stiva_redo->comanda, " ");
                        param1 = strtok(NULL, " ");
                        param2 = strtok(NULL, " \n");
                        Operatie_RE_RA(capete, pozitii, param1, param2, 1);
                        s = stiva_redo->sir_memorat;
                        ss = stiva_redo->sir_memorat2;
                        stiva_redo = eliminare_el_stiva(stiva_redo, sir_auxiliar, s, ss, litera_speciala, pozitie_speciala);
                        sir_auxiliar[0] = '\0';
                    }
                    else if (strncmp(stiva_redo->comanda, "ra", 2) == 0) {
                        strcpy(sir_auxiliar, stiva_redo->comanda);
                        param1 = strtok(stiva_redo->comanda, " ");
                        param1 = strtok(NULL, " ");
                        param2 = strtok(NULL, " \n");
                        Operatie_RE_RA(capete, pozitii, param1, param2, -1);
                        s = stiva_redo->sir_memorat;
                        ss = stiva_redo->sir_memorat2;
                        stiva_redo = eliminare_el_stiva(stiva_redo, sir_auxiliar, s, ss, litera_speciala, pozitie_speciala);
                        sir_auxiliar[0] = '\0';
                    }
                    else if (strncmp(stiva_redo->comanda, "dw", 2) == 0) {
                        strcpy(sir_auxiliar, stiva_redo->comanda);
                        strcpy(sir_auxiliar2, stiva_redo->sir_memorat);
                        param1 = strtok(stiva_redo->comanda, " ");
                        param1 = strtok(NULL, " ");
                        Operatie_DW_DA(capete, pozitii, param1, 1);
                        stiva_redo = eliminare_el_stiva(stiva_redo, sir_auxiliar, sir_auxiliar2, sir_special2, litera_speciala, pozitie_speciala);
                        sir_auxiliar[0] = '\0';
                        sir_auxiliar2[0] = '\0';
                    }
                    else if (strncmp(stiva_redo->comanda, "da", 2) == 0) {
                        strcpy(sir_auxiliar, stiva_redo->comanda);
                        param1 = strtok(stiva_redo->comanda, " ");
                        param1 = strtok(NULL, " ");
                        Operatie_DW_DA(capete, pozitii, param1, -1);
                        s = stiva_redo->sir_memorat;
                        ss = stiva_redo->sir_memorat2;
                        stiva_redo = eliminare_el_stiva(stiva_redo, sir_auxiliar, s, ss, litera_speciala, pozitie_speciala);
                        sir_auxiliar[0] = '\0';
                    }
                }
            }
        }
        // Aici ne situam pe modul de inserare litera-cu-litera in care trebuie sa avem
        // In vedere sa crestem acel contor care ne indica, in caz ca exista multiple inserari
        // De text, cate linii continea secventa de text de la pasul respectiv pentru a sti
        // Daca stergem \n de la finalul secventei sau nu
        else {
            if (ch == 10 && capete->cursor != capete->sfarsit )
                contor_endline++; 
            adaugareInLista(capete, pozitii, ch);
            // Construim un sir care contine secventa de text adaugata in lista pentru a
            // O salva intr-un nod de stiva ca sa putem stii, in caz de undo sau redo,
            // Sa o stergem/adaugam inapoi
            sir_auxiliar3[m++] = ch; 
     
        }
    }
    return 0;
}
