#include "Game.h"
#include <ctime>
#include <cstdlib> 

const sf::Time TimePerFrame = sf::seconds(1.0f/60.0f);

Game::Game()
	: mWindow(sf::VideoMode(800, 600), "SFML Application")
	, mIsMovingUp(false), mIsMovingDown(false), mIsMovingLeft(false), mIsMovingRight(false)
	, PlayerSpeed(25.0f)
	, mPlayer()
	, movement(0.0f, 0.0f)
	, mTarget()
	, playingGame(true)
{
	mTimeToUpdate = 100;
	mCurrentTime = 0.0f;
	srand(time(NULL));
	mTarget.setSize(sf::Vector2f(25.0f, 25.0f));
	mTarget.setFillColor(sf::Color::Red);
	createTarget();
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		processEvents();
		while (playingGame)
		{
			timeSinceLastUpdate += clock.restart();
			while (timeSinceLastUpdate > TimePerFrame)
			{
				timeSinceLastUpdate -= TimePerFrame;
				processEvents();
				update(TimePerFrame);
			}
			render();
		}
	}
}

void Game::processEvents(){
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}

void Game::update(sf::Time deltaTime)
{
	if (mCurrentTime < mTimeToUpdate)
    {
        mCurrentTime += mClock.restart().asMilliseconds();
    }
	else
    {
        mCurrentTime = 0.0f;

		if (mIsMovingUp)
		{
			if (movement.y == 25.0f)
				gameOver();
			else
				movement = sf::Vector2f(0.0f, -25.0f);
		}
		if (mIsMovingDown)
		{
			if (movement.y == -25.0f)
				gameOver();
			else
				movement = sf::Vector2f(0.0f, 25.0f);
		}
		if (mIsMovingLeft)
		{
			if (movement.x == 25.0f)
				gameOver();
			else
				movement = sf::Vector2f(-25.0f, 0.0f);
		}
		if (mIsMovingRight)
		{
			if (movement.x == -25.0f)
				gameOver();
			else
				movement = sf::Vector2f(25.0f, 0.0f);
		}

		if(mPlayer.getPos().x < 0.0f || mPlayer.getPos().x > 775.0f || mPlayer.getPos().y < 0.0f || mPlayer.getPos().y > 575.0f)
			gameOver();

		if(!mFollowers.empty())
			if (mFollowers.size() > 1)
				for (int i = 0; i < mFollowers.size(); i++)
					if (mPlayer.getPos() == mFollowers[i].getPos())
						gameOver();

		mPlayer.setOldPos();
		//std::cout << "player old x: " << mPlayer.getOldPos().x << std::endl << "player old y: " << mPlayer.getOldPos().y << std:: endl;
		mPlayer.move(movement);
		//std::cout << "player x: " << mPlayer.getPos().x << std::endl << "player y: " << mPlayer.getPos().y << std:: endl;

		if(!mFollowers.empty())
		{
			mFollowers[0].setOldPos();
			mFollowers[0].move(mPlayer.getOldPos());
			if (mFollowers.size() > 1)
				for (int i = 1; i < mFollowers.size(); i++)
				{
					mFollowers[i].setOldPos();
					mFollowers[i].move(mFollowers[i-1].getOldPos());
				}
		}

		if(mPlayer.getPos() == mTarget.getPosition())
		{
			addFollower();
			createTarget();
		}
	}
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(mTarget);
	mWindow.draw(mPlayer.get());
	if (!mFollowers.empty())
		for (int i = 0; i < mFollowers.size(); i++)
			mWindow.draw(mFollowers[i].get());
	mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed){
	if (key == sf::Keyboard::Up)
		mIsMovingUp = isPressed;
	if (key == sf::Keyboard::Down)
		mIsMovingDown = isPressed;
	if (key == sf::Keyboard::Left)
		mIsMovingLeft = isPressed;
	if (key == sf::Keyboard::Right)
		mIsMovingRight = isPressed;
	if (key == sf::Keyboard::Escape)
		mWindow.close();
}

void Game::gameOver(){
	movement = sf::Vector2f(0.0f, 0.0f);
	playingGame = false;
}

void Game::addFollower()
{
	Follower newFollower;

	if (mFollowers.empty())
		newFollower.setPosition(mPlayer.getOldPos());
	else
		newFollower.setPosition(mFollowers.back().getOldPos());

	mFollowers.push_back(newFollower);
}

void Game::createTarget()
{
	int randX, randY;
	randX = (rand()%32)*25;
	randY = (rand()%24)*25;
	sf::Vector2f targetPos((float)randX, (float)randY);
	//std::cout << targetPos.x << std::endl << targetPos.y << std::endl;

	/*if (targetPos == mPlayer.getPos())
		createTarget();
	else
		if (!mFollowers.empty())
			for (int i = 0; i < mFollowers.size(); i++)
				if (targetPos == mFollowers[i].getPos())
				{
					createTarget();
					break;
				}*/
	mTarget.setPosition(targetPos);
}
