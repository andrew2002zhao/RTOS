/* The KCD Task Template File */

#include "../usr/usr_msg.h"
#include "common.h"
#include "../INC/rtx.h"


#define MSG_IN_BUF_SIZE 100
#define SIZE_OF_ALPHANUMERIC_CASE_SENSITIVE 62

#define COMMAND_SIZE 1
#define MSG_TO_SEND_BUF_SIZE 65

#define RESERVED_TID 161

#define ENTER_ASCII 13
#define DEL_ASCII 127
char msg_to_send_buf[MSG_TO_SEND_BUF_SIZE];
task_t key_map[SIZE_OF_ALPHANUMERIC_CASE_SENSITIVE];

//this converts all the ascii we need to the correct range
int ascii_to_key(char ascii) {
    if(ascii >= '0' && ascii <= '9') {
        // 0 - 9
        return ascii - 48; 
    } else if(ascii >= 'A' && ascii <= 'Z') {
        // 10 - 35
        return ascii - 65 + 10;
    } else if(ascii >= 'a' && ascii <= 'z') {
        // 36 - 61
        return ascii - 97 + 36;
    }
    return -1;
}

void kcd_task(void)
{
    // create a mailbox
    mbx_create(KCD_MBX_SIZE);
    //writting characters from mailbox to this buffer
    char msg_in_buf[MSG_IN_BUF_SIZE];

    //intializing the all the elements n the keymap to a tid so we dont have garbage values
    for(int i = 0; i < SIZE_OF_ALPHANUMERIC_CASE_SENSITIVE; i++) {
        key_map[i] = RESERVED_TID;
    }

    //size of the msg that we want to sent to a task
    int msg_to_send_size = 0;
    while(1) {
        //rcv a msg (will grab a header and the data)
        recv_msg(NULL, msg_in_buf, MSG_IN_BUF_SIZE);
        //grabbing the header from the buffer
        RTX_MSG_HDR header = *((RTX_MSG_HDR *) msg_in_buf);
        
        //if the msg is a KCD_REG we want to store who the symbol belongs to in your key_map
        if(header.type == KCD_REG) {
            //get the character from the buffer
            char c = *(msg_in_buf + 12);
            //convert it to a valid range using function
            int key = ascii_to_key(c);
            //store the tid of the sender in the key_map
            key_map[key] = header.sender_tid;
        }
        //KEY_IN TYPE
        else if(header.type == KEY_IN) {
            //getting the character we are currently on
            char c = *(msg_in_buf + 12);
            //if the character is enter that means the first character should be %
            if(c == ENTER_ASCII) {
                //if we dont 
                if(msg_to_send_buf[0] != '%') {
                    //not a command and error send
                    //Invalid Command
                    SER_PutChar(1, "Invalid Command \n\r");
                    //clear msg_to_send_buf
                    msg_to_send_size = 0;
                    continue;
                }
                //if the length of the msg is bigger than the size if our msg send buff then we just send the msg we have so far and reset the counter
                if(msg_to_send_size == MSG_TO_SEND_BUF_SIZE) {
                    //max size error send 
                    // Invalid Command
                    SER_PutChar(1, "Invalid Command \n\r");
                    //clear msg_to_send_buf
                    msg_to_send_size = 0;
                    continue;
                }
                    
                //if the key is not in range we return an error
                int key = ascii_to_key(msg_to_send_buf[1]) ;
                if (key == -1) {
                    //if invalid key send 
                    //Command cannot be processed
                    SER_PutChar(1, "Command cannot be processed \n\r");
                    //clear msg_to_send_buf
                    msg_to_send_size = 0;
                    continue;

                } 
                //we have the key now, so we check if we have a tid associated to it
                task_t recv_tid = key_map[key];
                if(recv_tid == RESERVED_TID) {
                    //if nothing registered send
                    //Command cannot be processed
                    SER_PutChar(1, "Command cannot be processed \n\r");
                    //clear msg_to_send_buf
                    msg_to_send_size = 0;
                    continue;
                } 

                //check to see if the task still exists
                RTX_TASK_INFO rtx_task_info;
                tsk_get_info(recv_tid, &(rtx_task_info));
                //check if task is dormant
                if(rtx_task_info.state == DORMANT) {
                    //if dormant send
                    //Command cannot be processed
                    SER_PutChar(1, "Command cannot be processed \n\r");
                    //clear msg_to_send_buf
                    msg_to_send_size = 0;
                    continue;
                }
                //construct a msg to send over
                //allocating space of the header and the msg minus the size of the %
                char * msg_out_buf = (char *) mem_alloc(sizeof(RTX_MSG_HDR) + msg_to_send_size - COMMAND_SIZE);
                //interperting the first 12 bytes as the header
                RTX_MSG_HDR * msg_out_hdr = ((RTX_MSG_HDR*) msg_out_buf);
                //setting the metadata in the header
                msg_out_hdr -> length = sizeof(RTX_MSG_HDR) + msg_to_send_size - COMMAND_SIZE;
                msg_out_hdr -> type = KCD_CMD;
                //the msg was sent by the isr
                msg_out_hdr -> sender_tid = TID_KCD;

                //copy the whole string byte by byte 
                for(int i = 0; i < msg_to_send_size - COMMAND_SIZE; i++) {
                    //copy the string byte by byte
                    //starting at the after the buffer
                    (msg_out_buf + sizeof(RTX_MSG_HDR))[i] = (msg_to_send_buf + COMMAND_SIZE)[i];
                }
                
                send_msg(recv_tid, msg_out_buf);
                mem_dealloc(msg_out_buf);
                //clear msg_to_send_buf (start reading the next piece of data)
                msg_to_send_size = 0;
            }
            else{
                //deleting characters
                if(c == DEL_ASCII) {
                    msg_to_send_buf[msg_to_send_size] = ' ';
                    msg_to_send_size--;
                }
                //if we have space for more characters in our list we add them
                else if(msg_to_send_size != MSG_TO_SEND_BUF_SIZE) {
                    //more characters than we can hold
                    //do nothing
                    msg_to_send_buf[msg_to_send_size] = c;
                    msg_to_send_size++;
                } 
            }
        }
        //do nothing on other msg types

    }

}



/*

possible tests:

    1) reg a task then deallocate the task then allocate another task on the same tid
        - we can add a symbol field in the tcb

    2) write to a buffer of a dormant task


*/