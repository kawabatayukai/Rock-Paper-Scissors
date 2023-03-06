#include "Enemy_02.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"

//�R���X�g���N�^�@   ���N���X�̃R���X�g���N�^���Ăԁ@�@�@�@ ���@���@���@�@�@����    ����
Enemy_02::Enemy_02(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
{
	speed = 7.0f;
	dir = 1;
	hp = 100;

	image = LoadGraph("images/stage02/junp4.png");

	Init_Jangeki();       //����񌂂�p��

}

//�f�X�g���N�^
Enemy_02::~Enemy_02()
{

}


//�X�V
void Enemy_02::Update()
{
	//����񌂍X�V�E����
	Update_Jangeki();

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

	if (jump_cnt < 1)
	{
		if (GetRand(1) == 1)  //������jump_flg��true�ɂ���
		{
			jump_flg = true;
		}

		if (land_flg == true && jump_flg == true)    //jump_flg���W�����v�̏���
		{
			//g_add = -21.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
			land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
			jump_flg = false;  //�W�����v�p�t���O�̃��Z�b�g
			jump_cnt++;
		}
	}

	if (jump_cnt >= 1 && direction_flg == false)
	{

		x = x - 5;
		if (x < 100)
		{
			image = LoadGraph("images/stage02/junp2.png");
			jump_cnt = 0;
			direction_flg = true;
		}
		
		if (land_flg == true && GetRand(1) == 1)    //GetRand(30) == 3�@�̂Ƃ��낪�W�����v�̏���
		{
			g_add = -25.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
			land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
			
		}
		
	}

	else if (jump_cnt >= 1 && direction_flg == true)
	{
		x = x + 5;
		if (x > 1180)
		{
			image = LoadGraph("images/stage02/junp4.png");
			jump_cnt = 0;
			direction_flg = false;
		}
		if (land_flg == true && GetRand(1) == 1)    //GetRand(30) == 3�@�̂Ƃ��낪�W�����v�̏���
		{
			g_add = -25.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
			land_flg = false;  //�n�ʂɂ��Ă��Ȃ�

		}
		
	}

	
 
	y_add = (y - old_y) + g_add;  //����̗���������ݒ�
	
	//�������x�̐���
	if (y_add > static_cast<float>(MAX_LENGTH)) y_add = static_cast<float>(MAX_LENGTH);
   

	old_y = y;                    //1�t���[���O�̂����W
	y += y_add;                   //���������������W�ɉ��Z����
	g_add = _GRAVITY;              //�d�͉����x������������

	/************************************************************/
}

//�`��
void Enemy_02::Draw() const
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
void Enemy_02::Update_Jangeki()
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
		if (frame_count % 120 == 0) obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, speed, type);
	}
}
//old_y�̎擾�֐�
int Enemy_02::Get_OldY()
{
	return old_y;
}

//y�̎擾�֐�
int Enemy_02::Get_Y()
{
	return y;
}