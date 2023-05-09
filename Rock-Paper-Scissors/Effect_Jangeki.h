#pragma once
#include"Jangeki_Base.h"
#include"CharaBase.h"

/** ����񌂂ł͂Ȃ� **/

//�G�t�F�N�g�𔭐�������(����񌂓��m�̏Փ�)
class Effect_Jangeki
{
public:
	Effect_Jangeki(float play_x, float play_y, Jan_Type type = Jan_Type::PAPER, _CHAR_TYPE character = _CHAR_TYPE::PLAYER);
	~Effect_Jangeki();

	void Update();
	void Draw() const;

	bool Check_PlayEnd();          //�Đ��I�� true

	//Character�̍��W
	void SetCharacterLocation(const float& x = 0.f, const float& y = 0.f);

	_CHAR_TYPE GetCharacterType() const { return character; }

private:
	float play_x;            //�G�t�F�N�g�Đ����W��
	float play_y;            //�G�t�F�N�g�Đ����W��

	unsigned int frame_count;      //�t���[���J�E���^
	unsigned int index_effect;     //�z�񑀍�
	unsigned int index_max;        //�摜�ő吔
	
	int* image_effect;             //�G�t�F�N�g�摜
	int image_sub;                 //�T�u�G�t�F�N�g

	const _CHAR_TYPE character;

	bool finish_effect;            //�G�t�F�N�g����
};
