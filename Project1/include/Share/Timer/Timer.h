#pragma once
#include "../../GameInfo.h"

/*
	델타 타임이란 ?
	프레임 간의 시간차이를 의미한다.
	FPS 는 1초에 몇 번 화면이 갱신 되었는가를 의미한다.
	60fps -> 1초에 화면이 60번 그려진것이다.
	60fps 일 때 1프레임은 몇 초 인가 ? 0.016666초 정도 된다.
*/

class CTimer
{
	friend class CGameManager;

private:
	static LARGE_INTEGER mSecond;
	static LARGE_INTEGER mTime;
	static float mDeltaTime;	// 델타타임을 나타내는 것

private:
	static void Init();
	static float Update();

public:
	static float GetDeltaTime();
};

