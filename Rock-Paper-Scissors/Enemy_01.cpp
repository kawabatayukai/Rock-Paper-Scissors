#include"Enemy_01.h"
#include"DxLib.h"
#include<math.h>
#include"Jangeki_Base.h"
#include"Jangeki_Coming.h"

//定数　
namespace _CONSTANTS_01
{
	// "足場"は画面右から順に 1,2,3,....と番号をつける
	const float FLOOR_NO_01_X = 1150.0f;   //足場１ (中心ｘ座標)
	const float FLOOR_NO_01_Y = 500.0f;    //足場１ (中心ｙ座標)

	const float FLOOR_NO_02_X = 950.0f;    //足場２ (中心ｘ座標)
	const float FLOOR_NO_02_Y = 290.0f;    //足場２ (中心ｙ座標)

	const float FLOOR_NO_03_X = 560.0f;    //足場３ (中心ｘ座標)
	const float FLOOR_NO_03_Y = 140.0f;    //足場３ (中心ｙ座標)

	const float FLOOR_NO_03_L = 350.0f;    //足場３（左ｘ座標）
	const float FLOOR_NO_03_R = 770.0f;    //足場３（右ｘ座標）

	const float FLOOR_NO_04_X = 110.0f;    //足場４ (中心ｘ座標)
	const float FLOOR_NO_04_Y = 290.0f;    //足場４ (中心ｙ座標)

	const float FLOOR_NO_05_X = 310.0f;    //足場５ (中心ｘ座標)
	const float FLOOR_NO_05_Y = 500.0f;    //足場５ (中心ｙ座標)

	//const float FLOOR_NO_03 = 790.0f;   //足場３ (中心ｘ座標)
	//const float FLOOR_NO_04 = 1185.0f;  //足場４ (中心ｘ座標)

}


//コンストラクタ　   基底クラスのコンストラクタを呼ぶ　　　　 ｘ　ｙ　幅　　　高さ    属性
Enemy_01::Enemy_01(float x, float y, Jan_Type type) : EnemyBase(x, y, 100.0f, 100.0f, type)
, Now_Action(ACT_TYPE::NOT_ACT), jan_count(0), current_action(0)
{
	speed = 4.0f;
	dir = 1;
	hp = 100;

	image = LoadGraph("images/tyokitest.png");

	Init_Jangeki();       //じゃん撃を用意
}

//デストラクタ
Enemy_01::~Enemy_01()
{

}


//更新
void Enemy_01::Update()
{
	//じゃん撃更新・生成
	Update_Jangeki();

	Move_Controller();

	/********************   ジャンプ関係   ********************/

	//if (land_flg == true && GetRand(30) == 3)    //GetRand(30) == 3　のところがジャンプの条件
	//{
	//	g_add = -21.5f;    //重力加速度をマイナス値に　　下げるほどジャンプ力アップ
	//	land_flg = false;  //地面についていない
	//}

	y_add = (y - old_y) + g_add;  //今回の落下距離を設定

	//落下速度の制限
	if (y_add > static_cast<float>(MAX_LENGTH)) y_add = static_cast<float>(MAX_LENGTH);

	old_y = y;                    //1フレーム前のｙ座標
	y += y_add;                   //落下距離をｙ座標に加算する
	g_add = _GRAVITY;              //重力加速度を初期化する

	/**********************************************************/

}

//描画
void Enemy_01::Draw() const
{
	//中心から描画
	DrawRotaGraphF(x, y, 1, 0, image, TRUE);

	//じゃん撃描画
	Draw_Jangeki();


	//DrawFormatString(50, 100, 0xff00ff, "Current : %d", current_action);

}

//じゃん撃生成・更新
void Enemy_01::Update_Jangeki()
{
	//じゃん撃配列をひとつずつ
	for (jan_count = 0; jan_count < JANGEKI_MAX; jan_count++)
	{
		//配列の jan_count 番目がnullptr（空要素）ならそれ以上処理しない
		if (obj_jangeki[jan_count] == nullptr) break;

		obj_jangeki[jan_count]->Update();

		//画面外で削除する
		if (obj_jangeki[jan_count]->CheckScreenOut() == true)
		{
			DeleteJangeki(jan_count);
			jan_count--;
		}
	}

	/*********************** ↓↓ 発射・生成 ↓↓ ***********************/

	////配列の空要素
	//if (jan_count < JANGEKI_MAX && obj_jangeki[jan_count] == nullptr)
	//{
	//	float radius = 35.5f;   //半径
	//	float speed = -2.0f;     //スピード

	//	//ランダムな属性を生成
	//	Jan_Type type = static_cast<Jan_Type>(GetRand(2));


	//	//生成
	//	if (frame_count % 120 == 0) obj_jangeki[jan_count] = new Jangeki_Base(x, y, radius, speed, type);
	//}
}


//ジャンプ（ジャンプ力）
void Enemy_01::Jump_Enemy(float g_add)
{
	//マイナス値でなければ処理しない
	if (g_add > 0) return;

	//接地していれば
	if (land_flg == true)
	{
		this->g_add = g_add;    //重力加速度をマイナス値に　
		land_flg = false;       //地面についていない
	}
}

//行動制御
void Enemy_01::Move_Controller()
{
	//目標座標
	float target_x = 0;
	float target_y = 0;

	//移動量
	float move_x = x;
	float move_y = y;

	switch (current_action)
	{
	case 0:
		Action01_LR(target_x, target_y);
		break;

	case 1:
		Action02_Jump(target_x, target_y);
		break;

	case 2:
		Action03_Floor_LR(target_x, target_y);
		break;

	case 3:
		Action04_GetOff_Floor_LEFT(target_x, target_y);
		break;

	default:
		target_x = 1280 / 2;
		break;
	}

	//x座標が目標と不一致
	if (x != target_x)
	{
		//目標の方が大きい（目標は右方向）
		if (x < target_x)
		{
			move_x += speed;      //右移動（正の値）

			//目標を超えた場合
			if (x <= target_x && target_x <= move_x)
			{
				move_x = target_x;     //目標座標で固定
			}
		}
		else
		{
			move_x -= speed; //左移動（負の値）

			//目標を超えた場合
			if (move_x <= target_x && target_x <= x)
			{
				move_x = target_x;     //目標座標で固定
			}
		}
	}

	//移動を反映
	x = move_x;
	y = move_y;
}





//左右移動
void Enemy_01::Action01_LR(float& target_x, float& target_y)
{
	// 到達した回数
	static unsigned short count_ari;

	if (count_ari == 0)
	{
		target_x = 500;

		if (x == 500) count_ari = 1;

		Jump_Enemy();
	}

	if (count_ari == 1 && land_flg == true)
	{
		target_x = 980;

		if (x == 980)
		{
			current_action = 1;  //actionの終了（次のアクションへ）
			count_ari = 0;       //初期化
		}
	}
}

//ジャンプで足場を渡る
void Enemy_01::Action02_Jump(float& target_x, float& target_y)
{
	// 到達した回数
	static unsigned short count_ari;

	//ジャンプ地点を目指す
	if (count_ari == 0)
	{
		target_x = 990.0f;   //ジャンプ地点へ

		//到達
		if (x == 990.0f)
		{
			Jump_Enemy();   //ジャンプ
			count_ari = 1;
		}
	}

	//足場1を目指す
	if (count_ari == 1)
	{
		target_x = _CONSTANTS_01::FLOOR_NO_01_X;      //足場１を目指す

		//到達
		if (x == _CONSTANTS_01::FLOOR_NO_01_X && land_flg == true)
		{
			Jump_Enemy();   //ジャンプ
			count_ari = 2;
		}
	}

	//足場2を目指す
	if (count_ari == 2)
	{
		target_x = _CONSTANTS_01::FLOOR_NO_02_X;      //足場２を目指す

		//到達
		if (x == _CONSTANTS_01::FLOOR_NO_02_X && y == (_CONSTANTS_01::FLOOR_NO_02_Y - h / 2))
		{
			Jump_Enemy();        //ジャンプ
			count_ari = 3;
		}
	}

	//足場3を目指す
	if (count_ari == 3)
	{
		target_x = _CONSTANTS_01::FLOOR_NO_03_X;      //足場３を目指す

		//到達
		if (x == _CONSTANTS_01::FLOOR_NO_03_X && y == (_CONSTANTS_01::FLOOR_NO_03_Y - h / 2))
		{
			current_action = 2;  //アクションの終了（次のアクションへ）
			count_ari = 0;       //初期化
		}
	}


}

//足場上を往復する
void Enemy_01::Action03_Floor_LR(float& target_x, float& target_y)
{
	// 到達した回数
	static unsigned short count_ari;

	//最初に左
	if (count_ari == 0 || count_ari == 2)
	{
		target_x = _CONSTANTS_01::FLOOR_NO_03_L;

		if (x == _CONSTANTS_01::FLOOR_NO_03_L)
		{
			//じゃん撃を発射
			Fire_JanTakeAim(player_x, player_y);

			count_ari++;
		}
	}

	//次に右
	if (count_ari == 1 || count_ari == 3)
	{
		target_x = _CONSTANTS_01::FLOOR_NO_03_R;

		if (x == _CONSTANTS_01::FLOOR_NO_03_R)
		{
			//じゃん撃を発射
			Fire_JanTakeAim(player_x, player_y);

			count_ari++;

			if (count_ari == 4)
			{
				current_action = 3;  //アクションの終了（次のアクションへ）
				count_ari = 0;       //初期化
			}
		}
	}
}

//足場を左から降りる
void Enemy_01::Action04_GetOff_Floor_LEFT(float& target_x, float& target_y)
{
	// 到達した回数
	static unsigned short count_ari;

	if (x == 330) Jump_Enemy();

	//足場4を目指す
	if (count_ari == 0)
	{
		target_x = _CONSTANTS_01::FLOOR_NO_04_X;

		if (x == _CONSTANTS_01::FLOOR_NO_04_X)
		{
			count_ari = 1;
		}
	}


	//足場5を目指す
	if (count_ari == 1)
	{
		target_x = _CONSTANTS_01::FLOOR_NO_05_X;

		if (x == _CONSTANTS_01::FLOOR_NO_05_X)
		{
			current_action = 1;  //アクションの終了（"ジャンプで足場を渡る"へ）
			count_ari = 0;       //初期化
		}
	}
}

//プレイヤー目掛けてじゃん撃を発射する
void Enemy_01::Fire_JanTakeAim(const float& player_x, const float& player_y)
{
	//配列の空要素
	if (jan_count < JANGEKI_MAX && obj_jangeki[jan_count] == nullptr)
	{
		float radius = 35.5f;   //半径
		float speed = 2.5f;     //スピード

		//ランダムな属性を生成
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));

		//生成
		obj_jangeki[jan_count] = new Jangeki_Coming(x, y, radius, speed, type, player_x, player_y);
	}
}