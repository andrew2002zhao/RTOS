#include "usr_task.h"
#include "printf.h"

#define HIGHEST_PRIORITY 0
#define LOWEST_PRIORITY 255

#define HEAD_SENTINEL 0
#define TAIL_SENTINEL 1

TCB * priority_scheduler[256];
TCB sentinel_head[256];
TCB sentinel_tail[256];

void usr_scheduler_init(TCB* null_task) {
    //initialize head and tail pointers for every priority level
    for(int priority_level = HIGHEST_PRIORITY; priority_level <= LOWEST_PRIORITY; priority_level++) {

        sentinel_head[priority_level].isSentinel = 1;
        sentinel_tail[priority_level].isSentinel = 1;
        sentinel_head[priority_level].next = &(sentinel_tail[priority_level]);

        priority_scheduler[priority_level] = &(sentinel_head[priority_level]);
    }
    //also add the null_task into priority level 255; 
    TCB* null_head = priority_scheduler[LOWEST_PRIORITY];
    TCB* null_tail = null_head -> next;
    null_head -> next = null_task;
    null_task -> next = null_tail;

}

TCB* usr_scheduler() {
    for(int current_priority = HIGHEST_PRIORITY; current_priority <= LOWEST_PRIORITY; current_priority++) {
        TCB* priority_head = priority_scheduler[current_priority];
        TCB* priority_head_next = priority_head -> next;
        if(priority_head_next -> isSentinel == 0) {
            //found a task 
            //it has higher priority than the current running task

            return priority_head_next;
            // if(current_priority > gp_current_task -> prio) {
            //     //schedule it to run and change the state of the old task
               
            //     //schedule the higher priority task
                
            //     // gp_current_task = priority_head_next;
            //     priority_head -> next = priority_head_next -> next;
            //     priority_head_next -> next = NULL;
                
            // }
            // else{
            //     //do nothing
            //     return NULL;
            // }
        }
    }
    return NULL;
}

void usr_scheduler_add(TCB* tcb) {
    int priority = tcb -> prio;
    TCB* priority_head = priority_scheduler[priority];
    TCB* temp = priority_head;
    tcb -> isSentinel = 0;
    while((temp -> next) -> isSentinel != 1) {
        temp = temp -> next;
    }
    tcb -> next = temp -> next;
    temp -> next = tcb;
}

void usr_scheduler_remove(TCB * tcb) {
    int priority = tcb -> prio;
    //find the list head in the linked list
    TCB * priority_head = priority_scheduler[priority];

    
    TCB * temp = priority_head;
    //start at the first node after the head
    while(temp -> next != tcb) {
        temp = temp -> next;
    }
    temp -> next = tcb -> next;
    tcb -> next = NULL;
}
