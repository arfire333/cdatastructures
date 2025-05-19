#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define KD_MAX_DIMENSION 2 

typedef int64_t kd_key_t[KD_MAX_DIMENSION];

typedef struct kd_node_t kd_node_t;
struct kd_node_t {
    kd_node_t *l;
    kd_node_t *r;
    kd_key_t key;
    double value;
};

kd_node_t *kd_insert(kd_node_t *root, kd_key_t *key, double value){
    if( root==NULL ){
        root=(kd_node_t*)malloc(sizeof(kd_node_t));
        if(root){
            memcpy(root->key,key,sizeof(int64_t)*KD_MAX_DIMENSION);
            root->value=value; 
            root->l=NULL;
            root->r=NULL;
        }
        return root;
    }
    
    return NULL;
};

kd_node_t *kd_delete(kd_node_t *root, kd_key_t *key){
    printf("Not implemented\n");
    return NULL;
};

void kd_destroy(kd_node_t *root){
    printf("Not implemented\n");
};

void print_tree(kd_node_t *root){
    printf("Not implemented\n");
}

#ifndef EXCLUDE_MAIN
int main(int argc, char *argv[]){
    printf("Prepare to kdtree!\n");    
    return 0;
}
#endif