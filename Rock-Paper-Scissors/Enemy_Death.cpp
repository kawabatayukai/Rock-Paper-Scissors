#include "Enemy_Death.h"
#include"DxLib.h"

Enemy_Death::Enemy_Death(const float& x, const float& y, const int& stage_num,const Jan_Type& type)
	:CharaBase(x, y, 0, 0)
{
	switch (stage_num)
	{
	case 1:
		image_death = LoadGraph("images/Death/stage01_death.png");
		se_death = LoadSoundMem("Sound/Janken/���E�j���g��01.mp3");
		break;
	case 2:
		image_death = LoadGraph("images/Death/stage02_death.png");
		se_death = LoadSoundMem("Sound/Janken/�J�G��03.mp3");
		break;
	case 3:
		image_death = LoadGraph("images/Death/stage03_death.png");
		se_death = LoadSoundMem("Sound/Janken/�悭�킩��Ȃ��@�B��.wav");
		break;
	case 4:
		image_death = LoadGraph("images/Death/stage04_death.png");
		se_death = LoadSoundMem("Sound/Janken/�u�������[�[���I�v.mp3");
		break;
	case 5:
		image_death = LoadGraph("images/Death/stage05_death.png");
		se_death = LoadSoundMem("Sound/Janken/�u�������[�[���I�v.mp3");
		break;
	case 6:
	{
		int* image = new int[3];
		LoadDivGraph("images/Death/stage06_death.png", 3, 3, 1, 100, 100, image);
		image_death = image[static_cast<int>(type)];
		se_death = LoadSoundMem("Sound/Janken/�u�������[�[���I�v.mp3");
		delete[] image;
	}
		break;
	case 7:
		image_death = LoadGraph("images/Death/stage07_death.png");
		se_death = LoadSoundMem("Sound/Janken/�u�������[�[���I�v.mp3");
		break;
	case 8:
		image_death = LoadGraph("images/Death/stage08_death.png");
		se_death = LoadSoundMem("Sound/Janken/�u�������[�[���I�v.mp3");
		break;
	case 9:
		image_death = LoadGraph("images/Death/stage09_death.png");
		se_death = LoadSoundMem("Sound/Janken/�u�������[�[���I�v.mp3");
		break;
	case 10:
		image_death = LoadGraph("images/�����p���}����̂ݍ�.png");
		se_death = LoadSoundMem("Sound/Janken/�u�������[�[���I�v.mp3");
		break;

	default:
		image_death = LoadGraph("images/�����p���}����̂ݍ�.png");
		break;
	}

	g_add = -24.5f;    //�d�͉����x���}�C�i�X�l��
	old_y = y;
	land_flg = false;  //�n�ʂɂ��Ă��Ȃ�
}

Enemy_Death::~Enemy_Death()
{
	DeleteSoundMem(se_death);
}

void Enemy_Death::Update()
{
	/********************   �W�����v�֌W   ********************/

	y_add = (y - old_y) + g_add;  //����̗���������ݒ�

	//�������x�̐���
	

	old_y = y;                    //1�t���[���O�̂����W
	y += y_add;                   //���������������W�ɉ��Z����
	g_add = _GRAVITY;              //�d�͉����x������������

	if (y > old_y) land_flg = false;

	/**********************************************************/

	if (CheckSoundMem(se_death) == 0) PlaySoundMem(se_death, DX_PLAYTYPE_BACK);
}

void Enemy_Death::Draw() const
{
	DrawRotaGraphF(x, y, 1, 0, image_death, TRUE);
}

//���S���o����
bool Enemy_Death::IsDeathEnd()
{
	if (y > 780) return true;

	return false;
}
