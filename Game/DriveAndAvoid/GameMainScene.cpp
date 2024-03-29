#include"GameMainScene.h"
#include"../Object/RankinData.h"
#include"DxLib.h"
#include<math.h>

GamaMainScene::GamaMainScene() :high_score(0), back_ground(NULL),
barrier_image(NULL),
mileage(0), player(nullptr),
enemy(nullptr)
{
	for (int i = 0;i < 3;i++)
	{
		enemy_image[i] = NULL;
		enemy_count[i] = NULL;
	}
}
GamaMainScene::~GamaMainScene()
{

}
//初期化処理
void GameMainScene::Initialize()
{

	//高得点値を読み込む
	ReadHighScore();
	
	//画像の読み込み
	back_ground = LoadGraph("Resource/images/back.bmp");
	barrier_image = LoadGraph("Resource/images/barrier.png");
	int result = LoadDivGraph("Resource/images/car.bmp", 3, 3, 1, 63, 120, 
		enemy_image);

	//エラーチェック
	if (back_ground == -1)
	{
		throw("Resource/images/back.bmpがありません`n");

	}
	if (result == -1)
	{
		throw("Resource/images/car.bmpがありません`n");
	}
	if (barrier_image == -1)
	{
		throw("Resource/images/car.bmpがありません`n");
	}
	//オブジェクトの生成
	player = new Player;
	enemy = new Enemy * [10];

	//オブジェクトの初期化
	player->Initialize();

	for (int i = 0;i < 10;i++)
	{
		enemy[i] = nullptr;
	}
}
//更新処理
eSceneType GameMainScene::Update()
{
	//プレイヤーの更新
	player->Updata();

	//移動距離の更新
	mileage += (int)player->GetSpeed
	() + 5;

	//適正性処理
	if (mileage / 20 % 100 == 0)
	{
		for (int i = 0;i < 10;i++)
		{
			if (enemy[i] == nullptr)
			{
				int type = GetRand(3) % 3;
				enemy[i] = new Enemy(type, enemy_image[type]);
				enemy[i]->Initialize();
				break;
			}
		}
	}
	//敵の更新と当たり判定チェック
	for (int i = 0;i < 10;i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Updata(player->GetSpeed());

			//画面外に行ったら、敵を削除してスコア加算
			if (enemy[i]->GetLocation().y >= 640.0f)
			{
				enemy_count[enemy[i]->GetType()]++;
				enemy_[i]->Finalize();
				delete enemy[i];
				enemy[i] = nullptr;
			}
			//当たり判定の確認
			if (IsHitCheck(player, enemy[i]))
			{
				player->SetActive(false);
				player->DecreaseHp(-50.0f);
				enemy[i]->Finalize();
				delete enemy[i];
				enemy[i] = nullptr;
			}
		}
	}
	//プレイヤーの燃料が体力が０未満なら、リザルトに遷移する
	if (player->GetFuel() < 0.0f || player->GetHp() < 0.0f)
	{
		return eSceneType::E_RESULT;
	}
	return GetNowScene();
}
//描画処理
void GameMainScene::Draw()const
{
	//背景画像の描画
	DrawGraph(0, mileage % 480 - 480, back_ground, TRUE);
	DrawGraph(0, mileage % 480, back_ground, TRUE);
	
	//敵の描画
	for (int i = 0;i < 10;i++)
	{
		if (nenemy[i] != nullptr)
		{
			enemy[i]->Draw();
		}
	}
	//プレイヤーの描画
	player->Draw();

	//UIの描画
	DrawBox(500, 640m480, GetContColor(0, 153, 0), TRUE);
	SetFontSize(16);
	DrawFormaString(510, 20, GetColor(0, 0, 0), "ハイスコア");
	DrawFormaString(560, 40, GetColor(255, 255, 255), "%08d",high_scre);
	DrawFormaString(510, 80, GetColor(0, 0, 0), "避けた数");
	for (int i = 0;i < 3;i++)
	{
		DrawRotaGraph(523 + (i * 50), 120, 0, 3, 0, enemy_iimage[i], TRUE,
			FALSE);
		DrawFormatString(510 + (i * 50), 140, Getcolor(255, 255, 255), "%03d",
			enemy_count[i]);
	}
	DrawFormatString(510, 200, Getcolor(0, 0, 0), "走行距離");

	DrawFormatString(555, 220, Getcolor(255,255,255), "%08d",mileage/10);
	DrawFormatString(510, 240, Getcolor(0,0,0), "スピード");
	DrawFormatString(555, 260, Getcolor(255,255,255),"%08.1f",
		player->GetSpeed());

	//バリアの枚数の描画
	for (int i = 0;i < player->GetBarriarCont();i++) {
		DrawRotaGraph(520 + i * 25, 340, 0.2f, 0, barrier_image, TRUE, FALSE);
	}
	//燃料がゲージの描画
	float fx = 510.0f;
	float fy = 390.0f;

	DrawFormatString(fx, fy, Getcolor(0, 0, 0), "FUEL METER");
	DrawBoxAA(fx, fy + 20.0f, fx + (player->GetFuel() * 100 / 2000), fy +40.0f, 
		GetColor(0, 102, 204), TRUE);

	DrawBoxAA(fx, fy + 20.0f, fx + 100.0f,fy +40.0f, GetColor(0, 0, 0), FALSE);

	//体力ゲージの描画
	fx = 510.0f;
	fy = 430.0f;
	DrawFormatString(fx, fy, Getcolor(0, 0, 0), "PLAYER HP");
	DrawBoxAA(fx, fy + 20.0f, fx + (player->GetHp() * 100 / 1000), fy + 40.0f,
		GetColor(255,0,0), TRUE);
	DrawBoxAA(fx, fy + 20.0f, fx + 100.0f, fy + 40.0f,
		GetColor(0,0,0), FALSE);
}
//終了時処理
void GetMainScene::Finalize()
{
	//スコアを計算する
	int score = (mileage / 10 * 10);
	for (int i = 0;i < 3;i++)
	{
		score += (i + 1) * 50 * enemey_count[i];

	}
	//リザルトデータの書き込み
	FILE* fp = nullptr;
	//ファイルオープン
	errno_t result = fopen_s(&fp,"Resource/dat/result_data.csv", "w");

	//エラーチェック
	if (result != 0)
	{
		throw("Resource/dat/result_data.csvが開きません`n");

	}
	//
	fprintf(fp, "%d,`n", score);
	
	//
	for (int i = 0;i < 3;i++)
	{
		fprintf(fp, "%d,`n", enemy_count[i]);
	}
	//
	fclose(fp);

	//
	player->Finalize();
	delete player;

	for (int i = 0;i < 10;i++)
	{
		if (enemy[i] != nullptr)
		{
			enemy[i]->Finalize();
			delete enemy[i];
			enemy[i] = nullptr;

		}
	}
	delete[] enemy;
}
//現在のシーン情報を取得
eSceneType GameMainScene::GetNowScene()const
{
	return eSceneType::E_MAIN;
}
//ハイスコアの読み込み
void GameMainScene::ReadHighScore()
{
	RankingData data;
	data.Initialize();

	high_score = data.GetScore(0);

	data.Finalize();
	}
//当たり判定処理（プレイヤーと敵）
bool GemeMainScene::IsHitChck(Player* p, Enemy* e)
{
	//
	if (p->IsBarrise())
	{
		return false;
	}
	//
	if (e == nullptr)
	{
		return false;
	}
	//
	Vector2D box_ex = p->GetBoxSize() + e->GetBoxSize();

	//
	return ((fabsf(diff_location.x) < box_ex.x) && (fabsf(diff_location.y) <
		box_ex.y));
}
