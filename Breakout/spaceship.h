
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//
#pragma once
#if !defined(__SPACESHIP_H__)
#define __SPACESHIP_H__

// Library Includes

// Local Includes
#include "entity.h"

// Types

// Constants

// Prototypes

class CSpaceShip : public CEntity
{
	// Member Functions
public:
	CSpaceShip();
	virtual ~CSpaceShip();

	virtual bool Initialise(float m_x);

	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	void SetHit(bool _b);
	bool IsHit() const;

	void SpawnMe(int m_x);

protected:

private:
	CSpaceShip(const CSpaceShip& _kr);
	CSpaceShip& operator= (const CSpaceShip& _kr);

	// Member Variables
public:

protected:
	bool m_bHit;

private:

};


#endif    // __BRICK_H__