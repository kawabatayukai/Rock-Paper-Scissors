#pragma once
#include"AbstractScene.h"

//�^�C�g���V�[��
class TitleScene : public AbstractScene
{
public:

	//�R���X�g���N�^
	TitleScene();

	~TitleScene();     //�f�X�g���N�^

	void Update() override;      //�X�V
	void Draw() const override;  //�`��

	AbstractScene* ChangeScene() override;   //�V�[���̕ύX
private:

	int TitleImage = 0;
	int TitleBgm;
	int SelectSE;
	int ClickSE;
	int T_selectnum = 0;

	static int font_title;   //�t�H���g�n���h��
	int bgm;

	int image_Eye;
	int frame;
};