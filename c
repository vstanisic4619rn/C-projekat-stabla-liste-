#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cvor{
    char opstina[50];
    char teretana[50];
    int brojSprava;
    int brojKardio;
    struct Cvor* levi;
    struct Cvor* desni;
}Cvor;

void meni(){
    printf("Meni : \n\t1. Ucitavanje stabla\n\t2. Ispis svih teretana");
    printf("\n\t3. Ispis teretana sa spravama\n\t4. Ispis svih teretana u odredjenoj opstini");
    printf("\n\t5. Izlaz iz programa\nUnesite opciju : ");
}

void ispisCvora(Cvor* cvor){
    printf("\t%s (%s) - %d [%d]\n", cvor->teretana, cvor->opstina, cvor->brojSprava, cvor->brojKardio);
}

//Cukarica-Ahilej-92-21
Cvor* kreirajCvor(char* linija){
    Cvor* nov = (Cvor*) malloc(sizeof(Cvor));

    char* token = strtok(linija, "-");
    strcpy(nov->opstina, token);

    token = strtok(NULL, "-");
    strcpy(nov->teretana, token);

    token = strtok(NULL, "-");
    int brojSprava = atoi(token);
    nov->brojSprava = brojSprava;

    token = strtok(NULL, "-");
    int brojKardio = atoi(token);
    nov->brojKardio = brojKardio;

    nov->levi = NULL;
    nov->desni = NULL;

  //  ispisCvora(nov);

    return nov;
}

//Po opstini opadajuce (skroz levo treba da bude najveca opstina).
Cvor* dodajCvor(Cvor* koren, Cvor* noviCvor){
    if(koren == NULL)
        return noviCvor;

    if(strcmp(koren->opstina, noviCvor->opstina) < 0)
        koren->levi = dodajCvor(koren->levi, noviCvor);
    else
        koren->desni = dodajCvor(koren->desni, noviCvor);

    return koren;
}

void ispisStabla(Cvor* koren){
    if(koren == NULL)
        return;

    ispisStabla(koren->levi);
    ispisCvora(koren);
    ispisStabla(koren->desni);
}

void ispisStablaRastuce(Cvor* koren){
    if(koren == NULL)
        return;

    ispisStablaRastuce(koren->desni);
    ispisCvora(koren);
    ispisStablaRastuce(koren->levi);
}

//Sve teretane takve da je broj sprava koje nisu kardio veci od brojac
void ispisTeretanaSaSpravama(Cvor* koren, int broj){
    if(koren == NULL)
        return;

    ispisTeretanaSaSpravama(koren->levi, broj);     //pokreni levo podstablo rekurzivno 

    if((koren->brojSprava - koren->brojKardio) > broj){
        ispisCvora(koren);      //ovaj koren ispunjava uslov        
    }

    ispisTeretanaSaSpravama(koren->desni, broj);        //pokreni desno podstablo rekurzivno 
}

void ispisOpstinePoImenu(Cvor* koren, char* deo){
    if(koren == NULL)
        return;

    ispisOpstinePoImenu(koren->levi, deo);

    int offset = strlen(koren->opstina) - strlen(deo);
    //koren->opstina + offset :: kao da radimo sa novim stringom koji pocinje
    //  od pozicije offset u stringu koren->opstina
    if(strcmp(deo, koren->opstina + offset) == 0){
        ispisCvora(koren);
    }
    /*
    koren->opstina = Vozdovac : 8  : 0 + (8 - 4)
    ovac     : 4
    */

    ispisOpstinePoImenu(koren->desni, deo);
}





void brisanjeStabla(Cvor* koren){
    if(koren == NULL)
        return;

    brisanjeStabla(koren->levi);
    brisanjeStabla(koren->desni);
    free(koren);

    return;
}

int main()
{
    //Pravimo prazno stablo
    Cvor* koren = NULL;

    while(1){

        meni();

        int opcija;
        scanf("%d", &opcija);

        switch(opcija){
            case 1 : {
                //Ucitavamo podatke iz fajla u BPS
                FILE* fajl = fopen("UUP-21-22-FEB-G1-ulaz3.txt", "r");

                if(fajl == NULL){
                    printf("Doslo je do greske prilikom otvaranja fajla!");
                    break;
                }
                printf("\tUspesno je otvoren fajl!\n");


                char linija[200];

                do {
                    fgets(linija, 200, fajl);
                   // puts(linija);

                    Cvor* noviCvor = kreirajCvor(linija);
                    koren = dodajCvor(koren, noviCvor);

                } while(!feof(fajl));

                //ispisStabla(koren);

                fclose(fajl);

                break;
            }
            case 2 : {
                ispisStablaRastuce(koren);
                break;
            }
            case 3 : {
                printf("\tUnesite broj : ");
                int broj;
                scanf("%d", &broj);

                ispisTeretanaSaSpravama(koren, broj);
                break;
            }
            case 4 : {
                printf("\tUnesite deo naziva opstine : ");
                char deo[20];
                scanf("%s", deo);
              //  fgets(deo, 20, stdin);

                ispisOpstinePoImenu(koren, deo);
                break;
            }
            case 5 : {
                brisanjeStabla(koren);
                return 2;
            }
            default : {
                printf("Unos opcije nije validan!\n");
            }
        }

    }

    return 0;
}




typedef struct Teretana{

    char opstina [30];
    char ime[30];
    int brSprava;
    int kardioSprave;

    struct Teretana* levo;
    struct Teretana* desno;


}Teretana;


Teretana* kreirajTeretanu(char opstina[], char ime[], int brSprava, int kardioSprave){

Teretana* novi = (Teretana*)malloc(sizeof(Teretana));
strcpy(novi->ime, ime);
strcpy(novi->opstina, opstina);
novi->brSprava = brSprava;
novi->kardioSprave = kardioSprave;

novi->levi = NULL;
novi->desni= NULL;

return novi;

}

void meni(){
printf("Unesite opciju koju zelite : \n");
printf("Unesite 1 da biste ucitali podatke: \n");
printf("Unesite 2 radi ispisa svih teretana  : \n");
printf("Unesite opciju koju zelite : \n");
printf("Unesite opciju koju zelite : \n");
}


void ispisCvora(Teretana* cvor){
printf("%s  %s   %d   %d  \n", cvor->ime, cvor->opstina, cvor->brSprava, cvor-> kardioSprave);
}

Teretana* dodajCvor(Teretana* koren, Teretana* novi){

    if(koren==NULL){
        return novi;
    }

    if(strcmp(novi->opstina, koren->opstina)<0){
        koren->levo= dodajCvor(koren->levo, novi);
    }else{
        koren->desno=dodajCvor(koren->desno, novi);
    }

    return koren;
}

void ispisStabla(Teretana* koren){
if(koren == NULL){
    return;
}
ispisStabla(koren->levo);
ispisCvora(koren);
ispisStabla(koren->desno);

}

Teretana* ucitaj_fajl(){

FILE fp = fopen("probni_fajl.txt","r");
if(fp==NULL){
    printf("Pogresno ucitan fajl \n");
}
char linija[255];
Teretana* koren=NULL;

while(fgets(linija,255,fp)){
char* ime = strtok(linija,"-");
char opstina = strtok(NULL,"-");
int brSprava= atoi(strtok(NULL,"-"));
int kardioSprave=atoi(strtok(NULL,"\n"));

Teretana* novi = kreirajTeretanu(opstina,ime,brSprava,kardioSprave);


koren=dodajCvor(koren,novi);


fclose(fp);
return koren;

}



}

int main(){

Teretana* koren = NULL;
int opcija;
meni();
printf("Odaberite opciju: \n");
scanf("%d",&opcija);

switch(opcija){

    case 1: {   
    koren = ucitaj_fajl();
    break;

}
    case 2: {  
    ispisStablaRastuce(koren);
    break;

}
    case 3: 


}




typedef struct Ljudi {
    char ime [100];
    int visina;
    int tezina;
    struct Ljudi* levo;
    struct Ljudi* desno;

}Ljudi;


Ljudi* napraviOsobu(char ime [], int visina, int tezina){
Ljudi* osoba = (Ljudi)malloc(sizeof(Ljudi));
strcpy(osoba->ime, ime);
osoba->visina=visina;
osoba->tezina=tezina;
osoba->levo = NULL;
osoba->desno=NULL;

return osoba;
}

Ljudi* dodajOsobu(Ljudi* koren, Ljudi* novi){
    if(koren == NULL){
        return novi;
    }

    if(strcmp(novi->ime, koren->ime) < 0){
        koren->levo= dodajOsobu(koren->levo, novi);

    }else{
        koren->desno=dodajOsobu(koren->desno, novi);
    }

    return koren;

}


Ljudi* ucitaj_fajl(){
    FILE fp= fopen("UUP_ispit.txt", "r");

    if(fp ==NULL ){
        printf("Greska pri ucitavanju fajla \n");
        return NULL;
    }
    char linija[255];

    while(fgets(linija,255,fp)){
        char* ime = strtok(linija, ",");
        int visina = atoi(strtok(NULL,","));
        int tezina = atoi(strtok(NULL, ","));

        Ljudi* novi = napraviOsobu(ime,visina,tezina);
        Ljudi* koren = NULL;


        koren = dodajOsobu(koren, novi);


    }

fclose(fp);

return koren;

}

void stampaj(Ljudi* koren){

printf("%s  %d  %d  \n", koren->ime, koren->visina, koren-> tezina );

}

void stampaj_sve(Ljudi* koren){
if(koren == NULL){
    return;
}
stampaj_sve(koren->levo);
stampaj(koren);
stampaj_sve(koren->desno);

}

void obrisi_drvo(Ljudi* koren){
    if(trenutni == NULL){
        return;
    }

    obrisi_drvo(koren->levo);
    obrisi_drvo(koren->desno);
    free(koren);
}


int main(){
int opcija;

Ljudi* koren = NULL;

while(1){
scanf("%d", &opcija);

if(opcija == 1){
    koren = ucitaj_fajl();
}else if (opcija ==2){
    stampaj_sve(koren);
}else if (opcija == 3){
    obrisi_drvo(koren);
    return 0;
}
else{
    printf("Pogresan unos ! \n");
}


}

}



//  Napisati program koji obrađuje podatke o cvecari koriscenjem binarnog stabla.
//  Podatke o cvecari učitati iz fajla u kom su podaci o svakom cvetu predstavljeni na slededi način, svaki cvet u novoj liniji:
//  Naziv,kolicina,cena (na primer Ruza,34,100)
//  Napraviti meni za interakciju sa korisnikom preko konzole sa slededim opcijama:
//      1) učitavanje podataka iz fajla, ime fajla unosi korisnik, podaci se učitavaju u pretrazivacko stablo na osnovu cene
//      2) ispis svih cvetova iz stabla sortirano rastuce po ceni
//      3) ispis ukupnog broja cvetova u cvecari
//      4) brisanje cveta odredjene cene, korisnik unosi cenu
//      5) izlaz iz programa (obrisatu stablo iz memorije)



typedef struct Cvece{
    char naziv [100];
    int kolicina;
    int cena;

    struct Cvece* levo;
    struct Cvece* desno;

}Cvece;



void meni(){
printf("Unesite broj koju komandu zelite da aktivirate : \n");
printf(" 1.   Ucitavanje podataka iz fajla  \n");
printf("2. Ispis cvetova sortiranih  \n");
printf("3. ispis ukupnog broja cvetova :  \n");
printf("4. Brisanje cveta odredjene cene:  \n");
printf("Izlaz iz programa i brisanje :  \n");
}

Cvet* kreirajCvet(char naziv[100], int kolicina, int cena){

    Cvet* novi = (Cvet*)malloc(sizeof(Cvet));
    strcpy(novi->naziv, naziv);
    novi->kolicina = kolicina;
    novi-> cena = cena; 
    novi-> levo = NULL; 
    novi->desno = NULL;
    return novi;

}






Cvece* dodajNovi(Cvece* koren, Cvece* novi){

    if(koren == NULL){
        return novi;
    }
    if(koren->cena > novi-> cena ){
        koren-> levo = dodajNovi(koren->levo, novi);
    }else{
        koren->desno = dodajNovi(koren->desno, novi);
    }
    return koren;
}

Cvece* napraviFajl(){

FILE *fp; 
char linija[255];
fp = fopen("UUP_podaci.txt","r");

if(fp == NULL){
    printf("Pogresno ucitan fajl \n");
    return NULL;
}

while(linija,255,fp){
    char* naziv = strtok(linija,",");
    int kolicina = atoi(strtok(NULL,","));
    int cena = atoi(strtok(NULL, "\n"));
Cvece* novi = kreirajCvet(naziv, kolicina, cena);
Cvece* koren = NULL;
koren = dodajNovi(koren, novi);
}

fclose(fp);
return koren;

}

void ispisiSveCvetove(Cvece* koren){
    if(koren == NULL){
        return;
    }

    ispisiSveCvetove(koren->levo);
    printf("%s %d %d \n", koren->ime, koren->kolicina, koren->cena);
    ispisiSveCvetove(koren->desno);

}


int brCvetova(Cvece *koren){
    if(koren == NULL){
        return;
    }
    return koren -> kolicina + brCvetova(koren -> levo) + brCvetova(koren -> desno);
}

Cvece* minCvet(Cvece *koren){
    if(!koren->levo){
        return koren;
    }
    return minCvet(koren->levo);
}


void brisiStablo(Cvece *koren){
    if(koren){
        brisiStablo(koren->levo);
        brisiStablo(koren->desno);
        free(koren);
    }

}



int main(){


Cvece* koren = NULL;
int opcija, cena;

while(1){

meni();
scanf("%d", &opcija);

    switch(opcija){

        case 1: {
            koren = ucitaj_fajl();
            break;
        }
        case 2: { 
        ispisiSveCvetove(koren);
            break;
        }
        case 3:{
brisanjeStabla(koren);

        }

    }




}


}

------------------------------------------------------

typedef struct Temperatura{
    char drzava[20];
    char grad[20];
    int temperatura;

    Temperatura* levo;
    Temperatura* desno;


}Temperatura;


Temperatura* napraviGrad(char drzava[20], char grad[20],int temperatura){
    Temperatura* novi= (Temperatura*)malloc(sizeof(Temperatura));
    strcpy(novi->drzava, drzava);
    strcpy(novi->grad, grad);
    novi->temperatura = temperatura;

    novi->levo = NULL;
    novi->desno=NULL;

    return novi;

}


Temperatura* dodajNode(Temperatura* stablo, Temperatura* novi){
    if(stablo == NULL){
        return novi;
    }

    if(strcmp(novi->grad, stablo-> grad) < 0){
        stablo->levo = dodajNode(stablo->levo, novi);

    }else{
        stablo->desno = dodajNode(stablo->desno, novi);
    }
}


void ispisiTrenutni(Temperatura* koren){
    printf("%s  %s  %d", koren->drzava, koren->grad, koren->temperatura);

}

void ispisiSve(Temperatura* koren){
    if(koren){
        ispisiSve(koren->levo);
        ispisiTrenutni(koren);
        ispisiSve(koren->desno);

    }

}

Temperatura* ucitajFajl(){

FILE fp = fopen("UUP_z3.txt", "r");
char linija[255];
Temperatura* koren = NULL;

while(fgets(linija, 255, fp) != NULL){

    char drzava = strtok(linija, " ");
    char grad = strtok(NULL, " ");
    int temperatura = atoi(strtok(NULL, "\n"));

    Temperatura* novi = napraviGrad(drzava, grad, temperatura);
    koren = dodajNode(koren, novi);

}
return koren;

}


int main(){


Temperatura* koren = NULL;
int opcija;

while(1){
scanf("%d",&opcija);

meni();



}


}







typedef struct Osoba{
    char ime[40];
    char nazivDijete[40];
    int kilogrami;
   struct Osoba* levo;
   struct Osoba* desno;
}Osoba;


Osoba* kreirajOsobu(char ime[], char nazivDijete[], int kilogrami){

    Osoba *nova= (Osoba*)malloc(sizeof(Osoba));
    strcpy(nova->nazivDijete,nazivDijete);
    nova->kilogrami =kilogrami;
    Osoba* levo=NULL;
    Osoba* desno = NULL;

    return nova;
}

Osoba* dodajOsobu(Osoba* koren, Osoba* nova){
    if(koren == NULL){
        return nova;
    }

    if(strcmp(koren, nova) < 0){
        koren->levo=dodajOsobu(koren->levo, nova);
    }else{
        koren->desno=dodajOsobu(koren->desno, nova);
    }
    return koren;
}


void ispisiOsobu(Osoba* koren){
    printf("%s %s %d \n",koren->ime, koren->nazivDijete, koren->kilogrami);
}

void ispisiSve(Osoba* koren){
    ispisiSve(koren->levo);
    ispisiOsobu(koren);
    ispisiSve(koren->desno);
}


Osoba* ucitajFajl(){
FILE fp= fopen("UUP.txt", "r");
Osoba* koren = NULL;

if(fp == NULL){
    printf("Doslo je do greske prilikom ucitavanja fajla \n");
}
char linija[255];

while(fgets(linija, 255, fp) != 0){
    char* ime = strtok(linija, " ");
    char dijeta=strtok(NULL, " ");
    int kilogrami = atoi(strtok(NULL, "\n");

    Osoba* nova = kreirajOsobu(ime,dijeta,kilogrami);
    koren = dodajOsobu(koren, novi);

}


fclose(fp);
return koren;

}

Osoba* napraviKopiju(Osoba* original){
    Osoba* nova= (Osoba*)malloc(sizeof(Osoba));
    strcpy(nova->ime, original->ime);
    strcpy(nova->nazivDijete, original->nazivDijete);
    nova->kilogrami=original->kilogrami;


    return nova;



}

Osoba* obrisiSve(Osoba* koren){
if(koren != NULL){
    obrisiSve(koren->levo);
    obrisiSve(koren->desno);
    free(koren);
}
return NULL;
}

void NajvisaNajniza (Osoba* koren, Osoba* najvisa, Osoba* najniza){

    if(koren == NULL){
        return;
    }

    najvisaNajniza(koren->levo,najvisa,najniza);
    najvisaNajniza(koren->desno, najvisa, najniza);

    if(koren->visina > najvisa->visina){
        najvisa->visina = koren->visina;
        strcpy(najvisa->ime, koren->ime);
        najvisa->kilogrami = koren->kilogrami;
    }

    if(koren->visina < najniza->visina){
        najniza->visina = koren->visina;
        strcpy(najniza->ime, koren->ime);
        
    }


}