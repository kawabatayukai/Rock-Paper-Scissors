#pragma once
#include"AbstractScene.h"

//�^�C�g���V�[��
class TitleScene : public AbstractScene
{
private:

	int TitleImage = 0;
	int T_selectnum = 0;

	int font_title;   //�t�H���g�n���h��
public:

	//�R���X�g���N�^
	TitleScene();

	~TitleScene();     //�f�X�g���N�^

	void Update() override;      //�X�V
	void Draw() const override;  //�`��

	AbstractScene* ChangeScene() override;   //�V�[���̕ύX
};