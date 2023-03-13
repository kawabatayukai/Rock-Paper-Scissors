#include "Scene_Stage03.h"
#include"KeyManager.h"
#include"DxLib.h"
#include "Scene_GameClear.h"
#include "Scene_GameOver.h"
#include "Stage_Base.h"

//�f�o�b�O���[�h
#include"Debug_Manager.h"

//�R���X�g���N�^
Scene_Stage03::Scene_Stage03(const Player* player)
{
	stage = LoadGraph("images/stage03/stage03back.png");


	//�v���C���[��񂪓n����Ă����
	if (player != nullptr)
	{
		//���������p�����v���C���[�𐶐�
		obj_player = new Player(*player);
	}
	else
	{
		//�v���C���[�𐶐�
		obj_player = new Player(10, 640);
	}

	//�G�𐶐�							//�G�̑����`���L
	obj_enemy = new Enemy_03(950, 680, Jan_Type::ROCK);//�G�̈ʒu

	//���E�ǂ̗p��
	Init_Floor(STAGE_03_FLOOR);

	//�������  STAGE_03_FLOOR ��
	obj_floor[0] = new Floor(0, 700, 1280, 20, GetColor(240,230,140));      //��
	obj_floor[1] = new Floor(0, 0, 20, 1720,GetColor(240, 230, 140));        //�ǁi���j
	obj_floor[2] = new Floor(1260, 0, 20, 1720,GetColor(240, 230, 140));     //�ǁi�E�j

	//�E���珇��
	obj_floor[3] = new Floor(970, 300, 130, 40, GetColor(193, 107, 68));//����1
	obj_floor[4] = new Floor(780, 230, 130, 40, GetColor(193, 107, 68));//����2//130
	obj_floor[5] = new Floor(585, 300, 130, 40, GetColor(193, 107, 68));//����3//100
	obj_floor[6] = new Floor(400, 230, 130, 40, GetColor(193, 107, 68));//����4//130
	obj_floor[7] = new Floor(220, 300, 130, 40, GetColor(193, 107, 68));//����5//130
	obj_floor[8] = new Floor(20,  400, 90, 40, GetColor(193, 107, 68));//����6//100
	obj_floor[9] = new Floor(120, 550, 90, 40, GetColor(193, 107, 68));//����7//130
	//obj_floor[10] = new Floor(15, 250, 120, 20);//����8//130

}

//�f�X�g���N�^
Scene_Stage03::~Scene_Stage03()
{
}

//�X�V
void Scene_Stage03::Update()
{
	//�ڐG����񂯂�łȂ���
	if (janken_flag == false)
	{
		obj_player->Update();    // �v���C���[�X�V�E����\
		obj_enemy->Update();     //�G�L�����X�V�E��������
		obj_enemy->ChangeDir(obj_player->GetX());//�v���C���[��x < 640��������G�l�~�[�̒e�̌�����ς���
		obj_enemy->ChangeType(obj_enemy->GetType());
	


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

					//��~���_���[�W�y��
					if (obj_enemy-> GetWaitTime() > 0) {

						obj_enemy->ReceiveDamage(10);     //�y���_���[�W������

					}
					else{
					obj_enemy->ReceiveDamage(30);     //�_���[�W������

					}
					obj_player->DeleteJangeki(i);     //������������񌂂��폜
					i--;
				}

				break;

			case Jan_Type::SCISSORS:                       //�G�̑����@�`���L

				//�O�[�̂���񌂂̂ݗL��
				if (jangeki_type == Jan_Type::ROCK)
				{

					if(obj_enemy->GetWaitTime() > 0){

						obj_enemy->ReceiveDamage(10);     //�y���_���[�W������
					}
					else {
						obj_enemy->ReceiveDamage(30);     //�_���[�W������
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

						obj_enemy->ReceiveDamage(10); //�y���_���[�W������

					}
					else {

						obj_enemy->ReceiveDamage(30); //�_���[�W������

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
			//�_���[�W���󂯂�i�v���C���[�j
			obj_player->ReceiveDamage(30);

			//������������񌂂��폜
			obj_enemy->DeleteJangeki(i);
			i--;
		}
	}


	HitCtrl_Floor(obj_player, STAGE_03_FLOOR);     // player�@���E�ǔ���
	HitCtrl_Floor(obj_enemy, STAGE_03_FLOOR);      // �G�@�@�@���E�ǔ���


}


//�`��
void Scene_Stage03::Draw() const
{
	//�X�e�[�W�`��
	DrawGraph(0, 0, stage, FALSE);

	//HP�`��
	DrawUI(obj_enemy->GetType(), obj_enemy->GetHP());

	//�ڐG����񂯂�łȂ���
	if (janken_flag == false)
	{

		obj_player->Draw();  //�v���C���[�`��
		obj_enemy->Draw();   //�G�L�����`��

	
		//���E�Ǖ`��
		for (int i = 0; i < STAGE_03_FLOOR; i++)
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

	//DrawString(640, 360, "Stage03", 0xffff);
}

//����񂯂�X�V�E��������
void Scene_Stage03::Update_Janken()
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
	//if (obj_enemy->GetHP() < 0) {

	//	//�Q�[���N���A�V�[���֐؂�ւ�
	//	return dynamic_cast<AbstractScene*> (new GameClearScene(4));

	//}

	//�v���C���[��HP��0
	if (obj_player->GetHP() < 0) {

		//�Q�[���I�[�o�[�V�[���֐؂�ւ�
		return dynamic_cast<AbstractScene*> (new GameOverScene(3));
	}

#endif // DEBUG_OFF_03

	return this;
}