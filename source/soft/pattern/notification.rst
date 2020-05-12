.. index:: 状態通知

.. _状態通知:

状態通知
============================
| 複数のマイコンを連携して一つのシステムを構築する場合、
| 当然ある程度の情報をマイコン間でやり取りをする。
| その際に、通信していいかどうかの判断の為に相手の状態を知る必要がある。
| よくある失敗例として、相手の起動完了を待たずに通信を行ってしまった例である。

.. seqdiag::
    :desctable:

    seqdiag {
        activation=none;
        === 失敗例 ===
        Power; MicomA; MicomB;
        Power -> MicomA[label = "Power ON"];
        Power -> MicomB[label = "Power ON"];
        MicomA -> MicomA[label = "起動完了"];
        MicomA -> MicomB[failed,label = "メッセージ送信"];
        MicomB -> MicomB[label = "起動完了"];
    }

.. seqdiag::
    :desctable:

    seqdiag {
        activation=none;
        === 成功例 ===
        Power; MicomA; MicomB;
        Power -> MicomA[label = "Power ON"];
        Power -> MicomB[label = "Power ON"];
        MicomA -> MicomA[label = "起動完了"];
        MicomB -> MicomB[label = "起動完了"];
        MicomA <- MicomB[label = "起動完了通知"];
        MicomA -> MicomB[label = "メッセージ送信"];
    }

| よくある対策は以下の二つである。

* 絶対に起動が遅いことが確実な方が先に通信を送る。
* :ref:`LowActive` で通知する。
    | 大抵こちらの方が確実なのでこちらが使用される印象が強い。

