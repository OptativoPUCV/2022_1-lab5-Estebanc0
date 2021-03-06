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
    tree->root->left=NULL;

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
    TreeNode* aux=tree->root;
    TreeNode* var=NULL;
    while(1){
        if(tree->lower_than(aux->pair->key,key)==1){
            if(aux->right==NULL){break;}
            aux=aux->right;
            continue;
        }
        if(tree->lower_than(aux->pair->key,key)==0){
            if(aux->left==NULL){break;}
            aux=aux->left;
            var=aux->parent;
            continue;            
        }

    }
    if(tree->lower_than(aux->pair->key,key)==1 && var!=NULL){
        tree->current=aux;
        return var->pair;
    }
    if(var==NULL){return NULL;}
    tree->current=aux;
    return aux->pair;
}

Pair * firstTreeMap(TreeMap * tree) {
    TreeNode* first=minimum(tree->root);
    tree->current=first;
    return first->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
    TreeNode*next;
    if( tree->current->right!=NULL){
        next=minimum(tree->current->right);
        tree->current=next;
        return next->pair;
    }
    TreeNode* aux=tree->current->parent;
    while(aux!=NULL){
        if(tree->lower_than(tree->current->pair->key,aux->pair->key)==1){
            tree->current=aux;
            return aux->pair;
        }
        else{
            aux=aux->parent;
        }
    } 
    return NULL;
}
