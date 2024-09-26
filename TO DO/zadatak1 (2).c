#include <stdio.h>
#include <stdlib.h>

typedef struct Node{                                            //  Kod binarnih stabala, svaki element moze da ima levo dete ili desno dete (moze i oba).
    int data;                                                   //  Podaci.
    struct Node *left;                                          //  Pokazivac na levo dete.
    struct Node *right;                                         //  Pokazivac na desno dete.
}Node;

Node *createNode(int data)
{
    Node *new = (Node*) malloc(sizeof(Node));                        //  Koristili smo calloc da bi nam left i right odmah dobili vrendost NULL (0).
    new->data = data;
    new->left=NULL;
    new->right=NULL;
    return new;
}

Node *insertNodeR(Node *root, int data)                         //  Dodavanje cvora u stablo (rekurzivno).
{
    if(root == NULL){                                           //  Ako je cvor prazan, dodajemo element.
        return createNode(data);                                //  Elemente uvek dodajemo kao listove.
    }
    if(data < root->data){                                      //  Ako je vrednost elementa koji dodajemo manja od trenutno razmatranog cvora,
        root->left = insertNodeR(root->left, data);             //  rekurzivno dodajemo taj element u levo podstablo trenutno razmatranog cvora.
    }else{                                                      //  U suprotnom, rekurzivno ga dodajemo u desno podstablo trenutno razmatranog cvora.
        root->right = insertNodeR(root->right, data);
    }
    return root;
}

void insertNodeDPR(Node **root, int data)                       //  Dodavanje cvora u stablo pomocu pokazivaca na pokazivac (rekurzivno).
{
    if(*root == NULL){
        *root = createNode(data);
        return;
    }
    if(data < (*root)->data){
        insertNodeDPR(&(*root)->left, data);
    }else{
        insertNodeDPR(&(*root)->right, data);
    }
}

Node *insertNodeI(Node *root, int data)                         //  Dodavanje cvora u stablo (iterativno).
{
    if(root == NULL){
        return createNode(data);
    }
    Node *parent = NULL;
    Node *curr = root;
    int left = 0;                                               //  Flag koji koristimo da bismo znali u kom podstablu se nalazimo (levom ili desnom).
    while(curr){
        parent = curr;
        if(data < curr->data){
            left = 1;
            curr = curr->left;
        }else{
            left = 0;
            curr = curr->right;
        }
    }
    if(left){
        parent->left = createNode(data);
    }else{
        parent->right = createNode(data);
    }
    return root;
}

void insertNodeDPI(Node **root, int data)                       //  Dodavanje cvora u stablo pomocu pokazivaca na pokazivac (iterativno).
{
    if(*root == NULL){
        *root = createNode(data);
        return;
    }
    Node *parent = NULL;
    Node *curr = *root;
    int left = 0;
    while(curr){
        parent = curr;
        if(data < curr->data){
            left = 1;
            curr = curr->left;
        }else{
            left = 0;
            curr = curr->right;
        }
    }
    if(left){
        parent->left = createNode(data);
    }else{
        parent->right = createNode(data);
    }
}

void printInorder(Node *root)                                   //  Imamo tri redosleda po kojima mozemo da ispisujemo elemente stabla
{                                                               //  (Inorder, Preorder, i Postorder).
    if(root == NULL){                                           //  Razlikuju se samo po sta se prvo ispisuje.
        return;
    }
    printInorder(root->left);
    printf("%d ", root->data);
    printInorder(root->right);
}

void printPreorder(Node *root)
{
    if(root == NULL){
        return;
    }
    printf("%d ", root->data);
    printInorder(root->left);
    printInorder(root->right);
}

void printPostorder(Node *root)
{
    if(root == NULL){
        return;
    }
    printInorder(root->left);
    printInorder(root->right);
    printf("%d ", root->data);
}

Node *findNodeR(Node *root, int data)                           //  Nalazimo element po vrednosti (rekurzivno).
{
    if(root == NULL){
        return NULL;
    }
    if(root->data == data){
        return root;
    }
    if(data < root->data){
        return findNodeR(root->left, data);
    }else{
        return findNodeR(root->right, data);
    }
}

Node *findNodeI(Node *root, int data)                           //  Nalazimo element po vrednosti (iterativno).
{
    while(root){
        if(root->data == data){
            return root;
        }
        if(data < root->data){
            root = root->left;
        }else{
            root = root->right;
        }
    }
    return NULL;
}

void deleteBST(Node *root)                                      //  Brisanje stabla.
{
    if(root == NULL){
        return;
    }
    deleteBST(root->left);
    deleteBST(root->right);
    printf("Removing %d\n", root->data);
    free(root);
}

void deleteDPBST(Node **root)                                   //  Brisanje stabla pomocu pokazivaca na pokazivac.
{
    if(*root == NULL){
        return;
    }
    deleteDPBST(&(*root)->left);
    deleteDPBST(&(*root)->right);
    printf("Removing %d\n", (*root)->data);
    free(*root);
    *root = NULL;
}

void insertLefovers(Node **destinationNode, Node *leftovers)    //  Funkcija za dodavanje elemenata koji su ostali da vise nakon brisanja nekog cvora u stablu.
{
    if(leftovers){                                              //  Ako imamo ostatak, dodajemo ga element po element.
        insertNodeDPR(destinationNode, leftovers->data);        //  Dodajemo prvo koren tog podstabla cije elemente dodajemo,
        insertLefovers(destinationNode, leftovers->left);       //  a zatim rekurzivno pozivamo funkciju za njegovo levo podstablo,
        insertLefovers(destinationNode, leftovers->right);      //  i desno podstablo.
        free(leftovers);                                        //  Kako uklonimo element, tako oslobadjamo memoriju (oslobadjamo
    }                                                           //  memoriju od najdubljeg elementa ka najplicem elementu u stablu).
}

void removeNode(Node **root, int data)                          //  Uklanjamo element iz stabla tako sto na njegovo mesto stavljamo
{                                                               //  njegovo levo podstablo, a zatim elemente iz njegovog desnog podstabla
    Node *parent = NULL;                                        //  dodajemo podstablo ciji je koren roditelj elementa kojeg smo uklonili.
    Node *curr = *root;
    int left = 0;
    while(curr){
        if(curr->data == data){                                 //  Pronasli smo cvor koji zelimo da uklonimo.
            if(parent){                                         //  Element koji uklanjamo nije koren stabla, nego unutrasnji cvor.
                if(left){                                       //  Ako je levo dete parent-a element koji uklanjamo.
                    parent->left = curr->left;
                }else{                                          //  Ako je desno dete parent-a element koji uklanjamo.
                    parent->right = curr->left;
                }
                insertLefovers(&parent, curr->right);
            }else{                                              //  Element koji uklanjamo je koren stabla.
                *root = curr->left;
                insertLefovers(root, curr->right);
            }
            free(curr);
            return;
        }else{                                                  //  Krecemo se kroz stablo sve dok ne dodjemo do trazenog elementa.
            parent = curr;
            if(data < curr->data){
                left = 1;
                curr = curr->left;
            }else{
                left = 0;
                curr = curr->right;
            }
        }
    }
}

int getMaxDepth(Node *root)                                     //  Funkcija koja odredjuje maksimalnu dubinu u stablu.
{
    if(root == NULL){                                           //  Ako je stablo prazno dubina je nula.
        return 0;
    }
    int leftDepth = getMaxDepth(root->left);                    //  Rekurzivno trazimo maksimalnu dubinu levog podstabla.
    int rightDepth = getMaxDepth(root->right);                  //  Rekurzivno trazimo maksimalnu dubinu desnog podstabla.
    int depth = leftDepth > rightDepth ? leftDepth : rightDepth;
    return ++depth;                                             //  Ukupna dubina stabla je za jedan veca od najvece dubine u podstablima.
}

int getWidth(Node *root, int level)                             //  Funkcija koja vraca sirinu stabla na odredjenoj dubini.
{
    if(root == NULL){                                           //  Ako je stablo prazno, njeogva sirina je 0.
        return 0;
    }
    if(level == 1){                                             //  Ako je dubina stabla 1, to znaci da se nalazimo u listu (dubina ide odozdo na gore,
        return 1;                                               //  listovi su na dubini 1, dok je koren stabla na maksimalnoj dubini).
    }else if(level > 1){
        return getWidth(root->left, level - 1) + getWidth(root->right, level - 1);      //  Ako nismo u listu, vracamo sabranu sirinu levog i desnog podstabla.
    }
}

int getMaxWidth(Node *root)                                     //  Funkcija koja vraca maksimalnu sirinu u celom binarnom stablu
{                                                               //  (maksimalan broj cvorova na istoj dubini).
    int maxWidth = 0;
    int width;
    int maxDepth = getMaxDepth(root);
    for(int i = 1; i <= maxDepth; i++){                         //  Trazimo sirinu za svaki nivo dubine, od 1 do maxDepth pomocu funkcije getWidth().
        width = getWidth(root, i);
        maxWidth = maxWidth > width ? maxWidth : width;         //  Ako je dobijena sirina veca od dotadasnje maksimalne, azuriramo maxWidth.
    }
    return maxWidth;
}

int main()
{
    Node *bst = NULL;
    int n;
    int data;

    printf("Unesite broj elemenata u stablu: ");
    scanf("%d", &n);

    printf("Unesite %d celih brojeva: ", n);
    for(int i = 0; i < n; i++){
        scanf("%d", &data);
        // bst = insertNodeR(bst, data);
        // bst = insertNodeI(bst, data);
        // insertNodeDPR(&bst, data);
        insertNodeDPI(&bst, data);
    }

    printf("Adresa na kojoj se nalazi stablo: %p\n", bst);

    printInorder(bst);
    // printPreorder(bst);
    // printPostorder(bst);
    printf("\n");

    printf("Maksimalna dubina stabla je %d.\n", getMaxDepth(bst));
    printf("Maksimalna sirina stabla je %d.\n", getMaxWidth(bst));

    printf("Unesite vrednost za element koji zelite da pronadjete: ");
    scanf("%d", &data);

    Node *temp = findNodeI(bst, data);
    // Node *temp = findNodeR(bst, data);

    if(temp){
        printf("Adresa na kojoj se nalazi broj %d je: %p\n", temp->data, temp);
    }else{
        printf("Trazena vrednost ne postoji u stablu.\n");
    }

    printf("Unesite broj elemenata koji zelite da uklonite: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++){
        printf("Unesite ceo broj: ");
        scanf("%d", &data);
        removeNode(&bst, data);
        printInorder(bst);
        printf("\n");
    }

    // deleteBST(bst);
    deleteDPBST(&bst);
    printf("Adresa na kojoj se nalazi stablo nakon brisanja: %p\n", bst);

    return 0;
}
