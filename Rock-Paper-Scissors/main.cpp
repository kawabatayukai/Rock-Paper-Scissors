#include"DxLib.h"
#include"SceneManager.h"
#include"Scene_GameMain.h"
#include"Scene_Title.h"
#include"Jangeki_Player.h"
#include"SoundSystem.h"
#include "Scne_TitleInterval.h"
#include"KeyManager.h"
#include"FPS_Controll.h"

/*　　変数　　*/
int g_OldKey;      // 前回の入力キー 
int g_NowKey;      // 今回の入力キー 
int g_KeyFlg;      // 入力キー情報


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    SetOutApplicationLogValidFlag(FALSE);	// ログテキスト出力しない
    SetMainWindowText("JANKEN WORLD");       //タイトルを設定
    ChangeWindowMode(TRUE);                //ウィンドウモードで起動
    //SetWindowSize(1280, 720);
    SetGraphMode(1280, 720, 32);           //ウィンドウサイズを設定
    SetWindowIconID(123);                  //ウィンドウのアイコン
    if (DxLib_Init() == -1) return -1;     //DXライブラリの初期化処理
    SetDrawScreen(DX_SCREEN_BACK);         //描画先画面を裏にする

    //シーンマネージャー     　　　　　　　　　　　　　　　タイトルを設定
    SceneManager sceneMng(dynamic_cast<AbstractScene*>(new Scne_TitleInterval()));

    //じゃん撃画像
    Jangeki_Player::LoadJanImage();
    Jangeki_Base::Input_Images();

    //サウンド
    SoundSystem::LoadSounds_SE();
    //SoundSystem::LoadSounds_BGM();

    //FPS固定用
    FPS_Controll fps_ctrl(60);

    //ESCキーまたはコントローラーBackボタンで終了
    while (ProcessMessage() == 0 && !KeyManager::OnKeyClicked(KEY_INPUT_ESCAPE) && !KeyManager::OnPadClicked(PAD_INPUT_7))
    {
        // 画面の初期化 
        ClearDrawScreen();

        sceneMng.Update();     //更新
        sceneMng.Draw();       //描画

        //シーンの変更   ENDの場合　nullptr
        if (sceneMng.ChangeScene() == nullptr)
        {
            DxLib_End();  //DxLib終了処理
            return 0;
        }

        //FPS固定処理
        fps_ctrl.Get();
        fps_ctrl.Wait();
        //fps_ctrl.Disp();
        //DrawFormatString(0, 50, 0xff0000, "%f", GetFPS());

        //裏画面の内容を表画面に反映
        ScreenFlip();
    }

    DxLib_End();		    // ＤＸライブラリ使用の終了処理

    return 0;				// ソフトの終了 
}