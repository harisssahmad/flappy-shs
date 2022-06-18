#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
using namespace std;
// Screen dimensions
#define SCREENW 600
#define SCREENH 800

class Pipe {	
	sf::Texture pipe;
	
	sf::Sprite sprite;
	
	static int pipeW;
	static float pipeX;
	static int spacing;
	static float spaceY;
	public:
		Pipe() {
			if (!pipe.loadFromFile("assets/yellow_pipe.png"))
			{
			    // error...
			}
			sprite.setTexture(pipe);
		}
		Pipe(const std::string a) {
			if (!pipe.loadFromFile("assets/yellow_pipe_top.png"))
			{
			    // error...
			}
			sprite.setTexture(pipe);
		}
		static void set_pipeX(const float x) {
			pipeX = x;
		}
		static void set_spaceY(const float y) {
			spaceY = y;
		}
		static void set_spacing(const float s) {
			spacing = s;
		}
		sf::Sprite& get_sprite() {
			return sprite;
		}
		static const int get_pipeW() {
			return pipeW;
		}
		static const float get_pipeX() {
			return pipeX;
		}
		static const float get_spaceY() {
			return spaceY;
		}
		static const int get_spacing() {
			return spacing;
		}
};

int Pipe::pipeW = 100;
float Pipe::pipeX = SCREENW + pipeW;
int Pipe::spacing = 300;
float Pipe::spaceY = SCREENH/3;

class Interface {
	public:
		/* Interface to implement rules for Players
		All players must have these functions! */
		virtual void fly() = 0;
		virtual void fall() = 0;
		virtual void play_scored() = 0;
		virtual void play_died() = 0;
		virtual const bool isColliding(sf::RectangleShape&, sf::RectangleShape&) = 0;
		virtual const bool scoreCheck(Pipe&) = 0;
};

class MusicManager;

class Player: public Interface {
	friend class MusicManager;
	float yPos;
	float velocity;
	float gravity;
	float rotation_speed;
	float speed;
	bool isActive;
	
	//Background music object
	sf::Music music;
	
	//Sound objects
	sf::SoundBuffer soundBuffer1;
	sf::Sound scored; //sound when score is incremented
	
	sf::SoundBuffer soundBuffer2;
	sf::Sound died; //sound when player dies

	sf::Texture texture;
	
	sf::Sprite sprite;
	
	sf::Vector2f origin;
	public:
		Player () {
			//SETTING DEFAULTS HERE
			origin = sf::Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
			yPos = SCREENH/3;
			velocity = 0;
			gravity = 0.5;
			sprite.setTexture(texture);
			sprite.setOrigin(origin);
			rotation_speed = 0;
			speed = 4.5;
			//Setting scored sound
			scored.setBuffer(soundBuffer1);
			soundBuffer1.loadFromFile("audio/wow.ogg");
			scored.setBuffer(soundBuffer1);
			//Setting died sound
			died.setBuffer(soundBuffer2);
			soundBuffer2.loadFromFile("audio/oof.ogg");
			died.setBuffer(soundBuffer2);
		}
		Player (const std::string n) {
			if(n == "Flash") {
				if (!texture.loadFromFile("assets/flash.png")) {
				    // error...
				}
			}
			if(n == "Eren") {
				if (!texture.loadFromFile("assets/eren.png")) {
				    // error...
				}
			}
			if(n == "Elon") {
				if (!texture.loadFromFile("assets/elon.png")) {
				    // error...
				}
			}
			if(n == "Einstein") {
				if (!texture.loadFromFile("assets/einstein.png")) {
				    // error...
				}
			}
			if(n == "Batman") {
				if (!texture.loadFromFile("assets/batman.png")) {
				    // error...
				}
			}
			if(n == "Bateman") {
				if (!texture.loadFromFile("assets/bateman.png")) {
				    // error...
				}
			}
			origin = sf::Vector2f(sprite.getGlobalBounds().width / 2, sprite.getGlobalBounds().height / 2);
			yPos = SCREENH/3;
			velocity = 0;
			gravity = 0.5;
			sprite.setTexture(texture);
			sprite.setOrigin(origin);
			rotation_speed = 0;
			speed = 4.5;
			
			scored.setBuffer(soundBuffer1);
			soundBuffer1.loadFromFile("audio/wow.ogg");
			scored.setBuffer(soundBuffer1);
			
			died.setBuffer(soundBuffer2);
			soundBuffer2.loadFromFile("audio/oof.ogg");
			died.setBuffer(soundBuffer2);
		}
		sf::Sprite& get_sprite() {
			return sprite;
		}
		sf::Texture& get_texture() {
			return texture;
		}
		sf::Music& get_music() {
			return music;
		}
		sf::Sound& get_scored() {
			return scored;
		}
		sf::Sound& get_died() {
			return died;
		}
		virtual void set_physics() = 0; //Rule so that each ability overrides its own physics!
	    void set_yPos(const float y) {
	    	yPos = y;
		}
		void set_velocity(const float v) {
			velocity = v;
		}
		void set_speed(const float s) {
			speed = s;
		}
		void set_gravity(const float g) {
			gravity = g;
		}
		void set_rotation_speed(const float r) {
			rotation_speed = r;
		}
		void set_isActive(const bool a) {
			isActive = a;
		}
		void fly() {
			velocity = 10.0f;
            rotation_speed-= 20.0f;
			if(rotation_speed < -90.0f) {
				rotation_speed = -90.0f;
			}
			sprite.setRotation(rotation_speed);
		}
		void fall() {

            velocity -= gravity;

            rotation_speed += 0.45f;

			if(rotation_speed < -45.0f) {
				rotation_speed += 0.45f;
			}

			if(rotation_speed > 90.0f) {
				rotation_speed = 90.0f;
			}

			sprite.setRotation(rotation_speed);

			if(velocity < -30) {
				velocity = -30;
			}
			
		}
		void play_scored() {
			scored.play();
			scored.setVolume(150);
		}
		void play_died() {
			died.play();
			died.setVolume(150);
		}
	    const float get_yPos() {
	    	return yPos;
		}
		const float get_velocity() {
	    	return velocity;
		}
	    const float get_gravity() {
	    	return gravity;
		}
		const float get_rotation_speed() {
			return rotation_speed;
		}
		const float get_speed() {
			return speed;
		}
		const bool get_isActive() {
			return isActive;
		}
		const bool isColliding(sf::RectangleShape& t, sf::RectangleShape& b) {
			if(sprite.getGlobalBounds().intersects(t.getGlobalBounds()) ||
				sprite.getGlobalBounds().intersects(b.getGlobalBounds()) ||
				yPos > SCREENH) {
					
				return true;
			} else {
				return false;
			}
		}
		const bool scoreCheck(Pipe& b) {
			if(b.get_sprite().getPosition().x == (SCREENW/10)+15 || b.get_sprite().getPosition().x == (SCREENW/10)+20 ||
			   b.get_sprite().getPosition().x == (SCREENW/10)+10) {
					return true;
			    } else {
			   		return false;
			    }
		}
};

class SuperSpeed: public Player {
	public:
		//Overriding set_physics
		void set_physics() {
			set_speed(8.5); // for superspeed
		}
		SuperSpeed() {
			//superspeeders have... super speed, ofc!
			set_physics();
		}
		SuperSpeed(const string t):Player(t) {
			set_physics();
		}
		//Overriding ScoreCheck() function
		const bool scoreCheck(Pipe& b) {
			if(b.get_sprite().getPosition().x == (SCREENW/10)+10 || b.get_sprite().getPosition().x == (SCREENW/10)+17.5 ||
			   b.get_sprite().getPosition().x == (SCREENW/10)+11) {
					return true;
			    } else {
			   		return false;
			    }
		}
};

class Flash: public SuperSpeed {
	public:
		void set_sounds() {
			
		}
		Flash():SuperSpeed("Flash") {
			
		}
};

class Eren: public SuperSpeed {
	public:
		void set_sounds() {
			
		}
		Eren():SuperSpeed("Eren") {
			
		}
};

class SuperCheater: public Player {
	public:
		SuperCheater() {
			// super cheaters cheat on the collision mechanism
		}
		SuperCheater(const string t):Player(t) {
			set_physics();
		}
		void set_physics() {
			//left blank, as default physics is required
		}
		//overriding isColliding() function 
		const bool isColliding(sf::RectangleShape& t, sf::RectangleShape& b) {
			if(get_yPos() > SCREENH) {
				return true;
			} else {
				return false;
			}
		}
};

class Elon: public SuperCheater {
	public:
		void set_sounds() {
			
		}
		Elon():SuperCheater("Elon") {
			
		}
};

class Bateman: public SuperCheater {
	public:
		void set_sounds() {
			
		}
		Bateman():SuperCheater("Bateman") {
			
		}
};

class SuperFlipper: public Player {
	public:
		SuperFlipper() {
			
		}
		SuperFlipper(const string t):Player(t) {
			
		}
		void set_physics() {
			//left blank, as default physics is required
		}
		void fly() {
			set_velocity(8.0f);
			get_sprite().setRotation(get_rotation_speed());
		}
		void fall() {
			set_velocity(get_velocity() - get_gravity());
            set_rotation_speed(get_rotation_speed() - 4.0f);

			get_sprite().setRotation(get_rotation_speed());

			if(get_velocity() < -30) {
				set_velocity(-30);
			}
		}
};

class Batman: public SuperFlipper {
	public:
		void set_sounds() {
			
		}
		Batman():SuperFlipper("Batman") {
			
		}
};

class Einstein: public SuperFlipper {
	public:
		Einstein():SuperFlipper("Einstein") {
			
		}
		void set_sounds() {
			
		}
};

class ScoreManager {
	fstream highestscore;
	std::ostringstream ssScore;
	std::ostringstream hhScore;
	sf::Text scoreText;
	sf::Text highscoreText;
	sf::Font font;
	
	sf::Texture texture;
	
	sf::Sprite gameOver;
	
	int score, highscore;
	
	public:
		ScoreManager() {
		    // Load it from a file
			if (!font.loadFromFile("FlappyBirdRegular-9Pq0.ttf"))
			{
			    // error...
			}
			scoreText.setString(ssScore.str());
			scoreText.setFont(font);
			scoreText.setCharacterSize(40);
			scoreText.setFillColor(sf::Color(70,130,180));
			scoreText.setOutlineColor(sf::Color::White);
			scoreText.setOutlineThickness(5);
			
			highscoreText.setString(hhScore.str());
			highscoreText.setFont(font);
			highscoreText.setCharacterSize(70);
			highscoreText.setFillColor(sf::Color(196,26,26));
			highscoreText.setOutlineColor(sf::Color::White);
			highscoreText.setOutlineThickness(3);
			
			if (!texture.loadFromFile("assets/screen.png"))
			{
			    // error...
			}
			gameOver.setTexture(texture);
			try {
				//Reading previous highest score
				highestscore.open("highestscore.txt", ios::in);
				highestscore >> highscore;
				//Setting the highscore value after reading:
				/*
				'Decryption' process: subtract 837283 from the file value as:
				83 = S (Saad)
				72 = H (Haris)
				83 = S (Shahmeer)
				*/
				highscore -= 837283;
			}
			catch(int x) {
				exit(1);
			}
		}
		void store_highestscore() {
			//Storing highscore using expection handling:
			try {
				highestscore.open("highestscore.txt", ios::out);
				/*
				'Encryption' process: add 837283 to the file value as:
				83 = S (Saad)
				72 = H (Haris)
				83 = S (Shahmeer)
				*/
				highestscore << highscore + 837283;
				highestscore.close();
			} catch(int x) {
				static int tries = 0;
				if(tries <= 3) {
					tries++;
					store_highestscore(); // recursive call to retry 3 times then exit
				} else {
					exit(1);
				}
			}
			
		}
		operator ++(int) {
			score++;
		}
		void display_score() {
			ssScore.str("");
			ssScore << "Score: " << score;
			scoreText.setString(ssScore.str());
		}
		void display_highscore() {
			hhScore.str("");
			hhScore << "Highscore: " << highscore;
			highscoreText.setString(hhScore.str());
		}
		void set_highscore(const int h) {
			highscore = h;
		}
		void set_score(const int h) {
			score = h;
		}
		sf::Text& get_scoreText() {
			return scoreText;
		}
		sf::Text& get_highscoreText() {
			return highscoreText;
		}
		sf::Sprite& get_gameOver() {
			return gameOver;
		}
		const int get_score() {
			return score;
		}
		const int get_highscore() {
			return highscore;
		}
};

ScoreManager sm;

Flash p1;
Eren p2;
Elon p3;
Einstein p4;
Batman p5;
Bateman p6;

// Class for background of the game!
class Background {
	sf::Texture texture;
	sf::Sprite bg;
	
	public:
		Background() {
			if (!texture.loadFromFile("assets/bg.jpg")) {
			    // error...
			}
			bg.setTexture(texture);
			bg.setScale(sf::Vector2f(1.2f, 1.0f));
		}
		void change_background(string bgPath) {
			texture.loadFromFile(bgPath);
			bg.setTexture(texture);
			bg.setScale(sf::Vector2f(1.2f, 1.0f));
		}
		sf::Sprite& get_bg() {
			return bg;
		}
};

class GameManager {
	Background background;
	bool started;
	public:
		GameManager() {
			started = false;
		}
		Background& get_background() {
			return background;
		}
		void set_started(const bool s) {
			started = s;
		}
		const bool get_started() {
			return started;
		}
		template <class pl1, class pl2, class pl3, class pl4, class pl5, class pl6>
		void change_active(pl1& pp1, pl2& pp2, pl3& pp3, pl4& pp4, pl5& pp5, pl6& pp6, int select) {
			pp1.set_isActive(false);
			pp2.set_isActive(false);
			pp3.set_isActive(false);
			pp4.set_isActive(false);
			pp5.set_isActive(false);
			pp6.set_isActive(false);
			switch(select) {
				case 1:
					pp1.set_isActive(true);
					break;
				case 2:
					pp2.set_isActive(true);
					break;
				case 3:
					pp3.set_isActive(true);
					break;
				case 4:
					pp4.set_isActive(true);
					break;
				case 5:
					pp5.set_isActive(true);
					break;
				case 6:
					pp6.set_isActive(true);
					break;
				default:
					break;
			}
		}
};

GameManager gm;

class MusicManager {
	//Main menu music
    sf::Music music;
	public:
		MusicManager() {
			music.openFromFile("audio/projsound.ogg"); //default music
			music.setVolume(10);
			music.play();
			music.setLoop(true);
		}
		template <class pl1, class pl2, class pl3, class pl4, class pl5, class pl6>
		void change_music(pl1& pp1, pl2& pp2, pl3& pp3, pl4& pp4, pl5& pp5, pl6& pp6, int select) {
			music.pause();
			pp1.get_music().pause();
			pp2.get_music().pause();
			pp3.get_music().pause();
			pp4.get_music().pause();
			pp5.get_music().pause();
			pp6.get_music().pause();
			switch(select) {
				case 1:
					pp1.get_music().openFromFile("audio/flash.ogg");
					pp1.get_music().setVolume(10);
					pp1.get_music().play();
					pp1.get_music().setLoop(true);
					break;
				case 2:
					pp2.get_music().openFromFile("audio/eren.ogg");
					pp2.get_music().setVolume(10);
					pp2.get_music().play();
					pp2.get_music().setLoop(true);
					break;
				case 3:
					pp3.get_music().openFromFile("audio/elon.ogg");
					pp3.get_music().setVolume(10);
					pp3.get_music().play();
					pp3.get_music().setLoop(true);
					break;
				case 4:
					pp4.get_music().openFromFile("audio/einstein.ogg");
					pp4.get_music().setVolume(10);
					pp4.get_music().play();
					pp4.get_music().setLoop(true);
					break;
				case 5:
					pp5.get_music().openFromFile("audio/batman.ogg");
					pp5.get_music().setVolume(10);
					pp5.get_music().play();
					pp5.get_music().setLoop(true);
					break;
				case 6:
					pp6.get_music().openFromFile("audio/bateman.ogg");
					pp6.get_music().setVolume(10);
					pp6.get_music().play();
					pp6.get_music().setLoop(true);
					break;
				default:
					break;
			}
		}
};

MusicManager mm;

// Reset
void reset(){	
	
	if(p1.get_isActive() == true) {
		p1.set_yPos(SCREENH/3);
	    p1.get_sprite().setRotation(0.0f);
	    p1.set_velocity(0);
	    p1.set_rotation_speed(0);
	} else if(p2.get_isActive() == true) {
		p2.set_yPos(SCREENH/3);
	    p2.get_sprite().setRotation(0.0f);
	    p2.set_velocity(0);
	    p2.set_rotation_speed(0);
	} else if(p3.get_isActive() == true) {
		p3.set_yPos(SCREENH/3);
	    p3.get_sprite().setRotation(0.0f);
	    p3.set_velocity(0);
	    p3.set_rotation_speed(0);
	} else if(p4.get_isActive() == true) {
		p4.set_yPos(SCREENH/3);
	    p4.get_sprite().setRotation(0.0f);
	    p4.set_velocity(0);
	    p4.set_rotation_speed(0);
	} else if(p5.get_isActive() == true) {
		p5.set_yPos(SCREENH/3);
	    p5.get_sprite().setRotation(0.0f);
	    p5.set_velocity(0);
	    p5.set_rotation_speed(0);
	} else if(p6.get_isActive() == true) {
		p6.set_yPos(SCREENH/3);
	    p6.get_sprite().setRotation(0.0f);
	    p6.set_velocity(0);
	    p6.set_rotation_speed(0);
	}

    Pipe::set_pipeX(SCREENW + (Pipe::get_pipeW() * 2));

    Pipe::set_spaceY( rand()%((SCREENH-(SCREENH/10))-Pipe::get_spacing()) );
    gm.set_started(false);
    sm.set_score(0);
}

int main(){
	
    // Set up SFML window
    sf::RenderWindow window(sf::VideoMode(SCREENW, SCREENH), "Flappy Saad-Haris-Shahmeer | SHS");
    window.setFramerateLimit(60); // game runs on 60 frames!

	
	gm.change_active(p1, p2, p3, p4, p5, p6, 1); // Making Player1 active when game turns on (Flash)
	
    // Set up Pipe stuff
    Pipe top = Pipe("top");
	Pipe bottom;
	top.get_sprite().setOrigin( sf::Vector2f(0, top.get_sprite().getGlobalBounds().height) );
    top.get_sprite().setPosition(sf::Vector2f(Pipe::get_pipeW(), Pipe::get_spacing()));
    bottom.get_sprite().setPosition(sf::Vector2f(Pipe::get_pipeW(),SCREENH - (Pipe::get_spaceY() + Pipe::get_spacing()) ));
    sf::RectangleShape topCollision(sf::Vector2f(Pipe::get_pipeW(), Pipe::get_spacing()));
    sf::RectangleShape bottomCollision(sf::Vector2f(Pipe::get_pipeW(),SCREENH - (Pipe::get_spaceY() + Pipe::get_spacing()) ));
    //Setting collision detectors to be transparent
    topCollision.setFillColor(sf::Color(0,0,0,0));
    bottomCollision.setFillColor(sf::Color(0,0,0,0));
    //Setting positions:
    
    sm.get_gameOver().setPosition(0,0);
	sm.get_highscoreText().setPosition((SCREENW/2)-160, 310);

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                // Change window size back to normal when it is changed
                case sf::Event::Resized:
                    window.setSize(sf::Vector2u(SCREENW, SCREENH));
                    break;
                case sf::Event::KeyPressed:
                    switch(event.key.code){
                        case sf::Keyboard::Space:
                        case sf::Keyboard::W:
                            // Start game if not already started
                            if(gm.get_started() == false){
                                gm.set_started(true);
                                break;
                            }
                            // Fly
                            if(p1.get_isActive() == true) {
								p1.fly();
							} else if(p2.get_isActive() == true) {
								p2.fly();
							} else if(p3.get_isActive() == true) {
								p3.fly();
							} else if(p4.get_isActive() == true) {
								p4.fly();
							} else if(p5.get_isActive() == true) {
								p5.fly();
							} else if(p6.get_isActive() == true) {
								p6.fly();
							}
                            
                            break;
                        case sf::Keyboard::R:
                            // Reset everything
                            reset();
                            break;
                        // Pause the game
                        case sf::Keyboard::P:
                        case sf::Keyboard::Escape:
                            if(gm.get_started() == false) {
                            	gm.set_started(true);
							} else {
								gm.set_started(false);
							}
                            break;
                        // PLAYER CHANGE:
                    	case sf::Keyboard::Numpad1:
                    	case sf::Keyboard::Num1:
                    		if(gm.get_started() == false) { // player can only be changed if game is paused!
                    			//Music setup
                    			mm.change_music(p1, p2, p3, p4, p5, p6, 1);
								
								//Background setup
								gm.get_background().change_background("assets/flash.jpg");
								
								gm.change_active(p1, p2, p3, p4, p5, p6, 1);
							}
							break;
						case sf::Keyboard::Numpad2:
                    	case sf::Keyboard::Num2:
							if(gm.get_started() == false) {
								//Music setup
								mm.change_music(p1, p2, p3, p4, p5, p6, 2);
								
								//Background setup
								gm.get_background().change_background("assets/eren.jpg");
								
	    						gm.change_active(p1, p2, p3, p4, p5, p6, 2);
							}
							break;
						case sf::Keyboard::Numpad3:
                    	case sf::Keyboard::Num3:
							if(gm.get_started() == false) {
								//Music setup
								mm.change_music(p1, p2, p3, p4, p5, p6, 3);
								
								//Background setup
								gm.get_background().change_background("assets/elon.jpg");
								
	    						gm.change_active(p1, p2, p3, p4, p5, p6, 3);
							}
							break;
						case sf::Keyboard::Numpad4:
                    	case sf::Keyboard::Num4:
							if(gm.get_started() == false) {
								//Music setup
								mm.change_music(p1, p2, p3, p4, p5, p6, 4);
								
								//Background setup
								gm.get_background().change_background("assets/brain.jpg");
								
	    						gm.change_active(p1, p2, p3, p4, p5, p6, 4);
							}
							break;
						case sf::Keyboard::Numpad5:
                    	case sf::Keyboard::Num5:
							if(gm.get_started() == false) {
								//Music setup
								mm.change_music(p1, p2, p3, p4, p5, p6, 5);
								
								//Background setup
								gm.get_background().change_background("assets/batman.jpg");
								
	    						gm.change_active(p1, p2, p3, p4, p5, p6, 5);
							}
							break;
						case sf::Keyboard::Numpad6:
                    	case sf::Keyboard::Num6:
							if(gm.get_started() == false) {
								//Music setup
								mm.change_music(p1, p2, p3, p4, p5, p6, 6);
								
								//Background setup
								gm.get_background().change_background("assets/bateman.jpg");
								
	    						gm.change_active(p1, p2, p3, p4, p5, p6, 6);
							}
							break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
        if(gm.get_started() == true){ //checking if game is started
			sm.display_score();

            // Update positions and other game physics stuff
            if(p1.get_isActive() == true) {
				//Player falls
				p1.fall();
	
	            p1.set_yPos(p1.get_yPos() - p1.get_velocity());
	            if(p1.get_yPos() < 0)
	                p1.set_yPos(0);
	            Pipe::set_pipeX(Pipe::get_pipeX()-p1.get_speed());
	            
	            //Update score
	            if(p1.scoreCheck(bottom) ) {
	            	sm++; //add 1 to score
		            sm.display_score();
					
					//Playing sound
					p1.play_scored();
					
					if(sm.get_score() >= sm.get_highscore()){
	        			
	        			//Setting the highest score
						sm.set_highscore( sm.get_score() );
	        			
	        			//Storing the highest score
	        			sm.store_highestscore();
					}
				}
	            
			} else if(p2.get_isActive() == true) {
				//Player falls
				p2.fall();
	
	            p2.set_yPos(p2.get_yPos() - p2.get_velocity());
	            if(p2.get_yPos() < 0)
	                p2.set_yPos(0);
	            Pipe::set_pipeX(Pipe::get_pipeX()-p2.get_speed());
	            
		        //Update score
	            if(p2.scoreCheck(bottom) ) {
	            	sm++;
		            sm.display_score();
		            
		            //Playing sound
					p2.play_scored();
					
					if(sm.get_score() >= sm.get_highscore()){
	        			
	        			//Setting the highest score

						sm.set_highscore( sm.get_score() );
	        			
	        			//Storing the highest score
	        			sm.store_highestscore();	
					}
				}
			} else if(p3.get_isActive() == true) {
				//Player falls
				p3.fall();
	
	            p3.set_yPos(p3.get_yPos() - p3.get_velocity());
	            if(p3.get_yPos() < 0)
	                p3.set_yPos(0);
	            Pipe::set_pipeX(Pipe::get_pipeX()-p3.get_speed());
	            
		        //Update score
	            if(p3.scoreCheck(bottom) ) {
	            	sm++;
		            sm.display_score();
		            
		            //Playing sound
					p3.play_scored();
					
					if(sm.get_score() >= sm.get_highscore()){
	        			
	        			//Setting the highest score

						sm.set_highscore( sm.get_score() );
	        			
	        			//Storing the highest score
	        			sm.store_highestscore();	
					}
				}
			} else if(p4.get_isActive() == true) {
				//Player falls
				p4.fall();
	
	            p4.set_yPos(p4.get_yPos() - p4.get_velocity());
	            if(p4.get_yPos() < 0)
	                p4.set_yPos(0);
	            Pipe::set_pipeX(Pipe::get_pipeX()-p4.get_speed());
	            
		        //Update score
	            if(p4.scoreCheck(bottom) ) {
	            	sm++;
		            sm.display_score();
		            
		            //Playing sound
					p4.play_scored();
					
					if(sm.get_score() >= sm.get_highscore()){
	        			
	        			//Setting the highest score
						sm.set_highscore( sm.get_score() );
	        			
	        			//Storing the highest score
	        			sm.store_highestscore();	
					}
				}
			} else if(p5.get_isActive() == true) {
				//Player falls
				p5.fall();
	
	            p5.set_yPos(p5.get_yPos() - p5.get_velocity());
	            if(p5.get_yPos() < 0)
	                p5.set_yPos(0);
	            Pipe::set_pipeX(Pipe::get_pipeX()-p5.get_speed());
	            
		        //Update score
	            if(p5.scoreCheck(bottom) ) {
	            	sm++;
		            sm.display_score();
		            
		            //Playing sound
					p5.play_scored();
					
					if(sm.get_score() >= sm.get_highscore()){
	        			
	        			//Setting the highest score
						sm.set_highscore( sm.get_score() );
	        			
	        			//Storing the highest score
	        			sm.store_highestscore();
					}
				}
			} else if(p6.get_isActive() == true) {
				//Player falls
				p6.fall();
	
	            p6.set_yPos(p6.get_yPos() - p6.get_velocity());
	            if(p6.get_yPos() < 0)
	                p6.set_yPos(0);
	            Pipe::set_pipeX(Pipe::get_pipeX()-p6.get_speed());
	            
		        //Update score
	            if(p6.scoreCheck(bottom) ) {
	            	sm++;
		            sm.display_score();
		            
		            //Playing sound
					p6.play_scored();
					
					if(sm.get_score() >= sm.get_highscore()){
	        			
	        			//Setting the highest score

						sm.set_highscore( sm.get_score() );
	        			
	        			//Storing the highest score
	        			sm.store_highestscore();
					}
				}
			}
            

            //Make the pipe go back and change where the space is
            if(Pipe::get_pipeX() < -100){

                Pipe::set_pipeX(SCREENW + (Pipe::get_pipeW() * 2));

                Pipe::set_spaceY( rand()%((SCREENH-(SCREENH/10))-Pipe::get_spacing()) );
                top.get_sprite().setPosition(sf::Vector2f(Pipe::get_pipeW(), Pipe::get_spaceY()));

                topCollision.setSize(sf::Vector2f(Pipe::get_pipeW(), Pipe::get_spaceY()));
            }
             
            //Collision detection
            if(p1.get_isActive() == true) {
            	if(p1.isColliding(topCollision, bottomCollision) ) {
            		reset();
					
					//Playing sound
					p1.play_died();
					
					top.get_sprite().setPosition(sf::Vector2f(Pipe::get_pipeW(), Pipe::get_spaceY()));

                	topCollision.setSize(sf::Vector2f(Pipe::get_pipeW(), Pipe::get_spaceY()));
				}
			}
			//Collision detection
			else if(p2.get_isActive() == true) {
				if(p2.isColliding(topCollision, bottomCollision) ) {
					reset();
					
					//Playing sound
					p2.play_died();
					
					top.get_sprite().setPosition(sf::Vector2f(Pipe::get_pipeW(), Pipe::get_spaceY()));

                	topCollision.setSize(sf::Vector2f(Pipe::get_pipeW(), Pipe::get_spaceY()));
                }
			}
			//Collision detection
			else if(p3.get_isActive() == true) {
				if(p3.isColliding(topCollision, bottomCollision) ) {
					reset();
					
					//Playing sound
					p3.play_died();
					
					top.get_sprite().setPosition(sf::Vector2f(Pipe::get_pipeW(), Pipe::get_spaceY()));

                	topCollision.setSize(sf::Vector2f(Pipe::get_pipeW(), Pipe::get_spaceY()));
                }
			}
			//Collision detection
			else if(p4.get_isActive() == true) {
				if(p4.isColliding(topCollision, bottomCollision) ) {
					reset();
					
					//Playing sound
					p4.play_died();
					
					top.get_sprite().setPosition(sf::Vector2f(Pipe::get_pipeW(), Pipe::get_spaceY()));

                	topCollision.setSize(sf::Vector2f(Pipe::get_pipeW(), Pipe::get_spaceY()));
                }
			}
			//Collision detection
			else if(p5.get_isActive() == true) {
				if(p5.isColliding(topCollision, bottomCollision) ) {
					reset();
					
					//Playing sound
					p5.play_died();
					
					top.get_sprite().setPosition(sf::Vector2f(Pipe::get_pipeW(), Pipe::get_spaceY()));

                	topCollision.setSize(sf::Vector2f(Pipe::get_pipeW(), Pipe::get_spaceY()));
                }
			}
			//Collision detection
			else if(p6.get_isActive() == true) {
				if(p6.isColliding(topCollision, bottomCollision) ) {
					reset();
					
					//Playing sound
					p6.play_died();
					
					top.get_sprite().setPosition(sf::Vector2f(Pipe::get_pipeW(), Pipe::get_spaceY()));

                	topCollision.setSize(sf::Vector2f(Pipe::get_pipeW(), Pipe::get_spaceY()));
                }
			}
        }
        // If game is paused, show the menu:
        if(gm.get_started() == false) {
			sm.display_highscore();
		}
        
        // Showing and hiding player sprites depending on their isActive value:
        if(p1.get_isActive() == true ) {
        	p1.get_sprite().setPosition(SCREENW/10, p1.get_yPos());
		} else if(p1.get_isActive() == false) {
			p1.get_sprite().setPosition(-100, -100);
		}
		if(p2.get_isActive() == true ) {
        	p2.get_sprite().setPosition(SCREENW/10, p2.get_yPos());
		} else if(p2.get_isActive() == false) {
			p2.get_sprite().setPosition(-100, -100);
		}
		if(p3.get_isActive() == true ) {
        	p3.get_sprite().setPosition(SCREENW/10, p3.get_yPos());
		} else if(p3.get_isActive() == false) {
			p3.get_sprite().setPosition(-100, -100);
		}
		if(p4.get_isActive() == true ) {
        	p4.get_sprite().setPosition(SCREENW/10, p4.get_yPos());
		} else if(p4.get_isActive() == false) {
			p4.get_sprite().setPosition(-100, -100);
		}
		if(p5.get_isActive() == true ) {
        	p5.get_sprite().setPosition(SCREENW/10, p5.get_yPos());
		} else if(p5.get_isActive() == false) {
			p5.get_sprite().setPosition(-100, -100);
		}
		if(p6.get_isActive() == true ) {
        	p6.get_sprite().setPosition(SCREENW/10, p6.get_yPos());
		} else if(p6.get_isActive() == false) {
			p6.get_sprite().setPosition(-100, -100);
		}
		// Setting the position for score of the game:
        sm.get_scoreText().setPosition((SCREENW/2)-60, 740);
        
		//Pipe Sprites position setting:
		top.get_sprite().setPosition(sf::Vector2f(Pipe::get_pipeX(), Pipe::get_spaceY()));
		bottom.get_sprite().setPosition(sf::Vector2f(Pipe::get_pipeX(),(Pipe::get_spaceY() + Pipe::get_spacing()) ));
		
		//Colliders position setting:
		topCollision.setPosition(Pipe::get_pipeX(), 0);
        bottomCollision.setPosition(sf::Vector2f(Pipe::get_pipeX(),(Pipe::get_spaceY() + Pipe::get_spacing()) ));
		
		// Draw everything
        window.clear();
        window.draw(gm.get_background().get_bg());
        window.draw(p1.get_sprite());
        window.draw(p2.get_sprite());
        window.draw(p4.get_sprite());
        window.draw(p5.get_sprite());
        window.draw(topCollision);
        window.draw(bottomCollision);
        window.draw(top.get_sprite());
        window.draw(bottom.get_sprite());
        window.draw(p3.get_sprite());
        window.draw(p6.get_sprite());
		window.draw(sm.get_scoreText());
		if(gm.get_started() == false) {
			window.draw(sm.get_gameOver());
			window.draw(sm.get_highscoreText());
		}
        window.display();
    }

    return 0;
}
