#include "CharaBase.h"
#include<math.h>

//コンストラクタ    ｘ,ｙ座標, 幅,高さ　を設定
CharaBase::CharaBase(float x, float y, float w, float h) : x(x), y(y), w(w), h(h)
{
	speed = 0.0f;
	hp = 10;
	dir = 0;
	obj_jangeki = nullptr;
}

//デストラクタ
CharaBase::~CharaBase()
{

}


//じゃん撃生成・更新    使っても使わなくても
void CharaBase::Update_Jangeki()
{
	//使うときは派生クラス内で定義します
}

//じゃん撃描画
void CharaBase::Draw_Jangeki() const
{
	for (int i = 0; i < JANGEKI_MAX; i++)
	{
		//要素がなければ処理しない
		if (obj_jangeki[i] == nullptr) break;
		obj_jangeki[i]->Draw();                //配列に要素がある時
	}
}


//じゃん撃用意   じゃん撃を使用するときにコンストラクタで呼び出す
void CharaBase::Init_Jangeki()
{
	//じゃん撃＊JANGEKI_MAX個分 のメモリを確保
	obj_jangeki = new Jangeki_Base * [JANGEKI_MAX];

	for (int i = 0; i < JANGEKI_MAX; i++)
	{
		obj_jangeki[i] = nullptr;           //初期化
	}
}


//じゃん撃を削除
void CharaBase::DeleteJangeki(int jan_count)
{
	delete obj_jangeki[jan_count];       //削除
	obj_jangeki[jan_count] = nullptr;    //初期化

	//詰める
	for (int i = jan_count; i < (JANGEKI_MAX - 1); i++)
	{
		//次の要素が nullptr ならそれ以上は処理しない
		if (obj_jangeki[i + 1] == nullptr) break;

		obj_jangeki[i] = obj_jangeki[i + 1];
		obj_jangeki[i + 1] = nullptr;
	}
}


/*******************  当たり判定  *******************/

//Floor(床)との当たり処理
void CharaBase::Hit_Floor(const Floor* floor)
{
	int box_x = floor->GetX();   //floorのｘ座標
	int box_y = floor->GetY();   //floorのｙ座標
	int box_w = floor->GetW();   //floorの幅
	int box_h = floor->GetH();   //floorの高さ

	//矩形と矩形の当たり判定
	if ( CheckHitBox_Box(box_x, box_y, box_w, box_h) == true )
	{

		//キャラクター側　（キャラクターの座標は中心基準）
		int cX_Min = static_cast<int>(x - (w / 2));     //最小ｘ（左）
		int cX_Max = static_cast<int>(x + (w / 2)) - 1; //最大ｘ（右）
		int cY_Min = static_cast<int>(y - (h / 2));     //最小ｙ（上）
		int cY_Max = static_cast<int>(y + (h / 2)) - 1; //最大ｙ（下）

		//floor側 　　　　（floorの座標は左上基準）
		int fX_Min = box_x;                //最小ｘ（左）
		int fX_Max = box_x + box_w;        //最大ｘ（右）
		int fY_Min = box_y;                //最小ｙ（上）
		int fY_Max = box_y + box_h;        //最大ｙ（下）


		//キャラクター下方向    床にめりこまない
		if (cY_Max - fY_Min < MAX_LENGTH)  //キャラクターの下端とfloorの上端を比較
		{
			y = static_cast<float>(fY_Min) - (h / 2);
			land_flg = true;   //接地
		}
		
		//キャラクター右方向
		if (cY_Max - fX_Min < MAX_LENGTH)
		{
			x = static_cast<float>(fX_Min) - (w / 2);
		}

		//キャラクター左方向
		if (fX_Max - cY_Min < MAX_LENGTH)
		{
			x = static_cast<float>(fX_Max) + (w / 2);
		}

		
	}
}

//キャラクター同士の当たり判定  Hit:true
bool CharaBase::Hit_Character(const CharaBase* character)
{
	//（int型に変換）
	int c_w = static_cast<int> ( character->GetW() );   //幅　
	int c_h = static_cast<int> ( character->GetH() );   //高さ
	int c_x = static_cast<int> ( character->GetX() ) - ( c_w / 2 );  //ｘ座標を左上基準に
	int c_y = static_cast<int> ( character->GetY() ) - ( c_h / 2 );  //ｙ座標を左上基準に

	//矩形同士の当たり判定
	if (CheckHitBox_Box(c_x, c_y, c_w, c_h) == true) return true;  //当たり

	return false;   //当たりなし
}

//じゃん撃とキャラクターの当たり判定
bool CharaBase::Hit_Jangeki(const Jangeki_Base* jangeki)
{
	float j_x = jangeki->GetX();    //じゃん撃のｘ  取得
	float j_y = jangeki->GetY();    //じゃん撃のｙ　取得
	float j_r = jangeki->GetR();    //じゃん撃の半径取得

	//キャラクター（矩形）とじゃん撃（円形）の当たり判定
	if (CheckHitBox_Circle(j_x, j_y, j_r) == true)  return true; //あたり

	return false;   //当たりなし
}



//矩形と矩形の当たり判定
bool CharaBase::CheckHitBox_Box(int box_x, int box_y, int box_w, int box_h)
{
	//キャラクター側　（キャラクターの座標は中心基準）
	int pX_Min = static_cast<int>(x - (w / 2));     //最小ｘ（左）
	int pX_Max = static_cast<int>(x + (w / 2)) - 1; //最大ｘ（右）
	int pY_Min = static_cast<int>(y - (h / 2));     //最小ｙ（上）
	int pY_Max = static_cast<int>(y + (h / 2)) - 1; //最大ｙ（下）

	//当たり判定をとる対象　の4座標
	int tX_Min = box_x;            //最小ｘ（左）
	int tX_Max = box_x + box_w;    //最大ｘ（右）
	int tY_Min = box_y;            //最小ｙ（上）
	int tY_Max = box_y + box_h;    //最大ｙ（下）

	//矩形同士の判定
	if (pX_Max < tX_Min) {
	}
	else if (tX_Max < pX_Min) {
	}
	else if (pY_Max < tY_Min) {
	}
	else if (tY_Max < pY_Min) {
	}
	else
	{
		return true;  //当たり
	}

	return false;
}

//矩形と円形の当たり判定
bool CharaBase::CheckHitBox_Circle(float c_x, float c_y, float c_r)
{
	//Enemyの矩形
	float n_lx = x - (w / 2);       //左端(Left
	float n_rx = x + (w / 2) - 1;   //右端(Right
	float n_ty = y - (h / 2);       //上端(Top
	float n_by = y + (h / 2) - 1;   //下端(Bottom

	//矩形の上・下の範囲
	if (c_x > n_lx && c_x < n_rx && c_y > n_ty - c_r && c_y < n_by + c_r) return true;

	//矩形の左・右の範囲
	if (c_x > n_lx - c_r && c_x < n_rx + c_r && c_y > n_ty && c_y < n_by) return true;

	//"角丸"　矩形の各頂点を中心とした円
	float cir_Lx = powf((n_lx - c_x), 2.0f);       //左x    （頂点 と 円の中心点 の差）の2乗
	float cir_Rx = powf((n_rx - c_x), 2.0f);       //右x                  〃
	float cir_Ty = powf((n_ty - c_y), 2.0f);       //上y                  〃
	float cir_By = powf((n_by - c_y), 2.0f);       //下y                  〃
	float rad_sq = powf(c_r, 2.0f);                //半径の2乗

	if ((cir_Lx + cir_Ty) < rad_sq) return true;   //左上
	if ((cir_Rx + cir_Ty) < rad_sq) return true;   //右上
	if ((cir_Lx + cir_By) < rad_sq) return true;   //左下
	if ((cir_Rx + cir_By) < rad_sq) return true;   //右下

	//それ以外は当たりナシ
	return false;
}

/****************************************************/

//ダメージを受ける　（hp -= damage）
void CharaBase::ReceiveDamage(int damage)
{
	//ダメージが0以上
	if (damage > 0)
	{
		hp -= damage;
	}

	return;
}


//ｘ座標変更
void CharaBase::SetX(const float x)
{
	if (x > 0)
	{
		this->x = x;
	}
}
//ｙ座標変更
void CharaBase::SetY(const float y)
{
	if (y > 0)
	{
		this->y = y;
	}
}