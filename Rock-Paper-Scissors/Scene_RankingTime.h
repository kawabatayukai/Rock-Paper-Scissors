#pragma once
#include "AbstractScene.h"
class Scene_RankingTime :
    public AbstractScene
{
public:

	/*�R���X�g���N�^*/
	Scene_RankingTime();

	//�f�X�g���N�^
	~Scene_RankingTime();

	//�X�V
	void Update()override;

	//�`��
	void Draw()const override;

	//�V�[���̕ύX����
	AbstractScene* ChangeScene()override;

private:
	int backimage = 0;            //�w�i�摜
	int ranking_font;
	int r_bgm;
};

