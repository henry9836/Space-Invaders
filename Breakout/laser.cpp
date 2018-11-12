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

// This Includes
#include "laser.h"

// Static Variables

// Static Function Prototypes

// Implementation

CLaser::CLaser()
:m_fVelocityY(0.0f),
m_fVelocityX(0.0f)
{

}

CLaser::~CLaser()
{

}

bool
CLaser::Initialise(float _fPosX, float _fPosY, float _fVelocityY)
{
	VALIDATE(CEntity::Initialise(IDB_BITMAP7, IDB_BITMAP8));

	m_fX = _fPosX;
	m_fY = _fPosY;

	m_fVelocityX = 0;
	m_fVelocityY = _fVelocityY;

	return (true);
}

void
CLaser::Draw()
{
	CEntity::Draw();
}

void
CLaser::Process(float _fDeltaTick, CLaser* me)
{
	m_fX += m_fVelocityX * _fDeltaTick;
	m_fY += m_fVelocityY * _fDeltaTick;

	CEntity::Process(_fDeltaTick);
}

float
CLaser::GetVelocityX() const
{
	return (m_fVelocityX);
}

float
CLaser::GetVelocityY() const
{
	return (m_fVelocityY);
}

void
CLaser::SetVelocityX(float _fX)
{
	m_fVelocityX = _fX;
}

void
CLaser::SetVelocityY(float _fY)
{
	m_fVelocityY = _fY;
}

void CLaser::amBady()
{
	amBadGuy = true;
}

bool CLaser::getBad() {
	return amBadGuy;
}

float
CLaser::GetRadius() const
{
	return (GetWidth() / 2.0f);
}
