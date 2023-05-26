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

	/*�X�e�[�W1*/


	/*�X�e�[�W2*/
	ENEMY02_JUMP,
	ENEMY02_ZYANGEKI,

	/*�X�e�[�W3*/
	ENEMY_SLIGHTLYBROKEN,
	ENEMY_SHIELDBROKEN,
	ENEMY_GARDSTANCE,
	ENEMY_RUNNING,
	ENEMY_WORKING,

	/*�X�e�[�W4*/
	ENEMY_SPECIAL,
	ENEMY_SPECIAL_ATTACK,


	/*�X�e�[�W5*/


	/*�X�e�[�W6*/
	ENEMY06_SMOKE,


	/*�X�e�[�W7*/


	/*�X�e�[�W8*/
	//ENEMY08_Item,

	/*�X�e�[�W9*/
	ENEMY09_Teleprot,
	ENEMY09_Reflection,

	/*�X�e�[�W10*/
	ENEMY10_HAHAHA,
	ENEMY10_Tepepo,

	/*�G��*/
	
	/*����ȊO��*/
};



//�T�E���h
class SoundSystem
{
public:
	//SE,BGM�ǂݍ��݁imain.cpp�@�ň�x�ĂԂ����j
	static void LoadSounds_SE(); 

	static void PlaySE(const SE& se_type);       //SE�Đ�
	
	static void StopSE(const SE& se_type);

private:
	SoundSystem();   //�I�u�W�F�N�g�����Ȃ�


	static std::vector<int> se_sounds;    //���ׂĂ�SE
};
