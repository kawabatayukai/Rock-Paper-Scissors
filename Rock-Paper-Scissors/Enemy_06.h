#pragma once
#include"EnemyBase.h"

//6�X�e�[�W�@�G�L����
class Enemy_06 : public EnemyBase
{
public:
	//�R���X�g���N�^ ���W�E������ݒ�
	Enemy_06(float x, float y, Jan_Type type);

	~Enemy_06();                     //�f�X�g���N�^

	void Update() override;          //�X�V
	void Draw() const override;      //�`��

	void Update_Jangeki() override;  //����񌂐����E�X�V

	int Get_OldY();                   //old_y�̎擾�֐�
	int Get_Y();                      //y�̎擾

private:
	/********************   �W�����v�֌W   ********************/

	float old_x = 0;          //�O��̈ʒuX
	float old_y = 0;          //�O��̈ʒuY
	float y_add = 0;          //��������
	float g_add = 1.0f;       //�d�͉����x

	bool jump_flg = false;    //�W�����v�p�t���O�@�@�W�����v������:true   �W�����v���Ȃ�:false

	/**********************************************************/

	int frame_count = 0;       //����񌂔��˗p
};


