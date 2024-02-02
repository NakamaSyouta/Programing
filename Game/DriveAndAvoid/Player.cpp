#include"Player.h"
#include"../Utility/InputContorol.h"
#include"Dxlib.h"

Player::Player() :is_active(false), image(NULL), location(0.0f), box_size(0.0f),
angle(0.0f),
speed(0.0f), hp(0.0f), fuel(0.0f), barrier_count(0),
barrier(nullptr)
{

}
Player::~Player()
{

}
//
void Player::Initialize()
{
	is_active = true;
	location = Vector2D(320.0f, 380.0f);
	box_size = Vector2D(31.0f, 60.0f);
	angle = 0.0f;
	speed = 3.0f;
	hp = 1000;
	fuel = 20000;
	barrier_count = 3;

	//
	image = LoadGraph("Resource/images/carlpol.bmp");
	
	//
	if (image == -1)
	{
		throw("Resource/images/carlpol.bmp`n");

	}
}
//
void Player::Update()
{
	//
	if (!is_active)
	{
		angle += DX_PI_F / 24.0f;
		speed = 1.0f;
		if (angle >= DX_PI_F * 4.0f)
		{
			is_active = true;
		}
		return;
	}
	//
	fuel -= speed;

	//
	Movement();

	//
	Acceleration();

	if (InputControl::GetButtonDown(XINPUT_BUTTON_START))
	{
		is_active = false;
	}
	//
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B) && barrier_count > 0)
	{
		if (barrier == nullptr)
		{
			barrier_count--;
			barrier = new Barrier;
		}
	}
	//
	if (barrier != nullptr)
	{
		//
		if (barrier->IsFinished(this->speed))
		{
			delete barrier;
			barrier = nullptr;

		}
	}
}
//
void Player::Draw()
{
	//
	DrawRotaGraphF(location.x, location.y, 1.0, angle, image, TRUE);

	if (barrier != nullptr)
	{
		barrier->Draw(this->location);
	}
}
//
void Player::Finalize()
{
	//
	DeleteGraph(image);

	//
	if (barrier != nullptr)
	{
		delete barrier;
	}
}
void Player::SetActive(bool fig)
{
	this->is_active = fig;
}
//
void Player::DecreaseHp(float value)
{
	this->hp += value;
}
//
Vector2D Player::GetLocation()const
{
	return this->location;
}
//
Vector2D Player::GetBoxSize()const
{
	return this->box_size;
}
//
float Player::GetSpeed()const
{
	return this->speed;
}
float Player::GetHp()const
{
	return this->hp;
}
//
int Player::GetBarrierCount()const
{
	return(barrier != nullptr);
}
//
void Player::Movement()
{
	Vector2D  move = Vector2D(0.0f);
	angle = 0.0f;

	//
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_))
	{
		move += Vector2D(0.0f, 1.0f);
	}
	location += move;
	//
	if ((location.x < box_size.x) || (location.x >= 640.0f - 180) ||
		(location.y < box_size.y) || (location.y >= 480.0f - box_size.y))
	{
		location -= move;
	}
}
//
void Player::Acceleration()
{
	//
	if (InputControl::GetButtonDown(XINPUT_BUTTON_LEFT_SHOULDER) && speed > 1.0f)
	{
		speed -= 1.0f;
	}

	//
	if (InputControl::GetButtonDown(XINPUT_BUTTON_LEFT_SHOULDER) && speed < 10.0f)
	{
		speed += 1.0f;
	}
}