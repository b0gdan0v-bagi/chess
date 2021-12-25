
#include "playerController.h"
#include "Resourse.h"

void PlayerController::CreatePlayers()
{
	auto data = ResourseManager->GetData<ItemData>("field");
	if (data->GetData("style") == "PvE")
	{
		mGameStyle = eGameStyle::PvE;
		mAnotherPlayer = std::make_shared<Computer>(mField, ePlayerColor::Black, this);
		mSelectedPlayer = std::make_shared<Human>(mField, ePlayerColor::White, this);
		//player_1 = new Computer(mField, ePlayerColor::Black);
		//player_2 = new Human(mField, ePlayerColor::White);
		//selectedPlayer = player_2;
	}
	else if (data->GetData("style") == "PvP")
	{
		mGameStyle = eGameStyle::PvP;
		mAnotherPlayer = std::make_shared<Human>(mField, ePlayerColor::Black, this);
		mSelectedPlayer = std::make_shared<Human>(mField, ePlayerColor::White, this);
		/*player_1 = new Human(mField, ePlayerColor::Black);
		player_2 = new Human(mField, ePlayerColor::White);
		selectedPlayer = player_2;*/
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

void PlayerController::MakeControlledMove(Cell* cell)
{
	if (cell && mSelectedPlayer->IsHuman())
	{
		mSelectedPlayer->MakeMove(cell);
	}
}

void PlayerController::OnMoveEnded()
{
	std::swap(mSelectedPlayer, mAnotherPlayer);
	/*if (selectedPlayer == player_1)
	{
		selectedPlayer = player_2;
	}
	else
	{
		selectedPlayer = player_1;
	}*/
}

void PlayerController::Update(const float dt)
{
	mCount += dt;
	if (mCount > mDelay) 
	{
		mCount = 0.f;
		if (!mSelectedPlayer->IsHuman())
		{
			auto computer = std::static_pointer_cast<Computer>(mSelectedPlayer);
			computer->MakeMove(nullptr);
			OnMoveEnded();
		}
	}
}

PlayerController::~PlayerController()
{
	//delete player_1;
	//delete player_2;
}
