文字を入れると音が鳴る for WINDOWS
==================================
DTMF符号的な
0-9, A-D, *, #で音が鳴るよ

必要
----
- mingwとかcygwinとか
- libwinmm.a

ビルド
------
    ./configure
	make

使い方
------
	./release.exe
	Input [0-9A-D#\*]+ > 0123

ライセンス
----------
Modified BSD (3-clause)

既知の問題
----------
- 全くテストされてない
- 単一環境のみ動作確認
