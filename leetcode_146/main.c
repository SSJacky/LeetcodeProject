//
//  main.c
//  leetcode_21
//
//  Created by 夏蜃詰 on 2022/9/13.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
//Definition for singly-linked list.
typedef struct node_t{
    int val;
    int valid;
    struct node_t *next;
    struct node_t *prev;
} LRUCache;

struct lru_t {
    int size;
    int capacity;
    LRUCache *head;
    LRUCache *tail;
    LRUCache **hash_table;
} m_lru;

LRUCache* lRUCacheCreate(int capacity) {
    uint32_t index = 1;
    
    LRUCache *head = (LRUCache *)malloc(sizeof(LRUCache)*(capacity));
    m_lru.hash_table = (LRUCache **)malloc(sizeof(LRUCache *)*(capacity));
    LRUCache **current = &head;
    m_lru.head = head;
    m_lru.capacity = capacity;
    
    (*current)->prev = NULL;
    
    while(index < capacity){
        (*current)->val = 0;
        (*current)->valid = 0;
        (*current)->next = *current+1;
        (*current+1)->prev = *current;
        current = &((*current)->next);
        index++;
    }

    (*current)->next = NULL;
    m_lru.tail = *current;
    m_lru.size = 0;
    
    return head;
}

int lRUCacheGet(LRUCache* obj, int key) {
    if(m_lru.hash_table[key]->valid!=true) {
        return 0;
    }
    else if(m_lru.hash_table[key]->next == m_lru.tail){
        return 1;
    }
    else{
        /*remove get node*/
        LRUCache **indir = &obj;
        LRUCache *current = (m_lru.hash_table[key]->prev);
        while(*indir != m_lru.hash_table[key]){
            indir=&((*indir)->next);
        }
        current = *indir;
        *indir = m_lru.hash_table[key]->next;
        
        (*indir)->prev = current->prev;
        /*insert node to tail*/
        m_lru.head = obj;
        m_lru.tail->next = m_lru.hash_table[key];
        m_lru.hash_table[key]->prev = m_lru.tail;
        m_lru.tail =m_lru.hash_table[key];
        
        
        return 1;
    }
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    LRUCache **indir = &obj;
    LRUCache *current = obj;

    if(m_lru.tail->valid==1){
        
        indir=&((*indir)->next);
        
        current = (*indir)->next;
        m_lru.head->next=current;
        current->prev = m_lru.head;
        
        (*indir)->prev = m_lru.tail->prev;
        m_lru.tail->prev->next=(*indir);
        
        (*indir)->next = m_lru.tail;
        
        m_lru.hash_table[key] = (*indir);
        (*indir)->val = value;
        
        return;
        
    }
    while((*indir)->valid == 1){
        indir = &(*indir)->next;
    }
    
    (*indir)->val=value;
    (*indir)->valid=1;
    m_lru.hash_table[key] = (*indir);
    
}

void lRUCacheFree(LRUCache* obj) {
    free(obj);
}

void print_all(LRUCache* list) {
    printf("List : ");
    LRUCache *q = list;
    if(q==NULL)return;
    printf("head = %p\n", q);
    printf("next = %p\n",q->next);
    printf("prev = %p\n",q->prev);
    printf("val = %d\n",q->val);
    printf("valid = %d\n",q->valid);
    q = q->next;
    
    while (q != NULL) {
        printf("node = %p\n", q);
        printf("next = %p\n",q->next);
        printf("prev = %p\n",q->prev);
        printf("val = %d\n",q->val);
        printf("valid = %d\n",q->valid);
        q = q->next;
    }
    
    printf("N\n");
}

void print_hash(LRUCache** list,int capacity) {
    printf("hash : \n");
    for(int i = 0;i<capacity;i++){
        if(list[i]==NULL){
            printf(" N \n");
        }
        else {
            LRUCache *q = list[i];
            printf("head = %p\n", q);
            printf("next = %p\n",q->next);
            printf("prev = %p\n",q->prev);
            printf("val = %d\n",q->val);
            printf("valid = %d\n",q->valid);
        }
    }
    
}

int main() {
    printf("first test\n");
 
    LRUCache* head_cache=lRUCacheCreate(3);
    print_all(head_cache);
    
    
    lRUCachePut(head_cache,3,3);
    print_all(head_cache);
    lRUCachePut(head_cache,2,2);
    print_all(head_cache);
    lRUCachePut(head_cache,1,1);
    print_all(head_cache);

    lRUCacheGet(head_cache,3);
    printf("all tests passed!\n\n");
    print_all(head_cache);
    //print_all(m_lru.hash_table[3]);
 
    return 0;
}

