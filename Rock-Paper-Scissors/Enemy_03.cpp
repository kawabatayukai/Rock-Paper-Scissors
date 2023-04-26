#include "Enemy_03.h"
#include"DxLib.h"
#include"Player.h"
#include"Jangeki_Base.h"
#include"Jangeki_Coming.h"
#include <typeinfo>


//�R���X�g���N�^�@   ���N���X�̃R���X�g���N�^���Ăԁ@�@�@�@ ���@���@���@�@�@����    ����
Enemy_03::Enemy_03(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
{

	speed = 1.5f;//1.5f //�O��1.85f
	dir = 1;//�G�l�~�[�̌���
	hp = 100;

	/*enemyimage[0] = LoadGraph("images/stage03/stage03attack.png");
	enemyimage[1] = LoadGraph("images/stage03/stage03gard.png");
	enemyimage[2] = LoadGraph("images/stage03/stage03jump.png");*/

	LoadDivGraph("images/stage03/stage03Anim.png", 6, 6, 1, 100, 100, enemyimage);
	LoadDivGraph("images/stage03/stage03SheeldEnduranse1.png", 6, 6, 1, 100, 100, enemyimage1);
	LoadDivGraph("images/stage03/stage03SheeldEnduranse2.png", 6, 6, 1, 100, 100, enemyimage2);
	LoadDivGraph("images/stage03/stage03SheeldEnduranse3.png", 6, 6, 1, 100, 100, enemyimage3);
	LoadDivGraph("images/stage03/stage03SheeldEnduranse4.png", 6, 6, 1, 100, 100, enemyimage4);

	LoadDivGraph("images/stage03/BreakSheeldAnim.png", 8, 8, 1, 220, 220, SheeldBreakAnim);


	//LoadDivGraph("images/stage03/stage03AnimMirror.png", 6, 6, 1, 100, 100, enemyimageMirror);

	Init_Jangeki();       //����񌂂�p��

	//�����p�^�[�� �J��Ԃ��@//0�œ���,1�Ŏ~�܂�
	moveinfo[0] = { 0, 950.f, 0.f , 1,  0 ,1 };//�����ʒu��X��950�Œ�~

	moveinfo[1] = { 1,  0 ,   0.f , 2, 200 ,1 };//�����ʒu��X��950�Œ�~
	//�������瓮��
	moveinfo[2] = { 0, 650.f, 0.f , 3,  0 ,0 };//X��650�܂œ���

	moveinfo[3] = { 1,  0 ,   0.f , 4, 0 ,1 };//X��650�Œ�~

	moveinfo[4] = { 0, 350.f, 0.f , 5, 0 ,1 };//X��350�܂œ���

	moveinfo[5] = { 1,  0 ,   0.f , 6, 200 ,1 };//X��350�Œ�~

	moveinfo[6] = { 0, 350.f, 0.f , 7, 0 ,1 };//X��350�̑���ɔ��

	moveinfo[7] = { 1,  0 ,   0.f , 8, 0 ,1 };//X��350�Œ�~

	//����ɏ��
	moveinfo[8] = { 0,  50.f , 0.f , 9, 0 ,0 };//X��70����ɔ��

	//moveinfo[9] = { 1,  0 ,   0.f , 10, 200 ,1 };//X��70�Œ�~

	moveinfo[9] = { 0, 280.f, 0.f , 10,  0 ,0 };//X��280�̑���ɔ��

	moveinfo[10] = { 1,  0 ,   0.f , 11, 200,1 };//X��280�Œ�~

	moveinfo[11] = { 0, 465.f, 0.f , 12,  0 ,0 };//X��465�̑���ɔ��

	//moveinfo[12] = { 1,  0 ,   0.f , 14, 200,1 };//X��465�Œ�~

	moveinfo[12] = { 0, 585.f,0.f , 13,  0 ,0 };//X��585�̑���ɔ��

	moveinfo[13] = { 1,  0 ,   0.f , 14, 200,1 };//X��585�Œ�~

	moveinfo[14] = { 0, 780.f, 0.f , 15,  0 ,0 };//X��780�̑���ɔ��

	//moveinfo[17] = { 1,  0 ,   0.f , 18, 200,1 };//X��780�Œ�~

	moveinfo[15] = { 0, 970.f, 0.f , 16,  0 ,0 };//X��970�̑���ɔ��

	moveinfo[16] = { 1,  0 ,   0.f , 17, 200,1 };//X��970�̑���Œ�~

	moveinfo[17] = { 0, 1150.f, 0.f , 18,  0 ,0 };//X��1160�̑���ɔ��

	//moveinfo[21] = { 1,  0 ,   0.f , 22, 200,1 };//X��1160�Œ�~

	moveinfo[18] = { 0,  1150.f , 0.f , 19, 0, 1 };//X��1160�̑���ɔ��

	//moveinfo[19] = { 1,  0 ,   0.f , 20, 200,1 };//X��1160�Œ�~

	moveinfo[19] = { 0,  970.f , 0.f , 20, 0, 1 };//X��930�܂ňړ�

	moveinfo[20] = { 1,  0 , 0.f , 21, 200,1 };//X��930�Œ�~


	//�O��̋t�p�^�[����
	moveinfo[21] = { 0, 1150.f , 0.f , 22, 0, 0 };//X��1050�̑���ɔ��

	//moveinfo[27] = { 1,  0 , 0.f , 28, 200,1 };//X��1020�Œ�~

	moveinfo[22] = { 0,  1150.f , 0.f , 23, 0, 0 };//X��1160�̑���ɔ��

	moveinfo[23] = { 1,  0 , 0.f , 24, 200, 1 };//X��1160�Œ�~

	moveinfo[24] = { 0,  970.f , 0.f , 25, 0, 0 };//X��970�̑���ɔ��

	//moveinfo[25] = { 1,  0 , 0.f , 26, 200,1 };//X��970�Œ�~

	moveinfo[25] = { 0,  780.f , 0.f , 26, 0, 0 };//X��780�̑���ɔ��

	moveinfo[26] = { 1,  0 , 0.f , 27, 200,1 };//X��780�Œ�~

	moveinfo[27] = { 0,  585.f , 0.f , 28, 0, 0 };//X��585�̑���ɔ��

	//moveinfo[28] = { 1,  0 ,   0.f , 29, 200,1 };//X��585�Œ�~

	moveinfo[28] = { 0, 465.f, 0.f , 29,  0 ,0 };//X��465�̑���ɔ��

	moveinfo[29] = { 1,  0 ,   0.f , 30, 200,1 };//X��465�Œ�~

	moveinfo[30] = { 0, 280.f, 0.f , 31,  0 ,0 };//X��280�̑���ɔ��


	//moveinfo[31] = { 1,  0 ,   0.f , 32, 200,1 };//X��280�Œ�~

	moveinfo[31] = { 0, 50.f,  0.f , 32,  0 ,0 };//X��70�܂œ���

	moveinfo[32] = { 1,  0 ,   0.f , 33, 200,1 };//X��70�Œ�~
	//�������瓮��2
	moveinfo[33] = { 0, 350.f, 0.f , 34,  0 ,1 };//�����ʒu��X��350�Œ�~

	moveinfo[34] = { 1,  0 ,   0.f , 35, 200 ,1 };//�����ʒu��X��350�Œ�~

	moveinfo[35] = { 0, 650.f, 0.f , 36,  0 ,0 };//X��650�܂œ���

	moveinfo[36] = { 1,  0 ,   0.f , 37, 200 ,1 };//X��650�Œ�~

	moveinfo[37] = { 0,	950.f, 0.f , 38, 0 ,0 };//X��900�܂œ���

	//moveinfo[47] = { 1,	 0,  0.f , 48, 62 ,1 };//X��900�ŏ����̎��Ԓ�~

	moveinfo[38] = { 1,  0 ,   0.f , 0, 200 ,1 };//X��900�Œ�~���z��[0]�ɖ߂�

}



//�f�X�g���N�^
Enemy_03::~Enemy_03()
{

}

//�X�V
void Enemy_03::Update()
{


	if (land_flg == true && moveinfo[current].enemywaitTime == 0 && moveinfo[current].jumpflg == 0)    //GetRand(30) == 3�@�̂Ƃ��낪�W�����v�̏���
	{
		g_add = -23.f;    //����-21.5f,�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v
		land_flg = false;  //�n�ʂɂ��Ă��Ȃ�

		speed = 2.8f;
	}


	//����񌂍X�V�E����
	Update_Jangeki();



	////�����ύX
	if (moveinfo[current].enemywaitTime > 0 || moveinfo[current].enemywaitTime < 200 && moveinfo[current].jumpflg == 0) {

		e_type = Jan_Type::ROCK;


	}
	//�����Ă���Ƃ������ύX
	/*else if (moveinfo[current].enemywaitTime < 200 && moveinfo[current].jumpflg == 0) {



		e_type = Jan_Type::SCISSORS;
	}*/

	if (hp > 40) {//HP40%��葽���̊ԃp�^�[���̓���������


		//�X�e03�p�^�[���p�֐�
		switch (moveinfo[current].moveflg)
		{
		case 0:
			Move_Pattern();

			break;
		case 1:
			//�҂����ԃJ�E���g
			waitcount++;
			if (moveinfo[current].enemywaitTime <= waitcount) {

				waitcount = 0;
				current = moveinfo[current].next_index;

				//�����_���ȓ���X����//
				//moveinfo[current].location_x = GetRand(1150);


			}
			/*case 2:
				MoveRunAway(float enemy_x, float enemy_y, int player_x, int player_y);*/
			break;
		default:
			break;
		}


	}
	else if (hp<=40 && st3_animcount < 8) {



	}
	else {

		//enemy��x��475�ȉ��̎�
		if (x <= 475) {

			//�O�����������
			speed = 7.5f;

		}
		//enemy��x��950�ȉ���475�ȏ�̎�
		else if (x <= 950 && x >= 475) {

			//�O�����������
			speed = 5.5f;

		}
		//enemy��x��950�ȏ�̎�
		else if (x >= 950) {

			//�O�����������
			speed = 7.5f;

		}
		//����ȊO�͕��ʂ̓���
		else
		{

			speed = 1.5f;


		}

		//�ڕW���W
		static float target_x = 0;
		static float target_y = 0;


		//��v��
		static int count;
		if (count == 0)
		{
			target_x = GetRand(1170) + 70;
			//if (x==1000)
			//{
			//	count = 1;
			//}
			count = 1;
		}
		if (count == 1)
		{

			if (x == target_x)
			{
				count = 0;
			}
		}

		//�ړ���
		float move_x = x;
		float move_y = y;
		moveinfo[current].jumpflg = 1;

		//x���W���ڕW�ƕs��v
		if (x != target_x)
		{
			//�ڕW�̕����傫���i�ڕW�͉E�����j
			if (x < target_x)
			{
				move_x += speed;      //�E�ړ��i���̒l�j


				//�ڕW�𒴂����ꍇ
				if (x <= target_x && target_x <= move_x)
				{
					move_x = target_x;     //�ڕW���W�ŌŒ�
				}
			}
			else
			{
				move_x -= speed; //���ړ��i���̒l�j


				//�ڕW�𒴂����ꍇ
				if (move_x <= target_x && target_x <= x)
				{
					move_x = target_x;     //�ڕW���W�ŌŒ�
				}
			}
		}

		////y���W���ڕW�ƕs��v
		//if (y != target_y)
		//{
		//	//�ڕW�̕����傫���i�ڕW�͉E�����j
		//	if (y < target_y)
		//	{
		//		move_y += speed;      //�E�ړ��i���̒l�j


		//		//�ڕW�𒴂����ꍇ
		//		if (y <= target_y && target_y <= move_y)
		//		{
		//			move_y = target_y;     //�ڕW���W�ŌŒ�
		//		}
		//	}
		//	else
		//	{
		//		move_y -= speed; //���ړ��i���̒l�j


		//		//�ڕW�𒴂����ꍇ
		//		if (move_y <= target_y && target_y <= y)
		//		{
		//			move_y = target_y;     //�ڕW���W�ŌŒ�
		//		}
		//	}
		//}
		//�ړ��𔽉f
		x = move_x;
		y = move_y;

		if (old_x == x)
		{
			target_x = GetRand(1170) + 70;

		}




	}

	//HP��0�ȉ���������HP��0����
	if (hp <= 0)hp = 0;


	//if (x + (w / 2) == (1280 - 20))
	//{
	//	dir = -1;
	//}
	//else if (x - (w / 2) == (20))
	//{
	//	dir = 1;
	//}

	//x += dir * speed;

	///********************   �W�����v�֌W   ********************/

	y_add = (y - old_y) + g_add;  //����̗���������ݒ�

//�������x�̐���
	if (y_add > static_cast<float>(MAX_LENGTH)) y_add = static_cast<float>(MAX_LENGTH);

	old_y = y;              //1�t���[���O�̂����W
	y += y_add;            //���������������W�ɉ��Z����
	g_add = _GRAVITY;     //�d�͉����x������������


	//�z��0�`2�Ԗڂ̉摜�̃��[�v
	if (++Eframe_count_anim % 40 == 0) {

		Ecurrentindex_st03++;
		if (Ecurrentindex_st03 >= 3)Ecurrentindex_st03 = 0;
		Eframe_count_anim = 0;
	}

	//�O��̂�
	old_x = x;

	//HP��40%�ȉ�Animcount��8��菬�������A�j���[�V��������
	if (hp <= 40 && st3_animcount < 8) {

		++st3_animtimer;
		if (st3_animtimer % 8 == 0) {

			st3_animcount++;
			st3_animtimer = 0;
		}

	}


}
/********************   ���ړ�   ********************/

//if (land_flg == true && GetRand(30) == 3)    //GetRand(30) == 3�@�̂Ƃ��낪�W�����v�̏���
//{
//	enemy_x = -21.5f;    //�d�͉����x���}�C�i�X�l�Ɂ@�@������قǃW�����v�̓A�b�v


//	land_flg = false;  //�n�ʂɂ��Ă��Ȃ�

//}

//old_x = (x - old_x) + enemy_x;  //����̗���������ݒ�

////�������x�̐���
//if (enemy_x > static_cast<float>(MAX_LENGTH)) enemy_x = static_cast<float>(MAX_LENGTH);

//old_x = x;                    //1�t���[���O��x���W
//x += enemy_x;                   //����������x���W�ɉ��Z����
//enemy_x = _GRAVITY;              //�d�͉����x������������

/**********************************************************/

//�`��
void Enemy_03::Draw() const

{
	////////////////////////
	///HP��86�ȏ�̎�
	///////////////////////

	if (hp >= 86) {

		
		//�G�l�~�[��~��
		if (moveinfo[current].enemywaitTime > 0) {


			//�K�[�h���̉摜�`��							
			DrawRotaGraphF(x, y, 1, 0, enemyimage[5]/*[1]*/, TRUE, dir == -1 ? 0 : 1);


		}

		//�W�����v��
		else if (moveinfo[current].jumpflg == 0 && moveinfo[current].moveflg == 0 && moveinfo[current].enemywaitTime < 200) {

			//�W�����v���̉摜�`��							
			DrawRotaGraphF(x, y, 1, 0, enemyimage[4]/*[2]*/, TRUE, dir == -1 ? 0 : 1);

		}
		//��������Ȃ��Ƃ�
		//�����Ă���Ƃ�
		else {

			//�G�l�~�[�̍\���̂ƈ�v�����Ƃ���     �G�l�~�[�����܂��͉E�ɓ���
			if (enemy_state == ENEMY_STATE::LEFTMOVE || enemy_state == ENEMY_STATE::RIGHTMOVE && moveinfo[current].enemywaitTime < 200) {

				//�U�����̉摜�`��								//������ς���
				DrawRotaGraphF(x, y, 1, 0, enemyimage[Ecurrentindex_st03]/*[0]*/, TRUE, dir == -1 ? 0 : 1);
			}


		}

	}

	//////////////////////
	//HP85�ȉ���70�ȏ�̂Ƃ�
	/////////////////////
	else if (hp <= 85 && hp >= 71) {

		
		if (moveinfo[current].enemywaitTime > 0) {

			DrawRotaGraphF(x, y, 1, 0, enemyimage1[5]/*[1]*/, TRUE, dir == -1 ? 0 : 1);

		}
		else if (moveinfo[current].jumpflg == 0 && moveinfo[current].moveflg == 0 && moveinfo[current].enemywaitTime < 200) {



			//�W�����v���̉摜�`��							
			DrawRotaGraphF(x, y, 1, 0, enemyimage1[4]/*[2]*/, TRUE, dir == -1 ? 0 : 1);

		}

		else {

			//�G�l�~�[�̍\���̂ƈ�v�����Ƃ��ɃG�l�~�[�����܂��͉E�ɓ���
			if ((enemy_state == ENEMY_STATE::LEFTMOVE || enemy_state == ENEMY_STATE::RIGHTMOVE && moveinfo[current].enemywaitTime < 200)) {
				//�U�����̉摜�`��								//������ς���
				DrawRotaGraphF(x, y, 1, 0, enemyimage1[Ecurrentindex_st03]/*[0]*/, TRUE, dir == -1 ? 0 : 1);
			}


		}



	}
	////////////////////////
	//HP70�ȉ��� 55�ȏ�̂Ƃ�
	////////////////////////
	else if (hp <= 70 && hp >= 56) {
		
		if (moveinfo[current].enemywaitTime > 0) {

			DrawRotaGraphF(x, y, 1, 0, enemyimage2[5]/*[1]*/, TRUE, dir == -1 ? 0 : 1);

		}
		else if (moveinfo[current].jumpflg == 0 && moveinfo[current].moveflg == 0 && moveinfo[current].enemywaitTime < 200) {

			//�W�����v���̉摜�`��							
			DrawRotaGraphF(x, y, 1, 0, enemyimage2[4]/*[2]*/, TRUE, dir == -1 ? 0 : 1);

		}
		else {

			//�G�l�~�[�̍\���̂ƈ�v�����Ƃ��ɃG�l�~�[�����܂��͉E�ɓ���
			if ((enemy_state == ENEMY_STATE::LEFTMOVE || enemy_state == ENEMY_STATE::RIGHTMOVE && moveinfo[current].enemywaitTime < 200)) {
				//�U�����̉摜�`��								//������ς���
				DrawRotaGraphF(x, y, 1, 0, enemyimage2[Ecurrentindex_st03]/*[0]*/, TRUE, dir == -1 ? 0 : 1);
			}
		}

	}

	//////////////////////////
	//HP55�ȉ���41�ȏ�̂Ƃ�
	//////////////////////////
	else if(hp <= 55 && hp >= 41){
		
		if ( moveinfo[current].enemywaitTime > 0) {


			DrawRotaGraphF(x, y, 1, 0, enemyimage3[5]/*[1]*/, TRUE, dir == -1 ? 0 : 1);

		}
		else if (moveinfo[current].jumpflg == 0 && moveinfo[current].moveflg == 0 && moveinfo[current].enemywaitTime < 200) {

			//�W�����v���̉摜�`��							
			DrawRotaGraphF(x, y, 1, 0, enemyimage3[4]/*[2]*/, TRUE, dir == -1 ? 0 : 1);

		}
		else {

			//�G�l�~�[�̍\���̂ƈ�v�����Ƃ��ɃG�l�~�[�����܂��͉E�ɓ���
			if ((enemy_state == ENEMY_STATE::LEFTMOVE || enemy_state == ENEMY_STATE::RIGHTMOVE && moveinfo[current].enemywaitTime < 200)) {
				//�U�����̉摜�`��								//������ς���
				DrawRotaGraphF(x, y, 1, 0, enemyimage3[Ecurrentindex_st03]/*[0]*/, TRUE, dir == -1 ? 0 : 1);
			}


		}
	}

	//////////////////////////
	//HP40�ȉ��̂Ƃ�
	////////////////////////////
	else {
		
			//�G�l�~�[�̍\���̂ƈ�v�����Ƃ��ɃG�l�~�[�����܂��͉E�ɓ���
		if ((hp <= 40 /*&& hp >= 39*/ && enemy_state == ENEMY_STATE::LEFTMOVE || enemy_state == ENEMY_STATE::RIGHTMOVE && moveinfo[current].enemywaitTime < 200)) {
			//�U�����̉摜�`��								//������ς���
			
			DrawRotaGraphF(x, y, 1, 0, enemyimage4[Ecurrentindex_st03]/*[0]*/, TRUE, dir == -1 ? 0 : 1);
			////////////
			//�G�t�F�N�g
			////////////
			if (st3_animcount < 8) {

				SetDrawBlendMode(DX_BLENDMODE_ADD,155);
				DrawRotaGraphF(x, y, 1, 0, SheeldBreakAnim[st3_animcount],TRUE);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			}
		}

	}

	
	

	//����񌂕`��
	Draw_Jangeki();


	//�e�X�g                                                      //�ԐF
	if (hp <= 85 && moveinfo[current].enemywaitTime > 0) DrawFormatString((int)(x - 35), (int)(y - 50), GetColor(0, 0, 255), "�h��DOWN��", moveinfo[current].enemywaitTime);

	if (hp <= 40) DrawFormatString((int)(x - 50), (int)(y - 70), GetColor(255, 0, 0), " �U��UP��", hp);

	if (hp <= 0)DrawString((int)(x - 100), (int)(y - 120), "death!", 0xff0000);

}

//����񌂐����E�X�V
void Enemy_03::Update_Jangeki()
{
	int jan_count;

	//����񌂔z����ЂƂ���
	for (jan_count = 0; jan_count < JANGEKI_MAX; jan_count++)
	{
		//�z��� jan_count �Ԗڂ�nullptr�i��v�f�j�Ȃ炻��ȏ㏈�����Ȃ�
		if (obj_jangeki[jan_count] == nullptr) break;

		obj_jangeki[jan_count]->Update();

		//�v���C���[�̍��W���Z�b�g����
		obj_jangeki[jan_count]->SetTargetLocation(player_x, player_y);

		//��ʊO�ō폜����
		if (obj_jangeki[jan_count]->CheckScreenOut() == true)
		{
			DeleteJangeki(jan_count);
			jan_count--;
		}
	}

	/*********************** ���� ���ˁE���� ���� ***********************/
	frame_count++;

	//�z��̋�v�f
	if (jan_count < JANGEKI_MAX && obj_jangeki[jan_count] == nullptr)
	{
		float radius = 35.5f;   //���a //35.5f
		float speed = 4.5f /** dir*/;     //�X�s�[�h//3.0

		//�����_���ȑ����𐶐�
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));//2 //��ɑ������̃W���������J��o��


		//�v���C���[�����ւ̃W����������

		if (hp >= 41) {
			if (frame_count % 100 == 0) obj_jangeki[jan_count] = new Jangeki_Coming(x, y, radius, speed, type, player_x, player_y);
		}
		////�ʏ�e����
		//if (frame_count % 120 == 0) obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, speed, type);

		//�U��UP���̃W������
		else if (hp <= 40) {

			float radius = 50.0f;
			float speed = 4.5f;

			if (frame_count % 120 == 0) obj_jangeki[jan_count] = new Jangeki_Coming(x, y, radius, speed, type, player_x, player_y);

		}


	}
}

void Enemy_03::Move_Pattern() {

	//�ړ������
	float move_x = x;
	float move_y = y;

	//�ڎw���Ă�����W��X���W����v�����Ƃ�
	if (x == moveinfo[current].location_x) {

		current = moveinfo[current].next_index; //���̃p�^�[��

		//speed��up
		speed = 2.8f;
	}


	//x���W���ڎw���Ă�����W�ƕs��v
	if (x != moveinfo[current].location_x) {


		//�W�����v���Ă���Ƃ�
		if (moveinfo[current].jumpflg == 0) {

			//speed��up,����ɏ悹�邽�߂̒���
			speed = 4.3f;

		}


		//�ڎw���Ă���x���W�̉E�����傫��
		if (x < moveinfo[current].location_x) {

			move_x += speed; //�E�ړ��Ƀv���X����

			enemy_state = ENEMY_STATE::RIGHTMOVE;

			//�ڎw���Ă������W�𒴂����Ƃ�
			if (x <= moveinfo[current].location_x && moveinfo[current].location_x <= move_x)
			{

				move_x = moveinfo[current].location_x; //�ڎw���Ă������W�ŌŒ�

			}

		}
		else
		{
			move_x -= speed; //���ړ��Ƀ}�C�i�X����

			enemy_state = ENEMY_STATE::LEFTMOVE;

			//�ڎw���Ă������W�𒴂����Ƃ�
			if (move_x <= moveinfo[current].location_x && moveinfo[current].location_x <= x)
			{

				move_x = moveinfo[current].location_x; //�ڎw���Ă������W�ŌŒ�

			}


		}


	}


	//�ړ��𔽉f����
	x = move_x;
	y = move_y;

}

//enemywaitTime�p��
int Enemy_03::GetWaitTime()const {

	return moveinfo[current].enemywaitTime;
}



//�G�l�~�[�̍��W���p��
void Enemy_03::ChangeDir(float enemy_x)
{
	if (enemy_x < x) dir = -1;
	else dir = 1;
}

