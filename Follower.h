#include <SFML/Graphics.hpp>

class Follower{
private:
	sf::RectangleShape mFollower;
	sf::Vector2f oldPos;
public:
	Follower();
	sf::RectangleShape get(){return mFollower;};
	sf::Vector2f getPos(){return mFollower.getPosition();};
	void setPosition(sf::Vector2f pos){mFollower.setPosition(pos);};
	void move(sf::Vector2f pos){mFollower.setPosition(pos);};
	void setOldPos(){oldPos = mFollower.getPosition();};
	sf::Vector2f getOldPos(){return oldPos;};
};