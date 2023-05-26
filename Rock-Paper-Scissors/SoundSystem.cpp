#include"DxLib.h"
#include"SoundSystem.h"

//staticメンバ変数の実体生成

//すべてのSE
std::vector<int> SoundSystem::se_sounds;  


//SE,BGM読み込み（main.cpp　で一度呼ぶだけ）
void  SoundSystem::LoadSounds_SE()
{
	//SE
	// se_sounds.push_back(LoadSoundMem("サウンドへのパス"));

	/*プレイヤー↓*/

	se_sounds.push_back (LoadSoundMem("Sound/jump_player.mp3"));

	/*プレイヤー↑*/

	/*敵↓*/

	/*ステージ1*/

	/*ステージ2*/
	se_sounds.push_back(LoadSoundMem("Sound/enemy(Jump).mp3"));
	se_sounds.push_back(LoadSoundMem("Sound/zyangeki.mp3"));
	/*ステージ3*/
	se_sounds.push_back(LoadSoundMem("Sound/st03/SlightlyBrokenSE.wav"));
	se_sounds.push_back(LoadSoundMem("Sound/st03/BrokenSE.wav"));
	se_sounds.push_back(LoadSoundMem("Sound/st03/GardStance.wav"));
	se_sounds.push_back(LoadSoundMem("Sound/st03/RunningSt03.wav"));
	se_sounds.push_back(LoadSoundMem("Sound/st03/WorkingSt03.wav"));
	/*ステージ4*/
	se_sounds.push_back(LoadSoundMem("Sound/stage04/specialSE.wav"));
	se_sounds.push_back(LoadSoundMem("Sound/stage04/specialAttackSE.wav"));

	/*ステージ5*/

	/*ステージ6*/
	se_sounds.push_back(LoadSoundMem("Sound/stage06/bomb.mp3"));

	/*ステージ7*/

	/*ステージ8*/
	//se_sounds.push_back(LoadSoundMem("Sound/Stage8/stage8_Item.mp3"));
	/*ステージ9*/
	se_sounds.push_back(LoadSoundMem("Sound/stage09/teleport.mp3"));
	se_sounds.push_back(LoadSoundMem("Sound/stage09/reflection.mp3"));


	/*ステージ10*/
	se_sounds.push_back(LoadSoundMem("Sound/笑い声2.mp3"));
	se_sounds.push_back(LoadSoundMem("Sound/ピョョョ2.mp3"));

	/*敵↑*/

	/*それ以外↓*/
	
}





//SE再生
void SoundSystem::PlaySE(const SE& se_type)
{
	int plays = se_sounds[static_cast<int> (se_type)];

	if (1)
	{
		PlaySoundMem(plays, DX_PLAYTYPE_BACK);
	}
}

//SE停止
void SoundSystem::StopSE(const SE& se_type)
{
	int plays = se_sounds[static_cast<int> (se_type)];

	if (1)
	{
		StopSoundMem(plays);
	}
}

