#include <stdio.h>

typedef struct Drvo{
    char ime[255];
    int visina;
    int tezina;
    struct Drvo* levo;
    struct Drvo* desno;
} Drvo;

typedef struct Drvo2{ 
    char ime[250];
    int tezina;
    struct Drvo2* levo;
    struct Drvo2* desno;

}Drvo2;

Drvo2* napravi2(char ime[], int tezina){
    Drvo2* novi= (Drvo2*)malloc(sizeof(Drvo2));
    strcpy(novi->ime, ime);
    novi->tezina= tezina;
    novi->levo = NULL;
    novi->desno=NULL;
    
    return novi;
}

Drvo2* dodaj2(Drvo2* koren, Drvo2* novi){
    if(koren==NULL){
        return novi;
    }

    if(strcmp(novi->ime, trenutni-> ime) < 0){
        koren->levo= dodaj(koren->levo, novi);
    }else{
        koren->desno=dodaj(koren->desno, novi);
    }
}

Drvo* napravi(char* ime, int visina, int tezina){
    Drvo* drvo = (Drvo*)malloc(sizeof(Drvo));
    strcpy(drvo->ime, ime);
    drvo->visina = visina;
    drvo->tezina = tezina;
    drvo->levo = NULL;
    drvo->desno = NULL;

    return drvo;
}


void napraviPoTezini(Drvo* koren, Drvo2* koren2, int tezina){
    if(koren == NULL){
        return;
        napraviPoTezini(koren->levo, koren2, tezina);
        napraviPoTezini(koren->desno, koren2, tezina);

        if(koren->tezina < tezina){
            Drvo2* novi = napravi2(koren->ime, koren->tezina);
            koren=dodaj2(koren, novi);
        }
    }

}

Drvo* dodaj(Drvo* trenutni, Drvo* za_dodavanje){
    if(trenutni == NULL)
        return za_dodavanje;

    if(strcmp(za_dodavanje->ime, trenutni->ime) < 0){
        trenutni->levo = dodaj(trenutni->levo, za_dodavanje);
    }
    else{
        trenutni->desno = dodaj(trenutni->desno, za_dodavanje);
    }

    return trenutni;
}

/// UUP-21-22-JAN-G2-Z3 fajl
Drvo* ucitaj_fajl(){
    FILE* fp = fopen("UUP-21-22-JAN-G2-Z3 fajl.txt", "r");
    if(fp == NULL){
        printf("Nisam uspeo da otvorim fajl :(\n");
        return NULL;
    }
    Drvo* koren = NULL;
    char linija[255];
    while(fgets(linija, 255, fp)){
        char* ime = strtok(linija, ",");
        int visina = atoi(strtok(NULL, ","));
        int tezina = atoi(strtok(NULL, "\n"));
        Drvo* element = napravi(ime, visina, tezina);
        /// Dodavanje u stablo
        koren = dodaj(koren, element);
    }

    fclose(fp);
    return koren;
}

void stampaj(Drvo* trenutni){
    printf("%s %d %d\n", trenutni->ime, trenutni->visina, trenutni->tezina);
}

void stampaj_sve(Drvo* trenutni){
    if(trenutni == NULL)
        return;
    stampaj_sve(trenutni->levo);
    stampaj(trenutni);
    stampaj_sve(trenutni->desno);
}

void obrisi_drvo(Drvo* trenutni){
    if(trenutni == NULL)
        return;
    obrisi_drvo(trenutni->levo);
    obrisi_drvo(trenutni->desno);
    free(trenutni);
}

void najvisa_najniza(Drvo* trenutni, Drvo* najvisa, Drvo* najniza){
    if(trenutni == NULL)
        return;
    najvisa_najniza(trenutni->levo, najvisa, najniza);
    najvisa_najniza(trenutni->desno, najvisa, najniza);
    /// Uzmi trenutnu visinu osobe i uporedi sa najviseom i najnizom
    if(trenutni->visina > najvisa->visina){
        /// Azuriraj najvisa
        najvisa->visina = trenutni->visina;
        najvisa->tezina = trenutni->tezina;
        strcpy(najvisa->ime, trenutni->ime);
    }
    if(trenutni->visina < najniza->visina){
        /// Azuriraj najnizu
        najniza->visina = trenutni->visina;
        najniza->tezina = trenutni->tezina;
        strcpy(najniza->ime, trenutni->ime);
    }
}

Drvo* dodaj_u_novo_drvo(Drvo* novo_drvo_koren, Drvo* za_dodavanje){
    if(novo_drvo_koren == NULL)
        return za_dodavanje;
    if(za_dodavanje->tezina > novo_drvo_koren->tezina){
        novo_drvo_koren->levo = dodaj_u_novo_drvo(novo_drvo_koren->levo, za_dodavanje);
    }
    else{
        novo_drvo_koren->desno = dodaj_u_novo_drvo(novo_drvo_koren->desno, za_dodavanje);
    }
    return novo_drvo_koren;
}

Drvo* napravi_kopiju(Drvo* org){
    Drvo* kopija = (Drvo*)malloc(sizeof(Drvo));
    kopija->tezina = org->tezina;
    kopija->visina = org->visina;
    strcpy(kopija->ime, org->ime);
    return kopija;
}

void napravi_po_tezini(Drvo* koren, Drvo** noviKoren, int tezina){
    /// Obilazak postojeceg drveta
    if(koren == NULL)
        return;
    napravi_po_tezini(koren->levo, noviKoren, tezina);
    napravi_po_tezini(koren->desno, noviKoren, tezina);
    /// Dodaj u novo drvo
    if(koren->tezina < tezina)
        *noviKoren = dodaj_u_novo_drvo(*noviKoren, napravi_kopiju(koren));
}

/// Marko,189,79
int main(){

    int opcija;
    Drvo* koren = NULL;
    while(1){
        scanf("%d", &opcija);
        if(opcija == 1){
            /// Ucitaj iz fajla
            koren = ucitaj_fajl();
        }
        else if(opcija == 2){
            stampaj_sve(koren);
        }
        else if(opcija == 3){
            /// najvisa i najniza osoba
            Drvo najvisa;
            Drvo najniza;
            najniza.visina = 999;
            najvisa.visina = 0;
            najvisa_najniza(koren, &najvisa, &najniza);
            printf("%s %d %d\n", najvisa.ime, najvisa.visina, najvisa.tezina);
            printf("%s %d %d\n", najniza.ime, najniza.visina, najniza.tezina);
        }
        else if(opcija == 4){
            /// Ispis svih osoba lakis od tezine, nerastuce
            printf("Unesi tezinu\n");
            int tezina;
            scanf("%d", &tezina);
            Drvo* novi_koren = NULL; /// Cuva novo stablo sortirano po tezini
            napravi_po_tezini(koren, &novi_koren, tezina);
            stampaj_sve(novi_koren);
            obrisi_drvo(novi_koren);
        }
        else if(opcija == 5){
            obrisi_drvo(koren);
            return 0;
        }
        else{
            printf("Pogresan unos!\n");
        }
    }
    return 0;
}
