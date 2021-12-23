
#include "playerController.h"
#include "Resourse.h"

void PlayerController::CreatePlayers()
{
	auto data = ResourseManager->GetData<ItemData>("field");
	if (data->GetData("style") == "PvE")
	{
		mGameStyle = eGameStyle::PvE;
		player_1 = new Computer(mField, ePlayerColor::Black);
		player_2 = new Human(mField, ePlayerColor::White);
		selectedPlayer = player_2;
	}
	else if (data->GetData("style") == "PvP")
	{
		mGameStyle = eGameStyle::PvP;
		player_1 = new Human(mField, ePlayerColor::Black);
		player_2 = new Human(mField, ePlayerColor::White);
		selectedPlayer = player_2;
	}
}

PlayerController::PlayerController(Field* field) 
	: mField(field)
	, mDelay(10.f)
	, mCount(0.f)
{
	CreatePlayers();
	auto data = ResourseManager->GetData<ItemData>("field");
	mDelay = std::stof(data->GetData("delay"));
}

void PlayerController::OnMoveEnded()
{
	if (selectedPlayer == player_1)
	{
		selectedPlayer = player_2;
	}
	else
	{
		selectedPlayer = player_1;
	}
}

void PlayerController::Update(const float dt)
{
	mCount += dt;
	if (mCount > mDelay) 
	{
		mCount = 0.f;
		if (!selectedPlayer->IsHuman())
		{
			auto computer = static_cast<Computer*>(selectedPlayer);
			computer->MakeMove();
			OnMoveEnded();
		}
	}
}

PlayerController::~PlayerController()
{
	delete player_1;
	delete player_2;
}
