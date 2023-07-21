#!/bin/sh

# 実行用ディレクトリ作成
mkdir build
cd build

if $# > 1 ; then
    cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake -DCMAKE_BUILD_TYPE=Debug ..
else
    # buildディレクトリ内に入り、cmakeで自動ビルド
    cmake -DCMAKE_TOOLCHAIN_FILE=../toolchain.cmake -DCMAKE_BUILD_TYPE=Release ..
fi

# makefileができるので、実行ファイルを作成する
make

# 実行バイナリに必要な動的ライブラリをCmakeLink.txt記述にしたがってインストール
make install

# Windows側にMinGWをインストールしていない場合向け
cp /usr/lib/gcc/x86_64-w64-mingw32/*posix/libgcc_s_seh-1.dll ./install/bin/
cp /usr/lib/gcc/x86_64-w64-mingw32/*posix/libstdc++-6.dll ./install/bin/
cp /usr/x86_64-w64-mingw32/lib/libwinpthread-1.dll ./install/bin/

# bin以下にアプリを移動
# cp ./myexe.exe ./install/bin/

# Windows環境にファイルをコピー
# cp ./install/bin/ 'Windows任意フォルダ' -r
