#include "Scene_Stage06.h"
#include"KeyManager.h"
#include"DxLib.h"
#include"Scene_GameOver.h"
#include "Scene_GameClear.h"
#include "Enemy_02.h"
#include"GameData.h"

//�f�o�b�O���[�h
#include"Debug_Manager.h"

//�R���X�g���N�^
Scene_Stage06::Scene_Stage06(const Player* player)
{
	//�v���C���[��񂪓n����Ă����
	if (player != nullptr)
	{
		//���������p�����v���C���[�𐶐�
		obj_player = new Player(*player);
	}
	else
	{
		//�v���C���[�𐶐�
		obj_player = new Player(100, 600);
	}

	//�G�𐶐�
	obj_enemy = new Enemy_06(1200, 360, Jan_Type::SCISSORS);

	//�w�i�摜�̓ǂݍ���
	stage6_BackImage = LoadGraph("images/stage6/mori32-.png");

	//���E�ǂ̗p��
	Init_Floor(STAGE_06_FLOOR);

	//�������  STAGE_06_FLOOR ��
	obj_floor[0] = new Floor(0, 700, 1280, 20, 22822);        //��
	obj_floor[1] = new Floor(0, 0 - 400, 20, 1720 + 400);           //�ǁi���j
	obj_floor[2] = new Floor(1260, 0 - 400, 20, 1720 + 400);           //�ǁi�E�j

	obj_floor[3] = new Floor(81, 150, 120, 10, 22822);          //����[3]�`[15]
	obj_floor[4] = new Floor(81, 350, 120, 10, 22822);
	obj_floor[5] = new Floor(81, 550, 120, 10, 22822);

	obj_floor[6] = new Floor(333, 250, 120, 10, 22822);
	obj_floor[7] = new Floor(333, 450, 120, 10, 22822);

	obj_floor[8] = new Floor(585, 150, 120, 10, 22822);
	obj_floor[9] = new Floor(585, 350, 120, 10, 22822);
	obj_floor[10] = new Floor(585, 550, 120, 10, 22822);

	obj_floor[11] = new Floor(837, 250, 120, 10, 22822);
	obj_floor[12] = new Floor(837, 450, 120, 10, 22822);

	obj_floor[13] = new Floor(1089, 150, 120, 10, 22822);
	obj_floor[14] = new Floor(1089, 350, 120, 10, 22822);
	obj_floor[15] = new Floor(1089, 550, 120, 10, 22822);

	obj_floor[16] = new Floor(0, -220, 1280, 20, 22822);        //�V��

	//�������Ԃ��Z�b�g
	GameData::Set_TimeLimit(5460);
}

//�f�X�g���N�^
Scene_Stage06::~Scene_Stage06()
{
}

//�X�V
void Scene_Stage06::Update()
{
	//�ڐG����񂯂�J�n�O
	if (GetJanState() == Jan_State::BEFORE)
	{
		obj_player->Update();    // �v���C���[�X�V�E����\
		obj_enemy->Update();     //�G�L�����X�V�E��������

		//�v���C���[���W���擾
		obj_enemy->SetPlayerLocation(obj_player->GetX(), obj_player->GetY());

		//�v���C���[�������擾
		obj_enemy->SetPlayerDirection(obj_player->GetDirection());

		//���Ԃ��J�E���g
		GameData::Time_Update();
	}

	//�ڐG����񂯂񏈗�
	Touch_Janken(obj_enemy, this, 6);

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
					obj_player->DeleteJangeki(i);     //������������񌂂��폜
					i--;
				}

				break;

			case Jan_Type::SCISSORS:                       //�G�̑����@�`���L

				//�O�[�̂���񌂂̂ݗL��
				if (jangeki_type == Jan_Type::ROCK)
				{
					obj_enemy->ReceiveDamage(10);     //�_���[�W������
					obj_player->DeleteJangeki(i);     //������������񌂂��폜
					i--;
				}
				break;

			case Jan_Type::PAPER:                          //�G�̑����@�p�[

				//�`���L�̂���񌂂̂ݗL��
				if (jangeki_type == Jan_Type::SCISSORS)
				{
					obj_enemy->ReceiveDamage(10);     //�_���[�W������
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

	//�ǂƂ̓����蔻��
	if (obj_player->Get_X() <= 50 || obj_player->Get_X() >= 1220)
	{
		HitCtrl_Floor(obj_player, STAGE_06_FLOOR);     // player�@���E�ǔ���
	}

	//�v���C���[��y���W���������Ȃ����̂ݓ����蔻����擾
	if (obj_player->Get_Y() >= obj_player->Get_OldY() || obj_player->Get_Y() <= -200)
	{
		HitCtrl_Floor(obj_player, STAGE_06_FLOOR);     // player�@���E�ǔ���
	}

	//�G��y���W���������Ȃ����̂ݓ����蔻����擾
	if (obj_enemy->Get_Y() >= obj_enemy->Get_OldY() || obj_enemy->Get_Y() <= -200)
	{
		HitCtrl_Floor(obj_enemy, STAGE_06_FLOOR);      // �G�@�@�@���E�ǔ���
	}
}


//�`��
void Scene_Stage06::Draw() const
{
	//�w�i�̕`��
	DrawGraph(0, 0, stage6_BackImage, TRUE);

	//UI�̕`��
	DrawUI(obj_enemy->GetType(), obj_enemy->GetHP());
	DrawUI_ON_Enemy(obj_enemy);

	//�ڐG����񂯂�J�n�O
	if (GetJanState() == Jan_State::START || GetJanState() == Jan_State::BEFORE)
	{

		obj_player->Draw();  //�v���C���[�`��
		obj_enemy->Draw();   //�G�L�����`��

		//���E�Ǖ`��
		for (int i = 0; i < STAGE_06_FLOOR; i++)
		{
			if (obj_floor[i] == nullptr) break;
			obj_floor[i]->Draw();
		}

		// �ڐG�����u�Ԃ̉��o
		if (GetJanState() == Jan_State::START) Draw_JankenStart();
	}
	else
	{
		//�ڐG������񂯂�`��
		Draw_Janken();
	}

	DrawString(640, 360, "Stage06", 0xffffff);
}

//����񂯂�`��
void Scene_Stage06::Draw_Janken() const
{
	obj_janken->Draw();
}

void Scene_Stage06::AfterJanken_WIN()
{
	obj_player = new Player(100, 600);     //�v���C���[���w����W�ɐ���
}

void Scene_Stage06::AfterJanken_LOSE()
{
	obj_player = new Player(100, 600);                            //�v���C���[���w����W�ɐ���
	//obj_enemy  = new Enemy_06(1149, 480, obj_enemy->GetType());   //�G���w����W�ɐ���
	obj_enemy->SpeedUp();                                         //�G�̓���s��1
}

//�V�[���̕ύX
AbstractScene* Scene_Stage06::ChangeScene()
{
	//"Debug_Manager.h" �� #define DEBUG_OFF_06 ���R�����g�A�E�g����ƊJ�����[�h
#ifdef DEBUG_OFF_06

	//�G��HP��0�ȉ�
	if (obj_enemy->GetHP() <= 0)
	{
		//�Q�[���N���A�V�[���֐؂�ւ�
		return dynamic_cast<AbstractScene*> (new GameClearScene(7));
	}

	//�v���C���[��HP��0�ȉ�
	if (obj_player->GetHP() <= 0  || GameData::Get_Each_Time() <= 0 )
	{
		//�Q�[���I�[�o�[�V�[���֐؂�ւ�
		return dynamic_cast<AbstractScene*> (new GameOverScene(6));
	}

#endif // DEBUG_OFF_06

	return this;
}