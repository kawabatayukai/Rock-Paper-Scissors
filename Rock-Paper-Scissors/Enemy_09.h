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
	void SpecialMoveEnmey();
	void Create_Homing(int jan_count, float x, float y, float r, float speed, Jan_Type type);

	void HP(); 

	void frameUP();
	void frameDown();

	bool Getflg();
	void Tflg();
	void Fflg();


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
	bool rflg = false; //���˗p
	bool Spflg = true; 
	
	Player* type;

};


