#include "Scene_Stage04.h"
#include"KeyManager.h"
#include"DxLib.h"
#include"Scene_GameOver.h"
#include"Scene_GameClear.h"
#include"GameData.h"
#include"SoundSystem.h"

//�f�o�b�O���[�h
#include"Debug_Manager.h"

//�R���X�g���N�^
Scene_Stage04::Scene_Stage04(const Player* player)
{
	//�������Ԃ��Z�b�g(3����)
	GameData::Set_TimeLimit(10800);

	back_image = LoadGraph("images/Stage04/Stage_Image2.png");

	//�v���C���[��񂪓n����Ă����
	if (player != nullptr)
	{
		//���������p�����v���C���[�𐶐�
		obj_player = new Player(*player);
	}
	else
	{
		//�v���C���[�𐶐�
		obj_player = new Player(640, 360);
	}

	//�G�𐶐�
	obj_enemy = new Enemy_04(1100, 360, Jan_Type::SCISSORS);

	//���E�ǂ̗p��
	Init_Floor(STAGE_04_FLOOR);

	//�������  STAGE_04_FLOOR ��
	obj_floor[0] = new Floor(0,  700, 1280,   20, 0x493759);		//��
	obj_floor[1] = new Floor(0,    0,   20, 1720, 0x493759);		//�ǁi���j
	obj_floor[2] = new Floor(1260, 0,   20, 1720, 0x493759);		//�ǁi�E�j
	obj_floor[3] = new Floor(300, 500, 200, 10, 0x493759);			//����(����)
	obj_floor[4] = new Floor(650, 450, 150, 10, 0x493759);			//����(�^�񒆉�)
	obj_floor[5] = new Floor(400, 250, 150, 10, 0x493759);			//����(�㉡)
	obj_floor[6] = new Floor(390, 425, 10, 170, 0x493759);			//����(���c)
	obj_floor[7] = new Floor(717, 395, 10, 130, 0x493759);			//����(�^�񒆏c)
	obj_floor[8] = new Floor(467, 195, 10, 130, 0x493759);			//����(��c)
	obj_floor[9] = new Floor(850, 250, 150, 10, 0x493759);			//����(�E��)
	obj_floor[10] = new Floor(917, 195, 10, 130, 0x493759);			//����(�E�c)
	obj_floor[11] = new Floor(80, 300, 150, 10, 0x493759);			//����Ǎۍ��@
	obj_floor[12] = new Floor(80, 500, 120, 10, 0x493759);			//����Ǎۍ��A
	obj_floor[13] = new Floor(1100, 350, 100,  10, 0x493759);	    //����ǍۉE�@
	obj_floor[14] = new Floor(1050, 510, 130,  10, 0x493759);		//����ǍۉE�A
}

//�f�X�g���N�^
Scene_Stage04::~Scene_Stage04()
{
}

//�X�V
void Scene_Stage04::Update()
{
	//BGM�Đ�
	SoundSystem::PlayBGM(BGM::STAGE04_BGM);

	//�ڐG����񂯂�J�n�O
	if (GetJanState() == Jan_State::BEFORE)
	{
		obj_player->Update();    // �v���C���[�X�V�E����\
		obj_enemy->Update();     //�G�L�����X�V�E��������
		obj_enemy->SetPlayerLocation(obj_player->GetX(), obj_player->GetY());	//�v���C���[�̍��W���擾

		//���Ԃ��J�E���g
		GameData::Time_Update();
	}

	//�ڐG����񂯂񏈗�
	Touch_Janken(obj_enemy, this, 4);

	Effect_Update_HitJangeki(obj_enemy);

	//player�̂���񌂂��Ƃ��Ă���
	Jangeki_Base** player_jangeki = obj_player->GetJangeki();

	//enemy�̂���񌂂��Ƃ��Ă���
	Jangeki_Base** enemy_jangeki = obj_enemy->GetJangeki();

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//����񌂓��m�̓����蔻��i�v���C���[����񌂖ڐ��j
	for (int p_count = 0; p_count < JANGEKI_MAX; p_count++)
	{
		if (player_jangeki[p_count] == nullptr) break;         //����񌂂��Ȃ����͏������Ȃ�

		bool delete_player = false;       //�v���C���[����񌂍폜�t���O�@true:�폜�@false:�폜���Ȃ�

		for (int e_count = 0; e_count < JANGEKI_MAX; e_count++)
		{
			if (enemy_jangeki[e_count] == nullptr) break;         //����񌂂��Ȃ����͏������Ȃ�

			if (player_jangeki[p_count]->Hit_Jangeki(enemy_jangeki[e_count]) == true)
			{
				//�L�������`�F�b�N
				int result = player_jangeki[p_count]->CheckAdvantage(enemy_jangeki[e_count]);

				switch (result)
				{
				case 0:             //player�̂���񌂂��s��

					//player���̂���񌂂��폜
					delete_player = true;

					break;

				case 1:             //player�̂���񌂂��L��

					//enemy���̂���񌂂��폜
					obj_enemy->DeleteJangeki(e_count);
					e_count--;

					break;

				case 2:             //������

					//player���̂���񌂂��폜
					delete_player = true;

					//enemy���̂���񌂂��폜
					obj_enemy->DeleteJangeki(e_count);
					e_count--;

					break;

				default:
					break;
				}
			}
		}

		//�v���C���[����񌂍폜�t���O��true
		if (delete_player == true)
		{
			//player���̂���񌂂��폜
			obj_player->DeleteJangeki(p_count);
			p_count--;
		}
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//player����񌂂�enemy�̓����蔻��
	for (int i = 0; i < JANGEKI_MAX; i++)
	{
		if (player_jangeki[i] == nullptr) break;         //����񌂂��Ȃ����͏������Ȃ�

		//����񌂂Ƃ̓����蔻��
		if (obj_enemy->Hit_Jangeki(player_jangeki[i]) == true)
		{
			Jan_Type enemy_type = obj_enemy->GetType();            //�G�̑���
			Jan_Type jangeki_type = player_jangeki[i]->GetType();  //������������񌂂̑���

			//�s�������̂݃_���[�W������
			switch (enemy_type)
			{
			case Jan_Type::ROCK:                           //�G�̑����@�O�[

				//�p�[�̂���񌂂̂ݗL��
				if (jangeki_type == Jan_Type::PAPER)
				{
					obj_enemy->ReceiveDamage(15);     //�_���[�W������
					obj_enemy->Change_JanType();      //�������ς��
					obj_player->DeleteJangeki(i);     //������������񌂂��폜
					i--;
				}

				break;

			case Jan_Type::SCISSORS:                       //�G�̑����@�`���L

				//�O�[�̂���񌂂̂ݗL��
				if (jangeki_type == Jan_Type::ROCK)
				{
					obj_enemy->ReceiveDamage(15);     //�_���[�W������
					obj_enemy->Change_JanType();      //�������ς��
					obj_player->DeleteJangeki(i);     //������������񌂂��폜
					i--;
				}
				break;

			case Jan_Type::PAPER:                          //�G�̑����@�p�[

				//�`���L�̂���񌂂̂ݗL��
				if (jangeki_type == Jan_Type::SCISSORS)
				{
					obj_enemy->ReceiveDamage(15);     //�_���[�W������
					obj_enemy->Change_JanType();      //�������ς��
					obj_player->DeleteJangeki(i);     //������������񌂂��폜
					i--;
				}
				break;

			default:
				break;
			}
		}
	}


	//enemy����񌂂�player�̓����蔻��
	for (int i = 0; i < JANGEKI_MAX; i++)
	{
		//����񌂂��Ȃ����͏������Ȃ�
		if (enemy_jangeki[i] == nullptr) break;

		//����񌂂Ƃ̓����蔻��
		if (obj_player->Hit_Jangeki(enemy_jangeki[i]) == true)
		{
			//�_���[�W���󂯂�i�v���C���[�j
			obj_player->ReceiveDamage(20);

			//������������񌂂��폜
			obj_enemy->DeleteJangeki(i);
			i--;
		}
	}


	//HitCtrl_Floor(obj_player, STAGE_04_FLOOR);     // player�@���E�ǔ���

	////�ǂƂ̓����蔻��
	if (obj_player->Get_X() <= 50 || obj_player->Get_X() >= 1200)
	{
		HitCtrl_Floor(obj_player, STAGE_04_FLOOR);     // player�@���E�ǔ���
	}

	//�v���C���[��y���W���������Ȃ����̂ݓ����蔻����擾
	if (obj_player->Get_Y() >= obj_player->Get_OldY())
	{
		HitCtrl_Floor(obj_player, STAGE_04_FLOOR);     // player�@���E�ǔ���
	}
}


//�`��
void Scene_Stage04::Draw() const
{
	//�X�e�[�W�w�i�`��
	DrawRotaGraph(640, 360, 1, 0, back_image, FALSE);

	DrawUI(obj_enemy->GetType(),obj_enemy->GetHP());
	DrawUI_ON_Enemy(obj_enemy);

	//�ڐG����񂯂�łȂ���
	if (GetJanState() == Jan_State::START || GetJanState() == Jan_State::BEFORE)
	{

		obj_player->Draw();  //�v���C���[�`��
		obj_enemy->Draw();   //�G�L�����`��

		//���E�Ǖ`��
		for (int i = 0; i < STAGE_04_FLOOR; i++)
		{
			if (obj_floor[i] == nullptr) break;
			obj_floor[i]->Draw();
		}

		//�ڐG�����u�Ԃ̉��o
		if (GetJanState() == Jan_State::START) Draw_JankenStart();
	}
	else
	{
		//�ڐG������񂯂�`��
		Draw_Janken();
	}

	//Effect
	Effect_Draw_HitJangeki();
}

//����񂯂�`��
void Scene_Stage04::Draw_Janken() const
{
	obj_janken->Draw();
}

//�V�[���̕ύX
AbstractScene* Scene_Stage04::ChangeScene()
{
	//"Debug_Manager.h" �� #define DEBUG_OFF_04 ���R�����g�A�E�g����ƊJ�����[�h
#ifdef DEBUG_OFF_04

	//�G��HP��0�ȉ�
	if (IsEnd_DeathEnemy() == true)
	{
		//BGM��~
		SoundSystem::StopBGM(BGM::STAGE04_BGM);
		//�Q�[���N���A�V�[���֐؂�ւ�
		return dynamic_cast<AbstractScene*> (new GameClearScene(5));
	}

	//�v���C���[��HP��0�ȉ�
	if (obj_player->IsDeathPlayer() == true)
	{
		//BGM��~
		SoundSystem::StopBGM(BGM::STAGE04_BGM);
		//�Q�[���I�[�o�[�V�[���֐؂�ւ�
		return dynamic_cast<AbstractScene*> (new GameOverScene(4));
	}

#endif // DEBUG_OFF_04

	return this;
}

//����񂯂�I����̋����i�v���C���[�����j
void Scene_Stage04::AfterJanken_WIN()
{
	obj_player->Recover_HP(50);
	obj_player->SetX(260);
	obj_player->SetY(620);
	obj_enemy->SetX(1180);
}

//����񂯂�I����̋����i�v���C���[�����j
void Scene_Stage04::AfterJanken_LOSE()
{
	obj_enemy->Special_Action();
	obj_player->SetX(260);
	obj_player->SetY(620);
	obj_enemy->SetX(1180);
}