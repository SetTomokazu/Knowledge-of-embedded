.. index:: ライフサイクル

.. _ライフサイクル:

ライフサイクル
==============
| バッファや処理のライフサイクルを意識する

概要
-----------
| デスクトップ環境で動作するアプリと異なり、組み込みでは常時ソフトが動き続けている。
| このため、初期化や解放と言った制御を自力で守るような構造にする必要がある。
| また、バッファが保存されているRAM領域はマイコン上にある為、当然マイコンの動作に影響を受ける。


.. code-block:: c
    :linenos:


    /* OS無しの場合 */
    typedef unsigned char uchar;

    uchar hoge;
    /* 動作開始時にmainが呼ばれる前に呼ばれる初期設定用関数 */
    void hot_start(void) {
        hoge = 0;
    }

    /* 動作中に常に呼ばれ続ける関数 */
    void main(void) {
        detect_hoge();
    }

    static void detect_hoge(void) {
        if( P0_1 == Low )
        hoge++;
    }

.. code-block:: c
    :linenos:

    /* OS有りの場合 */
    typedef unsigned char uchar;

    uchar hoge;
    /* 動作開始時にmainが呼ばれる前に呼ばれる初期設定用関数 */
    void hot_start(void) {
        hoge = 0;
    }

    /* 動作中にサービスが回ってくる関数 */
    void main(void) {
        hot_start();

        while(1) {
            /* 動作し続けるように無限ループになっている */
            detect_hoge();
        }
    }

    static void detect_hoge(void) {
        hoge++;
    }
