#include "Scene_Stage09.h"
#include"KeyManager.h"
#include"DxLib.h"
#include"Scene_GameOver.h"
#include "Scene_GameClear.h"
#include"Scene_Stage10.h"


//�f�o�b�O���[�h
#include"Debug_Manager.h"

//�R���X�g���N�^
Scene_Stage09::Scene_Stage09(const Player* player)
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
	obj_enemy = new Enemy_09(1110, 480, Jan_Type::SCISSORS);

	reflection = new Jangeki_Reflection(0, 0, 0, 0, Jan_Type::ROCK);

	//���E�ǂ̗p��
	Init_Floor(STAGE_09_FLOOR);

	//�������  STAGE_09_FLOOR ��
	obj_floor[0] = new Floor(0, 700, 1280, 20);        //��
	obj_floor[1] = new Floor(0, 0, 20, 1720);           //�ǁi���j
	obj_floor[2] = new Floor(1260, 0, 20, 1720);           //�ǁi�E�j
	//����   ����
	obj_floor[3] = new Floor(100, 500, 120, 20);
	obj_floor[4] = new Floor(300, 325, 120, 20);  
	obj_floor[5] = new Floor(100, 150, 120, 20); 
	//����   �E��
	obj_floor[6] = new Floor(1050, 500, 120, 20);
	obj_floor[7] = new Floor(850, 325, 120, 20);     
	obj_floor[8] = new Floor(1050, 150, 120, 20);    
	//����   �E��
	obj_floor[9] = new Floor(560, 420, 120, 20);
	obj_floor[10] = new Floor(560, 100, 120, 20);

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
		obj_enemy->reflection->SetEnemyLocation(obj_enemy->GetX(), obj_enemy->GetY());
	}

	//�ڐG����񂯂񏈗�
	Touch_Janken(obj_enemy, this);


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
					if (Rflg == false) 
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

		//����񌂂Ƃ̓����蔻��
		if (obj_enemy->Hit_Jangeki(player_jangeki[i]) == true)
		{
			
			obj_player->DeleteJangeki(i);     //������������񌂂��폜
			i--;

			obj_enemy->reflection->trueFlg();

			//	//����񌂕`��
			//	obj_enemy->Draw_Jangeki();
			//	obj_enemy->Update_Jangeki();

			//	Jan_Type enemy_type = obj_enemy->GetType();            //�G�̑���
			//	Jan_Type jangeki_type = player_jangeki[i]->GetType();  //������������񌂂̑���

			//	//�s�������̂݃_���[�W������
			//	switch (enemy_type)
			//	{
			//	case Jan_Type::ROCK:                           //�G�̑����@�O�[

			//		//�p�[�̂���񌂂̂ݗL��
			//		if (jangeki_type == Jan_Type::PAPER)
			//		{
			//			obj_enemy->ReceiveDamage(30);     //�_���[�W������
			//			obj_player->DeleteJangeki(i);     //������������񌂂��폜
			//			i--;
			//		}

			//		break;

			//	case Jan_Type::SCISSORS:                       //�G�̑����@�`���L

			//		//�O�[�̂���񌂂̂ݗL��
			//		if (jangeki_type == Jan_Type::ROCK)
			//		{
			//			obj_enemy->ReceiveDamage(30);     //�_���[�W������
			//			obj_player->DeleteJangeki(i);     //������������񌂂��폜
			//			i--;
			//		}
			//		break;

			//	case Jan_Type::PAPER:                          //�G�̑����@�p�[

			//		//�`���L�̂���񌂂̂ݗL��
			//		if (jangeki_type == Jan_Type::SCISSORS)
			//		{
			//			obj_enemy->ReceiveDamage(30);     //�_���[�W������
			//			obj_player->DeleteJangeki(i);     //������������񌂂��폜
			//			i--;
			//		}
			//		break;

			//	default:
			//		break;
			//	}
		}
		//obj_enemy->reflection->falseFlg();
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
						Rflg = true;
						obj_enemy->reflection->Delete_reflectionJangeki(r_count);
						r_count--;

						//�z�[�~���O����ꐶ��
						obj_player->Create_Homing(p_count, player_jangeki[p_count]->GetX() , player_jangeki[p_count]->GetY(), player_jangeki[p_count]->GetR(), player_jangeki[p_count]->GetSpeed(), player_jangeki[p_count]->GetType());

						//delete_player = true;
						//obj_enemy->Homing();

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
				obj_player->ReceiveDamage(30);

				//������������񌂂��폜
				obj_enemy->reflection->Delete_reflectionJangeki(i);
				i--;
			}
		}

		//���˂��ꂽ����񌂂�enemy�̓����蔻��
		if (Rflg == true) {
			for (int i = 0; i < JANGEKI_MAX; i++)
			{
				//����񌂂��Ȃ����͏������Ȃ�
				if (reflection_jangeki[i] == nullptr) break;

				//����񌂂Ƃ̓����蔻��
				if (obj_enemy->Hit_Jangeki(reflection_jangeki[i]) == true)
				{
					//�_���[�W���󂯂�i�v���C���[�j
					obj_enemy->ReceiveDamage(30);

					//������������񌂂��폜
					obj_enemy->reflection->Delete_reflectionJangeki(i);
					i--;
					Rflg = false;
				}
			}
		}
		

	HitCtrl_Floor(obj_player, STAGE_09_FLOOR);     // player�@���E�ǔ���
	HitCtrl_Floor(obj_enemy, STAGE_09_FLOOR);      // �G�@�@�@���E�ǔ���
}


//�`��
void Scene_Stage09::Draw() const
{
	//HP�\��
	DrawUI(obj_enemy->GetType(), obj_enemy->GetHP());
	//�ڐG����񂯂�łȂ���
	if (GetJanState() == Jan_State::BEFORE)
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

	}
	else
	{
		//�ڐG������񂯂�`��
		Draw_Janken();
	}

	DrawString(640, 360, "Stage09", 0xffffff);
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
	if (obj_enemy->GetHP() < 0)
	{
		//�Q�[���N���A�V�[���֐؂�ւ�
		return dynamic_cast<AbstractScene*> (new GameClearScene(10));
	}

	//�v���C���[��HP��0�ȉ�
	if (obj_player->GetHP() < 0)
	{
		//�Q�[���I�[�o�[�V�[���֐؂�ւ�
		return dynamic_cast<AbstractScene*> (new GameOverScene(9));
	}

#endif // DEBUG_OFF_09

	return this;
}

//����񂯂�I����̋����i�v���C���[�����j
void Scene_Stage09::AfterJanken_WIN()
{
	obj_player->SetX(100);
}

//����񂯂�I����̋����i�v���C���[�����j
void Scene_Stage09::AfterJanken_LOSE()
{
	obj_player->SetX(100);
}