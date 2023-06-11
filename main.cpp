#include <stdio.h>
#include <math.h>
#include "portaudio.h"
#include "soundtouch/SoundTouch.h"
#include <string.h>

#define DEBUG
#define SAMPLE_RATE (44100)
#define PA_SAMPLE_TYPE paFloat32    // 浮動小数点型データ32bit浮動小数点
#define FRAMES_PER_BUFFER (32)

soundtouch::SoundTouch soundTouch;

typedef float SAMPLE;

void print_select () {
    printf("\n");
    printf("* Setting Option Change or Application End\n");
    printf("* Select Option And Input Option Name.\n\n");
    printf("* Option List\n");
    printf("> exit      : End Application.\n");
    printf("> *         : Start Voice Conversion!\n");
    printf("> default   : Set default Voice! and Start Voice Conversion!\n");
    printf("> default1  : Set default Voice! (No Library) and Start Voice Conversion\n");
    printf("> custom    : Custom Mode!\n\n");
    printf("> lady_A    : Set Lady_A Voice! and Start Voice Conversion!\n");
    printf("> man_A     : Set man_A Voice! and Start Voice Conversion!\n");
    printf("\n");
    printf("> ");
}

void print_set (
    float* tempo                // テンポ変更
,   float* tempo_ch             // テンポ変更（倍率）
,   float* pitch                // ピッチ倍率変更
,   float* pitchsemitone        // ピッチ半音変更
,   float* rate_ch              // 速度変更（倍率）
,   float* rate                 // 速度変更
,   unsigned int* aa_filter     // ノイズフィルタ
,   unsigned int* quick_seek    // クイックシーク
,   unsigned int* sequencems    // 内部バッファ長
,   unsigned int* seekwind      // シークウィンドウ長
,   unsigned int* overlap       // オーバーラップ長
) {
    printf ("[ 1]. soundTouch.setChannels                         (%d);\n",   2);
    printf ("[ 2]. soundTouch.setSampleRate                       (%u);\n",   SAMPLE_RATE);
    printf ("[ 3]. soundTouch.setTempo                            (%f);\n",   *tempo);
    printf ("[ 4]. soundTouch.setTempoChange                      (%f);\n",   *tempo_ch);
    printf ("[ 5]. soundTouch.setPitch                            (%f);\n",   *pitch);
    printf ("[ 6]. soundTouch.setPitchSemiTones                   (%f);\n",   *pitchsemitone);
    printf ("[ 7]. soundTouch.setRateChange                       (%f);\n",   *rate_ch);
    printf ("[ 8]. soundTouch.setRate                             (%f);\n",   *rate);
    printf ("[ 9]. soundTouch.setSetting(SETTING_USE_AA_FILTER,   %u);\n",    *aa_filter);
    printf ("[10]. soundTouch.setSetting(SETTING_USE_QUICKSEEK,   %u);\n",    *quick_seek);
    printf ("[11]. soundTouch.setSetting(SETTING_SEQUENCE_MS,     %u);\n",    *sequencems);
    printf ("[12]. soundTouch.setSetting(SETTING_SEEKWINDOW_MS,   %u);\n",    *seekwind);
    printf ("[13]. soundTouch.setSetting(SETTING_OVERLAP_MS,      %u);\n",    *overlap);
    printf ("\n");
}

void custom_set (
    float* tempo                // テンポ変更
,   float* tempo_ch             // テンポ変更（倍率）
,   float* pitch                // ピッチ倍率変更
,   float* pitchsemitone        // ピッチ半音変更
,   float* rate_ch              // 速度変更（倍率）
,   float* rate                 // 速度変更
,   unsigned int* aa_filter     // ノイズフィルタ
,   unsigned int* quick_seek    // クイックシーク
,   unsigned int* sequencems    // 内部バッファ長
,   unsigned int* seekwind      // シークウィンドウ長
,   unsigned int* overlap       // オーバーラップ長
) {
    char str[64];
    float fvalue;
    unsigned int uvalue;
    while (1) {
        // 要素の確認
        print_set(
            tempo
        ,   tempo_ch
        ,   pitch
        ,   pitchsemitone
        ,   rate_ch
        ,   rate
        ,   aa_filter
        ,   quick_seek
        ,   sequencems
        ,   seekwind
        ,   overlap
        );
        /* セットする項目を受け取る */
        printf("set value [3~13] or [exit]\n");
        printf("> ");
        scanf("%s", str);   // 入力待ち
        printf("\n");
        if (strcmp(str, "exit") == 0) {
            // パラメタセット終了
            printf("End Custom.\n");
            break;
        } else if (strcmp(str, "3") == 0) {
            printf("float setTempo = ");
            scanf("%f", &fvalue);
            printf("\n");
            printf("Input value is [ %f ]\n May I set this value?\n\n", fvalue);
            printf("Yes or No: Input [y] or [n]\n");
            scanf("%s", str);
            if  (strcmp(str, "y") == 0) *tempo = fvalue;
        } else if (strcmp(str, "4") == 0) {
            printf("float setTempoChange = ");
            scanf("%f", &fvalue);
            printf("\n");
            printf("Input value is [ %f ]\n May I set this value?\n\n", fvalue);
            printf("Yes or No: Input [y] or [n]\n");
            scanf("%s", str);
            if  (strcmp(str, "y") == 0) *tempo_ch = fvalue;
        } else if (strcmp(str, "5") == 0) {
            printf("float setPitch = ");
            scanf("%f", &fvalue);
            printf("\n");
            printf("Input value is [ %f ]\n May I set this value?\n\n", fvalue);
            printf("Yes or No: Input [y] or [n]\n");
            scanf("%s", str);
            if  (strcmp(str, "y") == 0) *pitch = fvalue;
        } else if (strcmp(str, "6") == 0) {
            printf("float setPitchSemiTones = ");
            scanf("%f", &fvalue);
            printf("\n");
            printf("Input value is [ %f ]\n May I set this value?\n\n", fvalue);
            printf("Yes or No: Input [y] or [n]\n");
            scanf("%s", str);
            if  (strcmp(str, "y") == 0) *pitchsemitone = fvalue;
        } else if (strcmp(str, "7") == 0) {
            printf("float setRateChange = ");
            scanf("%f", &fvalue);
            printf("\n");
            printf("Input value is [ %f ]\n May I set this value?\n\n", fvalue);
            printf("Yes or No: Input [y] or [n]\n");
            scanf("%s", str);
            if  (strcmp(str, "y") == 0) *rate_ch = fvalue;
        } else if (strcmp(str, "8") == 0) {
            printf("float setRate = ");
            scanf("%f", &fvalue);
            printf("\n");
            printf("Input value is [ %f ]\n May I set this value?\n\n", fvalue);
            printf("Yes or No: Input [y] or [n]\n");
            scanf("%s", str);
            if  (strcmp(str, "y") == 0) *rate = fvalue;
        } else if (strcmp(str, "9") == 0) {
            while (1) {
                printf("Select [0] or [1]\n");
                printf("unsigned int SETTING_USE_AA_FILTER = ");
                scanf("%u", &uvalue);
                if (uvalue == 0 || uvalue == 1) break;
                printf("\n");
            }
            printf("Input value is [ %u ]\n May I set this value?\n\n", uvalue);
            printf("Yes or No: Input [y] or [n]\n");
            scanf("%s", str);
            if  (strcmp(str, "y") == 0) *aa_filter = uvalue;
        } else if (strcmp(str, "10") == 0) {
            while (1) {
                printf("Select [0] or [1]\n");
                printf("unsigned int SETTING_USE_QUICKSEEK = ");
                scanf("%u", &uvalue);
                if (uvalue == 0 || uvalue == 1) break;
                printf("\n");
            }
            printf("Input value is [ %u ]\n May I set this value?\n\n", uvalue);
            printf("Yes or No: Input [y] or [n]\n");
            scanf("%s", str);
            if  (strcmp(str, "y") == 0) *quick_seek = uvalue;
        } else if (strcmp(str, "11") == 0) {
            printf("float SETTING_SEQUENCE_MS = ");
            scanf("%u", &uvalue);
            printf("\n");
            printf("Input value is [ %u ]\n May I set this value?\n\n", uvalue);
            printf("Yes or No: Input [y] or [n]\n");
            scanf("%s", str);
            if  (strcmp(str, "y") == 0) *sequencems = uvalue;
        } else if (strcmp(str, "12") == 0) {
            printf("float SETTING_SEEKWINDOW_MS = ");
            scanf("%u", &uvalue);
            printf("\n");
            printf("Input value is [ %u ]\n May I set this value?\n\n", uvalue);
            printf("Yes or No: Input [y] or [n]\n");
            scanf("%s", str);
            if  (strcmp(str, "y") == 0) *seekwind = uvalue;
        } else if (strcmp(str, "13") == 0) {
            printf("float SETTING_OVERLAP_MS = ");
            scanf("%u", &uvalue);
            printf("\n");
            printf("Input value is [ %u ]\n May I set this value?\n\n", uvalue);
            printf("Yes or No: Input [y] or [n]\n");
            scanf("%s", str);
            if  (strcmp(str, "y") == 0) *overlap = uvalue;
        } else {
            printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
            printf("!!  There is no such setting items!       !!\n");
            printf("!!  Please enter the setting items again! !!\n");
            printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
        }
    }
}

void select_mode (
    char *str
,   float* tempo                // テンポ変更
,   float* tempo_ch             // テンポ変更（倍率）
,   float* pitch                // ピッチ倍率変更
,   float* pitchsemitone        // ピッチ半音変更
,   float* rate_ch              // 速度変更（倍率）
,   float* rate                 // 速度変更
,   unsigned int* aa_filter     // ノイズフィルタ
,   unsigned int* quick_seek    // クイックシーク
,   unsigned int* sequencems    // 内部バッファ長
,   unsigned int* seekwind      // シークウィンドウ長
,   unsigned int* overlap       // オーバーラップ長
) {
    /* 条件分岐 */
    if (strcmp(str, "default") == 0) {
        *tempo           = 1.0f; // テンポ設定
        *tempo_ch        = 1.0f; // テンポ設定（倍率）
        *pitch           = 1.0f; // ピッチ設定
        *pitchsemitone   = 1.0f; // ピッチ半音変更
        *rate_ch         = 1.0f; // 速度変更（倍率）
        *rate            = 1.0f; // 速度変更
        *aa_filter       = 0;    // ノイズ除去（0/1,無効/有効）
        *quick_seek      = 0;    // クイックシーク
        *sequencems      = 32;   // 内部バッファ長
        *seekwind        = 20;   // シークウィンドウ長
        *overlap         = 8;    // オーバーラップ長
    } else if (strcmp(str, "lady_A") == 0) {
        *tempo           = 1.5f; // テンポ設定
        *tempo_ch        = 1.0f; // テンポ設定（倍率）
        *pitch           = 1.0f; // ピッチ設定
        *pitchsemitone   = 1.5f; // ピッチ半音変更
        *rate_ch         = 1.0f; // 速度変更（倍率）
        *rate            = 1.2f; // 速度変更
        *aa_filter       = 0;    // ノイズ除去（0/1,無効/有効）
        *quick_seek      = 0;    // クイックシーク
        *sequencems      = 32;   // 内部バッファ長
        *seekwind        = 20;   // シークウィンドウ長
        *overlap         = 8;    // オーバーラップ長
    } else if (strcmp(str, "man_A") == 0) {
        *tempo           = 1.2f; // テンポ設定
        *tempo_ch        = 0.0f; // テンポ設定（倍率）
        *pitch           = 1.2f; // ピッチ設定
        *pitchsemitone   = -4.0f;// ピッチ半音変更
        *rate_ch         = 1.0f; // 速度変更（倍率）
        *rate            = 1.0f; // 速度変更
        *aa_filter       = 0;    // ノイズ除去（0/1,無効/有効）
        *quick_seek      = 0;    // クイックシーク
        *sequencems      = 32;   // 内部バッファ長
        *seekwind        = 20;   // シークウィンドウ長
        *overlap         = 8;    // オーバーラップ長
    } else if (strcmp(str, "custom") == 0) {
        custom_set(
            tempo
        ,   tempo_ch
        ,   pitch
        ,   pitchsemitone
        ,   rate_ch
        ,   rate
        ,   aa_filter
        ,   quick_seek
        ,   sequencems
        ,   seekwind
        ,   overlap
        );
    } else {}
    /* パラメタ設定 */
    soundTouch.setChannels(2);                                  // 入力チャンネル数
    soundTouch.setSampleRate(SAMPLE_RATE);                      // サンプルレート44100 Hz
    soundTouch.setTempo(*tempo);                                // テンポ(速度)設定:直接指定:速度,ピッチに影響:(def:1)
    soundTouch.setTempoChange(*tempo_ch);                       // テンポ設定:変化率指定:相対的な変化量:(def:1)
    soundTouch.setPitch(*pitch);                                // ピッチ設定:ピッチの変更を倍率指定:ピッチの変化率を倍率指定:倍速の速さで再生され高低変化
    soundTouch.setPitchSemiTones(*pitchsemitone);               // ピッチ設定:ピッチの変更を半音単位指定:音の高さの変化量を半音数指定:正->高,負->低
    soundTouch.setRateChange(*rate_ch);                         // 再生速度変更:倍率指定:速度:ピッチや音質に影響しない(def:1)
    soundTouch.setRate(*rate);                                  // 再生速度指定:再生速度そのもの:ピッチや音質に影響(def:1)
    soundTouch.setSetting(SETTING_USE_AA_FILTER, *aa_filter);   // エイリアシングノイズ（0無効/１有効）除去
    soundTouch.setSetting(SETTING_USE_QUICKSEEK, *quick_seek);  // クイックシーク(0/1,無効/有効)音声の位置高速移動（品質犠牲）
    soundTouch.setSetting(SETTING_SEQUENCE_MS, *sequencems);    // 内部バッファ長（正の整数）小さい->処理遅延小リソース大
    soundTouch.setSetting(SETTING_SEEKWINDOW_MS, *seekwind);    // シークウィンドウ長（正の整数）大きい->精度向上,処理遅延増
    soundTouch.setSetting(SETTING_OVERLAP_MS, *overlap);        // オーバーラップ長（正の整数）大きい->滑らか/遅延,

    printf("\nnow : %s \n", str);
}

// コールバック関数
static int ioCallback(
    const void *inputBuffer                     // 入力バッファへのポインタ
,   void *outputBuffer                          // 出力バッファへのポインタ
,   unsigned long framesPerBuffer               // バッファあたりフレーム数
,   const PaStreamCallbackTimeInfo* timeInfo    // ストリームの現在の時刻
,   PaStreamCallbackFlags statusFlags           // ストリームの状態を示す型のビットマスク
,   void *userData                              // userData引数で渡された任意のユーザデータへのポインタ
) {
    SAMPLE *out = (SAMPLE*)outputBuffer;            // オーディオサンプルを取得するためSAMPLE型キャスト
    const SAMPLE *in = (const SAMPLE*)inputBuffer;  // オーディオサンプルを読み取るためSAMPE型キャスト
    unsigned int i;
    (void) timeInfo; /* Prevent unused variable warnings. */
    (void) statusFlags;
    (void) userData;

    /* inputをステレオにする */
    SAMPLE stereo_in[framesPerBuffer*2];
    for (i=0; i<framesPerBuffer; i++) {
        stereo_in[2*i] = in[i];
        stereo_in[2*i+1] = in[i];
    }
    /* 入力バッファからデータを読み取り */
    soundTouch.putSamples(stereo_in, framesPerBuffer);
    /* 出力バッファにデータを書き込む */
    soundTouch.receiveSamples(out, framesPerBuffer);

    // 処理が成功したかどうかチェック
    if (soundTouch.numSamples() == 0) {
        for (i=0; i<framesPerBuffer*2; i++) {
            out[i] = 0;
        }
    }
    // 入出力処理が継続される
    return paContinue;
}

static int ioCallback_default(
    const void *inputBuffer                     // 入力バッファへのポインタ
,   void *outputBuffer                          // 出力バッファへのポインタ
,   unsigned long framesPerBuffer               // バッファあたりフレーム数
,   const PaStreamCallbackTimeInfo* timeInfo    // ストリームの現在の時刻
,   PaStreamCallbackFlags statusFlags           // ストリームの状態を示す型のビットマスク
,   void *userData                              // userData引数で渡された任意のユーザデータへのポインタ
) {
    SAMPLE *out = (SAMPLE*)outputBuffer;            // オーディオサンプルを取得するためSAMPLE型キャスト
    const SAMPLE *in = (const SAMPLE*)inputBuffer;  // オーディオサンプルを読み取るためSAMPE型キャスト
    unsigned int i;

    if (inputBuffer == NULL) {
        for(i=0; i<framesPerBuffer; i++){
            out[i*2] = 0;
            out[i*2+1] = 0;    
        }
    } else {
        for (i=0; i<framesPerBuffer; i++) {
            out[i*2] = in[i];
            out[i*2+1] = in[i];
        }
    }
    // 入出力処理が継続される
    return paContinue;
}


int main(void) {
    /* ローカル変数宣言(初期設定) */
    float tempo             = 2.0f; // テンポ変更
    float tempo_ch          = 1.0f; // テンポ変更（倍率）
    float pitch             = 2.0f; // ピッチ倍率変更
    float pitchsemitone     = 4.0f; // ピッチ半音変更
    float rate_ch           = 1.0f; // 速度変更（倍率）
    float rate              = 1.0f; // 速度変更
    unsigned int aa_filter  = 0;    // ノイズフィルタ(0/1,無効/有効)
    unsigned int quick_seek = 0;    // クイックシーク(0/1,無効/有効)
    unsigned int sequencems = 32;   // 内部バッファ長
    unsigned int seekwind   = 20;   // シークウィンドウ長
    unsigned int overlap    = 4;    // オーバーラップ長

    // 入力デバイス、サンプリングレート、チャネル数を指定
    PaStreamParameters inputParameters;
    // 出力ストリームのパラメタ指定
    PaStreamParameters outputParameters;
    // PortAudioストリームを指定
    PaStream *stream;
    // PA_APIエラーコード格納
    PaError err;

    //PA_APIの初期化
    err = Pa_Initialize();
    if( err != paNoError ) {
        Pa_Terminate(); // PA_APIの終了
        return 1;
    }
    // デフォルト入力デバイス取得
    inputParameters.device = Pa_GetDefaultInputDevice();
    if (inputParameters.device == paNoDevice) {
        printf("Error: No default input device.\n");
        Pa_Terminate(); // PA_APIの終了
        return 1;
    }
    inputParameters.channelCount = 1; /* モノラルインプット */
    inputParameters.sampleFormat = PA_SAMPLE_TYPE;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo( inputParameters.device )->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = NULL;

    // デフォルト出力デバイス取得
    outputParameters.device = Pa_GetDefaultOutputDevice(); /* デフォルトアウトプットデバイス */
    if (outputParameters.device == paNoDevice) {
        printf("Error: No default output device.\n");
        Pa_Terminate(); // PA_APIの終了
        return 1;
    }

    outputParameters.channelCount = 2; /* ステレオアウトプット */
    outputParameters.sampleFormat = PA_SAMPLE_TYPE;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    char str[64];

    while (1) {
        print_select();     // オプション表示
        scanf("%s", str);   // 入力待ち
        printf("\n");
        if (strcmp(str, "exit") == 0){  // 処理終了
            printf("End Application.\n");
            break;
        } else if(strcmp(str, "default1") == 0) {
            // ストリームを開く
            err = Pa_OpenStream(
                &stream             // ストリーム情報格納（ストリームのアドレス）
            ,   &inputParameters    // 入力デバイスの設定を保持
            ,   &outputParameters   // 出力デバイスの設定を保持
            ,   SAMPLE_RATE         // サンプリング周波数
            ,   FRAMES_PER_BUFFER   // １回バッファリングあたりのフレーム数
            ,   0                   // ストリームオプション：0でデフォルト
            ,   ioCallback_default  // 音声の入出力に関するイベントが発生するたびに呼び出される
            ,   NULL                // コールバック関数に渡されるデータへのポインタ
            );
        } else {
            // 変換モードの決定とパラメタ設定
            select_mode(
                str
            ,   &tempo
            ,   &tempo_ch
            ,   &pitch
            ,   &pitchsemitone
            ,   &rate_ch
            ,   &rate
            ,   &aa_filter
            ,   &quick_seek
            ,   &sequencems
            ,   &seekwind
            ,   &overlap
            );
            printf("\n");

            // ストリームを開く
            err = Pa_OpenStream(
                &stream             // ストリーム情報格納（ストリームのアドレス）
            ,   &inputParameters    // 入力デバイスの設定を保持
            ,   &outputParameters   // 出力デバイスの設定を保持
            ,   SAMPLE_RATE         // サンプリング周波数
            ,   FRAMES_PER_BUFFER   // １回バッファリングあたりのフレーム数
            ,   0                   // ストリームオプション：0でデフォルト
            ,   ioCallback          // 音声の入出力に関するイベントが発生するたびに呼び出される
            ,   NULL                // コールバック関数に渡されるデータへのポインタ
            );
        }
        if( err != paNoError ) {
            Pa_Terminate();
            return 1;
        }
        err = Pa_StartStream( stream );
        if( err != paNoError ) {
            Pa_Terminate();
            return 1;
        }

        /* 終了指示待機 */
        printf("Hit [e]+Enter to Stop Voice Change.\n");
        printf("> ");
        while(getchar() != 'e');
        printf("\n");

        err = Pa_StopStream( stream );
        if( err != paNoError ) {
            Pa_Terminate();
            printf("Pa_StopStream Error\n");
            return 1;
        }
        err = Pa_CloseStream( stream );
        if( err != paNoError ) {
            Pa_Terminate();
            printf("Pa_CloseStream Error\n");
            return 1;
        }
    }
    printf("Finished\n");
    Pa_Terminate(); // PA_API終了

    return 0;
}
