#include "Scene_Result.h"
#include"Scene_Ranking.h"
#include"Scene_InputRanking.h"
#include <DxLib.h>
#include "KeyManager.h"

int a = 0;

//�X�V
void  Scene_Result::Update()
{
	// �t�H���g�T�C�Y�̐ݒ�
	SetFontSize(20);

	// ���O���͎w��������̕`��
	DrawString(150, 240, "�����L���O�ɓo�^���܂�", 0xFFFFFF);
	DrawString(150, 270, "���O���p���œ��͂��Ă�������", 0xFFFFFF);

	// ���O�̓���
	DrawString(150, 310, "> ", 0xFFFFFF);
	DrawBox(160, 305, 300, 335, 0x000055, TRUE);

	//�����L���O���͏���
	if (KeyInputSingleCharString(170, 310, 10, name, FALSE) == 1)
	{
		inputRanking.setName(9, name);
		inputRanking.setScore(9, 10);	// �����L���O�f�[�^�̂P�O�ԖڂɃX�R�A��o�^
		inputRanking.SortRanking();		// �����L���O���בւ�
		inputRanking.SaveRanking();		// �����L���O�f�[�^�̕ۑ�
		a = 1;
	}
}
//�`��
void  Scene_Result::Draw() const
{
	// �t�H���g�T�C�Y�̐ݒ�
	SetFontSize(20);

	// ���O���͎w��������̕`��
	DrawString(150, 240, "�����L���O�ɓo�^���܂�", 0xFFFFFF);
	DrawString(150, 270, "���O���p���œ��͂��Ă�������", 0xFFFFFF);

	// ���O�̓���
	DrawString(150, 310, "> ", 0xFFFFFF);
	DrawBox(160, 305, 300, 335, 0x000055, TRUE);
}

//�V�[���̕ύX����
AbstractScene* Scene_Result::ChangeScene()
{
	//if (KeyManager::OnPadClicked(PAD_INPUT_A) == true)
	if (a == 1)
	{
		return new Scene_Ranking();
	}
	return this;
}