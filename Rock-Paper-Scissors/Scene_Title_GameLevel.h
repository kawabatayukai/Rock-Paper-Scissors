#pragma once
#include "AbstractScene.h"
class Scene_Title_GameLevel :
    public AbstractScene
{
private:

	int TitleImage = 0;
	int T_selectnum = 0;

	int font_title;   //�t�H���g�n���h��
	int font_debug;   //�f�o�b�O�p�t�H���g
public:

	//�R���X�g���N�^
	Scene_Title_GameLevel();

	~Scene_Title_GameLevel();     //�f�X�g���N�^

	void Update() override;      //�X�V
	void Draw() const override;  //�`��

	AbstractScene* ChangeScene() override;   //�V�[���̕ύX
};

