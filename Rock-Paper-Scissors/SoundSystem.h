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

	ENEMY_SLIGHTLYBROKEN,
	ENEMY_SHIELDBROKEN,
	ENEMY_SPECIAL,
	ENEMY_SPECIAL_ATTACK,
	ENEMY10_HAHAHA,
	ENEMY10_Tepepo,

	/*敵↑*/
	
	/*それ以外↓*/
};

//BGMの種類  bgmを追加した際にここに追加
enum class BGM
{
	TITLE,
	ST03_BGM,
	STAGE04_BGM,
	ENEMY_10_Form2BGM,
	ENEMY_10_Marry,
	ENEMY_10_Arupus,
	ENEMY_10_London,
};



//サウンド
class SoundSystem
{
public:
	//SE,BGM読み込み（main.cpp　で一度呼ぶだけ）
	static void LoadSounds_SE(); 
	static void LoadSounds_BGM();

	static void PlaySE(const SE& se_type);       //SE再生
	static void PlayBGM(const BGM& bgm_type);    //BGM再生
	
	static void StopSE(const SE& se_type);
	static void StopBGM(const BGM& bgm_type);

private:
	SoundSystem();   //オブジェクトを作らない


	static std::vector<int> se_sounds;    //すべてのSE
	static std::vector<int> bgm_sounds;   //すべてのBGM
};
