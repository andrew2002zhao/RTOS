#include "usr_msg.h"
#include "../INC/rtx.h"
#include "printf.h"


#define START_OF_QUEUE_INDEX 0
#define DEFAULT_MAILBOX_QUEUE_SIZE 16

#define SIZE_OF_MAILBOX_OVERHEAD_IN_BYTES 24

TCB* blocked_head_sentinel;
TCB* blocked_tail_sentinel;


int usr_mailbox_push(MAILBOX* mailbox , void * message_to_add) {
	char * char_message_to_add = (char*) message_to_add;
    //theres enough space for this message
    int message_length = *((int*) message_to_add);

    if(mailbox -> circular_queue_size < message_length) {
        return RTX_ERR;
    }
    else{
        //copying data over byte by byte
        for(int i = 0; i < message_length; i++){
            mailbox -> circular_queue[mailbox -> tail] = char_message_to_add[i];
            mailbox -> tail += 1;
            if(( mailbox -> tail) >= (mailbox -> circular_queue_max_size) ) {
                mailbox -> tail = 0;//rolled over the max allocated memory of the array, start writing from the start
            } 

        }
        mailbox -> entries += 1;
		mailbox -> circular_queue_size -= message_length;


		return RTX_OK;

    }
}

int usr_mailbox_pop(MAILBOX* mailbox , void* message_to_fill, int length) {
	char * message_to_fill_char = (char*) message_to_fill;
	char * circular_queue_head_char = mailbox -> circular_queue;


	//cant straight up grab the length since the integer could be wrapped around the circular queue
	int head_temp = mailbox -> head;
	char message_length_char_array[4];
	//also insert backwards into the array for proper endianess
	for(int i = 0; i < 4; i++) {
		message_length_char_array[i] = circular_queue_head_char[head_temp];


		head_temp += 1;
        //rolling over
		if((head_temp) >= (mailbox -> circular_queue_max_size) ) {
			head_temp = 0;//rolled over the max allocated memory of the array, start writing from the start
		}
	}

    //first 4 bytes are the length so if we type cast to int we can just get it
	int message_length = *((int *) message_length_char_array);

    if(message_length > length) {
        //the buffer isn't large enough to store the message, remove the top message

        for(int i = 0; i < message_length; i++){

        	mailbox -> head += 1;

			if(( mailbox -> head) >= (mailbox -> circular_queue_max_size) ) {
				mailbox -> head = 0;//rolled over the max allocated memory of the array, start writing from the start
			}



        }
        mailbox -> circular_queue_size += message_length;
		mailbox -> entries -= 1;
		return RTX_ERR;

    }
    //move over the header first


    for(int i = 0; i < message_length; i++){

    	message_to_fill_char[i] = circular_queue_head_char[mailbox -> head];
    	mailbox -> head += 1;
        if(( mailbox -> head) >= (mailbox -> circular_queue_max_size) ) {
            mailbox -> head = 0;//rolled over the max allocated memory of the array, start writing from the start
        } 
    }
    mailbox -> entries -= 1;
    mailbox -> circular_queue_size += message_length;
    return RTX_OK;
    
}

int usr_k_mbx_create(size_t size) {
    //already has a mailbox or invalid size
    if(gp_current_task -> mailbox != NULL || size < MIN_MBX_SIZE) {
        return RTX_ERR;
    }
    
    //I know my current running task and assign it's mailbox pointer to mailbox
    MAILBOX * mailbox = (MAILBOX *) mem_alloc(size + SIZE_OF_MAILBOX_OVERHEAD_IN_BYTES); //this pointer is kernel owned though
    
    if(mailbox == NULL) {
        return RTX_ERR;
    }
    mailbox -> entries = 0;
    //head and tail sentinel get assigned to index 0
    mailbox -> head = START_OF_QUEUE_INDEX;
    mailbox -> tail = START_OF_QUEUE_INDEX;
    //the max index of the circular queue is the size of the allocated block minus the overhead
    mailbox -> circular_queue_size = size;
    mailbox -> circular_queue_max_size = size;
    mailbox -> circular_queue = (char *) (((char *) mailbox) +  SIZE_OF_MAILBOX_OVERHEAD_IN_BYTES);
    gp_current_task -> mailbox = mailbox;

    return RTX_OK;
}

void usr_blocked_add(TCB* tcb_to_add) {
   tcb_to_add -> next = blocked_head_sentinel -> next;
   blocked_head_sentinel -> next = tcb_to_add;
}
void usr_blocked_remove(task_t tid_to_find, TCB* tcb_to_return) {
   TCB * temp = blocked_head_sentinel;
   while(temp -> next -> tid != tid_to_find) {
       temp = temp -> next;
   }
   //temp -> next is the value we want to remove
   tcb_to_return = temp -> next;
   temp -> next = tcb_to_return -> next;

   tcb_to_return -> next = NULL;
}

int usr_k_send_msg(task_t receiver_tid, const void* buf) {
    if (buf == NULL) {
        return RTX_ERR;
    }


    MESSAGE* message = (MESSAGE*) buf; //
    //current task is the one sending the msg
    message -> msg_header.sender_tid = gp_current_task->tid;
    //if the msg is less than the min size we return error
    if(message -> msg_header.length < MIN_MSG_SIZE){
        return RTX_ERR;
    }

    //unblock message if it was blocked and preempt if necessary
    //search for the mailbox of a tcb
    for(int i = 0; i < MAX_TASKS; i++) {
        if(g_tcbs[i].tid == receiver_tid && g_tcbs[i].state != DORMANT) {
            //doesnt have a mailbox
            if( g_tcbs[i].mailbox == NULL){
                return RTX_ERR;
            }
            //we have found the mailbox of the receiver so send it over
            int status = usr_mailbox_push(g_tcbs[i].mailbox, message);//RTX_OK means enough space in receiver maibox, RTX_ERR means not enough space in receiver mailbox
            if (status == RTX_OK) { 

                if (g_tcbs[i].state == BLK_MSG) { //if the receiver was blocked then unblock and preempt if necessary
                    g_tcbs[i].state = READY; //unblock it
                    //remove it from the blocked queue
				    usr_blocked_remove(receiver_tid, &(g_tcbs[i]));

				   //add it to the scheduler, has shit to run
				    usr_scheduler_add(&(g_tcbs[i]));

                    k_tsk_run_new();
                }
            }
            return status;
            

            //if it was blocked
            
        }
    }
    return RTX_ERR; //mailbox does not exist
}

int usr_k_recv_msg(task_t *sender_tid, void* buf, size_t len) {
    //if no mailbox is present
    if(gp_current_task -> mailbox == NULL || buf == NULL) {
        return RTX_ERR;
    }
    //if empty then block and wait for a new message
    if( ((MAILBOX *) (gp_current_task -> mailbox)) -> entries == 0) {
        //remove from ready scheduler
        usr_scheduler_remove(gp_current_task);
        gp_current_task -> state = BLK_MSG;
        //add to blocked queue
        usr_blocked_add(gp_current_task);
        //run a new task in the mean time
        k_tsk_run_new();
    }
    int status = usr_mailbox_pop(gp_current_task -> mailbox, buf, len);

    if(sender_tid != NULL) {
        //type cast the buff to be able to extract the sender_tid
        RTX_MSG_HDR * rtx_msg_hdr = (RTX_MSG_HDR *) buf;
        *(sender_tid) = rtx_msg_hdr -> sender_tid;
    }

    return status; //RTX_OK on message returning properly, RTX_ERR on buffer not being large enough to store the message
}
