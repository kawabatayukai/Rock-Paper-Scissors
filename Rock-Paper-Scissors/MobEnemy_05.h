#include"EnemyBase.h"
#include"Effect_Jangeki.h"
#include"Player.h"

class MobEnemy_05 : public EnemyBase
{
public:
	MobEnemy_05(float x, float y, Jan_Type type);		//コンストラクタ
	~MobEnemy_05();										//デストラクタ
	void Update() override;          //更新
	void Draw() const override;      //描画

	void Update_Jangeki() override;  //じゃん撃生成・更新

	void Janken_lose();

	void Janken_win();

	void Jan_360degrees();

	//エフェクト発生
	void CreateEffect(_CHAR_TYPE character, Jan_Type type);
	//05のMobEnemy専用
	void Effect_MobEnemy(const Player* player);

private:
	int frame_count = 0;       //じゃん撃発射用

	int Mobenemy_image;			//画像用

	int jan_count;

	bool Spflg = true;  //特殊行動フラグ

	int SPcount = 0;

	bool Jan_loseflg = false;

	int losetimer = 0;

	Effect_Jangeki** obj_effect;              //エフェクト（じゃん撃hit）
	int effect_count;
};