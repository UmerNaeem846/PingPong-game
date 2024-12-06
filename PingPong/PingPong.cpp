#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include <cstdlib>
#include <ctime>
#include "PingPong.h"

using namespace sf;
using namespace std;

void PingPong::initwindow()
{
	window.create(VideoMode(1280, 900), "2048", Style::Titlebar | Style::Close | Style::Resize);
	window.setFramerateLimit(60);
}

void PingPong::makingbar1andbar2()
{
	bar1.setSize(Vector2f(20, 100));
	bar1.setPosition(40, 400);
	bar1.setFillColor(Color::White);

	bar2.setSize(Vector2f(20, 100));
	bar2.setPosition(1220, 400);
	bar2.setFillColor(Color::White);
}

void PingPong::makingline()
{
	line.setFillColor(Color::White);
	line.setSize(Vector2f(5, 900));
	line.setPosition(637.5, 0);
}

void PingPong::makingball()
{
	ball.setRadius(8);
	ball.setPosition(1200,442);
	ball.setFillColor(Color::Blue);
}

PingPong::PingPong()
{
	initwindow();
	makingbar1andbar2();
	makingball();
	makingline();
}

bool const PingPong::windowisopen() const
{
	return window.isOpen();
}

void PingPong::UpdatingBar1andBar2Position()
{
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		bar1.move(0, -barsspeed);
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
	{
		bar1.move(0, barsspeed);
	}
	if (Keyboard::isKeyPressed(Keyboard::Up))
	{
		bar2.move(0,-barsspeed);
	}
	if (Keyboard::isKeyPressed(Keyboard::Down))
	{
		bar2.move(0, barsspeed);
	}
	if (bar1.getPosition().y > 800)
	{
		bar1.setPosition(40,800 );
	}
	if (bar1.getPosition().y < 0)
	{
		bar1.setPosition(40, 0);
	}
	if (bar2.getPosition().y > 800)
	{
		bar2.setPosition(1220, 800);
	}
	if (bar2.getPosition().y < 0)
	{
		bar2.setPosition(1220, 0);
	}

}

void PingPong::UpdatingBallPosition()
{


	fortext.loadFromFile("AGENCYB.TTF");
	Score1.setFont(fortext);
	Score1.setCharacterSize(24);
	Score1.setFillColor(Color::White);
	Score1.setString("Score: " + to_string(score1));
	Score1.setPosition(300, 40);

	Score2.setFont(fortext);
	Score2.setCharacterSize(24);
	Score2.setFillColor(Color::White);
	Score2.setString("Score: " + to_string(score2));
	Score2.setPosition(900, 40);

	if (gamestarted)
	{
		ball.move(ballspeedx, ballspeedy);

		if (ball.getPosition().y <= 0 || ball.getPosition().y + 16 >= 900)
		{
			ballspeedy = -ballspeedy;
		}
		if (touchbar2 && (ball.getPosition().x <= 0))
		{
			score2++;
			Score2.setString("Score: " + to_string(score2));

			touchbar2 = false;
			gamestarted = false;
			ballspeedx = -ballspeedx;
			gamewin();
			ball.setPosition(1200, 442);
			makingbar1andbar2();
		}
		if (touchbar1 && (ball.getPosition().x >= 1280))
		{
			score1++;
			Score2.setString("Score: " + to_string(score1));
			ballspeedx = -ballspeedx;
			touchbar1 = false;
			gamestarted = false;
			gamewin();
			ball.setPosition(62, 442);
			makingbar1andbar2();
		}
	}
	
}


void PingPong::ballandbar()
{
	if (ball.getGlobalBounds().intersects(bar1.getGlobalBounds()))
	{
		ballspeedx = -ballspeedx;
		touchbar1 = true;
	}
	else if (ball.getGlobalBounds().intersects(bar2.getGlobalBounds()))
	{
		ballspeedx = -ballspeedx;
		touchbar2 = true;
	}
}

void PingPong::gamewin()
{
	forgamewin.setFont(fortext);
	forstartbutton.setFont(fortext);
	if (score1 == 1 || score2 == 1)
	{
		gamewins = true;
		gamestarted = false;
		forgamewin.setCharacterSize(35);
		forgamewin.setFillColor(Color::White);
		forgamewin.setPosition(540, 350);
		forstartbutton.setCharacterSize(32);
		forstartbutton.setFillColor(Color::White);
		forstartbutton.setPosition(560, 450);
		if (score1 == 1)
		{
			forgamewin.setString("Player 1 wins!");
			forstartbutton.setString("Start Game");
			score1 = 0;
			score2 = 0;
		}
		if (score2==1)
		{
			forgamewin.setString("Player 2 wins!");
			forstartbutton.setString("Start Game");
			score1 = 0;
			score2 = 0;
		}

	}
}

void PingPong::eventpoll()
{
	while (window.pollEvent(key))
	{
		switch (key.type)
		{
		case Event::Closed:
			window.close();
		case Event::KeyPressed:
			if (key.key.code == Keyboard::Space)
			{
				gamestarted = true;
			}
		case Event::MouseMoved:
			if (forstartbutton.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window))))
			{
				forstartbutton.setFillColor(Color::Green);
			}
			else
			{
				forstartbutton.setFillColor(Color::White);
			}
		case Event::MouseButtonPressed:
			if (forstartbutton.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window))))
			{
				if (key.key.code == Mouse::Left)
				{
					gamewins = false;
				}
			} 
		}
	}
}

void PingPong::update()
{
	eventpoll();
	if (gamestarted)
	{
		UpdatingBar1andBar2Position();
		ballandbar();
	}
	UpdatingBallPosition();


}

void PingPong::render()
{
	window.clear();
	if (gamewins)
	{
		window.draw(forgamewin);
		window.draw(forstartbutton);

	}
	if (!gamewins)
	{
		window.draw(line);
		window.draw(bar1);
		window.draw(bar2);
		window.draw(ball); 
		window.draw(Score1);
		window.draw(Score2);
	}


	window.display();
}
