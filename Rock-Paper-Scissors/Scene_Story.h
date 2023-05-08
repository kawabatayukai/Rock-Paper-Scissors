#pragma once
#include"AbstractScene.h"
#include<iostream>
#include<vector>

//���炷��
class Scene_Story : public AbstractScene
{
public:
	//�R���X�g���N�^
	Scene_Story();         

	//�f�X�g���N�^
	~Scene_Story();               

	void Update() override;
	void Draw() const override;

	//�V�[���̕ύX
	AbstractScene* ChangeScene() override;

private:

	//���炷���e�L�X�g
	std::vector<std::string> *text;

	bool isLoadFailed;  //�ǂݍ��ݎ��s!
	int font_text;      //�e�L�X�g�p�t�H���g
	int font_skip;      //"skip"�p�t�H���g

	int scroll_y;       //�X�N���[��(�e�L�X�g�`��y���W�Ɍ��Z����)
	int scroll_speed;   //�X�N���[�����x(A�{�^���ő���)

	bool str_end;
	int skipflash_count;//�X�L�b�v�_�ŗp�t���[���J�E���^�[
};