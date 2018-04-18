#define __TASK_A_C__	/* �w�b�_�ɑ΂��A�Q�Ƃ��Ă���C�\�[�X�t�@�C����������ׂ̒�` */

#include <stdio.h>
#include "TaskB.h"

void TaskB_Init(void);
void TaskB_Main(void);
void TaskB_Term(void);

ITask_t Task_B = {
    TaskB_Init,
    TaskB_Main,
    TaskB_Term
};

void TaskB_Init(void) {
	printf("%s\n", "Init TaskB");
}
void TaskB_Main(void) {
	printf("%s\n", "Do TaskB");
}
void TaskB_Term(void) {
	printf("%s\n", "Term TaskB");
}
