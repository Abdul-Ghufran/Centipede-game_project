

#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;

// Initializing Dimensions.
// resolutionX and resolutionY determine the rendering resolution.

const int resolutionX = 960;
const int resolutionY = 960;
const int boxPixelsX = 32;
const int boxPixelsY = 32;
const int gameRows = resolutionX / boxPixelsX; // Total rows on grid
const int gameColumns = resolutionY / boxPixelsY; // Total columns on grid

// Initializing GameGrid.
int gameGrid[gameRows][gameColumns] = {};

// The following exist purely for readability.
const int x = 0;	
const int y = 1;
const int exists = 2;

/////////////////////////////////////////////////////////////////////////////
//                                                                         //
// Write your functions declarations here. Some have been written for you. //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

void drawMushrooms(sf::RenderWindow& window , sf::Texture& mushroomTexture , sf::Sprite& mushroomSprite , float mushroom[][2] , bool check[] , int numberOfMushrooms);

void drawPlayer(sf::RenderWindow& window, float player[], sf::Sprite& playerSprite);

void movePlayer( float player[] , sf::Clock& playerClock);

void drawBullet(sf::RenderWindow& window, float bullet[], sf::Sprite& bulletSprite);

void moveBullet(float bullet[], sf::Clock& bulletClock);

void drawcentipede(sf::RenderWindow& window , sf::Texture& centipedeheadTexture , sf::Texture& centipedebodyTexture , sf::Sprite& centipedeheadSprite , sf::Sprite& centipedebodySprite , float 
centipede[][2], int& segments , bool moveRight);

void drawcentipede1(sf::RenderWindow& window , sf::Texture& centipedeheadTexture , sf::Texture& centipedebodyTexture , sf::Sprite& centipedeheadSprite , sf::Sprite& centipedebodySprite , float centipede1[][2], int& segments ) ;

void moveCentipede(float centipede[][2] , bool& moveRight , int& segments , bool& moveDown , float mushroom[][2], int& numberOfMushrooms, bool check[]);

void checkbulletmushroomCollision(float bullet[], float mushroom[][2]  , bool mushroomhalved[] , bool check[] , int& numberOfMushrooms , int& score);

void checkBulletCentipedeCollision(sf::RenderWindow& window , float bullet[], float centipede[][2], int &segments, float boxPixelsX , bool& moveRight , int& score);

void checkPlayerCentipedeCollision(sf::RenderWindow& window, float player[], float centipede[][2], int segments) ;

int main()
{
	srand(time(0));
	
	// Generate a random number of mushrooms (between 20 and 30)
	int numberOfMushrooms = rand() % 11 + 20;
	int score = 0 ;
	int location = (rand() % (gameRows-10)) * boxPixelsY;
	
        bool check[numberOfMushrooms] = {} ; //true if mushroom exits and false if doesnt exi
        
	// Declaring RenderWindow.
	sf::RenderWindow window(sf::VideoMode(resolutionX, resolutionY), "Centipede", sf::Style::Close | sf::Style::Titlebar);

	// Used to resize your window if it's too big or too small. Use according to your needs.
	window.setSize(sf::Vector2u(640, 640)); // Recommended for 1366x768 (768p) displays.
	// window.setSize(sf::Vector2u(1280, 1280)); // Recommended for 2560x1440 (1440p) displays.
	// window.setSize(sf::Vector2u(1920, 1920)); // Recommended for 3840x2160 (4k) displays.
	
	// Used to position your window on every launch. Use according to your needs.
	window.setPosition(sf::Vector2i(100, 0));

	// Initializing Background Music.
	sf::Music bgMusic;
	bgMusic.openFromFile("Music/field_of_hopes.ogg");
	bgMusic.play();
	bgMusic.setVolume(50);

	// Initializing Background.
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	backgroundTexture.loadFromFile("Textures/background.jpg");
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setColor(sf::Color(255, 255, 255, 255 * 0.50)); // Reduces Opacity to 50%
	
	//initializing score text
	sf::Text scoreText;
	sf::Font font;
	font.loadFromFile("Textures/arial.ttf");
	scoreText.setFont(font);
	scoreText.setCharacterSize(40);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(10, 10); 

	
        // Initializing mashrooms.
        float mushroom[numberOfMushrooms][2] = {};
        bool mushroomhalved[numberOfMushrooms] = {};
        sf::Texture mushroomTexture;
        sf::Sprite mushroomSprite(mushroomTexture);
        mushroomTexture.loadFromFile("Textures/mushroom.png");
        mushroomSprite.setTexture(mushroomTexture);
        mushroomSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));

	
	// Initializing Player and Player Sprites.
	float player[2] = {};
	player[x] = (gameColumns / 2) * boxPixelsX;
	player[y] = (gameColumns * 3 / 4) * boxPixelsY;
	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	playerTexture.loadFromFile("Textures/player.png");
	playerSprite.setTexture(playerTexture);
	playerSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
    sf::Clock playerClock;
	

	// Initializing Bullet and Bullet Sprites.
	float bullet[3] = {};
	bullet[x] = player[x];
	bullet[y] = player[y] - boxPixelsY;
	bullet[exists] = true;
	sf::Clock bulletClock;
	sf::Texture bulletTexture;
	sf::Sprite bulletSprite;
	bulletTexture.loadFromFile("Textures/bullet.png");
	bulletSprite.setTexture(bulletTexture);
	bulletSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
	
	
	// Initializing centipede and centipede Sprites.
	int segments = 12 ;
        float centipede[segments][2] = {};
        float centipede1[segments][2] = {};
	bool moveRight = true ;
	bool moveDown = true ;
	sf::Texture centipedebodyTexture;
	sf::Texture centipedeheadTexture;
        sf::Sprite centipedebodySprite(centipedebodyTexture);
        sf::Sprite centipedeheadSprite(centipedeheadTexture);
        centipedebodyTexture.loadFromFile("Textures/c_body_left_walk.png");
        centipedeheadTexture.loadFromFile("Textures/c_head_left_walk.png");
        centipedebodySprite.setTexture(centipedebodyTexture);
        centipedebodySprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
        centipedeheadSprite.setTexture(centipedeheadTexture);
        centipedeheadSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
       
        for (int i = 0; i < segments; ++i) 
        {
  	  
  	  centipede[i][y] =  location ;  // Random row generation of centipede
	}
        
        //giving random position to every mushroom on the screen 
        for(int i = 0 ; i < numberOfMushrooms ; ++i)
	{
	    
    	  // Set a random position for each mushroom
     	   mushroom[i][x] = (rand() % gameColumns) * boxPixelsX;
     	   mushroom[i][y] = (rand() % gameRows-2) * boxPixelsY;
     	   check[i] = true;
	   
	}
        
	while( window.isOpen() ) {

		///////////////////////////////////////////////////////////////
		//                                                           //
		// Call Your Functions Here. Some have been written for you. //
		// Be vary of the order you call them, SFML draws in order.  //
		//                                                           //
		///////////////////////////////////////////////////////////////

		window.draw(backgroundSprite);
		
		drawMushrooms(window , mushroomTexture , mushroomSprite , mushroom , check , numberOfMushrooms);
		
		drawPlayer(window, player, playerSprite);
		
		movePlayer(player, playerClock);
                
		drawcentipede(window , centipedeheadTexture , centipedebodyTexture , centipedeheadSprite , centipedebodySprite  , centipede, segments , moveRight);
		
		drawcentipede1(window , centipedeheadTexture , centipedebodyTexture , centipedeheadSprite , centipedebodySprite  , centipede1, segments );
		
		moveCentipede(centipede , moveRight , segments , moveDown , mushroom , numberOfMushrooms , check);
		
		//bullet functions for drawing , movement and collisions
		if (bullet[exists] == true) {
			
			drawBullet(window, bullet, bulletSprite);
			
			moveBullet(bullet, bulletClock );
			
			checkbulletmushroomCollision( bullet, mushroom , mushroomhalved , check , numberOfMushrooms , score);
			
			checkBulletCentipedeCollision(window , bullet, centipede, segments, boxPixelsX, moveRight , score);
		}
		
		checkPlayerCentipedeCollision( window, player , centipede , segments) ;

		sf::Event e;
		while (window.pollEvent(e)) 
		{
			if (e.type == sf::Event::Closed) 
			{
				return 0;
			}
			
			
	    		if (e.type == sf::Event::KeyPressed)
	    		{
                		if (e.key.code == sf::Keyboard::Space)  //bullet is generated when space is pressed
                		{ 
                	
                    			if (!bullet[exists]) 
                    			{
                        			bullet[x] = player[x];
                        			bullet[y] = player[y] - boxPixelsY;
                        			bullet[exists] = true;
                    			}    
                		}
            		}
			
		}
		
		scoreText.setString("Score: " + std::to_string(score));
		// Draw the score on the window
		window.draw(scoreText);		
		window.display();   //display all the functions and the logic implemented
		
		window.clear();
	}
}

////////////////////////////////////////////////////////////////////////////
//                                                                        //
// Write your functions definitions here. Some have been written for you. //
//                                                                        //
////////////////////////////////////////////////////////////////////////////


//function that draws random number of muhsrooms on the screen at random locations
void drawMushrooms(sf::RenderWindow& window , sf::Texture& mushroomTexture , sf::Sprite& mushroomSprite , float mushroom[][2] , bool check[] , int numberOfMushrooms)
{
   
   
     for (int i = 0; i < numberOfMushrooms; ++i) 
     {
        
        if(check[i])   // checks for the mushroom existence.This helps in creating a limited number of mushrooms
        {    
            // Create mushroom sprite
            mushroomSprite.setTexture(mushroomTexture);
            mushroomSprite.setPosition((mushroom[i][x]), (mushroom[i][y]));

            // Draw the mushroom sprite
            window.draw(mushroomSprite);
        }
    }
  
} 


//function that draws the player sprite on the window 
void drawPlayer(sf::RenderWindow& window, float player[], sf::Sprite& playerSprite) {
	playerSprite.setPosition(player[x], player[y]);
	window.draw(playerSprite);
	
}


//function that moves the player sprite using arrow keys
void movePlayer( float player[], sf::Clock& playerClock)
{
    if (playerClock.getElapsedTime().asMilliseconds() < 60)  // added a clock so that the player movement is in accordance to the screen pixels 
    return;
    playerClock.restart();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player[x] > 0) {
        player[x] -= boxPixelsX; // Move left upto 32 pixels
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player[x] < resolutionX - boxPixelsX) {
        player[x] += boxPixelsX; // Move right upto 32 pixels
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player[y] > 0) {
        player[y] -= boxPixelsY; // Move up upto 32 pixels
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && player[y] < resolutionY - boxPixelsY) {
        player[y] += boxPixelsY; // Move down upto 32 pixels
    }
}


//function for drawing the bullet
void drawBullet(sf::RenderWindow& window, float bullet[], sf::Sprite& bulletSprite) {
	bulletSprite.setPosition(bullet[x], bullet[y]);
	window.draw(bulletSprite);    //draws bullet sprite
	
}


//function that moves the bullet on the screen 
void moveBullet(float bullet[], sf::Clock& bulletClock) 
{
	if (bulletClock.getElapsedTime().asMilliseconds() < 20)    // added clock to fix the speed with which the bullet travels
	return;
	
	bulletClock.restart();
	bullet[y] -= boxPixelsY;     // indicates that the bullet moves upwards along the y-axis
		
	if (bullet[y] < -boxPixelsY)
	bullet[exists] = false;      // this vanishes the bullet once it reaches the upper end of the window 
}

//function to draw the centipede segment by segment on the screen 
void drawcentipede(sf::RenderWindow& window , sf::Texture& centipedeheadTexture , sf::Texture& centipedebodyTexture , sf::Sprite& centipedeheadSprite , sf::Sprite& centipedebodySprite , float centipede[][2], int& segments , bool moveRight) 
{
     
    for(int i = 0 ; i < segments ; i++) 
    {
        
        if(i == 0)   //for the first segment
        {
            if(!moveRight)   //if the centipede does not face right direction then print head segment first 
            {
            	centipedeheadSprite.setTexture(centipedeheadTexture);
            	centipedeheadSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
            	centipedeheadSprite.setPosition(centipede[i][0], centipede[i][5]);
            	window.draw(centipedeheadSprite);
            }
            
            if(moveRight)   //if the centipede faces right direction then print body segment first
            {
            	centipedebodySprite.setTexture(centipedebodyTexture);
            	centipedebodySprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
            	centipedebodySprite.setPosition(centipede[i][0], centipede[i][1]);
	    	window.draw(centipedebodySprite);
            }
        }
        
        else
        {
             //prints the body segments of the centipede
             centipede[i][0] = centipede[i-1][0] + 32;     //spawns the new segment ahead of the previous one 
             centipedebodySprite.setTexture(centipedebodyTexture);
             centipedebodySprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
             centipedebodySprite.setPosition(centipede[i][0], centipede[i][1]);
	     window.draw(centipedebodySprite);
	    

	     if(moveRight)    // when the centipede is facing right
	     {
	     	 if(i == segments - 1)    // the last segment should be a head
	     	 {
	     	     centipedeheadSprite.setTexture(centipedeheadTexture);
             	     centipedeheadSprite.setTextureRect(sf::IntRect(boxPixelsX, 0, -boxPixelsX, boxPixelsY));
             	     centipedeheadSprite.setPosition(centipede[segments-1][0], centipede[segments-1][1]);
             	     window.draw(centipedeheadSprite);
             	 }    
	     }
	}
    }
    
}




void drawcentipede1(sf::RenderWindow& window , sf::Texture& centipedeheadTexture , sf::Texture& centipedebodyTexture , sf::Sprite& centipedeheadSprite , sf::Sprite& centipedebodySprite , float centipede1[][2], int& segments ) 
{
     
    for(int i = 0 ; i < segments ; i++) 
    {
        
        if(i == 0)   //for the first segment
        {
           
            	centipedeheadSprite.setTexture(centipedeheadTexture);
            	centipedeheadSprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
            	centipedeheadSprite.setPosition(centipede1[i][0], centipede1[i][5]);
            	window.draw(centipedeheadSprite);
            
          
        }
        
        else
        {
             //prints the body segments of the centipede
             centipede1[i][0] = centipede1[i-1][0] + 32;     //spawns the new segment ahead of the previous one 
             centipedebodySprite.setTexture(centipedebodyTexture);
             centipedebodySprite.setTextureRect(sf::IntRect(0, 0, boxPixelsX, boxPixelsY));
             centipedebodySprite.setPosition(centipede1[i][0], centipede1[i][1]);
	     window.draw(centipedebodySprite);
	    
	}
    }
    
}


//function to move the centipede on the screen 
void moveCentipede(float centipede[][2], bool& moveRight, int& segments, bool& moveDown , float mushroom[][2], int& numberOfMushrooms, bool check[]) 
{
    
    if (moveDown == true) 
    {
        for (int i = 0; i < segments; i++) 
        {
            // Move the centipede
            if (moveRight) 
                centipede[i][0] += 0.5;
            else 
                centipede[i][0] -= 0.5;
        }

        // Check if the centipede reached the screen boundaries
        if (centipede[0][0] < 0 || centipede[segments - 1][0] > resolutionX - boxPixelsX) 
        {
            moveRight = !moveRight;

            // Move the centipede down by 1 position
            for (int i = 0; i < segments; i++) 
                centipede[i][1] += boxPixelsY;
          
           
            //---------------------------------------------------------------------
            // Check if the centipede has reached the player area
            if (centipede[0][1] >= resolutionY - 5 * boxPixelsY) 
            {
                
                // Move the centipede back and forth in the player area
        	for (int i = 0; i < segments; i++) 
        	{
            		// Move the centipede
            		if (moveRight) 
                	centipede[i][0] += 0.5; 
            		else 
                	centipede[i][0] -= 0.5;
        	}

        	// Check if the centipede reached the screen boundaries in the player area
        	if (centipede[0][0] < 0 || centipede[segments - 1][0] > resolutionX - boxPixelsX)
        	{
            		moveRight = !moveRight;    //change its direction
            
             		for (int i = 0; i < segments; i++) 
                	centipede[i][1] += boxPixelsY;    //move the segments down by one position
        	}
        	
        	if (centipede[0][1] >= resolutionY - boxPixelsY)       // if centipede reached the end of the screen
            	{
            	    moveDown = false;       //it should start moving up
            	   
            	}
                
                
            }
            
            
        }
    } 
    
    
     // Check for collisions with mushrooms
    for (int i = 0; i < numberOfMushrooms; i++)
    {
        for (int j = 0; j < segments; j++)
        {
            if (check[i] && (centipede[j][x] == mushroom[i][x]) && (centipede[j][y] == mushroom[i][y]))
            {
                // Change direction if the centipede collides with a mushroom
                moveRight = !moveRight;

                // Move the centipede down by 1 position
                for (int k = 0; k < segments; k++)
                    centipede[k][1] += boxPixelsY;

                // Update mushroom status i.e vanish it
                check[i] = false;
            }
        }
    }
    
    
    
    if(moveDown == false)    //if centipede is moving up
    {
        // Move the centipede back and forth in the player area
        for (int i = 0; i < segments; i++) 
        {
            // Move the centipede
            if (moveRight) 
                centipede[i][0] += 0.5; 
            else 
                centipede[i][0] -= 0.5;
                
        }

        // Check if the centipede reached the screen boundaries in the player area
        if (centipede[0][0] < 0 || centipede[segments - 1][0] > resolutionX - boxPixelsX)
        {
            moveRight = !moveRight;       //change the direction
            
            for (int i = 0; i < segments; i++) 
                centipede[i][1] -= boxPixelsY;      // Move the centipede up by 1 position
                
            // Check if the centipede has reached the player area border
            if (centipede[0][1] <= resolutionY - 5 * boxPixelsY) 
            {   
                moveDown = true;       //it should start moving down
                
            }
        }
    }
    
    
}


//function to check the collision of mushroom with the bullet 
void checkbulletmushroomCollision(float bullet[], float mushroom[][2], bool mushroomhalved[] , bool check[], int& numberOfMushrooms , int& score)
{

   
    
    for (int i = 0; i < numberOfMushrooms; i++)
    {
    
        if (bullet[exists] && check[i] && (bullet[y] == mushroom[i][y]) && (bullet[x] == mushroom[i][x]) )
        {
       
            bullet[exists] = false;        //the bullet disappears
            score+=1;
            // If the mushroom is not already halved, halve its size
            if (mushroomhalved[i] == false)
            {
                mushroomhalved[i] = true;     //change the mushroom status 
            }
 
            else if (mushroomhalved[i] == true)
            {
                // If the mushroom is already halved, remove it
                check[i] = false;
                
            }
    
        }
    }
}


//function to check the collison of the bullet and the centipede segments
void checkBulletCentipedeCollision(sf::RenderWindow& window , float bullet[], float centipede[][2], int& segments, float boxPixelsX, bool& moveRight , int& score) 
{
    // Check if the bullet collides with any segment of the centipede
    for (int i = 0; i < segments; i++) 
    {

        // Check if the bullet's position is within the bounding box of the centipede segment
        if (bullet[exists] && 
            bullet[x] < centipede[i][x] + boxPixelsX && bullet[x] + boxPixelsX > centipede[i][x] &&
            bullet[y] < centipede[i][y] + boxPixelsX && bullet[y] + boxPixelsX > centipede[i][y]) 
        {
        
            bullet[exists] = false; // Bullet disappears
            
            if(moveRight == false)
            {
            	if (i == 0) 
            	{
                     // If the bullet hits the head, destroy the entire centipede
                     segments = 0;
                     score+=20;
                     sf::Music deathofcentipede;
		     deathofcentipede.openFromFile("Sound Effects/1up.wav");
		     deathofcentipede.play();
	 	     deathofcentipede.setVolume(50);
       	        
            	cout << "Game Over! YOU WIN... " << endl <<"Headshot to the centipede..."<<endl;
            	
            	sf::Clock delayClock;

            	// produce a delay of 2 seconds 
            	   while (delayClock.getElapsedTime().asSeconds() < 2) 
            	   {
                	// Keep the window open during the delay
                   	sf::Event e;
                	while (window.pollEvent(e)) 
                	{
                    	    if (e.type == sf::Event::Closed) 
                    	    {
                        	window.close();
                        	return;
                    	    }
                	}
            	   }

            	   window.close(); // Close the window to exit the game
                     
            	} 
            }
            
            if(moveRight == true)
            {
            	if (i == segments - 1) 
            	{
                     // If the bullet hits the head, destroy the entire centipede
                     segments = 0;
                     score+=20;
                     sf::Music deathofcentipede;
		     deathofcentipede.openFromFile("Sound Effects/1up.wav");
		     deathofcentipede.play();
	 	     deathofcentipede.setVolume(50);
       	        
            	cout << "Game Over! YOU WIN... " << endl <<"Headshot to the centipede..."<<endl;
            	
            	sf::Clock delayClock;

            	// produce a delay of 2 seconds 
            	   while (delayClock.getElapsedTime().asSeconds() < 2) 
            	   {
                	// Keep the window open during the delay
                   	sf::Event e;
                	while (window.pollEvent(e)) 
                	{
                    	    if (e.type == sf::Event::Closed) 
                    	    {
                        	window.close();
                        	return;
                    	    }
                	}
            	   }

            	   window.close(); // Close the window to exit the game
            	} 
            }
              
            	
            if(moveRight == true || moveRight == false)
            {
                segments--;   
                score+=10;
            }
            
        }
    }
}


//function to check the collision of player and the centipede segments 
void checkPlayerCentipedeCollision(sf::RenderWindow& window, float player[], float centipede[][2], int segments) 
{
    // Check if the player collides with any segment of the centipede
    for (int i = 0; i < segments; i++) 
    {
        if ( (player[y] == centipede[i][y]) && (player[x] == centipede[i][x]) )      // condition to check the collision of the player and centipede segments
       	    {
       	        //plays a sound of destruction when collision occurs
       	        sf::Music deathofplayer;
		deathofplayer.openFromFile("Sound Effects/death.wav");                    
		deathofplayer.play();       
		deathofplayer.setVolume(50);
       	        
            	cout << "Game Over! YOU LOST... " << endl <<"Your player got struck by the centipede ..."<<endl;
            	
            	sf::Clock delayClock;

            // Introduce a delay of 2 seconds (you can adjust this value)
            while (delayClock.getElapsedTime().asSeconds() < 1) 
            {
                // Keep the window open during the delay
                sf::Event e;
                while (window.pollEvent(e)) 
                {
                    if (e.type == sf::Event::Closed) 
                    {
                        window.close();
                        return;
                    }
                }
            }

              window.close(); // Close the window to exit the game
            	
            }
    }
    
}




