#pragma once
#include<iostream>
#include<vector>

//SEの種類   seを追加した際にここに追加
enum class SE
{
	/*プレイヤー↓*/

	PLAYER_JUMP,

	/*プレイヤー↑*/

	/*敵↓*/

	/*ステージ1*/


	/*ステージ2*/
	ENEMY02_JUMP,
	ENEMY02_ZYANGEKI,

	/*ステージ3*/
	ENEMY_SLIGHTLYBROKEN,
	ENEMY_SHIELDBROKEN,
	ENEMY_GARDSTANCE,
	ENEMY_RUNNING,
	ENEMY_WORKING,

	/*ステージ4*/
	ENEMY_SPECIAL,
	ENEMY_SPECIAL_ATTACK,


	/*ステージ5*/


	/*ステージ6*/
	ENEMY06_SMOKE,


	/*ステージ7*/


	/*ステージ8*/
	//ENEMY08_Item,

	/*ステージ9*/
	ENEMY09_Teleprot,
	ENEMY09_Reflection,

	/*ステージ10*/
	ENEMY10_HAHAHA,
	ENEMY10_Tepepo,

	/*敵↑*/
	
	/*それ以外↓*/
};



//サウンド
class SoundSystem
{
public:
	//SE,BGM読み込み（main.cpp　で一度呼ぶだけ）
	static void LoadSounds_SE(); 

	static void PlaySE(const SE& se_type);       //SE再生
	
	static void StopSE(const SE& se_type);

private:
	SoundSystem();   //オブジェクトを作らない


	static std::vector<int> se_sounds;    //すべてのSE
};
