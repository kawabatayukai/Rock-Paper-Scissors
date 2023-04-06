#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"
#include "Enemy_Cannon.h"

//�R���X�g���N�^�@   ���N���X�̃R���X�g���N�^���Ăԁ@�@�@�@ ���@���@���@�@�@����    ����
Enemy_Cannon::Enemy_Cannon(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
{
	image = LoadGraph("images/tyokitest.png");

	Init_Jangeki();       //����񌂂�p��

	Enemy_image = LoadGraph("images/stage08/Stage8_image.png");
}

//�f�X�g���N�^2
Enemy_Cannon::~Enemy_Cannon()
{

}


//�X�V
void Enemy_Cannon::Update()
{
	//����񌂍X�V�E����
	Update_Jangeki();
}
//�`��
void Enemy_Cannon::Draw() const
{
	//���S����`��
	DrawRotaGraphF(x, y, 4.f, 0, Enemy_image, TRUE);
	

	//����񌂕`��
	Draw_Jangeki();
}

//����񌂐����E�X�V
void Enemy_Cannon::Update_Jangeki()
{
	int jan_count;

	//����񌂔z����ЂƂ���
	for (jan_count = 0; jan_count < JANGEKI_MAX; jan_count++)
	{
		//�z��� jan_count �Ԗڂ�nullptr�i��v�f�j�Ȃ炻��ȏ㏈�����Ȃ�
		if (obj_jangeki[jan_count] == nullptr) break;

		obj_jangeki[jan_count]->Update();

		//��ʊO�ō폜����
		if (obj_jangeki[jan_count]->CheckScreenOut() == true)
		{
			DeleteJangeki(jan_count);
			jan_count--;
		}
	}

	/*********************** ���� ���ˁE���� ���� ***********************/
	frame_count++;

	//�z��̋�v�f
	if (jan_count < JANGEKI_MAX && obj_jangeki[jan_count] == nullptr)
	{
		float radius = 45.5f;   //���a
		float speed = -13.0f;     //�X�s�[�h

		//�����_���ȑ����𐶐�
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));


		//����
		if (frame_count % 120 == 0) obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, speed, type);
	}

}