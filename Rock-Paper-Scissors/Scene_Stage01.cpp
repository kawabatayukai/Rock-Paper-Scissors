#include "Scene_Stage01.h"
#include"KeyManager.h"
#include"Scene_GameOver.h"
#include"Scene_GameClear.h"
#include"DxLib.h"

//�f�o�b�O���[�h
#include"Debug_Manager.h"

//�\�����镶����
namespace _STR_TUTORIAL
{
	//char draw_str[][40] =
	//{
	//	"�悤�����B�ŏ��ɑ�����������܂�",
	//	"���X�e�B�b�N�ō��E�ړ��ł��܂�",
	//	"LB�{�^���ŃW�����v���܂�",
	//	"�E�X�e�B�b�N�ŏƏ��𑀍�ł��܂�",
	//	"�G�ɐڐG����Ƃ���񂯂񂪎n�܂�܂�",
	//};
}

//�R���X�g���N�^
Scene_Stage01::Scene_Stage01(const Player* player)
	: frame_count(0), Now_Tut_State(TUTORIAL_STATE::START_TUTORIAL)
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
	obj_enemy = new Enemy_01(1200, 360, Jan_Type::SCISSORS);

	//���E�ǂ̗p��
	Init_Floor(STAGE_01_FLOOR);

	//�������
	obj_floor[0] = new Floor(0, 700, 1280, 20);        //��
	obj_floor[1] = new Floor(0, 0, 20, 720);           //�ǁi���j
	obj_floor[2] = new Floor(1260, 0, 20, 720);           //�ǁi�E�j
	obj_floor[3] = new Floor(1000, 100, 120, 50);      //�ǁi�E�j
	obj_floor[4] = new Floor(400, 300, 500, 20);      //�ǁi�E�j


	//�F
	blue = GetColor(0, 0, 255);
	red = GetColor(255, 0, 0);
	brack = GetColor(0, 0, 0);
	white = GetColor(255, 255, 255);
	green = GetColor(0, 255, 0);

	//�t�H���g�f�[�^���쐬�@�@�@�@�@�@Windows�W�����ڃt�H���g�Ȃ���v�B�����@�@�@[��� "Yu Gothic UI"]
	font_tut = CreateFontToHandle("���C���I", 40, 8, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 2);
}

//�f�X�g���N�^
Scene_Stage01::~Scene_Stage01()
{
}

//�X�V
void Scene_Stage01::Update()
{
	//�ڐG����񂯂�J�n�O
	if (GetJanState() == Jan_State::BEFORE)
	{
		obj_player->Update();    // �v���C���[�X�V�E����\
		//obj_enemy->Update();     //�G�L�����X�V�E��������

		//�v���C���[�̍��W���擾
		//obj_enemy->SetPlayerLocation(obj_player->GetX(), obj_player->GetY());

	}

	//�ڐG����񂯂񏈗�
	Touch_Janken(obj_enemy, this, 1);


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


	HitCtrl_Floor(obj_player, STAGE_01_FLOOR);     // player�@���E�ǔ���
	HitCtrl_Floor(obj_enemy, STAGE_01_FLOOR);      // �G�@�@�@���E�ǔ���



	switch (Now_Tut_State)
	{
	case Scene_Stage01::TUTORIAL_STATE::START_TUTORIAL:
		break;
	case Scene_Stage01::TUTORIAL_STATE::PLAYER_MOVE:
		break;
	case Scene_Stage01::TUTORIAL_STATE::PLAYER_JUMP:
		break;
	case Scene_Stage01::TUTORIAL_STATE::PLAYER_AIMING:
		break;
	case Scene_Stage01::TUTORIAL_STATE::TOUCH_JANKEN:
		break;
	default:
		break;
	}

	NextTutorial();

}

//�`��
void Scene_Stage01::Draw() const
{
	//�ڐG����񂯂�J�n�O
	if (GetJanState() == Jan_State::BEFORE)
	{

		obj_player->Draw();  //�v���C���[�`��
		//obj_enemy->Draw();   //�G�L�����`��

		//���E�Ǖ`��
		for (int i = 0; i < STAGE_01_FLOOR; i++)
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


	//�\�����镶����
	//const char* str = _STR_TUTORIAL::draw_str[static_cast<int>(Now_Tut_State)];

	//DrawStringToHandle(200, 200, str, green, font_tut, white);



	//�_��
	static int counter;

	if (counter++ < 30)
	{
		DrawCircle(1060, 320, 20, white, TRUE);
		DrawCircle(1060, 320, 18, green, TRUE);
		DrawStringToHandle(1030, 310, "A", white, font_tut, brack);

		//DrawStringToHandle(1060, 320, "-- Press  A  Button --", white, font_other, green);
	}
	else if (counter > 60)  counter = 0;
	else {}


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
	if (obj_enemy->GetHP() < 0)
	{
		//�Q�[���N���A�V�[���֐؂�ւ�
		return dynamic_cast<AbstractScene*> (new GameClearScene(2));
	}

	//�v���C���[��HP��0�ȉ�
	if (obj_player->GetHP() < 0)
	{
		//�Q�[���I�[�o�[�V�[���֐؂�ւ�
		return dynamic_cast<AbstractScene*> (new GameOverScene(1));
	}

#endif 

	return this;   //�X�V�Ȃ�
}

//���̑����
void Scene_Stage01::NextTutorial()
{
	//�`���[�g���A��
	if (KeyManager::OnPadClicked(PAD_INPUT_A))
	{
		switch (Now_Tut_State)
		{
		case Scene_Stage01::TUTORIAL_STATE::START_TUTORIAL:

			//���E�ړ���
			Now_Tut_State = TUTORIAL_STATE::PLAYER_MOVE;
			break;

		case Scene_Stage01::TUTORIAL_STATE::PLAYER_MOVE:

			//�W�����v��
			Now_Tut_State = TUTORIAL_STATE::PLAYER_JUMP;
			break;

		case Scene_Stage01::TUTORIAL_STATE::PLAYER_JUMP:

			//�Ə���
			Now_Tut_State = TUTORIAL_STATE::PLAYER_AIMING;
			break;

		case Scene_Stage01::TUTORIAL_STATE::PLAYER_AIMING:

			//�ڐG����񂯂��
			Now_Tut_State = TUTORIAL_STATE::TOUCH_JANKEN;
			break;

		case Scene_Stage01::TUTORIAL_STATE::TOUCH_JANKEN:

			break;

		default:
			break;
		}
	}
}

//���E�ړ����m�F����
bool Scene_Stage01::CheckMoveLR()
{
	static bool move_left;    //���ړ�������
	static bool move_right;   //�E�ړ�������

	//�O��̍��W�ƈ�v���Ă����ꍇ�A�ړ����Ă��Ȃ�
	if (obj_player->Get_OldX() == obj_player->GetX()) return false;

	

	//�ǂ�����ړ�����
	if (move_left == true && move_right == true) return true;
}