#pragma once
#include"AbstractScene.h"
#include"Player.h"
#include"Floor.h"

//�Q�[�����C��
class GameMainScene : public AbstractScene
{
public:
	//�R���X�g���N�^()
	GameMainScene();

	~GameMainScene();                      //�f�X�g���N�^     

	void Update() override;                //�X�V

	void Draw() const override;            //�`��

	AbstractScene* ChangeScene() override; //�V�[���̕ύX

private:
	Player* obj_player;
	Floor** obj_floor;

	//�Z���N�g�ԍ�
	int select_num = 0;

	//AbstractScene** Stage_Select;    //0�`2�X�e�[�W�ւ̃|�C���^
};