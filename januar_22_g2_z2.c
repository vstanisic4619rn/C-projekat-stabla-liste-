#include <stdio.h>
#include <string.h>
            //STRING ZADATAK SA ISPITA 
/**
Ulaz: Veselo srce pola zdravlja

Izlaz: VESELO SRCE pola zdravlja

*/

int je_samoglasnik(char c){
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'
        || c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

void rec_malim_slovima(char str[], int s, int e){
    /// Veselo
    /// s      e
    for(int i=s; i<e; i++){
        if(str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 32;
    }
}

void rec_velikim_slovima(char* str, int s, int e){
    for(int i=s; i<e; i++){
        if(str[i] >= 'a' && str[i] <= 'z')
            str[i] -= 32;
    }
}

int main(){
    char str[255];
    fgets(str, 255, stdin);
    str[strlen(str)-1] = 0; /// veselo0
    /// strlen() -> jedina dozvoljena
    int n = strlen(str);
    int s = 0, e;
    int broj_samoglasnika = 0;
    for(int i=0; i<=n; i++){
        /// dosao si do kraja reci
        if(str[i] == ' ' || i == n){
            e = i;
            /// ispisati rec malim slovima
            if(broj_samoglasnika % 2 == 0){
                rec_malim_slovima(str, s, e);
            }
            else{ /// ispisati rec velikim slovima
                rec_velikim_slovima(str, s, e);
            }
            broj_samoglasnika = 0;
            s = i+1;
        }
        else if(je_samoglasnik(str[i])){
            broj_samoglasnika++;
        }
    }

    fputs(str, stdout);
    return 0;
}
