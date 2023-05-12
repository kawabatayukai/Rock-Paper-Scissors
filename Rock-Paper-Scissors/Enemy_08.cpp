#include "Enemy_08.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"
#include<math.h>

//�R���X�g���N�^�@   ���N���X�̃R���X�g���N�^���Ăԁ@�@�@�@ ���@���@���@�@�@����    ����
Enemy_08::Enemy_08(float x, float y, Jan_Type type) : EnemyBase(x, y, 90.0f, 90.0f, type)
{	
	speed = 7.0f;
	dir = 1;
	hp = 100;

	image = LoadGraph("images/tyokitest.png");

	Init_Jangeki();       //����񌂂�p��

	Enemy_image = LoadGraph("images/stage08/Stage8_image.png");
}

//�f�X�g���N�^2
Enemy_08::~Enemy_08()
{

}


//�X�V
void Enemy_08::Update()
{
	//����񌂍X�V�E����
	Update_Jangeki();

	

	static bool move;
	old_x = x;
	
	if (x <= 20 + w / 2) move = true;
	if (x >= 1280 - 20 - w / 2) move = false;
	
	if (++frame_move % 180 ==0)
	{
		if (move == true) move = false;
		else move = true;
	}
	else
	{

	}

	if (move == true) x += speed;
	else x -= speed;

	
	//if (frame_move <= 180 && frame_move > 200) speed = 0;
	//else if (frame_move == 186) frame_move = 0;
	//else speed = 7.;


	

	/********************   �W�����v�֌W   ********************/

	if (land_flg == true && GetRand(30) == 3)    //GetRand(30) == 3�@�̂Ƃ��낪�W�����v�̏���
	{
		g_add = -21.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
		land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
	}

	y_add = (y - old_y) + g_add;  //����̗���������ݒ�

	//�������x�̐���
	if (y_add > static_cast<float>(MAX_LENGTH)) y_add = static_cast<float>(MAX_LENGTH);

	old_y = y;                    //1�t���[���O�̂����W
	y += y_add;                   //���������������W�ɉ��Z����
	g_add = _GRAVITY;              //�d�͉����x������������

	/**********************************************************/

}

//�`��
void Enemy_08::Draw() const
{
	//���S����`��
	DrawRotaGraphF(x, y, 4.f, 0, Enemy_image, TRUE);

	//����񌂕`��
	Draw_Jangeki();

	DrawFormatString(100, 200, 0x000000, "%f", x);
	DrawFormatString(100, 250, 0x000000, "%f", old_x);
}

//����񌂐����E�X�V
void Enemy_08::Update_Jangeki()
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
		float radius = 25.5f;   //���a
		float speed = -7.0f;     //�X�s�[�h

		//�����_���ȑ����𐶐�
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));


		//����
		if (frame_count % 120 == 0) obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, speed, type);
	}
}