/*
 ****************************************************************************
 *
 *                  UNIVERSITY OF WATERLOO ECE 350 RTOS LAB
 *
 *                 Copyright 2020-2021 ECE 350 Teaching Team
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

#include "ae.h"
#include "ae_usr_tasks.h"
#include "rtx.h"
#include "Serial.h"
#include "printf.h"

extern void kcd_task(void);

task_t utid1;
task_t utid2;
task_t utid3;

#if TEST == 1
void utask1(void)
{
	printf("HELLO IM RUNNING TEST 1 \n");
    SER_PutStr (0,"utask1: entering \n\r");

    /* do something */
    tsk_create(&utid1, &utask69, 75, 0x200);  /*create a user task */
//    tsk_get_info(tid, &task_info);
//    tsk_set_prio(tid, 200);
    /* terminating */
     tsk_exit();
}

/**
 * @brief: a dummy task2
 */

//has prio 76
void uhello(void){

//	while(1){
		printf("hello \n");
		//set prio of other task higher than this tasks prio
		RTX_TASK_INFO buf2;
		tsk_get_info(utid3,&buf2);

		tsk_set_prio(utid3,4);

		RTX_TASK_INFO buf;
		tsk_get_info(utid3,&buf);

		tsk_yield();
		printf("hello2 \n");
//	}
	tsk_exit();
}
//this has priority 77
void uworld(void){

//	while(1){
		printf("world \n");
//		tsk_set_prio(utid3,5);
		//set prio of other task higher than this tasks prio
//		tsk_set_prio(utid2,4);
		tsk_yield();
//		}

	tsk_exit();

}

void utask69(void){

//	//make a new task with priority 5
	tsk_create(&utid2, &uhello, 76, 0x100);
	tsk_create(&utid3,&uworld, 77,0x300);

	RTX_TASK_INFO buf;
	tsk_get_info(utid2,&buf);
	printf("ALLOCATION FOR UHELLO %x \n", (int)(buf.u_stack_hi));


	RTX_TASK_INFO buf2;
	tsk_get_info(utid3,&buf2);
	printf("ALLOCATION FOR UWORLD %x \n", (int)(buf2.u_stack_hi));

//	//make a new task with priority 5
	tsk_exit();
}

void utask2(void)
{
    SER_PutStr (0,"utask2: entering \n\r");
    /* do something */
    long int x = 0;
    int ret_val = 10;
    int i = 0;
    int j = 0;
    for (i = 1;;i++) {
		char out_char = 'a' + i%10;
		for (j = 0; j < 5; j++ ) {
			SER_PutChar(0,out_char);
		}

		SER_PutStr(0,"\n\r");

		for ( x = 0; x < 5000000; x++); // some artifical delay

		if (i % 6 == 0) {
			SER_PutStr(0,"utask2 before yielding cpu.\n\r");
			ret_val = tsk_yield();
			SER_PutStr(0,"utask2 after yielding cpu.\n\r");
			printf("utask2: ret_val=%d\n\r", ret_val);
		}
	}
}
#endif

//testing multiple task of the same
#if TEST == 6969

task_t utid1;
task_t utid2;
task_t utid3;
task_t utid4;

void utask6969(void)
{
	printf("HELLO IM RUNNING TEST 1 \n");
    SER_PutStr (0,"utask1: entering \n\r");

    /* do something */
    tsk_create(&utid1, &uh1, 125, 0x200);  /*create a user task */
    tsk_create(&utid2, &uh2, 125, 0x200);  /*create a user task */
    tsk_create(&utid3, &uh3, 125, 0x200);  /*create a user task */
    tsk_create(&utid4, &uh4, 125, 0x200);  /*create a user task */
    /* terminating */
    printf("done \n");
    tsk_exit();
}
//all these tasks have the same priority
void uh1(void){
	for(int i =0; i<2;i++){
		printf("b\n");
		tsk_yield();
		printf("b --\n");
		tsk_yield();
	}
		tsk_exit();
}

void uh2(void){
	for(int i =0; i<2;i++){
		printf("i\n");
		tsk_yield();
		printf("i --\n");
		tsk_yield();
	}
	tsk_exit();
}

void uh3(void){
	for(int i =0; i<2;i++){
		printf("a\n");
		tsk_yield();
		printf("a --\n");
		tsk_yield();
	}
		tsk_exit();
}

void uh4(void){
	for(int i =0; i<2;i++){
		printf("n\n");
		tsk_yield();
		printf("n --\n");
		tsk_yield();
	}
	tsk_exit();
}

#endif

#if TEST == 111

void utask1(void) {
	printf("[UT1] Info: Entering user task 1!\r\n");
	printf("[UT1] Info: Searching for a task with kcd_task entry point!\r\n");

	RTX_TASK_INFO buffer;
	int flag = tsk_get_info(TID_KCD, &buffer);

	if ( flag == RTX_OK && buffer.state != DORMANT) {
		printf("[T_01] Failed: Found a task with kcd_task entry point!\r\n");
		printf("- This means that KCD task is created without being passed to tsk_init!\r\n");
		printf("- KCD task should be created only if it is passed to tsk_init!\r\n");
		printf("- This has to be fixed for lab4!\r\n");
	} else {
		printf("[T_01] Passed: Could not find any task with kcd_task entry point!\r\n");
	}

	test_mem();

	printf("============================================\r\n");
	printf("==================Test is done==============\r\n");
	printf("============================================\r\n");
	tsk_exit();
}

#endif

#if TEST == 99

void utask99(void) {
	test_99();

	printf("============================================\r\n");
	printf("==================Test is done==============\r\n");
	printf("============================================\r\n");
	tsk_exit();
}

#endif

#if TEST == 2

volatile char turn = 1;

void utask1(void) {
	printf("[UT1] Info: Entering user task 1!\r\n");

	RTX_MSG_HDR *msg = NULL;
	task_t sender_tid = 0;

	int i = 0;
	int j = 0;
	int eflag = 0;
	char tsk2_passed = 0;
	char correct_msg = 1;
	char message[4] = {'c', 'G', 'T', 'A'};
	utid1 = tsk_get_tid();

	printf("[UT1] Info: Creating a mailbox!\r\n");

	if (mbx_create(2 * (sizeof(RTX_MSG_HDR) + sizeof(task_t) + 5)) == RTX_OK) {
		printf("[UT1] Info: Allocating memory for messages!\r\n");

		msg = mem_alloc(sizeof(RTX_MSG_HDR) + 4);

		if (msg != NULL) {
			printf("[UT1] Info: Setting up a registration message!\r\n");

			msg->length = sizeof(RTX_MSG_HDR) + 1;
			msg->type = KCD_REG;
			*((char *)(msg + 1)) = 'c';

			printf("[UT1] Info: Registering 'c' command with the KCD task!\r\n");

			if (send_msg(TID_KCD, msg) == RTX_OK) {
				printf("[UT1] Passed: Registered 'c' command with the KCD!\r\n");
				printf("- Task 1 will wait for input commands from KCD in a loop!\r\n");
				printf("- Task 1 will let task 2 run by setting a global variable after receiving 2 commands!\r\n");
				printf("- Task 1 waist for task 2 to send it a message with test results!\r\n");
				printf("- Task 2 will register 'c' and 'd' with KCD and wait for KCD to receive 4 commands!\r\n");
				printf("- Task 2 will send a message to task 1 with test results and exits\r\n");
				printf("- Task 1 will print the results!\r\n");

				for (i = 0; i < 2; i++) {
					printf("[UT1] Info: Calling receive!\r\n");

					if (recv_msg(&sender_tid, msg, sizeof(RTX_MSG_HDR) + 4) == RTX_OK) {
						printf("[UT1] Info: Checking the sender!\r\n");

						if (sender_tid == TID_KCD) {
							printf("[UT1] Info: Checking the data in the message!\r\n");
							correct_msg = 1;

							if (((msg->length) - sizeof(RTX_MSG_HDR)) == 4) {
								for (j = 0; j < 4; j++) {
									char c = *((char *)(msg + 1) + j);

									SER_PutChar(1, c);

									if (c != message[j]) {
										correct_msg = 0;
									}
								}

								SER_PutStr(1, "\r\n");
							} else {
								correct_msg = 0;
							}

							if (correct_msg == 1) {
								printf("[UT1] Passed: Received the correct message from KCD!\r\n");
							} else {
								printf("[UT1] Failed: Received a wrong message from KCD!\r\n");
								eflag++;
							}

						} else {
							printf("[UT1] Failed: Message was not sent by KCD task!\r\n");
							printf("Cannot run the rest of the test items including:\r\n");
							printf("- Checking the content of the message.\r\n");
							eflag++;
						}

					} else {
						printf("[UT1] Failed: Receiving a message caused an error!\r\n");
						printf("Cannot run the rest of the test items including:\r\n");
						printf("- Checking the sender and the content of the message.\r\n");
						eflag++;
					}
				}
			} else {
				printf("[UT1] Failed: Could not register a command with KCD!\r\n");
				printf("Cannot run the rest of the test items including:\r\n");
				printf("- Calling recv_msg in a loop and to receive input commands from KCD.\r\n");
				eflag = 3;
			}

			printf("[UT1] Info: Setting global variable to let user task 2 register 'c' command!\r\n");
			turn = 2;

			printf("[UT1] Info: Searching for TID of task 2!\r\n");

			printf("[UT1] Info: Calling receive function to wait for task 2 to be done!\r\n");

			if (recv_msg(&sender_tid, msg, sizeof(RTX_MSG_HDR) + 4) == RTX_OK) {
				printf("[UT1] Info: Checking the sender!\r\n");

				if (sender_tid == utid2) {
					printf("[UT1] Passed: A message was received from task 2!\r\n");
					printf("[UT1] Info: Checking the content of message to see how many tests were passed by task 2!\r\n");

					if (*((char *)(msg + 1)) < 10) {
						tsk2_passed = *((char *)(msg + 1));
						printf("[UT1] Passed: %d tests passed by task 2!\r\n", (int)tsk2_passed);
					} else {
						tsk2_passed = 0;
						printf("[UT1] Failed: A wrong message was received from task 2!\r\n");
					}

					eflag += (7 - tsk2_passed);

				} else {
					printf("[UT1] Failed: Received a message from a task with different TID than task 2!\r\n");
					printf("Cannot run the rest of the test items including:\r\n");
					printf("- Checking task 2's tests.\r\n");
					eflag += 8;
				}
			} else {
				printf("[UT1] Failed: Message was not successfully received!\r\n");
				printf("Cannot run the rest of the test items including:\r\n");
				printf("- Checking task 2's tests.\r\n");
				eflag += 8;
			}

		} else {
			printf("[UT1] Failed: Could not allocate memory!\r\n");
			printf("Cannot run the rest of the test items including:\r\n");
			printf("- Calling recv_msg in a loop and to receive input commands from KCD; and\r\n");
			printf("- Checking task 2's tests.\r\n");
			eflag = 11;
		}
	} else {
		printf("[UT1] Failed: Could not create a mailbox!\r\n");
		printf("Cannot run the rest of the test items including:\r\n");
		printf("- Calling recv_msg in a loop and to receive input commands from KCD; and\r\n");
		printf("- Checking task 2's tests.\r\n");
		eflag = 11;
	}

	printf("============================================\r\n");
	printf("=============Final test results=============\r\n");
	printf("============================================\r\n");
	printf("[T_02] %d out of 11 tests passed!\r\n", 11 - eflag);
	tsk_exit();
}

void utask2(void) {
	printf("[UT2] Info: Entering user task 2!\r\n");

	RTX_MSG_HDR *msg = NULL;
	task_t sender_tid = 0;

	int i = 0;
	int j = 0;
	char sflag = 0;
	char correct_msg = 1;
	char message1[4] = {'c', 'G', 'T', 'A'};
	char message2[4] = {'d', 'G', 'T', 'A'};
	char *message;

	utid2 = tsk_get_tid();
	task_t tsk1_tid = 0;

	printf("[UT2] Info: Waiting for task 1 to be done with its first portion!\r\n");

	while(turn == 1);

	printf("[UT2] Info: Creating a mailbox!\r\n");

	if (mbx_create(2 * (sizeof(RTX_MSG_HDR) + sizeof(task_t) + 5)) == RTX_OK) {
		printf("[UT2] Info: Allocating memory for messages!\r\n");

		msg = mem_alloc(sizeof(RTX_MSG_HDR) + 4);

		if (msg != NULL) {
			printf("[UT2] Info: Setting up a registration message!\r\n");

			msg->length = sizeof(RTX_MSG_HDR) + 1;
			msg->type = KCD_REG;
			*((char *)(msg + 1)) = 'c';

			printf("[UT2] Info: Registering 'c' command with the KCD task!\r\n");

			if (send_msg(TID_KCD, msg) == RTX_OK) {
				printf("[UT2] Passed: Registered 'c' command with the KCD!\r\n");
				sflag++;

				printf("[UT2] Info: Setting up another registration message!\r\n");
				*((char *)(msg + 1)) = 'd';

				printf("[UT2] Info: Registering 'd' command with the KCD task!\r\n");

				if (send_msg(TID_KCD, msg) == RTX_OK) {
					printf("[UT2] Passed: Registered 'd' command with the KCD!\r\n");
					sflag++;

					for (i = 0; i < 4; i++) {
						printf("[UT2] Info: Calling receive!\r\n");
						printf("- KCD will send task 1 input commands!\r\n");
						if ((i % 2) == 0) {
							message = message1;
						} else {
							printf("%%dGROUP and then press enter!\r\n");
							message = message2;
						}
						printf("You will probably see the command echoed into the Putty!\r\n");

						if (recv_msg(&sender_tid, msg, sizeof(RTX_MSG_HDR) + 4) == RTX_OK) {
							printf("[UT2] Info: Checking the sender!\r\n");

							if (sender_tid == TID_KCD) {
								printf("[UT2] Info: Checking the data in the message!\r\n");
								correct_msg = 1;

								if (((msg->length) - sizeof(RTX_MSG_HDR)) == 4) {
									for (j = 0; j < 4; j++) {
										char c = *((char *)(msg + 1) + j);

										SER_PutChar(1, c);

										if (c != message[j]) {
											correct_msg = 0;
										}
									}

									SER_PutStr(1, "\r\n");
								} else {
									correct_msg = 0;
								}

								if (correct_msg == 1) {
									printf("[UT2] Passed: Received the correct message from KCD!\r\n");
									sflag++;
								} else {
									printf("[UT2] Failed: Received a wrong message from KCD!\r\n");
								}

							} else {
								printf("[UT2] Failed: Message was not sent by KCD task!\r\n");
								printf("Cannot run the rest of the test items including:\r\n");
								printf("- Checking the content of the message.\r\n");
							}

						} else {
							printf("[UT2] Failed: Receiving a message caused an error!\r\n");
							printf("Cannot run the rest of the test items including:\r\n");
							printf("- Checking the sender and the content of the message.\r\n");
						}
					}
				} else {
					printf("[UT2] Failed: Could not register a command with KCD!\r\n");
					printf("Cannot run the rest of the test items including:\r\n");
					printf("- Calling recv_msg in a loop and to receive input commands from KCD.\r\n");
				}
			} else {
				printf("[UT2] Failed: Could not register a command with KCD!\r\n");
				printf("Cannot run the rest of the test items including:\r\n");
				printf("- Calling recv_msg in a loop and to receive input commands from KCD.\r\n");
			}

			printf("[UT2] Info: Searching for TID of task 1!\r\n");
			tsk1_tid = utid1;
			if (tsk1_tid != 0) {
				printf("[UT2] Info: Changing priority of task 1 to lowest!");

				if (tsk_set_prio(tsk1_tid, 200) == RTX_OK) {
					printf("[UT2] Passed: Successfully changed priority of task 1 to lowest!\r\n");
					sflag++;

					printf("[UT2] Info: Setting up a message to be sent to test 1!\r\n");

					msg->type = DEFAULT;
					*((char *)(msg + 1)) = sflag;

					send_msg(tsk1_tid, msg);

				} else {
					printf("[UT2] Failed: Could not set priority of task 1!\r\n");
					printf("Cannot run the rest of the test items including:\r\n");
					printf("- Sending a message to task 1 to let it finish and print the test result!\r\n");
				}
			} else {
				printf("[UT2] Failed: Could not find TID of task 1!\r\n");
				printf("Cannot run the rest of the test items including:\r\n");
				printf("- Sending a message to task 1 to let it finish and print result!\r\n");
			}
		} else {
			printf("[UT2] Failed: Could not allocate memory!\r\n");
			printf("Cannot run the rest of the test items including:\r\n");
			printf("- Calling recv_msg in a loop and to receive input commands from KCD; and\r\n");
			printf("- Sending a message to task 1 and letting it print the test results.\r\n");
		}
	} else {
		printf("[UT2] Failed: Could not create a mailbox!\r\n");
		printf("Cannot run the rest of the test items including:\r\n");
		printf("- Calling recv_msg in a loop and to receive input commands from KCD; and\r\n");
		printf("- Sending a message to task 1 and letting it print the test results.\r\n");
	}

	printf("[UT2] Exiting task 2!\r\n");
	tsk_exit();
}

void utask3(void) {
	while(1) {
		tsk_yield();
	}
}

#endif

#if TEST == 3

volatile int sflag = 0;
int num_iterations = 8;
int num_dequeues = 8;

void utask1(void) {
	printf("[UT1] Info: Entering user task 1!\r\n");

	task_t my_tid  = 0;
	RTX_MSG_HDR *msg = NULL;

	int i = 0;
	int j = 0;
	int what_to_expect = 0;

	int message_len = 0;
	char is_sequential = 0;

	printf("[UT1] Info: Searching for TID of task 1!\r\n");

	utid1 = tsk_get_tid();
	my_tid = utid1;

	if (my_tid != 0) {
		printf("[UT1] Info: Creating a mailbox!\r\n");

		if (mbx_create(0x1FF) == RTX_OK) {
			printf("[UT1] Info: Allocating memory for the messages!\r\n");

			msg = mem_alloc(sizeof(RTX_MSG_HDR) + 4);

			if (msg != NULL) {
				printf("[UT1] Info: Calling receive to let task 2 send task 1 messages!\r\n");
				printf("1. Task 2 will change priority of task 1 to lowest!\r\n");
				printf("2. Task 2 will fill up task 1's mailbox!\r\n");
				printf("3. Task 2 will change priority of task 1 back to medium!\r\n");
				printf("4. Task 1 dequeues some messages (checking for content as well) and sets its own priority to lowest!\r\n");
				printf("5. Task 2 fills up task 1's mailbox and we repeat (3), (4), and (5) for few times!\r\n");

				for (i = 0; i < num_iterations; i++) {
					if ((i % 2) == 0) {
						message_len = 1;
					} else {
						message_len = 4;
					}

					is_sequential = 1;

					for (j = 0; j < num_dequeues; j++) {
						if (recv_msg(NULL, msg, sizeof(RTX_MSG_HDR) + message_len) == RTX_OK) {
							if ((*((int *)(msg + 1))) != what_to_expect) {
								is_sequential = 0;
								break;
							}
						} else {
							if ((i % 2) != 0) {
								is_sequential = 0;
								break;
							}
						}
						what_to_expect++;
					}

					if (is_sequential == 1) {
						printf("[UT1] Passed: Messages were sequential!\r\n");
						sflag++;
					} else {
						printf("[UT1] Failed: Messages were not sequential!\r\n");
						break;
					}

					printf("[UT1] Info: Setting the priority of task 1 to lowest\r\n");

					if (tsk_set_prio(my_tid, 200) != RTX_OK) {
						printf("[UT1] Failed: Could not set the priority of task 1 to lowest\r\n");
						break;
					}
				}
			} else {
				printf("[UT1] Failed to allocate memory for messages!\r\n");
			}
		} else {
			printf("[UT1] Failed: Could not create a mailbox!\r\n");
		}
	} else {
		printf("[UT1] Failed: Could not find TID of task 1!\r\n");
	}

	printf("============================================\r\n");
	printf("=============Final test results=============\r\n");
	printf("============================================\r\n");
	printf("[T_03] %d out of 17 tests passed!\r\n", sflag);
	tsk_exit();
}


void utask2(void) {
	printf("[UT2] Info: Entering task 2!\r\n");

	RTX_MSG_HDR *msg = NULL;
	task_t tsk1_tid = 0;

	int what_to_send = 0;
	int tsk1_mbx_cap = 0;

	int i = 0;
	int j = 0;

	char lost_cap = 0;

	printf("[UT2] Info: Searching for TID of task 1!\r\n");
	tsk1_tid = utid1;

	if (tsk1_tid != 0) {
		printf("[UT2] Info: Setting priority of task 1 to lowest!\r\n");

		if(tsk_set_prio(tsk1_tid, 200) == RTX_OK) {
			printf("[UT2] Info: Allocating memory for messages!\r\n");
			msg = mem_alloc(sizeof(RTX_MSG_HDR) + 4);

			if (msg != NULL) {
				printf("[UT2] Info: Setting up sequence of messages to be sent to task 1!\r\n");

				msg->type = DEFAULT;
				msg->length = sizeof(RTX_MSG_HDR) + 4;
				*((int *)(msg + 1)) = what_to_send;

				printf("[UT2] Info: Filling up task 1's mailbox!\r\n");
				while(send_msg(tsk1_tid, msg) == RTX_OK) {
					tsk1_mbx_cap++;
					*((int *)(msg + 1)) = (++what_to_send);
				}

				if (tsk1_mbx_cap > num_dequeues) {
					printf("[UT2] Passed: Filled up task 1's mailbox with more than %d messages!\r\n", num_dequeues);
					sflag++;

					for (i = 0; i < num_iterations; i++) {
                                                printf("[UT2] Info: Setting priority of task 1 back to medium!\r\n");

						if (tsk_set_prio(tsk1_tid, 150) == RTX_ERR) {
							printf("[UT2] Failed: Could not change priority of task 1 to medium!\r\n");
							break;
						}

						printf("[UT2] Info: Filling up task 1's mailbox again with %d more messages!\r\n", num_dequeues);

						lost_cap = 0;

						for (j = 0; j < num_dequeues; j++) {
							*((int *)(msg + 1)) = what_to_send;

							if (send_msg(tsk1_tid, msg) == RTX_ERR) {
								lost_cap = 1;
								break;
							} else {
								what_to_send++;
							}
						}

						if(lost_cap == 0) {
							printf("[UT2] Passed: Filled task1's mailbox again with %d messages!\r\n", num_dequeues);
							sflag++;
						} else {
							printf("[UT2] Failed: Task 1's mailbox got full with less than %d messages!\r\n", num_dequeues);
							break;
						}
					}
				} else {
					printf("[UT2] Failed: Could not send more than 4 messages to task 2 with huge capacity!\r\n");
				}
			} else {
				printf("[UT2] Failed: Could not allocate memory for messages!\r\n");
			}
		} else {
			printf("[UT2] Failed: Could not set priority of task 1 to lowest!\r\n");
		}
	} else {
		printf("[UT2] Failed: Could not find TID of task 1!\r\n");
	}

	printf("[UT2] Info: Exiting task 2!\r\n");
	tsk_exit();
}

#endif

/*
 *===========================================================================
 *                             END OF FILE
 *===========================================================================
 */
