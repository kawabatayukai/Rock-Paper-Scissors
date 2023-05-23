#include "Enemy_04.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"
#include"Jangeki_Coming.h"
#include "Jangeki_whole.h"
#include"SoundSystem.h"
#include <typeinfo>
#define _USE_MATH_DEFINES
#include<math.h>

//�R���X�g���N�^�@   ���N���X�̃R���X�g���N�^���Ăԁ@�@�@�@ ���@���@���@�@�@����    ����
Enemy_04::Enemy_04(float x, float y, Jan_Type type) : EnemyBase(x, y, 150.0f, 150.0f, type)
{
	speed = 1.0f;
	dir = 1;
	hp = 100;

	enemy_x = 640;
	enemy_y = 360;

	enemy_image[0] = LoadGraph("images/Stage04/stage_Boss04.png");
	enemy_image[1] = LoadGraph("images/Stage04/stage_Boss04(��).png");
	enemy_image[2] = LoadGraph("images/Stage04/stage_Boss04(�E��).png");
	enemy_image[3] = LoadGraph("images/Stage04/stage_Boss04(�E).png");
	enemy_image[4] = LoadGraph("images/Stage04/stage_Boss04(�E��).png");
	enemy_image[5] = LoadGraph("images/Stage04/stage_Boss04(��).png");
	enemy_image[6] = LoadGraph("images/Stage04/stage_Boss04(����).png");
	enemy_image[7] = LoadGraph("images/Stage04/stage_Boss04(��).png");
	enemy_image[8] = LoadGraph("images/Stage04/stage_Boss04(����).png");
	enemy_image[9] = LoadGraph("images/Stage04/stage_Boss04(����s��).png");

	Init_Jangeki();       //����񌂂�p��
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

	//�v���C���[�Ƃ̊p�x
	angle = atan2f((player_x - x), (player_y - y));

	//�����p�^�[��(�ʏ펞)
	moveinfo[0] = { 1, player_x, player_y, 0, 0 };

	//�����p�^�[��(����s����)
	moveinfo[1] = { 1,  enemy_x,  enemy_y, 0, 2 };
	moveinfo[2] = { 0,      0.f,      0.f, 0, 1 };

	switch (moveinfo[current].moveflg)
	{
	case 0:
		waitTime++;
		if (moveinfo[current].waitFlameTime <= waitTime)
		{
			if (specialFlg == true)
			{
				enemy_x = GetRand(1080) + 100;
				enemy_y = GetRand(340) + 100;
			}
			waitTime = 0;
			current = moveinfo[current].next_index;
		}
		break;

	case 1:
		Move_Pattern();
		break;

	default:
		break;
	}

	//�̗̓Q�[�W���}�C�i�X�ɂȂ�Ȃ��悤��
	if (hp <= 0) hp = 0;

	//����s������c��HP�ɂ���ăX�s�[�h���ς��
	if (specialFlg == true)
	{
		speed = 20.0f;
		specialTime++;
	}
	else if (hp <= 50)
	{
		speed = 2.6f;
	}
	else
	{
		speed = 1.8f;
	}

	//��������HP��
	if (hp < 100 && frame_count % 20 == 0) hp++;

	//����s������(4�b��)
	if (specialTime >= 240)
	{
		specialTime = 0;
		specialFlg = false;
		current = 0;
		SoundSystem::StopSE(SE::ENEMY_SPECIAL);
	}
}

//�`��
void Enemy_04::Draw() const
{	
	//���S����`��
	DrawRotaGraphF(x, y, 1.5, 0, enemy_image[0], TRUE);

	/************* ���� ���ڂ��v���C���[�̊p�x�֌����� ���� *************/

	//������̉摜
	if (angle > 2.625 && angle <= 3.15 || angle <= -2.625 && angle > -3)
	{
		DrawRotaGraphF(x, y, 1.5, 0, enemy_image[1], TRUE);
	}

	//�E������̉摜
	if (angle <= 2.625 && angle > 1.875)
	{
		DrawRotaGraphF(x, y, 1.5, 0, enemy_image[2], TRUE);
	}

	//�E�����̉摜
	if (angle <= 1.875 && angle > 1.125)
	{
		DrawRotaGraphF(x, y, 1.5, 0, enemy_image[3], TRUE);
	}

	//�E�������̉摜
	if (angle <= 1.125 && angle > 0.375)
	{
		DrawRotaGraphF(x, y, 1.5, 0, enemy_image[4], TRUE);
	}

	//�������̉摜
	if (angle <= 0.375 && angle > -0.375)
	{
		DrawRotaGraphF(x, y, 1.5, 0, enemy_image[5], TRUE);
	}

	//���������̉摜
	if (angle <= -0.375 && angle > -1.125)
	{
		DrawRotaGraphF(x, y, 1.5, 0, enemy_image[6], TRUE);
	}

	//�������̉摜
	if (angle <= -1.125 && angle > -1.875)
	{
		DrawRotaGraphF(x, y, 1.5, 0, enemy_image[7], TRUE);
	}

	//��������̉摜
	if (angle <= -1.875 && angle > -2.625)
	{
		DrawRotaGraphF(x, y, 1.5, 0, enemy_image[8], TRUE);
	}

	if (specialFlg == true)
	{
		DrawRotaGraphF(x, y, 1.5, 0, enemy_image[9], TRUE);
	}

	//����񌂕`��
	Draw_Jangeki();

	//�c��HP50�ȉ��̎��ɕ\��
	if (hp <= 50) DrawFormatString((int)(x - 60), (int)(y - 155), GetColor(30, 30, 255), "�X�s�[�hUP��", hp);
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

		//�v���C���[�̍��W���Z�b�g����
		obj_jangeki[jan_count]->SetTargetLocation(player_x, player_y);

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
		float radius = 45.0f;   //���a
		float speed  =  6.0f;   //�X�s�[�h

		//HP50�ȉ��ŃW�������X�s�[�h�ύX
		if (hp <= 50) speed = 10.0f;
		
		//�����_���ȑ����𐶐�
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));

		//����s����Ԃ��ǂ���
		if (specialFlg == false)
		{
			//�v���C���[�̊p�x�֔��˂���W����������
			if (frame_count % 60 == 0) obj_jangeki[jan_count] = new Jangeki_Coming(x, y, radius, speed, type, player_x, player_y);

			//if (frame_count % 121 == 0) obj_jangeki[jan_count] = new Jangeki_Coming(x, y, radius * 0.7, speed * 0, type, player_x, player_y);

		}
		else if (specialFlg == true)
		{
			if (frame_count % 60 == 0)
			{
				Jan_360degrees(jan_count, radius * 0.8, speed * 0.8, type);
				SoundSystem::PlaySE(SE::ENEMY_SPECIAL_ATTACK);
			}
		}
	}
}

void Enemy_04::Move_Pattern() {

	//�ړ������
	float move_x = x;
	float move_y = y;

	//�ڎw���Ă���x���W��y���W����v�����Ƃ�
	if (x == moveinfo[current].location_x && y == moveinfo[current].location_y) {
		current = moveinfo[current].next_index; //���̃p�^�[��
	}

	//x���W���ڎw���Ă�����W�ƕs��v
	if (x != moveinfo[current].location_x) {

		//�ڎw���Ă���x���W�̉E�����傫��
		if (x < moveinfo[current].location_x) {
			move_x += speed; //�E�ړ��Ƀv���X����

			//�ڎw���Ă������W�𒴂����Ƃ�
			if (x <= moveinfo[current].location_x && moveinfo[current].location_x <= move_x)
			{

				move_x = moveinfo[current].location_x; //�ڎw���Ă������W�ŌŒ�

			}

		}
		else
		{
			move_x -= speed; //���ړ��Ƀ}�C�i�X����

			//�ڎw���Ă������W�𒴂����Ƃ�
			if (move_x <= moveinfo[current].location_x && moveinfo[current].location_x <= x)
			{

				move_x = moveinfo[current].location_x; //�ڎw���Ă������W�ŌŒ�

			}


		}


	}

	//y���W���ڎw���Ă�����W�ƕs��v
	if (y != moveinfo[current].location_y) {

		//�ڎw���Ă���y���W�̉E�����傫��
		if (y < moveinfo[current].location_y) {
			move_y += speed; //���ړ��Ƀv���X����

			//�ڎw���Ă������W�𒴂����Ƃ�
			if (y <= moveinfo[current].location_y && moveinfo[current].location_y <= move_y)
			{

				move_y = moveinfo[current].location_y; //�ڎw���Ă������W�ŌŒ�

			}

		}
		else
		{
			move_y -= speed; //��ړ��Ƀ}�C�i�X����

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

void Enemy_04::Change_JanType()
{
	//���݂̑����ƈقȂ�2�����̂��������_��
	switch (this->e_type)
	{
	case Jan_Type::ROCK:

		e_type = GetRand(1) == 1 ? Jan_Type::PAPER : Jan_Type::SCISSORS;
		break;

	case Jan_Type::SCISSORS:

		e_type = GetRand(1) == 1 ? Jan_Type::PAPER : Jan_Type::ROCK;
		break;

	case Jan_Type::PAPER:

		e_type = GetRand(1) == 1 ? Jan_Type::ROCK : Jan_Type::SCISSORS;
		break;

	default:
		break;
	}

	return;
}

void Enemy_04::Special_Action()
{
	specialFlg = true;
	current = 1;
	SoundSystem::PlaySE(SE::ENEMY_SPECIAL);
}

//360�x����
void Enemy_04::Jan_360degrees(int count, float rad, float speed, Jan_Type type)
{
	//20�x����18����
	for (int i = count; i < (count + 18); i++)
	{
		double angle = static_cast<double>((20.0 * i) * (M_PI / 180));

		obj_jangeki[i] = new Jangeki_Base(x, y, rad, speed, angle, type);
	}
}