
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "resource.h"
#include "utils.h"
#include "spaceship.h"

// This Include

// Static Variables

// Static Function Prototypes

// Implementation

CSpaceShip::CSpaceShip()
	: m_bHit(false)
{

}

CSpaceShip::~CSpaceShip()
{

}

bool
CSpaceShip::Initialise(float m_x)
{
	VALIDATE(CEntity::Initialise(IDB_BITMAP9, IDB_BITMAP10));
	m_fX = m_x;
	m_fY = 15;
	return (true);
}

void
CSpaceShip::Draw()
{
	if (!m_bHit)
	{
		CEntity::Draw();
	}
}

void
CSpaceShip::Process(float _fDeltaTick)
{

	if (m_fX < 600) {
		m_fX += 1;
	}

	if (!m_bHit)
	{
		CEntity::Process(_fDeltaTick);
	}
}

void
CSpaceShip::SetHit(bool _b)
{
	m_bHit = _b;
}

bool
CSpaceShip::IsHit() const
{
	return (m_bHit);
}

void CSpaceShip::SpawnMe(int m_x) {
	m_bHit = false;
	m_fX = m_x;
	m_fY = 15;
}

