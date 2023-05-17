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
	double rate;  //回転率
	float angle;  //角度

	int image;
	int type;     //星のタイプ（エフェクト面）
};
