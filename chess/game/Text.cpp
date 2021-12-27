#include "Text.h"
#include "Drawer.h"

void Text::DrawSelf()
{
	// not working
	//_window->draw(mText); 
	sf::Text t(GetName(), mFont);
	t.setPosition(GetPosition());
	//t.setOrigin(-GetSize()/2.f);
	Drawer->Add(t);
}

Text::Text(const std::string& name, const sf::Vector2f coord, sf::Font font)
	:Entity(name)
	, mFont(font)
{
	SetPosition(coord);
}
