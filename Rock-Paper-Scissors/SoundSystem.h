#pragma once
#include<iostream>
#include<vector>

//SE�̎��   se��ǉ������ۂɂ����ɒǉ�
enum class SE
{
	PLAYER_JUMP,
	ENEMY_SLIGHTLYBROKEN,
	ENEMY_SHIELDBROKEN,
	
};

//BGM�̎��  bgm��ǉ������ۂɂ����ɒǉ�
enum class BGM
{
	TITLE,
};



//�T�E���h
class SoundSystem
{
public:
	//SE,BGM�ǂݍ��݁imain.cpp�@�ň�x�ĂԂ����j
	static void LoadSounds_SE(); 
	static void LoadSounds_BGM();

	static void PlaySE(const SE& se_type);       //SE�Đ�
	static void PlayBGM(const BGM& bgm_type);    //BGM�Đ�
	
	static void StopSE(const SE& se_type);
	static void StopBGM(const BGM& bgm_type);

private:
	SoundSystem();   //�I�u�W�F�N�g�����Ȃ�


	static std::vector<int> se_sounds;    //���ׂĂ�SE
	static std::vector<int> bgm_sounds;   //���ׂĂ�BGM
};
