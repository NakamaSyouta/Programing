#pragma once

#include"SceneBase.h"
#include"../Objet/Player.h"
#include"Enemy.h"

class GamaMainScene :public SceneBase
{
public:
	int high_score;
	int back_ground;
	int barrier_image;
	int mileage;
	int enemy_image[3];
	int enemy_count[3];
	Player*player;
	Enemy** enemy;


public:
	GamaMainScene();
	virtual ~GamaMainScene();

	virtual void Initialize()override;
	virtual eSceneType Update() override;
	virtual void Draw()const override;
	virtual void Finalize()override;

	virtual eSceneType GetNowScene()const override;

private:
	//�n�C�X�R�A�ǂݍ��ݏ���
	void ReadHighScore();
	//�����蔻��
	bool IsHitCheck(player* p, Enemy* e);

};