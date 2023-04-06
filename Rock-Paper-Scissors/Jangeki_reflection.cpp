#include "Jangeki_Reflection.h"
#include"Jangeki_Homing.h"
#include<math.h>
//�R���X�g���N�^
Jangeki_Reflection::Jangeki_Reflection(float x, float y, float r, float speed, Jan_Type type)
	:Jangeki_Base(x, y, r, speed, type)  ,jan_count_reflection(0)  // �����N���X�̃R���X�g���N�^���Ă�
{
	obj_reflection = nullptr;

}

//�f�X�g���N�^
Jangeki_Reflection::~Jangeki_Reflection()
{

}

void Jangeki_Reflection::Update_reflection()
{

	//����񌂔z����ЂƂ���
	for (jan_count_reflection = 0; jan_count_reflection < JANGEKI_MAX; jan_count_reflection++)
	{
		//�z��� jan_count �Ԗڂ�nullptr�i��v�f�j�Ȃ炻��ȏ㏈�����Ȃ�
		if (obj_reflection[jan_count_reflection] == nullptr) break;

		obj_reflection[jan_count_reflection]->Update();

		obj_reflection[jan_count_reflection]->SetTargetLocation(targetX, targetY);
		//��ʊO�ō폜����
		if (obj_reflection[jan_count_reflection]->CheckScreenOut() == true)
		{
			Delete_reflectionJangeki(jan_count_reflection);
			jan_count_reflection--;

		}
	}

}


//����񌂕`��
void Jangeki_Reflection::Draw_reflectionJangeki()const
{
	for (int i = 0; i < JANGEKI_MAX; i++)
	{
		//�v�f���Ȃ���Ώ������Ȃ�
		if (obj_reflection[i] == nullptr) break;

		obj_reflection[i]->Draw();
	}
}


//����񌂗p��   ����񌂂��g�p����Ƃ��ɃR���X�g���N�^�ŌĂяo��
void Jangeki_Reflection::Init_reflectionJangeki()
{
	//����񌂁�JANGEKI_MAX�� �̃��������m��
	obj_reflection = new Jangeki_Base * [JANGEKI_MAX];

	for (int i = 0; i < JANGEKI_MAX; i++)
	{
		obj_reflection[i] = nullptr;           //������
	}
}


//����񌂂��폜
void Jangeki_Reflection::Delete_reflectionJangeki(int jan_count_reflection)
{
	delete obj_reflection[jan_count_reflection];       //�폜
	obj_reflection[jan_count_reflection] = nullptr;    //������

	//�l�߂�
	for (int i = jan_count_reflection; i < (JANGEKI_MAX - 1); i++)
	{
		//���̗v�f�� nullptr �Ȃ炻��ȏ�͏������Ȃ�
		if (obj_reflection[i + 1] == nullptr) break;

		obj_reflection[i] = obj_reflection[i + 1];
		obj_reflection[i + 1] = nullptr;
	}
}



bool Jangeki_Reflection::GetFlg() {
	return reflectionFlg;
}

void Jangeki_Reflection::trueFlg() {
	reflectionFlg = true;
}
void Jangeki_Reflection::falseFlg() {
	reflectionFlg = false;
}

void Jangeki_Reflection::SetTargetLocation(float x, float y)
{
	targetX = x;
	targetY = y;
}
