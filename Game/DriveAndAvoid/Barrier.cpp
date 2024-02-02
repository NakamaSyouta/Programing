#include"Barrier.h"
#include"Dxlib.h"

Barrier::Barrier() :imager(NULL), life_span(1000)
{
	//
	imager = LoadGraph("Resource/images/barrier.png");
	//
	if (imager == -1)
	{
		throw("Resource/images/barrier.png‚ª‚ ‚è‚Ü‚¹‚ñ`n");

	}
}
Barrier::~Barrier()
{
	//
	DeleteGraph()

}
//
void Barrier::Draw(const Vector2D& location)
{
	DrawRotaGraphf(location.x, location.y, 1.0, 0.0, image, TRUE);

}
//
bool Barrier::lsFinished(float speed)
{
	life_span -= speed;

	return (life_span <= 0);
}