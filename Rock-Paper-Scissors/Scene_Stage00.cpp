#include"DxLib.h"
#include"KeyManager.h"
#include "Scene_Stage00.h"
#include"Scene_GameOver.h"
#include"Scene_GameClear.h"
#include"Janken.h"

//�f�o�b�O���[�h
#include"Debug_Manager.h"

//�R���X�g���N�^
Scene_Stage00::Scene_Stage00(const Player* player)
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
	obj_enemy = new Enemy_00(1200, 360, Jan_Type::SCISSORS);

	//���E�ǂ̗p��
	Init_Floor(STAGE_00_FLOOR);

	//���A�ǂ��@�@�@#define �@STAGE_00_FLOOR �@�������@�@
	//
	// new Floor(�����W,�����W,�@��,�@����) ��ݒ� 
	//
	// new Floor(�����W,�����W,�@��,�@����,  �F(16�i��))         �F���w��
	//
	// new Floor("images/�摜��",  �����W, �����W,�@��,�@����)�@ �摜��ݒ�
	//
	// (�摜�g�p�̗�) new Floor("images/Jangeki_Test.png",200, 200, 100, 50);

	obj_floor[0] = new Floor(50, 700, 1280, 20);        //��
	obj_floor[1] = new Floor(0, 0, 20, 1720);          //�ǁi���j
	obj_floor[2] = new Floor(1260,0,20,1720);          //�ǁi�E�j
	obj_floor[3] = new Floor(1000, 100, 120, 50);      //����
	obj_floor[4] = new Floor(40, 500, 500, 60);        //����
	obj_floor[5] = new Floor(100, 300, 100, 50);
	obj_floor[6] = new Floor(200, 100, 50,50);//�C���[�W�ǉ�

	//�e�X�g
	setumei = LoadGraph("images/Setumei.png");

	//�摜�ꗗ
	int players[10];
	LoadDivGraph("images/�����p���}��ALL�摜�r����.png", 10, 5, 2, 100, 100, players);

	player_image = players[0];
	player_all = LoadGraph("images/�����p���}��ALL�摜�r����.png");

	enemy_02 = LoadGraph("images/stage02/ex.png");
	enemy_03 = LoadGraph("images/stage03/stage03gard.png");
	enemy_04 = LoadGraph("images/Stage4/�X�e�[�W4_�{�X.png");
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
	//�ڐG����񂯂�J�n�O
	if (GetJanState() == Jan_State::BEFORE)
	{
		//obj_player->Update();    // �v���C���[�X�V�E����\
		//obj_enemy->Update();     //�G�L�����X�V�E��������

		////�v���C���[�̍��W���擾
		//obj_enemy->SetPlayerLocation(obj_player->GetX(), obj_player->GetY());
	}

	//�ڐG����񂯂񏈗�
	Touch_Janken(obj_enemy, this);

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
				int result = player_jangeki[p_count]->CheckAdvantage( enemy_jangeki[e_count] );

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


	HitCtrl_Floor(obj_player, STAGE_00_FLOOR);     // player�@���E�ǔ���
	HitCtrl_Floor(obj_enemy, STAGE_00_FLOOR);      // �G�@�@�@���E�ǔ���


}

//�`��
void Scene_Stage00::Draw() const
{
	//�ڐG����񂯂�J�n�O
	if (GetJanState() == Jan_State::BEFORE)
	{
		//obj_player->Draw();  //�v���C���[�`��
		//obj_enemy->Draw();   //�G�L�����`��

		////���E�Ǖ`��
		//for (int i = 0; i < STAGE_00_FLOOR; i++)
		//{
		//	if (obj_floor[i] == nullptr) break;
		//	obj_floor[i]->Draw();
		//}

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
	}
	else
	{
		//�ڐG������񂯂�`��
		Draw_Janken();
	}

	////�e�X�g
	//DrawGraph(20, 0, setumei, TRUE);

}


//����񂯂�`��
void Scene_Stage00::Draw_Janken() const
{
	obj_janken->Draw();
}

//�V�[���̕ύX
AbstractScene* Scene_Stage00::ChangeScene()
{
#ifdef DEBUG_OFF_00

	//�G��HP��0�ȉ�
	if (obj_enemy->GetHP() < 0)
	{
		//�Q�[���N���A�V�[���֐؂�ւ�
		return dynamic_cast<AbstractScene*> (new GameClearScene(1));
	}

	//�v���C���[��HP��0�ȉ�
	if (obj_player->GetHP() < 0)
	{
		//�Q�[���I�[�o�[�V�[���֐؂�ւ�
		return dynamic_cast<AbstractScene*> (new GameOverScene(0));
	}

#endif // _DEBUG_MODE_00




	return this;   //�X�V�Ȃ�
}
