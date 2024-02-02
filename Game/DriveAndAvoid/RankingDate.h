#pragma once

class RankingData
{
private:
	int score[6];
	int rank[6];
	char name[6][15];

public:
	RankingData();
	~RankingData();

	void Initialize();//‰Šú‰»ˆ—
	void Finalize();//I—¹ˆ—

public:
	//
	void SetRankingData(int score, const char* name);
	//
	int GetScore(int value)const;
	//
	int GetRank(int value)const;
	//
	const char* GetName(int value)const;

private:
	//
	void SortDate();
};