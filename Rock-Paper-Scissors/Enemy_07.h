#pragma once
#include"EnemyBase.h"
#include"Player.h"

//�s���p�^�[��07�p
struct Pattern_07
{
	int moveflag;       //0:�����Ȃ��@1:����
	float location_x;   //�ڕW���W��
	float location_y;   //�ڕW���W��


	int next_index;     //���̔z��(�p�^�[��)�ԍ�
};

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

	void Move_Pattern();             //�s���p�^�[���ɉ������s��
	
/*---------------------------- �p�^�[���łȂ��s�� --------------------------------------*/

	void Move_Controller();         //�s������

	//�v���C���[�������O�� 
	void Move_ON_RING(float& target_x, float& target_y);                            

	//�v���C���[�̏󋵂��擾
	void CheckPlayerState(const Player* player);

/*--------------------------------------------------------------------------------------*/

	void Jan_360degrees(int count, float rad, float speed, Jan_Type type);  //360�x���ˁi�K�E�j
	void Jan_Vertical(int count, float rad, float speed, Jan_Type type);    //�c�ɂ������񔭎ˁi����j

private:
	/********************   �W�����v�֌W   ********************/

	float old_x = 0;          //�O��̈ʒuX
	float old_y = 0;          //�O��̈ʒuY
	float y_add = 0;          //��������
	float g_add = 1.0f;       //�d�͉����x

	/**********************************************************/

	int frame_count = 0;       //����񌂔��˗p

	Pattern_07 moveinfo[20];   //�s���p�^�[��
	short current = 0;         //���݂̃p�^�[���z��Y��

	//���g���猩���v���C���[�̏��
	enum class PLAYER_STATE
	{
		ON_RING,         //�����O��
		DO_NOT,          //���f���Ȃ�
	};
	PLAYER_STATE Player_State;

	//�s���̎��
	enum class ACT_TYPE
	{
		NO_ACT,           //�s���Ȃ�
		
		LEFT_TO_RIGHT,    //������E�i�ŏI�I�ɉE�j
		RIGHT_TO_LEFT,    //�E���獶�i�ŏI�I�ɍ��j
	};
	ACT_TYPE Now_Action;  //���s���̍s��

//------------------------ �e�X�g ------------------------


};


