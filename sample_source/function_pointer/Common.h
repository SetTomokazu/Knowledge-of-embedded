#ifndef __COMMON_H__
#define __COMMON_H__

/* Project����Header */
typedef struct {
    void (*Init)(void); /* ����������   */
    void (*Main)(void); /* ���C������   */
    void (*Term)(void); /* �I������     */
} ITask_t;

#endif
