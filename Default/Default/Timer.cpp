#include "stdafx.h"
#include "Timer.h"

CTimer::CTimer():
	m_iCurrentTime(0),
	m_iRepeatRate(0),
	m_iCurrentCount(0) {

}

CTimer::~CTimer() {

}

void CTimer::StartTimer(const float _repeatRateSecond, std::function<void()> _pCallBack) {
  	m_iRepeatRate = _repeatRateSecond;
	pExcuteCallBack = _pCallBack;

	m_iCurrentTime = g_dwCurrentTime;
	m_iCurrentCount = 0;
	m_bRunTimer = true;
}

void CTimer::Update() {
	if (1 <= g_dwCurrentTime - m_iCurrentTime) {
		m_iCurrentCount += TIMESCALE;

		if (m_iCurrentCount >= m_iRepeatRate) {
			m_iCurrentCount = 0;
			
			pExcuteCallBack();
		}
	}

	m_iCurrentTime = g_dwCurrentTime;
}