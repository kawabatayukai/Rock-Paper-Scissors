#include"DxLib.h"
#include"SoundSystem.h"

//static�����o�ϐ��̎��̐���

//���ׂĂ�SE
std::vector<int> SoundSystem::se_sounds;  


//SE,BGM�ǂݍ��݁imain.cpp�@�ň�x�ĂԂ����j
void  SoundSystem::LoadSounds_SE()
{
	//SE
	// se_sounds.push_back(LoadSoundMem("�T�E���h�ւ̃p�X"));

	/*�v���C���[��*/

	se_sounds.push_back (LoadSoundMem("Sound/jump_player.mp3"));

	/*�v���C���[��*/

	/*�G��*/

	/*�X�e�[�W1*/

	/*�X�e�[�W2*/
	se_sounds.push_back(LoadSoundMem("Sound/enemy(Jump).mp3"));
	se_sounds.push_back(LoadSoundMem("Sound/zyangeki.mp3"));
	/*�X�e�[�W3*/
	se_sounds.push_back(LoadSoundMem("Sound/st03/SlightlyBrokenSE.wav"));
	se_sounds.push_back(LoadSoundMem("Sound/st03/BrokenSE.wav"));
	se_sounds.push_back(LoadSoundMem("Sound/st03/GardStance.wav"));
	se_sounds.push_back(LoadSoundMem("Sound/st03/RunningSt03.wav"));
	se_sounds.push_back(LoadSoundMem("Sound/st03/WorkingSt03.wav"));
	/*�X�e�[�W4*/
	se_sounds.push_back(LoadSoundMem("Sound/stage04/specialSE.wav"));
	se_sounds.push_back(LoadSoundMem("Sound/stage04/specialAttackSE.wav"));

	/*�X�e�[�W5*/

	/*�X�e�[�W6*/
	se_sounds.push_back(LoadSoundMem("Sound/stage06/bomb.mp3"));

	/*�X�e�[�W7*/

	/*�X�e�[�W8*/
	//se_sounds.push_back(LoadSoundMem("Sound/Stage8/stage8_Item.mp3"));
	/*�X�e�[�W9*/
	se_sounds.push_back(LoadSoundMem("Sound/stage09/teleport.mp3"));
	se_sounds.push_back(LoadSoundMem("Sound/stage09/reflection.mp3"));


	/*�X�e�[�W10*/
	se_sounds.push_back(LoadSoundMem("Sound/�΂���2.mp3"));
	se_sounds.push_back(LoadSoundMem("Sound/�s������2.mp3"));

	/*�G��*/

	/*����ȊO��*/
	
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

//SE��~
void SoundSystem::StopSE(const SE& se_type)
{
	int plays = se_sounds[static_cast<int> (se_type)];

	if (1)
	{
		StopSoundMem(plays);
	}
}

