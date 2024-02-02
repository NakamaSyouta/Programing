#pragma once
#include "../Utility/Vector2D.h"
#include"Barrier.h"

class Player
{
private:
	bool is_active;
	int image;
	Vector2D location;
	Vector2D box_size;
	float angle;
	float speed;
	float hp;
	float fuel;
	int barrier_count;
	Barrier* barrier;

public:
	Player();
	~Player();

	void Initialize();
	void Update();
	void Draw();
	void Finalize();

public:
	void SetActive(bool flg);
	void DecreaseHp(float value);
	Vector2D GetLocation()const;
	Vector2D GetBoxSize()const;
	float GetSpeed()const;
	float GetFuel()const;
	float GetHp()const;
	int GetBarrier()const;
	bool IsBarrier()const;

private:
	void Movement();
	void Acceleration();
};