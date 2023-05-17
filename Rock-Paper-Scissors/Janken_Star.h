#pragma 

class Janken_Star
{
public:
	Janken_Star(const float& x, const float& y,const float& targetX,const float& targetY);
	~Janken_Star();

	void Update();
	void Draw() const;

	float GetX() const { return x; }
	float GetY() const { return y; }

	bool CheckScreenOut();

private:
	float x;
	float y;

	float speed;
	double rate;  //��]��
	float angle;  //�p�x

	int image;
	int type;     //���̃^�C�v�i�G�t�F�N�g�ʁj
};
