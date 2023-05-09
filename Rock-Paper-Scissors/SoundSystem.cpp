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
	se_sounds.push_back (LoadSoundMem("Sound/jump_player.mp3"));
	se_sounds.push_back(LoadSoundMem("Sound/st03/SlightlyBrokenSE.wav"));
	se_sounds.push_back(LoadSoundMem("Sound/st03/BrokenSE.wav"));
}

void  SoundSystem::LoadSounds_BGM()
{
	//BGM
	// bgm_sounds.push_back(LoadSoundMem("サウンドへのパス"));
	bgm_sounds.push_back(LoadSoundMem("Sound/TitleBGM.mp3"));
	bgm_sounds.push_back(LoadSoundMem("Sound/st03/St03BGM.wav"));
	bgm_sounds.push_back(LoadSoundMem("Sound/stage04/stage04_BGM.wav"));
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