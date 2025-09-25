#include "AVLTree.h"
#include "BinTree.h"
#include <stdio.h>
#include <stdlib.h>
#define DEBUG 0

static void AVL_CASE_1(TNo** pt, char *h){
  TNo* ptu = (*pt)->left;
  if(ptu->bal == -1){
    if(DEBUG) puts("Simple Right Rotation");
    (*pt)->left = ptu->right; ptu->right = *pt;
    (*pt)->bal = 0; *pt = ptu;
  }else{
    if(DEBUG) puts("Double Right Rotation");
    TNo* ptv = ptu->right;
    ptu->right = ptv->left;
    ptv->left = ptu;
    (*pt)->left = ptv->right; 
    ptv->right = *pt;
    if(ptv->bal == -1) (*pt)->bal = 1;
    else (*pt)->bal = 0;
    if(ptv->bal == 1) ptu->bal = -1;
    else ptu->bal = 0;
    (*pt) = ptv;
  } (*pt)->bal = 0; *h = 0;
}

static void AVL_CASE_2(TNo** pt, char *h){
  
  TNo *ptu = (*pt)->right;
  if (ptu->bal ==1){
    if(DEBUG) puts("Simple Left Rotation");
    (*pt)->right = ptu->left;
    ptu->left = *pt;
    (*pt)->bal = 0; *pt = ptu;
  }else{
    if(DEBUG) puts("Double Left Rotation");
    TNo* ptv = ptu->left;
    ptu->left = ptv->right;
    ptv->right = ptu;
    (*pt)->right = ptv->left;
    ptv->left = *pt;
    if (ptv->bal == 1) (*pt)->bal = -1;
    else (*pt)->bal = 0;
    if (ptv->bal == -1) ptu->bal = 1;
    else ptu->bal = 0;
    (*pt) = ptv;
  }(*pt)->bal = 0; *h = 0;
}

int AVL_insert(int x, TNo** pt, char *h){
  if(*pt==NULL)
  {
    (*pt) = createNFill(x);
    *h = 1;
  }else{
    if(x==(*pt)->key)
      return 0;
    if(x < (*pt)->key){
      AVL_insert(x, &(*pt)->left, h);
      if(*h)
        switch((*pt)->bal){
          case 1: (*pt)->bal = 0; *h=0; break;
          case 0: (*pt)->bal = -1; break;
          case -1: AVL_CASE_1(pt, h); break;
        }
    }else{
      AVL_insert(x, &(*pt)->right, h);
      if(*h)
        switch((*pt)->bal){
          case -1: (*pt)->bal = 0; *h=0; break;
          case 0: (*pt)->bal = 1; break;
          case 1: AVL_CASE_2(pt, h); break;
        }
    }
  }
}

int AVL_exclude(int x, TNo** pt, char *h){
  if(*pt==NULL)
  {
    *h = 0;
    return 0; //could not find
  }else{
    if(x==(*pt)->key){
      *h=1;
      if((*pt)->left == NULL && (*pt)->right==NULL)//Sou uma folha
      {
        free((*pt));
        (*pt) = NULL;
        return 1;
      }else{
        if( (*pt)->left==NULL ^ (*pt)->right==NULL) //Xor I have only one tree
        {
           (*pt) = ((*pt)->left == NULL) ? (*pt)->right: (*pt)->left;
          return 1;
        }else{ //I have the two subtrees
          //findMin and change infos
          TNo* subs = BinTree_min((*pt)->right);
          //Change the key
          (*pt)->key = subs->key;
          //keep seeking for the new node to be deleted
          *h=0;
          x = subs->key;
        }
      }
    }
    int res;
    if(x < (*pt)->key){
      res = AVL_exclude(x, &(*pt)->left, h);
      if(res && *h)
      //Note some changes here: This is the evaluation of inserting on the right in the Ins-AVL
        switch((*pt)->bal){
          case -1: (*pt)->bal = 0; break;//Now, this could lead to a change in the height of my parent, so h should not be false here
          case 0: (*pt)->bal = 1; *h=0; break; //Look this is the case where it does not change the height, because bal was 0 (it had both trees before)
          case 1: AVL_CASE_2(pt, h); *h=1; break;
        }
    }else{
      res = AVL_exclude(x, &(*pt)->right, h);
      if(res && *h)
        switch((*pt)->bal){
          case 1: (*pt)->bal = 0; break;
          case 0: (*pt)->bal = -1; *h=0; break;
          case -1: AVL_CASE_1(pt, h); *h=1; break;
        }
    }
    return res;
  }
}