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
#include "Sprite.h"
#include "utils.h"

// This Include
#include "entity.h"

// Static Variables

// Static Function Prototypes

// Implementation

CEntity::CEntity()
: m_fX(0.0f)
, m_fY(0.0f)
{

}

CEntity::~CEntity()
{
    delete m_pSprite;
    m_pSprite = 0;
}

bool
CEntity::Initialise(const int _kiSpriteID, const int _kiMaskID)
{
	try {
		m_pSprite = new CSprite();
		VALIDATE(m_pSprite->Initialise(_kiSpriteID, _kiMaskID));
	}
	catch (...) {
		OutputDebugString(L"entity.cpp exception in Initialise() caught and handled :D");
	}
    return (true);
}

void
CEntity::Draw()
{
	try {
		m_pSprite->Draw();
	}
	catch (...) {
		OutputDebugString(L"entity.cpp exception in Draw() caught and handled :D");
	}
}

void
CEntity::Process(float _fDeltaTick)
{
	try {
		m_pSprite->SetX(static_cast<int>(m_fX));
		m_pSprite->SetY(static_cast<int>(m_fY));

		m_pSprite->Process(_fDeltaTick);
	}
	catch (...) {
		OutputDebugString(L"entity.cpp exception in Process() caught and handled :D");
	}
}

float 
CEntity::GetX() const
{
	try {
		if (this == nullptr) {
			return 0;
		}
		else {
			return (m_fX);
		}
	}
	catch (...) {
		OutputDebugString(L"entity.cpp exception in GetX() caught and handled :D");
		return 0.0;
	}
}

float 
CEntity::GetY() const
{
	try {
		return (m_fY);
	}
	catch (...) {
		OutputDebugString(L"entity.cpp exception in GetY() caught and handled :D");
		return 0.0;
	}
}

float 
CEntity::GetWidth() const
{
    return (static_cast<float>(m_pSprite->GetWidth()));
}

float 
CEntity::GetHeight() const
{
    return (static_cast<float>(m_pSprite->GetHeight()));
}

void
CEntity::SetX(float _f)
{
	try {
		m_fX = _f;
		m_pSprite->SetX(_f);
	}
	catch (...) {
		OutputDebugString(L"entity.cpp exception in SetX() caught and handled :D");
	}
}

void
CEntity::SetY(float _f)
{
	try {
		m_fY = _f;
		m_pSprite->SetY(_f);
	}
	catch (...) {
		OutputDebugString(L"entity.cpp exception in SetY() caught and handled :D");
	}
}