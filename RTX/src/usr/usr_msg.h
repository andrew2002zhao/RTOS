#pragma once

#include "k_msg.h"
#include "k_task.h"
#include "usr_task.h"
#include "common.h"

typedef struct message{ //this is a size 12 array
    RTX_MSG_HDR msg_header;
    void * msg_body; //this is dynamically allocated in memory on the kernel
} MESSAGE;

typedef struct mailbox { //the kernel owns this memory and this is dynamically allocated
    int entries; //the number of entries in the mailbox
    int head;
    int tail;
    int circular_queue_size;
    int circular_queue_max_size;
    char * circular_queue; //a queue of pointers for the mailbox
    
} MAILBOX;

typedef struct blocked_linked_list {
    TCB* blocked_head_sentinel;
    TCB* blocked_tail_sentinel;
} BLOCKED_LINKED_LIST;

void usr_blocked_add(TCB* tcb_to_add);
void usr_blocked_remove(task_t tid, TCB* tcb_to_return);

int usr_mailbox_push(MAILBOX* mailbox , void * message_to_add);
int usr_mailbox_pop(MAILBOX* mailbox , void* message_to_fill, int length);


int usr_k_mbx_create(size_t size);
int usr_k_send_msg(task_t receiver_tid, const void* buf);
int usr_k_recv_msg(task_t *sender_tid, void* buf, size_t len);
