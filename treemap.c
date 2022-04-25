#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap* map;
    map=(TreeMap*)malloc(sizeof(TreeMap));
    map->current=NULL;
    map->root=NULL;
    map->lower_than = lower_than;
    return map;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
   Pair* aux=searchTreeMap(tree,key);
   TreeNode* new=createTreeNode(key,value);
   if(aux->key==new->pair){
       if(tree->lower_than(key,aux)==1){
           tree->current->left=new;
           new->parent=tree->current;
           tree->current=new;
       }else{
           tree->current->right=new;
           new->parent=tree->current;
           tree->current=new;           
       }
   }
   
}

TreeNode * minimum(TreeNode * x){
    TreeNode* aux=x;
    while(aux!=NULL){
        if(aux->left==NULL){
            return aux;
        }
        aux=aux->left;
    }
    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    TreeNode* aux= tree->root;
    while(aux!=NULL){
        tree->current=aux;//guarda el ultimo nodo valido
        if(tree->lower_than (key,aux->pair->key)==1){
            aux=aux->left;
        }else if(tree->lower_than (aux->pair->key,key)==1){
            aux=aux->right;
        }else{
            tree->current=aux;
            return aux->pair;
        }
    }    
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    TreeNode* first=minimum(tree->root);
    tree->current=first;
    return first->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
    TreeNode*next;
    if( tree->current->right!=NULL){
        next=tree->current->right;
        tree->current=next;
        //return next->pair;
    }
    if( tree->current->left!=NULL){
        next=tree->current->left;
        tree->current=next;
        //return next->pair;
    }    
    return next->pair;
}
