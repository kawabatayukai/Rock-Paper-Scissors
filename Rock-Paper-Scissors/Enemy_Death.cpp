#include "Enemy_Death.h"
#include"DxLib.h"

Enemy_Death::Enemy_Death(const float& x, const float& y, const int& stage_num,const Jan_Type& type)
	:CharaBase(x, y, 0, 0)
{
	switch (stage_num)
	{
	case 1:
		image_death = LoadGraph("images/Death/stage01_death.png");
		break;
	case 2:
		image_death = LoadGraph("images/Death/stage02_death.png");
		break;
	case 3:
		image_death = LoadGraph("images/Death/stage03_death.png");
		break;
	case 4:
		image_death = LoadGraph("images/ワンパンマン顔のみ左.png");
		break;
	case 5:
		image_death = LoadGraph("images/Death/stage05_death.png");
		break;
	case 6:
	{
		int* image = new int[3];
		LoadDivGraph("images/Death/stage06_death.png", 3, 3, 1, 100, 100, image);
		image_death = image[static_cast<int>(type)];
		delete[] image;
	}
		break;
	case 7:
		image_death = LoadGraph("images/Death/stage07_death.png");
		break;
	case 8:
		image_death = LoadGraph("images/Death/stage08_death.png");
		break;
	case 9:
		image_death = LoadGraph("images/Death/stage09_death.png");
		break;
	case 10:
		image_death = LoadGraph("images/ワンパンマン顔のみ左.png");
		break;

	default:
		image_death = LoadGraph("images/ワンパンマン顔のみ左.png");
		break;
	}

	se_death = LoadSoundMem("Sound/Janken/「ぐああーーっ！」.mp3");

	g_add = -24.5f;    //重力加速度をマイナス値に
	old_y = y;
	land_flg = false;  //地面についていない
}

Enemy_Death::~Enemy_Death()
{
	DeleteSoundMem(se_death);
}

void Enemy_Death::Update()
{
	/********************   ジャンプ関係   ********************/

	y_add = (y - old_y) + g_add;  //今回の落下距離を設定

	//落下速度の制限
	

	old_y = y;                    //1フレーム前のｙ座標
	y += y_add;                   //落下距離をｙ座標に加算する
	g_add = _GRAVITY;              //重力加速度を初期化する

	if (y > old_y) land_flg = false;

	/**********************************************************/

	if (CheckSoundMem(se_death) == 0) PlaySoundMem(se_death, DX_PLAYTYPE_BACK);
}

void Enemy_Death::Draw() const
{
	DrawRotaGraphF(x, y, 1, 0, image_death, TRUE);
}

//死亡演出完了
bool Enemy_Death::IsDeathEnd()
{
	if (y > 780) return true;

	return false;
}
