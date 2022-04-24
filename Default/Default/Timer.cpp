#include "stdafx.h"
#include "Timer.h"

CTimer::CTimer() {

}

CTimer::~CTimer() {

}

void CTimer::StartTimer(float _repeatRateSecond, std::function<void()> _pCallBack) {
	m_iRepeatRateSecond = _repeatRateSecond;
	pExcuteCallBack = _pCallBack;

	m_iCurrentTime = g_dwCurrentTime;
	m_iCurrentSecondCount = 0;
	m_bRunTimer = true;
}

void CTimer::Update() {
	if (m_iRepeatRateSecond <= m_iCurrentTime - g_dwCurrentTime) {
		++m_iCurrentSecondCount;

		if (m_iCurrentSecondCount >= m_iRepeatRateSecond) {
			m_iCurrentSecondCount = 0;
			
			pExcuteCallBack();
		}
	}

	m_iCurrentTime = g_dwCurrentTime;
}