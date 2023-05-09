#pragma once
#include"EnemyBase.h"
#include"Jangeki_Base.h"
#include"Jangeki_reflection.h"
#include"Player.h"
//9�X�e�[�W�@�G�L����
class Enemy_09 : public EnemyBase
{
public:
	//�R���X�g���N�^ ���W�E������ݒ�
	Enemy_09(float x, float y, Jan_Type type);

	~Enemy_09();                     //�f�X�g���N�^

	void Update() override;          //�X�V
	void Draw() const override;      //�`��

	void Update_Jangeki() override;  //����񌂐����E�X�V

	void MoveEnmey_09();
	void Jan_360degrees();
	void Jan_40degrees();
	void SpecialMoveEnmey();

	void HP(); 

	void frameUP();
	void frameDown();

	bool Getflg();
	void Tflg();
	void Fflg();
	int Rand();

	bool Spflg = true;  //����s���t���O
	bool animflg = false;	//�A�j���[�V�����t���O
	bool ranimflg = false; //���˃A�j���[�V����
	bool Ranimflg = false;	//�čĐ��p


	Jangeki_Reflection* reflection;


private:
	/********************   �W�����v�֌W   ********************/

	float old_x = 0;          //�O��̈ʒuX
	float old_y = 0;          //�O��̈ʒuY
	float y_add = 0;          //��������
	float g_add = 1.0f;       //�d�͉����x

	/**********************************************************/

	int teleport = 300;
	int frame_count = 0;       //����񌂔��˗p
	int interval = 0;
	int Rimage;
	int image;
	int janFrame = 75;
	int count = 0;
	int SPcount = 0;
	
	bool rflg = false; //���˗p
	
	int animtimer = 0;

	
	int jan_count;
	
	Player* type;
	//�A�j���[�V�����p�摜�ϐ�
	int img_teleport[15];	//�Đ�
	int img_teleport2[15];	//�t�Đ�
	float before_x = 0;
	float before_y = 0;
	int anim_count = 0;  //�A�j���[�V������

	int refanim[15];

};


