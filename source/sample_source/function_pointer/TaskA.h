#ifndef __TASK_A_H__	/* ���d�Q�Ɩh�~�p�̒�^�� */
#define __TASK_A_H__	/* ���d�Q�Ɩh�~�p�̒�^�� */

/* ������C�\�[�X�t�@�C���ł�extern���g�p���Ȃ��悤�ɂ����^�� */
#ifdef __TASK_A_C__
#define EXTERN
#else
#define EXTERN extern
#endif

#include "Common.h"

EXTERN ITask_t Task_A;

#endif					/* ���d�Q�Ɩh�~�p�̒�^�� */
