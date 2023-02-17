#pragma once
#include"Jangeki_Base.h"

// �ڐG���̂���񂯂�  ���s�����߂�N���X
class Janken
{
public:
	//�R���X�g���N�^   �G�̏o��������炤
	Janken(Jan_Type enemy_jan);

	~Janken();            //�f�X�g���N�^

	void Update();        //�X�V
	void Draw() const;    //�`��

	Jan_Result GetResult() const { return result; }  //����񂯂�̌��ʂ�Ԃ�


private:

	//B�i�O�[�j,Y�i�`���L�j,X�i�p�[�j�̂����ꂩ�������ꂽ�u�ԁAtrue��Ԃ�
	bool Check_AnyButton();

	//"�ڐG������񂯂�"����
	//   Check_AnyButton() �ŉ����ꂽ�{�^���� enemy�i�����j�̏��s���ʂ�Ԃ� (�����ꂽ�{�^���ڐ�)
	Jan_Result Get_JankenResult();

private:
	bool button_B = false;   //B�{�^����������Ă��邩
	bool button_Y = false;   //Y�{�^����������Ă��邩
	bool button_X = false;   //X�{�^����������Ă��邩

	Jan_Type enemy_jan;      //�G�̏o����@�R���X�g���N�^�ł��炤
	Jan_Type player_jan;     //�v���C���[�̏o����  Check_AnyButton()�ŉ����ꂽ�{�^��

	Jan_Result result;       // ����񂯂�̌��ʂ��i�[����

	int image[3];            //�摜
};
