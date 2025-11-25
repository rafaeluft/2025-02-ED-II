#include "RBTree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define DEBUG_DELETE 1
#define BLACK "\033[30m"
#define RED "\033[31m"
#define RESET "\x1B[0m"

/**
* Primeira chamada: Root, "", TNo* T->nil 
*/
void BinTree_Terminal(TNo *, char *, TNo*);
void LEFT_ROTATE(RBTree* T, TNo* x);
void RIGHT_ROTATE(RBTree* T, TNo* x);
//------ Deletion algorithms ---- 
TNo* Tree_Minimum(RBTree* T, TNo* root){
  while(root->left != T->nil)
    root = root->left;
  return root;
}
void RB_Transplant(RBTree* T, TNo* u, TNo* v){
  if (u->p == T->nil)
    T->root = v;
  else 
    if(u == u->p->left)
      u->p->left = v;
    else
      u->p->right = v;
    v->p = u->p;
}

void RB_Delete_Fixup(RBTree* T, TNo *x) {
    TNo *w;
    TNo** root = &(T->root);
    if(DEBUG_DELETE)
      printf("Chamando o RB_Delete_Fixup(x=%d)", x->key);
    
    while (x != *root && x->color == black) {
        if (x == x->p->left) {  // x é filho esquerdo?
            w = x->p->right;  // w é o irmão de x
            if (w->color == red) {  // caso 1
              if(DEBUG_DELETE){
                printf("Caso 1: w(%d) é vermelho\n", w->key);
              }
                w->color = black;
                x->p->color = red;
                LEFT_ROTATE(T, x->p);
                w = x->p->right;
            }
            
            if (w->left->color == black && w->right->color == black) {  // caso 2
              if(DEBUG_DELETE){
                printf("Caso 2: os filhos de w(%d) sao black\n", w->key);
              }
                w->color = red;
                x = x->p;

            }
            else {
                if (w->right->color == black) {  // caso 3
                  if(DEBUG_DELETE){
                printf("Caso 3: o filho direito de w(%d) eh black\n", w->key);
              }
                    w->left->color = black;
                    w->color = red;
                    RIGHT_ROTATE(T, w);
                    w = x->p->right;
                }
                // caso 4
                if(DEBUG_DELETE){
                printf("Caso 4: w(%d)\n", w->key);
              }
                w->color = x->p->color;
                x->p->color = black;
                w->right->color = black;
                LEFT_ROTATE(T, x->p);
                x = *root;
            }
        }
        else {  // mesmo que acima, mas com "right" e "left" trocados
            w = x->p->left;
            
            if (w->color == red) {
              if(DEBUG_DELETE){
                printf("Caso 1: w(%d) é vermelho\n", w->key);
              }
                w->color = black;
                x->p->color = red;
                RIGHT_ROTATE(T, x->p);
                w = x->p->left;
            }
            
            if (w->right->color == black && w->left->color == black) {
              if(DEBUG_DELETE){
                printf("Caso 2: os filhos de w(%d) sao black\n", w->key);
              }  
              w->color = red;
                x = x->p;
            }
            else {
                if (w->left->color == black) {
                if(DEBUG_DELETE){
                  printf("Caso 3: o filho direito de w(%d) eh black\n", w->key);
              }

                    w->right->color = black;
                    w->color = red;
                    LEFT_ROTATE(T, w);
                    w = x->p->left;
                }
                if(DEBUG_DELETE){
                printf("Caso 4: w(%d)\n", w->key);
              }
                w->color = x->p->color;
                x->p->color = black;
                w->left->color = black;
                RIGHT_ROTATE(T, x->p);
                x = *root;
            }
        }
    }
    x->color = black;
}


bool RBTree_delete(RBTree* T, int key){
    TNo* z = T->root;
    while(z!=T->nil && z->key != key)
      z = (key < z->key) ? z->left : z->right;

    if (z == T->nil)
      return false;

    TNo *y = z;
    TNo *x;
    char y_original_color = y->color;
    
    if (z->left == T->nil) {
        x = z->right;
        RB_Transplant(T, z, z->right);
    }
    else if (z->right == T->nil) {
        x = z->left;
        RB_Transplant(T, z, z->left);
    }
    else {
        y = Tree_Minimum(T, z->right);  // y é o sucessor de z
        y_original_color = y->color;
        x = y->right;
        
        if (y != z->right) {  // y está mais abaixo na árvore?
            RB_Transplant(T, y, y->right);  // substitui y por seu filho direito
            y->right = z->right;  // filho direito de z se torna
            y->right->p = y;      // filho direito de y
        }
        else {
            if (x != T->nil) {
                x->p = y;  // caso x seja NULL
            }
        }
        
        RB_Transplant(T, z, y);  // substitui z por seu sucessor y
        y->left = z->left;           // e dá o filho esquerdo de z para y,
        y->left->p = y;              // que não tinha filho esquerdo
        y->color = z->color;
    }
    
    if (y_original_color == black) {  // se alguma violação red-black ocorreu,
        RB_Delete_Fixup(T, x);    // corrija-as
    }
    return true;
}

RBTree* RBTree_create(){
  RBTree *nova = malloc(sizeof(RBTree));
  if(nova){
    nova->nil = TNo_createNFill(0);
    nova->nil->color = black;
    nova->root = nova->nil;
  } return nova;
}

void LEFT_ROTATE(RBTree* T, TNo* x){
  TNo* y = x->right;
  x->right = y->left;
  if(y->left != T->nil)
    y->left->p = x;
  y->p = x->p;
  if (x->p == T->nil)
    T->root = y;
  else 
    if(x==x->p->left)
      x->p->left = y;
    else
      x->p->right = y;
    y->left = x;
    x->p = y;
}

void RIGHT_ROTATE(RBTree* T, TNo* y){
  TNo* x = y->left;
  y->left = x->right;
  if(x->right != T->nil)
    x->right->p = y;
  x->p = y->p;
  if (y->p == T->nil)
    T->root = x;
  else
    if (y==y->p->right)
      y->p->right = x;
    else 
      y->p->left = x;
  x->right = y;
  y->p = x;
}

void RB_insert_fixup(RBTree *T, TNo** z){
  TNo *y;
  while((*z)->p->color == red){
    if ((*z)->p == (*z)->p->p->left){
      y = (*z)->p->p->right;
      if (y->color == red){
        (*z)->p->color = black;
        y->color = black;
        (*z)->p->p->color = red;
        (*z) = (*z)->p->p;
      }else{
        if ((*z) == (*z)->p->right){
          (*z) = (*z)->p;
          LEFT_ROTATE(T,(*z));
        }
        (*z)->p->color = black;
        (*z)->p->p->color = red;
        RIGHT_ROTATE(T, (*z)->p->p);
      }
    }else{
      y = (*z)->p->p->left;
      if(y->color == red){
        (*z)->p->color = black;
        y->color = black;
        (*z)->p->p->color = red;
        (*z) = (*z)->p->p;
      }else{
        if((*z) == (*z)->p->left){
          (*z) = (*z)->p;
          RIGHT_ROTATE(T, (*z));
        }
        (*z)->p->color = black;
        (*z)->p->p->color = red;
        LEFT_ROTATE(T, (*z)->p->p);
      }
    }
  }
  T->root->color = black;
}

void RBTree_insert(RBTree* T, int info){
  TNo* z = TNo_createNFill(info);
  TNo* y = T->nil;
  TNo* x = T->root;
  while(x!=T->nil){
    y = x;
    x = (z->key < x->key) ? x->left : x->right;
  } 
  z->p = y;
  if(y==T->nil)
    T->root = z;
  else 
    if(z->key < y->key)
      y->left = z;
    else 
      y->right = z;
  z->left = T->nil;
  z->right = T->nil;
  z->color = red;
  RB_insert_fixup(T, &z);
}

/**
* Função do Luiz Felipe, aluno da turma 2023/01, 
  com algumas pequenas alterações.
*/

void PrintRbNode(TNo *x){
  if(x->color == red)
    printf(RED "%d\n", x->key);
  else
    printf(BLACK "%d\n", x->key);
}
void BinTree_Terminal(TNo *x, char *prefixo, TNo* nil){
  if(x==nil){
    printf("Impossível imprimir arvore");
    return;
  }
  char *N_prefixo="", *ponteiro, *segmento;
  if(x->p==nil)
    PrintRbNode(x);
  else{
    if(x->p->right!=nil && x->p->left!=nil && x->p->right!=x){
      ponteiro = "├── ";
      segmento = "│   ";
    }
    else{
      ponteiro = "└── ";
      segmento = "    ";
    }
    printf(RESET "%s%s", prefixo, ponteiro); 
    PrintRbNode(x);
    N_prefixo = malloc(strlen(prefixo)+strlen(segmento)+2);
    sprintf(N_prefixo, "%s%s", prefixo, segmento);
  }
  if(x->left!=nil)
    BinTree_Terminal(x->left, N_prefixo, nil); 
  if(x->right!= nil)
    BinTree_Terminal(x->right, N_prefixo, nil);
}

void RBTree_print(RBTree* T){
  if(T!=NULL){
    printf(RESET "");
    BinTree_Terminal(T->root, "", T->nil);
    printf(RESET "");
  }
}

void RBTree_preorder(TNo* root, TNo* nil){
  if(root!=nil){
    printf("%d%c,", root->key, root->color);
    RBTree_preorder(root->left, nil);
    RBTree_preorder(root->right, nil);
  }
}
void RBTree_inorder(TNo* root, TNo* nil){
  if(root!=nil){
    RBTree_inorder(root->left, nil);
    printf("%d%c,", root->key, root->color);
    RBTree_inorder(root->right, nil);
  }
}

void RBTree_posorder(TNo* root, TNo* nil){
  if(root!=nil){
    RBTree_posorder(root->left, nil);
    RBTree_posorder(root->right, nil);
    printf("%d%c,", root->key, root->color);
  }
}

TNo* TNo_createNFill(int key){
  TNo* novo = malloc(sizeof(TNo));
  if (novo){
    novo->key = key;
    novo->left = NULL;
    novo->right = NULL;
    novo->p = NULL;
    novo->bal = 0;
  }return novo;
}
