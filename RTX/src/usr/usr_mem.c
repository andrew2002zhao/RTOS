//macros used for allocate
#define ERROR -1
#define NO_PARTITION 0
#define PARTITION 1

//macro for the size of the m_node header
#define HEADER_SIZE 16
#define BYTE_ALIGN 8

//macros used for m_node states
#define NON_SENTINEL 0
#define FREE_NODE 0
#define TAKEN_NODE 1

//macros used for dealloc errors
#define SENTINEL_FREE_ERROR -2
#define ALREADY_FREE_ERROR -3

//macros used for coalesce
#define TAKEN_BLOCK -1
#define FIRST_FREE_BLOCK 0
#define COALESCED_FREE_BLOCK 1
#define HEAD_SENTINEL_CONTROL_BITS 2
#define TAIL_SENTINEL_CONTROL_BITS 4

#define MIN_NODES_TO_INIT 3


#define FREE_NODE 0
#define TAKEN_NODE 1

#define TRUE 1
#define FALSE 0

#define SIZE_OF_ZERO 0

#define KERNAL_OWNED_STACK 500;

#include "usr_mem.h"
#include "printf.h"

// Global Variables
int fragments;
int initialized;
m_node * head_sentinel;
m_node * tail_sentinel;

unsigned int head_sentinel_addy;
unsigned int tail_sentinel_addy;


int usr_k_mem_init(void) {
     unsigned int end_addr = (unsigned int) &Image$$ZI_DATA$$ZI$$Limit;

    //8 byte aligning our end_addr and RAM_END
	 int remainder = end_addr % BYTE_ALIGN;
	 if(remainder != 0) end_addr += BYTE_ALIGN - remainder;

     unsigned int real_end = RAM_END;
     remainder = real_end % BYTE_ALIGN;
     if(remainder != 0) real_end += BYTE_ALIGN - remainder;

    /* calculating total heap space */
    if ( real_end - end_addr < (MIN_NODES_TO_INIT*sizeof(m_node)) ){
        initialized = FALSE;
        return RTX_ERR;
    }

    /* Created the head and Tail Sentinal Nodes*/
    head_sentinel = (void *)end_addr;
    head_sentinel_addy = (int)head_sentinel;
    tail_sentinel = (void *)(real_end-sizeof(m_node));
    tail_sentinel_addy = (int)tail_sentinel;

    init_node(
        head_sentinel,
        HEAD_SENTINEL_CONTROL_BITS,
        TAKEN_NODE,
        NULL,
        SIZE_OF_ZERO
    );
    init_node(
        tail_sentinel,
        TAIL_SENTINEL_CONTROL_BITS,
        TAKEN_NODE,
        NULL,
        SIZE_OF_ZERO
    );

    /* Create big ass free node*/
    m_node * big_ahh_node = (void *) (end_addr + sizeof(m_node));
    int big_ahh_size = real_end - end_addr - MIN_NODES_TO_INIT*sizeof(m_node);
    init_node(
        big_ahh_node,
        NON_SENTINEL,
        FREE_NODE,
        tail_sentinel,
        big_ahh_size
    );

    /* Setting Next of Nodes*/
    head_sentinel->p_next = big_ahh_node;
    head_sentinel -> p_next = big_ahh_node;
    // set_node_p_next(head_sentinel,big_ahh_node);
    // printf("HEAD: %x\n", head_sentinel);
    // printf("TAIL: %x\n", tail_sentinel);

    initialized  = TRUE;
    return RTX_OK;
}


void * usr_k_mem_alloc(size_t requested_size) {
    //final version lab1
    //rounding our requested_size to 8 byte aligned
	if(requested_size <= 0){
		return NULL;
	}
	 int remainder = requested_size % BYTE_ALIGN;
	 if(remainder != 0) requested_size += BYTE_ALIGN - remainder;
    if(!initialized){
        return NULL; // This should never happen
    }

    //start at the head, and its current prev is null
    m_node * temp_ptr = head_sentinel;
    m_node * prev = NULL;

    while ((int)temp_ptr != (int)tail_sentinel) {
    	//tmp is not head ptr so we check to see if we can allocate the node 
        if((int)temp_ptr != (int)head_sentinel){

            //we are finally at a free node which is big enough to hold our data
            if(temp_ptr -> size >= requested_size) {
                //address of the data
                return allocate_node(temp_ptr, prev, requested_size);
            }
            //we have a free node but its size is to small so we move on
           
        }
        //updating the prev and temp_ptr 
        prev = temp_ptr;
        temp_ptr = temp_ptr -> p_next;
    }
    //could not find a spot for the data
    return NULL;
}

void * allocate_node(m_node * memory_node, m_node * prev, size_t requested_size) {
    //here we are checking if we do partition we have enough space for the new node 
    if(memory_node->size < requested_size + HEADER_SIZE){
        // return NO_PARTITION;
        //we dont want our block to be in the free linked list anymore
        prev -> p_next = memory_node -> p_next;
        //settting taken node next to null because we are not tracking the taken nodes anymore
        memory_node -> p_next = NULL;
        
        //just returning the address of the data ---- PTR MATH

        //set ownership
        memory_node->tid = gp_current_task->tid;
        // printf("ALOCATE NODE ADDRESS %d\n", (int) memory_node + HEADER_SIZE );
        return (void *)( (int) memory_node + HEADER_SIZE);
    }
    //THE NODE WE FOUND IS BIGGER THAN WHAT WE NEED SO WE NEED TO PARTITION THE NODE
    else{
        //address of the new partitioned node (gonna hold your data)
        m_node * new_free_node = (m_node*)((int)(memory_node) + HEADER_SIZE + ((int)requested_size));
        //this is how big our new node should be (will be the free node)
        int current_size = memory_node->size - (HEADER_SIZE + requested_size); 
        new_free_node -> size = current_size;
//        new_free_node -> control = 0;
        //grafting nodes
        prev->p_next = new_free_node;
        new_free_node->p_next = memory_node -> p_next;
        //this is holding the data
        memory_node -> p_next = NULL;
        memory_node->size = requested_size;
        //the address of the data

        //set ownership
        memory_node->tid = gp_current_task->tid;
//        printf("ALOCATE NODE ADDRESS %d\n", (int) memory_node + HEADER_SIZE );
        return (void *)( (int) memory_node + HEADER_SIZE);
    }

}

int usr_k_mem_dealloc(m_node * address_to_free) {
    //check to make sure we are not trying to free the head to tail and also that your memory is initialized
    if(!initialized){
        return RTX_ERR;
    }
    //not a valid address
    if(address_to_free == NULL) {
        return RTX_ERR;
    }
    //calculating the actual address to free. we get pointer to data but we want the start of the header
    address_to_free = (m_node *)((int)(address_to_free) - HEADER_SIZE);
    //we should never go into this because we dont want to fee our sentinal 
    if((int)address_to_free == head_sentinel_addy || (int)address_to_free == tail_sentinel_addy) {
    	// printf("TRYING TO FREE SENTINEL \n");
        return RTX_ERR;
    }


    // Test the ownership for block of memory, return err if not owned
//    if (address_to_free->tid != gp_current_task->tid){
//    	return RTX_ERR;
//    }

	// DeMorgans Theorem
    if ( (address_to_free->tid != gp_current_task->tid) && (address_to_free->tid != 500) )  {
		return RTX_ERR;
	}


    //initiate temp_ptr to head_sentinel (head at the beginning because coalescing as we go)
    m_node * temp_ptr = head_sentinel;
    // m_node * first_free = NULL; //(keep track of free block for coalescing)
    while((int)temp_ptr != (int)tail_sentinel){
        
        //double free case
        if(((int) address_to_free) == (int)temp_ptr){
        	// printf("TRYING TO DOUBLE FREE \n");
            return RTX_ERR;
        }
        if(((int)temp_ptr) < (int)address_to_free && (int)address_to_free < ((int) (temp_ptr->p_next))){
            ((m_node *)address_to_free) -> p_next = (m_node *) (temp_ptr -> p_next );
            temp_ptr -> p_next = ((m_node *) address_to_free);
            coalesce(temp_ptr, ((m_node *)address_to_free), (m_node *) (address_to_free -> p_next));
            return RTX_OK;
        }
        temp_ptr = temp_ptr -> p_next;
        
        
    }
    return RTX_ERR;
}

int usr_k_mem_count_extfrag(size_t size) {

    if(size == 0) return 0;

    int extFrag=0;
    m_node *tmp_node = head_sentinel->p_next;   // Starts at the first node after the head. As one always exists

    while((int)tmp_node != (int)tail_sentinel ){
        if(( tmp_node -> size + HEADER_SIZE < size )){
            extFrag++;
        }
        tmp_node = tmp_node->p_next;
    }

    return extFrag;
}

void coalesce(m_node * prev, m_node * current_node, m_node * next) {

    if((int)next != tail_sentinel_addy){
        //trying to see if we are near the next ptr
        if(((int)current_node) + HEADER_SIZE + current_node->size == ((int)next)){
            //grafting middle with right
            current_node -> p_next = next -> p_next;
            //the new big little ahhh node
            // set_node_size(current_node, get_node_size(current_node) + HEADER_SIZE + get_node_size(next));
            current_node ->size = current_node ->size + HEADER_SIZE +  next->size;
        }
    }
    if((int)prev!=head_sentinel_addy){
        if(((int)prev) + HEADER_SIZE + prev->size == ((int)current_node)){
            //grafting the prev with next
            prev -> p_next = current_node -> p_next;
            // set_node_size(prev, get_node_size(prev) + HEADER_SIZE + get_node_size(current_node));
            prev ->size = prev->size + HEADER_SIZE +  current_node->size;

        }
    }


}

//=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-*********************UNUSED FOR NOW **************************************-=-===-=-=-=-=-=-=-=-=-=-=-=-=-=-==-==-=
//-----------------------------------------------------------------------------------------------------
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=Helper Functions
int get_node_size(m_node * node) {
    return node -> size;
}
void set_node_size(m_node * node, int size){
    if(size < 0) return;
    if(node == NULL) return;
    node->size = size;
}

//Control Helper Functions
//------------------------------------------------getting ST bit functions-----------------------------------------------------

//int get_node_free(m_node * node){
//    //ex 101 & 001 = 101
//    return (node->control & 1) ^ 1;
//}
//int get_node_taken(m_node * node){
//    //ex 101 & 000 = 0
//    return node->control & 1;
//}
////-------------------------------------------------changing ST bit functions ----------------------------------------------------

//void set_node_free(m_node * node){
//    //101 & 110 = 0
//    node->control &= 6;
//}
//void set_node_taken(m_node * node){
//    //101 ^ 111 = 1
//    node->control |= 1;
//}
//------------------------------------------------sentinal node functions -----------------------------------------------------

int is_head_sentinel(m_node * node){
    return ((int)node == head_sentinel_addy);
}
int is_tail_sentinel(m_node * node){
	return ((int)node == tail_sentinel_addy);
}
//void set_node_sentinel_head(m_node * node){
//    node -> control |= 2;
//}
//void set_node_sentinel_tail(m_node * node){
//    node -> control |= 4;
//}
//-----------------------------------------------------setting and getting the next node ------------------------------------------------
m_node * get_node_p_next(m_node * node){
    return node->p_next;
}

void set_node_p_next(m_node * node, m_node * next){
    node->p_next = next;
}

//-----------------------------------------------------Init node ---------------------------------------------------------------
//pass the SE and ST as 3 digit numbers
int init_node(m_node * node_address, int SE, int ST, m_node * p_next, int size){

//    int local_tmp = 0;
//    node_address->control = local_tmp  | SE | ST;
    node_address->size = size;
    node_address->p_next = p_next;

}




