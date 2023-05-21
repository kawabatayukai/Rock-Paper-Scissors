#pragma once
#include"AbstractScene.h"
#include"Player.h"
#include"Floor.h"

//�w���v�V�[��
class HelpScene : public AbstractScene
{	
public:
	//�R���X�g���N�^
	HelpScene();

	~HelpScene();     //�f�X�g���N�^

	void Update() override;      //�X�V
	void Draw() const override;  //�`��

	AbstractScene* ChangeScene() override;   //�V�[���̕ύX

private:
	int HelpImage = 0;      //�摜
	int image_back;         //�w�i
	static int font_help;   //�t�H���g

	Player* obj_player;     //�v���C���[
	Floor** obj_floor;      //��

	int helpTime;           //����
	int help_bgm;            //�w���v���BGM
};