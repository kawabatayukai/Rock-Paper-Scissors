#pragma once
#include "AbstractScene.h"
#include"SortSave.h"

class Scene_Ranking : public AbstractScene
{
public:
	Scene_Ranking(/*const RankingData* Data*/);

	/*�R���X�g���N�^*/
	virtual ~Scene_Ranking() {};

	//�X�V
	void Update()override;

	//�`��
	void Draw()const override;

	//�V�[���̕ύX����
	AbstractScene* ChangeScene()override;

private:
	int backimage = 0;            //�w�i�摜
	//RankingData dataRanking[RANKING_DATA];  // �����L���O�f�[�^�ϐ��錾
};

