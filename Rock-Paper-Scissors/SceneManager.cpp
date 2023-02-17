#include "SceneManager.h"
#include"KeyManager.h"

//更新
void SceneManager::Update()
{
    //現在シーンのアップデートを実行
    mScene->Update();

    //キーボードのアップデートを実行
    KeyManager::Update();
}


//現在のシーンの Draw(描画を行う関数)のみを実行
void SceneManager::Draw() const
{
    //const はメンバ変数の変更を拒否
    mScene->Draw();
}

//シーンの変更処理
AbstractScene* SceneManager::ChangeScene()
{
    //現在のシーンのシーン変更を実行
    AbstractScene* NextScene = mScene->ChangeScene();

    //次のシーンが現在のシーンと異なる場合、次のシーンに切り替える
    if (NextScene != mScene)
    {
        delete mScene;        //現在のシーンを削除
        mScene = NextScene;   //次のシーンに切り替える
    }

    //新たなシーンを返す
    return NextScene;
}