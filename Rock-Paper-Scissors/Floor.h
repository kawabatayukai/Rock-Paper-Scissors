#pragma once

//��`
class Floor
{
public:

	//�R���X�g���N�^  
	Floor(int x = 0, int y = 700, int w = 1280, int h = 20);

	void Draw() const;                //�`��

	int GetX() const { return x; }    //�����W�擾
	int GetY() const { return y; }    //�����W�擾
	int GetW() const { return w; }    //���@�@�擾
	int GetH() const { return h; }    //�����@�擾

private:
	//���W�͍���(�L�����N�^�[�͒��S)
	int x;
	int y;
	int w;
	int h;
};