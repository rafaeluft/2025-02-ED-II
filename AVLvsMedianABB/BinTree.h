#ifndef BINTREE_H
#define BINTREE_H

typedef struct no{
  struct no *left, *right, *p;
  int key, bal;
} TNo;

typedef struct{
  TNo* root;
} BinTree;

TNo* createNFill(int);
BinTree* BinTree_create();
int BinTree_insert_r(TNo** root, TNo*);
int BinTree_insert(BinTree*, TNo*);

TNo* BinTree_search(BinTree*, int);
int BinTree_delete(BinTree*, int);
//Utils
//Receives a non null node;
TNo* BinTree_max(TNo*);
TNo* BinTree_min(TNo*);
TNo* BinTree_sucessor(TNo*);

//Funções de impressao
void BinTree_preorder(TNo*);
void BinTree_posorder(TNo*);
void BinTree_inorder(TNo*);

#endif