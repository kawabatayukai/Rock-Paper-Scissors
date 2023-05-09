#include"DxLib.h"
#include"SoundSystem.h"

//static�����o�ϐ��̎��̐���

//���ׂĂ�SE
std::vector<int> SoundSystem::se_sounds;  
//���ׂĂ�BGM
std::vector<int> SoundSystem::bgm_sounds;   

//SE,BGM�ǂݍ��݁imain.cpp�@�ň�x�ĂԂ����j
void  SoundSystem::LoadSounds_SE()
{
	//SE
	// se_sounds.push_back(LoadSoundMem("�T�E���h�ւ̃p�X"));
	se_sounds.push_back (LoadSoundMem("Sound/jump_player.mp3"));
	se_sounds.push_back(LoadSoundMem("Sound/st03/SlightlyBrokenSE.wav"));
	se_sounds.push_back(LoadSoundMem("Sound/st03/BrokenSE.wav"));
}

void  SoundSystem::LoadSounds_BGM()
{
	//BGM
	// bgm_sounds.push_back(LoadSoundMem("�T�E���h�ւ̃p�X"));
	bgm_sounds.push_back(LoadSoundMem("Sound/TitleBGM.mp3"));
	bgm_sounds.push_back(LoadSoundMem("Sound/st03/St03BGM.wav"));
	bgm_sounds.push_back(LoadSoundMem("Sound/stage04/stage04_BGM.wav"));
}



//SE�Đ�
void SoundSystem::PlaySE(const SE& se_type)
{
	int plays = se_sounds[static_cast<int> (se_type)];

	if (1)
	{
		PlaySoundMem(plays, DX_PLAYTYPE_BACK);
	}
}

//BGM�Đ�
void SoundSystem::PlayBGM(const BGM& bgm_type)
{
	int plays = bgm_sounds[static_cast<int> (bgm_type)];

	//�Đ������i1�ōĐ����j
	if (CheckSoundMem(plays) == 0)
	{
		PlaySoundMem(plays, DX_PLAYTYPE_BACK);
	}
}

//SE��~
void SoundSystem::StopSE(const SE& se_type)
{
	int plays = se_sounds[static_cast<int> (se_type)];

	if (1)
	{
		StopSoundMem(plays);
	}
}

//BGM��~
void SoundSystem::StopBGM(const BGM& bgm_type)
{
	int plays = bgm_sounds[static_cast<int> (bgm_type)];

	//�Đ������i1�ōĐ����j
	if (1)
	{
		StopSoundMem(plays);
	}
}