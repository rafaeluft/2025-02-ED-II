#ifndef RBTREE_H
#define RBTREE_H
#include <stdbool.h>
#define red 'R'
#define black 'B'

typedef struct no {
  int key;
  struct no *p, *left, *right;
  int bal;
  char color;
}TNo;

typedef struct {
  TNo *root, 
  *nil;//Sentinela
}RBTree;

RBTree* RBTree_create();
void RBTree_insert(RBTree*, int);

bool RBTree_delete(RBTree*, int);
void RBTree_print(RBTree*);
/**
@param TNo* root node of a tree
@param TNo* pointer to nil node
*/
void RBTree_preorder(TNo*, TNo*);
void RBTree_inorder(TNo*, TNo*);
void RBTree_posorder(TNo*, TNo*);
TNo* TNo_createNFill(int key);

void BinTree_Terminal(TNo *, char *, TNo*);
#endif