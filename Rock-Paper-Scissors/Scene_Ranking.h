#pragma once
#include "AbstractScene.h"
#include"SortSave.h"

class Scene_Ranking : public AbstractScene
{
public:


	Scene_Ranking(/*const RankingData* Data*/);

	//�f�X�g���N�^
	 ~Scene_Ranking();

	//�X�V
	void Update()override;

	//�`��
	void Draw()const override;

	//�V�[���̕ύX����
	AbstractScene* ChangeScene()override;

private:
	int backimage = 0;            //�w�i�摜
	int ranking_font;
	//RankingData dataRanking[RANKING_DATA_COLUMN];  // �����L���O�f�[�^�ϐ��錾
	int r_bgm;
};

