#include <stdio.h>
#include <time.h>
#include <conio.h>
#include "Common.h"

#include "TaskA.h"
#include "TaskB.h"

ITask_t* tasklist[] = {
    &Task_A,
    &Task_B
};

#define TASK_MAX (sizeof(tasklist) / sizeof(ITask_t*))
#define TASK_SPAN   1   /* �^�X�N���s�Ԋu[s] */

int IsTimeout(time_t* past, double span)
{
    int result;
    time_t tmp = time(NULL);
    result = (span <= difftime(tmp, *past));
    if(result){
        *past = tmp;
    }
    return result;
}

void main(void) {
    int i;
    time_t past;
    /* �S�^�X�N���������� */
    past = time(NULL);
    for(i = 0; i < TASK_MAX; i++) {
        ((*tasklist[i]).Init)();
    }
    /* �S�^�X�N�̒ʏ퓮����s */
    while(!kbhit()) {
        for(i = 0; i < TASK_MAX; i++) {
            ((*tasklist[i]).Main)();
        }
        while(1) {
            /*TASK_SPAN[s]�҂��߂̏���*/
            /* ���ۂ�RTC�����g�p���邪Windows�łȂ��̂Ŏb��I�� */
            if(IsTimeout(&past, TASK_SPAN)) {
                break;
            }
        }
    }
    /* �S�^�X�N�I������ */
    for(i = 0; i < TASK_MAX; i++) {
        ((*tasklist[i]).Term)();
    }
}
