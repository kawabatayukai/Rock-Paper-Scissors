#include"DxLib.h"
#include"SceneManager.h"
#include"Scene_GameMain.h"
#include"Scene_Title.h"
#include"Jangeki_Player.h"

/*　　変数　　*/
int g_OldKey;      // 前回の入力キー 
int g_NowKey;      // 今回の入力キー 
int g_KeyFlg;      // 入力キー情報


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    SetOutApplicationLogValidFlag(FALSE);	// ログテキスト出力しない
    SetMainWindowText("Neko");       //タイトルを設定
    ChangeWindowMode(TRUE);                //ウィンドウモードで起動
    //SetWindowSize(1280, 720);
    SetGraphMode(1280, 720, 32);           //ウィンドウサイズを設定
    if (DxLib_Init() == -1) return -1;     //DXライブラリの初期化処理
    SetDrawScreen(DX_SCREEN_BACK);         //描画先画面を裏にする

    //シーンマネージャー     　　　　　　　　　　　　　　　タイトルを設定
    SceneManager sceneMng(dynamic_cast<AbstractScene*>(new TitleScene()));

    //じゃん撃画像
    Jangeki_Player::LoadJanImage();
    Jangeki_Base::Input_Images();

    //ESCキーまたはコントローラーBackボタンで終了
    while (ProcessMessage() == 0 && !(g_NowKey & PAD_INPUT_9) && !(g_NowKey & PAD_INPUT_7))
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

        //裏画面の内容を表画面に反映
        ScreenFlip();
    }

    DxLib_End();		    // ＤＸライブラリ使用の終了処理

    return 0;				// ソフトの終了 
}