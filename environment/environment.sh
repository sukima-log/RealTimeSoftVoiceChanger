#bin/sh

CURRENT=$(cd $(dirname $0);pwd)
echo $CURRENT

# 処理を一時停止 -> Enterキーで進む
echo "======================================================"
echo "comment : change directory!!"
echo "comment : If you want to proceed, press the Enter key!!"
echo "======================================================"
read Wait

# environmentに移動
cd $CURRENT

pwd

# 処理を一時停止 -> Enterキーで進む
echo "======================================================"
echo "comment : MinGW install!!"
echo "comment : If you want to proceed, press the Enter key!!"
echo "======================================================"
read Wait

sudo apt-get update

# wget install
sudo apt-get install gpg wget -y

# MinGW install
sudo apt install mingw-w64 mingw-w64-tools -y

# version確認
x86_64-w64-mingw32-gcc --version


# 処理を一時停止 -> Enterキーで進む
echo "======================================================"
echo "comment : CMake install!!"
echo "comment : If you want to proceed, press the Enter key!!"
echo "======================================================"
read Wait

sudo apt-get update

# CMake install
sudo apt install cmake -y

# version確認
cmake --version


# 処理を一時停止 -> Enterキーで進む
echo "======================================================"
echo "comment : PortAudio install!!"
echo "comment : If you want to proceed, press the Enter key!!"
echo "======================================================"
read Wait

sudo apt-get update

# PortAudio install
mkdir portaudio_build
cd portaudio_build

sudo apt-get install build-essential -y


git clone https://github.com/PortAudio/portaudio

# ビルド用ディレクトリ
cd portaudio
mkdir build
cd build

cmake -DCMAKE_INSTALL_PREFIX=/usr/x86_64-w64-mingw32 \
    -DCMAKE_TOOLCHAIN_FILE=$CURRENT/../toolchain.cmake \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_SHARED_LIBS=ON ..

make

sudo make install


# 処理を一時停止 -> Enterキーで進む
echo "======================================================"
echo "comment : SoundTouch install!!"
echo "comment : If you want to proceed, press the Enter key!!"
echo "======================================================"
read Wait

sudo apt-get update
sudo apt-get install autoconf automake libtool pkg-config build-essential g++ -y

# SoundTouch install
cd $CURRENT
mkdir soundtouch_build
cd soundtouch_build

wget https://www.surina.net/soundtouch/soundtouch-2.3.0.tar.gz
tar zxvf soundtouch-2.3.0.tar.gz
cd soundtouch-2.3.0

echo "LT_INIT([win32-dll],[-no-undefined])">>configure.ac

./bootstrap

autoconf --install

./configure --host=x86_64-w64-mingw32 --prefix=/usr/x86_64-w64-mingw32

echo "libSoundTouch_la_LDFLAGS = -no-undefined">>Makefile.am

automake --add-missing

make

sudo make install


# cmake -DCMAKE_INSTALL_PREFIX=/usr/x86_64-w64-mingw32 \
#     -DCMAKE_TOOLCHAIN_FILE=$CURRENT/../toolchain.cmake \
#     -DCMAKE_BUILD_TYPE=Release \
#     -DBUILD_SHARED_LIBS=ON .

# cmake --build .

# cmake --install .

# make

# sudo make install
