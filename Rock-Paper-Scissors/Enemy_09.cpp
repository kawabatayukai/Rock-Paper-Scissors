#include "Enemy_09.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"
#include"Scene_Stage09.h"
#include"Jangeki_Homing.h"


//�R���X�g���N�^�@   ���N���X�̃R���X�g���N�^���Ăԁ@�@�@�@ ���@���@���@�@�@����    ����
Enemy_09::Enemy_09(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
{

	speed = 7.0f;
	dir = 1;
	hp = 100;


	image = LoadGraph("images/stage09/Stage9_1.png");
	
	/*image = LoadGraph("images/stage09/Stage9.png");*/

	//����񌂂�p��
	Init_Jangeki();       
	reflection = new Jangeki_Reflection(x, y, w, h, Jan_Type::ROCK);
	reflection->Init_reflectionJangeki();
	
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
	reflection->Update_reflection();

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

	//y_add = (y - old_y) + g_add;  //����̗���������ݒ�

	////�������x�̐���
	//if (y_add > static_cast<float>(MAX_LENGTH)) y_add = static_cast<float>(MAX_LENGTH);

	//old_y = y;                    //1�t���[���O�̂����W
	//y += y_add;                   //���������������W�ɉ��Z����
	//g_add = _GRAVITY;              //�d�͉����x������������

	/**********************************************************/

}

//�`��
void Enemy_09::Draw() const
{
	
	//���S����`��
	DrawRotaGraphF(x, y, 1, 0, image, TRUE);
	

	//����񌂕`��
	Draw_Jangeki();
	reflection->Draw_reflectionJangeki();
	

	//�e�X�g
	if (hp > 0) DrawFormatString((int)(x - 100), (int)(y - 100), 0xffffff, "HP : %d", hp);
	else DrawString((int)(x - 100), (int)(y - 100), "death!", 0xffffff);

}
//void Enemy_09::RDraw() 
//{
//	DrawRotaGraphF(GetX(), GetY(), 1, 0, image, TRUE);
//}

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
		
		//�z�[�~���O����񌂂ł���΃v���C���[�̍��W���Z�b�g����
		obj_jangeki[jan_count]->SetTargetLocation(player_x, player_y);
		reflection->SetTargetLocation(player_x, player_y);

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
		float speed = 3.0f;     //�X�s�[�h

		//�����_���ȑ����𐶐�
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));

	
		//����
		if (frame_count % janFrame == 0) obj_jangeki[jan_count] = new Jangeki_Homing(x, y, radius, speed, type);
		/*if(GetHP()!=1)
		{
			if (frame_count % 100 == 0) obj_jangeki[jan_count] = new Jangeki_Homing(x, y, radius, speed, type);
		}*/
		
		//���˂���񌂐���
		if (reflection->GetFlg() == true)reflection->obj_reflection[reflection->jan_count_reflection] = new Jangeki_Homing(x, y, radius, speed, type, true);
		reflection->falseFlg();
	}
}

void Enemy_09::MoveEnmey_09() 
{
	interval++;
	if (/*land_flg == true && *//*GetRand(100) == 5 &&*/ interval % 300 == 0) {
		switch (GetRand(12))
		{
		//����
		case 0:
			x = 160;
			y = 480;
			break;
		case 1:
			x = 160;
			y = 700;
			break;
		case 2:
			x = 360;
			y = 305;
			break;
		case 3:
			x = 360;
			y = 700;
			break;
		case 4:
			x = 160;
			y = 130;
			break;
		//�E��
		case 5:
			x = 1110;
			y = 480;
			break;
		case 6:
			x = 1110;
			y = 700;
			break;
		case 7:
			x = 910;
			y = 305;
			break;
		case 8:
			x = 910;
			y = 700;
			break;
		case 9:
			x = 1110;
			y = 130;
			break;
		//�^��
		case 10:
			x = 620;
			y = 400;
			break;
		case 11:
			x = 620;
			y = 80;
			break;
		case 12:
			x = 620;
			y = 700;
			break;
		}
	}

}

void Enemy_09::frameUP()
{
	if (janFrame >= 55)
	{
		janFrame = janFrame - 5;
	}
}

void Enemy_09::frameDown()
{
	if (janFrame < 75)
	{
		janFrame = janFrame + 5;
	}

}

void Enemy_09::HP() 
{
	if (hp <= 0)
	{
		hp = 1;
	}
}