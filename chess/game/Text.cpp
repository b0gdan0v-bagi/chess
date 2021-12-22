#include "Text.h"

void Text::DrawSelf()
{
	// not working
	//_window->draw(mText); 
	sf::Text t(GetName(), mFont);
	t.setPosition(GetPosition());
	//t.setOrigin(-GetSize()/2.f);
	_window->draw(t);
}

Text::Text(sf::RenderWindow* window, const std::string& name, const sf::Vector2f coord, sf::Font font)
	:Entity(name, window)
	, mFont(font)
{
	SetPosition(coord);
}
