#pragma once
#include <memory>
#include "player.h"
#include "Utils.h"

class Player;

class PlayerController
{
	eGameStyle mGameStyle;
	std::shared_ptr<Player> mSelectedPlayer;
	std::shared_ptr<Player> mAnotherPlayer;

	Field* mField;
	void CreatePlayers();

	float mDelay, mCount;

public:
	PlayerController(Field* field);
	std::shared_ptr<Player> GetSelectedPlayer() { return mSelectedPlayer; }
	void MakeControlledMove(Cell* cell);
	void OnMoveEnded();
	void Update(const float dt);
	~PlayerController();
};