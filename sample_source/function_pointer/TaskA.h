#ifndef __TASK_A_H__	/* 多重参照防止用の定型文 */
#define __TASK_A_H__	/* 多重参照防止用の定型文 */

/* 同名のCソースファイルではexternを使用しないようにする定型文 */
#ifdef __TASK_A_C__
#define EXTERN
#else
#define EXTERN extern
#endif

#include "Common.h"

EXTERN ITask_t Task_A;

#endif					/* 多重参照防止用の定型文 */
