#ifndef __COMMON_H__
#define __COMMON_H__

/* Project‹¤’ÊHeader */
typedef struct {
    void (*Init)(void); /* ‰Šú‰»ˆ—   */
    void (*Main)(void); /* ƒƒCƒ“ˆ—   */
    void (*Term)(void); /* I—¹ˆ—     */
} ITask_t;

#endif
