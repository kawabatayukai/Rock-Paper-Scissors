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

private:
	const float play_x;            //�G�t�F�N�g�Đ����W��
	const float play_y;            //�G�t�F�N�g�Đ����W��

	unsigned short frame_count;    //�t���[���J�E���g
	int image_effect[10];          //�摜
	int index_image;               //�摜No
};
