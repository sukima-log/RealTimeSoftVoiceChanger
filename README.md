# RealTimeSoftVoiceChanger

# 実行方法


以下、スクリプト[compile.sh]を実行することで手順4、`make install`まで自動実行

<hr>

1. 実行用のディレクトリを作る<br>
　`mkdir build`<br>
　`cd build`

2. buildディレクトリ内に入り、cmakeで自動ビルドする<br>
　`cmake -DCMAKE_TOOLCHAIN_FILE=~/toolchain.cmake -DCMAKE_BUILD_TYPE=Release ..`<br>


3. makefileができるので、実行ファイルを作成する<br>
　`make`<br>



4. 実行バイナリに必要な動的ライブラリをCMakeLink.txtの記述にしたがって自動的にとってくる<br>
　`make install`<br>

5. /install/以下のbinディレクトリに[.dll]ファイルなどの[.exe]ファイルの実行に必要な動的ライブラリが入る。<br>


6. 実行ファイルを/install/bin以下に移動させて、Windows側のフォルダにbinごと移動させる<br>

7. Windows側で/binフォルダに入り、コマンドプロンプトを立ち上げて実行ファイルを実行する。<br/>
　※本来は、対象ライブラリの動的ライブラリファイル「.dll」と実行ファイル「.exe」さえあれば動作可能


# 環境の初期化

スクリプト[clean.sh]を実行で「compile.sh」で作成した/bin以下削除して初期化
