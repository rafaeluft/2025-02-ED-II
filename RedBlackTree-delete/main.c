#include "RBTree.h"
#include<stdio.h>
#include <stdlib.h>
//#include "RBTreeToLatex.h"


void printTree(RBTree *T){
  printf("PRE: ");
  RBTree_preorder(T->root, T->nil);
  printf("\nInORDER: ");
  RBTree_inorder(T->root, T->nil);
  printf("\nPos: ");
  RBTree_posorder(T->root, T->nil);
  putchar('\n');
}
//Uso: ./a.out >latex-template/tree.tex
int main(int argc, char *argv[]){
  
  RBTree *T = RBTree_create();
  char op; int operando;
  do{
    scanf("%c %d\n", &op, &operando);
    switch (op)
    {
    case 'q': puts("Bye"); 
      break;
    case 'i': RBTree_insert(T, operando);
     break;
    case 'p': BinTree_Terminal(T->root, "", T->nil); 
      break;
    case 'r': 
      printf("Tentando remover o %d \n", operando);
      if(RBTree_delete(T, operando))
        printf("Sucesso ao remover o %d\n", operando);
      else
        printf("Ocorreu um erro ao tentar remover %d\n", operando);
      break;
    default:
      puts("Operações suportadas: p 0, i 3, r 4, q 0");
      break;
    }
  }while(op != 'q');
  //RBTree_print(T);
  return 0;
}
