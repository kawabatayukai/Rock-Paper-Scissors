#pragma once
#include "AbstractScene.h"
class Scene_Ranking_GameLevel :
    public AbstractScene
{
private:

	int TitleImage = 0;
	int T_selectnum = 0;

	static int font_title;   //�t�H���g�n���h��
public:

	//�R���X�g���N�^
	Scene_Ranking_GameLevel();

	~Scene_Ranking_GameLevel();     //�f�X�g���N�^

	void Update() override;      //�X�V
	void Draw() const override;  //�`��

	AbstractScene* ChangeScene() override;   //�V�[���̕ύX
};

