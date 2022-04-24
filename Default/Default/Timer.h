#pragma once

#include "Include.h"

class CTimer
{
public:
	CTimer();
	~CTimer();

	void StartTimer(float, std::function<void()>);

	void StopTimer() { m_bRunTimer = false; }
	void Update();

private:
	bool m_bRunTimer;
	std::function<void()> pExcuteCallBack;

	int m_iCurrentTime;
	float m_iRepeatRateSecond;
	float m_iCurrentCount;
	
};

