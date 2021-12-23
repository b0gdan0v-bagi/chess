#include "pawn.h"
#include "Resourse.h"
#include "Utils.h"

Pawn::Pawn(sf::RenderWindow* window, ePlayerColor color, const sf::Vector2f size, const sf::Vector2f pos)
	:Figure(window, color, size, pos)
{
	auto getData = color == ePlayerColor::White ? "white_pawn" : "black_pawn";
	mSprite = ResourseManager->GetData<ItemTexture>(getData)->GetSprite();
}
