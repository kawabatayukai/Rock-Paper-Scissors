#pragma once

class FPS_Controll
{
public:
    FPS_Controll(float RefreshRate = 60.0f, int UpdateTime = 800);

    void Wait();     //待ち時間の計算
    float Get();     //FPS値の計算
    void Disp();     //描画処理

private:
    int frame_time;  //1フレームの時間(ミリ秒)
    int wait_time;   //待ち時間
    int last_time;   //最後に取得した時間と
    int now_time;    //今の時間
    float count;     //フレームのカウント
    float fps;       //表示するしたFPS値
    int update_time; //表示値を更新する時間
    int last_update; //最後に表示値を更新した時間

    //描画関係の変数
    int disp_x, disp_y;

    //初期化
    void Init(float RefreshRate, int UpdateTime);
};