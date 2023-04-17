#include "Enemy_04.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"
#include"Jangeki_Coming.h"
#include <typeinfo>

//�R���X�g���N�^�@   ���N���X�̃R���X�g���N�^���Ăԁ@�@�@�@ ���@���@���@�@�@����    ����
Enemy_04::Enemy_04(float x, float y, Jan_Type type) : EnemyBase(x, y, 150.0f, 150.0f, type)
{
	speed = 1.0f;
	dir = 1;
	hp = 100;

	enemy_image[0] = LoadGraph("images/Stage4/stage_Boss04.png");
	enemy_image[1] = LoadGraph("images/Stage4/stage_Boss04(��).png");
	enemy_image[2] = LoadGraph("images/Stage4/stage_Boss04(�E��).png");
	enemy_image[3] = LoadGraph("images/Stage4/stage_Boss04(�E).png");
	enemy_image[4] = LoadGraph("images/Stage4/stage_Boss04(�E��).png");
	enemy_image[5] = LoadGraph("images/Stage4/stage_Boss04(��).png");
	enemy_image[6] = LoadGraph("images/Stage4/stage_Boss04(����).png");
	enemy_image[7] = LoadGraph("images/Stage4/stage_Boss04(��).png");
	enemy_image[8] = LoadGraph("images/Stage4/stage_Boss04(����).png");

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

	//�����p�^�[��
	moveinfo[0] = { 1, player_x, player_y, 0, 1 };
	moveinfo[1] = { 0,      0.f,      0.f, 0, 0 };

	switch (moveinfo[current].moveflg)
	{
	case 0:
		waitTime++;
		if (moveinfo[current].waitFlameTime <= waitTime)
		{
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
	
	//HP50���ȉ��ŃX�s�[�hUP
	//if (hp <= 50) speed = 2.0f;
	//else speed = 1.0f;
	
	//��������HP��
	if (hp < 100 && frame_count % 25 == 0) hp++;
}

//�`��
void Enemy_04::Draw() const
{	
	//���S����`��
	DrawRotaGraphF(x, y, 1.5, 0, enemy_image[0], TRUE);

	/************* ���� ���ڂ̈ʒu���v���C���[�Ƃ̊p�x�ɂ���ĕς��� ���� *************/

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

	//����񌂕`��
	Draw_Jangeki();

	if (hp > 0) DrawFormatString((int)(x - 45), (int)(y - 130), 0xffffff, "HP : %d", hp);
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
		float speed  =  2.5f;   //�X�s�[�h
		
		//�����_���ȑ����𐶐�
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));


		//�v���C���[�̊p�x�֔��˂���W����������
		if (frame_count % 60 == 0) obj_jangeki[jan_count] = new Jangeki_Coming(x, y, radius, speed, type, player_x, player_y);

		//HP��50%�ȉ��ŐV���ȃW����������
		//if (hp <= 50)
		//{
		//	//�v���C���[��x���W�ɂ���Ĕ��˂��������ς���(���E)
		//	if (player_x <= 640)
		//	{
		//		if (frame_count % 40 == 0) obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius * 0.5, speed * -1.5, type);
		//	}
		//	else if (player_x > 640)
		//	{
		//		if (frame_count % 40 == 0) obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius * 0.5, speed *  2, type);
		//	}
		//	
		//}
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
