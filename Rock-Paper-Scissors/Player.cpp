#include"DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include<string.h>
#include "Player.h"
#include"KeyManager.h"

//����񌂔��ˊԊu�@�i1�b�j
#define PLAYER_JAN_INTERVAL 60


//�R���X�g���N�^�@�@�@�@�@�@�@�@�@�@�@�@�@  ���@���@���@�@�@����
Player::Player(float x, float y) : CharaBase(x, y, 57.0f, 100.0f)  //���N���X�̃R���X�g���N�^���Ă�
{
	speed = 7.0f;
	hp = 100;

	//�摜�ǂݍ���
	image = LoadGraph("images/sd_body-1.png");
	LoadDivGraph("images/Jangeki_Test2.png", 3, 3, 1, 100, 100, image_JanType);  //����񌂉摜

	Init_Jangeki();       //����񌂂�p��

	//�f�t�H���g�� �O�[
	select_JanType = Jan_Type::ROCK;

}

//�R���X�g���N�^�i�R�s�[�R���X�g���N�^�j
Player::Player(const Player& player) : CharaBase(player.x, player.y, player.w, player.h)  //���N���X�̃R���X�g���N�^���Ă�
{
	//�����o�ϐ��������̃I�u�W�F�N�g�̓��e�ŏ���������
	// 
	//
	//�����o�Ƀ|�C���^�ϐ����܂ނ��ߒ���


/************ ���N���X�@CharaBase�@�̓��e ************/

	this->speed    = player.speed;       //�X�s�[�h
	this->hp       = player.hp;          //HP
	this->dir      = player.dir;         //����
	this->land_flg = player.land_flg;    //�ڒn�t���O

	Init_Jangeki();       //����񌂂�p�Ӂi����񌂂͈����p���Ȃ��j

/************* �����܂Ł@CharaBase�@�̓��e *************/

	
	this->image          = player.image;             //�v���C���[�摜
	this->select_JanType = player.select_JanType;    //�I������"��"
	this->jan_angle = player.jan_angle;              //����񌂊p�x


	//�I������񌂉摜�R�s�[�i��������Ȃ��j
	memcpy_s(image_JanType, sizeof(player.image_JanType), player.image_JanType, sizeof(player.image_JanType));
}

//�f�X�g���N�^
Player::~Player()
{

}

//�X�V
void Player::Update()
{
	//��
	if (KeyManager::OnPadPressed(PAD_INPUT_LEFT))  x -= speed;

	//�E
	if (KeyManager::OnPadPressed(PAD_INPUT_RIGHT)) x += speed;

	//�����
	Update_Jangeki();

	/********************   �W�����v�֌W   ********************/

	if (land_flg == true && KeyManager::OnPadClicked(PAD_INPUT_5))
	{
		g_add = -21.5f;    //�d�͉����x���}�C�i�X�l��
		land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
	}

	y_add = (y - old_y) + g_add;  //����̗���������ݒ�

	//�������x�̐���
	if (y_add > static_cast<float>(MAX_LENGTH)) y_add = static_cast<float>(MAX_LENGTH);

	old_y = y;                    //1�t���[���O�̂����W
	y += y_add;                   //���������������W�ɉ��Z����
	g_add = _GRAVITY;              //�d�͉����x������������

	/**********************************************************/



	//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

	//�E�X�e�B�b�N�̃A�i���O���͂��擾
	//double right_x = static_cast<double>(KeyManager::GetPadInputState().ThumbRX);   //��
	//double right_y = static_cast<double>(KeyManager::GetPadInputState().ThumbRY);   //��
	double right_x = static_cast<double>(KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_X));   //��
	double right_y = static_cast<double>(KeyManager::Get_StickValue(Stick_Code::RIGHT_STICK_Y));   //��

	jan_angle = atan2(static_cast<double>(right_y - y), static_cast<double>(right_x - x));

	//if (right_x <= 128&&right_x>=0) right_x = 0;
	//if (right_y <= 128 && right_y >= 0) right_y = 0;

	//if (right_y < 0) right_y = 0;

	//�v���C���[���W
	DrawFormatString(300, 200, 0xffffff, "Player_X : %f", x);
	DrawFormatString(300, 230, 0xffffff, "Player_Y : %f", y);

	//�E�X�e�B�b�N�A�i���O���͒l
	DrawFormatString(500, 300, 0xffffff, "Right_X : %d", static_cast<int>(right_x));
	DrawFormatString(500, 330, 0xffffff, "Right_Y : %d", static_cast<int>(right_y));
	

	//�p�x
	//double angle = atan2(static_cast<double>(y - right_y), static_cast<double>(x - right_x));


	DrawFormatString(500, 430, 0xffffff, "�t���ڍ��W_X : %lf", static_cast<double>(right_x - x));
	DrawFormatString(500, 460, 0xffffff, "�t���ڍ��W_Y : %lf", static_cast<double>(right_y - y));
	DrawFormatString(500, 490, 0xffffff, "�t����(�ʓx�@) : %lf", jan_angle * 180 / M_PI);

	//if (angle < 0) angle = 0;
	//if (angle > M_PI - 0.01) angle = M_PI - 0.01;
	//

	int vx = static_cast<int>(550 * cos(jan_angle));
	int vy = static_cast<int>(550 * sin(jan_angle));
	//if (right_x <= 128 && right_x >= 0) vx = 0;
	//if (right_y <= 128 && right_y >= 0) vy = 0;

	//DrawLine(x, y, x - vx, y + vy, 0xffff00, 5);
	DrawLine(x, y, x + vx, y - vy, 0xffff00, 5);

	DrawFormatString(500, 360, 0xffffff, "Angle : %lf", jan_angle);

	////�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`
}

//�`��
void Player::Draw() const
{
	//���S����`��
	DrawRotaGraphF(x, y, 1, 0, image, TRUE); 

	//����񌂕`��
	Draw_Jangeki();

	//�e�X�g HP�\��
	if (hp > 0) DrawFormatString((int)(x - 100), (int)(y - 100), 0xffffff, "HP : %d", hp);

	//�e�X�g �I�������
	DrawString(30, 100, "SELECT : ", 0xffffff);
	DrawRotaGraph(160, 100, 0.5, 0, image_JanType[static_cast<int>(select_JanType)], TRUE);
	DrawString(30, 150, "RB : ����", 0xffffff);


}

//����񌂐����E�X�V
void Player::Update_Jangeki()
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

	// B,Y,X�@�{�^���Ŕ��˂��邶��񌂑�����I���i�Z�b�g�j����
	if (KeyManager::OnPadClicked(PAD_INPUT_B))         //B�{�^��
	{
		//  �O�[��I�� 
		select_JanType = Jan_Type::ROCK;
	}
	else if (KeyManager::OnPadClicked(PAD_INPUT_4))    //Y�{�^��
	{
		//  �`���L��I�� 
		select_JanType = Jan_Type::SCISSORS;
	}
	else if (KeyManager::OnPadClicked(PAD_INPUT_3))    //X�{�^��
	{
		//  �p�[��I�� 
		select_JanType = Jan_Type::PAPER;
	}
	else {}


	//�z��̋�v�f
	if (jan_count < JANGEKI_MAX && obj_jangeki[jan_count] == nullptr)
	{
		float radius = 35.5f;   //���a
		float speed = 8.0f;     //�X�s�[�h

		//RB�{�^���őI�����������̂���񌂂𔭎�
		if (KeyManager::OnPadClicked(PAD_INPUT_6) == true && jan_interval == 0)
		{
			//����񌂐���
			//obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, speed, select_JanType);
			obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, speed, jan_angle, select_JanType);

			//�Ԋu�ݒ�
			jan_interval = PLAYER_JAN_INTERVAL;
		}
	}

	//�Ԋu
	jan_interval--;
	if (jan_interval < 0) jan_interval = 0;
}

//old_y�̎擾�֐�
int Player::Get_OldX()
{
	return static_cast<int>(old_x);
}

//y�̎擾�֐�
int Player::Get_X()
{
	return static_cast<int>(x);
}

//old_y�̎擾�֐�
int Player::Get_OldY()
{
	return static_cast<int>(old_y);
}

//y�̎擾�֐�
int Player::Get_Y()
{
	return static_cast<int>(y);
}