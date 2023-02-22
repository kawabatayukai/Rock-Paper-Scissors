#include "Scene_Stage04.h"
#include"KeyManager.h"
#include"DxLib.h"
#include"Scene_GameOver.h"
#include"Scene_GameClear.h"

//�R���X�g���N�^
Scene_Stage04::Scene_Stage04(const Player* player)
{
	back_image = LoadGraph("images/Stage4/Stage_Image2.png");

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
	obj_enemy = new Enemy_04(1200, 360, Jan_Type::SCISSORS);

	//���E�ǂ̗p��
	Init_Floor(STAGE_04_FLOOR);

	//�������  STAGE_04_FLOOR ��
	obj_floor[0] = new Floor(0, 700, 1280, 20, 0x493759);		//��
	obj_floor[1] = new Floor(0, 0, 1280, 1, 0x493759);			//�V��
	obj_floor[2] = new Floor(0, 0, 20, 1720, 0x493759);			//�ǁi���j
	obj_floor[3] = new Floor(1260, 0, 20, 1720, 0x493759);		//�ǁi�E�j
	obj_floor[4] = new Floor(300, 500, 200, 15, 0x493759);		//����(����)
	obj_floor[5] = new Floor(600, 350, 150, 15, 0x493759);		//����(�^�񒆉�)
	obj_floor[6] = new Floor(400, 180, 150, 15, 0x493759);		//����(�㉡)
	obj_floor[7] = new Floor(390, 425, 15, 170, 0x493759);		//����(���c)
	obj_floor[8] = new Floor(667, 295, 15, 130, 0x493759);		//����(�^�񒆏c)
	obj_floor[9] = new Floor(467, 125, 15, 130, 0x493759);		//����(��c)
	obj_floor[10] = new Floor(0, 320, 100, 10, 0x493759);		//���@
	obj_floor[11] = new Floor(0, 540, 70, 10, 0x493759);		//���A
	obj_floor[12] = new Floor(300, 0, 10, 80, 0x493759);		//���B
	obj_floor[13] = new Floor(900, 0, 10, 130, 0x493759);		//���C
	obj_floor[14] = new Floor(1100, 0, 10, 40, 0x493759);		//���D
	obj_floor[15] = new Floor(1180, 150, 100, 10, 0x493759);	//���E
	obj_floor[16] = new Floor(1230, 400, 30, 10, 0x493759);		//���F
	obj_floor[17] = new Floor(1000, 650, 10, 70, 0x493759);		//���G
	obj_floor[18] = new Floor(700, 680, 10, 40, 0x493759);		//���H
}

//�f�X�g���N�^
Scene_Stage04::~Scene_Stage04()
{
}

//�X�V
void Scene_Stage04::Update()
{
	//�ڐG����񂯂�łȂ���
	if (janken_flag == false)
	{
		obj_player->Update();    // �v���C���[�X�V�E����\
		obj_enemy->Update();     //�G�L�����X�V�E��������



		//�G�ƃv���C���[�̓����蔻��  �@������"�ڐG����񂯂�"
		if (obj_enemy->Hit_Character(obj_player) == true)
		{
			//�G���o����������_���Ɍ��߂�@�@�@�i�����_����int�^�̒l(0�`2)�� Jan_Type�^�ɕϊ��j
			Jan_Type enemy_janken = static_cast<Jan_Type> (GetRand(2));

			//����񂯂�p�I�u�W�F�N�g����
			obj_janken = new Janken(enemy_janken);


			//�ڐG����񂯂�J�n
			janken_flag = true;

		}
	}
	else
	{
		//�ڐG������񂯂�̏��������s
		Update_Janken();
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


	HitCtrl_Floor(obj_player, STAGE_04_FLOOR);     // player�@���E�ǔ���
	HitCtrl_Floor(obj_enemy, STAGE_04_FLOOR);      // �G�@�@�@���E�ǔ���


}


//�`��
void Scene_Stage04::Draw() const
{
	//�X�e�[�W�w�i�`��
	DrawRotaGraph(640, 360, 1, 0, back_image, FALSE);

	//�ڐG����񂯂�łȂ���
	if (janken_flag == false)
	{

		obj_player->Draw();  //�v���C���[�`��
		obj_enemy->Draw();   //�G�L�����`��

		//���E�Ǖ`��
		for (int i = 0; i < STAGE_04_FLOOR; i++)
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

	//DrawString(640, 360, "Stage04", 0xffffff);
}

//����񂯂�X�V�E��������
void Scene_Stage04::Update_Janken()
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
void Scene_Stage04::Draw_Janken() const
{
	obj_janken->Draw();
}

//�V�[���̕ύX
AbstractScene* Scene_Stage04::ChangeScene()
{
	//�G��HP��0�ȉ�
	if (obj_enemy->GetHP() < 0)
	{
		//�Q�[���N���A�V�[���֐؂�ւ�
		return dynamic_cast<AbstractScene*> (new GameClearScene(5));
	}

	//�v���C���[��HP��0�ȉ�
	if (obj_player->GetHP() < 0)
	{
		//�Q�[���I�[�o�[�V�[���֐؂�ւ�
		return dynamic_cast<AbstractScene*> (new GameOverScene());
	}

	return this;
}