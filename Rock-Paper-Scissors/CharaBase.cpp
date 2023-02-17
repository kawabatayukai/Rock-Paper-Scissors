#include "CharaBase.h"
#include<math.h>

//�R���X�g���N�^    ��,�����W, ��,�����@��ݒ�
CharaBase::CharaBase(float x, float y, float w, float h) : x(x), y(y), w(w), h(h)
{
	speed = 0.0f;
	hp = 10;
	dir = 0;
	obj_jangeki = nullptr;
}

//�f�X�g���N�^
CharaBase::~CharaBase()
{

}


//����񌂐����E�X�V    �g���Ă��g��Ȃ��Ă�
void CharaBase::Update_Jangeki()
{
	//�g���Ƃ��͔h���N���X���Œ�`���܂�
}

//����񌂕`��
void CharaBase::Draw_Jangeki() const
{
	for (int i = 0; i < JANGEKI_MAX; i++)
	{
		//�v�f���Ȃ���Ώ������Ȃ�
		if (obj_jangeki[i] == nullptr) break;
		obj_jangeki[i]->Draw();                //�z��ɗv�f�����鎞
	}
}


//����񌂗p��   ����񌂂��g�p����Ƃ��ɃR���X�g���N�^�ŌĂяo��
void CharaBase::Init_Jangeki()
{
	//����񌂁�JANGEKI_MAX�� �̃��������m��
	obj_jangeki = new Jangeki_Base * [JANGEKI_MAX];

	for (int i = 0; i < JANGEKI_MAX; i++)
	{
		obj_jangeki[i] = nullptr;           //������
	}
}


//����񌂂��폜
void CharaBase::DeleteJangeki(int jan_count)
{
	delete obj_jangeki[jan_count];       //�폜
	obj_jangeki[jan_count] = nullptr;    //������

	//�l�߂�
	for (int i = jan_count; i < (JANGEKI_MAX - 1); i++)
	{
		//���̗v�f�� nullptr �Ȃ炻��ȏ�͏������Ȃ�
		if (obj_jangeki[i + 1] == nullptr) break;

		obj_jangeki[i] = obj_jangeki[i + 1];
		obj_jangeki[i + 1] = nullptr;
	}
}


/*******************  �����蔻��  *******************/

//Floor(��)�Ƃ̓����菈��
void CharaBase::Hit_Floor(const Floor* floor)
{
	int box_x = floor->GetX();   //floor�̂����W
	int box_y = floor->GetY();   //floor�̂����W
	int box_w = floor->GetW();   //floor�̕�
	int box_h = floor->GetH();   //floor�̍���

	//��`�Ƌ�`�̓����蔻��
	if ( CheckHitBox_Box(box_x, box_y, box_w, box_h) == true )
	{

		//�L�����N�^�[���@�i�L�����N�^�[�̍��W�͒��S��j
		int cX_Min = static_cast<int>(x - (w / 2));     //�ŏ����i���j
		int cX_Max = static_cast<int>(x + (w / 2)) - 1; //�ő傘�i�E�j
		int cY_Min = static_cast<int>(y - (h / 2));     //�ŏ����i��j
		int cY_Max = static_cast<int>(y + (h / 2)) - 1; //�ő備�i���j

		//floor�� �@�@�@�@�ifloor�̍��W�͍����j
		int fX_Min = box_x;                //�ŏ����i���j
		int fX_Max = box_x + box_w;        //�ő傘�i�E�j
		int fY_Min = box_y;                //�ŏ����i��j
		int fY_Max = box_y + box_h;        //�ő備�i���j


		//�L�����N�^�[������    ���ɂ߂肱�܂Ȃ�
		if (cY_Max - fY_Min < MAX_LENGTH)  //�L�����N�^�[�̉��[��floor�̏�[���r
		{
			y = static_cast<float>(fY_Min) - (h / 2);
			land_flg = true;   //�ڒn
		}
		
		//�L�����N�^�[�E����
		if (cY_Max - fX_Min < MAX_LENGTH)
		{
			x = static_cast<float>(fX_Min) - (w / 2);
		}

		//�L�����N�^�[������
		if (fX_Max - cY_Min < MAX_LENGTH)
		{
			x = static_cast<float>(fX_Max) + (w / 2);
		}

		
	}
}

//�L�����N�^�[���m�̓����蔻��  Hit:true
bool CharaBase::Hit_Character(const CharaBase* character)
{
	//�iint�^�ɕϊ��j
	int c_w = static_cast<int> ( character->GetW() );   //���@
	int c_h = static_cast<int> ( character->GetH() );   //����
	int c_x = static_cast<int> ( character->GetX() ) - ( c_w / 2 );  //�����W��������
	int c_y = static_cast<int> ( character->GetY() ) - ( c_h / 2 );  //�����W��������

	//��`���m�̓����蔻��
	if (CheckHitBox_Box(c_x, c_y, c_w, c_h) == true) return true;  //������

	return false;   //������Ȃ�
}

//����񌂂ƃL�����N�^�[�̓����蔻��
bool CharaBase::Hit_Jangeki(const Jangeki_Base* jangeki)
{
	float j_x = jangeki->GetX();    //����񌂂̂�  �擾
	float j_y = jangeki->GetY();    //����񌂂̂��@�擾
	float j_r = jangeki->GetR();    //����񌂂̔��a�擾

	//�L�����N�^�[�i��`�j�Ƃ���񌂁i�~�`�j�̓����蔻��
	if (CheckHitBox_Circle(j_x, j_y, j_r) == true)  return true; //������

	return false;   //������Ȃ�
}



//��`�Ƌ�`�̓����蔻��
bool CharaBase::CheckHitBox_Box(int box_x, int box_y, int box_w, int box_h)
{
	//�L�����N�^�[���@�i�L�����N�^�[�̍��W�͒��S��j
	int pX_Min = static_cast<int>(x - (w / 2));     //�ŏ����i���j
	int pX_Max = static_cast<int>(x + (w / 2)) - 1; //�ő傘�i�E�j
	int pY_Min = static_cast<int>(y - (h / 2));     //�ŏ����i��j
	int pY_Max = static_cast<int>(y + (h / 2)) - 1; //�ő備�i���j

	//�����蔻����Ƃ�Ώہ@��4���W
	int tX_Min = box_x;            //�ŏ����i���j
	int tX_Max = box_x + box_w;    //�ő傘�i�E�j
	int tY_Min = box_y;            //�ŏ����i��j
	int tY_Max = box_y + box_h;    //�ő備�i���j

	//��`���m�̔���
	if (pX_Max < tX_Min) {
	}
	else if (tX_Max < pX_Min) {
	}
	else if (pY_Max < tY_Min) {
	}
	else if (tY_Max < pY_Min) {
	}
	else
	{
		return true;  //������
	}

	return false;
}

//��`�Ɖ~�`�̓����蔻��
bool CharaBase::CheckHitBox_Circle(float c_x, float c_y, float c_r)
{
	//Enemy�̋�`
	float n_lx = x - (w / 2);       //���[(Left
	float n_rx = x + (w / 2) - 1;   //�E�[(Right
	float n_ty = y - (h / 2);       //��[(Top
	float n_by = y + (h / 2) - 1;   //���[(Bottom

	//��`�̏�E���͈̔�
	if (c_x > n_lx && c_x < n_rx && c_y > n_ty - c_r && c_y < n_by + c_r) return true;

	//��`�̍��E�E�͈̔�
	if (c_x > n_lx - c_r && c_x < n_rx + c_r && c_y > n_ty && c_y < n_by) return true;

	//"�p��"�@��`�̊e���_�𒆐S�Ƃ����~
	float cir_Lx = powf((n_lx - c_x), 2.0f);       //��x    �i���_ �� �~�̒��S�_ �̍��j��2��
	float cir_Rx = powf((n_rx - c_x), 2.0f);       //�Ex                  �V
	float cir_Ty = powf((n_ty - c_y), 2.0f);       //��y                  �V
	float cir_By = powf((n_by - c_y), 2.0f);       //��y                  �V
	float rad_sq = powf(c_r, 2.0f);                //���a��2��

	if ((cir_Lx + cir_Ty) < rad_sq) return true;   //����
	if ((cir_Rx + cir_Ty) < rad_sq) return true;   //�E��
	if ((cir_Lx + cir_By) < rad_sq) return true;   //����
	if ((cir_Rx + cir_By) < rad_sq) return true;   //�E��

	//����ȊO�͓�����i�V
	return false;
}

/****************************************************/

//�_���[�W���󂯂�@�ihp -= damage�j
void CharaBase::ReceiveDamage(int damage)
{
	//�_���[�W��0�ȏ�
	if (damage > 0)
	{
		hp -= damage;
	}

	return;
}


//�����W�ύX
void CharaBase::SetX(const float x)
{
	if (x > 0)
	{
		this->x = x;
	}
}
//�����W�ύX
void CharaBase::SetY(const float y)
{
	if (y > 0)
	{
		this->y = y;
	}
}