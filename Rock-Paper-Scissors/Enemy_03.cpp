#include "Enemy_03.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"
#include <typeinfo>


//�R���X�g���N�^�@   ���N���X�̃R���X�g���N�^���Ăԁ@�@�@�@ ���@���@���@�@�@����    ����
Enemy_03::Enemy_03(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
{

	speed = 1.85f;//1.5f
	dir = 1;//�G�l�~�[�̌���
	hp = 100;

	enemyimage[0] = LoadGraph("images/stage03/stage03attack.png");
	enemyimage[1] = LoadGraph("images/stage03/stage03gard.png");

	Init_Jangeki();       //����񌂂�p��

	//�����p�^�[�� �J��Ԃ��@//0�œ���,1�Ŏ~�܂�
	moveinfo[0] = { 0, 950.f, 0.f , 1,  0 ,1 };//�����ʒu��X��950�Œ�~

	moveinfo[1] = { 1,  0 ,   0.f , 2, 125 ,1 };//�����ʒu��X��950�Œ�~
	//�������瓮��
	moveinfo[2] = { 0, 650.f, 0.f , 3,  0 ,1 };//X��650�܂œ���

	moveinfo[3] = { 1,  0 ,   0.f , 4, 125 ,1 };//X��650�Œ�~

	moveinfo[4] = { 0, 325.f, 0.f , 5, 0 ,1 };//X��325�܂œ���

	moveinfo[5] = { 1,  0 ,   0.f , 6, 125 ,1 };//X��325�Œ�~

	//����ɏ��
	moveinfo[6] = { 0, 325.f, 0.f , 7, 0 ,0 };//X��325�Œ�~

	moveinfo[7] = { 1,  0 ,   0.f , 8, 125 ,1 };//X��325�Œ�~

	moveinfo[8] = { 0,  70.f , 0.f , 9, 0 ,0 };//X��325�Œ�~

	moveinfo[9] = { 1,  0 ,   0.f , 10, 125 ,1 };//X��325�Œ�~

	moveinfo[10] = { 0, 280.f, 0.f , 11,  0 ,0 };//X��650�܂œ���

	moveinfo[11] = { 1,  0 ,   0.f , 12, 125,1 };//X��325�Œ�~

	moveinfo[12] = { 0, 465.f, 0.f , 13,  0 ,0 };//X��650�܂œ���

	moveinfo[13] = { 1,  0 ,   0.f , 14, 125,1 };//X��325�Œ�~

	moveinfo[14] = { 0, 585.f,0.f , 15,  0 ,0 };//X��650�܂œ���

	moveinfo[15] = { 1,  0 ,   0.f , 16, 125,1 };//X��325�Œ�~

	moveinfo[16] = { 0, 780.f, 0.f , 17,  0 ,0 };//X��650�܂œ���

	moveinfo[17] = { 1,  0 ,   0.f , 18, 125,1 };//X��325�Œ�~

	moveinfo[18] = { 0, 970.f, 0.f , 19,  0 ,0 };//X��650�܂œ���

	moveinfo[19] = { 1,  0 ,   0.f , 20, 125,1 };//X��325�Œ�~

	moveinfo[20] = { 0, 1160.f, 0.f , 21,  0 ,0 };//X��650�܂œ���

	moveinfo[21] = { 1,  0 ,   0.f , 22, 125,1 };//X��325�Œ�~

	moveinfo[22] = { 0,  1020.f , 0.f , 23, 0, 1 };//X��325�Œ�~

	moveinfo[23] = { 1,  0 ,   0.f , 24, 125,1 };//X��325�Œ�~

	moveinfo[24] = { 0,  930.f , 0.f , 25, 0, 1 };//X��325�Œ�~

	moveinfo[25] = { 1,  0 , 0.f , 26, 125,1 };//X��325�Œ�~

	moveinfo[26] = { 0, 1020.f , 0.f , 27, 0, 0 };//X��325�Œ�~

	moveinfo[27] = { 1,  0 , 0.f , 28, 125,1 };//X��325�Œ�~

	moveinfo[28] = { 0,  1160.f , 0.f , 29, 0, 0 };//X��325�Œ�~

	moveinfo[29] = { 1,  0 , 0.f , 30, 125, 1 };//X��325�Œ�~

	moveinfo[30] = { 0,  970.f , 0.f , 31, 0, 0 };//X��325�Œ�~

	moveinfo[31] = { 1,  0 , 0.f , 32, 125,1 };//X��325�Œ�~

	moveinfo[32] = { 0,  780.f , 0.f , 33, 0, 0 };//X��325�Œ�~

	moveinfo[33] = { 1,  0 , 0.f , 34, 125,1 };//X��325�Œ�~

	moveinfo[34] = { 0,  585.f , 0.f , 35, 0, 0 };//X��325�Œ�~

	moveinfo[35] = { 1,  0 ,   0.f , 36, 125,1 };//X��325�Œ�~

	moveinfo[36] = { 0, 465.f, 0.f , 37,  0 ,0 };//X��650�܂œ���

	moveinfo[37] = { 1,  0 ,   0.f , 38, 125,1 };//X��325�Œ�~

	moveinfo[38] = { 0, 280.f, 0.f , 39,  0 ,0 };//X��650�܂œ���

	moveinfo[39] = { 1,  0 ,   0.f , 40, 125,1 };//X��325�Œ�~

	moveinfo[40] = { 0, 70.f,  0.f , 41,  0 ,0 };//X��650�܂œ���

	moveinfo[41] = { 1,  0 ,   0.f , 42, 125,1 };//X��325�Œ�~
	//�������瓮��2
	moveinfo[42] = { 0, 325.f, 0.f , 43,  0 ,1 };//�����ʒu��X��950�Œ�~

	moveinfo[43] = { 1,  0 ,   0.f , 44, 125 ,1 };//�����ʒu��X��950�Œ�~
	
	moveinfo[44] = { 0, 650.f, 0.f , 45,  0 ,1 };//X��650�܂œ���

	moveinfo[45] = { 1,  0 ,   0.f , 46, 125 ,1 };//X��650�Œ�~

	moveinfo[46] = { 0,	950.f, 0.f , 47, 0 ,1 };//X��325�܂œ���

	moveinfo[47] = { 1,	 0,  0.f , 48, 62 ,1 };//X��325�܂œ���

	moveinfo[48] = { 1,  0 ,   0.f , 0, 125 ,1 };//X��650�Œ�~���z��[0]�ɖ߂�

}



//�f�X�g���N�^
Enemy_03::~Enemy_03()
{

}

//�X�V
void Enemy_03::Update()
{
	if (land_flg == true && moveinfo[current].enemywaitTime == 0 && moveinfo[current].jumpflg == 0)    //GetRand(30) == 3�@�̂Ƃ��낪�W�����v�̏���
	{
		g_add = -23.f;    //����-21.5f,�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
		land_flg = false;  //�n�ʂɂ��Ă��Ȃ�

		speed = 2.8f;
	}

	//����񌂍X�V�E����
	Update_Jangeki();

	//�����ύX
	if (moveinfo[current].enemywaitTime > 0) {

		e_type = Jan_Type::ROCK;

	}
	//��L�̑����ύX�ȊO
	else e_type = Jan_Type::SCISSORS;

	//�X�e03�p�^�[���p�֐�
	switch (moveinfo[current].moveflg)
	{
	case 0:
		Move_Pattern();

		break;
	case 1:
		waitcount++;
		if (moveinfo[current].enemywaitTime <= waitcount) {

			waitcount = 0;
			current = moveinfo[current].next_index;

		}
		break;
	default:
		break;
	}


	//HP��0�ȉ���������HP��0����
	if (hp <= 0)hp = 0;



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



	y_add = (y - old_y) + g_add;  //����̗���������ݒ�

	//�������x�̐���
	if (y_add > static_cast<float>(MAX_LENGTH)) y_add = static_cast<float>(MAX_LENGTH);

	old_y = y;              //1�t���[���O�̂����W
	y += y_add;            //���������������W�ɉ��Z����
	g_add = _GRAVITY;     //�d�͉����x������������





}
/********************   ���ړ�   ********************/

//if (land_flg == true && GetRand(30) == 3)    //GetRand(30) == 3�@�̂Ƃ��낪�W�����v�̏���
//{
//	enemy_x = -21.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v


//	land_flg = false;  //�n�ʂɂ��Ă��Ȃ�

//}

//old_x = (x - old_x) + enemy_x;  //����̗���������ݒ�

////�������x�̐���
//if (enemy_x > static_cast<float>(MAX_LENGTH)) enemy_x = static_cast<float>(MAX_LENGTH);

//old_x = x;                    //1�t���[���O��x���W
//x += enemy_x;                   //����������x���W�ɉ��Z����
//enemy_x = _GRAVITY;              //�d�͉����x������������

/**********************************************************/

//�`��
void Enemy_03::Draw() const

{
	//�G�l�~�[��~��
	if (moveinfo[current].enemywaitTime > 0) {

		//�K�[�h���̉摜�`��
		DrawRotaGraphF(x, y, 1, 0, enemyimage[1], TRUE, dir == -1 ? 0 : 1);


	}
	//��������Ȃ��Ƃ�
	else {
		//�U�����̉摜�`��
		DrawRotaGraphF(x, y, 1, 0, enemyimage[0], TRUE, dir == -1 ? 0 : 1);
	}




	//����񌂕`��
	Draw_Jangeki();




	//�e�X�g                                                      //�ԐF
	if (moveinfo[current].enemywaitTime > 0) DrawFormatString((int)(x - 100), (int)(y - 100), GetColor(0, 0, 255), "�h��� UP��", moveinfo[current].enemywaitTime);

	if (hp <= 50) DrawFormatString((int)(x - 100), (int)(y - 80), GetColor(255, 0, 0), "�U���� UP��", hp);

	if (hp <= 0)DrawString((int)(x - 100), (int)(y - 120), "death!", 0xff0000);

}

//����񌂐����E�X�V
void Enemy_03::Update_Jangeki()
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
		float radius = 40.0f;   //���a //35.5f
		float speed = 6.0f * dir;     //�X�s�[�h//3.0

		//�����_���ȑ����𐶐�
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));//2


		//����
		if (frame_count % 120 == 0) obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, speed, type);
	}
}

void Enemy_03::Move_Pattern() {

	//�ړ������
	float move_x = x;
	float move_y = y;

	//�ڎw���Ă�����W��X���W����v�����Ƃ�
	if (x == moveinfo[current].location_x) {

		current = moveinfo[current].next_index; //���̃p�^�[��

		//speed��up
		speed = 2.8f;

	}

	//x���W���ڎw���Ă�����W�ƕs��v
	if (x != moveinfo[current].location_x) {

		//�W�����v���Ă���Ƃ�
		if (moveinfo[current].jumpflg == 0) {

			//speed��up
			speed = 4.0f;

		}


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

	//�ړ��𔽉f����
	x = move_x;
	y = move_y;

}

//enemywaitTime�p��
int Enemy_03::GetWaitTime()const {

	return moveinfo[current].enemywaitTime;
}



//�v���C���[�̍��W���p��
void Enemy_03::ChangeDir(float x)
{
	if (x < 640) dir = -1;
	else dir = 1;
}
