#include "SearchBinTree.h"
#include<stdio.h>
#include<stdlib.h>
TNo* TNo_createNFill(int key){
    TNo* novo = malloc(sizeof(TNo));
    if(novo){
        novo->key = key;
        novo->left = NULL;
        novo->right = NULL;
        novo->p = NULL;
    }
    return novo;
}
BinTree* BinTree_create(){
    BinTree* nova = malloc(sizeof(BinTree));
    if(nova)
        nova->root = NULL; //Estado da árvore vazia
    return nova;
}

bool BinTree_insert(BinTree* T, int key){
    TNo* z = TNo_createNFill(key);
    if(z == NULL)
        return false;
    TNo* y = NULL;
    TNo* x = T->root;
    while(x!=NULL){
        y = x;
        x = (z->key < x->key)? x->left:x->right;
    }
    z-> p = y;
    if (y==NULL)
        T->root = z;
    else
        if (z->key < y->key)
            y->left = z;
        else
            y->right = z;
    return true;
}
TNo* BinTree_search(TNo*, int);
void BinTree_pre(TNo* root){
    if(root){
        printf("%d, ", root->key);
        if(root->left)
            BinTree_pre(root->left);
        if(root->right)
            BinTree_pre(root->right);
    }
}
void BinTree_in(TNo* root){
    if(root){
        if(root->left)
            BinTree_in(root->left);
        printf("%d, ", root->key);
        if(root->right)
            BinTree_in(root->right);
    }

}
void BinTree_pos(TNo* root){
    if(root){
        if(root->left)
            BinTree_pos(root->left);
        if(root->right)
            BinTree_pos(root->right);
        printf("%d, ", root->key);
    }    
}
