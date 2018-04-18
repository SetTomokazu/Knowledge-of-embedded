.. index:: Pointer, ポインタ

.. _ポインタ:

Pointer(ポインタ)
============================
| ポインタは組み込みでなんだかんだ使用される。
| その扱いと特性について再度理解しておく。

.. index:: NULL

.. _NULL:

NULL
============================
| NULLポインタであるが、これを組み込みで使用する場合少々厄介なことになる
| NULLポインタと言うが、これはポインタの指し示すアドレスが0であるだけである。
| そして、マイコンのアドレス空間によっては、アドレス0に変数や関数が普通に存在する場合がある。
| その場合、正常なのにNULLチェックで弾かれる可能性があるため、注意しよう。

.. warning:: NULLポインタであるアドレス0番地がアドレスとして正常の場合がある


.. index:: Function Pointer, 関数ポインタ

.. _関数ポインタ:

Function Pointer(関数ポインタ)
====================================
| なんだかんだ使用されるのがこの関数ポインタである。
| 規模が大きい開発になると、理解や制御を簡単にするために一定の構造化を行うのは常套手段である。
| 以下に :ref:`Task` のインターフェースを構造化した際の記述例を示す。

:download:`プロジェクト一式Download </sample_source/function_pointer.zip>`

.. literalinclude:: /sample_source/function_pointer/Common.h
    :caption: Common.h
    :language: c
    :encoding: shiftjis
    :linenos:

.. literalinclude:: /sample_source/function_pointer/TaskA.h
    :caption: TaskA.h
    :language: c
    :encoding: shiftjis
    :linenos:

.. literalinclude:: /sample_source/function_pointer/TaskA.c
    :caption: TaskA.c
    :language: c
    :encoding: shiftjis
    :linenos:

.. literalinclude:: /sample_source/function_pointer/Scheduler.c
    :caption: Scheduler.c
    :language: c
    :encoding: shiftjis
    :linenos:

