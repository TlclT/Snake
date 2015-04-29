#include <iostream>
#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include <vector>
#include "Follower.h"

class Game{
private:
	sf::RenderWindow mWindow;
	Player mPlayer;
	std::vector<Follower> mFollowers;
	sf::RectangleShape mTarget;
	bool mIsMovingUp;
	bool mIsMovingDown;
	bool mIsMovingLeft;
	bool mIsMovingRight;
	float PlayerSpeed;
	float mCurrentTime;
	int mTimeToUpdate;
	sf::Clock mClock;
	sf::Vector2f movement;
	bool playingGame;
private:
	void processEvents();
	void update(sf::Time);
	void render();
	void handlePlayerInput(sf::Keyboard::Key, bool);
	void gameOver();
	void addFollower();
	void createTarget();
public:
	Game();
	void run();
};