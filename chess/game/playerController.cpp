
#include "playerController.h"
#include "Resourse.h"

void PlayerController::CreatePlayers()
{
	auto data = ResourseManager->GetData<ItemData>("field");
	if (data->GetData("style") == "PvE")
	{
		mGameStyle = eGameStyle::PvE;
		player_1 = new Human(mField, ePlayerColor::Black);
		player_2 = new Computer(mField, ePlayerColor::White);

		selectedPlayer = player_1;
	}
}

PlayerController::PlayerController(Field* field) 
	: mField(field)
{
	CreatePlayers();
}

PlayerController::~PlayerController()
{
	delete player_1;
	delete player_2;
}
