#pragma once
#include"EnemyBase.h"

//1�X�e�[�W�@�G�L����
class Enemy_01 : public EnemyBase
{
public:
	//�R���X�g���N�^ ���W�E������ݒ�
	Enemy_01(float x, float y, Jan_Type type);

	~Enemy_01();                     //�f�X�g���N�^

	void Update() override;          //�X�V
	void Draw() const override;      //�`��

	void Update_Jangeki() override;  //����񌂐����E�X�V


	//�W�����v�i�W�����v�́j
	void Jump_Enemy(float g_add = -21.5f);

/*---------------------------- �p�^�[���s�� --------------------------------------*/

	//�s������
	void Move_Controller();

	//���E�ړ�
	void Action01_LR(float& target_x, float& target_y);

	//�W�����v�ő����n��
	void Action02_Jump(float& target_x, float& target_y);

	//��������������
	void Action03_Floor_LR(float& target_x, float& target_y);

	//�����������~���
	void Action04_GetOff_Floor_LEFT(float& target_x, float& target_y);

	//�v���C���[�ڊ|���Ă���񌂂𔭎˂���
	void Fire_JanTakeAim(const float& player_x, const float& player_y);

/*--------------------------------------------------------------------------------*/

private:
	/********************   �W�����v�֌W   ********************/

	float old_x = 0;          //�O��̈ʒuX
	float old_y = 0;          //�O��̈ʒuY
	float y_add = 0;          //��������
	float g_add = 1.0f;       //�d�͉����x

	/**********************************************************/

	int jan_count;           //����񌂔z��̋�v�f�擪�ԍ�������i��ނȂ��j

	//�s��
	enum class ACT_TYPE
	{
		NOT_ACT,             //�s���Ȃ�
		 
		LEFT_TO_RIGHT,       //���E�ړ�
		CROSS_FLOOR,         //�����n��
		LEFT_TO_RIGHT_FLOOR, //�����ō��E�ɉ���
	};
	ACT_TYPE Now_Action;

	int current_action;        //���݂̃A�N�V����
};


