#include "Enemy_09.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"

//�R���X�g���N�^�@   ���N���X�̃R���X�g���N�^���Ăԁ@�@�@�@ ���@���@���@�@�@����    ����
Enemy_09::Enemy_09(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
{
	speed = 7.0f;
	dir = 1;
	hp = 100;

	image = LoadGraph("images/tyokitest.png");

	Init_Jangeki();       //����񌂂�p��

}

//�f�X�g���N�^
Enemy_09::~Enemy_09()
{

}


//�X�V
void Enemy_09::Update()
{
	//����񌂍X�V�E����
	Update_Jangeki();
	MoveEnmey_09();

	//if (x + (w / 2) == (1280 - 20))
	//{
	//	dir = -1;
	//}
	//else if (x - (w / 2) == (20))
	//{
	//	dir = 1;
	//}

	//x += dir * speed;

	/********************   �W�����v�֌W   ********************/

	//if (land_flg == true && GetRand(30) == 3)    //GetRand(30) == 3�@�̂Ƃ��낪�W�����v�̏���
	//{
    //	g_add = -21.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
	//	land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
	//}

	y_add = (y - old_y) + g_add;  //����̗���������ݒ�

	//�������x�̐���
	if (y_add > static_cast<float>(MAX_LENGTH)) y_add = static_cast<float>(MAX_LENGTH);

	old_y = y;                    //1�t���[���O�̂����W
	y += y_add;                   //���������������W�ɉ��Z����
	g_add = _GRAVITY;              //�d�͉����x������������

	/**********************************************************/

}

//�`��
void Enemy_09::Draw() const
{
	//���S����`��
	DrawRotaGraphF(x, y, 1, 0, image, TRUE);

	//����񌂕`��
	Draw_Jangeki();

	//�e�X�g
	if (hp > 0) DrawFormatString((int)(x - 100), (int)(y - 100), 0xffffff, "HP : %d", hp);
	else DrawString((int)(x - 100), (int)(y - 100), "death!", 0xffffff);

}

//����񌂐����E�X�V
void Enemy_09::Update_Jangeki()
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
		float radius = 35.5f;   //���a
		float speed = -3.0f;     //�X�s�[�h

		//�����_���ȑ����𐶐�
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));


		//����
		if (frame_count % 120 == 0 /*|| Hit_Jangeki()==true*/) obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, speed, type);
	}
}
void Enemy_09::MoveEnmey_09() {
	interval++;
	if (land_flg == true && /*GetRand(100) == 5 &&*/ interval % 120 == 0) {
		switch (GetRand(7))
		{
		case 0:
			x = 160;
			y = 480;
			break;
		case 1:
			x = 360;
			y = 305;
			break;
		case 2:
			x = 160;
			y = 130;
			break;
		case 3:
			x = 1110;
			y = 480;
			break;
		case 4:
			x = 910;
			y = 305;
			break;
		case 5:
			x = 1110;
			y = 130;
			break;
		case 6:
			x = 620;
			y = 400;
			break;
		case 7:
			x = 620;
			y = 80;
			break;
		}
	}

}