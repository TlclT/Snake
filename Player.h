#include <SFML/Graphics.hpp>

class Player{
private:
	sf::RectangleShape mPlayer;
	sf::Vector2f oldPos;
public:
	Player();
	sf::RectangleShape get(){return mPlayer;};
	sf::Vector2f getPos(){return mPlayer.getPosition();};
	void move(sf::Vector2f pos){mPlayer.move(pos);};
	void setOldPos(){oldPos = mPlayer.getPosition();};
	sf::Vector2f getOldPos(){return oldPos;};
};