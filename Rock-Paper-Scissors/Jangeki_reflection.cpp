#include "Jangeki_Reflection.h"
#include<math.h>
//コンストラクタ
Jangeki_Reflection::Jangeki_Reflection(float x, float y, float r, float speed, Jan_Type type)
	:Jangeki_Base(x, y, r, speed, type)    // ←基底クラスのコンストラクタを呼ぶ
{
	obj_reflection = nullptr;
	
}

//デストラクタ
Jangeki_Reflection::~Jangeki_Reflection()
{

}

void Jangeki_Reflection::Update_reflection()  {
	int jan_count_reflection;

	//じゃん撃配列をひとつずつ
	for (jan_count_reflection = 0; jan_count_reflection < JANGEKI_MAX; jan_count_reflection++)
	{
		//配列の jan_count 番目がnullptr（空要素）ならそれ以上処理しない
		if (obj_reflection[jan_count_reflection] == nullptr) break;

		obj_reflection[jan_count_reflection]->Update();

		//画面外で削除する
		if (obj_reflection[jan_count_reflection]->CheckScreenOut() == true)
		{
			Delete_reflectionJangeki(jan_count_reflection);
			jan_count_reflection--;
			
		}
	}

	/*********************** ↓↓ 発射・生成 ↓↓ ***********************/

	//配列の空要素
	if (jan_count_reflection < JANGEKI_MAX && obj_reflection[jan_count_reflection] == nullptr)

	{

		
		float radius = 35.5f;   //半径
		float speed = -3.0f;     //スピード

		//ランダムな属性を生成
		Jan_Type type = static_cast<Jan_Type>(GetRand(2));
		
		/*if (reflectionFlg == true) obj_reflection[jan_count_reflection] = new Jangeki_Base(chara->GetX(), chara->GetY(), radius, speed, type);
		reflectionFlg = false;*/
	}
	
}
//じゃん撃描画
void Jangeki_Reflection::Draw_reflectionJangeki ()const
{
	for (int i = 0; i < JANGEKI_MAX; i++)
	{
		//要素がなければ処理しない
		if (obj_reflection[i] == nullptr) break;
		obj_reflection[i]->Draw();                //配列に要素がある時
	}
}


//じゃん撃用意   じゃん撃を使用するときにコンストラクタで呼び出す
void Jangeki_Reflection::Init_reflectionJangeki()
{
	//じゃん撃＊JANGEKI_MAX個分 のメモリを確保
	obj_reflection = new Jangeki_Base * [JANGEKI_MAX];

	for (int i = 0; i < JANGEKI_MAX; i++)
	{
		obj_reflection[i] = nullptr;           //初期化
	}
}


//じゃん撃を削除
void Jangeki_Reflection::Delete_reflectionJangeki(int jan_count_reflection)
{
	delete obj_reflection[jan_count_reflection];       //削除
	obj_reflection[jan_count_reflection] = nullptr;    //初期化

	//詰める
	for (int i = jan_count_reflection; i < (JANGEKI_MAX - 1); i++)
	{
		//次の要素が nullptr ならそれ以上は処理しない
		if (obj_reflection[i + 1] == nullptr) break;

		obj_reflection[i] = obj_reflection[i + 1];
		obj_reflection[i + 1] = nullptr;
	}
}

bool Jangeki_Reflection::GetFlg() {
	return reflectionFlg;
}

void Jangeki_Reflection::trueFlg() {
	reflectionFlg = true;
}
void Jangeki_Reflection::falseFlg() {
	reflectionFlg = false;
}
