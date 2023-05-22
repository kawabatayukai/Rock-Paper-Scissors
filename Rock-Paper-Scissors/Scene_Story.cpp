#include"DxLib.h"
#include"Scene_Story.h"
#include"Scene_Stage01.h"
#include<fstream>
#include<string>
#include<sstream>
#include"KeyManager.h"
#include "SortSave.h"
#include"Scene_NextStage.h"

int Scene_Story::font_text = 0;      //�e�L�X�g�p�t�H���g
int Scene_Story::font_skip = 0;      //"skip"�p�t�H���g

//�萔
namespace _C_STORY
{
	const int CENTER_X = 640;    //��ʒ��S
	const int FIRST_Y = 720;     //�e�L�X�g1�s�ڂ̍���

	const int MIN_SPEED = 2;     //�Œ�X�N���[���X�s�[�h
	const int MAX_SPEED = 10;     //�ő�X�N���[���X�s�[�h
}

//�R���X�g���N�^
Scene_Story::Scene_Story() :
	isLoadFailed(false), str_end(false)
	, scroll_y(0), scroll_speed(_C_STORY::MIN_SPEED), skipflash_count(0)
{

	story_bgm = LoadSoundMem("Sound/Story.wav");

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
		if (data.compare("����Ȑ��E�𐳂��ׂ��A��l���u�v������񂯂񐢊E���ɏo�ꂷ��-----") == 0)
		{
			std::string name(sortSave.getRankingData(9).name);
			data.insert(data.find("�u") + 2, name);
		}

		text->push_back(data);
	}

	//�t�H���g���쐬
	if (font_text == 0)
		font_text = CreateFontToHandle("���C���I", 30, 10, DX_FONTTYPE_ANTIALIASING, -1, 0);
	if (font_skip == 0)
		font_skip = CreateFontToHandle("���C���I", 20, 10, DX_FONTTYPE_ANTIALIASING);

	image_back = LoadGraph("images/Story/Story_Back.png");
	

}

//�f�X�g���N�^
Scene_Story::~Scene_Story()
{

	StopSoundMem(story_bgm);

	//�e�L�X�g���폜
	delete text;
}

void Scene_Story::Update()
{

	//StoryBGM
	if (CheckSoundMem(story_bgm) == 0) PlaySoundMem(story_bgm, DX_PLAYTYPE_LOOP);

	using namespace _C_STORY;

	DrawGraph(0, 0, image_back, TRUE);

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
void Scene_Story::Draw() const
{
	using namespace _C_STORY;

	//DrawLine(CENTER_X, 0, CENTER_X, 720, 0xffffff, 3);
	

	//�_��"Skip"
	if (skipflash_count < 120)
	{
		if (scroll_speed <= _C_STORY::MIN_SPEED)
		{
			DrawStringToHandle(1050, 700, "Press B To Skip", 0xffffff, font_skip);
		}
		else if (scroll_speed > _C_STORY::MIN_SPEED)
		{
			DrawStringToHandle(1050, 700, "Press B To Slowly", 0xffffff, font_skip);
		}
		else {};
	}
}

//�V�[���̕ύX
AbstractScene* Scene_Story::ChangeScene()
{
	if(str_end == true && KeyManager::OnPadClicked(PAD_INPUT_A))
		//return dynamic_cast<AbstractScene*> (new Scene_Stage01());
		return dynamic_cast<AbstractScene*> (new Scene_NextStage(1));

	//�e�L�X�g�t�@�C���ǂݍ��ݎ��s�ŃX�e�[�W1��
	if (isLoadFailed == true)  
		return dynamic_cast<AbstractScene*> (new Scene_Stage01());
	//�X�V�Ȃ�
	return this;
}