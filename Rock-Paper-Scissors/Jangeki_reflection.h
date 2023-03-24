#pragma once
#include "Jangeki_Base.h"
#include"DxLib.h"
#include"CharaBase.h"
class Jangeki_Reflection : public Jangeki_Base{

public:
		//�R���X�g���N�^  ���@�@�@�@���@�@�@���a�@�@�X�s�[�h�@�@�@�^�C�v
	Jangeki_Reflection(float x, float y, float r, float speed, Jan_Type type);

	~Jangeki_Reflection();

	//virtual void Update() override;       //�X�V�@�I�[�o�[���C�h�i�Ē�`�j
	void Draw(float rx, float ry) const ;        //�`��͊��N���X�̓��e�̂܂܂�ok

	void Update_reflection();
	void Draw_reflectionJangeki() const;
	void Init_reflectionJangeki();
	void Delete_reflectionJangeki(int jan_count_reflection);

	bool GetFlg();
	void trueFlg();
	void falseFlg();

	Jangeki_Base** obj_reflection;//���˃W�������p�z��
	Jangeki_Base** GetJangeki() const { return obj_reflection; } //���˂��ꂽ�W�������擾

	int jan_count_reflection;
	
	void SetTargetLocation(float x, float y);
	
protected:
	
private:
	//���˂���񌂂��ǂ���
	bool reflectionFlg = false;
	
	float targetX = 0;
	float targetY = 0;
	
	int Rimage[3];
	

};

