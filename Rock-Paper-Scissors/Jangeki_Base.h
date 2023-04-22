#pragma once

//����񂯂�^�C�v
enum class Jan_Type
{
	ROCK,        //���b�N�@�@�@�i�O�[�j
	SCISSORS,    //�V�U�[�Y�@�@�i�`���L�j
	PAPER,       //�y�[�p�[�@�@�i�p�[�j

	NONE,        //������
};

//����񂯂�̌���
enum class Jan_Result
{
	LOSE,            //����
	WIN,             //����
	ONEMORE,         //������
	_ERROR = 99      //�G���[
};

//�G�t�F�N�g�̎��
enum class EFFECT_TYPE
{
	WIN,         //����
	OFFSET,      //���E

	_NO_EFFECT,  //�G�t�F�N�g�Ȃ�
};

//�����
class Jangeki_Base
{
public:
	//�R���X�g���N�^  ���@�@�@�@���@�@�@���a�@�@�X�s�[�h�@�@�@�^�C�v      ���˃^�C�v��
	Jangeki_Base(float x, float y, float r, float speed, Jan_Type type, bool ref = false);

	//�R���X�g���N�^�i�p�x����j
	Jangeki_Base(float x, float y, float r, float speed, double angle, Jan_Type type, bool ref = false);

	//�f�X�g���N�^
	~Jangeki_Base();

	virtual void Update();                    //�X�V
	virtual void Draw() const;                //�`��
	bool CheckScreenOut();                    //��ʊO�ɂ��邩�@true:��ʊO�@false:��ʓ�

	//�G�t�F�N�g�𓮍삳����i�S�Ă̔h������񌂓��EUpdate�ŌĂԁj�����F�t���[�����̊g���
	void Update_Effect(double fp_rate = 5.0);

	/* 
	   *********  �����̂���񌂑����Ǝ����̑������r  *********  
	   �E�����̑������s���i��@�����F�O�[�@�����F�p�[�j�@�@return 0
	   �E�����̑������L���i��@�����F�O�[�@�����F�`���L�j�@return 1
	   �E�@�@�@�������@�@�i��@�����F�O�[�@�����F�O�[�j�@�@return 2
	*/
	int CheckAdvantage(const Jangeki_Base* jangeki);

	float GetX() const { return x; }           //�����W�擾
	float GetY() const { return y; }           //�����W�擾
	float GetR() const { return r; }           //���a�擾
	float GetSpeed() const { return speed; }   //�X�s�[�h�擾
	Jan_Type GetType() const { return type; }  //�����擾

	//�^�C�v�擾�i�O�[,�`���L,�p�[�j
	Jan_Type GeteEnemyType() const { return type; }

	//�ǐՑΏۂ̍��W���Z�b�g�@�v���C���[�̍��W����肽���Ƃ��Ɏg���܂�
	void SetTargetLocation(const float target_x, const float target_y);

	//����񌂓��m�̓����蔻��
	bool Hit_Jangeki(const Jangeki_Base* jangeki);

	//�~�`�̓����蔻��
	bool Hit_CircleCircle(float c_x, float c_y, float c_r) const;

	//�������ׂ��G�t�F�N�g���擾����
	Jan_Result GetEffectType() const;

	//

protected:

	float x;            //��
	float y;            //��
	float r;            //���a
	float speed;        //�X�s�[�h
	float speed_y = 0;  //�����W�X�s�[�h

	int image[3];       //����񌂉摜
	int image_smoke[4]; //�X���[�N�ȃG�t�F�N�g
	short smoke_index;  //�G�t�F�N�g�A�j���[�V�����p

	double rate_pct;    //�g�嗦
	double rate_turn;   //��]��

	//���ː�p
	int reflection_image[3];
	bool refrection;    //true�̎��A���g�͔��˂ł���

	Jan_Type type;      //�^�C�v�@�O�[or�`���Lor�p�[


	float target_x = 0; //�Ώۂ̂����W
	float target_y = 0; //�Ώۂ̂����W

	//�������ׂ��G�t�F�N�g�̎��
	Jan_Result effect_type; 


	


	EFFECT_TYPE player_effect;   //player������񌂂���������G�t�F�N�g
	EFFECT_TYPE enemy_effect;    //enemy������񌂂���������G�t�F�N�g
};
