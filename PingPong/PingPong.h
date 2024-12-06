#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include <cstdlib>
#include <ctime>

using namespace sf;
using namespace std;

struct PingPong
{
private:
	RenderWindow window; //Making Window For Game with buttons of resize close titlebar etc.
	Event key; //Capturing Event if we press any key in window

	float barsspeed=6;
	float ballspeedx = 4;
	float ballspeedy = -5;
	bool touchbar2 = false;
	bool touchbar1 = false;
	bool gamewins = false;
	bool gamestarted = false;

	int score1 = 0;
	int score2 = 0;

	CircleShape ball;
	RectangleShape bar1;
	RectangleShape bar2;
	RectangleShape line;

	Font fortext;
	Text Score1;
	Text Score2;
	Text forgamewin;
	Text forstartbutton;

	void initwindow();
	void makingbar1andbar2();
	void makingline();
	void makingball();




public:
	PingPong();

	//Accessor
	bool const windowisopen() const;

	void UpdatingBar1andBar2Position();
	void UpdatingBallPosition();
	void ballandbar();
	void gamewin();
	void eventpoll();
	void update();
	void render();



};

