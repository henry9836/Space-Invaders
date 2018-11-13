//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: background.h
// Description	: it holds info for the background image
// Author		: Henry Oliver
// Mail			: henry.oliver@mediadesign.school.nz
//


#pragma once

#if !defined(__BACKGROUND_H__)
#define __BACKGROUND_H__

// Library Includes

// Local Includes
#include "entity.h"

// Types

// Constants

// Prototypes
class CSprite;

class CBackGround : public CEntity
{
	// Member Functions
public:
	CBackGround();
	virtual ~CBackGround();

	virtual bool Initialise();

	virtual void Draw();
	virtual void Process(float _fDeltaTick);


protected:

private:
	CBackGround(const CBackGround& _kr);
	CBackGround& operator= (const CBackGround& _kr);

	// Member Variables
public:

protected:


private:

};

#endif