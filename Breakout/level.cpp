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
#include <stdio.h>      
#include <stdlib.h> 
#include <time.h>       

// This Include
#include "level.h"

// Static Variables

// Static Function Prototypes

// Implementation

#define CHEAT_BOUNCE_ON_BACK_WALL

using namespace std;

bool goLeft = false;
const int kiGap = 5;
float enemyspeed = 0.2f;
float score = 0;
int wave = 1;
float cooldownmax= 65;
float timer;
float laserspeed = 100;
bool timeractive;
const float fBallVelX = 200.0f;
const float fBallVelY = 75.0f;
bool godmode = false;
bool cooldownon = true;
bool DebugNextLvl = false;
bool DebugShoot_b = false;

CLevel::CLevel()
: m_iBricksRemaining(0)
, m_pPlayer(0)
, m_iWidth(0)
, m_iHeight(0)
, m_fpsCounter(0)
{

}

CLevel::~CLevel()
{
    while (m_vecBricks.size() > 0)
    {
        CBrick* pBrick = m_vecBricks.at(m_vecBricks.size() - 1);

        m_vecBricks.pop_back();

        delete pBrick;
    }

	while (m_vecLasers.size() > 0)
	{
		CLaser* m_vecLaser = m_vecLasers.at(m_vecLasers.size() - 1);

		m_vecLasers.pop_back();

		delete m_vecLaser;
	}

	while (m_vecLasersEnemy.size() > 0)
	{
		CLaser* m_elaser = m_vecLasersEnemy.at(m_vecLasersEnemy.size() - 1);

		m_vecLasersEnemy.pop_back();

		delete m_elaser;
	}

	delete m_space_Ship;
	m_space_Ship = 0;

    delete m_pPlayer;
    m_pPlayer = 0;

	delete m_fpsCounter;
	m_fpsCounter = 0;

	delete m_pBackground;
	m_pBackground = 0;

}

bool CLevel::DebugShoot() {

	for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
	{
		if (!(m_vecBricks.at(i)->IsHit())) {
				m_elaser = new CLaser();
				m_elaser->Initialise(m_vecBricks.at(i)->GetX(), m_vecBricks.at(i)->GetY(), laserspeed);
				m_vecLasersEnemy.push_back(m_elaser);
		}
	}
	return false;
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

	m_space_Ship = new CSpaceShip();
	m_space_Ship->Initialise(2000);

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

	int numofSheilds = 4;
	iCurrentX = 50;
	int kiGap = 50;
	for (int i = 0; i < numofSheilds; i++)
	{
		CShield* m_sheild = new CShield();
		VALIDATE(m_sheild->Initialise());

		m_sheild->SetX(iCurrentX);
		m_sheild->SetY((_iHeight - (1.5f * m_pPlayer->GetHeight())) - 50);

		m_sheilds.push_back(m_sheild);

		iCurrentX += (static_cast<int>(m_sheild->GetWidth()) + kiGap);
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
		if (m_vecBricks.at(i) != nullptr) {
			m_vecBricks.at(i)->Draw();
		}
    }
	for (unsigned int i = 0; i < m_vecLasers.size(); ++i)
	{
		if (m_vecLasers.at(i) != nullptr) {
			m_vecLasers.at(i)->Draw();
		}
	}
	for (unsigned int i = 0; i < m_vecLasersEnemy.size(); ++i)
	{
		if (m_vecLasersEnemy.at(i) != nullptr) {
			m_vecLasersEnemy.at(i)->Draw();
		}
	}

	for (unsigned int i = 0; i < m_sheilds.size(); ++i)
	{
		if (m_sheilds.at(i) != nullptr) {
			m_sheilds.at(i)->Draw();
		}
	}

    m_pPlayer->Draw();
	m_space_Ship->Draw();
	
    DrawScore();
	DrawFPS();
	UpdateScoreText();
}

void CLevel::AleinMove() {
	for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
	{
		int doIWantToShoot = 0;
		doIWantToShoot = rand() % 100000 + 1;
		if (m_vecBricks.at(i) != nullptr) {
			if (goLeft) {
				if (m_vecBricks.at(i)->GetX() > kiGap) {
					m_vecBricks.at(i)->SetX(m_vecBricks.at(i)->GetX() - enemyspeed);
				}
				else {
					if (m_vecBricks.at(i)->IsHit()) {

					}
					else {
						goLeft = !goLeft;
						for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
						{
							m_vecBricks.at(i)->SetY(m_vecBricks.at(i)->GetY() + 10);
						}
					}
				}
			}

			else {
				if (m_vecBricks.at(i)->GetX() < m_iWidth - kiGap) {
					m_vecBricks.at(i)->SetX(m_vecBricks.at(i)->GetX() + enemyspeed);
				}
				else {
					goLeft = !goLeft;
					for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
					{
						m_vecBricks.at(i)->SetY(m_vecBricks.at(i)->GetY() + 10);
					}
				}
			}

			if ((m_vecBricks.at(i)->GetY()) > 530) { //when aliens go below player
				if (m_vecBricks.at(i) != nullptr) {
					if (m_vecBricks.at(i)->IsHit()) {

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
			if (!(m_vecBricks.at(i)->IsHit())) {
				if ((doIWantToShoot < 10005) && (doIWantToShoot > 10000)) {
					m_elaser = new CLaser();
					m_elaser->Initialise(m_vecBricks.at(i)->GetX(), m_vecBricks.at(i)->GetY(), laserspeed);
					m_vecLasersEnemy.push_back(m_elaser);
					Beep(300, 25);
				}
			}
		}
	}
}

void CLevel::LaserMoon(float _fDeltaTick) {
	try {
		for (unsigned int i = 0; i < m_vecLasers.size(); ++i)
		{
			if (m_vecLasers.at(i) != nullptr) {
				if (((m_vecLasers.at(i)->GetY()) < 30) || ((m_vecLasers.at(i)->GetY()) > 850)) {
					m_vecLasers.erase(m_vecLasers.begin() + i);
					break;
				}
				else {
					m_vecLasers.at(i)->Draw();
					m_vecLasers.at(i)->Process(_fDeltaTick, m_vecLasers.at(i));
				}
			}

		}
	}
	catch (...) {
		OutputDebugString(L"level.cpp exception caught in Laser Moon ERROR:1");
	}
	try {
		for (unsigned int i = 0; i < m_vecLasersEnemy.size(); ++i)
		{
			if (m_vecLasersEnemy.at(i) != nullptr) {
				if (((m_vecLasersEnemy.at(i)->GetY()) < 30) || ((m_vecLasersEnemy.at(i)->GetY()) > 850)) {
					m_vecLasersEnemy.erase(m_vecLasersEnemy.begin() + i);
					break;
				}
				else {
					m_vecLasersEnemy.at(i)->Draw();
					m_vecLasersEnemy.at(i)->Process(_fDeltaTick, m_vecLasersEnemy.at(i));
				}
			}

		}
	}
	catch (...) {
		OutputDebugString(L"level.cpp exception caught in Laser Moon ERROR:2");
	}

}

bool CLevel::Spawnthebadguys() {
	try {
		const int kiNumofEnemies = 55;
		const int kiStartX = 20;
		const int maxWidthSpawn = 400 - 100;
		const int maxperRow = 11;
		int iCurrentX = kiStartX;
		int iCurrentY = kiStartX;
		int currentrowelement = 0;
		enemyspeed = enemyspeed * 1.5f;
		m_vecBricks.clear();
		m_vecLasers.clear();
		m_vecLasersEnemy.clear();
		m_pPlayer->SetHealth(3);
		Beep(300, 25);
		Beep(500, 25);
		Beep(700, 25);
		Beep(1000, 25);
		Beep(1100, 25);
		Beep(1500, 50);

		/* Spawn Spaceship If I feel like it :P*/
		int spawnAlien = 0;
		spawnAlien = rand() % 100 + 1;
		if (spawnAlien > 75) {
			int i;
			i = rand() % 10000 + 1;
			m_space_Ship->SpawnMe(i);
			Beep(1500, 150);
			Beep(1750, 150);
			Beep(1950, 150);
			Beep(1500, 150);
			Beep(1750, 150);
			Beep(1950, 150);
			Beep(1500, 150);
			Beep(1750, 150);
			Beep(1950, 150);
		}
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
	}
	catch (...) {
		OutputDebugString(L"level.cpp exception in Spawnthebadguys() caught and handled :D");
	}
	return true;
}

void
CLevel::Process(float _fDeltaTick)
{
	try {
		AleinMove();
		LaserMoon(_fDeltaTick);

		m_pBackground->Process(_fDeltaTick);
		m_pPlayer->Process(_fDeltaTick);
		m_space_Ship->Process(_fDeltaTick);
		ProcessLaserCollision();

		ProcessCheckForWin();
		ProcessBallBounds();
		DrawScore();
		CheckforDeath();

		for (unsigned int i = 0; i < m_vecBricks.size(); ++i)
		{
			m_vecBricks.at(i)->Process(_fDeltaTick);
		}

		if ((timeractive) && (cooldownon)) {
			if (timer < 0) {
				timeractive = false;
			}
		}
		else {
			try {
				if (GetAsyncKeyState(VK_SPACE) & 0x8000)
				{
					m_plaser = new CLaser();
					m_plaser->Initialise(m_pPlayer->GetX(), m_pPlayer->GetY(), -laserspeed);
					m_vecLasers.push_back(m_plaser);
					Beep(500, 25);
				}
				timer = cooldownmax;
				timeractive = true;
			}
			catch (...) {

			}
		}

		timer -= 1;

		m_fpsCounter->CountFramesPerSecond(_fDeltaTick);

		if (DebugNextLvl) {
			Spawnthebadguys();
			DebugNextLvl = false;
			wave++;
		}

		if (DebugShoot_b) {
			DebugShoot();
			DebugShoot_b = false;
		}
	}
	catch (...) {
		OutputDebugString(L"level.cpp exception in Process() caught and handled :D");
	}
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
		if (!godmode) {
			Beep(1500, 50);
			Beep(1100, 25);
			Beep(1000, 25);
			Beep(700, 25);
			Beep(500, 25);
			Beep(300, 25);
			CGame::GetInstance().GameOverLostToLives();
		}
	}
}

void CLevel::ProcessLaserCollision() {
	for (int i = 0; i < m_vecLasers.size(); ++i)
	{
		for (int j = 0; j < m_vecBricks.size(); ++j)
		{
			if ((m_vecLasers.at(i) != nullptr) && (m_vecBricks.at(j) != nullptr)) {
				if (m_vecBricks.at(j)->IsHit())
				{

				}
				else {
					try {
						float fBallR = m_vecLasers.at(i)->GetRadius();

						float fBallX = m_vecLasers.at(i)->GetX();
						float fBallY = m_vecLasers.at(i)->GetY();

						float fBrickX = m_vecBricks.at(j)->GetX();
						float fBrickY = m_vecBricks.at(j)->GetY();

						float fBrickH = m_vecBricks.at(j)->GetHeight();
						float fBrickW = m_vecBricks.at(j)->GetWidth();

						if ((fBallX + fBallR > fBrickX - fBrickW / 2) &&
							(fBallX - fBallR < fBrickX + fBrickW / 2) &&
							(fBallY + fBallR > fBrickY - fBrickH / 2) &&
							(fBallY - fBallR < fBrickY + fBrickH / 2))
						{
							m_vecBricks.at(j)->SetHit(true);
							score += 50;
							Beep(1000, 25);
							m_vecLasers.erase(m_vecLasers.begin() + i);
						}
					}
					catch (...){
						OutputDebugString(L"level.cpp exception in ProcessLaserCollision() caught and handled :D");
					}
				}
			}
		}
	}
	for (int i = 0; i < m_vecLasers.size(); ++i)
	{
		for (int j = 0; j < m_sheilds.size(); ++j)
		{
			if ((m_vecLasers.at(i) != nullptr) && (m_sheilds.at(j) != nullptr)) {
				if (m_sheilds.at(j)->IsHit())
				{

				}
				else {
					try {
						float fBallR = m_vecLasers.at(i)->GetRadius();

						float fBallX = m_vecLasers.at(i)->GetX();
						float fBallY = m_vecLasers.at(i)->GetY();

						float fBrickX = m_sheilds.at(j)->GetX();
						float fBrickY = m_sheilds.at(j)->GetY();

						float fBrickH = m_sheilds.at(j)->GetHeight();
						float fBrickW = m_sheilds.at(j)->GetWidth();

						if ((fBallX + fBallR > fBrickX - fBrickW / 2) &&
							(fBallX - fBallR < fBrickX + fBrickW / 2) &&
							(fBallY + fBallR > fBrickY - fBrickH / 2) &&
							(fBallY - fBallR < fBrickY + fBrickH / 2))
						{
							m_sheilds.at(j)->setHealth((m_sheilds.at(j)->getHealth()) - 1);
							score += 50;
							Beep(450, 25);
							if (m_sheilds.at(j)->getHealth() <= 0) {
								m_sheilds.at(j)->SetHit(true);
							}
							m_vecLasers.erase(m_vecLasers.begin() + i);
						}
					}
					catch (...) {
						OutputDebugString(L"level.cpp exception in ProcessLaserCollision() caught and handled :D");
					}
				}
			}
		}
	}
	for (int i = 0; i < m_vecLasersEnemy.size(); ++i)
	{
		for (int j = 0; j < m_sheilds.size(); ++j)
		{
			if ((m_vecLasersEnemy.at(i) != nullptr) && (m_sheilds.at(j) != nullptr)) {
				if (m_sheilds.at(j)->IsHit())
				{

				}
				else {
					try {
						float fBallR = m_vecLasersEnemy.at(i)->GetRadius();

						float fBallX = m_vecLasersEnemy.at(i)->GetX();
						float fBallY = m_vecLasersEnemy.at(i)->GetY();

						float fBrickX = m_sheilds.at(j)->GetX();
						float fBrickY = m_sheilds.at(j)->GetY();

						float fBrickH = m_sheilds.at(j)->GetHeight();
						float fBrickW = m_sheilds.at(j)->GetWidth();

						if ((fBallX + fBallR > fBrickX - fBrickW / 2) &&
							(fBallX - fBallR < fBrickX + fBrickW / 2) &&
							(fBallY + fBallR > fBrickY - fBrickH / 2) &&
							(fBallY - fBallR < fBrickY + fBrickH / 2))
						{
							m_sheilds.at(j)->setHealth((m_sheilds.at(j)->getHealth()) - 1);
							score += 50;
							Beep(450, 25);
							if (m_sheilds.at(j)->getHealth() <= 0) {
								m_sheilds.at(j)->SetHit(true);
							}
							m_vecLasersEnemy.erase(m_vecLasersEnemy.begin() + i);
						}
					}
					catch (...) {
						OutputDebugString(L"level.cpp exception in ProcessLaserCollision() caught and handled :D");
					}
				}
			}
		}
	}
	for (int i = 0; i < m_vecLasersEnemy.size(); ++i)
	{
			if ((m_vecLasersEnemy.at(i) != nullptr)) {
				try {
					float fBallR = m_vecLasersEnemy.at(i)->GetRadius();

					float fBallX = m_vecLasersEnemy.at(i)->GetX();
					float fBallY = m_vecLasersEnemy.at(i)->GetY();

					float fBrickX = m_pPlayer->GetX();
					float fBrickY = m_pPlayer->GetY();

					float fBrickH = m_pPlayer->GetHeight();
					float fBrickW = m_pPlayer->GetWidth();

					if ((fBallX + fBallR > fBrickX - fBrickW / 2) &&
						(fBallX - fBallR < fBrickX + fBrickW / 2) &&
						(fBallY + fBallR > fBrickY - fBrickH / 2) &&
						(fBallY - fBallR < fBrickY + fBrickH / 2))
					{
						m_pPlayer->SetHealth((m_pPlayer->GetHealth()) - 1);
						Beep(1300, 25);
						m_vecLasersEnemy.erase(m_vecLasersEnemy.begin() + i);
					}
				}
				catch (...) {
					OutputDebugString(L"level.cpp exception in ProcessLaserCollision() caught and handled :D");
				}
			}
	}
	for (int i = 0; i < m_vecLasers.size(); ++i)
	{
		if ((m_vecLasers.at(i) != nullptr)) {
			try {
				float fBallR = m_vecLasers.at(i)->GetRadius();

				float fBallX = m_vecLasers.at(i)->GetX();
				float fBallY = m_vecLasers.at(i)->GetY();

				float fBrickX = m_space_Ship->GetX();
				float fBrickY = m_space_Ship->GetY();

				float fBrickH = m_space_Ship->GetHeight();
				float fBrickW = m_space_Ship->GetWidth();

				if ((fBallX + fBallR > fBrickX - fBrickW / 2) &&
					(fBallX - fBallR < fBrickX + fBrickW / 2) &&
					(fBallY + fBallR > fBrickY - fBrickH / 2) &&
					(fBallY - fBallR < fBrickY + fBrickH / 2))
				{
					m_space_Ship->SetHit(true);
					Beep(1300, 25);
					Beep(1500, 25);
					Beep(1700, 25);
					score += 1500;
					m_vecLasers.erase(m_vecLasers.begin() + i);
				}
			}
			catch (...) {
				OutputDebugString(L"level.cpp exception in ProcessLaserCollision() caught and handled :D");
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
		if (m_vecBricks.at(i) != nullptr) {
			if (!m_vecBricks.at(i)->IsHit())
			{
				return;
			}
		}
    }
	wave += 1;
	Spawnthebadguys();
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
	try {
		HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();

		const int kiX = 0;
		const int kiY = m_iHeight - 14;
		SetBkMode(hdc, TRANSPARENT);

		TextOutA(hdc, kiX, kiY, m_strScore.c_str(), static_cast<int>(m_strScore.size()));
		SetTextColor(hdc, RGB(255, 255, 255));

		// vector.at(3]
		// vector.at(3)

		DisplayHeath();
		TextOutA(hdc, kiX, kiY - 20, m_health.c_str(), static_cast<int>(m_health.size()));
		SetTextColor(hdc, RGB(255, 255, 255));

		DisplayScore();
		TextOutA(hdc, kiX, kiY - 40, m_score.c_str(), static_cast<int>(m_score.size()));
		SetTextColor(hdc, RGB(255, 255, 255));
	}
	catch (...) {
		OutputDebugString(L"level.cpp exception in DrawScore() caught and handled :D");
	}
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

void GodMode()
{
	try {
		godmode = !godmode;
		OutputDebugString(L"GODMODE");
	}
	catch (...) {

	}
}

void nocooldown(){
	try
	{
		cooldownon = !cooldownon;
		OutputDebugString(L"laser galoor");
	}
	catch(...){
	}
}

void nextwave()
{
	try
	{
		DebugNextLvl = true;
		OutputDebugString(L"going up?");
	}
	catch (...) {
	}
}

void spawnUFO()
{
}

void laserspeedadd()
{
	try {
		laserspeed += 10;
		OutputDebugString(L"moar lase speed");
	}
	catch (...) {

	}
}

void laserspeeddown()
{
	try {
		laserspeed -= 10;
		OutputDebugString(L"less laser speed");
	}
	catch (...) {

	}
}

void aleinspeedup()
{
	try {
		enemyspeed += 0.5;
		OutputDebugString(L"moar enemy speed");
	}
	catch (...) {

	}
}

void aleinspeeddown()
{
	try {
		enemyspeed -= 0.5;
		OutputDebugString(L"less enemy speed");
	}
	catch (...) {

	}
}

void everybodyshoot()
{
	try {
		DebugShoot_b = true;
		OutputDebugString(L"FIRE!");
	}
	catch (...) {

	}
	
}
