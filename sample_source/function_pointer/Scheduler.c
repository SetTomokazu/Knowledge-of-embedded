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
#define TASK_SPAN   1   /* タスク実行間隔[s] */

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
    /* 全タスク初期化処理 */
    past = time(NULL);
    for(i = 0; i < TASK_MAX; i++) {
        ((*tasklist[i]).Init)();
    }
    /* 全タスクの通常動作実行 */
    while(!kbhit()) {
        for(i = 0; i < TASK_MAX; i++) {
            ((*tasklist[i]).Main)();
        }
        while(1) {
            /*TASK_SPAN[s]待つための処理*/
            /* 実際はRTC等を使用するがWindowsでないので暫定的に */
            if(IsTimeout(&past, TASK_SPAN)) {
                break;
            }
        }
    }
    /* 全タスク終了処理 */
    for(i = 0; i < TASK_MAX; i++) {
        ((*tasklist[i]).Term)();
    }
}
