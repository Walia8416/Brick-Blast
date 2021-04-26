#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>

using namespace std;

int main()
{ 
	sf::Font font;
	font.loadFromFile("assets/ZOMBIE.ttf");
	string ss = "GAME OVER \n";
	sf::Text over;
	over.setFont(font);
	
	over.setCharacterSize(60);
	over.setFillColor(sf::Color::Red);
	over.setPosition(60,250);

	sf::Text done;
	done.setFont(font);
	done.setString("YOU WIN!!");
	done.setCharacterSize(70);
	done.setFillColor(sf::Color::Yellow);
	done.setPosition(130,250);


    const int SIZE=600, P_WIDTH=100, P_HEIGHT=25, RADIUS=10, B_WIDTH=100, B_HEIGHT=15;
    const float VEL=0.5, pVEL = 0.5;
    bool ballCollide=false,victory=false;
    float diag=0.0, b_diag=0.0;
    int pos_x=20, pos_y=20, n=0, count=0;

    vector<sf::RectangleShape> bricks(30, sf::RectangleShape(sf::Vector2f(B_WIDTH,B_HEIGHT)));
    

    sf::RenderWindow win(sf::VideoMode(SIZE, SIZE), "Brick Blast",sf::Style::Close);

    sf::RectangleShape paddle(sf::Vector2f(P_WIDTH,P_HEIGHT));
    paddle.setFillColor(sf::Color::Yellow);
    paddle.setPosition(255,550);




    for (int i=0; i<6; i++)
    {
    	for (int j=0; j<5; j++)
    	{	

    		bricks[n].setPosition(pos_x, pos_y);
            if (j%2 == 0)
            {
                bricks[n].setFillColor(sf::Color(68, 199, 114));
            }

            else
            {
            	bricks[n].setFillColor(sf::Color(75, 179, 189));
            }
            
    		pos_x+=110;
    		n++;
    	}
    	pos_x=20;
    	pos_y+=35;	
    }

    

    sf::CircleShape ball(RADIUS);
    ball.setFillColor(sf::Color::Red);
    ball.setPosition(295,250);

    while(win.isOpen())
    {   
        sf::Event evnt;
        while(win.pollEvent(evnt))
        {
            switch(evnt.type)
            {
                case sf::Event::Closed:
                    win.close();
                    break;
            }
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {   
            if (paddle.getPosition().x > 10)
            {
                paddle.move(-pVEL,0.0);
            }  
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            if (paddle.getPosition().x < SIZE-110)
            {
                paddle.move(pVEL,0.0);
            }
        }

        if (!ballCollide)
        {	
        	if (ball.getPosition().y < SIZE-(RADIUS*2))
        	{
        		ball.move(b_diag,VEL);
        	}

        	if (ball.getPosition().x < (RADIUS*2))
        	{
        		b_diag=0.3;
        	}

        	if (ball.getPosition().x > (SIZE-(RADIUS*2)))
        	{
        		b_diag=-0.3;
        	}

        	if (ball.getPosition().y > SIZE-(RADIUS*2)-RADIUS)
        	{
        		victory=true;
        	} 	
        	
        }

        if (ballCollide)
        {
        	ball.move(diag,-VEL);
        	if (ball.getPosition().y <= RADIUS)
        	{
        		ballCollide=false;
        		b_diag=0.0;

        	}

        	if (ball.getPosition().x < (RADIUS*2))
        	{
        		diag=0.4;
        	}

        	if (ball.getPosition().x > (SIZE-(RADIUS*2)))
        	{
        		diag=-0.4;
        	}
        }

        //cout << "PADDLE = "<< paddle.getPosition().x << " BALL = " << " " << ball.getPosition().y << endl;
        if (ball.getPosition().y < paddle.getPosition().y && ball.getPosition().y > paddle.getPosition().y-(RADIUS*2) && ball.getPosition().x > paddle.getPosition().x -(RADIUS*2) && ball.getPosition().x < paddle.getPosition().x+P_WIDTH+(RADIUS*2))
        {
        	ballCollide=true;
        	diag=0.0;

        	if (ball.getPosition().x > paddle.getPosition().x-(RADIUS*2) && ball.getPosition().x < paddle.getPosition().x+(P_WIDTH/4))
        	{
        		diag=-0.5;
        	}

        	if (ball.getPosition().x > paddle.getPosition().x+75 && ball.getPosition().x < paddle.getPosition().x+(P_WIDTH+(RADIUS*2)))
        	{
        		diag=0.5;
        	}
        }



        win.clear();
        if (!victory && count<n)
        { 
	        win.draw(paddle);
	        win.draw(ball);

	        for (int i=0; i<n; i++)
	        {	
	        	
		        if (ball.getPosition().y < bricks[i].getPosition().y + B_HEIGHT && ball.getPosition().y > bricks[i].getPosition().y && ball.getPosition().x > bricks[i].getPosition().x - (RADIUS*2) && ball.getPosition().x < bricks[i].getPosition().x + B_WIDTH)
		        {
		        	bricks[i].setPosition(-100,0);
		        	ballCollide=false;
                    
		        	count++;
                    if (ball.getPosition().x < bricks[i].getPosition().x + 50 )
                    {
                        b_diag=-0.5;
                    }

                    else
                    {
                    	b_diag=0.5;
                    }

		        
		        }	
		    	win.draw(bricks[i]);
		    }
		}

		if (count==n)
		{	
			
			win.draw(done);
			victory=false;
		}

		if (victory)
		{
			over.setString(ss + "       SCORE - " +  to_string(count));
			win.draw(over);
		} 


        win.display();
	}
}



