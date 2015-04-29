#include "Player.h"

Player::Player()
	: mPlayer()
{
	mPlayer.setSize(sf::Vector2f(25.0f, 25.0f));
	mPlayer.setFillColor(sf::Color::White);
	mPlayer.setPosition(400.0f, 300.0f);
}