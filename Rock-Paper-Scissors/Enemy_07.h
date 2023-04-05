#pragma once
#include"EnemyBase.h"
#include"Player.h"

//7�X�e�[�W�@�G�L����
class Enemy_07 : public EnemyBase
{
public:
	//�R���X�g���N�^ ���W�E������ݒ�
	Enemy_07(float x, float y, Jan_Type type);

	~Enemy_07();                     //�f�X�g���N�^

	void Update() override;          //�X�V
	void Draw() const override;      //�`��

	void Update_Jangeki() override;  //����񌂐����E�X�V

	//�W�����v�i�W�����v�́j
	void Jump_Enemy(float g_add = -21.5f);

	void Change_JanType();           //�����_���ɑ����ω�

/*---------------------------- �p�^�[���łȂ��s�� --------------------------------------*/

	void Move_Controller();          //�s������

	//�v���C���[�������O�� 
	void Move_ON_RING(float& target_x, float& target_y);                            

	//�v���C���[������i�󒆁j��
	void Move_ON_FLOOR(float& target_x, float& target_y);

	//�v���C���[�������2�b�ȏ�
	void Move_ON_FLOOR_LURK(float& target_x, float& target_y);

	//�v���C���[����O
	void Move_OUT_RING(float& target_x, float& target_y);

	//�v���C���[�̏󋵂��擾
	void CheckPlayerState(const Player* player);


	//�s�����������i�ڐG����񂯂�I����@�p�j
	void Init_MoveAndAction();

	//�i�_�C�u���Ɂj�����蔻����Ƃ�Ȃ�  true : �_�C�u���B�����蔻����Ƃ�Ȃ� 
	bool Is_Diving_Collision();

	//�i�_�C�u���Ɂj�ڐG����񂯂�����Ȃ�  true : �_�C�u���B�ڐG����񂯂�����Ȃ�
	bool Is_Diving_TouchJanken();   

/*--------------------------------------------------------------------------------------*/

	void Jan_360degrees();  //360�x����
	void Jan_Vertical(int count, float rad, float speed, Jan_Type type);    //�c�ɂ������񔭎ˁi����j

private:
	/********************   �W�����v�֌W   ********************/

	float old_x = 0;          //�O��̈ʒuX
	float old_y = 0;          //�O��̈ʒuY
	float y_add = 0;          //��������
	float g_add = 1.0f;       //�d�͉����x

	/**********************************************************/

	const float init_speed;    //�����X�s�[�h�i�Œ�j
	double draw_angle;         //�`��p�x

	int jan_count;             //Update_Jangeki() �� ����񌂔z��̋�v�f�̔z��ԍ�������

	//���g���猩���v���C���[�̏��
	enum class PLAYER_STATE
	{
		ON_RING,         //�����O��
		ON_FLOOR,        //�����
		ON_FLOOR_LURK,   //�����Ő���ł���
		OUT_RING,        //�����O�O

		DO_NOT,          //���f���Ȃ�
	};
	PLAYER_STATE Player_State;

	//�s���̎��
	enum class ACT_TYPE
	{
		NO_ACT,             //�s���Ȃ�
		
		LEFT_TO_RIGHT,      //������E�i�ŏI�I�ɉE�j
		RIGHT_TO_LEFT,      //�E���獶�i�ŏI�I�ɍ��j
		CLIMB_CORNER_LEFT,  //�R�[�i�[�ɏ��i���j
		CLIMB_CORNER_RIGHT, //�R�[�i�[�ɏ��i�E�j
		CROSS_FLOOR_LEFT,   //�����n��i������E�j
		CROSS_FLOOR_RIGHT,  //�����n��i�E���獶�j
		DIVE_OUT_LEFT,      //��O�փ_�C�u�i���j
		DIVE_OUT_RIGHT,     //��O�փ_�C�u�i�E�j
	};
	ACT_TYPE Now_Action;    //���s����Action�i�s���j
	ACT_TYPE Pre_Action;    //�P�O��Action�i�s���j

//------------------------ �e�X�g ------------------------

	unsigned int frame_count;  //�t���[���J�E���g�ϐ�

	int* image_NowState;       //���ݕ`�悷�ׂ��摜
	int image_running[9];      //�摜�i����j
	int current_index = 0;
};


