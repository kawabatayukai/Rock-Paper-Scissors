#include "Scene_Ranking.h"
#include"Scene_InputRanking.h"
#include <DxLib.h>
#include"Scene_Title.h"
#include "KeyManager.h"
<<<<<<< HEAD
=======
#include"SortSave.h"
#include"Scene_InputRanking.h"
>>>>>>> parent of bfaa0a9 (繝ｩ繝ｳ繧ｭ繝ｳ繧ｰ蜃ｦ逅�縺ｮ螟画峩霑ｽ蜉)

int g_WaitTime = 0;

//更新
void Scene_Ranking::Update()
{

}

//描画
void Scene_Ranking::Draw() const
{
	//ランキング一覧を表示
	SetFontSize(30);
	for (int i = 0; i < 10; i++)
	{
<<<<<<< HEAD
=======
		//DrawFormatString(80, 170 + i * 25, 0xFFFFFF, "%2d   %10s  %10d", dataRanking[i].rank, dataRanking[i].name, dataRanking[i].score);
>>>>>>> parent of bfaa0a9 (繝ｩ繝ｳ繧ｭ繝ｳ繧ｰ蜃ｦ逅�縺ｮ螟画峩霑ｽ蜉)
		DrawFormatString(80, 170 + i * 25, 0xFFFFFF, "%2d   %10s  %10d", inputRanking.getRankingData(i).no, inputRanking.getRankingData(i).name, inputRanking.getRankingData(i).score);
	}

	SetFontSize(100);
	//文字の表示(点滅)
	if (++g_WaitTime < 30) {
		SetFontSize(24);
		DrawString(150, 450, "--  Press A ボタン  --", 0xFF0000);
	}
	else if (g_WaitTime > 60) {
		g_WaitTime = 0;
	}

}

//シーンの変更処理
AbstractScene* Scene_Ranking::ChangeScene()
{
	if (KeyManager::OnPadClicked(PAD_INPUT_A) == true)//KEY_INPUT_RETURN
	{
		return dynamic_cast<AbstractScene*> (new TitleScene());
	}
	return this;
}