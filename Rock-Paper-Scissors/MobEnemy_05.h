#include"EnemyBase.h"
#include"Effect_Jangeki.h"
#include"Player.h"

class MobEnemy_05 : public EnemyBase
{
public:
	MobEnemy_05(float x, float y, Jan_Type type);		//�R���X�g���N�^
	~MobEnemy_05();										//�f�X�g���N�^
	void Update() override;          //�X�V
	void Draw() const override;      //�`��

	void Update_Jangeki() override;  //����񌂐����E�X�V

	void Janken_lose();

	void Janken_win();

	void Jan_360degrees();

	//�G�t�F�N�g����
	void CreateEffect(_CHAR_TYPE character, Jan_Type type);
	//05��MobEnemy��p
	void Effect_MobEnemy(const Player* player);

private:
	int frame_count = 0;       //����񌂔��˗p

	int Mobenemy_image;			//�摜�p

	int jan_count;

	bool Spflg = true;  //����s���t���O

	int SPcount = 0;

	bool Jan_loseflg = false;

	int losetimer = 0;

	Effect_Jangeki** obj_effect;              //�G�t�F�N�g�i�����hit�j
	int effect_count;
};