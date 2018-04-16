
.. index:: union

.. _union:

union
==========
| 研修でこれ一体何がしたいんだと思ったunionは :ref:`Bit field` で大活躍する。
| :ref:`Bit field` の各ビットの値を、バイト単位で初期化をしたい場合等、
| アクセス用のメンバをunionで共存させてしまえばいい。

.. code-block:: c

    typedef struct {
        unsigned char bit0 : 1;
        unsigned char bit1 : 1;
        unsigned char bit2 : 1;
        unsigned char bit3 : 1;
        unsigned char bit4 : 1;
        unsigned char bit5 : 1;
        unsigned char bit6 : 1;
        unsigned char bit7 : 1;
    } bit_t;
    typedef union {
        /* 必ず同じサイズのものを書くこと */
        unsigned char   byte;
        bit_t           bit;
    } byte_t;

    int main(void) {
        byte_t a = {0};
        a.bit.bit7 = 1;     /* これで0x80となる */
        unsigned char b = a.byte;   /* これで0x80が取れる */
        return 0;
    }
