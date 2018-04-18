#define __TASK_A_C__	/* ヘッダに対し、参照しているCソースファイルを教える為の定義 */

#include <stdio.h>
#include "TaskA.h"

void TaskA_Init(void);
void TaskA_Main(void);
void TaskA_Term(void);

ITask_t Task_A = {
    TaskA_Init,
    TaskA_Main,
    TaskA_Term
};

void TaskA_Init(void) {
	printf("%s\n", "Init TaskA");
}
void TaskA_Main(void) {
	printf("%s\n", "Do TaskA");
}
void TaskA_Term(void) {
	printf("%s\n", "Term TaskA");
}
