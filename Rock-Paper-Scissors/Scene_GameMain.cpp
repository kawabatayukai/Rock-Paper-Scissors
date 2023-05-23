#include"DxLib.h"
#include"Scene_GameMain.h"
#include"KeyManager.h"

#include"Scene_Stage00.h"
#include"Scene_Stage01.h"
#include"Scene_Stage02.h"
#include"Scene_Stage03.h"
#include"Scene_Stage04.h"
#include"Scene_Stage05.h"
#include"Scene_Stage06.h"
#include"Scene_Stage07.h"
#include"Scene_Stage08.h"
#include"Scene_Stage09.h"
#include"Scene_Stage10.h"

#include"Scene_End.h"
#include"Scene_Help.h"
#include"Scene_GameClear.h"
#include"Scene_GameOver.h"

#include"Scene_InputNameRanking.h"


//�R���X�g���N�^
GameMainScene::GameMainScene()
{
	//�v���C���[�����@�@�@�@�������W��ݒ�
	obj_player = new Player(640.f, 360.f);

	//���̃��������m��
	obj_floor = new Floor * [1];

	//������
	for (int i = 0; i < 1; i++) obj_floor[i] = nullptr;
	obj_floor[0] = new Floor(0, 700, 1280, 40);

	//�t�H���g�̃T�C�Y�ݒ�
	SetFontSize(40);
}

//�f�X�g���N�^
GameMainScene::~GameMainScene()
{
	SetFontSize(20);

	delete obj_player;
	delete[] obj_floor;
}

//�X�V
void GameMainScene::Update()
{
	if (KeyManager::OnPadClicked(PAD_INPUT_RIGHT) == true)
	{
		select_num++;

		if (select_num > 15) select_num = 0;
	}

	if (KeyManager::OnPadClicked(PAD_INPUT_LEFT) == true)
	{
		select_num--;

		if (select_num < 0) select_num = 15;
	}

	obj_player->Update();
	obj_player->Hit_Floor(obj_floor[0]);
}

//�`��
void GameMainScene::Draw() const
{

	//�t�H���g�̃T�C�Y�ݒ�
	SetFontSize(40);

	DrawString(0, 100, "�Q�[�����C��", 0xffffff);

	DrawString(340, 300, "�����̒S���X�e�[�W��I��ł�������", 0xffffff);
	DrawString(340, 350, "A�{�^���Ō���", 0xffffff);

	DrawString(100, 400, " �� 1  2  3  4  5  6  7  8  9 10  E H GO GC INR", 0xffffff);

	DrawCircle(140 + (select_num * 60), 415, 30, 0xffff00, FALSE, 3);

	obj_floor[0]->Draw();
	obj_player->Draw();
}

//�V�[���̕ύX
AbstractScene* GameMainScene::ChangeScene()
{
	//A�{�^��
	if (KeyManager::OnPadClicked(PAD_INPUT_A) == true)
	{
		//�e�X�e�[�W��
		switch (select_num)
		{
		case 0:
			return dynamic_cast<AbstractScene*> (new Scene_Stage00(obj_player));
			break;

		case 1:
			return dynamic_cast<AbstractScene*> (new Scene_Stage01());
			break;

		case 2:
			return dynamic_cast<AbstractScene*> (new Scene_Stage02());
			break;

		case 3:
			return dynamic_cast<AbstractScene*> (new Scene_Stage03());
			break;

		case 4:
			return dynamic_cast<AbstractScene*> (new Scene_Stage08());
			break;

		case 5:
			return dynamic_cast<AbstractScene*> (new Scene_Stage05());
			break;

		case 6:
			return dynamic_cast<AbstractScene*> (new Scene_Stage06());
			break;

		case 7:
			return dynamic_cast<AbstractScene*> (new Scene_Stage07());
			break;

		case 8:
			return dynamic_cast<AbstractScene*> (new Scene_Stage04());
			break;

		case 9:
			return dynamic_cast<AbstractScene*> (new Scene_Stage09());
			break;

		case 10:
			return dynamic_cast<AbstractScene*> (new Scene_Stage10());
			break;

		case 11:
			return dynamic_cast<AbstractScene*> (new EndScene());
			break;

		case 12:
			return dynamic_cast<AbstractScene*> (new HelpScene());
			break;

		case 13:
			return dynamic_cast<AbstractScene*> (new GameOverScene(0));
			break;

		case 14:
			return dynamic_cast<AbstractScene*> (new GameClearScene(1));
			break;

		case 15:
			return dynamic_cast<AbstractScene*> (new Scene_InputNameRanking());
			break;



		default:
			break;
		}

	}


	//return dynamic_cast<AbstractScene*> (new Scene_Stage00());
	

	return this;
}