#pragma once
#include "AbstractScene.h"
class Scene_RankingTime :
    public AbstractScene
{
public:
	Scene_RankingTime();

	/*�R���X�g���N�^*/
	virtual ~Scene_RankingTime() {};

	//�X�V
	void Update()override;

	//�`��
	void Draw()const override;

	//�V�[���̕ύX����
	AbstractScene* ChangeScene()override;

private:
	int backimage = 0;            //�w�i�摜
	int ranking_font;
	
};

