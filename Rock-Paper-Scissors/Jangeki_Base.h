#pragma once

//����񂯂�^�C�v
enum class Jan_Type
{
	ROCK,        //���b�N�@�@�@�i�O�[�j
	SCISSORS,    //�V�U�[�Y�@�@�i�`���L�j
	PAPER,       //�y�[�p�[�@�@�i�p�[�j
};

//����񂯂�̌���
enum class Jan_Result
{
	LOSE,            //����
	WIN,             //����
	ONEMORE,         //������
	_ERROR = 99      //�G���[
};

//�����
class Jangeki_Base
{
public:
	//�R���X�g���N�^  ���@�@�@�@���@�@�@���a�@�@�X�s�[�h�@�@�@�^�C�v
	Jangeki_Base(float x, float y, float r, float speed, Jan_Type type);

	//�R���X�g���N�^�i�p�x����j
	Jangeki_Base(float x, float y, float r, float speed, double angle, Jan_Type type);

	//�f�X�g���N�^
	~Jangeki_Base();

	void Update();                    //�X�V
	void Draw() const;                //�`��
	bool CheckScreenOut();            //��ʊO�ɂ��邩�@true:��ʊO�@false:��ʓ�

	/* 
	   *********  �����̂���񌂑����Ǝ����̑������r  *********  
	   �E�����̑������s���i��@�����F�O�[�@�����F�p�[�j�@�@return 0
	   �E�����̑������L���i��@�����F�O�[�@�����F�`���L�j�@return 1
	   �E�@�@�@�������@�@�i��@�����F�O�[�@�����F�O�[�j�@�@return 2
	*/
	int CheckAdvantage(const Jangeki_Base* jangeki);

	float GetX() const { return x; }  //�����W�擾
	float GetY() const { return y; }  //�����W�擾
	float GetR() const { return r; }  //���a�擾
	Jan_Type GetType() const { return type; }  //�����擾

	//�^�C�v�擾�i�O�[,�`���L,�p�[�j
	Jan_Type GeteEnemyType() const { return type; }

	//����񌂓��m�̓����蔻��
	bool Hit_Jangeki(const Jangeki_Base* jangeki);

	//�~�`�̓����蔻��
	bool Hit_CircleCircle(float c_x, float c_y, float c_r) const;

protected:

	float x;     //��
	float y;     //��
	float r;     //���a
	float speed; //�X�s�[�h
	float speed_y = 0; //�����W�X�s�[�h

	int image[3];

	Jan_Type type;   //�^�C�v�@�O�[or�`���Lor�p�[
};
