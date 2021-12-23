#include "figure.h"

Figure::Figure(sf::RenderWindow* window, ePlayerColor color) : Entity("figure", window), mPlayerColor(color)
{
}
