//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: player.cpp
// Description	: controls player
// Author		: Henry Oliver
// Mail			: henry.oliver@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "resource.h"
#include "utils.h"

// This Include
#include "player.h"
#include "laser.h"
#include "Game.h"
#include "player.h"
#include "Brick.h"
#include "Ball.h"
#include "utils.h"
#include "backbuffer.h"
#include "framecounter.h"
#include "background.h"


// Static Variables

// Static Function Prototypes

// Implementation

CPlayer::CPlayer()
{

}

CPlayer::~CPlayer()
{

}

bool
CPlayer::Initialise()
{
    VALIDATE(CEntity::Initialise(IDB_BITMAP1, IDB_BITMAP2));

    return (true);
}

void
CPlayer::Draw()
{
    CEntity::Draw();
}

void
CPlayer::Process(float _fDeltaTick)
{
	try {
		float fHalfPaddleW = static_cast<float>(m_pSprite->GetWidth() / 2.0);

		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			m_fX += 400.0f * _fDeltaTick;
		}
		else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_fX -= 400.0f * _fDeltaTick;
		}
		if (m_fX - fHalfPaddleW <= 0)
		{
			m_fX = fHalfPaddleW;
		}
		else if (m_fX + fHalfPaddleW >= 385)
		{
			m_fX = 385 - fHalfPaddleW;
		}
	}
	catch (...) {
		OutputDebugString(L"Player.cpp exception caught and handled :D");
	}
	CEntity::Process(_fDeltaTick);
}

int CPlayer::GetHealth()
{
	return health;
}

void CPlayer::SetHealth(int in)
{
	health = in;
}
