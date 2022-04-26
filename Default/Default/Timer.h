#pragma once

#include "Include.h"

class CTimer
{
public:
	CTimer();
	~CTimer();

	void StartTimer(const float, std::function<void()>);

	void StopTimer() { m_bRunTimer = false; }
	void Update();

private:
	bool m_bRunTimer;
	std::function<void()> pExcuteCallBack;

	int m_iCurrentTime;
	float m_iRepeatRate;
	float m_iCurrentCount;
};

