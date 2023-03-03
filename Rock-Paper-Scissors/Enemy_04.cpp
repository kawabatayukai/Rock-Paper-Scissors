#include "Enemy_04.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"
#include <typeinfo>

//�R���X�g���N�^�@   ���N���X�̃R���X�g���N�^���Ăԁ@�@�@�@ ���@���@���@�@�@����    ����
Enemy_04::Enemy_04(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
{
	speed = 2.5f;
	dir = 1;
	hp = 100;

	image = LoadGraph("images/Stage4/�X�e�[�W4_�{�X.png");

	Init_Jangeki();       //����񌂂�p��

		//�����p�^�[��
	moveinfo[0] = { 1,0.f,200.f,1 };
	moveinfo[1] = { 1,0.f,500.f,0 };
}

//�f�X�g���N�^
Enemy_04::~Enemy_04()
{

}


//�X�V
void Enemy_04::Update()
{
	//����񌂍X�V�E����
	Update_Jangeki();

	//�X�e04�p�^�[���p�֐�
	Move_Pattern();

	//if (hp <= 50)
	//{
	//	speed = 6.0f;
	//}

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
	//	g_add = -31.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
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
void Enemy_04::Draw() const
{	
	//���S����`��
	DrawRotaGraphF(x, y, 3, 0, image, TRUE);

	//����񌂕`��
	Draw_Jangeki();



	//�e�X�g
	if (hp > 0) DrawFormatString((int)(x - 100), (int)(y - 100), 0xffffff, "HP : %d", hp);
	else DrawString((int)(x - 100), (int)(y - 100), "death!", 0xffffff);

}

//����񌂐����E�X�V
void Enemy_04::Update_Jangeki()
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

void Enemy_04::Move_Pattern() {

	//�ړ������
	float move_x = x;
	float move_y = y;

	//�ڎw���Ă�����W��X���W����v�����Ƃ�
	if (y == moveinfo[current].location_y) {
		current = moveinfo[current].next_index; //���̃p�^�[��
	}

	//x���W���ڎw���Ă�����W�ƕs��v
	if (y != moveinfo[current].location_y) {

		//�ڎw���Ă���x���W�̉E�����傫��
		if (y < moveinfo[current].location_y) {
			move_y += speed; //�E�ړ��Ƀv���X����

			//�ڎw���Ă������W�𒴂����Ƃ�
			if (y <= moveinfo[current].location_y && moveinfo[current].location_y <= move_y)
			{

				move_y = moveinfo[current].location_y; //�ڎw���Ă������W�ŌŒ�

			}

		}
		else
		{
			move_y -= speed; //���ړ��Ƀ}�C�i�X����

			//�ڎw���Ă������W�𒴂����Ƃ�
			if (move_y <= moveinfo[current].location_y && moveinfo[current].location_y <= y)
			{

				move_y = moveinfo[current].location_y; //�ڎw���Ă������W�ŌŒ�

			}


		}


	}

	//�ړ��𔽉f����
	x = move_x;
	y = move_y;

}