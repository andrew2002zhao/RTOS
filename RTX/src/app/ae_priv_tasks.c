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
#include "ae_priv_tasks.h"
#include "ae_usr_tasks.h"
#include "Serial.h"
#include "printf.h"
#include "k_mem.h"

task_t ktid1;
task_t ktid2;
task_t ktid3;


#if TEST == 0
/*****************************************************************************
 * @brief       a task that prints AAAAA, BBBBB, CCCCC,...., ZZZZZ on each line.
 *              It yields the cpu every 6 lines are printed.
 *****************************************************************************/
void ktask1(void)
{
    int i = 0;
    int j = 0;
    long int x = 0;

    while (1) {
        char out_char = 'A' + i % 26;
        for (j = 0; j < 5; j++ ) {
            SER_PutChar(0,out_char);
        }

        SER_PutStr(0,"\n\r");

        for ( x = 0; x < DELAY; x++);

        if ( (++i) % 6 == 0 ) {
            SER_PutStr(0,"priv_task1 before yielding cpu.\n\r");
            k_tsk_yield();
            SER_PutStr(0,"priv_task1 after yielding cpu.\n\r");
        }
    }
}

/*****************************************************************************
 * @brief:      a task that prints 00000, 11111, 22222,....,99999 on each line.
 *              It yields the cpu every 6 lines are printed
 *              before printing these lines indefinitely, it creates a
 *              new task and and obtains the task information. It then
 *              changes the newly created task's priority.
 *****************************************************************************/

void ktask2(void)
{
    long int x = 0;
    int i = 0;
    int j = 0;
    task_t tid;

    k_tsk_create(&tid, &utask1, LOW, 0x200);  /*create a user task */
    k_tsk_set_prio(tid, LOWEST);


    for (i = 1;;i++) {
        char out_char = '0' + i%10;
        for (j = 0; j < 5; j++ ) {
            SER_PutChar(0,out_char);
        }
        SER_PutStr(0,"\n\r");

        for ( x = 0; x < DELAY; x++); // some artifical delay
        if ( i%6 == 0 ) {
            SER_PutStr(0,"priv_task2 before yielding CPU.\n\r");
            k_tsk_yield();
            SER_PutStr(0,"priv_task2 after yielding CPU.\n\r");
        }
    }
}
#endif
/*
 *===========================================================================
 *                             END OF FILE
 *===========================================================================
 */
