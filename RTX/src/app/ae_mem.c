/*
 ****************************************************************************
 *
 *                  UNIVERSITY OF WATERLOO ECE 350 RTOS LAB
 *
 *                     Copyright 2020-2021 Yiqing Huang
 *                          All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright
 *    notice and the following disclaimer.
 *
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
 *  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 ****************************************************************************
 */

/**************************************************************************//**
 * @file        ae_mem.c
 * @brief       memory lab auto-tester
 *
 * @version     V1.2021.01
 * @authors     Yiqing Huang
 * @date        2021 JAN
 *
 *****************************************************************************/

#include "rtx.h"
#include "Serial.h"
#include "printf.h"
#include "ae.h"
#include "../usr/usr_mem.h"

#if TEST == -1



int test_mem(void) {
	unsigned int start = timer_get_current_val(2);
	printf("NOTHING TO TEST.\r\n");
	unsigned int end = timer_get_current_val(2);

	// Clock counts down
	printf("This took %u us\r\n", start - end);

	printf("%x\r\n", (unsigned int) &Image$$ZI_DATA$$ZI$$Limit);
	return TRUE;
}

#endif
#if TEST == 1
//BOOL test_coalescing_free_regions_using_count_extfrag() {
//	void * p1 = k_mem_alloc(32);
//	void * p2 = k_mem_alloc(32);
//
//	unsigned int header_size = (unsigned int)p2 - (unsigned int)p1 - 32;
//
//	void * p3 = k_mem_alloc(32);
//	void * p4 = k_mem_alloc(32);
//	void * p5 = k_mem_alloc(32);
//	void * p6 = k_mem_alloc(32);
//	void * p7 = k_mem_alloc(32);
//	void * p8 = k_mem_alloc(32);
//	void * p9 = k_mem_alloc(32);
//
//	int size_33_plus_one_header = k_mem_count_extfrag(32 + header_size + 1);
//	int size_97_plus_three_header = k_mem_count_extfrag(96 + 3*header_size + 1);
//
//
//
//	if((size_33_plus_one_header!=0) || (size_97_plus_three_header!=0)) {
//		printf("test_coalescing_free_regions_using_count_extfrag: 1. Either mem_alloc or mem_count_extfrag has failed.\r\n");
//		k_mem_dealloc(p1);
//		k_mem_dealloc(p2);
//		k_mem_dealloc(p3);
//		k_mem_dealloc(p4);
//		k_mem_dealloc(p5);
//		k_mem_dealloc(p6);
//		k_mem_dealloc(p7);
//		k_mem_dealloc(p8);
//		k_mem_dealloc(p9);
//		return FALSE;
//	}
//
//	k_mem_dealloc(p2);
//	k_mem_dealloc(p4);
//	k_mem_dealloc(p6);
//
//	k_mem_dealloc(p8);
//
//	size_33_plus_one_header = k_mem_count_extfrag(32 + header_size + 1);
//	size_97_plus_three_header = k_mem_count_extfrag(96 + 3*header_size + 1);
//	printf("this is the val of size 33: %d\n",size_33_plus_one_header);
//	printf("this is the val of size 97: %d\n",size_97_plus_three_header);
//
//	if((size_33_plus_one_header!=4) || (size_97_plus_three_header!=4)) {
//		printf("test_coalescing_free_regions_using_count_extfrag: 2. Either mem_dealloc or coalescing has failed 1.\r\n");
//		k_mem_dealloc(p1);
//		k_mem_dealloc(p3);
//		k_mem_dealloc(p5);
//		k_mem_dealloc(p7);
//		k_mem_dealloc(p9);
//		return FALSE;
//	}
//
//
//	k_mem_dealloc(p3);
//	k_mem_dealloc(p7);
//	printf("EIMAAN3 WUZ HERE\n");
//
//	size_33_plus_one_header = k_mem_count_extfrag(32 + header_size + 1);
//	size_97_plus_three_header = k_mem_count_extfrag(96 + 3*header_size + 1);
//
//	if((size_33_plus_one_header!=0) || (size_97_plus_three_header!=2)) {
//		printf("test_coalescing_free_regions_using_count_extfrag: 3. Either mem_dealloc or coalescing has failed. 2\r\n");
//		k_mem_dealloc(p1);
//		k_mem_dealloc(p5);
//		k_mem_dealloc(p9);
//		return FALSE;
//	}
//
//	k_mem_dealloc(p1);
//	k_mem_dealloc(p5);
//	k_mem_dealloc(p9);
//
//	int size_289_plus_nine_header = k_mem_count_extfrag(288 + 9*header_size + 1);
//	printf("EIMAAN4 WUZ HERE\n");
//	if(size_289_plus_nine_header!=0) {
//		printf("test_coalescing_free_regions_using_count_extfrag: 4. Either mem_dealloc or coalescing has failed.\r\n");
//		return FALSE;
//	}
//
//	return TRUE;


#define N 10

#define CODE_MEM_INIT -1
#define CODE_MEM_ALLOC -2
#define CODE_MEM_DEALLOC -3
#define CODE_HEAP_LEAKAGE_1 -4
#define CODE_HEAP_LEAKAGE_2 -5
#define CODE_SUCCESS 0

int heap_leakage_test() {

	char *p_old[N], *p_new[N];

	// Step 1: Allocate memory
	for (int i = 0; i < N; i++) {
//		p_old[i] = (char*) k_mem_alloc(i * 256 + 255);

		// pointer to allocated memory should not be null
		// starting address of allocated memory should be four-byte aligned
		if (p_old[i] == NULL || ((unsigned int) p_old[0] & 3))
			return CODE_MEM_ALLOC;

		if (i > 0) {
			// adjacent allocated memory should not conflict
			if (p_old[i - 1] + 256 * i >= p_old[i])
				return CODE_MEM_ALLOC;
		}
	}

	// Step 2: De-allocate memory
	for (int i = 0; i < N; i++) {
		if (k_mem_dealloc(p_old[i]) == -1) {
			return CODE_MEM_DEALLOC;
		}
	}

	// Step 3: Memory Leakage
	for (int i = 0; i < N; i++) {
//		p_new[i] = (char*) k_mem_alloc((N - i) * 256 - 1);

		// pointer to allocated memory should not be null
		// starting address of allocated memory should be four-byte aligned
		if (p_new[i] == NULL || ((unsigned int) p_new[0] & 3))
			return CODE_HEAP_LEAKAGE_1;

		if (i > 0) {
			// adjacent allocated memory should not conflict
			if (p_new[i - 1] + 256 * (N - i + 1) >= p_new[i])
				return CODE_HEAP_LEAKAGE_1;
		}
	}

	// the total occupied area in the re-allocation
	// should be the same as in the initial allocation
	if ((p_old[0] != p_new[0])
			|| (p_old[N - 1] + N * 256 != p_new[N - 1] + 256)) {
		return CODE_HEAP_LEAKAGE_2;
	}

	for (int i = 0; i < N; i++) {
		k_mem_dealloc(p_new[i]);
	}

	return CODE_SUCCESS;
}




int test_mem(void) {

//	int test_coalescing_free_regions_result = test_coalescing_free_regions_using_count_extfrag();
	int test_result = heap_leakage_test();

	printf("TEST FINISHED RUNNING %d\n",  test_result);

	return test_result;
}
#endif

#if TEST == 99
BOOL test_99_real() {
	printf("TEST STARTEDDDDDD\n");
	// WRITE SHIT HEREEEE______________________________________
		void * p1 = k_mem_alloc(1);
		void * p2 = k_mem_alloc(32);
		void * p3 = k_mem_alloc(32);
		void * p4 = k_mem_alloc(1000);
		void * p5 = k_mem_alloc(32);
		void * p6 = k_mem_alloc(83);
		void * p7 = k_mem_alloc(32);
		void * p8 = k_mem_alloc(32);
		void * p9 = k_mem_alloc(199);



		//deallocing here
		printf("size of p1 is: %d \n", ((m_node * ) ((int) p4 - HEADER_SIZE)) -> size);
		k_mem_dealloc(p9);
		printf("size of p1 is: %d \n", ((m_node * ) ((int) p1 - HEADER_SIZE)) -> size);
		k_mem_dealloc(p8);
		printf("size of p1 is: %d \n", ((m_node * ) ((int) p1 - HEADER_SIZE)) -> size);
		k_mem_dealloc(p7);
		printf("size of p1 is: %d \n", ((m_node * ) ((int) p1 - HEADER_SIZE)) -> size);
		k_mem_dealloc(p6);
		printf("size of p1 is: %d \n", ((m_node * ) ((int) p1 - HEADER_SIZE)) -> size);
		k_mem_dealloc(p5);
		printf("size of p1 is: %d \n", ((m_node * ) ((int) p1 - HEADER_SIZE)) -> size);
		k_mem_dealloc(p4);
		printf("size of p1 is: %d \n", ((m_node * ) ((int) p1 - HEADER_SIZE)) -> size);
		k_mem_dealloc(p3);
		printf("size of p1 is: %d \n", ((m_node * ) ((int) p1 - HEADER_SIZE)) -> size);
		k_mem_dealloc(p2);
		printf("size of p1 is: %d \n", ((m_node * ) ((int) p1 - HEADER_SIZE)) -> size);
		k_mem_dealloc(p1);
		printf("size of p1 is ------ FINAL---1: %d \n", ((m_node * ) ((int) p1 - HEADER_SIZE)) -> size);

		//ALLOC AGAIN
		p1 = k_mem_alloc(3);
		p2 = k_mem_alloc(32);

		p3 = k_mem_alloc(32);
		p4 = k_mem_alloc(5);
		p5 = k_mem_alloc(32);
		p6 = k_mem_alloc(32);
		p7 = k_mem_alloc(90);
		p8 = k_mem_alloc(200);
		p9 = k_mem_alloc(32);

		//randomized the version of the dealloc
		k_mem_dealloc(p3);
//		printf("size of p1 is: %d \n", ((m_node *) ((int) p1 - 12))->size);
		k_mem_dealloc(p9);
		printf("size of p9 is: %d \n", ((m_node *) ((int) p9 - HEADER_SIZE))->size);
		k_mem_dealloc(p5);
//		printf("size of p1 is: %d \n", ((m_node *) ((int) p1 - 12))->size);
		k_mem_dealloc(p7);
//		printf("size of p1 is: %d \n", ((m_node *) ((int) p1 - 12))->size);
		k_mem_dealloc(p2);
		printf("size of p2 is: %d \n", ((m_node *) ((int) p2 - HEADER_SIZE))->size);
		k_mem_dealloc(p6);
		printf("size of p5 is: %d \n", ((m_node *) ((int) p5 - HEADER_SIZE))->size);
		k_mem_dealloc(p1);
		printf("size of p1 is: %d \n", ((m_node *) ((int) p1 - HEADER_SIZE))->size);
		k_mem_dealloc(p8);
		printf("size of p5 is: %d \n", ((m_node *) ((int) p5 - HEADER_SIZE))->size);
		k_mem_dealloc(p4);
		printf("size of p1 is ---- FINAL---2: %d \n", ((m_node *) ((int) p1 - HEADER_SIZE))->size);


		p1 = k_mem_alloc(1);
//		k_mem_dealloc(p1);
		printf("size of p1 is ---- FINAL---3: %d \n", k_mem_dealloc(p1));
//		k_mem_dealloc(p1);
		printf("size of p1 is ---- FINAL---4: %d \n", k_mem_dealloc(p1));


		p1 = k_mem_alloc(4);
		p2 = k_mem_alloc(12);
		p3 = k_mem_alloc(4);
		p4 = k_mem_alloc(8);
		p5 = k_mem_alloc(4);
		p6 = k_mem_alloc(4);
		p7 = k_mem_alloc(4);
		p8 = k_mem_alloc(4);
		p9 = k_mem_alloc(4);

		printf("size of p1 is: %d \n", ((m_node * ) ((int) p1 - HEADER_SIZE)) -> size);
		printf("size of p2 is: %d \n", ((m_node * ) ((int) p2 - HEADER_SIZE)) -> size);
		printf("size of p3 is: %d \n", ((m_node * ) ((int) p3 - HEADER_SIZE)) -> size);
		printf("size of p4 is: %d \n", ((m_node * ) ((int) p4 - HEADER_SIZE)) -> size);
		printf("size of p5 is: %d \n", ((m_node * ) ((int) p5 - HEADER_SIZE)) -> size);
		printf("size of p6 is: %d \n", ((m_node * ) ((int) p6 - HEADER_SIZE)) -> size);
		printf("size of p7 is: %d \n", ((m_node * ) ((int) p7 - HEADER_SIZE)) -> size);
		printf("size of p8 is: %d \n", ((m_node * ) ((int) p8 - HEADER_SIZE)) -> size);
		printf("size of p9 is: %d \n", ((m_node * ) ((int) p9 - HEADER_SIZE)) -> size);

		k_mem_dealloc(p3);
		printf("size of frag is ---- FINAL---5: %d \n", k_mem_count_extfrag(9+HEADER_SIZE));
		k_mem_dealloc(p2);
		printf("size of frag is ---- FINAL---5: %d \n", k_mem_count_extfrag(25));

		printf("size of p1 is: %d \n", ((m_node * ) ((int) p1 - HEADER_SIZE)) -> size);

		printf("size of p4 is: %d \n", ((m_node * ) ((int) p4 - HEADER_SIZE)) -> size);
		printf("size of p5 is: %d \n", ((m_node * ) ((int) p5 - HEADER_SIZE)) -> size);
		printf("size of p6 is: %d \n", ((m_node * ) ((int) p6 - HEADER_SIZE)) -> size);
		printf("size of p7 is: %d \n", ((m_node * ) ((int) p7 - HEADER_SIZE)) -> size);
		printf("size of p8 is: %d \n", ((m_node * ) ((int) p8 - HEADER_SIZE)) -> size);
		printf("size of p9 is: %d \n", ((m_node * ) ((int) p9 - HEADER_SIZE)) -> size);

		k_mem_dealloc(p4);
		k_mem_dealloc(p6);
		k_mem_dealloc(p8);

		printf("size of frag is ---- FINAL---5: %d \n", k_mem_count_extfrag(100));
		printf("size of frag is ---- FINAL---5: %d \n", k_mem_count_extfrag(4));
		printf("size of frag is ---- FINAL---5: %d \n", k_mem_count_extfrag(9));
		printf("size of frag is ---- FINAL---5: %d \n", k_mem_count_extfrag(13));

//		void * arr[200];
//		int count = 0;
//
//		for (int i = 0; i < 200; i++){
//			arr[i] = k_mem_alloc(4);
//		}
//		for (int i = 199; i < 0; i--){
//			k_mem_dealloc(arr[i]);
//		}

//		for (int i = 0; i < 21; i++ ){
//
//			int x = k_mem_dealloc(arr[i]);
//			if (x==0) count++;
//			if(count == 21){
//				printf("BREAKINGGGG\n");
//				break;}
//		}

//		printf("Eimaan ---- FINAL---3: %d \n", ((m_node *) ((int) arr[1] - 12))->size);


	return TRUE;
}

int test89(){
	printf("NAFIX BIAN CUTE\n\n");
	return 0;
}

int test_99(void) {
	printf("\nTEST 99 FUNCTION STARTING\n");
	int ret_val = test_throughput();

	return ret_val;
}

int test_throughput(void){
	printf("NAFIX BIAN CUTE\n\n");
    unsigned int start = timer_get_current_val(2);

    int *p1;
    for(int i = 1; i < 201; ++i){
        p1 = k_mem_alloc(i);
        k_mem_dealloc(p1);
    }

    unsigned int end = timer_get_current_val(2);

    // Clock counts down
    printf("This took %u us\r\n", start - end);

    return 0;
}
#endif

#if TEST == 2

#define N 10

#define CODE_MEM_INIT -1
#define CODE_MEM_ALLOC -2
#define CODE_MEM_DEALLOC -3
#define CODE_HEAP_LEAKAGE_1 -4
#define CODE_HEAP_LEAKAGE_2 -5
#define CODE_SUCCESS 0

int heap_leakage_test() {

	char *p_old[N], *p_new[N];

	// Step 1: Allocate memory
	for (int i = 0; i < N; i++) {
		p_old[i] = (char*) k_mem_alloc(i * 256 + 255);

		// pointer to allocated memory should not be null
		// starting address of allocated memory should be four-byte aligned
		if (p_old[i] == NULL || ((unsigned int) p_old[0] & 3))
			return CODE_MEM_ALLOC;

		if (i > 0) {
			// adjacent allocated memory should not conflict
			if (p_old[i - 1] + 256 * i >= p_old[i])
				return CODE_MEM_ALLOC;
		}
	}

	// Step 2: De-allocate memory
	for (int i = 0; i < N; i++) {
		if (k_mem_dealloc(p_old[i]) == -1) {
			return CODE_MEM_DEALLOC;
		}
	}

	// Step 3: Memory Leakage
	for (int i = 0; i < N; i++) {
		p_new[i] = (char*) k_mem_alloc((N - i) * 256 - 1);

		// pointer to allocated memory should not be null
		// starting address of allocated memory should be four-byte aligned
		if (p_new[i] == NULL || ((unsigned int) p_new[0] & 3))
			return CODE_HEAP_LEAKAGE_1;

		if (i > 0) {
			// adjacent allocated memory should not conflict
			if (p_new[i - 1] + 256 * (N - i + 1) >= p_new[i])
				return CODE_HEAP_LEAKAGE_1;
		}
	}

	// the total occupied area in the re-allocation
	// should be the same as in the initial allocation
	if ((p_old[0] != p_new[0])
			|| (p_old[N - 1] + N * 256 != p_new[N - 1] + 256)) {
		return CODE_HEAP_LEAKAGE_2;
	}

	for (int i = 0; i < N; i++) {
		k_mem_dealloc(p_new[i]);
	}

	return CODE_SUCCESS;
}

int test_mem(void) {

	int result = heap_leakage_test();
	switch (result) {
	case CODE_MEM_INIT:
	case CODE_MEM_ALLOC:
		printf("Err: Basic allocation fails.\r\n");
		break;
	case CODE_MEM_DEALLOC:
		printf("Err: Basic deallocation fails.\r\n");
		break;
	case CODE_HEAP_LEAKAGE_1:
		printf("Err: Reallocation fails.\r\n");
		break;
	case CODE_HEAP_LEAKAGE_2:
		printf("Err: Heap memory is leaked.\r\n");
		break;
	case CODE_SUCCESS:
		printf("No heap leakage.\r\n");
		break;
	default:
	}

	return result == CODE_SUCCESS;
}
#endif

/*
 *===========================================================================
 *                             END OF FILE
 *===========================================================================
 */
