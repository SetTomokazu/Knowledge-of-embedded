.. index:: switch

.. _switch:

switch
============================
| C言語でおなじみのswitch文だが、
| 組み込みで使用する場合にはあまり見ない独特な使い方をする。

.. code-block:: c

    unsigned char sequence;

    void seq_manager(void) {
        /* 毎回処理を行ったら次の実行時までサービスを返す為、 */
        /* このような段階を踏んで処理を変えるような記述を使う */
        switch(sequence) {
            case 0:
                seq_0();
                sequence++;
                break;
            case 1:
                seq_1();
                sequence++;
                break;
            case 2:
                seq_2();
                sequence = 0;
                break;
            default:
                break;
        }
    }


.. note::
    | switch文では条件分岐を高速に行うために値と分岐先のアドレスをまとめたテーブルを作成する。
    | このテーブルがconstセクションに自動的に配置される為、セクションを切る際には注意が必要である。
