#pragma once
#include "AbstractScene.h"
class Scene_Title_GameLevel :
    public AbstractScene
{
private:
	int T_selectnum = 0;

	//�����摜
	int ex_image;
	int normal_image;
	int image_back;

	static int font_title;   //�t�H���g�n���h��
public:

	//�R���X�g���N�^
	Scene_Title_GameLevel();

	~Scene_Title_GameLevel();     //�f�X�g���N�^

	void Update() override;      //�X�V
	void Draw() const override;  //�`��

	AbstractScene* ChangeScene() override;   //�V�[���̕ύX
};

