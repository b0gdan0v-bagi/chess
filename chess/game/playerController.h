#pragma once
#include <memory>
#include "player.h"
#include "Utils.h"

class Player;

class PlayerController
{
	eGameStyle mGameStyle;
	Player* player_1;
	Player* player_2;

	Player* selectedPlayer;
	Field* mField;
	void CreatePlayers();

	float mDelay, mCount;

public:
	PlayerController(Field* field);
	Player* GetSelectedPlayer() { return selectedPlayer; }
	void OnMoveEnded();
	void Update(const float dt);
	/*bool HumanControl() { return selectedPlayer->IsHuman(); }
	ePlayerColor GetCurrentPlayerColor() { return selectedPlayer->GetPlayerColor(); }*/
	~PlayerController();
};