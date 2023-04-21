#pragma once
#include"EnemyBase.h"

//�s���p�^�[��03�p
struct Pattern_03 {

	int moveflg; //0:����,1:�����Ȃ�
	float location_x; //�ڎw���Ă�����Wx
	float location_y; //�ڎw���Ă�����Wy
	int next_index; //���z��̃p�^�[���̔ԍ�
	int enemywaitTime;//�G�l�~�[�̑҂�����
	int jumpflg; //�W�����v���邩���Ȃ��� //0:����@//1:���Ȃ�
	


};

//3�X�e�[�W�@�G�L����
class Enemy_03 : public EnemyBase
{
public:
	//�R���X�g���N�^ ���W�E������ݒ�
	Enemy_03(float x, float y, Jan_Type type);

	~Enemy_03();                     //�f�X�g���N�^

	void Update() override;          //�X�V
	void Draw() const override;    //�`��

	void Update_Jangeki() override;  //����񌂐����E�X�V

	void Move_Pattern();//�����̃p�^�[��

	int GetWaitTime()const;//�҂����Ԃ̎擾

	void ChangeDir(float enemy_x);//�����̐؂�ւ�

	float Get_OldY() const { return old_y; } //Y���W�̎擾

	//void MoveRunAway(float enemy_x, float enemy_y,int player_x,int player_y);//

	//void EnemyHP();

private:
	/********************   �W�����v�֌W   ********************/

	//float old_x = 0; 

	//�O��̈ʒuX
	float old_x = 0;    //�O��̈ʒuX
	float old_y = 0;	//�O��̈ʒuY
	float y_add = 0;     //��������  
	float g_add = 1.0f;//�d�͉����x
	

	//�񋓑̃X�e�[�W3
	enum class ENEMY_STATE
	{
		STOP,
		LEFTMOVE,
		RIGHTMOVE,
		JUMP,
	};
	ENEMY_STATE enemy_state = ENEMY_STATE::STOP;
	

	//�񋓑̃X�e�[�W3
	/*enum class ENEMY_STATE1
	{
		STOP1,
		LEFTMOVE1,
		RIGHTMOVE1,
		JUMP1,
	};
	ENEMY_STATE1 enemy_state1 = ENEMY_STATE1::STOP1;*/



	/**********************************************************/
	int frame_count ;       //����񌂔��˗p

	int waitcount ;//�҂����ԃJ�E���g

	Pattern_03 moveinfo[40]; //�s���p�^�[��50��
	short current ; //���݂̃p�^�[���z��Y��


	int frame_count_anim = 0;       //�G�̃A�j���[�V�����p
	int frame_count_anim1 = 0;       //�G�̃A�j���[�V����1�p


	int enemyimage[6];  //���S�̎��̉摜
	int enemyimage1[6]; //�ϋv�l1�̎��̉摜
	int enemyimage2[6]; //�ϋv�l2�̎��̉摜
	int enemyimage3[6]; //�ϋv�l3�̎��̉摜
	int enemyimage4[6]; //���ꂩ���̎��̉摜

	int* now_image;//���݂̉摜���擾

	//int enemyimageMirror[6];//�G�摜���]
	int currentindex_st03 = 0;
	int currentindex1_st03 = 0;
	/*int screenWidth = 0;
	int screenHeight = 0;*/
	
};


