#include"EnemyBase.h"

class MobEnemy_05 :EnemyBase
{
public:
	MobEnemy_05(float x, float y, Jan_Type type);		//�R���X�g���N�^
	~MobEnemy_05();										//�f�X�g���N�^
	void Update() override;          //�X�V
	void Draw() const override;      //�`��

	void Update_Jangeki() override;  //����񌂐����E�X�V

private:
	int frame_count = 0;       //����񌂔��˗p
};