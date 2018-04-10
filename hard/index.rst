ハード
==================
マイコン上でソフトが動くとはどういう事なのか。
.exeを叩けばそれっぽく動くのはWindowsがよしなにやってくれてるお蔭である。
組み込みではどこまでしなければならないのか。


立ち上げ
------------------

 | マイコン開発を行う際、Windows上で動作させる時の様にいきなりソースを記述しても動かない。
 | まずはマイコン自体の設定を行う必要がある。

 .. toctree::
    :maxdepth: 2

    micon_setup

機能紹介
---------------

 .. toctree::
    :glob:
    :maxdepth: 2

    peripherals/index
    interrupt/index


用語集
---------------

 .. toctree::
    :maxdepth: 2

    glossary
