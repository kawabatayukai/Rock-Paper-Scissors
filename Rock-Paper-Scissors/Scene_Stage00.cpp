#include"DxLib.h"
#include"KeyManager.h"
#include "Scene_Stage00.h"
#include"Scene_GameMain.h"
#include"Janken.h"

//�f�o�b�O���[�h
#include"Debug_Manager.h"

//�R���X�g���N�^
Scene_Stage00::Scene_Stage00(const Player* player) : frame_count(0)
{
	//�摜�ꗗ
	int players[10];
	LoadDivGraph("images/�����p���}��ALL�摜�r����.png", 10, 5, 2, 100, 100, players);

	player_image = players[0];
	player_all = LoadGraph("images/�����p���}��ALL�摜�r����.png");

	enemy_02 = LoadGraph("images/stage02/ex.png");
	enemy_03 = LoadGraph("images/stage03/stage03gard.png");
	enemy_04 = LoadGraph("images/Stage4/�X�e�[�W4_�{�X100.png");
	enemy_05 = LoadGraph("images/stage05/Stage5_Enemy_NoMove_Left.png");
	enemy_06 = LoadGraph("images/tyokitest.png");
	enemy_07 = LoadGraph("images/tyokitest.png");
	enemy_08 = LoadGraph("images/stage08/Stage8_image100.png");
	enemy_09 = LoadGraph("images/stage09/Stage9_100.png");
	enemy_10 = LoadGraph("images/tyokitest.png");
}

//�f�X�g���N�^
Scene_Stage00::~Scene_Stage00()
{
}

//�X�V
void Scene_Stage00::Update()
{
	frame_count++;
	if (frame_count > 60) frame_count = 0;

	return;
}

//�`��
void Scene_Stage00::Draw() const
{
	DrawBox(0, 0, 1280, 720, 0xffffff, TRUE);

	//���ׂẴL������`��
	DrawGraph(50, 0, player_image, TRUE);
	DrawGraph(200, 0, enemy_02, TRUE);
	DrawGraph(350, 0, enemy_03, TRUE);
	DrawGraph(500, 0, enemy_04, TRUE);
	DrawGraph(650, 0, enemy_05, TRUE);
	DrawGraph(50, 150, enemy_06, TRUE);
	DrawGraph(200, 150, enemy_07, TRUE);
	DrawGraph(350, 150, enemy_08, TRUE);
	DrawGraph(500, 150, enemy_09, TRUE);
	DrawGraph(650, 150, enemy_10, TRUE);

	DrawGraph(50, 350, player_all, TRUE);

	if (frame_count < 30) DrawString(350, 670, "Press A Button To SelectScene", 0x006400);
}



//�V�[���̕ύX
AbstractScene* Scene_Stage00::ChangeScene()
{
#ifdef DEBUG_OFF_00

	//A�{�^���ŃQ�[�����C���ɖ߂�
	if (KeyManager::OnPadClicked(PAD_INPUT_A))
	{
		return dynamic_cast<AbstractScene*> (new GameMainScene());
	}
		
#endif // _DEBUG_MODE_00

	return this;   //�X�V�Ȃ�
}
