#pragma once
#include <memory>
#include "player.h"

class PlayerController
{
	eGameStyle mGameStyle;
	Player* player_1;
	Player* player_2;

	Player* selectedPlayer;
	Field* mField;
	void CreatePlayers();

public:
	PlayerController(Field* field);
	~PlayerController();
};