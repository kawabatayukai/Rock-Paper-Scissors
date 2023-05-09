#include "Scene_Stage09.h"
#include"KeyManager.h"
#include"DxLib.h"
#include"Scene_GameOver.h"
#include "Scene_GameClear.h"
#include"Scene_Stage10.h"
#include"GameData.h"


//�f�o�b�O���[�h
#include"Debug_Manager.h"

//�R���X�g���N�^
Scene_Stage09::Scene_Stage09(const Player* player)
{

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
	obj_enemy = new Enemy_09(1110, 480, Jan_Type::NONE);

	reflection = new Jangeki_Reflection(0, 0, 0, 0, Jan_Type::ROCK);

	stageimage = LoadGraph("images/stage09/stage09_image.png");



	//���E�ǂ̗p��
	Init_Floor(STAGE_09_FLOOR);

	//�������  STAGE_09_FLOOR ��
	obj_floor[0] = new Floor(0, 700, 1280, 20);        //��
	obj_floor[1] = new Floor(0, -200, 20, 1720);           //�ǁi���j
	obj_floor[2] = new Floor(1260, -200, 20, 1720);           //�ǁi�E�j
	//����   ����
	obj_floor[3] = new Floor(100, 500, 120, 20, 0xd2d2d2);
	obj_floor[4] = new Floor(300, 325, 120, 20, 0xd2d2d2);
	obj_floor[5] = new Floor(100, 150, 120, 20, 0xd2d2d2);
	//����   �E��
	obj_floor[6] = new Floor(1050, 500, 120, 20, 0xd2d2d2);
	obj_floor[7] = new Floor(850, 325, 120, 20, 0xd2d2d2);
	obj_floor[8] = new Floor(1050, 150, 120, 20, 0xd2d2d2);
	//����   ����
	obj_floor[9] = new Floor(560, 450, 120, 20, 0xd2d2d2);
	obj_floor[10] = new Floor(560, 130, 120, 20, 0xd2d2d2);

}

//�f�X�g���N�^
Scene_Stage09::~Scene_Stage09()
{
}

//�X�V
void Scene_Stage09::Update()
{
	//�ڐG����񂯂�J�n�O
	if (GetJanState() == Jan_State::BEFORE)
	{
		obj_player->Update();    // �v���C���[�X�V�E����\

		//�iplayer���j�G�̍��W���擾
		obj_player->SetEnemyLocation(obj_enemy->GetX(), obj_enemy->GetY());

		obj_enemy->Update();     //�G�L�����X�V�E��������
		obj_enemy->reflection->Update_reflection();
		//�v���C���[�̍��W���擾
		obj_enemy->SetPlayerLocation(obj_player->GetX(), obj_player->GetY());

		GameData::Time_Update();
	}

	//�ڐG����񂯂񏈗�
	//����s�����ƃA�j���[�V�����Đ����͂Ȃ�
	if (obj_enemy->Spflg == false && obj_enemy->animflg == false)
		Touch_Janken(obj_enemy, this, 9);

	Effect_Update_HitJangeki(obj_enemy);

	//player�̂���񌂂��Ƃ��Ă���
	Jangeki_Base** player_jangeki = obj_player->GetJangeki();

	//enemy�̂���񌂂��Ƃ��Ă���
	Jangeki_Base** enemy_jangeki = obj_enemy->GetJangeki();

	//���˂��ꂽ����񌂂��Ƃ��Ă���
	Jangeki_Base** reflection_jangeki = obj_enemy->reflection->GetJangeki();

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//����񌂓��m�̓����蔻��i�v���C���[����񌂖ڐ��j
	for (int p_count = 0; p_count < JANGEKI_MAX; p_count++)
	{
		if (player_jangeki[p_count] == nullptr) break;         //����񌂂��Ȃ����͏������Ȃ�

		bool delete_player = false;       //�v���C���[����񌂍폜�t���O�@true:�폜�@false:�폜���Ȃ�

		for (int e_count = 0; e_count < JANGEKI_MAX; e_count++)
		{
			if (enemy_jangeki[e_count] == nullptr) break;         //����񌂂��Ȃ����͏������Ȃ�uuuuuuuuuuuuuuuuuuuuuuu

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
					if (player_jangeki[p_count]->GetR() != 35.f)
					{
						delete_player = true;
					}

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

		if (obj_enemy->animflg == false) {
			//����񌂂Ƃ̓����蔻��
			if (obj_enemy->Hit_Jangeki(player_jangeki[i]) == true)
			{

				if (player_jangeki[i]->GetR() == 35.f || obj_enemy->Getflg() == true)
				{
					obj_enemy->ReceiveDamage(20);
					//������������񌂂��폜
					obj_player->DeleteJangeki(i);
					i--;
					if (obj_enemy->Getflg() == true)obj_enemy->Fflg();
				}
				else
				{
					obj_player->DeleteJangeki(i);     //������������񌂂��폜
					i--;
					obj_enemy->reflection->trueFlg();
				}
			}
			obj_enemy->HP();

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
			//����s������10�_���[�W
			if (enemy_jangeki[i]->GetR()==40.f)obj_player->ReceiveDamage(10);
			else obj_player->ReceiveDamage(30);
			
			//������������񌂂��폜
			obj_enemy->DeleteJangeki(i);
			i--;
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���˂���񌂓����蔻��

	//���˂��ꂽ����񌂂�player����񌂂̓����蔻��
	for (int p_count = 0; p_count < JANGEKI_MAX; p_count++)
	{
		if (player_jangeki[p_count] == nullptr) break;         //����񌂂��Ȃ����͏������Ȃ�

		bool delete_player = false;       //�v���C���[����񌂍폜�t���O�@true:�폜�@false:�폜���Ȃ�

		for (int r_count = 0; r_count < JANGEKI_MAX; r_count++)
		{
			if (reflection_jangeki[r_count] == nullptr) break;         //����񌂂��Ȃ����͏������Ȃ�

			if (player_jangeki[p_count]->Hit_Jangeki(reflection_jangeki[r_count]) == true)
			{
				//�L�������`�F�b�N
				int result = player_jangeki[p_count]->CheckAdvantage(reflection_jangeki[r_count]);

				switch (result)
				{
				case 0:             //player�̂���񌂂��s��

					//player���̂���񌂂��폜
					delete_player = true;

					break;

				case 1:             //player�̂���񌂂��L��

					//enemy���̂���񌂂��폜
					obj_enemy->reflection->Delete_reflectionJangeki(r_count);
					r_count--;

					//�z�[�~���O����ꐶ��
					obj_player->Create_Homing(p_count, player_jangeki[p_count]->GetX(), player_jangeki[p_count]->GetY(), 35.f, 10, player_jangeki[p_count]->GetType());

					break;

				case 2:             //������

					//player���̂���񌂂��폜
					delete_player = true;

					//enemy���̂���񌂂��폜
					obj_enemy->reflection->Delete_reflectionJangeki(r_count);
					r_count--;

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


	//���˂��ꂽ����񌂂ƃv���C���[�̓����蔻��
	for (int i = 0; i < JANGEKI_MAX; i++)
	{
		//����񌂂��Ȃ����͏������Ȃ�
		if (reflection_jangeki[i] == nullptr) break;
		//����񌂂Ƃ̓����蔻��
		if (obj_player->Hit_Jangeki(reflection_jangeki[i]) == true)
		{
			
			//�_���[�W���󂯂�i�v���C���[�j
			obj_player->ReceiveDamage(20);

			//������������񌂂��폜
			obj_enemy->reflection->Delete_reflectionJangeki(i);
			i--;
		}
	}


	//�ǂƂ̓����蔻��
	if (obj_player->Get_X() <= 50 || obj_player->Get_X() >= 1200)
	{
		HitCtrl_Floor(obj_player, STAGE_09_FLOOR);     // player�@���E�ǔ���
	}

	//�v���C���[��y���W���������Ȃ����̂ݓ����蔻����擾
	if (obj_player->Get_Y() >= obj_player->Get_OldY())
	{
		HitCtrl_Floor(obj_player, STAGE_09_FLOOR);     // player�@���E�ǔ���
	}
	HitCtrl_Floor(obj_enemy, STAGE_09_FLOOR);      // �G�@�@�@���E�ǔ���
}


//�`��
void Scene_Stage09::Draw() const
{

	DrawGraph(0, 0, stageimage, false);
	
	//HP�\��
	DrawUI(obj_enemy->GetType(), obj_enemy->GetHP());
	DrawUI_ON_Enemy(obj_enemy);

	//�ڐG����񂯂�łȂ���
	if (GetJanState() == Jan_State::START || GetJanState() == Jan_State::BEFORE)
	{

		obj_player->Draw();  //�v���C���[�`��
		obj_enemy->Draw();   //�G�L�����`��
		obj_enemy->reflection->Draw_reflectionJangeki();


		//���E�Ǖ`��
		for (int i = 0; i < STAGE_09_FLOOR; i++)
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

	DrawString(640, 360, "Stage09", 0xffffff);
	Effect_Draw_HitJangeki();
}


//����񂯂�`��
void Scene_Stage09::Draw_Janken() const
{
	obj_janken->Draw();
}

//�V�[���̕ύX
AbstractScene* Scene_Stage09::ChangeScene()
{
	//"Debug_Manager.h" �� #define DEBUG_OFF_09 ���R�����g�A�E�g����ƊJ�����[�h
#ifdef DEBUG_OFF_09

	//�G��HP��0�ȉ�
	if (clearFlg == true)
	{
		//�Q�[���N���A�V�[���֐؂�ւ�
		return dynamic_cast<AbstractScene*> (new GameClearScene(10));
	}

	//�v���C���[��HP��0�ȉ�
	if (obj_player->IsDeathPlayer() == true)
	{
		//�Q�[���I�[�o�[�V�[���֐؂�ւ�
		return dynamic_cast<AbstractScene*> (new GameOverScene(9));
	}

#endif  DEBUG_OFF_09

	return this;
}

//����񂯂�I����̋����i�v���C���[�����j
void Scene_Stage09::AfterJanken_WIN()
{
	
	if (obj_enemy->GetHP() == 1)
	{
		clearFlg = true;
	}
	obj_player->SetX(100);
	obj_enemy->SetX(1110);
	obj_enemy->frameDown();
	obj_enemy->Tflg();
}
//����񂯂�I����̋����i�v���C���[�����j
void Scene_Stage09::AfterJanken_LOSE()
{

	if (obj_enemy->GetHP() == 1)
	{
		obj_enemy->SetHP(-hp);
		hp = hp / 2;
		if (GameData::Get_Total_Time() <= 3600)
			GameData::Set_TimeLimit(5400);
	}
	
	obj_player->SetX(100);
	obj_enemy->SetX(1110);
	obj_enemy->frameUP();
	obj_enemy->Spflg = true;

}