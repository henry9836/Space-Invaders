//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: level.h
// Description	: the game level info and class stored here
// Author		: Henry Oliver
// Mail			: henry.oliver@mediadesign.school.nz
//



#pragma once

#if !defined(__LEVEL_H__)
#define __LEVEL_H__

// Library Includes
#include <vector>
#include <string>

// Local Includes
#include "laser.h"
#include "spaceship.h"
#include "sheild.h"
// Types

// Constants

// Prototypes
class CBall;
class CPlayer;
class CSheild;
class CBrick;
class CFPSCounter;
class CBackGround;


class CLevel
{
    // Member Functions
public:
    CLevel();
    virtual ~CLevel();

	bool DebugShoot();

    virtual bool Initialise(int _iWidth, int _iHeight);

    virtual void Draw();
	void AleinMove();
	void LaserMoon(float _fDeltaTick);
	bool Spawnthebadguys();
    virtual void Process(float _fDeltaTick);

    CPlayer* GetPlayer() const;

    int GetBricksRemaining() const;

protected:
    void ProcessBallWallCollision();
	void CheckforDeath();
	void ProcessLaserCollision();
	//void ProcessPlayerWallCollison();
    void ProcessBallPlayerCollision();
    void ProcessBallBrickCollision();

	void ProcessCheckForWin();
	//void ProcessCheckForLose();
    void ProcessBallBounds();

    void UpdateScoreText();
    void DrawScore();
	void DrawFPS();
	void DisplayHeath();
	void DisplayScore();
    void SetBricksRemaining(int _i);

private:
    CLevel(const CLevel& _kr);
    CLevel& operator= (const CLevel& _kr);

    // Member Variables
public:

protected:
	CBackGround* m_pBackground;
    CBall* m_pBall;
    CPlayer* m_pPlayer;
	CLaser* m_plaser;
	CLaser* m_elaser;
	CShield* m_sheild;
	CSpaceShip* m_space_Ship;
    std::vector<CBrick*> m_vecBricks;
	std::vector<CLaser*> m_vecLasers;
	std::vector<CLaser*> m_vecLasersEnemy;
	std::vector<CShield*> m_sheilds;
	CFPSCounter* m_fpsCounter;

    int m_iWidth;
    int m_iHeight;

    int m_iBricksRemaining;

    std::string m_strScore;
	std::string m_health;
	std::string m_score;

private:

};

void GodMode();
void nocooldown();
void nextwave();
void spawnUFO();
void laserspeedadd();
void laserspeeddown();
void aleinspeedup();
void aleinspeeddown();
void everybodyshoot();

#endif    // __LEVEL_H__


