#include "Scene_Stage07.h"
#include"KeyManager.h"
#include"DxLib.h"
#include"GameData.h"

#include"Scene_GameOver.h"
#include"Scene_GameClear.h"

//�f�o�b�O���[�h
#include"Debug_Manager.h"

//�R���X�g���N�^
Scene_Stage07::Scene_Stage07(const Player* player)
{
	//�������Ԃ��Z�b�g
	GameData::Set_TimeLimit(6000);


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
	obj_enemy = new Enemy_07(900, 360, Jan_Type::SCISSORS);

	//���E�ǂ̗p��
	Init_Floor(STAGE_07_FLOOR);

	//�������  STAGE_07_FLOOR ��
	obj_floor[0] = new Floor(0, 700, 1280, 20);        //��
	obj_floor[1] = new Floor(0, 0, 20, 1720);          //�ǁi���j
	obj_floor[2] = new Floor(1260, 0, 20, 1720);       //�ǁi�E�j
	obj_floor[3] = new Floor("images/stage07/Ring.png", 220, 590, 840, 110);   //�����O
	obj_floor[4] = new Floor(220, 440, 30, 10, 0x007cfe);        //�R�[�i�[�|�X�g�i�����蔻��͏����@�@DrawBox�ŕ\���j
	obj_floor[5] = new Floor(1030, 440, 30, 10, 0x007cfe);       //�R�[�i�[�|�X�g�i�����蔻��͏����@�@DrawBox�ŕ\���j
	obj_floor[6] = new Floor(20, 230, 150, 20);        //����      
	obj_floor[7] = new Floor(1110, 230, 150, 20);      //����
	obj_floor[8] = new Floor(410, 110, 160, 20);       //����
	obj_floor[9] = new Floor(710, 110, 160, 20);       //����

	//�摜�ǂݍ���
	image_back = LoadGraph("images/stage07/back02.png");
	image_spotlight = LoadGraph("images/stage07/soptlight.png");
}

//�f�X�g���N�^
Scene_Stage07::~Scene_Stage07()
{
}

//�X�V
void Scene_Stage07::Update()
{
	//���Ԃ��J�E���g
	GameData::Time_Update();


	//�ڐG����񂯂�J�n�O
	if (GetJanState() == Jan_State::BEFORE)
	{
		obj_player->Update();    // �v���C���[�X�V�E����\
		obj_enemy->Update();     //�G�L�����X�V�E��������

		//�v���C���[�̍��W���擾
		obj_enemy->SetPlayerLocation(obj_player->GetX(), obj_player->GetY());

		//�v���C���[�������O�ォ
		obj_enemy->CheckPlayerState(obj_player);
	}
	
	//�ڐG����񂯂񏈗� (�G�̍s����"�_�C�u"�̎��͔���Ȃ�)
	if (obj_enemy->Is_Diving_TouchJanken() != true)
	{
		Touch_Janken(obj_enemy, this, 7);
	}

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
					obj_enemy->ReceiveDamage(10);     //�_���[�W������
					obj_enemy->Change_JanType();      //�������ς��

					obj_player->DeleteJangeki(i);     //������������񌂂��폜
					i--;
				}

				break;

			case Jan_Type::SCISSORS:                       //�G�̑����@�`���L

				//�O�[�̂���񌂂̂ݗL��
				if (jangeki_type == Jan_Type::ROCK)
				{
					obj_enemy->ReceiveDamage(10);     //�_���[�W������
					obj_enemy->Change_JanType();      //�������ς��

					obj_player->DeleteJangeki(i);     //������������񌂂��폜
					i--;
				}
				break;

			case Jan_Type::PAPER:                          //�G�̑����@�p�[

				//�`���L�̂���񌂂̂ݗL��
				if (jangeki_type == Jan_Type::SCISSORS)
				{
					obj_enemy->ReceiveDamage(10);     //�_���[�W������
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
			obj_player->ReceiveDamage(10);

			//������������񌂂��폜
			obj_enemy->DeleteJangeki(i);
			i--;
		}
	}

	HitCtrl_Floor(obj_player, STAGE_07_FLOOR);     // player�@���E�ǔ���

	//��ߺ�˰ہi�_�C�u�j���̏ꍇ�A������Ƃ�Ȃ�
	if (obj_enemy->Is_Diving_Collision() != true)
	{
		HitCtrl_Floor(obj_enemy, STAGE_07_FLOOR);      // �G�@�@�@���E�ǔ���
	}
	
}


//�`��
void Scene_Stage07::Draw() const
{
	//�w�i
	DrawGraph(0, 0, image_back, TRUE);

	//UI
	DrawUI(obj_enemy->GetType(), obj_enemy->GetHP());

	//DrawFormatString(300, 300, 0xffffff, "%d", GameData::Get_Score());

	//�e�X�g
	//DrawFormatString(300, 300, 0x00ff00, "p-x : %f   p-y : %f", obj_player->GetX(), obj_player->GetY());

	//�ڐG����񂯂�J�n�O
	if (GetJanState() == Jan_State::BEFORE)
	{

		obj_player->Draw();  //�v���C���[�`��
		obj_enemy->Draw();   //�G�L�����`��

		//���E�Ǖ`��
		for (int i = 0; i < STAGE_07_FLOOR; i++)
		{
			if (obj_floor[i] == nullptr) break;
			obj_floor[i]->Draw();
		}

		//�R�[�i�[�|�X�g
		DrawBox(220, 440, (220 + 30), (440 + 150), 0x007cfe, TRUE);    //��
		DrawBox(1030, 440, (1030 + 30), (440 + 150), 0x007cfe, TRUE);  //�E


		//���[�v
		DrawBox(250, 450, (250 + 780), (450 + 5), 0x000000, TRUE);     //�g�b�v���[�v
		DrawBox(250, 500, (250 + 780), (500 + 5), 0x000000, TRUE);     //�Z�J���h���[�v
		DrawBox(250, 550, (250 + 780), (550 + 5), 0x000000, TRUE);     //�T�[�h���[�v

		//�X�|�b�g���C�g�`��
		SetDrawBlendMode(DX_BLENDMODE_ADD_X4, 150);
		DrawGraph(0, 0, image_spotlight, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else
	{
		//�ڐG������񂯂�`��
		Draw_Janken();
	}
}

//����񂯂�`��
void Scene_Stage07::Draw_Janken() const
{
	obj_janken->Draw();
}


//����񂯂�I����̋����i�v���C���[�����j
void Scene_Stage07::AfterJanken_WIN()
{
	//obj_player->SetX(100);
	//obj_enemy->SetX(900);

	obj_enemy->Init_MoveAndAction();

}

//����񂯂�I����̋����i�v���C���[�����j
void Scene_Stage07::AfterJanken_LOSE()
{
	obj_player->SetX(100);
	obj_enemy->SetX(900);

	obj_enemy->Init_MoveAndAction();
}


//�V�[���̕ύX
AbstractScene* Scene_Stage07::ChangeScene()
{
#ifdef DEBUG_OFF_07

	//�G��HP��0�ȉ�
	if (obj_enemy->GetHP() < 0)
	{
		//�Q�[���N���A�V�[���֐؂�ւ�
		return dynamic_cast<AbstractScene*> (new GameClearScene(8));
	}

	//�v���C���[��HP��0�ȉ�
	if (obj_player->GetHP() < 0 || GameData::Get_Each_Time() <= 0)
	{
		//�Q�[���I�[�o�[�V�[���֐؂�ւ�
		return dynamic_cast<AbstractScene*> (new GameOverScene(7));
	}

#endif // DEBUG_OFF_07

	return this;
}