//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: player.h
// Description	: player class stored here
// Author		: Henry Oliver
// Mail			: henry.oliver@mediadesign.school.nz
//


#pragma once

#if !defined(__PLAYER_H__)
#define __PLAYER_H__

// Library Includes

// Local Includes
#include "entity.h"
#include "Sprite.h"
#include "laser.h"

// Types

// Constants

// Prototypes
class CPlayer : public CEntity
{
    // Member Functions
public:
	CPlayer();
    virtual ~CPlayer();

    virtual bool Initialise();

    virtual void Draw();
	virtual void Process(float _fDeltaTick); \

	int GetHealth();
	void SetHealth(int in);

protected:
	CLaser * m_pLaser;

private:
	CPlayer(const CPlayer& _kr);
	CPlayer& operator= (const CPlayer& _kr);

    // Member Variables
public:
	int health = 3;
protected:

private:

};

#endif    // __PADDLE_H__
