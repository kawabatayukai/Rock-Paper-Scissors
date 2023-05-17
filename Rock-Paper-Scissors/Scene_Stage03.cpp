#include "Scene_Stage03.h"
#include"KeyManager.h"
#include"DxLib.h"
#include "Scene_GameClear.h"
#include "Scene_GameOver.h"
#include "Stage_Base.h"
#include "GameData.h"
#include"SoundSystem.h"


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
	obj_floor[3] = new Floor("images/stage03/BlockImages.png", 1130, 340, 95, 30);//����1//130,GetColor(193, 107, 68)
	obj_floor[4] = new Floor("images/stage03/BlockImages.png", 1130, 500, 95, 30);//����2//130,	GetColor(193, 107, 68)
	obj_floor[5] = new Floor("images/stage03/BlockImages.png", 920, 205, 95, 30);//����3, GetColor(193, 107, 68)
	obj_floor[6] = new Floor("images/stage03/BlockImages.png", 770, 150, 95, 30);//����4//130, GetColor(193, 107, 68)
	obj_floor[7] = new Floor("images/stage03/BlockImages.png", 575, 205, 95, 30);//����5//100, GetColor(193, 107, 68)
	obj_floor[8] = new Floor("images/stage03/BlockImages.png", 390, 150, 95, 30);//����6//130, GetColor(193, 107, 68)
	obj_floor[9] = new Floor("images/stage03/BlockImages.png", 240, 205, 95, 30);//����7//130, GetColor(193, 107, 68)
	obj_floor[10] = new Floor("images/stage03/BlockImages.png", 60, 340, 95, 30);//����8//100, GetColor(193, 107, 68)
	obj_floor[11] = new Floor("images/stage03/BlockImages.png", 60, 500, 95, 30);//����9//130, GetColor(193, 107, 68)


	
	//obj_floor[12] = new Floor("images/stage03/BlockImages.png", 970, 405, 95, 10);//����3, GetColor(193, 107, 68)
	//obj_floor[12] = new Floor("images/stage03/BlockImages.png", 790, 360, 95, 10);//����4//130, GetColor(193, 107, 68)
	//obj_floor[13] = new Floor("images/stage03/BlockImages.png", 595, 425, 95, 10);//����5//100, GetColor(193, 107, 68)
	//obj_floor[14] = new Floor("images/stage03/BlockImages.png", 410, 360, 95, 10);//����6//130, GetColor(193, 107, 68)
	//obj_floor[16] = new Floor("images/stage03/BlockImages.png", 210, 405, 95, 10);//����7//130, GetColor(193, 107, 68)

	//�������Ԃ��Z�b�g
	GameData::Set_TimeLimit(10860); //3���@//2�� ���@7200 % 3600

	//BGM���[�h
	bgm = LoadSoundMem("Sound/st03/St03BGM.wav");
}

//�f�X�g���N�^
Scene_Stage03::~Scene_Stage03()
{
	StopSoundMem(bgm);
}

//�X�V
void Scene_Stage03::Update()
{
	//BGM��炷
	if (CheckSoundMem(bgm) == 0) PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);


	//�ڐG����񂯂�J�n�O
	if (GetJanState()  == Jan_State::BEFORE)
	{
		obj_player->Update();    // �v���C���[�X�V�E����\
		obj_enemy->Update();     //�G�L�����X�V�E��������
		obj_enemy->ChangeDir(obj_player->GetX());//�v���C���[��x < 640��������G�l�~�[�̒e�̌�����ς���
		obj_enemy->SetPlayerLocation(obj_player->GetX(), obj_player->GetY());	//�v���C���[�̍��W���擾
		
		//���Ԃ��J�E���g
		GameData::Time_Update();
	}

	
	
	//�ڐG����񂯂񏈗�
	Touch_Janken(obj_enemy, this, 3);

	//����SE��~
	StopSoundMem(obj_enemy->GetRunSE());
	//����SE��~
	StopSoundMem(obj_enemy->GetWalkSE());

	Effect_Update_HitJangeki(obj_enemy);

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
			case Jan_Type::ROCK:           //�G�̑����@�O�[

				//�p�[�̂���񌂂̂ݗL��
				if (jangeki_type == Jan_Type::PAPER)
				{

					//HP86�ȏ�̎�
					if (obj_enemy->GetHP() >= 86) {


						if(obj_enemy->GetWaitTime() > 0 || obj_enemy->GetWaitTime() < 200){

							SheeldEnduranse = 27;				//3 - ����񂯂񕉂����� 1
							obj_enemy->ReceiveDamage(30 - SheeldEnduranse - EnemyCutDamege); //�y���_���[�W������

						}

					}

					else if (obj_enemy->GetHP() <= 85 && obj_enemy->GetHP() >= 71) {


						if(obj_enemy->GetWaitTime() > 0 || obj_enemy->GetWaitTime() < 200) {

							SheeldEnduranse = 24;			//6 - ����񂯂񕉂����� 3
							obj_enemy->ReceiveDamage(30 - SheeldEnduranse- EnemyCutDamege); //�y���_���[�W������
							
						}

						SoundSystem::PlaySE(SE::ENEMY_SLIGHTLYBROKEN);
					
					}
					else if (obj_enemy->GetHP() <= 70 && obj_enemy->GetHP() >= 56) {
					
						if(obj_enemy->GetWaitTime() > 0 || obj_enemy->GetWaitTime() < 200){

							SheeldEnduranse = 21;			//9 - ����񂯂񕉂����� 5
							obj_enemy->ReceiveDamage(30 - SheeldEnduranse- EnemyCutDamege); //�y���_���[�W������

						}

						SoundSystem::PlaySE(SE::ENEMY_SLIGHTLYBROKEN);
						
					}
					else if (obj_enemy->GetHP() <= 55 && obj_enemy->GetHP() >= 41) {

			
						if(obj_enemy->GetWaitTime() > 0 ||  obj_enemy->GetWaitTime() < 200){

							
							SheeldEnduranse = 18;				//12 - ����񂯂񕉂����� 6
							obj_enemy->ReceiveDamage(30 - SheeldEnduranse - EnemyCutDamege); //�y���_���[�W������
						
						}

						SoundSystem::PlaySE(SE::ENEMY_SHIELDBROKEN);
					}
					else if (obj_enemy->GetHP() <= 40) {


						if (obj_enemy->GetWaitTime() > 0 || obj_enemy->GetWaitTime() < 200) {

							
							SheeldEnduranse = 15;				//15 - ����񂯂񕉂����� 8
							obj_enemy->ReceiveDamage(30 - SheeldEnduranse - EnemyCutDamege); //�y���_���[�W������
						}
						

					}

					else {

						if (obj_enemy->GetWaitTime() < 200 || obj_enemy->GetWaitTime() > 0){
															 

															//1 - ����񂯂񕉂����� 1

							obj_enemy->ReceiveDamage(1 - EnemyCutDamege); //�_���[�W������


						}
					}


					obj_player->DeleteJangeki(i);     //������������񌂂��폜
					i--;

				}

				break;

			//case Jan_Type::SCISSORS:                       //�G�̑����@�`���L

			//	//�O�[�̂���񌂂̂ݗL��
			//	if (jangeki_type == Jan_Type::ROCK)
			//	{

			//		//HP��100�ȉ���85�ȏ�̎�
			//		if (obj_enemy->GetHP() >= 86 && obj_enemy->GetWaitTime() > 0) {

			//			SheeldEnduranse = 27;
			//			obj_enemy->ReceiveDamage(30 - (SheeldEnduranse)-EnemyCutDamege); //�y���_���[�W������

			//		}
			//		else if (obj_enemy->GetHP() <= 85 && obj_enemy->GetHP() >= 71 && obj_enemy->GetWaitTime() > 0) {

			//			SheeldEnduranse = 24;
			//			obj_enemy->ReceiveDamage(30 - (SheeldEnduranse)-EnemyCutDamege); //�y���_���[�W������


			//		}
			//		else if (obj_enemy->GetHP() <= 70 && obj_enemy->GetHP() >= 56 && obj_enemy->GetWaitTime() > 0) {

			//			SheeldEnduranse = 21;
			//			obj_enemy->ReceiveDamage(30 - (SheeldEnduranse)-EnemyCutDamege); //�y���_���[�W������


			//		}
			//		else if (obj_enemy->GetHP() <= 55 && obj_enemy->GetHP() >= 41 && obj_enemy->GetWaitTime() > 0) {

			//			SheeldEnduranse = 18;
			//			obj_enemy->ReceiveDamage(30 - (SheeldEnduranse)-EnemyCutDamege); //�y���_���[�W������


			//		}
			//		else if (obj_enemy->GetHP() <= 40 && obj_enemy->GetWaitTime() > 0) {

			//			SheeldEnduranse = 15;
			//			obj_enemy->ReceiveDamage(30 - (SheeldEnduranse)-EnemyCutDamege); //�y���_���[�W������


			//		}

			//		//}
			//		else {

			//			SheeldEnduranse = 0;
			//			obj_enemy->ReceiveDamage(8 - EnemyCutDamege); //�_���[�W������

			//		}


			//		obj_player->DeleteJangeki(i);     //������������񌂂��폜
			//		i--;
			//	}
			//	break;

			//case Jan_Type::PAPER:                          //�G�̑����@�p�[

			//	//�`���L�̂���񌂂̂ݗL��
			//	if (jangeki_type == Jan_Type::SCISSORS)
			//	{
			//		//if (obj_enemy->GetWaitTime() > 0) {

			//			//HP�ɉ����ĐH�炤�_���[�W���ω�����
			//			
			//			//HP��100�ȉ���85�ȏ�̎�
			//			if (obj_enemy->GetHP() >= 86 && obj_enemy->GetWaitTime() > 0) {

			//				SheeldEnduranse = 27;
			//				obj_enemy->ReceiveDamage(30 -(SheeldEnduranse)- EnemyCutDamege); //�y���_���[�W������

			//			}
			//			else if (obj_enemy->GetHP() <= 85 && obj_enemy->GetHP() >= 71 &&obj_enemy->GetWaitTime() > 0) {

			//				SheeldEnduranse = 24;
			//				obj_enemy->ReceiveDamage(30 - (SheeldEnduranse)-EnemyCutDamege); //�y���_���[�W������


			//			}
			//			else if (obj_enemy->GetHP() <= 70 && obj_enemy->GetHP() >= 56 && obj_enemy->GetWaitTime() > 0) {

			//				SheeldEnduranse = 21;
			//				obj_enemy->ReceiveDamage(30 - (SheeldEnduranse)-EnemyCutDamege); //�y���_���[�W������


			//			}
			//			else if (obj_enemy->GetHP() <= 55 && obj_enemy->GetHP() >= 41 && obj_enemy->GetWaitTime() > 0) {

			//				SheeldEnduranse = 18;
			//				obj_enemy->ReceiveDamage(30 - (SheeldEnduranse)-EnemyCutDamege); //�y���_���[�W������


			//			}
			//			else if (obj_enemy->GetHP() <= 40 && obj_enemy->GetWaitTime() > 0) {

			//				SheeldEnduranse = 15;
			//				obj_enemy->ReceiveDamage(30 - (SheeldEnduranse)-EnemyCutDamege); //�y���_���[�W������


			//			}

			//		//}
			//		else {

			//				SheeldEnduranse = 0;
			//			obj_enemy->ReceiveDamage(8 - EnemyCutDamege); //�_���[�W������

			//		}


			//		obj_player->DeleteJangeki(i);     //������������񌂂��폜
			//		i--;
			//	}
			//	break;

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
			//�G�l�~�[��HP��40�ȉ��̏ꍇ25�_���[�W�H�炤
			if (obj_enemy->GetHP() <= 40) {

				//���a��50.0f�̏ꍇ�̃_���[�W
				float radius = 50.0f;

				if (radius >= 50.0f) {

					obj_player->ReceiveDamage(25 - PlayerCutDamege) ;
				}
			}
			else if (obj_enemy->GetHP() <= 85 && obj_enemy->GetHP() >= 41) {

				//���a��50.0f�̏ꍇ�̃_���[�W
				float radius = 25.5f;

				if (radius >= 25.5f) {

					obj_player->ReceiveDamage(15 - PlayerCutDamege);
				}

			}
			//����ȊO
			//�ʏ펞�̃_���[�W���󂯂�i�v���C���[�j
			else obj_player->ReceiveDamage(15 - PlayerCutDamege);

			
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

		//����񂯂񕉂�����
		if (Player_Janwin == 1)
		{
			float p_x = obj_player->GetX();
			float p_y = obj_player->GetY();

			DrawString(p_x, p_y - 55, "�h���UP��", 0xfff);
		}
		else {
			int Player_Janwin = 0;
		}

		if (Enemy_Janwin == 1) {

			if (obj_enemy->GetWaitTime() > 0) {
				//�G�l�~�[������ʃe�L�X�g�\��

				DrawFormatString((int)(obj_enemy->GetX() - 40), (int)(obj_enemy->GetY() - 90), GetColor(0, 0, 255), "����ɖh��UP��", obj_enemy->GetWaitTime());
			}
			else {

				int Enemy_Janwin = 0;

			}
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
	
	//�ڐG����񂯂�Effect
	Effect_Draw_HitJangeki();

  


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
	if (IsEnd_DeathEnemy() == true) {


		//����SE��~
		StopSoundMem(obj_enemy->GetRunSE());
		//����SE��~
		StopSoundMem(obj_enemy->GetWalkSE());
		//�Q�[���N���A�V�[���֐؂�ւ�
		return dynamic_cast<AbstractScene*> (new GameClearScene(4));

	}

	//�v���C���[��HP��0�ȉ�
					//���S���o//
	if (obj_player->IsDeathPlayer() == true){
		 

		//����SE��~
		StopSoundMem(obj_enemy->GetRunSE());
		//����SE��~
		StopSoundMem(obj_enemy->GetWalkSE());
		//�Q�[���I�[�o�[�V�[���֐؂�ւ�
		return dynamic_cast<AbstractScene*> (new GameOverScene(3));
	}

#endif // DEBUG_OFF_03

	return this;
}

//����񂯂�I����̋����i�v���C���[�����j

void Scene_Stage03::AfterJanken_WIN()
{

	//��������1
	Player_Janwin = 1;


	//����񂯂񏟗���
	PlayerCutDamege = 10;
	
	obj_player->SetX(200);
	
	
}

//����񂯂�I����̋����i�v���C���[�����j
void Scene_Stage03::AfterJanken_LOSE()
{

	//��������1
	Enemy_Janwin = 1;


	if(obj_enemy->GetHP() >= 86){

	    //����񂯂�s�k��
	    EnemyCutDamege = 2;
	}
	else if(obj_enemy->GetHP() <= 85 && obj_enemy->GetHP() >= 71) {

		//����񂯂�s�k��
		EnemyCutDamege = 3;

	}
	else if (obj_enemy->GetHP() <= 70 && obj_enemy->GetHP() >= 56) {

		//����񂯂�s�k��
		EnemyCutDamege = 5;

	}
	else if (obj_enemy->GetHP() <= 55 && obj_enemy->GetHP() >= 41) {

		//����񂯂�s�k��
		EnemyCutDamege = 6;

	}
	else if (obj_enemy->GetHP() <= 40) {


		//����񂯂�s�k��
		EnemyCutDamege = 8;


	}
	else {

		//����񂯂�s�k��
		EnemyCutDamege = 1;

	}

	//X��200�Ɉړ�
	obj_player->SetX(200);
	

}


