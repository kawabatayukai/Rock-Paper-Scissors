#include "Scene_Stage08.h"
#include"KeyManager.h"
#include"DxLib.h"
#define PI    3.1415926535897932384626433832795f

//�R���X�g���N�^
Scene_Stage08::Scene_Stage08(const Player* player)
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
	obj_enemy = new Enemy_08(1200, 360, Jan_Type::SCISSORS);

	//���E�ǂ̗p��
	Init_Floor(STAGE_08_FLOOR);

	//�������  STAGE_08_FLOOR ��
	obj_floor[0] = new Floor(0, 700, 1280, 20);        //��
	obj_floor[1] = new Floor(0, 0, 20, 1720);           //�ǁi���j
	obj_floor[2] = new Floor(1260, 0, 20, 1720);           //�ǁi�E�j
	obj_floor[3] = new Floor(211, 590, 100, 5);      //����@��1
	obj_floor[4] = new Floor(465, 590, 105, 5);      //����@��2
	obj_floor[5] = new Floor(717, 590, 107, 5);      //����@��3
	obj_floor[6] = new Floor(973, 590, 110, 5);      //����@��4
	obj_floor[7] = new Floor(307, 470, 160, 5);      //����@�E��
	obj_floor[8] = new Floor(565, 470, 153, 5);      //����@�E��
	obj_floor[9] = new Floor(820, 470, 153, 5);      //����@�E��
	obj_floor[10] = new Floor(465, 470, 5, 120);      //����@�E��
	obj_floor[11] = new Floor(306, 470, 5, 120);      //����@�E��
	obj_floor[12] = new Floor(717, 470,  5,120);      //����@�E��
	obj_floor[13] = new Floor(973, 470,  5,120);      //����@�E��
	obj_floor[14] = new Floor(565, 475, 5, 120);      //����@�E��
	obj_floor[15] = new Floor(820, 475, 5, 120);      //����@�E��

	obj_floor[16] = new Floor(311, 290, 100, 5);      //����@�E��
	obj_floor[17] = new Floor(565, 290, 105, 5);      //����@�E��
	obj_floor[18] = new Floor(817, 290, 108, 5);      //����@�E��
	obj_floor[19] = new Floor(1073, 290, 445, 5);      //����@�E��
	obj_floor[20] = new Floor(407, 170, 160, 5);      //����@�E��
	obj_floor[21] = new Floor(665, 170, 153, 5);      //����@�E��
	obj_floor[22] = new Floor(920, 170, 153, 5);      //����@�E��
	obj_floor[23] = new Floor(565, 170, 5, 120);      //����@�E��
	obj_floor[24] = new Floor(406, 170, 5, 120);      //����@�E��
	obj_floor[25] = new Floor(817, 170, 5, 120);      //����@�E��
	obj_floor[26] = new Floor(920, 175, 5, 120);      //����@�E��
	obj_floor[27] = new Floor(665, 175, 5, 120);      //����@�E��

	Back_image = LoadGraph("Stage08_1");
}

//�f�X�g���N�^
Scene_Stage08::~Scene_Stage08()
{
}

//�X�V
void Scene_Stage08::Update()
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


	HitCtrl_Floor(obj_player, STAGE_08_FLOOR);     // player�@���E�ǔ���
	HitCtrl_Floor(obj_enemy, STAGE_08_FLOOR);      // �G�@�@�@���E�ǔ���


}


//�`��
void Scene_Stage08::Draw() const
{
	DrawRotaGraph(640, 360, 1.f, 0, Back_image,TRUE);
	//�ڐG����񂯂�łȂ���
	if (janken_flag == false)
	{

		obj_player->Draw();  //�v���C���[�`��
		obj_enemy->Draw();   //�G�L�����`��

		//���E�Ǖ`��
		for (int i = 0; i < STAGE_08_FLOOR; i++)
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

	DrawString(640, 360, "Stage08", 0xffffff);
}

//����񂯂�X�V�E��������
void Scene_Stage08::Update_Janken()
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
void Scene_Stage08::Draw_Janken() const
{
	obj_janken->Draw();
}

//�V�[���̕ύX
AbstractScene* Scene_Stage08::ChangeScene()
{
	return this;
}