.. index:: struct

.. _struct:

struct
============================
| いつもの構造体
| 基本的には定義にはtypedefを使うことがコーディング規約で推奨されている。


.. index:: Bit field

.. _Bit field:

Bit field
---------------
| データの型は最も小さいサイズは1byteだが、
| 構造体を使用すれば1bit単位でデータを定義できる。

.. code-block:: c

    typedef struct {
        /* : の後ろの数字がビット数 */
        unsigned char bit0 : 1;
        unsigned char bit1 : 1;
        unsigned char bit2 : 1;
        unsigned char bit3 : 1;
        unsigned char bit4 : 1;
        unsigned char bit5 : 1;
        unsigned char bit6 : 1;
        unsigned char bit7 : 1;
    } bit_t;

    int main(void) {
        bit_t a = {0};
        a.bit7 = 1; /* 普通の構造体のようにアクセスできる */
        return 0;
    }

.. warning::
    | 型のサイズ分必ず埋める事。また、複数の型を使わない事

    .. code-block:: c

        typedef struct {
            unsigned char   bit0_3  : 4;
            unsigned int    bit4_31 : 28;
        } bit_t;

    | これは最終的に8byte分のサイズになる。
    | コンパイラが以下のように修正するからである。
    | 全く意図通りではない
    | これをされることを :ref:`境界値調正` という。

    .. code-block:: c

        typedef struct {
            unsigned char   bit0_3  : 4;
            unsigned char   dummy1  : 4;    /* ucharサイズの残りの穴埋め */
            unsigned char   dummy2;         /* 次のuintの配置アドレスを4の倍数にするための穴埋め */
            unsigned char   dummy3;         /* 次のuintの配置アドレスを4の倍数にするための穴埋め */
            unsigned char   dummy4;         /* 次のuintの配置アドレスを4の倍数にするための穴埋め */
            unsigned int    bit4_31 : 28;
            unsigned int    dummy5  : 4;    /* uintサイズの残りの穴埋め */
        } bit_t;
