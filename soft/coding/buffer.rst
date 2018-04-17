.. index:: bufferの使い方

.. _buffer:

bufferの使い方
============================
| 組み込みには限られた領域しかRAMが存在しない。
| その為、用途毎にサイズの上限を定めることが多々ある。
| これはmalloc等のRAM上のどこを使用するのか不明瞭な関数の使用を回避する目的もある。

.. index:: ring buffer

.. _ring buffer:

ring buffer
============================
| 循環バッファともいう。
| 延々と新しいものを保存し続ける際に使用する。つまりはログである。
| 大抵のログファイルは延々と文字列を長く詳しく書き、それを上から順番に追記していくが、
| そんな領域は組み込みのRAMには存在しない。
| その為、まずログ1つ分のサイズを一定に定める。
| 次にログを書き込み領域のサイズを定める。
| そしてそこに上から順番に保存していき、一番最後まで行ったら先頭に戻ることを繰り返す。
| その為管理用のバッファとして、どこまで書いたかとどこまで読んだかを保存する。

.. code-block:: c

    #define LOG_SIZE 8
    #define LOG_MAX 500
    typedef struct {
        unsigned char data[LOG_SIZE];
    } log_t;

    typedef struct {
        unsigned int read_point;
        unsigned int write_point;
    } ring_buffer_manager_t;

    log_t log[LOG_MAX];
    ring_buffer_manager_t manager;

    void write(log_t* l) {
        memcpy(&log[manager.write_point], l, sizeof(log_t));
        manager.write_point++;
        if(manager.write_point >= LOG_MAX) {
            manager.write_point = 0;
        }
    }
