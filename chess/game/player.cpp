#include "player.h"

Player::Player(Field* field, ePlayerColor color) :mField(field), mPlayerColor(color)
{
}

Human::Human(Field* field, ePlayerColor color) :Player(field, color)
{
}

Computer::Computer(Field* field, ePlayerColor color) : Player(field, color)
{
}
