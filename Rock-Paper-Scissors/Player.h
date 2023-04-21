#pragma once
#include "CharaBase.h"

//�v���C���[�N���X�@CharaBase���p��
class Player : public CharaBase
{
public:
	//�R���X�g���N�^
	Player(float x, float y);
	Player(const Player& player);

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

	//�v���C���[��UI�`��
	void PlayerDrawUI(int hp) const;

	//HP�񕜁i���� : �񕜗ʁj
	void Recover_HP(const unsigned int recovery);

	//�����擾 0:���@1:�E
	int GetDirection() const { return dir; }

private:
	/********************   �W�����v�֌W   ********************/

	float old_x = 0;          //�O��̈ʒuX
	float old_y = 0;          //�O��̈ʒuY
	float y_add = 0;          //��������
	float g_add = 1.0f;       //�d�͉����x

	/**********************************************************/

	int image[10]; //�摜
	int image_Jamp[2];

	int head_Image[1];

	int armL_Image[3];
	int armR_Image[3];

	int player_Image; //�摜�̔z��ێ�

	int playerGetMove;   //�ړ��ێ�

	int playerCount; //�摜�̃t���[���J�E���g

	int playerChange_Image; //�摜�ύX

	int pCount; //�Ō�̉摜

	Jan_Type select_JanType;  //�I������"��"

	double jan_angle = 0;     //����񌂂̊p�x
	int jan_interval = 0;     //����񌂔��ˊԊu

	float enemy_x = 0;        //�G�̍��W��
	float enemy_y = 0;        //�G�̍��W��

	int image_JanType[3];     //�I������񌂉摜
	int image_setsumei;       //��������p�@����
	int hpImage;

	//�����i���E�̂݁j
	enum class DIRECTION
	{
		LEFT,
		RIGHT,
	};

	int ui_font;  //ui�p�t�H���g�n���h��
};