#include"EnemyBase.h"

class MobEnemy_05 :EnemyBase
{
public:
	MobEnemy_05(float x, float y, Jan_Type type);		//コンストラクタ
	~MobEnemy_05();										//デストラクタ
	void Update() override;          //更新
	void Draw() const override;      //描画

	void Update_Jangeki() override;  //じゃん撃生成・更新

private:
	int frame_count = 0;       //じゃん撃発射用
};