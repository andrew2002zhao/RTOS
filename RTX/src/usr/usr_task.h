#pragma once

#include "k_task.h"
#include "common.h"
#include "k_inc.h"

void usr_scheduler_init(TCB* null_task);

TCB* usr_scheduler(void);
void usr_scheduler_add(TCB* tcb);
void usr_scheduler_remove(TCB* tcb);



//extern TCB * priority_scheduler[256];
