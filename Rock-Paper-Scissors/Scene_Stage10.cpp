#include "Scene_Stage10.h"
#include"Scene_GameOver.h"
#include"Scene_GameClear.h"
#include"KeyManager.h"
#include"DxLib.h"
#include"Scene_GameClear.h"
#include"Scene_GameOver.h"
#include"Jangeki_Homing.h"
#include"GameData.h"
#include"Enemy_10.h"
#include"Jangeki_whole.h"
#include"Scene_InputNameRanking.h"
#include"Scene_Ranking.h"
#include"SortSave.h"

//�f�o�b�O���[�h
#include"Debug_Manager.h"
#include "SoundSystem.h"

//�R���X�g���N�^
Scene_Stage10::Scene_Stage10(const Player* player)
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
	obj_enemy = new Enemy_10(1050, 220, Jan_Type::SCISSORS);

	//���E�ǂ̗p��
	Init_Floor(STAGE_10_FLOOR);

	//�������  STAGE_10_FLOOR ��
	obj_floor[0] = new Floor(0, 700, 1280, 20);        //��
	obj_floor[1] = new Floor(0, 0, 20, 1720);           //�ǁi���j
	obj_floor[2] = new Floor(1260, 0, 20, 1720);           //�ǁi�E�j

	reflection = new Jangeki_Reflection(0, 0, 0, 0, Jan_Type::ROCK);

	//BGM���[�h
	bgm[0] = LoadSoundMem("Sound/stage10/stage10.wav");
	bgm[1] = LoadSoundMem("Sound/stage10/stage10_2.wav");

	back_image = LoadGraph("images/Stage10/����.png");
}

//�f�X�g���N�^
Scene_Stage10::~Scene_Stage10()
{
	for (int i = 0; i < 2; i++)
	{
		StopSoundMem(bgm[i]);
	}
}

//�X�V
void Scene_Stage10::Update()
{
	switch (obj_enemy->Get_Enemy10Form())
	{
		/***********
		* ���`��
		***********/
	case 1:

		static int interval;
		interval++;

		//BGM
		if (interval % 10 == 0)
		{
			if (CheckSoundMem(bgm[0]) == 0) PlaySoundMem(bgm[0], DX_PLAYTYPE_LOOP);
		}
		//if (interval % 300 == 0)
		//{
		//	if (CheckSoundMem(bgm[0]) == 0) PlaySoundMem(bgm[0], DX_PLAYTYPE_LOOP);
		//}
		//if (interval % 600 == 0)
		//{
		//	if (CheckSoundMem(bgm[2]) == 0) PlaySoundMem(bgm[2], DX_PLAYTYPE_LOOP);
		//}

		/*����*/
		obj_floor[3] = new Floor(100, 350, 120, 50);      
		obj_floor[4] = new Floor(1000, 350, 120, 50);      

		/*��*/
		obj_floor[5] = new Floor(0, 700, 1280, 20);        
		obj_floor[6] = new Floor(0, 700, 1280, 20);        
		obj_floor[7] = new Floor(0, 700, 1280, 20);        
		obj_floor[8] = new Floor(0, 700, 1280, 20);        
		obj_floor[9] = new Floor(0, 700, 1280, 20);       
		obj_floor[10] = new Floor(0, 700, 1280, 20);        
		obj_floor[11] = new Floor(0, 700, 1280, 20);        
		obj_floor[12] = new Floor(0, 700, 1280, 20);        
		obj_floor[13] = new Floor(0, 700, 1280, 20);       
		obj_floor[14] = new Floor(0, 700, 1280, 20);        
		obj_floor[15] = new Floor(0, 700, 1280, 20);       
		break;

		/***********
		* ���`��
		***********/
	case 2:

		//BGM STOP
		StopSoundMem(bgm[0]);

		//BGM
		if (CheckSoundMem(bgm[1]) == 0) PlaySoundMem(bgm[1], DX_PLAYTYPE_LOOP);

		/*����*/  
		obj_floor[3] = new Floor(100, 500, 120, 20, 0xd2d2d2);//�e���|�[�g���ʒu
		obj_floor[4] = new Floor(81, 300, 120, 10, 22822);
		obj_floor[5] = new Floor(0, 700, 1280, 20);
		obj_floor[6] = new Floor(1050, 500, 120, 20, 0xd2d2d2);//�e���|�[�g�E�ʒu
		obj_floor[7] = new Floor(333, 400, 120, 10, 22822);
		obj_floor[8] = new Floor(585, 100, 120, 10, 22822);
		obj_floor[9] = new Floor(560, 520, 120, 20, 0xd2d2d2);//�e���|�[�g�^�񒆈ʒu
		obj_floor[10] = new Floor(0, 700, 1280, 20);
		obj_floor[11] = new Floor(837, 200, 120, 10, 22822);
		obj_floor[12] = new Floor(800, 500, 120, 10, 22822);
		obj_floor[13] = new Floor(1089, 100, 120, 10, 22822);
		obj_floor[14] = new Floor(1089, 300, 120, 10, 22822);
		obj_floor[15] = new Floor(100, 100, 120, 10, 22822);
		break;
	default:
		break;
	}

	//�ڐG����񂯂�łȂ���
	//if (janken_flag == false)
	//{
	//	obj_player->Update();    // �v���C���[�X�V�E����\
	//	obj_enemy->Update();     //�G�L�����X�V�E��������
	//
	//	/*���˒e*/
	//	//obj_enemy->reflection->Update_reflection();
	//
	//	/*�X�e�[�W�ł̑����ω�*/
	//	//obj_enemy->SetType(Jan_Type::PAPER);
	//
	//	/*�G���v���C���[�̍��W��Ԃ�*/
	//	obj_enemy->SetPlayerLocation(obj_player->GetX(), obj_player->GetY());
	//
	//	//�G�ƃv���C���[�̓����蔻��  �@������"�ڐG����񂯂�"
	//	if (obj_enemy->Hit_Character(obj_player) == true)
	//	{
	//		//�G���o����������_���Ɍ��߂�@�@�@�i�����_����int�^�̒l(0�`2)�� Jan_Type�^�ɕϊ��j
	//		Jan_Type enemy_janken = static_cast<Jan_Type> (GetRand(2));
	//
	//		//����񂯂�p�I�u�W�F�N�g����
	//		obj_janken = new Janken(enemy_janken);
	//
	//		//�ڐG����񂯂�J�n
	//		janken_flag = true;
	//	}
	//}
	//else
	//{
	//	//�ڐG������񂯂�̏��������s
	//	Update_Janken();
	//}

	//�ڐG����񂯂�J�n�O
	if (GetJanState() == Jan_State::BEFORE)
	{
		obj_player->Update();    // �v���C���[�X�V�E����\
		obj_enemy->Update();     //�G�L�����X�V�E��������

		//�v���C���[���W���擾
		obj_enemy->SetPlayerLocation(obj_player->GetX(), obj_player->GetY());

		//�v���C���[�������擾
		//obj_enemy->SetPlayerDirection(obj_player->GetDirection());

		//���Ԃ��J�E���g
		GameData::Time_Update();
	}

	//�ڐG����񂯂񏈗�
	Touch_Janken(obj_enemy, this, 10);

	/*�G�t�F�N�g�ǉ�(�X�R�A���Z)*/
	Effect_Update_HitJangeki(obj_enemy);

	//player�̂���񌂂��Ƃ��Ă���
	Jangeki_Base** player_jangeki = obj_player->GetJangeki();

	//enemy�̂���񌂂��Ƃ��Ă���
	Jangeki_Base** enemy_jangeki = obj_enemy->GetJangeki();

	//���˂��ꂽ����񌂂��Ƃ��Ă���
	//Jangeki_Base** reflection_jangeki = obj_enemy->reflection->GetJangeki();

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
					obj_enemy->ReceiveDamage(30);     //�_���[�W������
					obj_player->DeleteJangeki(i);     //������������񌂂��폜
					i--;
				}

				break;

			case Jan_Type::SCISSORS:                       //�G�̑����@�`���L

				//�O�[�̂���񌂂̂ݗL��
				if (jangeki_type == Jan_Type::ROCK)
				{
					obj_enemy->ReceiveDamage(30);     //�_���[�W������
					obj_player->DeleteJangeki(i);     //������������񌂂��폜
					i--;
				}
				break;

			case Jan_Type::PAPER:                          //�G�̑����@�p�[

				//�`���L�̂���񌂂̂ݗL��
				if (jangeki_type == Jan_Type::SCISSORS)
				{
					obj_enemy->ReceiveDamage(30);     //�_���[�W������
					obj_player->DeleteJangeki(i);     //������������񌂂��폜
					i--;
				}
				break;

			default:
				break;
			}

			/*���˒e*/
			//if (player_jangeki[i]->GetR() == 35.f || obj_enemy->Getflg() == true)
			//{
			//	obj_enemy->ReceiveDamage(20);
			//
			//	//������������񌂂��폜
			//	obj_player->DeleteJangeki(i);
			//	i--;
			//	if (obj_enemy->Getflg() == true)obj_enemy->Fflg();
			//}
			//else
			//{
			//	obj_player->DeleteJangeki(i);     //������������񌂂��폜
			//	i--;
			//	obj_enemy->reflection->trueFlg();
			//}
			//obj_enemy->HP();
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���˂���񌂓����蔻��

	//���˂��ꂽ����񌂂�player����񌂂̓����蔻��
	//for (int p_count = 0; p_count < JANGEKI_MAX; p_count++)
	//{
	//	if (player_jangeki[p_count] == nullptr) break;         //����񌂂��Ȃ����͏������Ȃ�
	//	bool delete_player = false;       //�v���C���[����񌂍폜�t���O�@true:�폜�@false:�폜���Ȃ�
	//	for (int r_count = 0; r_count < JANGEKI_MAX; r_count++)
	//	{
	//		if (reflection_jangeki[r_count] == nullptr) break;         //����񌂂��Ȃ����͏������Ȃ�
	//		if (player_jangeki[p_count]->Hit_Jangeki(reflection_jangeki[r_count]) == true)
	//		{
	//			//�L�������`�F�b�N
	//			int result = player_jangeki[p_count]->CheckAdvantage(reflection_jangeki[r_count]);
	//			switch (result)
	//			{
	//			case 0:             //player�̂���񌂂��s��
	//				//player���̂���񌂂��폜
	//				delete_player = true;
	//				break;
	//			case 1:             //player�̂���񌂂��L��
	//				//enemy���̂���񌂂��폜
	//				obj_enemy->reflection->Delete_reflectionJangeki(r_count);
	//				r_count--;
	//				//�z�[�~���O����ꐶ��
	//				obj_player->Create_Homing(p_count, player_jangeki[p_count]->GetX(), player_jangeki[p_count]->GetY(), 35.f, 10, player_jangeki[p_count]->GetType());
	//				break;
	//			case 2:             //������
	//				//player���̂���񌂂��폜
	//				delete_player = true;
	//				//enemy���̂���񌂂��폜(���˒e)
	//				obj_enemy->reflection->Delete_reflectionJangeki(r_count);
	//				r_count--;
	//				break;
	//			default:
	//				break;
	//			}
	//		}
	//	}
	//	//�v���C���[����񌂍폜�t���O��true
	//	if (delete_player == true)
	//	{
	//		//player���̂���񌂂��폜
	//		obj_player->DeleteJangeki(p_count);
	//		p_count--;
	//	}
	//}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//enemy����񌂂�player�̓����蔻��
	for (int i = 0; i < JANGEKI_MAX; i++)
	{
		//����񌂂��Ȃ����͏������Ȃ�
		if (enemy_jangeki[i] == nullptr) break;

		//����񌂂Ƃ̓����蔻��
		if (obj_player->Hit_Jangeki(enemy_jangeki[i]) == true)
		{
			//�_���[�W���󂯂�i�v���C���[�j
			obj_player->ReceiveDamage(30);

			//������������񌂂��폜
			obj_enemy->DeleteJangeki(i);

			/*������������񌂂��폜(���˒e)*/
			//obj_enemy->reflection->Delete_reflectionJangeki(i);
			i--;
		}
	}
	//HitCtrl_Floor(obj_player, STAGE_10_FLOOR);     // player�@���E�ǔ���
	//HitCtrl_Floor(obj_enemy, STAGE_10_FLOOR);      // �G�@�@�@���E�ǔ���

	//�ǂƂ̓����蔻��
	if (obj_player->Get_X() <= 50 || obj_player->Get_X() >= 1220)
	{
		HitCtrl_Floor(obj_player, STAGE_10_FLOOR);     // player�@���E�ǔ���
	}

	//�v���C���[��y���W���������Ȃ����̂ݓ����蔻����擾
	if (obj_player->Get_Y() >= obj_player->Get_OldY() || obj_player->Get_Y() <= -200)
	{
		HitCtrl_Floor(obj_player, STAGE_10_FLOOR);     // player�@���E�ǔ���
	}

	//�G��y���W���������Ȃ����̂ݓ����蔻����擾
	if (obj_enemy->Get_Y() >= obj_enemy->Get_OldY() || obj_enemy->Get_Y() <= -200)
	{
		HitCtrl_Floor(obj_enemy, STAGE_10_FLOOR);      // �G�@�@�@���E�ǔ���
	}
}


//�`��
void Scene_Stage10::Draw() const
{
	if (obj_enemy->Get_Enemy10Form() == 1)
	{
		//�X�e�[�W�w�i�`��
		DrawRotaGraph(640, 360, 1, 0, back_image, FALSE);
	}

	if (obj_enemy->Get_Enemy10Form() == 2)
	{
		//�w�i�̕`��
		DrawGraph(0, 0, 0, FALSE);
	}

	if (obj_enemy->Get_Enemy10Form() == 1 && obj_enemy->IsDeathEnemy10() == true) //���`��
	{
		//�_��
		static int counter;

		if (counter++ < 30)
		{
			DrawString(550, 350, "-- Press  A  Button --", 0xffffffff);
		}
		else if (counter > 60)  counter = 0;
	}

	//UI�̕`��
	DrawUI(obj_enemy->GetType(), obj_enemy->GetHP());
	DrawUI_ON_Enemy(obj_enemy);

	//�ڐG����񂯂�J�n�O
	if (GetJanState() == Jan_State::START || GetJanState() == Jan_State::BEFORE)
	{
		obj_player->Draw();  //�v���C���[�`��
		obj_enemy->Draw();   //�G�L�����`��

		//���E�Ǖ`��
		for (int i = 0; i < STAGE_10_FLOOR; i++)
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

	/*�G�t�F�N�g�`��*/
	Effect_Draw_HitJangeki();
}

//����񂯂�X�V�E��������
void Scene_Stage10::Update_Janken()
{
	//�@�����͉��ǂ����ق�������

	obj_janken->Update();

	//A�{�^���������ꂽ�Ƃ� 
	if (KeyManager::OnPadClicked(PAD_INPUT_A) == true)
	{
		//���ʂ��擾
		switch (obj_janken->GetResult())
		{
		case Jan_Result::LOSE:    //����

			obj_player->SetX(640);   //���炷
			janken_flag = false;

			obj_enemy->Init_Jangeki();

			delete obj_janken;
			break;

		case Jan_Result::WIN:     //����

			obj_player->SetX(640);   //���炷
			janken_flag = false;

			obj_enemy->Init_Jangeki();

			delete obj_janken;
			break;

		case Jan_Result::ONEMORE: //������

			janken_flag = false;

			obj_enemy->Init_Jangeki();

			delete obj_janken;
			break;

		case Jan_Result::_ERROR:  //�܂�����񂯂�
			break;

		default:
			break;
		}
	}
}

//����񂯂�`��
void Scene_Stage10::Draw_Janken() const
{
	obj_janken->Draw();
}

/*����񂯂�ɏ�������*/
void Scene_Stage10::AfterJanken_WIN()
{
	if(obj_enemy->Get_Enemy10Form() == 1)
	{
		obj_enemy->ReceiveDamage(100);
	}

	if (obj_enemy->Get_Enemy10Form() == 2)
	{
		obj_player->Recover_HP(50);
	}
}

/*����񂯂�ɕ�������*/
void Scene_Stage10::AfterJanken_LOSE()
{
	if (obj_enemy->Get_Enemy10Form() == 1)
	{
		obj_player->ReceiveDamage(100);
	}

	if (obj_enemy->Get_Enemy10Form() == 2)
	{
		obj_enemy->Recover_HP(30);
	}
}

//�V�[���̕ύX
AbstractScene* Scene_Stage10::ChangeScene()
{
	//"Debug_Manager.h" �� #define DEBUG_OFF_10 ���R�����g�A�E�g����ƊJ�����[�h
#ifdef DEBUG_OFF_10

	/*�G��HP��0�ȉ�*/
	if (obj_enemy->Get_Enemy10Form() == 1 && obj_enemy->IsDeathEnemy10() == true) //���`��
	{
		StopSoundMem(bgm[0]);
		//StopSoundMem(bgm[1]);
		//StopSoundMem(bgm[2]);
	}
	if(obj_enemy->Get_Enemy10Form() == 2 && obj_enemy->IsDeathEnemy10() == true) //���`��
	{
		//�Q�[���N���A�V�[���֐؂�ւ�
		return dynamic_cast<AbstractScene*> (new GameClearScene(11));
	}
	 	   
	/*�v���C���[��HP��0�ɂȂ�����*/
	if (obj_player->IsDeathPlayer() == true)
	{
		//�Q�[���I�[�o�[�V�[���֐؂�ւ�
		return dynamic_cast<AbstractScene*> (new GameOverScene(10));
	}

#endif // DEBUG_OFF_10
	return this;
}