#include "Scne_TitleInterval.h"
#include"DxLib.h"
#include"KeyManager.h"
#include"Scene_Title.h"

//�R���X�g���N�^
Scne_TitleInterval::Scne_TitleInterval() : frame(0), speed(10)
{
	image_high = LoadGraph("images/title_high.png");
	image_middle = LoadGraph("images/title_middle.png");
	image_low = LoadGraph("images/title_low.png");
}

//�f�X�g���N�^
Scne_TitleInterval::~Scne_TitleInterval()
{

}

void Scne_TitleInterval::Update()
{
	frame++;
	if (frame > 128) frame = 128;
}

//�`��
void Scne_TitleInterval::Draw() const
{
	//DrawString(0, 360, "Press A", 0xffffff);
	//DrawString(0, 400, "�Â����^�C�g��", 0xffffff);

	DrawGraph(-1280 + (frame * speed + 10), 0, image_high,TRUE);
	DrawGraph(1280 - (frame * speed + 10), (720 - 250), image_low, TRUE);
}

//�V�[���̕ύX
AbstractScene* Scne_TitleInterval::ChangeScene()
{
	if (frame == 128)
		return dynamic_cast<AbstractScene*> (new TitleScene());
	//�X�V�Ȃ�
	return this;
}