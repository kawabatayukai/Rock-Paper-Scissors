#include "Scene_Stage05.h"
#include "KeyManager.h"
#include "DxLib.h"
#include"Scene_GameOver.h"
#include "Scene_GameClear.h"
#define PI    3.1415926535897932384626433832795f

//�f�o�b�O���[�h
#include"Debug_Manager.h"

//�R���X�g���N�^
Scene_Stage05::Scene_Stage05(const Player* player)
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
		obj_player = new Player(640, 360);
	}

	//�G�𐶐�
	obj_enemy = new Enemy_05(1000, 160, Jan_Type::SCISSORS);

	mob = new MobEnemy_05 * [3];
	for (int i = 0; i < 3; i++) mob[i] = nullptr;


	mob[0] = new MobEnemy_05(640, 100, Jan_Type::PAPER);
	mob[1] = new MobEnemy_05(50, 420, Jan_Type::SCISSORS);
	mob[2] = new MobEnemy_05(1230, 420, Jan_Type::ROCK);

	reflection = new Jangeki_Reflection(0, 0, 0, 0, Jan_Type::ROCK);

	if (mob[0]->GetHP() <= 0 && mob[1]->GetHP() <= 0 && mob[2]->GetHP() <= 0)
	{
		mob[0] = new MobEnemy_05(640, 100, Jan_Type::PAPER);
		mob[1] = new MobEnemy_05(50, 420, Jan_Type::SCISSORS);
		mob[2] = new MobEnemy_05(1230, 420, Jan_Type::ROCK);
	}


	//���E�ǂ̗p��
	Init_Floor(STAGE_05_FLOOR);

	//�������  STAGE_05_FLOOR ��
	obj_floor[0] = new Floor(0, 700, 1280, 20, 0x00ff00);        //��
	obj_floor[1] = new Floor(0, 0, 20, 1720, 0x00ff00);           //�ǁi���j
	obj_floor[2] = new Floor(1260, 0, 20, 1720, 0x00ff00);           //�ǁi�E�j
	obj_floor[3] = new Floor(260, 300, 120, 15, 0x00ff00);      //����@(����)
	obj_floor[4] = new Floor(260, 540, 120, 15, 0x00ff00);      //����@(����)
	obj_floor[5] = new Floor(590, 420, 120, 15, 0x00ff00);      //����@(�^��)
	obj_floor[6] = new Floor(900, 540, 120, 15, 0x00ff00);      //����@(�E��)
	obj_floor[7] = new Floor(900, 300, 120, 15, 0x00ff00);      //����@(�E��)

	Back_image = LoadGraph("images/stage05/Stage5_Stageimage.png", TRUE);
}

//�f�X�g���N�^
Scene_Stage05::~Scene_Stage05()
{
}

//�X�V
void Scene_Stage05::Update()
{
	static int timer = 0;
	timer++;

	/*if (timer == 900)
	{
		timer = 0;
	}*/
	//�ڐG����񂯂�J�n�O
	if (GetJanState() == Jan_State::BEFORE)
	{
		if (obj_enemy->respawn_mobenemy() == true)
		{
			for (int i = 0; i < 3; i++)
			{
				mob[i]->Init_Jangeki();
				mob[i]->Recover_HP(100);
			}
			obj_enemy->SetRespawn(false);
		}

		obj_player->Update();    // �v���C���[�X�V�E����\
		obj_enemy->GetMobEnemy(mob);
		obj_enemy->Update();     //�G�L�����X�V�E��������

		obj_enemy->reflection->Update_reflection();

		for (int i = 0; i < 3; i++)
		{
			mob[i]->Update();

			//�v���C���[�̍��W���擾
			mob[i]->SetPlayerLocation(obj_player->GetX(), obj_player->GetY());
		}



		//�v���C���[�̍��W���擾
		obj_enemy->SetPlayerLocation(obj_player->GetX(), obj_player->GetY());
	}
	//�ڐG����񂯂񏈗�
	Touch_Janken(obj_enemy, this, 5);



	//player�̂���񌂂��Ƃ��Ă���
	Jangeki_Base** player_jangeki = obj_player->GetJangeki();

	//enemy�̂���񌂂��Ƃ��Ă���
	Jangeki_Base** enemy_jangeki = obj_enemy->GetJangeki();

	//���˂��ꂽ�W���������Ƃ��Ă���
	Jangeki_Base** reflection_Jangeki = obj_enemy->reflection->GetJangeki();

	Jangeki_Base** mobenemy_jangek[3];
	mobenemy_jangek[0] = mob[0]->GetJangeki();
	mobenemy_jangek[1] = mob[1]->GetJangeki();
	mobenemy_jangek[2] = mob[2]->GetJangeki();

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	for (int a = 0; a < 3; a++)
	{
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
						mob[a]->DeleteJangeki(e_count);
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
	}




	for (int a = 0; a < 3; a++)
	{
		Jangeki_Base** enemy_jangeki = mobenemy_jangek[a];
		if (mob[a]->GetHP() > 0)
		{
			//����񌂓��m�̓����蔻��i�v���C���[����񌂖ڐ��j(mob�p)
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
							mob[a]->DeleteJangeki(e_count);
							e_count--;

							break;

						case 2:             //������

							//player���̂���񌂂��폜
							delete_player = true;

							//enemy���̂���񌂂��폜
							mob[a]->DeleteJangeki(e_count);
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
		}
	}




	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//player����񌂂�enemy�̓����蔻��
	for (int i = 0; i < JANGEKI_MAX; i++)
	{
		for (int i = 0; i < 3; i++)
		{
			if (mob[0]->GetHP() <= 0 && mob[1]->GetHP() <= 0 && mob[2]->GetHP() <= 0)
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
							obj_enemy->reflection->trueFlg();
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
							obj_enemy->reflection->trueFlg();
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
							obj_enemy->reflection->trueFlg();
						}
						break;

					default:
						break;
					}
				}
			}

		}
	}

	for (int a = 0; a < 3; a++)
	{
		if (mob[a]->GetHP() > 0)
		{
			//player����񌂂�mobenemy�̓����蔻��
			for (int i = 0; i < JANGEKI_MAX; i++)
			{
				if (player_jangeki[i] == nullptr) break;         //����񌂂��Ȃ����͏������Ȃ�

				//����񌂂Ƃ̓����蔻��
				if (mob[a]->Hit_Jangeki(player_jangeki[i]) == true)
				{
					Jan_Type mobenemy_type = mob[a]->GetType();            //�G�̑���
					Jan_Type jangeki_type = player_jangeki[i]->GetType();  //������������񌂂̑���

					//�s�������̂݃_���[�W������
					switch (mobenemy_type)
					{
					case Jan_Type::ROCK:                           //�G�̑����@�O�[

						//�p�[�̂���񌂂̂ݗL��
						if (jangeki_type == Jan_Type::PAPER)
						{
							mob[a]->ReceiveDamage(20);     //�_���[�W������
							obj_player->DeleteJangeki(i);     //������������񌂂��폜
							i--;
						}

						break;

					case Jan_Type::SCISSORS:                       //�G�̑����@�`���L

						//�O�[�̂���񌂂̂ݗL��
						if (jangeki_type == Jan_Type::ROCK)
						{
							mob[a]->ReceiveDamage(20);     //�_���[�W������
							obj_player->DeleteJangeki(i);     //������������񌂂��폜
							i--;
						}
						break;

					case Jan_Type::PAPER:                          //�G�̑����@�p�[

						//�`���L�̂���񌂂̂ݗL��
						if (jangeki_type == Jan_Type::SCISSORS)
						{
							mob[a]->ReceiveDamage(20);     //�_���[�W������
							obj_player->DeleteJangeki(i);     //������������񌂂��폜
							i--;
						}
						break;

					default:
						break;
					}
				}
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
			obj_player->ReceiveDamage(30);

			//������������񌂂��폜
			obj_enemy->DeleteJangeki(i);
			i--;
		}
	}

	for (int a = 0; a < 3; a++)
	{
		Jangeki_Base** enemy_jangeki = mobenemy_jangek[a];
		if (mob[a]->GetHP() > 0)
		{
			//mobenemy����񌂂�player�̓����蔻��
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
					mob[a]->DeleteJangeki(i);
					i--;
				}
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���˂���񌂓����蔻��
	//���˂��ꂽ����񌂂�player����񌂂̓����蔻��
	for (int p_count = 0; p_count < JANGEKI_MAX; p_count++)
	{
		if (player_jangeki[p_count] == nullptr) break;         //����񌂂��Ȃ����͏������Ȃ�
		bool delete_player = false;       //�v���C���[����񌂍폜�t���O�@true:�폜�@false:�폜���Ȃ�
		for (int r_count = 0; r_count < JANGEKI_MAX; r_count++)
		{
			if (reflection_Jangeki[r_count] == nullptr) break;         //����񌂂��Ȃ����͏������Ȃ�
			if (player_jangeki[p_count]->Hit_Jangeki(reflection_Jangeki[r_count]) == true)
			{
				//�L�������`�F�b�N
				int result = player_jangeki[p_count]->CheckAdvantage(reflection_Jangeki[r_count]);
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
		if (reflection_Jangeki[i] == nullptr) break;
		//����񌂂Ƃ̓����蔻��
		if (obj_player->Hit_Jangeki(reflection_Jangeki[i]) == true)
		{
			//�_���[�W���󂯂�i�v���C���[�j
			obj_player->ReceiveDamage(30);
			//������������񌂂��폜
			obj_enemy->reflection->Delete_reflectionJangeki(i);
			i--;
		}
	}

	//�ǂƂ̓����蔻��
	if (obj_player->Get_X() <= 50 || obj_player->Get_X() >= 1200)
	{
		HitCtrl_Floor(obj_player, STAGE_05_FLOOR);     // player�@���E�ǔ���
	}
	//�v���C���[��y���W���������Ȃ����̂ݓ����蔻����擾
	if (obj_player->Get_Y() >= obj_player->Get_OldY())
	{
		HitCtrl_Floor(obj_player, STAGE_05_FLOOR);     // player�@���E�ǔ���
	}

	//HitCtrl_Floor(obj_player, STAGE_05_FLOOR);     // player�@���E�ǔ���
	HitCtrl_Floor(obj_enemy, STAGE_05_FLOOR);      // �G�@�@�@���E�ǔ���
}


//�`��
void Scene_Stage05::Draw() const
{
	//DrawRotaGraph(640, 240, 2.0f, 0, Back_image, TRUE);
	DrawGraph(0, 0, Back_image, FALSE);

	DrawUI(obj_enemy->GetType(), obj_enemy->GetHP());
	DrawUI_ON_Enemy(obj_enemy);
	for (int a = 0; a < 3; a++)
	{
		if (mob[a]->GetHP() > 0)
			DrawUI_ON_Enemy(mob[a]);
	}

	//�ڐG����񂯂�J�n�O
	if (GetJanState() == Jan_State::START || GetJanState() == Jan_State::BEFORE)
	{

		obj_player->Draw();  //�v���C���[�`��
		obj_enemy->Draw();   //�G�L�����`��

		for (int i = 0; i < 3; i++)
		{
			if (mob[i]->GetHP() > 0)
			{
				mob[i]->Draw();
			}
		}


		//���E�Ǖ`��
		for (int i = 0; i < STAGE_05_FLOOR; i++)
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


	DrawString(640, 360, "Stage05", 0xffffff);
}



//����񂯂�`��
void Scene_Stage05::Draw_Janken() const
{
	obj_janken->Draw();
}

//�V�[���̕ύX
AbstractScene* Scene_Stage05::ChangeScene()
{
	//"Debug_Manager.h" �� #define DEBUG_OFF_05 ���R�����g�A�E�g����ƊJ�����[�h
#ifdef DEBUG_OFF_05

	//�G��HP��0�ȉ�
	if (obj_enemy->GetHP() <= 0)
	{
		//�Q�[���N���A�V�[���֐؂�ւ�
		return dynamic_cast<AbstractScene*> (new GameClearScene(6));
	}

	//�v���C���[��HP��0�ȉ�
	if (obj_player->GetHP() < 0)
	{
		//�Q�[���I�[�o�[�V�[���֐؂�ւ�
		return dynamic_cast<AbstractScene*> (new GameOverScene(5));
	}

#endif // DEBUG_OFF_05

	return this;
}


//����񂯂�I����̋����i�v���C���[�����j
void Scene_Stage05::AfterJanken_WIN()
{
	obj_player->SetX(200);
	for (int a = 0; a < 3; a++)
	{
		mob[a]->Janken_win();
	}

}

//����񂯂�I����̋����i�v���C���[�����j
void Scene_Stage05::AfterJanken_LOSE()
{
	for (int a = 0; a < 3; a++)
	{
		mob[a]->Janken_lose();
	}
	obj_player->SetX(200);
}