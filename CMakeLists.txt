cmake_minimum_required(VERSION 3.10)

project(myproject)

set(CMAKE_SYSTEM_NAME Windows)

set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
set(CMAKE_SYSTEM_PROCESSOR x86_64)


add_executable(myexe main.cpp)

target_link_libraries(myexe portaudio SoundTouch)

# 実行ファイルと依存するライブラリを含むフォルダを指定する
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install")
install(TARGETS myexe RUNTIME DESTINATION "${CMAKE_INSTALL_PREFIX}")
# ここでMinGWのライブラリがある場所にしておかないと、.dllじゃなくて.soファイルが入る
install(DIRECTORY "/usr/x86_64-w64-mingw32/" DESTINATION "${CMAKE_INSTALL_PREFIX}")

