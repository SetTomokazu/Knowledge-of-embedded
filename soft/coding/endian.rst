.. index:: Endian

.. _Endian:

Endian
===========
| ここにマイコンの違いによって本当に面倒なことになるお話がある。
| 詳しくは `Wiki <https://ja.wikipedia.org/wiki/%E3%82%A8%E3%83%B3%E3%83%87%E3%82%A3%E3%82%A2%E3%83%B3>`_ 参照
| これと同じ事が :ref:`Bit field` にも存在する。
| その為、その差分を吸収するために以下のように書いてあることがある。

.. code-block:: c

    typedef struct {
    #ifdef __BIG_ENDIAN__
        unsigned char bit0 : 1;
        unsigned char bit1 : 1;
        unsigned char bit2 : 1;
        unsigned char bit3 : 1;
        unsigned char bit4 : 1;
        unsigned char bit5 : 1;
        unsigned char bit6 : 1;
        unsigned char bit7 : 1;
    #else
        unsigned char bit7 : 1;
        unsigned char bit6 : 1;
        unsigned char bit5 : 1;
        unsigned char bit4 : 1;
        unsigned char bit3 : 1;
        unsigned char bit2 : 1;
        unsigned char bit1 : 1;
        unsigned char bit0 : 1;
    #endif
    } bit_t;

.. code-block:: c

    void parse_message(unsigned char *msg) {
        unsigned int tmp = 0;
        tmp =
    #ifdef __BIG_ENDIAN__
            msg[3] << 24 |
            msg[4] << 16 |
            msg[5] <<  8 |
            msg[6];
    #else
            msg[6] << 24 |
            msg[5] << 16 |
            msg[4] <<  8 |
            msg[3];
    #endif
    }

.. note:: 決して「なんじゃこりゃあ！？」とか言って消さないように
