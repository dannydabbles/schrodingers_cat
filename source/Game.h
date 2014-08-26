//
//
//
//   Project : Schrödinger's cat
//   File Name : Game.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_GAME_H)
#define _GAME_H

#include "GameState.h"
#include "MapManager.h"
#include "UserInterfaceManager.h"
#include "PlayerProfile.h"

class Game
{
public:
   Game();
	
   void Draw();
   void Init();
   void ShutDown();
	void Update(uint64 time);
	
private:
	LaserPointer* lpFinger;
   MapManager* mmController;
   UserInterfaceManager* uimManager;
	bool bUpdated;
};

#endif  //_GAME_H
