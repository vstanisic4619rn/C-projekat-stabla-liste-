#include <stdio.h>

typedef struct Tree{
    int index; /// index studenta
    int value; /// novac studenta
    struct Tree* left;
    struct Tree* right;
}Tree;

typedef struct Lista{
    int index;
    int total_value;
    struct Lista* next;
}Lista;

Lista* new_list(int index, int total_value){
    Lista* lista = (Lista*)malloc(sizeof(Lista));
    lista->index = index;
    lista->total_value = total_value;
    lista->next = NULL;
    return lista;
}

Tree* make_new(int index, int value){
    Tree* tree = (Tree*)malloc(sizeof(Tree));
    tree->index = index;
    tree->value = value;
    tree->left = NULL;
    tree->right = NULL;
    return tree;
}

Tree* insert_node_i(Tree* root, Tree* to_add){
    if(root == NULL){
        return to_add;
    }
    Tree* root_copy = root;
    Tree* parent = NULL;
    int dir = 0; /// 0 - left, 1 - right
    while(root_copy){
        parent = root_copy;
        if(to_add->value < root_copy->value){
            dir = 1;
            root_copy = root_copy->left;
        }
        else{
            dir = 0;
            root_copy = root_copy->right;
        }
    }
    if(dir == 0){
        parent->left = to_add;
    }
    else{
        parent->right = to_add;
    }

    return root;
}

Tree* insert_node_r(Tree* root, Tree* to_add){
    if(root == NULL)
        return to_add;
    if(to_add->value < root->value){
        root->left = insert_node_r(root->left, to_add);
    }
    else{
        root->right = insert_node_r(root->right, to_add);
    }

    return root;
}

void preorder(Tree* root){
    if(root == NULL)
        return;
    printf("%d %d\n", root->index, root->value);
    preorder(root->left);
    preorder(root->right);
}

void inorder(Tree* root){
    if(root == NULL)
        return;
    inorder(root->right);
    printf("%d %d\n", root->index, root->value);
    inorder(root->left);
}

void postorder(Tree* root){
    if(root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    printf("%d %d\n", root->index, root->value);
}

void delete_bst(Tree* root){
    if(root == NULL)
        return;
    delete_bst(root->left);
    delete_bst(root->right);
    free(root);
}

/// print lower<=index<=upper
void print_case(Tree* root, int lower, int upper){
    if(root == NULL)
        return;
    /// char* podstring;
    /// root->ime;
    /// strstr(root->ime, podstring) == NULL -> ne nalazi
    ///  *
    /// petar
    /// eta
    ///
    if(root->index >= lower && root->index <= upper){
        printf("$ %d %d\n", root->index, root->value);
    }
    print_case(root->left, lower, upper);
    print_case(root->right, lower, upper);
}

Lista* insert_in_lista(Lista* head, int index, int value){
    if(head == NULL)
        return new_list(index, value);

    Lista* tmp = head;
    while(tmp){
        if(tmp->index == index){
            tmp->total_value += value;
            return head;
        }
        tmp = tmp->next;
    }
    Lista* new_el = new_list(index, value);
    new_el->next = head;
    return new_el;

}

Tree* load_from_file(Lista** head){
    Tree* root = NULL;
    FILE* fp = fopen("stabla.txt", "r");
    char linija[255];
    while(fgets(linija, 255, fp)){

        if(linija[strlen(linija)-1] == '\n')
            linija[strlen(linija)-1] = 0;

        int index = atoi(strtok(linija, " "));
        int value = atoi(strtok(NULL, " "));
        /// dodaj index i value u listu Lista
        *head = insert_in_lista(*head, index, value);
        Tree* new_node = make_new(index, value);
        root = insert_node_r(root, new_node);
    }

    fclose(fp);
    return root;
}

void print_lista(Lista* head){
    if(head == NULL)
        return;
    printf("lista:  %d %d\n", head->index, head->total_value);
    print_lista(head->next);
}

int main(){
    Tree* root = NULL;
    Lista* head = NULL;
    root = load_from_file(&head);
    inorder(root);
    printf("Stampaj case:\n");
    print_case(root, 3, 5);
    print_lista(head);

    /*while(1){
        int broj;
        scanf("%d", &broj);
        switch(broj){
        case 1:
            printf("Unesite lower i upper bound\n");
            int lower, upper;
            scanf("%d %d", &lower, &upper);
            printf("%d i %d\n", lower, upper);
            break;
        }
    }*/
    return 0;
}
