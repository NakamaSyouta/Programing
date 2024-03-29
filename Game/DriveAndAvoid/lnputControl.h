#pragma once
#include "Vector2D.h"

//入力管理機能
class InputControl
{
private:
	static bool now_button[16];//現在フレーム入力値
	static bool old_button[16];//過去フレーム入力値
	static float trigger[2];   //左右トリガー入力値
	static Vector2D stick[2];  //左右スティック入力値

public:
	static void Update();     //更新処理
	
	//ボタン入力取得処理
	static bool GetButton(int button);         //
	static bool GetButtonDown(int button);//
	static bool GetButtonUp(int button);  //

	//
	static float GetLeftTrigger();            //
	static float GetRightTrigger();           //

	//
	static Vector2D GetLeftTStick();
	static Vector2D GetRightStick();

private:
	//
	static bool CheckButtonRange(int button);

};