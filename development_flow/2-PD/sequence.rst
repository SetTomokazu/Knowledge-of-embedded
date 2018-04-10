####################
シーケンス図
####################


シーケンス図
================
| 何かと作成する図の一つ

概要
----------
| データや処理の流れを模式的に表すためによく使用される。
| 母体の解析中や設計時の概略図作成用に多用する。

目的
------------
| 簡略に各タスクや関数の繋がりを示したり、データのやり取りを図示するために使用する。
| どこで何をやりつつ動作しているのか、追加や変更はどこに挿入するのかを示すために非常に重宝する。


作成方法
--------------
| 大体Excelの図を使用して作成する事になる。
| 運が良ければ現在見ているSphinxやPlantUMLを使用することが可能かもしれない。
| ただし、図の自由度という意味では好き勝手にオブジェクトが配置できるExcelに軍配が上がる為、
| 詳細な分岐を考えずに簡略にデータの流れなどを示したい時にSphinxやPlantUMLを使用するとよい。
|
| 以下の図はPCと基盤を接続し、基盤上のEEPROMに保存されているデータを要求した際のフローのサンプルである。

.. seqdiag::
    :desctable:

    seqdiag {
        PC; Micom_PCIF; Micom_MSGMNG; Micom_I2CIF; EEPROM;

        PC => Micom_PCIF [label = "データ要求", return = "データ応答"] {
            Micom_PCIF => Micom_MSGMNG[label = "受信データ転送", return ="送信データ転送"] {
                Micom_MSGMNG => Micom_I2CIF[label = "EEPROMデータRead要求", return = "EEPROMRead結果応答"] {
                    Micom_I2CIF =>EEPROM [label = "データRead"];
                }
            }
        }

        PC              [description = "マイコンと接続しているPC"];
        Micom_PCIF      [description = "マイコン内のUART通信監理タスク"];
        Micom_MSGMNG    [description = "マイコン内のメッセージ処理タスク"];
        Micom_I2CIF     [description = "マイコン内のI2C通信監理タスク"];
        EEPROM          [description = "データを保存しているEEPROM"];
    }

