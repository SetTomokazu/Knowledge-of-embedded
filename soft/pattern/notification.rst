.. index:: 状態通知

.. _状態通知:

状態通知
============================
| 複数のマイコンを連携して一つのシステムを構築する場合、
| 当然ある程度の情報をマイコン間でやり取りをする。
| その際に、通信していいかどうかの判断の為に相手の状態を知る必要がある。

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

