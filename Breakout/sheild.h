#pragma once

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

#if !defined(__SHEILD_H__)
#define __SHEILD_H__

// Library Includes

// Local Includes
#include "entity.h"

// Types

// Constants

// Prototypes

class CShield : public CEntity
{
	// Member Functions
public:
	CShield();
	virtual ~CShield();

	virtual bool Initialise();

	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	void SetHit(bool _b);
	bool IsHit() const;

	void setHealth(int _health);
	int getHealth();
	void S_X(float _f);
	void S_Y(float _f);
protected:

private:
	CShield(const CShield& _kr);
	CShield& operator= (const CShield& _kr);

	// Member Variables
public:

protected:
	bool m_bHit;

private:

};


#endif    // __BRICK_H__

