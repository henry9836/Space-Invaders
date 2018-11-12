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
#include "game.h"
#include "player.h"
#include "Brick.h"
#include "Ball.h"
#include "utils.h"
#include "backbuffer.h"
#include "framecounter.h"
#include "background.h"
#include <string>
#include <windows.h>
#include <iostream>
#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

// This Include
#include "level.h"

// Static Variables

// Static Function Prototypes

// Implementation

#define CHEAT_BOUNCE_ON_BACK_WALL

using namespace std;

float laserspeed = 10;
bool goLeft = false;
const int kiGap = 5;
float enemyspeed = 0.2f;
float score = 0;
int wave = 1;
float cooldownmax= 85;
float timer;
bool timeractive;
const float fBallVelX = 200.0f;
const float fBallVelY = 75.0f;

CLevel::CLevel()
: m_iBricksRemaining(0)
, m_pPlayer(0)
//, m_pBall(0)
, m_iWidth(0)
, m_iHeight(0)
, m_fpsCounter(0)
{

}

CLevel::~CLevel()
{
    while (m_vecBricks.size() > 0)
    {
        CBrick* pBrick = m_vecBricks[m_vecBricks.size() - 1];

        m_vecBricks.pop_back();

        delete pBrick;
    }

    delete m_pPlayer;
    m_pPlayer = 0;

	delete m_fpsCounter;
	m_fpsCounter = 0;

	delete m_pBackground;
	m_pBackground = 0;

}

bool
CLevel::Initialise(int _iWidth, int _iHeight)
{
    m_iWidth = _iWidth;
    m_iHeight = _iHeight;

	srand((unsigned int)time(NULL));

	m_pBackground = new CBackGround();
	VALIDATE(m_pBackground->Initialise());
	//Set the background position to start from {0,0}
	m_pBackground->SetX((float)m_iWidth / 2);
	m_pBackground->SetY((float)m_iHeight / 2);

    m_pPlayer = new CPlayer();
    VALIDATE(m_pPlayer->Initialise());
	m_pPlayer->SetX(_iWidth / 2.0f);
	m_pPlayer->SetY(_iHeight - (1.5f * m_pPlayer->GetHeight()));

	//m_plaser = new CLaser();
	//VALIDATE(m_plaser->Initialise(m_pPlayer->GetX(), 100, laserspeed));

    // Set the player's position to be centered on the x, 
    // and a little bit up from the bottom of the window.

    const int kiNumofEnemies = 55;
    const int kiStartX = 20;
    
	const int maxWidthSpawn = _iWidth - 100;
	const int maxperRow = 11;

    int iCurrentX = kiStartX;
    int iCurrentY = kiStartX;
	int currentrowelement = 0;

    for (int i = 0; i < kiNumofEnemies; ++i)
    {
        CBrick* pBrick = new CBrick();
        VALIDATE(pBrick->Initialise());

        pBrick->SetX(static_cast<float>(iCurrentX));
        pBrick->SetY(static_cast<float>(iCurrentY));

        iCurrentX += static_cast<int>(pBrick->GetWidth()) + kiGap;

		currentrowelement++;

        if ((iCurrentX > maxWidthSpawn) || (currentrowelement+1 > maxperRow))
        {
            iCurrentX = kiStartX;
			currentrowelement = 0;
            iCurrentY += 20;
        }
		
        m_vecBricks.push_back(pBrick);
    }

    SetBricksRemaining(kiNumofEnemies);
	m_fpsCounter = new CFPSCounter();
	VALIDATE(m_fpsCounter->Initialise());

    return (true);
}

void
CLevel::Draw()
{
	m_pBackground->Draw();
	for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
    {
		if (m_vecBricks[i] != nullptr) {
			m_vecBricks[i]->Draw();
		}
    }
	for (unsigned int i = 0; i < m_vecLasers.size(); ++i)
	{
		if (m_vecLasers[i] != nullptr) {
			m_vecLasers[i]->Draw();
		}
	}

	for (unsigned int i = 0; i < m_vecLasersEnemy.size(); ++i)
	{
		if (m_vecLasersEnemy[i] != nullptr) {
			m_vecLasersEnemy[i]->Draw();
		}
	}

    m_pPlayer->Draw();
	
    DrawScore();
	DrawFPS();
	UpdateScoreText();
}

void CLevel::AleinMove() {
	for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
	{
		int doIWantToShoot = 0;
		doIWantToShoot = rand() % 100000 + 1;
		if (m_vecBricks[i] != nullptr) {
			if (goLeft) {
				if (m_vecBricks[i]->GetX() > kiGap) {
					m_vecBricks[i]->SetX(m_vecBricks[i]->GetX() - enemyspeed);
				}
				else {
					if (m_vecBricks[i]->IsHit()) {

					}
					else {
						goLeft = !goLeft;
						for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
						{
							m_vecBricks[i]->SetY(m_vecBricks[i]->GetY() + 10);
						}
					}
				}
			}

			else {
				if (m_vecBricks[i]->GetX() < m_iWidth - kiGap) {
					m_vecBricks[i]->SetX(m_vecBricks[i]->GetX() + enemyspeed);
				}
				else {
					goLeft = !goLeft;
					for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
					{
						m_vecBricks[i]->SetY(m_vecBricks[i]->GetY() + 10);
					}
				}
			}

			if ((m_vecBricks[i]->GetY()) > 530) {
				if (m_vecBricks[i] != nullptr) {
					if (m_vecBricks[i]->IsHit()) {

					}
					else {
						Beep(1500, 50);
						Beep(1100, 25);
						Beep(1000, 25);
						Beep(700, 25);
						Beep(500, 25);
						Beep(300, 25);
						CGame::GetInstance().GameOverLostToAleins();
					}
				}

			}
			if (!(m_vecBricks[i]->IsHit())) {
				if ((doIWantToShoot < 10005) && (doIWantToShoot > 10000)) {
					m_elaser = new CLaser();
					m_elaser->Initialise(m_vecBricks[i]->GetX(), m_vecBricks[i]->GetY(), 100);
					m_vecLasersEnemy.push_back(m_elaser);
					Beep(300, 25);
				}
			}
		}
	}
}

void CLevel::LaserMoon(float _fDeltaTick) {
	for (unsigned int i = 0; i < m_vecLasers.size(); ++i)
	{
		if (m_vecLasers[i] != nullptr) {
			if (((m_vecLasers[i]->GetY()) < 30) || ((m_vecLasers[i]->GetY()) > 850)) {
				m_vecLasers.erase(m_vecLasers.begin() + i);
				break;
			}
			else {
				m_vecLasers[i]->Draw();
				m_vecLasers[i]->Process(_fDeltaTick, m_vecLasers[i]);
			}
		}
		
	}
	for (unsigned int i = 0; i < m_vecLasersEnemy.size(); ++i)
	{
		if (m_vecLasersEnemy[i] != nullptr) {
			if (((m_vecLasersEnemy[i]->GetY()) < 30) || ((m_vecLasersEnemy[i]->GetY()) > 850)) {
				m_vecLasersEnemy.erase(m_vecLasersEnemy.begin() + i);
				break;
			}
			else {
				m_vecLasersEnemy[i]->Draw();
				m_vecLasersEnemy[i]->Process(_fDeltaTick, m_vecLasersEnemy[i]);
			}
		}

	}

}

bool CLevel::Spawnthebadguys() {
	const int kiNumofEnemies = 55;
	const int kiStartX = 20;
	const int maxWidthSpawn = 400 - 100;
	const int maxperRow = 11;
	int iCurrentX = kiStartX;
	int iCurrentY = kiStartX;
	int currentrowelement = 0;
	enemyspeed = enemyspeed *1.5f;
	m_vecBricks.clear();
	m_vecLasers.clear();
	m_vecLasersEnemy.clear();
	Beep(300, 25);
	Beep(500, 25);
	Beep(700, 25);
	Beep(1000, 25);
	Beep(1100, 25);
	Beep(1500, 50);
	for (int i = 0; i < kiNumofEnemies; ++i)
	{
		CBrick* pBrick = new CBrick();
		VALIDATE(pBrick->Initialise());

		pBrick->SetX(static_cast<float>(iCurrentX));
		pBrick->SetY(static_cast<float>(iCurrentY));

		iCurrentX += static_cast<int>(pBrick->GetWidth()) + kiGap;

		currentrowelement++;

		if ((iCurrentX > maxWidthSpawn) || (currentrowelement + 1 > maxperRow))
		{
			iCurrentX = kiStartX;
			currentrowelement = 0;
			iCurrentY += 20;
		}

		m_vecBricks.push_back(pBrick);
	}
	return true;
}

void
CLevel::Process(float _fDeltaTick)
{

	AleinMove();
	LaserMoon(_fDeltaTick);

	m_pBackground->Process(_fDeltaTick);
	m_pPlayer->Process(_fDeltaTick);
	ProcessLaserCollision();

    ProcessCheckForWin();
	ProcessBallBounds();
	DrawScore();
	CheckforDeath();

    for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
    {
		m_vecBricks[i]->Process(_fDeltaTick);
    }
	
	if (timeractive) {
		if (timer < 0) {
			timeractive = false;
		}
	}
	else {
		if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			m_plaser = new CLaser();
			m_plaser->Initialise(m_pPlayer->GetX(), m_pPlayer->GetY(), -100);
			m_vecLasers.push_back(m_plaser);
			Beep(500, 25);
		}
		timer = cooldownmax;
		timeractive = true;
	}
    
	timer -= 1;

	m_fpsCounter->CountFramesPerSecond(_fDeltaTick);
}

CPlayer* 
CLevel::GetPlayer() const
{
    return (m_pPlayer);
}

void 
CLevel::ProcessBallWallCollision()
{
}

void CLevel::CheckforDeath() {
	if ((m_pPlayer->GetHealth() < 0) || (m_pPlayer->GetHealth() == 0)) {
		Beep(1500, 50);
		Beep(1100, 25);
		Beep(1000, 25);
		Beep(700, 25);
		Beep(500, 25);
		Beep(300, 25);
		CGame::GetInstance().GameOverLostToLives();
	}
}

void CLevel::ProcessLaserCollision() {
	for (int i = 0; i < m_vecLasers.size(); ++i)
	{
		for (int j = 0; j < m_vecBricks.size(); ++j)
		{
			if ((m_vecLasers[i] != nullptr) && (m_vecBricks[j] != nullptr)) {
				if (m_vecBricks[j]->IsHit())
				{

				}
				else {
					float fBallR = m_vecLasers[i]->GetRadius();

					float fBallX = m_vecLasers[i]->GetX();
					float fBallY = m_vecLasers[i]->GetY();

					float fBrickX = m_vecBricks[j]->GetX();
					float fBrickY = m_vecBricks[j]->GetY();

					float fBrickH = m_vecBricks[j]->GetHeight();
					float fBrickW = m_vecBricks[j]->GetWidth();

					if ((fBallX + fBallR > fBrickX - fBrickW / 2) &&
						(fBallX - fBallR < fBrickX + fBrickW / 2) &&
						(fBallY + fBallR > fBrickY - fBrickH / 2) &&
						(fBallY - fBallR < fBrickY + fBrickH / 2))
					{
						m_vecBricks[j]->SetHit(true);
						score += 50;
						Beep(1000, 25);
						m_vecLasers.erase(m_vecLasers.begin() + i);
					}
				}
			}
		}
	}
	for (int i = 0; i < m_vecLasersEnemy.size(); ++i)
	{
			if ((m_vecLasersEnemy[i] != nullptr)) {
					float fBallR = m_vecLasersEnemy[i]->GetRadius();

					float fBallX = m_vecLasersEnemy[i]->GetX();
					float fBallY = m_vecLasersEnemy[i]->GetY();

					float fBrickX = m_pPlayer->GetX();
					float fBrickY = m_pPlayer->GetY();

					float fBrickH = m_pPlayer->GetHeight();
					float fBrickW = m_pPlayer->GetWidth();

					if ((fBallX + fBallR > fBrickX - fBrickW / 2) &&
						(fBallX - fBallR < fBrickX + fBrickW / 2) &&
						(fBallY + fBallR > fBrickY - fBrickH / 2) &&
						(fBallY - fBallR < fBrickY + fBrickH / 2))
					{
						m_pPlayer->SetHealth((m_pPlayer->GetHealth())-1);
						Beep(1300, 25);
						m_vecLasersEnemy.erase(m_vecLasersEnemy.begin() + i);
					}
			}
	}
}


void
CLevel::ProcessBallPlayerCollision()
{
}

void
CLevel::ProcessBallBrickCollision()
{
}

void
CLevel::ProcessCheckForWin()
{
    for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
    {
		if (m_vecBricks[i] != nullptr) {
			if (!m_vecBricks[i]->IsHit())
			{
				return;
			}
		}
    }
	wave += 1;
	Spawnthebadguys();//CGame::GetInstance().GameOverWon();
}

void
CLevel::ProcessBallBounds()
{
}

int 
CLevel::GetBricksRemaining() const
{
    return (m_iBricksRemaining);
}

void 
CLevel::SetBricksRemaining(int _i)
{
    m_iBricksRemaining = _i;
    UpdateScoreText();
}

void
CLevel::DrawScore()
{
    HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();

    const int kiX = 0;
    const int kiY = m_iHeight - 14;
	SetBkMode(hdc, TRANSPARENT);
    
    TextOutA(hdc, kiX, kiY, m_strScore.c_str(), static_cast<int>(m_strScore.size()));
	SetTextColor(hdc, RGB(255, 255, 255));


	DisplayHeath();
	TextOutA(hdc, kiX, kiY-20, m_health.c_str(), static_cast<int>(m_health.size()));
	SetTextColor(hdc, RGB(255, 255, 255));

	DisplayScore();
	TextOutA(hdc, kiX, kiY - 40, m_score.c_str(), static_cast<int>(m_score.size()));
	SetTextColor(hdc, RGB(255, 255, 255));
}

void 
CLevel::UpdateScoreText()
{
    m_strScore = "Wave: ";

    m_strScore += ToString(wave);
}

void CLevel::DisplayHeath() {

	m_health = "Lives: ";

	m_health += ToString(m_pPlayer->GetHealth());

}

void CLevel::DisplayScore() {

	m_score = "Score: ";

	m_score += ToString(score);

}

void 
CLevel::DrawFPS()
{
	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC(); 

	m_fpsCounter->DrawFPSText(hdc, m_iWidth, m_iHeight);

}