#include<iostream>
#include "PingPong.h"
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include <cstdlib>
#include <ctime>

using namespace sf;
using namespace std;


int main()
{
	srand(static_cast<unsigned>(std::time(nullptr)));
	//All window processes in initwindow function
	PingPong game;
	//Game Loop 
	//Game always in While loop.
	while (game.windowisopen()) // If window is close then it quits the while loop.
	{
		//Updating anything and draws it into screen
		game.update();
		//Render Something in a game and changing its position.
		game.render();
	}
	//End of Game
	return 0;
}
