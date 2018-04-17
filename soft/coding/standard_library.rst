.. index:: 標準ライブラリ

.. _標準ライブラリ:

標準ライブラリ
============================
| C言語でお馴染みの標準ライブラリだが、組み込みでは基本的に非推奨となっている。
| 大雑把な理由としてはどういう実装で動いているかが把握できない為である。
| 特にマイコンの開発環境で使用する標準ライブラリはコンパイラ依存の為当然開発環境に依存する。
| その為同名の関数でも実装方法が異なる恐れがあり、その違いで不具合が発生した場合の責任の所在が無い。
| 無いと結局使った本人の責任になる。
| その為の非推奨である。
| 使いたければ自力で実装しましょう。

.. index:: memset, memcpy, memcmp

.. _memset:
.. _memcpy:
.. _memcmp:

memset,memcpy,memcmp
============================
| おそらく初期化などで最も使用される標準関数である。
| が、内部の動作が非常に怪しいと専らの噂である。
| 一番の問題は「サイズが4の倍数でない場合、端数はどのように計算されるのだろうか」である。
| CPUとしてはint型である4byteでデータ取得や比較を行った方が動作が速い
| その為、以下のような中身だった場合、不具合が起こり得る。

.. code-block:: c

    void *memcpy(void *dst, const void *src, unsigned n) {
        unsigned i;
        unsigned int *d = dst;
        unsigned int *s = src;

        for(i = 0; i < n; i +=4) {
            *(dst++) = *(src++);
        }
    }

| これで引数nが5の場合、0～4byte目まではいいが、5～7byte目は

.. index:: sizeof

.. _sizeof:

sizeof
============================
| こいつも信用ならないという説があるがこればっかりは必要であると考える。
| この説が紛糾する原因は全て :ref:`Alignment` と :ref:`境界値調正`  にある。
| が、一番の敵は何も考えずに以下のようなコードを書く人である。

.. code-block:: c

    typedef struct {
        unsigned char data1;
        unsigned int data2;
    } hoge_t;

    hoge_t hoge;

    /* UART通信などで受信したメッセージをローカルにコピーする */
    void getdata_frommessage(unsigned char *msg) {
        memcpy(&hoge, msg, sizeof(hoge_t));
    }

| 上記コードで、msgが5byteしかなく、それ以降に何のデータが入っているか不明な場合、

.. code-block:: c

    hote.data2

| には何が入るんでしょうかねえ

.. code-block:: c

    typedef struct {
        unsigned char data1;
        unsigned int data2;
    } hoge_t;

    hoge_t hoge;

    /* UART通信などで受信したメッセージをローカルにコピーする */
    void getdata_frommessage(unsigned char *msg) {
        hoge.data1 = msg[0];
        hode.data2 =
            (unsigned int)msg[1] << 24 |
            (unsigned int)msg[2] << 16 |
            (unsigned int)msg[3] <<  8 |
            (unsigned int)msg[4];
    }

| そういうわけで大体こういう書き方になる。
