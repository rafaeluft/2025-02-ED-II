#include<stdio.h>
#include "SearchBinTree.h"




void PrintTree(BinTree *T){
    BinTree_pre(T->root);
    putchar('\n');
    BinTree_in(T->root);
    putchar('\n');
}
int main(){
    int V[] = {10, 5, 2, 7, 20, 15, 25};
    BinTree* T = BinTree_create();
    for(int i=0; i< 7; i++)
        if(!BinTree_insert(T, V[i]))
            printf("Erro ao inserir o elemento V[%i] = %i\n", i, V[i]);
    PrintTree(T);
    int to_be_deleted;
    //int to_be_deleted = 25;
    //BinTree_delete(T, to_be_deleted);
    to_be_deleted = 10;
    if(BinTree_delete(T, to_be_deleted))
        printf("No %d deletado com sucesso!\n", to_be_deleted);
    else
        printf("Nao encontrei no com o rotulo %d\n", to_be_deleted);
    PrintTree(T);
    return 0;
}