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

// This Include
#include "sheild.h"

// Static Variables

// Static Function Prototypes

// Implementation

int health = 10;

CShield::CShield()
	: m_bHit(false)
{

}

CShield::~CShield()
{

}

bool
CShield::Initialise()
{
	VALIDATE(CEntity::Initialise(IDB_BITMAP11, IDB_BITMAP12));

	return (true);
}

void
CShield::Draw()
{
	if (!m_bHit)
	{
		CEntity::Draw();
	}
}

void
CShield::Process(float _fDeltaTick)
{
	if (!m_bHit)
	{
		CEntity::Process(_fDeltaTick);
	}
}

void
CShield::SetHit(bool _b)
{
	m_bHit = _b;
}

bool
CShield::IsHit() const
{
	return (m_bHit);
}

void CShield::setHealth(int _health)
{
	health = _health;
}

int CShield::getHealth()
{
	return health;
}

void
CShield::S_X(float _f)
{
	try {
		m_fX = _f;
	}
	catch (...) {
	}
}

void
CShield::S_Y(float _f)
{
	try {
		m_fY = _f;
	}
	catch (...) {
	}
}