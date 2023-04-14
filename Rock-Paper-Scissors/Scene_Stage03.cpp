#include "Scene_Stage03.h"
#include"KeyManager.h"
#include"DxLib.h"
#include "Scene_GameClear.h"
#include "Scene_GameOver.h"
#include "Stage_Base.h"
#include "GameData.h"

//�f�o�b�O���[�h
#include"Debug_Manager.h"

//�R���X�g���N�^
Scene_Stage03::Scene_Stage03(const Player* player)
{
	stage = LoadGraph("images/stage03/stage03back.png");
	GroundImages = LoadGraph("images/stage03/GroundImages.png");
	BlockImages = LoadGraph("images/stage03/BlockImages.png");



	//�v���C���[��񂪓n����Ă����
	if (player != nullptr)
	{
		//���������p�����v���C���[�𐶐�
		obj_player = new Player(*player);
	}
	else
	{
		//�v���C���[�𐶐�
		obj_player = new Player(100, 640);
	}

	//�G�𐶐�							//�G�̑����`���L
	obj_enemy = new Enemy_03(950, 650, Jan_Type::SCISSORS);//�G�̈ʒu

	//���E�ǂ̗p��
	Init_Floor(STAGE_03_FLOOR);

	//�������  STAGE_03_FLOOR ��
	obj_floor[0] = new Floor("images/stage03/GroundImages.png", 0, 700, 1280, 20);      //��, GetColor(240, 230, 140)
	obj_floor[1] = new Floor("images/stage03/GroundImagesTate.png", 0, -100, 20, 1260);        //�ǁi���j, GetColor(240, 230, 140)
	obj_floor[2] = new Floor("images/stage03/GroundImagesTate.png", 1260, -100, 20, 1260);     //�ǁi�E�j, GetColor(240, 230, 140)

	//�E���珇��
	obj_floor[3] = new Floor("images/stage03/BlockImages.png", 1130, 340, 95, 1);//����1//130,GetColor(193, 107, 68)
	obj_floor[4] = new Floor("images/stage03/BlockImages.png", 1130, 500, 95, 1);//����2//130,	GetColor(193, 107, 68)
	obj_floor[5] = new Floor("images/stage03/BlockImages.png", 920, 205, 95, 1);//����3, GetColor(193, 107, 68)
	obj_floor[6] = new Floor("images/stage03/BlockImages.png", 770, 150, 95, 1);//����4//130, GetColor(193, 107, 68)
	obj_floor[7] = new Floor("images/stage03/BlockImages.png", 575, 205, 95, 1);//����5//100, GetColor(193, 107, 68)
	obj_floor[8] = new Floor("images/stage03/BlockImages.png", 390, 150, 95, 1);//����6//130, GetColor(193, 107, 68)
	obj_floor[9] = new Floor("images/stage03/BlockImages.png", 240, 205, 95, 1);//����7//130, GetColor(193, 107, 68)
	obj_floor[10] = new Floor("images/stage03/BlockImages.png", 60, 340, 95, 1);//����8//100, GetColor(193, 107, 68)
	obj_floor[11] = new Floor("images/stage03/BlockImages.png", 60, 500, 95, 1);//����9//130, GetColor(193, 107, 68)

	//obj_floor[12] = new Floor("images/stage03/BlockImages.png", 970, 405, 95, 10);//����3, GetColor(193, 107, 68)
	//obj_floor[12] = new Floor("images/stage03/BlockImages.png", 790, 360, 95, 10);//����4//130, GetColor(193, 107, 68)
	//obj_floor[13] = new Floor("images/stage03/BlockImages.png", 595, 425, 95, 10);//����5//100, GetColor(193, 107, 68)
	//obj_floor[14] = new Floor("images/stage03/BlockImages.png", 410, 360, 95, 10);//����6//130, GetColor(193, 107, 68)
	//obj_floor[16] = new Floor("images/stage03/BlockImages.png", 210, 405, 95, 10);//����7//130, GetColor(193, 107, 68)

	//�������Ԃ��Z�b�g
	GameData::Set_TimeLimit(7200); //2�� ���@7200 % 3600


}

//�f�X�g���N�^
Scene_Stage03::~Scene_Stage03()
{
}

//�X�V
void Scene_Stage03::Update()
{

	//���Ԃ��J�E���g
	GameData::Time_Update();


	//�ڐG����񂯂�J�n�O
	if (GetJanState()  == Jan_State::BEFORE)
	{
		obj_player->Update();    // �v���C���[�X�V�E����\
		obj_enemy->Update();     //�G�L�����X�V�E��������
		obj_enemy->ChangeDir(obj_player->GetX());//�v���C���[��x < 640��������G�l�~�[�̒e�̌�����ς���
		obj_enemy->SetPlayerLocation(obj_player->GetX(), obj_player->GetY());	//�v���C���[�̍��W���擾

		
	}

	//�ڐG����񂯂񏈗�
	Touch_Janken(obj_enemy, this, 3);

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

					//��~���_���[�W�y��
					if (obj_enemy->GetWaitTime() > 0) {

						obj_enemy->ReceiveDamage(12 - EnemyCutDamege);     //�y���_���[�W������

					}
					else {
						obj_enemy->ReceiveDamage(30 - EnemyCutDamege);     //�_���[�W������

					}
					obj_player->DeleteJangeki(i);     //������������񌂂��폜
					i--;

				}

				break;

			case Jan_Type::SCISSORS:                       //�G�̑����@�`���L

				//�O�[�̂���񌂂̂ݗL��
				if (jangeki_type == Jan_Type::ROCK)
				{

					if (obj_enemy->GetWaitTime() > 0) {

						obj_enemy->ReceiveDamage(12 - EnemyCutDamege);     //�y���_���[�W������
					}
					else {
						obj_enemy->ReceiveDamage(30 - EnemyCutDamege);     //�_���[�W������
					}
					obj_player->DeleteJangeki(i);     //������������񌂂��폜
					i--;
				}
				break;

			case Jan_Type::PAPER:                          //�G�̑����@�p�[

				//�`���L�̂���񌂂̂ݗL��
				if (jangeki_type == Jan_Type::SCISSORS)
				{
					if (obj_enemy->GetWaitTime() > 0) {

						obj_enemy->ReceiveDamage(12 - EnemyCutDamege); //�y���_���[�W������

					}
					else {

						obj_enemy->ReceiveDamage(30 - EnemyCutDamege); //�_���[�W������

					}

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
			//�G�l�~�[��HP��40�ȉ��̏ꍇ35�_���[�W�H�炤
			if (obj_enemy->GetHP() <= 40) {

				//���a��90.0f�̏ꍇ�̃_���[�W
				float radius = 50.0f;

				if (radius >= 50.0f) {

					obj_player->ReceiveDamage(35 - PlayerCutDamege) ;
				}
			}

			//����ȊO
			//�ʏ펞�̃_���[�W���󂯂�i�v���C���[�j
			else obj_player->ReceiveDamage(20 - PlayerCutDamege);

			
			//������������񌂂��폜
			obj_enemy->DeleteJangeki(i);
			i--;
		}
	}

	///////////////���u���b�N�̓����蔻��폜///////////////////
	//�ǂƂ̓����蔻��
	if (obj_player->Get_X() <= 50 || obj_player->Get_X() >= 1200)
	{
		HitCtrl_Floor(obj_player, STAGE_03_FLOOR);     // player�@���E�ǔ���
	}

	//�v���C���[��y���W���������Ȃ����̂ݓ����蔻����擾
	if (obj_player->Get_Y() >= obj_player->Get_OldY())
	{
		HitCtrl_Floor(obj_player, STAGE_03_FLOOR);     // player�@���E�ǔ���
	}

	//�G��y���W���������Ȃ����̂ݓ����蔻����擾
	if (obj_enemy->GetY() >= obj_enemy->Get_OldY())
	{
		HitCtrl_Floor(obj_enemy, STAGE_03_FLOOR);      // �G�@�@�@���E�ǔ���
	}


}


//�`��
void Scene_Stage03::Draw() const
{
	//�X�e�[�W�`��
	DrawGraph(0, 0, stage, FALSE);

	//HP�`��
	DrawUI(obj_enemy->GetType(), obj_enemy->GetHP());
	DrawUI_ON_Enemy(obj_enemy);//HP�o�[

	//�ڐG����񂯂�łȂ���
	if (GetJanState() == Jan_State::START || GetJanState() == Jan_State::BEFORE)
	{

		obj_player->Draw();  //�v���C���[�`��
		obj_enemy->Draw();   //�G�L�����`��


		//���E�Ǖ`��
		for (int i = 0; i < STAGE_03_FLOOR; i++)
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

	//DrawString(640, 360, "Stage03", 0xffff);
}



//����񂯂�`��
void Scene_Stage03::Draw_Janken() const
{
	obj_janken->Draw();
}

//�V�[���̕ύX
AbstractScene* Scene_Stage03::ChangeScene()
{
	//"Debug_Manager.h" �� #define DEBUG_OFF_03 ���R�����g�A�E�g����ƊJ�����[�h
#ifdef DEBUG_OFF_03

	//�G��HP0
	if (obj_enemy->GetHP() < 0) {

		//�Q�[���N���A�V�[���֐؂�ւ�
		return dynamic_cast<AbstractScene*> (new GameClearScene(4));

	}

	//�v���C���[��HP��0�ȉ�
	if (obj_player->GetHP() < 0 || GameData::Get_Each_Time() <= 0){
		 

		//�Q�[���I�[�o�[�V�[���֐؂�ւ�
		return dynamic_cast<AbstractScene*> (new GameOverScene(3));
	}

#endif // DEBUG_OFF_03

	return this;
}

//����񂯂�I����̋����i�v���C���[�����j

void Scene_Stage03::AfterJanken_WIN()
{
	//����񂯂񏟗���
	PlayerCutDamege = 10;

	obj_player->SetX(200);
	obj_enemy->SetX(1150);
}

//����񂯂�I����̋����i�v���C���[�����j
void Scene_Stage03::AfterJanken_LOSE()
{

	//����񂯂�s�k��
	EnemyCutDamege = 5;

	obj_player->SetX(200);
	obj_enemy->SetX(1150);
}