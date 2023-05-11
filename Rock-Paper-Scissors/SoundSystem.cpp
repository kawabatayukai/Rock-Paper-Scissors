#include"DxLib.h"
#include"SoundSystem.h"

//staticメンバ変数の実体生成

//すべてのSE
std::vector<int> SoundSystem::se_sounds;  
//すべてのBGM
std::vector<int> SoundSystem::bgm_sounds;   

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

	/*ステージ3*/
	se_sounds.push_back(LoadSoundMem("Sound/st03/SlightlyBrokenSE.wav"));
	se_sounds.push_back(LoadSoundMem("Sound/st03/BrokenSE.wav"));
	se_sounds.push_back(LoadSoundMem("Sound/st03/Gard.wav"));
	se_sounds.push_back(LoadSoundMem("Sound/st03/RunningSt03.wav"));
	se_sounds.push_back(LoadSoundMem("Sound/st03/WorkingSt03.wav"));
	/*ステージ4*/
	se_sounds.push_back(LoadSoundMem("Sound/stage04/specialSE.wav"));
	se_sounds.push_back(LoadSoundMem("Sound/stage04/specialAttackSE.wav"));

	/*ステージ5*/

	/*ステージ6*/

	/*ステージ7*/

	/*ステージ8*/

	/*ステージ9*/

	/*ステージ10*/
	se_sounds.push_back(LoadSoundMem("Sound/笑い声2.mp3"));
	se_sounds.push_back(LoadSoundMem("Sound/ピョョョ2.mp3"));

	/*敵↑*/

	/*それ以外↓*/
}

void  SoundSystem::LoadSounds_BGM()
{
	//BGM
	// bgm_sounds.push_back(LoadSoundMem("サウンドへのパス"));
	bgm_sounds.push_back(LoadSoundMem("Sound/TitleBGM.mp3"));
	bgm_sounds.push_back(LoadSoundMem("Sound/st03/St03BGM.wav"));
	bgm_sounds.push_back(LoadSoundMem("Sound/stage04/stage04_BGM.wav"));
	bgm_sounds.push_back(LoadSoundMem("Sound/sento.mp3"));
	bgm_sounds.push_back(LoadSoundMem("Sound/VSQPD_0077_Mary_Had_a_Little_Lamb_FC.mp3"));
	bgm_sounds.push_back(LoadSoundMem("Sound/VSQPD_0046_Yankee_Doodle.mp3"));
	bgm_sounds.push_back(LoadSoundMem("Sound/VSQPD_0048_London_Bridge.mp3"));
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

//BGM再生
void SoundSystem::PlayBGM(const BGM& bgm_type)
{
	int plays = bgm_sounds[static_cast<int> (bgm_type)];

	//再生中か（1で再生中）
	if (CheckSoundMem(plays) == 0)
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

//BGM停止
void SoundSystem::StopBGM(const BGM& bgm_type)
{
	int plays = bgm_sounds[static_cast<int> (bgm_type)];

	//再生中か（1で再生中）
	if (1)
	{
		StopSoundMem(plays);
	}
}