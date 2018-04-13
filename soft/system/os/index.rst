.. index:: OS

.. _OS:

OS
==============
| 組み込み開発を行う場合、OSの動きまでを意識した開発をする必要がある。
| ここでは、なぜOSが必要なのかとそのOSの動きについて解説する。


なぜOSが必要なのか
------------------
| まず、組み込みで動作するシステムとは電源を入れてから落とすまでずっと動き続けるものである。
| その間に検知、演算、描画、制御を並行してこなす必要がある。
| 例えばC言語でこちらの入力を受け付け応答を返すプログラムは以下のようにかける。

.. code-block:: c

    int main(void)
    {
        int i;
        scanf("%d", &i);
        printf("入力は%dです\n", i);
        retuen 0;
    }

| だが、これでは入力を一つ受け付けたら動作が完了してしまう。
| これを永続的に行うようにするには単純に考えて無限ループを使ってこう書く。
| 終了したければCtrl+Cでも押せばいいだろう。

.. code-block:: c

    int main(void)
    {
        int i;
        while(1) {
            scanf("%d", &i);
            printf("入力は%dです\n", i);
        }
        retuen 0;
    }

| しかしこれでは入力を待っている間に他の事が出来ない。
| 例えば入力を待っている間に5秒毎に時間の経過を表示する場合どうすればよいだろうか。
| とりあえずこれで動く。

.. code-block:: c
    :linenos:

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <time.h>
    #include <conio.h>

    #define FALSE 0
    #define TRUE 1
    #define BS 8
    #define LF 10
    #define CR 13
    #define NUL 0

    time_t past;
    typedef struct {
        int length;			/* 文字列長保存 */
        char line[BUFSIZ];	/* 入力文字列 */
        char last;			/* 最後の入力キー */
    }input_t;

    input_t input;
    int HasInput(void)
    {
        char c = NUL;
        int result = FALSE;
        if(kbhit()) {
            c = getch();
            /* 押しっぱなし回避の為前回押されたキーと照合 */
            if(c != input.last) {
                if(c == BS) {
                    /* BackSpaceなら一文字削除 */
                    if(input.length > 0){
                        input.line[--input.length] = NUL;
                    }
                } else if(c == LF || c == CR) {
                    /* Enterが押されたら文字列確定 */
                    result = TRUE;
                } else {
                    /* それ以外なら文字列に追加 */
                    input.line[input.length++] = c;
                    if(input.length == BUFSIZ - 1){
                        /* 上限まで来たら一旦取り込み */
                        result = TRUE;
                    }
                }
            }
        }
        /* 最後に入力されたキーを記憶 */
        input.last = c;
        return result;
    }

    int IsTimeout(double span)
    {
        int result;
        time_t tmp = time(NULL);
        result = (span <= difftime(tmp, past));
        if(result){
            past = tmp;
        }
        return result;
    }

    int main(void)
    {
        double span = 5;
        memset(&input, 0, sizeof(input_t));
        past = time(NULL);
        while(1) {
            /* Stdin(キーボード入力)の監視 */
            if(HasInput()){
                printf("RECV=[%s]\n",input.line);
                memset(&input, 0, sizeof(input_t));
            }
            if(IsTimeout(span)) {
                printf("past %.0lf[s]\n", span);
            }
        }
        return 0;
    }

| 面倒なのでmain関数だけ見てもらえれば分かり易いが、
| 無限ループ内で実行したい全てをぐるぐる回す必要がある。
| この時、どれか一つの関数で処理が止まってしまえば他のものが動かない。
| これの開発を簡便化するために土台として使用されるのがOSである。

OSの役割
-------------
| OSは以下のような役割を果たす。

* 登録されているタスクに適切にサービスを提供する
    必要な機能をタスク単位のモジュールとして分割し、相互に連携させ全体としてのシステムを構築させる
* タスク間のメッセージIFを提供する。
    タスク間のデータのやり取りを行う為に、メッセージという共通規格を提供し各タスクの構造を統一する。
* タスクのイベントを管理する。
    | タスクが動作するかどうかの起因となるのがこのイベントである。
    | このイベントが立つことによりOSはそのタスクを起動する。

* 共通のタイマシステムを管理し、タスクに提供する。
    | タスクが受け持つ仕事の中にはタイマを利用するものが多く存在する。
    | 一定時間後に行う、もしくは一定の周期で繰り返すというものである。
    | その時間はタスク単体では正確にできない為、OSが時間の経過を観測しタスクへと提供する。
    | タスクからタイマを使用する場合は以下のような方法をとる

    * 一定時間のsleepをOSに申請し、その時間が過ぎたらサービスを返してもらう
    * 一定周期でイベントを発行してもらいその回数をカウントする事で必要な期間を測定する

OSの有無によるシステム構造の違い
--------------------------------
| OSがあろうがなかろうが、その上に複数の :ref:`タスク` があり、
| 相互にメッセージを送り合いながら動作していることは変わらない。
| しかし実際の動きが大きく異なる為、その差分をここに挙げる。

.. csv-table:: **OSの有無によるタスク動作の違い**
    :file: os.csv
    :encoding: 'shift_jis'
    :header-rows: 1
    :stub-columns: 1
    :widths: 10, 30,30

.. [1] そのため、通信等といった長時間必要な処理は割り込みで動作させ、OSもどきとタスクには影響を極力出さないようにする。
.. [2] タスク実行中に途中で動作を止められるため、どうしても止められたくない処理をする場合はディスパッチ禁止状態にすること。
