#pragma once
#include "AbstractScene.h"
#include"KeyBoard.h"

//�L�[�̎��
enum class CURSOR_TYPE
{
	NONE = 0,   // ����0�i�Ȃɂ�������Ă��Ȃ��j
	NORMAL,     // A�`B,a�`b,1�`9
	CANCEL,     //�u�~�v(�ЂƂ���)
	DONE,       //�uOK�v(�m��)
	MISS = 99
};

class Scene_InputNameRanking : public AbstractScene
{
public:
	Scene_InputNameRanking();
    ~Scene_InputNameRanking();
	//�X�V
	void Update()override;

	//�`��
	void Draw()const override;

	//�V�[���̕ύX����
	AbstractScene* ChangeScene()override;

private:
	KeyBoard* keyboard;   //�L�[�{�[�h
	int bgm;
};

