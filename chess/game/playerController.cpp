
#include "playerController.h"
#include "Resourse.h"

void PlayerController::CreatePlayers()
{
	switch (mGameStyle)
	{
	case eGameStyle::PvE:
	{
		mAnotherPlayer = std::make_shared<Computer>(mField, ePlayerColor::Black, this);
		mSelectedPlayer = std::make_shared<Human>(mField, ePlayerColor::White, this);
	}
		break;
	case eGameStyle::PvP:
	{
		mAnotherPlayer = std::make_shared<Human>(mField, ePlayerColor::Black, this);
		mSelectedPlayer = std::make_shared<Human>(mField, ePlayerColor::White, this);
	}
		break;
	case eGameStyle::EvE:
	{
		mAnotherPlayer = std::make_shared<Computer>(mField, ePlayerColor::Black, this);
		mSelectedPlayer = std::make_shared<Computer>(mField, ePlayerColor::White, this);
	}
	break;
	}
	auto data = ResourseManager->GetData<ItemData>("field");
	if (data->GetData("start") == "black") { std::swap(mAnotherPlayer, mSelectedPlayer); }
}

PlayerController::PlayerController(Field* field) 
	: mField(field)
	, mDelay(10.f)
	, mCount(0.f)
	, mGameStyle(eGameStyle::PvE)
{
	auto data = ResourseManager->GetData<ItemData>("field");
	mDelay = std::stof(data->GetData("delay"));
	auto gamestyle = data->GetData("style");
	if (gamestyle == "PvE")
	{
		mGameStyle = eGameStyle::PvE;
	}
	else if (gamestyle == "PvP")
	{
		mGameStyle = eGameStyle::PvP;
	}
	else if (gamestyle == "EvE")
	{
		mGameStyle = eGameStyle::EvE;
	}
	CreatePlayers();
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
}

void PlayerController::Update(const float dt)
{
	mCount += dt;
	if (mCount > mDelay && mField->IsGamePlayable()) 
	{
		mCount = 0.f;
		if (!mSelectedPlayer->IsHuman())
		{
			auto computer = std::static_pointer_cast<Computer>(mSelectedPlayer);
			computer->MakeMove(nullptr);
		}
	}
}

PlayerController::~PlayerController()
{
}
