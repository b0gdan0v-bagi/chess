#include "player.h"

Player::Player(Field* field, ePlayerColor color) 
	:mField(field), mPlayerColor(color), mIsReadyToMove(false)
{
}

Human::Human(Field* field, ePlayerColor color) :Player(field, color)
{
}

Computer::Computer(Field* field, ePlayerColor color) : Player(field, color)
{
}
