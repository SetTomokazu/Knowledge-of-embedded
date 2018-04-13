.. index:: C言語の標準仕様

.. _C言語の標準仕様:

C言語の標準仕様
============================

.. index:: Bit field

.. _Bit field:

Bit field
^^^^^^^^^^^^^^^^^^
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

.. index:: union

.. _union:

union
^^^^^^^^^^^^
| 研修でこれ一体何がしたいんだと思ったunionは :ref:`Bit field` で大活躍する。
| :ref:`Bit field` の各ビットの値を、

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

.. index:: Endian

.. _Endian:

Endian
^^^^^^^^^^^^^^
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

.. note:: 決して「なんじゃこりゃあ！？」とか言って消さないように


.. index:: Alignment

.. _Alignment:

Alignment
============================
| 分かり易くは　`外部記事 <http://ertl.jp/~takayuki/readings/info/no01.html>`_ 参照

**データはアクセスサイズの整数倍のアドレスからしか取得できない。**

| つまり、2byteのデータを読み書きする場合は アドレスが偶数でないと取得できない。
| int型の4byteを読み書きする際はアドレスが4の倍数である必要がある。
| それ以外の個所へ読み書きしようとすると基本的にエラーになる。

| 例えば以下のようにアドレスにデータが格納されているとする。

+--------+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
|Address | 0| 1| 2| 3| 4| 5| 6| 7| 8| 9| A| B| C| D| E| F|
+========+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+==+
|Data    |01|02|03|04|05|06|07|08|09|0A|0B|0C|0D|0E|0F|10|
+--------+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+

| この時、アドレス1から4バイトのデータは 0x02030405 であるが、
| これを取るためにint型でアクセスは基本的に出来ない。

.. note::
    この時のエラーはマイコンによって異なる。
    見聞きしたことがあるのは以下の3通り

    * 例外を出力する。
    * その次の正しいAlignmentへ読み書きし、そのまま動く。
    * はみ出ている部分を全て取得し、マイコンが自力で演算して正しい値を使用する。
        | このマイコンの時のみ、上記の0x02030405が取得できる。
        | が、これを当てにしたプログラムを書くと移植時の不具合の基になる為やらないこと。

.. index:: 境界値調正

.. _境界値調正:

境界値調正
============================
| コンパイラが :ref:`Alignment` を守る為に、構造体に詰め物をすること。
| 以下は境界値調正される構造体とその結果の例である。

.. code-block:: c

    /* 例1 */
    /* before */
    typedef struct {
        char    byte;
        int     word;
    } hoge_t;

    /* after */
    typedef struct {
        char    byte;
        char    dummy[3];   /* wordを4byteAlignmentに配置させるためのオフセット */
        int     word;
    } hoge_t;

.. code-block:: c

    /* 例2 */
    /* before */
    typedef struct {
        char    byte1;
        short   hword;
        char    byte2;
    } hoge_t;

    /* after */
    typedef struct {
        char    byte1;
        char    dummy1;     /* hwordを4byte :ref:`Alignment` に配置させるためのオフセット */
        short   hword;
        char    byte2;
        char    dummy2;     /* hoge_tのサイズを2byte :ref:`Alignment` に適合させるためのおまけ */
    } hoge_t;

.. warning:: 様々な型を内包した構造体は、一番サイズの大きい型の整数倍にサイズが調整される。

| このため、例えば例2の構造体において
| 構造体をパッと見ただけでは4byteだが、sizeofを行った結果は6byteになる。
| この為むやみやたらとmemcpyやキャストを行うと、想定外のアドレスへアクセスしていたり、
| 期待と違った値が読み出せたりするため大変危険である。
| 構造体を記述する際は常に隙間が空かないように注意する事。


.. index:: volatile

.. _volatile:

volatile
============================
| コンパイルする際のオプションで最適化というものがある。
| これはアセンブラレベルでのソースの簡略化や共通化によってコード量を減らしたり高速化したりすることである。
| なおそれをされると非常に面倒なことがあったりする。



#pragma
============


関数宣言

