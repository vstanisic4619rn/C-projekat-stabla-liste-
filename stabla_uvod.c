#include <stdio.h>

typedef struct {
    char ime[255];
    char dijeta[255];
    int kilaza;
    struct Tree* left;
    struct Tree* right;
} Tree;

Tree* make_new(char* ime, char* dijeta, int kilaza){
    Tree* new_node = (Tree*)malloc(sizeof(Tree));
    new_node->kilaza = kilaza;
    strcpy(new_node->ime, ime);
    strcpy(new_node->dijeta, dijeta);
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

Tree* insert_node_r(Tree* curr, Tree* to_add){
    if(curr == NULL){
        return to_add;
    }
    /// isti == 0
    /// prvi < drugi vraca (<0)
    /// prvi > drugi vraca (>0)
    if(strcmp(to_add->dijeta, curr->dijeta) < 0){
        curr->left = insert_node_r(curr->left, to_add);
    }
    else{
        curr->right = insert_node_r(curr->right, to_add);
    }
    return curr;
}

void delete_bst(Tree* node){
    if(node == NULL){
        return;
    }
    delete_bst(node->left);
    delete_bst(node->right);
    free(node);
}

void print_bst(Tree* curr){
    if(curr == NULL)
        return;
    print_bst(curr->left);
    printf("%s [%s] - %d\n", curr->ime, curr->dijeta, curr->kilaza);
    print_bst(curr->right);
}

void print_part_name(Tree* curr, char* part_of_name){
    if(curr == NULL)
        return;
    print_part_name(curr->left, part_of_name); /// left part
    char lowercase_name[255];
    strcpy(lowercase_name, curr->ime); /// lowercase_name = "Andjela"
    strlwr(lowercase_name); /// "andjela"
    strlwr(part_of_name); /// "an" ("AN")
    if(strstr(lowercase_name, part_of_name) != NULL){
        printf("%s [%s] - %d\n", curr->ime, curr->dijeta, curr->kilaza);
    }
    print_part_name(curr->right, part_of_name); /// right part
}

/// TODO: Fix
void best_diet(Tree* curr, char* prev_diet, char* best_diet_name, float* best_diet_avg, int* broj_o, int* suma){
    if(curr == NULL)
        return;
    /// levo
    best_diet(curr->left, curr->dijeta, best_diet_name, best_diet_avg, broj_o, suma);
    /// iste dijete, povecaj broj osoba na toj dijeti za 1, dodaj na sumu kilazu nove osobe
    if(strcmp(prev_diet, curr->dijeta) == 0){
        (*broj_o)++;
        (*suma) += curr->kilaza;
    } /// razlicite dijete, [bez glutena] i [hrono]
    else{
        float avg = (*suma) * 1.0 / (*broj_o);
        /// ako je prev_diet najbolja do sada, azuriraj vrednosti
        if(avg > *best_diet_avg){
            *best_diet_avg = avg;
            strcpy(best_diet_name, prev_diet);
        }
        /// resetovanje vrednosti za narednu dijetu
        *broj_o = 1;
        *suma = curr->kilaza;
    }
    /// desno
    best_diet(curr->right, curr->dijeta, best_diet_name, best_diet_avg, broj_o, suma);
}

/// Petar,paleo,2
int main(){


    char linija[255];
    Tree* root = NULL;

    int opcija;
    while(1){
        printf("Zdravo, izaberi opciju\n");
        scanf("%d", &opcija);
        if(opcija == 1){
            /// Ucitaj iz fajla
            FILE* fp = fopen("fajl.txt", "r");
            while(fgets(linija, 255, fp)){
                char* ime = strtok(linija, ",");
                char* dijeta = strtok(NULL, ",");
                int kilaza = atoi(strtok(NULL, "\n")); // "2" -> (int) 2

                Tree* node = make_new(ime, dijeta, kilaza);
                root = insert_node_r(root, node);
            }
            fclose(fp);
        }
        else if(opcija == 2){
            /// Stampaj stablo
            print_bst(root);
        }
        else if(opcija == 3){
            float best_diet_avg = 0;
            int broj_o = 0;
            int suma = 0;
            char best_diet_name[255];
            best_diet(root, root->dijeta, best_diet_name, &best_diet_avg, &broj_o, &suma);
            printf("%s - %f\n", best_diet_name, best_diet_avg);
        }
        else if(opcija == 4){
            printf("Unesite deo imena osobe\n");
            char deo[255];
            scanf("%s", deo);
            print_part_name(root, deo);
        }
        else if(opcija == 5){                   //komunikacija sa konzolom 
            delete_bst(root);
            return 0;
        }
    }
    return 0;
}
