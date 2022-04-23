#include "stdafx.h"
#include "AssistantPlayer.h"


CAssistantPlayer::CAssistantPlayer()
{
}

CAssistantPlayer::CAssistantPlayer(ASSISTANT_DIR iLeftRight)
{
	m_iLeftRight = iLeftRight;
}


CAssistantPlayer::~CAssistantPlayer()
{
}

void CAssistantPlayer::Initialize(void)
{
	m_tInfo.fX = 0.f;
	m_tInfo.fY = 0.f;

	m_tInfo.fCX = 10.f;
	m_tInfo.fCY = 10.f;

	m_fSpeed = 10.f;
}

int CAssistantPlayer::Update(void)
{
	if (m_iLeftRight == AST_LEFT)
	{
		m_tInfo.fX = m_pPlayerInfo->fX - (m_pPlayerInfo->fCX + m_tInfo.fCX + 2.f);
	}
	else
	{
		m_tInfo.fX = m_pPlayerInfo->fX + (m_pPlayerInfo->fCY + m_tInfo.fCX + 2.f);
	}

	m_tInfo.fY = m_pPlayerInfo->fY;

	Update_Rect();
	return 0;
}

void CAssistantPlayer::Late_Update(void)
{
}

void CAssistantPlayer::Render(HDC hDC)
{
	Rectangle(hDC, m_tRect.left, m_tRect.top, m_tRect.right, m_tRect.bottom);
}

void CAssistantPlayer::Release(void)
{
	m_pPlayerInfo = nullptr;
}

void CAssistantPlayer::SetPlayerInfo(INFO * pPlayerInfo)
{
	m_pPlayerInfo = pPlayerInfo;

	if (m_iLeftRight == AST_LEFT)
	{
		m_tInfo.fX = m_pPlayerInfo->fX - m_tInfo.fCX + 2.f;
	}
	else
	{
		m_tInfo.fX = m_pPlayerInfo->fX + m_tInfo.fCX + 2.f;
	}

	m_tInfo.fY = m_pPlayerInfo->fY;
}

void CAssistantPlayer::SetSpeed(float fSpeed)
{
	m_fSpeed = fSpeed;
}
