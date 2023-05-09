#pragma once
#include<iostream>
#include<vector>

//SE�̎��   se��ǉ������ۂɂ����ɒǉ�
enum class SE
{
	/*�v���C���[��*/

	PLAYER_JUMP,

	/*�v���C���[��*/

	/*�G��*/

	ENEMY_SLIGHTLYBROKEN,
	ENEMY_SHIELDBROKEN,
	ENEMY_SPECIAL,
	ENEMY_SPECIAL_ATTACK,
	ENEMY10_HAHAHA,
	ENEMY10_Tepepo,

	/*�G��*/
	
	/*����ȊO��*/
};

//BGM�̎��  bgm��ǉ������ۂɂ����ɒǉ�
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
