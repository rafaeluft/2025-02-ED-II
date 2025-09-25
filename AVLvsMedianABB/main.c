#include<stdio.h>
#include "BinTree.h"
#include "AVLTree.h"
#include<stdlib.h>

void printTree(TNo* root){
  printf("Preorder: ");
  BinTree_preorder(root);
  printf("InOrder: ");
  BinTree_inorder(root);
  putchar('\n');
}
int comp(const void *p1, const void *p2){
  const int *pp1 = p1;
  const int *pp2 = p2;
  return *pp1 - *pp2;
}

TNo* buildMtree(int V[], int i, int j){
  TNo *root = NULL;
  if(i<=j){
    int middle = (i+j)/2;
    root = createNFill(V[middle]);
    root->left = buildMtree(V, i, middle-1);
    root->right = buildMtree(V, middle+1, j);
  }
  return root;
}

//Adaptado de https://www.geeksforgeeks.org/check-whether-the-two-binary-search-trees-are-identical-or-not/
int isIdentical(TNo* root1, TNo* root2)
{
    // Check if both the trees are empty
    if (root1 == NULL && root2 == NULL)
        return 1;
    // If any one of the tree is non-empty
    // and other is empty, return false
    //If one of the trees are empty then return 0;
    else if (root1 == NULL ^ root2 == NULL)
      return 0;        
    else { // Check if current data of both trees equal
        // and recursively check for left and right subtrees
        if (root1->key == root2->key && isIdentical(root1->left, root2->left)
            && isIdentical(root1->right, root2->right))
            return 1;
        else
            return 0;
    }
}

int main(){
  int cases;
  scanf("%d\n", &cases);
  while(cases-->0){
    int size;
    scanf("%d\n", &size);
    TNo *avlTree = NULL, *mTree = NULL;
    char h;
    int V[size];
    for(int i=0; i<size; i++){
      scanf("%d", &V[i]);
      AVL_insert(V[i], &avlTree, &h);
    }
    qsort(V, size, sizeof(int), comp);
    mTree = buildMtree(V, 0, size-1);
    //printTree(avlTree);
    //printTree(mTree);
    printf("%d\n", isIdentical(avlTree, mTree));
  }
  return 0;
}