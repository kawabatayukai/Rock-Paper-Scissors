#pragma once
#include "CharaBase.h"
#include"Effect_Player.h"
#include"Effect_ChangePlayer.h"
#include"Sound_Jangeki.h"
#include"Sound_Player.h"

//�v���C���[�̏��
enum class PLAYER_STATE
{
	ALIVE,     //�����Ă���
	DEATH,     //����
	DEATH_END, //���񂾁����o�I���
};

//�v���C���[�N���X�@CharaBase���p��
class Player : public CharaBase
{
public:
	//�R���X�g���N�^
	Player(float x, float y);

	~Player();                       //�f�X�g���N�^

	void Update() override;          //�X�V
	void Draw() const override;      //�`��

	void Update_Jangeki() override;  //����񌂐����E�X�V

	//�z�[�~���O����ꐶ��
	void Create_Homing(int jan_count, float x, float y,float r, float speed, Jan_Type type);

	//�G�̍��W���擾
	void SetEnemyLocation( const float x, const float y);

	int Get_OldX();                   //old_x�̎擾�֐�
	int Get_X();                      //x�̎擾
	int Get_OldY();                   //old_y�̎擾�֐�
	int Get_Y();                      //y�̎擾

	/*�摜�̕ύX�擾*/
	void PlayerSwitch();

	/*�摜�̓���ύX*/
	void PlayerChangeMoveimg();

	/*�r�̕`��E����*/
	void ArmDrawMove() const;

	/*���̕`��E����*/
	void HeadDrawMove() const;

	/*�ڂ̕`��E����*/
	void EyeDrawMove() const;

	/*�̂̕`��E����*/
	void BodyDrawMove() const;

	//�v���C���[��UI�`��
	void PlayerDrawUI(int hp) const;

	//HP�񕜁i���� : �񕜗ʁj
	void Recover_HP(const unsigned int recovery);

	//�����擾 0:���@1:�E
	int GetDirection() const { return dir; }

	//�v���C���[�����S���Ă��邩
	bool IsDeathPlayer() const;

	void setName(int i, char name[11]);

	//SE�Đ�
	void Play_SE();
	//SE����(jan)
	void Create_SEJan();
	//SE����(player)
	void Create_SEPlayer(const SE_PLAYER& se_type);

private:
	/********************   �W�����v�֌W   ********************/

	float old_x = 0;          //�O��̈ʒuX
	float old_y = 0;          //�O��̈ʒuY
	float y_add = 0;          //��������
	float g_add = 1.0f;       //�d�͉����x

	/**********************************************************/

	int image[3][10]; //�摜
	int image_death;          //���S��

	int head_Image[4];        //��

	int eye_ImageR[2];          //��
	int eye_ImageL[2];          //��

	int armL_Image[3];        //����
	int armR_Image[3];        //�E��

	int player_Image;         //�摜�̔z��ێ�

	int playerGetMove;        //�ړ��ێ�

	int playerCount;          //�摜�̃t���[���J�E���g

	int playerCount2;          //�摜�̃t���[���J�E���g

	int playerChange_Image;   //�摜�ύX

	int pCount;               //�Ō�̉摜

	Jan_Type select_JanType;  //�I������"��"

	double jan_angle = 0;     //����񌂂̊p�x
	int jan_interval = 0;     //����񌂔��ˊԊu

	float enemy_x = 0;        //�G�̍��W��
	float enemy_y = 0;        //�G�̍��W��

	int image_JanType[3];     //�I������񌂉摜
	int image_setsumei;       //��������p�@����
	int image_set_circle;     //�~
	int image_set_LTRT;       //"LTRT"
	int image_set_GPT;
	int hpImage;

	int Prev_recoveryScore;   //�O��񕜂������̃X�R�A
	PLAYER_STATE player_state;

	//�����i���E�̂݁j
	enum class DIRECTION
	{
		LEFT,
		RIGHT,
		UP,
		DOWN,
	};

	//�G�t�F�N�g(��)
	Effect_Player* obj_effect;
	//�G�t�F�N�g(����)
	Effect_ChangePlayer* obj_effectchange;
	//SE
	Sound_Jangeki** obj_se;
	Sound_Player** obj_pse;

	static int name_font; //���O�E�t�H���g
};