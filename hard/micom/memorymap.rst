.. index:: Memory Map

.. _Memory Map:

Memory Map
=============
| マイコンにはそのビット数で把握できるMemory Mapが存在する。
| マイコンでアクセスできる領域は大別して以下の通りである。
| それ以外は予約領域である。

.. index:: ROM
    single: Memory Map; ROM

.. _ROM:

ROM
------
| Read Only Memoryの略
| ソースコードやテーブルがここに置かれる。
| 大抵 :ref:`FLASH` で構成されている。

.. index:: RAM
    single: Memory Map; RAM

.. _RAM:

RAM
------
| Random Access Memoryの略
| バッファがここに置かれる。
| 電源が落とされるとデータは消失するか不定になるため、使い始める際には必ず初期化する。
| マイコンの低電力消費モードを使用する場合は、使用しているRAMがデータを保持するかどうかを確認する事
| ここで次回も使用したいデータは :ref:`EEPROM` 等に保存する。
