#ifndef __COMMON_H__
#define __COMMON_H__

/* Project共通Header */
typedef struct {
    void (*Init)(void); /* 初期化処理   */
    void (*Main)(void); /* メイン処理   */
    void (*Term)(void); /* 終了処理     */
} ITask_t;

#endif
