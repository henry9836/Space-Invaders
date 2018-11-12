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

#if !defined(__LASER_H__)
#define __LASER_H__

// Library Includes

// Local Includes
#include "entity.h"

// Types

// Constants

// Prototypes
class CSprite;

class CLaser : public CEntity
{
	// Member Functions
public:
	CLaser();
	virtual ~CLaser();

	virtual bool Initialise(float _fPosX, float _fPosY, float _fVelocityY);

	virtual void Draw();
	void Process(float _fDeltaTick, CLaser * me);

	float GetVelocityX() const;
	float GetVelocityY() const;
	void SetVelocityX(float _fX);
	void SetVelocityY(float _fY);
	void amBady();
	bool getBad();

	float GetRadius() const;

protected:

private:
	CLaser(const CLaser& _kr);
	CLaser& operator= (const CLaser& _kr);

	// Member Variables
public:

protected:
	float m_fVelocityX;
	float m_fVelocityY;
	bool amBadGuy = false;

private:

};


#endif    // __BALL_H__
