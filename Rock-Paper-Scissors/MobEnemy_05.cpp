#include "MobEnemy_05.h"
#include "DxLib.h"

MobEnemy_05::MobEnemy_05(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
{

}
MobEnemy_05::~MobEnemy_05()
{

}
void MobEnemy_05::Update()
{

}
void MobEnemy_05::Draw() const
{

}

void MobEnemy_05::Update_Jangeki()
{
	int jan_count;

	//����񌂔z����ЂƂ���
	for (jan_count = 0; jan_count < JANGEKI_MAX; jan_count++)
	{
		//�z��� jan_count �Ԗڂ�nullptr�i��v�f�j�Ȃ炻��ȏ㏈�����Ȃ�
		if (obj_jangeki[jan_count] == nullptr) break;

		obj_jangeki[jan_count]->Update();

		//�z�[�~���O����񌂂ł���΃v���C���[�̍��W���Z�b�g����
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
		float radius = 35.5f;   //���a
		float speed = 5.0f;     //�X�s�[�h

		//�����_���ȑ����𐶐�
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));


		//����
		//if (frame_count % 120 == 0) obj_jangeki[jan_count] = new Jangeki_Spin(x, y, radius, speed, type,player_x,player_y);

	}
}