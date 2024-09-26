//  Napisati program koji obrađuje podatke o cvecari koriscenjem binarnog stabla.
//  Podatke o cvecari učitati iz fajla u kom su podaci o svakom cvetu predstavljeni na slededi način, svaki cvet u novoj liniji:
//  Naziv,kolicina,cena (na primer Ruza,34,100)
//  Napraviti meni za interakciju sa korisnikom preko konzole sa slededim opcijama:
//      1) učitavanje podataka iz fajla, ime fajla unosi korisnik, podaci se učitavaju u pretrazivacko stablo na osnovu cene
//      2) ispis svih cvetova iz stabla sortirano rastuce po ceni
//      3) ispis ukupnog broja cvetova u cvecari
//      4) brisanje cveta odredjene cene, korisnik unosi cenu
//      5) izlaz iz programa (obrisatu stablo iz memorije)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cvet{
    char naziv[20];
    int kolicina, cena;
    struct Cvet *left;
    struct Cvet *right;
}Cvet;

int ispisiMeni()
{
    char op[10];
    int opcija = 0;
    printf("MENI: \n");
    printf("1. Ucitaj datoteku\n");
    printf("2. Ispisi sve cvetove (sortirano rastuce po ceni)\n");
    printf("3. Ispisi ukupan broj cvetova\n");
    printf("4. Obrisi svet odredjene cene\n");
    printf("5. Izadji iz programa\n");
    while(opcija < 1 || opcija > 5){
        printf("Unesite opciju: ");
        fgets(op, 10, stdin);
        op[strlen(op) - 1] = 0;
        opcija = atoi(op);
    }
    return opcija;
}

Cvet *dodajSortirano(Cvet *stablo, Cvet *noviElement)
{
    if(!stablo){
        return noviElement;
    }
    if(stablo->cena > noviElement->cena){
        stablo->left = dodajSortirano(stablo->left, noviElement);
    }else{
        stablo->right = dodajSortirano(stablo->right, noviElement);
    }
    return stablo;
}

Cvet *ucitajDatoteku()
{
    char naziv[100], string[100], *token;
    FILE *f;
    Cvet *stablo = NULL;
    printf("Unesite ime datoteke: ");
    fgets(naziv, 100, stdin);
    naziv[strlen(naziv) - 1] = 0;
    if(f = fopen(naziv, "r")){
        while(fgets(string, 99, f) == string){
            Cvet *noviElement = (Cvet*) malloc(sizeof(Cvet));
            token = strtok(string, ",");
            strcpy(noviElement->naziv, token);
            token = strtok(NULL, ",");
            noviElement->kolicina = atoi(token);
            token = strtok(NULL, " \n");
            noviElement->cena = atoi(token);
            noviElement->left = NULL;
            noviElement->right = NULL;
            stablo = dodajSortirano(stablo, noviElement);
        }
        fclose(f);
        printf("Datoteka je uspesno ucitana\n");
    }else{
        printf("Datoteka ne postoji ili je nije moguce citati\n");
    }
    return stablo;
}

void ispisiCvet(Cvet* koren){
    printf("%s %d %d ", koren->naziv, koren->kolicina, koren->cena);
}

void ispisiSveCvetove(Cvet *stablo)
{
    if(!stablo){
        return;
    }
    ispisiSveCvetove(stablo->left);
    printf("%15s %5d %5d\n", stablo->naziv, stablo->kolicina, stablo->cena);    //ispisiCvet(koren);
    ispisiSveCvetove(stablo->right);
}

int brCvetova(Cvet *stablo)
{
    if(!stablo){
        return 0;
    }
    return stablo->kolicina + brCvetova(stablo->left) + brCvetova(stablo->right);
}

Cvet *minCvet(Cvet *stablo)
{
    if(!stablo->left){
        return stablo;
    }
    return minCvet(stablo->left);
}

Cvet *brisiCvet(Cvet *stablo, int cena)
{
    if(!stablo){
        return NULL;
    }
    if(stablo->cena > cena){
        stablo->left = brisiCvet(stablo->left, cena);
    }else if(stablo->cena < cena){
        stablo->right = brisiCvet(stablo->right, cena);
    }else{
        if(!stablo->left && !stablo->right){
            free(stablo);
            stablo = NULL;
        }else if(!stablo->left){
            Cvet *t = stablo;
            stablo = stablo->right;
            free(t);
        }else if(!stablo->right){
            Cvet *t = stablo;
            stablo = stablo->left;
            free(t);
        }else{
            Cvet *min = minCvet(stablo->right);
            strcpy(stablo->naziv, min->naziv);
            stablo->kolicina = min->kolicina;
            stablo->cena = min->cena;
            stablo->right = brisiCvet(stablo->right, min->cena);
        }
    }
    return stablo;
}

void brisiStablo(Cvet *stablo)
{
    if(stablo){
        brisiStablo(stablo->left);
        brisiStablo(stablo->right);
        free(stablo);
    }
}

int main()
{
    Cvet *cvece = NULL;
    int opcija, cena;
    while(1){
        opcija = ispisiMeni();
        switch(opcija){
            case 1:{
                brisiStablo(cvece);
                cvece = ucitajDatoteku();
                break;
            }
            case 2:{
                ispisiSveCvetove(cvece);
                break;
            }
            case 3:{
                printf("Ukupan broj cveca: %d\n", brCvetova(cvece));
                break;
            }
            case 4:{
                printf("Unesite cenu: ");
                scanf("%d", &cena);
                cvece = brisiCvet(cvece, cena);
                break;
            }
            case 5:{
                brisiStablo(cvece);
                return 0;
            }
        }
    }
}
