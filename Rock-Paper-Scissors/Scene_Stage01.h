#pragma once
#include "AbstractScene.h"
#include"Enemy_01.h"
#include"Stage_Base.h"
#include"Player.h"
#include"Floor.h"

#define STAGE_01_FLOOR 5         //���E�ǂ̍��v��

//0�X�e�[�W
class Scene_Stage01 : public Stage_Base
{
public:
	//�R���X�g���N�^
	Scene_Stage01(const Player* player = nullptr);

	~Scene_Stage01();                      //�f�X�g���N�^

	void Update() override;                //�X�V

	void Draw() const override;            //�`��

	AbstractScene* ChangeScene() override; //�V�[���̕ύX

	void Draw_Janken() const;              //����񂯂�`��

	//�`���[�g���A��
private:

	void NextTutorial();            //���̑����

	bool CheckMoveLR();             //���E�ړ����m�F����

private:
	Enemy_01* obj_enemy;            //�G

	
	int font_tut;                   //�`���[�g���A���p�t�H���g
	int frame_count;                //���Ԃ��J�E���g

	//�F
	int blue;
	int red;
	int brack;
	int white;
	int green;


	//�`���[�g���A���̒i�K
	enum class TUTORIAL_STATE
	{
		START_TUTORIAL,  //�`���[�g���A���J�n

		PLAYER_MOVE,     //�v���C���[�̍��E�ړ����m�F
		PLAYER_JUMP,     //�v���C���[�̃W�����v���m�F
		PLAYER_AIMING,   //�v���C���[�̏Ə����m�F

		TOUCH_JANKEN,    //�ڐG����񂯂�
	};
	TUTORIAL_STATE Now_Tut_State;    //���݂̃`���[�g���A���̏󋵂�ێ�
};

