#include "Scene_Stage01.h"
#include"KeyManager.h"
#include"Scene_GameOver.h"
#include"Scene_GameClear.h"
#include"DxLib.h"
#include"GameData.h"
#include"SoundSystem.h"
#include"Scene_Ranking.h"

//�f�o�b�O���[�h
#include"Debug_Manager.h"

//�R���X�g���N�^
Scene_Stage01::Scene_Stage01(const Player* player)
	: Now_Tut_State(TUTORIAL_STATE::START_TUTORIAL)
{
	//�������Ԃ��Z�b�g
	GameData::Set_TimeLimit(10800);

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
	obj_enemy = new Enemy_01(1110, 680, Jan_Type::SCISSORS);

	//���E�ǂ̗p��
	Init_Floor(STAGE_01_FLOOR);

	//�������
	obj_floor[0] = new Floor(0, 700, 1280, 20);        //��
	obj_floor[1] = new Floor(0, 0, 20, 720);           //�ǁi���j
	obj_floor[2] = new Floor(1260, 0, 20, 720);        //�ǁi�E�j

	obj_floor[3] = new Floor(1100, 500, 120, 20, 0x006400);      //����No.01
	obj_floor[4] = new Floor(900, 290, 120, 20, 0x006400);       //����No.02
	obj_floor[5] = new Floor(330, 140, 460, 20, 0x006400);       //����No.03
	obj_floor[6] = new Floor(50, 290, 120, 20, 0x006400);        //����No.04
	obj_floor[7] = new Floor(250, 500, 120, 20, 0x006400);       //����No.05

	//�摜�ǂݍ���
	image_back = LoadGraph("images/stage01/Tutorial_Back.png");

	//BGM���[�h
	bgm = LoadSoundMem("Sound/stage01/maou_game_battle37.mp3");
	
}

//�f�X�g���N�^
Scene_Stage01::~Scene_Stage01()
{
	delete obj_enemy;
	DeleteSoundMem(bgm);
}

//�X�V
void Scene_Stage01::Update()
{
	//BGM�Đ�
	
	if (CheckSoundMem(bgm) == 0) PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);

	//�ڐG����񂯂�J�n�O
	if (GetJanState() == Jan_State::BEFORE)
	{
		obj_player->Update();    // �v���C���[�X�V�E����\
		obj_enemy->Update();     //�G�L�����X�V�E��������

		//���Ԃ��J�E���g
		GameData::Time_Update();


		//�v���C���[�̍��W���擾
		obj_enemy->SetPlayerLocation(obj_player->GetX(), obj_player->GetY());

	}

	//�ڐG����񂯂񏈗�
	Touch_Janken(obj_enemy, this, 1);
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
					//�G�t�F�N�g����
					//Play_Effect(player_jangeki[p_count]->GetX(), player_jangeki[p_count]->GetY(), 0);
					break;

				case 1:             //player�̂���񌂂��L��

					//enemy���̂���񌂂��폜
					obj_enemy->DeleteJangeki(e_count);
					e_count--;

					//�G�t�F�N�g����
					//Play_Effect(player_jangeki[p_count]->GetX(), player_jangeki[p_count]->GetY(),1);
					break;

				case 2:             //������

					//player���̂���񌂂��폜
					delete_player = true;

					//enemy���̂���񌂂��폜
					obj_enemy->DeleteJangeki(e_count);
					e_count--;

					//�G�t�F�N�g����
					//Play_Effect(player_jangeki[p_count]->GetX(), player_jangeki[p_count]->GetY(),2);
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

			int jan_damage = 10;    //�_���[�W

			//�s�������̂݃_���[�W������
			switch (enemy_type)
			{
			case Jan_Type::ROCK:                           //�G�̑����@�O�[

				//�p�[�̂���񌂂̂ݗL��
				if (jangeki_type == Jan_Type::PAPER)
				{
					obj_enemy->ReceiveDamage(jan_damage);  //�_���[�W������
					obj_player->DeleteJangeki(i);          //������������񌂂��폜
					i--;
				}

				break;

			case Jan_Type::SCISSORS:                       //�G�̑����@�`���L

				//�O�[�̂���񌂂̂ݗL��
				if (jangeki_type == Jan_Type::ROCK)
				{
					obj_enemy->ReceiveDamage(jan_damage);  //�_���[�W������
					obj_player->DeleteJangeki(i);          //������������񌂂��폜
					i--;
				}
				break;

			case Jan_Type::PAPER:                          //�G�̑����@�p�[

				//�`���L�̂���񌂂̂ݗL��
				if (jangeki_type == Jan_Type::SCISSORS)
				{
					obj_enemy->ReceiveDamage(jan_damage);  //�_���[�W������
					obj_player->DeleteJangeki(i);          //������������񌂂��폜
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
			obj_player->ReceiveDamage(5);

			//������������񌂂��폜
			obj_enemy->DeleteJangeki(i);
			i--;
		}
	}


	//�ǂƂ̓����蔻��
	if (obj_player->Get_X() <= 50 || obj_player->Get_X() >= 1220)
	{
		HitCtrl_Floor(obj_player, STAGE_01_FLOOR);     // player�@���E�ǔ���
	}

	//�v���C���[��y���W���������Ȃ����̂ݓ����蔻����擾
	if (obj_player->Get_Y() >= obj_player->Get_OldY() || obj_player->Get_Y() <= -200)
	{
		HitCtrl_Floor(obj_player, STAGE_01_FLOOR);     // player�@���E�ǔ���
	}

	//�G��y���W���������Ȃ����̂ݓ����蔻����擾
	if (obj_enemy->Get_Y() >= obj_enemy->Get_OldY() || obj_enemy->Get_Y() <= -200)
	{
		HitCtrl_Floor(obj_enemy, STAGE_01_FLOOR);      // �G�@�@�@���E�ǔ���

		//(x - (w / 2))
		//(y - (h / 2))
		//(x + (w / 2))
		//(y + (h / 2))
	}
}

//�`��
void Scene_Stage01::Draw() const
{
	//�w�i
	DrawGraph(0, 0, image_back, FALSE);

	//UI
	DrawUI(obj_enemy->GetType(), obj_enemy->GetHP());
	DrawUI_ON_Enemy(obj_enemy);

	//�ڐG����񂯂�J�n�O
	if (GetJanState() == Jan_State::START || GetJanState() == Jan_State::BEFORE)
	{
		//���E�Ǖ`��
		for (int i = 0; i < STAGE_01_FLOOR; i++)
		{
			if (obj_floor[i] == nullptr) break;
			obj_floor[i]->Draw();
		}
		obj_player->Draw();  //�v���C���[�`��
		obj_enemy->Draw();   //�G�L�����`��

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
void Scene_Stage01::Draw_Janken() const
{
	obj_janken->Draw();
}

//�V�[���̕ύX
AbstractScene* Scene_Stage01::ChangeScene()
{
#ifdef DEBUG_OFF_01

	//�G��HP��0�ȉ�
	if (IsEnd_DeathEnemy() == true)
	{

		//�Q�[���N���A�V�[���֐؂�ւ�
		return dynamic_cast<AbstractScene*> (new GameClearScene(2));
		//sortSave.setScore(9, 10);	// �����L���O�f�[�^�̂P�O�ԖڂɃX�R�A��o�^
		//sortSave.SortRanking();		// �����L���O���בւ�
		//sortSave.SaveRanking();		// �����L���O�f�[�^�̕ۑ�
		//return new Scene_Ranking();
	}

	//�v���C���[��HP��0�ȉ�
	if (obj_player->IsDeathPlayer() == true)
	{
		//�Q�[���I�[�o�[�V�[���֐؂�ւ�
		return dynamic_cast<AbstractScene*> (new GameOverScene(1));
	}

#endif 

	return this;   //�X�V�Ȃ�
}

//����񂯂�I����̋����i�v���C���[�����j
void Scene_Stage01::AfterJanken_WIN()
{
	obj_player->SetX(1280 / 2);
	//obj_player->SetY(500);

	//HP��S��
	obj_player->Recover_HP(100);
}

//����񂯂�I����̋����i�v���C���[�����j
void Scene_Stage01::AfterJanken_LOSE()
{
	obj_player->SetX(1280 / 2);
	//obj_player->SetY(500);
}