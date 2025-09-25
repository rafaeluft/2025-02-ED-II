#include <stdio.h>
#include <stdlib.h>
#include "BinTree.h"

TNo* createNFill(int key){
  TNo* novo = (TNo*) malloc(sizeof(TNo));
  if (novo){
    novo->left = NULL;
    novo->right = NULL;
    novo->p = NULL;
    novo->key = key;
    novo->bal = 0;
  }
  return novo;
}
BinTree* BinTree_create(){
  BinTree* novo = (BinTree*) malloc(sizeof(BinTree));
  if (novo){
    novo->root = NULL;
  }
  return novo;
}

int BinTree_insert(BinTree* T, TNo* z){
  TNo *y = NULL, *x = T->root;
  while(x!=NULL){
    y = x;
    x = (z->key < x->key) ? x->left : x->right;
  }
  z->p = y;
  if (y == NULL)
    T->root = z;
  else if (z->key < y->key)
    y->left = z;
  else y->right = z; 
  //poderiamos impedir de inserir numeros repetidos por exemplo
  return 1;
}

int BinTree_insert_r(TNo** root, TNo* z){
  int key = z->key;
  if((*root)==NULL){
    *root = z;
    return 1;
  }
  //So remover que passara aceitar numeros repetidos
  if((*root)->key == key){
    //Nao aceita repetido
    return 0;
  }
  if(key < (*root)->key)
    return BinTree_insert_r(&(*root)->left, z);
  else
    return BinTree_insert_r(&(*root)->right, z);
}

TNo* BinTree_search(BinTree* T, int k){
  TNo* x = T->root;
  while (x!=NULL && k != x->key)
    x = (k > x->key) ? x->right : x->left;
  return x;
}
void Transplant(BinTree* T, TNo **u, TNo **v){
  if((*u)->p == NULL)
    T->root = *v;
  else if((*u)==(*u)->p->left)
    (*u)->p->left = *v;
  else (*u)->p->right = *v;
  if(*v!=NULL)
    (*v)->p = (*u)->p;
}

//Utils
TNo* BinTree_max(TNo* x){
  while(x->right)
    x = x->right;
  return x;
}
TNo* BinTree_min(TNo* xx){
  TNo* x = xx;
    while(x->left)
      x = x->left;
  return x;
}
TNo* BinTree_sucessor(TNo* x){
  if(x->right != NULL)
    return BinTree_min(x->right);
  TNo* y = x->p;
  while(y != NULL && x == y->right){
    x = y;
    y = y->p;
  }
}

void BinTree_preorder(TNo* root){
  if (root){
    printf("%d, ", root->key);
    BinTree_preorder(root->left);
    BinTree_preorder(root->right);
  }
}

void BinTree_posorder(TNo* root){
  if (root){
    BinTree_preorder(root->left);
    BinTree_preorder(root->right);
    printf("%d, ", root->key);  
  }
}

void BinTree_inorder(TNo* root){
  if (root){
    BinTree_inorder(root->left);
    printf("%d(%d), ", root->key, root->bal);  
    BinTree_inorder(root->right);
  }
}