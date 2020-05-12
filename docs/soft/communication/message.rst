メッセージ
==================
| マイコン間や、マイコン内のタスク間に於いての円滑なメッセージのやり取りには一定のフォーマットが必要である。
| そのフォーマットについて解説する。

概要
------
| 例えば、スイッチが押されている状態を通信で伝達する場合を考える。
| 押されている状態を1、押されていない状態を0とする。
| スイッチが一つしかないならば単に1と0のみを送ればいい。
| 受信側もそれしか来ないと分かっていれば意味を理解できる。
| しかし、複数のスイッチがあった場合、受信した1がどのスイッチのものかが判別できない。
| その為、データに定型のヘッダを付け、ヘッダ内に何のデータかを示すことで相互理解を行う。
| 構造の例を以下に示す。

.. code-block:: c

    /* sizeof(external_message_t) <= INT_MESSAGE_MAX_LENGTH */
    typedef struct {
        unsigned char id;       /* メッセージ種別   */
        unsigned char length;   /* メッセージ長     */
        unsigned char from;     /* メッセージ送信元 */
        unsigned char to;       /* メッセージ送信先 */
        unsigned char data[INT_MESSAGE_MAX_LENGTH];
    } internal_message_t;

    typedef struct {
        unsigned char id;
        unsigned char length;
        unsigned char data[EXT_MESSAGE_MAX_LENGTH]
    } external_message_t;

+-------------------------+
|メッセージ構造           |
+========+================+
|Header  |メッセージID    |
+        +----------------+
|        |メッセージ長    |
+        +----------------+
|        |その他必要な情報|
+--------+----------------+
|Body    |メッセージ内容  |
+--------+----------------+

.. csv-table:: メッセージ構造
    :header-rows: 1

    Index, 内部メッセージ, 外部メッセージ
    1, ID, | -
    2, Length, | -
    3, Body, ID
    4, Body, Length
    5, Body, Body
    ..., ..., ...

メッセージの種類
------------------
| メッセージには大別して以下の二つがある。
| これが基本であり全てである。

**外部メッセージ**
    マイコンの外へ通信する。

**内部メッセージ**
    マイコン内のタスクへデータを転送する。

メッセージの流れ
-------------------
| タスク間で行う通信とマイコン外への通信のイメージを以下に示す。

.. seqdiag::
    :desctable:
    :scale: 50

    seqdiag {
        activation = none;
        Task_a; Task_b; Task_MSGMNG; Task_UARTIF; Other;

        === 内部通信 ===
        Task_a -> Task_b[label = "ID     : 内部データ1\nLength : 3\nBody   : 内容"];
        === 外部送信 ===
        Task_a -> Task_UARTIF;
            Task_UARTIF -> Other;
        === 外部受信 ===
        Task_UARTIF <- Other;
        Task_MSGMNG <- Task_UARTIF;
        Task_a <- Task_MSGMNG;

        Task_a  [description = "適当なタスクA"];
        Task_b  [description = "適当なタスクB"];
        Task_MSGMNG  [description = "メッセージ振り分けタスク"];
        Task_UARTIF  [description = "UART通信制御タスク"];
        Other  [description = "マイコン外通信相手"];


    }
