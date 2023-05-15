#pragma once
#include"CharaBase.h"

//���S�����Ƃ��ɕʃI�u�W�F�N�g�𐶐�����
class Enemy_Death : public CharaBase
{
public:
	//���� : ���S���̍��W�A�X�e�[�W�ԍ�
	Enemy_Death(const float& x, const float& y, const int& stage_num = 0, const Jan_Type& type = Jan_Type::NONE);
	~Enemy_Death();

	void Update() override;
	void Draw() const override;

	bool IsDeathEnd();  //���S���o����

private:
	int image_death;

	float old_x = 0;          //�O��̈ʒuX
	float old_y = 0;          //�O��̈ʒuY
	float y_add = 0;          //��������
	float g_add = 1.0f;       //�d�͉����x
};
