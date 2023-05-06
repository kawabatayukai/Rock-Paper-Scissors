#include "Scne_TitleInterval.h"
#include"DxLib.h"
#include<fstream>
#include<string>
#include"KeyManager.h"
#include"Scene_Title.h"

//�萔
namespace _C_STORY
{
	const int CENTER_X = 640;    //��ʒ��S
	const int FIRST_Y = 300;     //�e�L�X�g1�s�ڂ̍���

	const int MIN_SPEED = 1;     //�Œ�X�N���[���X�s�[�h
	const int MAX_SPEED = 7;     //�ő�X�N���[���X�s�[�h
}

//�R���X�g���N�^
Scne_TitleInterval::Scne_TitleInterval() :
	isLoadFailed(false), str_end(false)
	, scroll_y(0), scroll_speed(_C_STORY::MIN_SPEED), skipflash_count(0)
{
	//�t�@�C���X�g���[��
	std::ifstream read_file;

	//�J��
	read_file.open("textdata/Arasuzi.txt", std::ios::in);

	//���s!
	if (read_file.fail() == true) isLoadFailed = true;

	//���I�ɐ���
	text = new std::vector<std::string>();

	//�ǂݍ���
	std::string data("");
	while (std::getline(read_file, data))
	{
		text->push_back(data);
	}

	//�t�H���g���쐬
	font_text = CreateFontToHandle("���C���I", 30, 10, DX_FONTTYPE_ANTIALIASING, -1, 0);
	font_skip = CreateFontToHandle("���C���I", 20, 10, DX_FONTTYPE_ANTIALIASING);
}

//�f�X�g���N�^
Scne_TitleInterval::~Scne_TitleInterval()
{
	//�e�L�X�g���폜
	delete text;

	//�t�H���g���폜
	DeleteFontToHandle(font_text);

	SetBackgroundColor(0, 0, 0);
}

void Scne_TitleInterval::Update()
{
	using namespace _C_STORY;

	//1�s���`��
	for (int i = 0; i < text->size(); i++)
	{
		std::string str(text->data()[i]);

		//������̕�
		int str_w = GetDrawStringWidthToHandle(str.c_str(), str.size(), font_text);

		//�`����W
		int str_x = CENTER_X - str_w / 2;
		int str_y = FIRST_Y + (i * 100) - scroll_y;

		//��ʊO�ŃX�L�b�v
		if (str_y < -30) continue;

		//char*�ɕϊ�,
		DrawFormatStringToHandle(str_x, str_y, 0xffffff, font_text, "%s", str.c_str());

		//�e�L�X�g�̍ŏI�s�܂ŏI��
		if (i >= text->size() - 1 && str_y < 0) str_end = true;
	}
	if (str_end == true) DrawStringToHandle(100, 100, "Press A To Start", 0xffffff, font_text);



	//B�{�^���ŉ��� / ���Z�b�g
	if (KeyManager::OnPadClicked(PAD_INPUT_B) == true)
	{
		if (scroll_speed <= _C_STORY::MIN_SPEED)
		{
			scroll_speed = _C_STORY::MAX_SPEED;
		}
		else if (scroll_speed > _C_STORY::MIN_SPEED)
		{
			scroll_speed = _C_STORY::MIN_SPEED;
		}
		else {};
	}

	//�X�N���[��
	scroll_y += scroll_speed;
	//�_��
	if (++skipflash_count >= 240) skipflash_count = 0;
}

//�`��
void Scne_TitleInterval::Draw() const
{
	using namespace _C_STORY;

	DrawLine(CENTER_X, 0, CENTER_X, 720, 0xffffff, 3);
	SetBackgroundColor(0, 64, 0);

	//static bool str_end;

	////1�s���`��
	//for (int i = 0; i < text->size(); i++)
	//{
	//	std::string str(text->data()[i]);

	//	//������̕�
	//	int str_w = GetDrawStringWidthToHandle(str.c_str(), str.size(), font_text);

	//	//�`����W
	//	int str_x = CENTER_X - str_w / 2;
	//	int str_y = FIRST_Y + (i * 100) - scroll_y;

	//	//��ʊO�ŃX�L�b�v
	//	if (str_y < -30) continue;

	//	//char*�ɕϊ�,
	//	DrawFormatStringToHandle(str_x, str_y, 0xffffff, font_text, "%s", str.c_str());

	//	//�e�L�X�g�̍ŏI�s�܂ŏI��
	//	if (i >= text->size() - 1 && str_y < 0) str_end = true;
	//}
	//if (str_end == true) DrawString(100, 100, "Press A To Start", 0xffffff);

	//�_��"Skip"
	if (skipflash_count < 120)
	{
		if (scroll_speed <= _C_STORY::MIN_SPEED)
		{
			DrawStringToHandle(1050, 700, "Press A or B To Skip", 0xffffff, font_skip);
		}
		else if (scroll_speed > _C_STORY::MIN_SPEED)
		{
			DrawStringToHandle(1050, 700, "Press B To Slowly", 0xffffff, font_skip);
		}
		else {};
	}
}

//�V�[���̕ύX
AbstractScene* Scne_TitleInterval::ChangeScene()
{
	//if (str_end == true && KeyManager::OnPadClicked(PAD_INPUT_A))
		//return dynamic_cast<AbstractScene*> (new TitleScene());
	if (KeyManager::OnPadClicked(PAD_INPUT_A) || KeyManager::OnPadClicked(PAD_INPUT_B))
		return dynamic_cast<AbstractScene*> (new TitleScene());

	//�e�L�X�g�t�@�C���ǂݍ��ݎ��s�ŃX�e�[�W1��
	if (isLoadFailed == true)
		return dynamic_cast<AbstractScene*> (new TitleScene());
	//�X�V�Ȃ�
	return this;
}