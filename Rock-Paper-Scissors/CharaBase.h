#pragma once
#include"Floor.h"
#include"Jangeki_Base.h"

#define MAX_LENGTH 16     //�߂肱�݋��e�͈�
#define _GRAVITY 1.0f     //�L�����N�^�[�ɂ�����d��

#define JANGEKI_MAX 60    //����񌂍ő吔


//�L�����N�^�[�̊��N���X�@�@�v���C���[�E�G�L�����̃x�[�X
class CharaBase
{
public:
	//�R���X�g���N�^    ��,�����W, ��,�����@��ݒ�
	CharaBase(float x, float y, float w, float h);
	~CharaBase();                  //�f�X�g���N�^

/****************  ���� �ȍ~�A�L�����N�^�[�����ʂ��Ď��ϐ��E�֐� ����  ****************/

	virtual void Update() = 0;          //�X�V�i��`�͔h���N���X���Łj
	virtual void Draw() const = 0;      //�`��i��`�͔h���N���X���Łj


	virtual void Update_Jangeki();      //����񌂐����E�X�V    �g���Ă��g��Ȃ��Ă�
	void Draw_Jangeki() const;          //����񌂕`��
	void Init_Jangeki();                //����񌂗p��   ����񌂂��g�p�������Ƃ��ɃR���X�g���N�^�ŌĂяo��
	void DeleteJangeki(int jan_count);  //����񌂍폜


	float GetX() const { return x; }    //�����W�擾
	float GetY() const { return y; }    //�����W�擾
	float GetW() const { return w; }    //���@�@�擾
	float GetH() const { return h; }    //�����@�擾
	int  GetHP() const { return hp; }   //  hp  �擾
	Jangeki_Base** GetJangeki() const { return obj_jangeki; }  //����񌂔z��擾

	void ReceiveDamage(int damage);     //�_���[�W���󂯂�@�ihp -= damage�j
	void SetX(const float x);           //�����W�ύX
	void SetY(const float y);           //�����W�ύX
 
	/*******************  �����蔻��  *******************/
	
	//Floor(��)�Ƃ̓����菈��
	void Hit_Floor(const Floor* floor);

	//�L�����N�^�[���m�̓����蔻��  Hit:true
	bool Hit_Character(const CharaBase* character);

	//����񌂂ƃL�����N�^�[�̓����蔻��
	bool Hit_Jangeki(const Jangeki_Base* jangeki);

private:
	//��`�Ƌ�`�̓����蔻��
	bool CheckHitBox_Box(int box_x, int box_y, int box_w, int box_h);

	//��`�Ɖ~�`�̓����蔻��
	bool CheckHitBox_Circle(float c_x, float c_y, float c_r);

	/****************************************************/

protected:
	//�L�����N�^�[�̍��W�͒��S
	float x;
	float y;
	float w;
	float h;

	float speed;              //�X�s�[�h
	int hp;                   //HP
	int dir;                  //����

	bool land_flg = false;    //�ڒn�t���O�@�@�ڒn:true   ��ڒn:false

	//����񌂁@�|�C���^�z��
	Jangeki_Base** obj_jangeki;
};
