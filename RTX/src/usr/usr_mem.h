#pragma once

#include "common.h"
#include "k_inc.h"


#define NO_ERROR 1
#define ERROR -1

#define HEADER_SIZE 16

#define NODE_ST
#define nullptr ((void*)0)


/* forward declaration */
struct memory_linked_list;

/* Memory Linked List */
typedef struct memory_linked_list {
//    int control;
    void * p_next; //(pointer is of type m_node)
    U32 size;
    U8 tid;
} m_node; //stands for memory node

/* Global Variables */
extern int fragments;

extern int initialized;

extern m_node * head_sentinel;
extern m_node * tail_sentinel;

/* Memory Linked List Helper Functions */
int init_node(m_node * node_address, int SE, int ST, m_node * p_next, int size);

int get_node_free(m_node * node); //returns taken status (0 free, 1 taken)
int get_node_taken(m_node * node);
void set_node_free(m_node * node); //set node free
void set_node_taken(m_node * node); //sets node taken

int is_head_sentinel(m_node * node); //returns if node is head sentinel
int is_tail_sentinel(m_node * node); //returns if node is tail sentinel
void set_node_sentinel_head(m_node * node); //changes passed node to head sentinel node
void set_node_sentinel_tail(m_node * node); //changes passed node to tail sentinel node

int get_node_size(m_node * node); //returns node size (bytes)
void set_node_size(m_node * node, int size); //sets node size (bytes)

m_node * get_node_p_next(m_node * node); //returns next node address
void set_node_p_next(m_node * node, m_node * next); //set next node address

/* User defined abstractions of defined methods */
int usr_k_mem_init(void); //init function, defined for us
void * usr_k_mem_alloc(size_t requested_size); //malloc, (bytes)
int usr_k_mem_dealloc(m_node * address_to_free); //free, address
int usr_k_mem_count_extfrag (size_t size);      // Returns number of extfrag



/* usr_k_mem_init Helper Functions */


/* usr_k_mem_alloc Helper Functions */
void * allocate_node(m_node * memory_node, m_node * prev, size_t requested_size);
// int partition_free_node(m_node * memory_node_to_partition, size_t requested_size);

/* usr_k_mem_dealloc Helper Functions */
void coalesce(m_node * prev, m_node * current_node, m_node * next);

/* usr_k_mem_count_extfrag Helper Functions */
int increment_fragments();
int decrement_fragments();

