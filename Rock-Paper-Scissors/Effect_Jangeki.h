#pragma once

/** ����񌂂ł͂Ȃ� **/


//�G�t�F�N�g�𔭐�������(����񌂓��m�̏Փ�)
class Effect_Jangeki
{
public:
	Effect_Jangeki(float play_x, float play_y);
	~Effect_Jangeki();

	void Update();
	void Draw() const;

	bool Check_PlayEnd();          //�Đ��I�� true

private:
	const float play_x;            //�G�t�F�N�g�Đ����W��
	const float play_y;            //�G�t�F�N�g�Đ����W��

	unsigned int frame_count;      //�t���[���J�E���^
	unsigned int index_effect;     //�z�񑀍�
	unsigned int index_max;        //�摜�ő吔
	
	int* image_effect;             //�G�t�F�N�g�摜

	bool finish_effect;            //�G�t�F�N�g����
};
