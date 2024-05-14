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
extern void kcd_task(void);

/**************************************************************************//**
 * @brief   	ae_init
 * @return		RTX_OK on success and RTX_ERR on failure
 * @param[out]  sys_info system initialization struct AE writes to
 * @param[out]	task_info boot-time tasks struct array AE writes to
 *
 *****************************************************************************/

int ae_init(RTX_SYS_INFO *sys_info, RTX_TASK_INFO *task_info, int num_tasks) {
    if (ae_set_sys_info(sys_info) != RTX_OK) {
        return RTX_ERR;
    }

    ae_set_task_info(task_info, num_tasks);
    return RTX_OK;
}

/**************************************************************************//**
 * @brief       fill the sys_info struct with system configuration info.
 * @return		RTX_OK on success and RTX_ERR on failure
 * @param[out]  sys_info system initialization struct AE writes to
 *
 *****************************************************************************/
int ae_set_sys_info(RTX_SYS_INFO *sys_info) {
    if (sys_info == NULL) {
        return RTX_ERR;
    }

    // Scheduling sys info set up, only do DEFAULT in lab2
    sys_info->sched = DEFAULT;

    return RTX_OK;
}

/**************************************************************************//**
 * @brief       fill the tasks array with information
 * @param[out]  tasks 		An array of RTX_TASK_INFO elements to write to
 * @param[in]	num_tasks	The length of tasks array
 * @return		None
 *****************************************************************************/

void ae_set_task_info(RTX_TASK_INFO *tasks, int num_tasks) {

    if (tasks == NULL) {
    	printf("[ERROR] RTX_TASK_INFO undefined\n\r");
        return;
    }

#if TEST == 0
    tasks[0].ptask = &ktask1;
    tasks[0].priv  = 1;
    tasks[0].prio  = 100;
	tasks[0].k_stack_size = (0x200);

	tasks[1].ptask = &ktask2;
	tasks[1].priv  = 1;
	tasks[1].prio  = 100;
	tasks[1].k_stack_size = (0x200);

	tasks[2].ptask = &utask2;
	tasks[2].priv  = 0;
	tasks[2].prio  = 100;
	tasks[2].k_stack_size = (0x200);
#endif


#if TEST == 1

    printf("============================================\r\n");
    printf("============================================\r\n");
    printf("Info: Starting T_01!\r\n");
    printf("Info: Initializing system with a single user task!\r\n");

    tasks[0].prio = 100;
	tasks[0].priv = 0;
	tasks[0].ptask = &utask1;
	tasks[0].k_stack_size = 0x200;
	tasks[0].u_stack_size = 0x200;

#endif


#if TEST == 6969

    printf("============================================\r\n");
    printf("============================================\r\n");
    printf("Info: Starting T_01!\r\n");
    printf("Info: Initializing system with a single user task!\r\n");

    tasks[0].prio = 100;
	tasks[0].priv = 1;
	tasks[0].ptask = &utask6969;
	tasks[0].k_stack_size = 0x200;
	tasks[0].u_stack_size = 0x200;

#endif

#if TEST == 99

    printf("============================================\r\n");
    printf("============================================\r\n");
    printf("Info: Starting T_99!\r\n");
    printf("Info: Initializing system with a single user task!\r\n");

    tasks[0].prio = HIGH;
	tasks[0].priv = 0;
	tasks[0].ptask = &utask99;
	tasks[0].k_stack_size = 0x200;
	tasks[0].u_stack_size = 0x200;

#endif


#if TEST == 2

    printf("============================================\r\n");
    printf("============================================\r\n");
    printf("Info: Starting T_02!\r\n");
    printf("Info: Initializing system with three user task and the KCD task!\r\n");
    printf("Info: UT1 (M), UT2 (L), KCD (H), UT4 (L)!\r\n");

    tasks[0].prio = 160;
	tasks[0].priv = 0;
	tasks[0].ptask = &utask1;
	tasks[0].k_stack_size = 0x200;
	tasks[0].u_stack_size = 0x200;

    tasks[1].prio = 175;
	tasks[1].priv = 0;
	tasks[1].ptask = &utask2;
	tasks[1].k_stack_size = 0x200;
	tasks[1].u_stack_size = 0x200;

	tasks[2].prio = 159;
	tasks[2].priv = 0;
	tasks[2].ptask = &kcd_task;
	tasks[2].k_stack_size = 0x200;
	tasks[2].u_stack_size = 0x200;

	tasks[3].prio = 200;
	tasks[3].priv = 0;
	tasks[3].ptask = &utask3;
	tasks[3].k_stack_size = 0x200;
	tasks[3].u_stack_size = 0x200;

#endif

#if TEST == 3

    printf("============================================\r\n");
    printf("============================================\r\n");
    printf("Info: Starting T_03!\r\n");
    printf("Info: Initializing system with two user tasks (M and L priorities)!\r\n");

    k_mem_init();
    tasks[0].prio = 150;
	tasks[0].priv = 0;
	tasks[0].ptask = &utask1;
	tasks[0].k_stack_size = 0x200;
	tasks[0].u_stack_size = 0x200;

    tasks[1].prio = 175;
	tasks[1].priv = 0;
	tasks[1].ptask = &utask2;
	tasks[1].k_stack_size = 0x200;
	tasks[1].u_stack_size = 0x200;

#endif

}

/*
 *===========================================================================
 *                             END OF FILE
 *===========================================================================
 */
