/*
* Name: Cameron Lochray, Sam, Zahra
* Date: April 2, 2023
*/

// Core Libraries
#include "Player.h"
#include <crtdbg.h>
#include <iostream>
#include <Windows.h>
#include <SDL_Image.h>
#include <SDL.h> //allows us to use SDL library
#include <vector> //to make a container for the projectiles
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include "Blaster.h"
#include "Collision.h"
#include "Tilemap.h"


/*
* Use SDL to open a window and render some sprites at given locations and scales
*/

//global variables
constexpr float FPS = 60.0f;
constexpr float DELAY_TIME = 1000.0f / FPS; //target deltaTime in ms
const int SCREEN_WIDTH = 1200;
const int SCREEN_HEIGHT = 600;
float deltaTime = 1 / FPS; //time passing between frames in seconds

SDL_Window* pWindow = nullptr; //pointer to SDL_Window. It stores a menory location which we can use later.
SDL_Renderer* pRenderer = nullptr;
bool isGameRunning = true;
bool loseGame = false;

float enemySpawnDelay = 1.0f;
float enemySpawnTimer = 0.0f;
float enemyStartSpawnTimer = 1.0f;



//create new instances of struct Fund to load textures
Player player;

// Enemy to copy
Sprite enemyOriginal;


Sprite background;
Sprite planet;
Sprite asteroid;
std::vector<Blaster> playerBlasterContainer; //std::vector is a class which allows dynamic size. This is a dynamic array of Sprite
std::vector<Player> enemyContainer; //Contains Enemy Ships
std::vector<Blaster> enemyBlasterContainer; //Contains Enemy Projectiles


//audio files
Mix_Chunk* sfxShipHit;
Mix_Chunk* sfxPlayerShoot;
Mix_Music* bgmDefault;
int audioVolumeCurrent = MIX_MAX_VOLUME / 2;

//UI
TTF_Font* uiFont;
TTF_Font* uiLoseFont;
int scoreCurrent = 0;
Sprite uiSpriteScore;
Sprite uiSpriteHealth;
Sprite uiSpriteLose;

float shakeLevel = 0.0f; // betweeen 0 and 1
float shakeMagnitude = 20.0f;
float shakeDecay = 2.0f;
Vec2 scoreSpriteBasePosiiton = { 50,50 };
Vec2 healthSpriteBasePosiiton = { 800,50 };
Vec2 loseSpriteBasePosiiton = { 10,300 };

//input variables
bool isUpPressed = false;
bool isDownPressed = false;
bool isLeftPressed = false;
bool isRightPressed = false;
bool isShootPressed = false;
bool isDodgePressed = false;

//Map
Tilemap map;

//Audio
Mix_Chunk* LoadSound(const char* filePath)
{
	Mix_Chunk* sound = Mix_LoadWAV(filePath);
	if (sound == NULL)
	{
		std::cout << "Mix_LoadWAV failed to load file: " << filePath << "-" << SDL_GetError() << std::endl;
	}
	return sound;
}
void Start()
{
	Mix_Volume(-1, audioVolumeCurrent);
	Mix_PlayMusic(bgmDefault, -1);
}
//health
void Restart()
{
	loseGame = false;
	player.SetHealth(10);

	enemyContainer.clear();
	enemyBlasterContainer.clear();
}
void LoseGame()
{
	std::string loseGameString = "You Lose!! Press R to Restart";
	SDL_Color color = { 255,255,255,255 };
	uiSpriteLose = Sprite(uiLoseFont, loseGameString.c_str(), color,pRenderer);


	uiSpriteLose.position.x = loseSpriteBasePosiiton.x;
	uiSpriteLose.position.y = loseSpriteBasePosiiton.y;

	loseGame = true;
}
void TakeHealth(int damage)
{
	player.TakeHealth(1);
	if (player.GetHealth() <= 0)
	{
		LoseGame();
	}
}
//Score
void AddScore(int toAdd)
{
	scoreCurrent += toAdd;
	shakeLevel = min(1, shakeLevel + 0.5f);

}
//Spawn
void SpawnEnemy()
{
	//enemy textures
	Sprite enemy = enemyOriginal;

	//Spawning at Random Position
	enemy.position =
	{
		(float)(rand() % (SCREEN_WIDTH - (int)enemy.getSize().x)),
		 (0)
	};
	enemy.flipState = SDL_FLIP_HORIZONTAL;
	enemy.rotation = 270.0;

	Player enemy1;
	enemy1.sprite = enemy;

	enemy1.fireRepeatDelay = 1.5;
	enemy1.moveSpeedPx = 50;
	enemy1.shipHealth = 1;
	enemy1.RestShootCoodown();
	//Add to enemy
	enemyContainer.push_back(enemy1);
	//reset timer
	enemySpawnTimer = enemySpawnDelay;
}
//Collison
bool IsOffScreen(Sprite sprite)
{
	bool isOffLeft = sprite.position.x + sprite.getSize().x < 0;
	bool isOffRight = sprite.position.x > SCREEN_WIDTH;
	bool isOffTop = sprite.position.y + sprite.getSize().y < 0 - sprite.getSize().y;
	bool isOffBottom = sprite.position.y > SCREEN_HEIGHT;
	return (isOffLeft || isOffRight || isOffTop || isOffBottom);
}
void CollisionDetection()
{
	for (std::vector<Blaster>::iterator it = enemyBlasterContainer.begin(); it != enemyBlasterContainer.end();)
	{
		Sprite& enemyBlaster = it->sprite;
		if (AreSpritesOverlapping(player.sprite, enemyBlaster))
		{
			std::cout << "Player was Hit" << std::endl;
			if (!player.isDodging)
			{
				TakeHealth(1);
			}
				

			//sound when player gets hit
			Mix_PlayChannel(-1, sfxShipHit, 0);

			//remove this element from the container
			it = enemyBlasterContainer.erase(it);
		}
		if (it != enemyBlasterContainer.end())
		{
			it++;
		}
	}
	for (std::vector<Blaster>::iterator blasterIterator = playerBlasterContainer.begin(); blasterIterator != playerBlasterContainer.end();)
	{
		for (std::vector<Player>::iterator enemyIterator = enemyContainer.begin(); enemyIterator != enemyContainer.end();)
		{
			//Test for collision between player blaster and enemy
			if (AreSpritesOverlapping(blasterIterator->sprite, enemyIterator->sprite))
			{
				//destroy player projectile
				blasterIterator = playerBlasterContainer.erase(blasterIterator);
				//destroy enemy
				enemyIterator = enemyContainer.erase(enemyIterator);

				AddScore(100);
				//enemy gets hit
				Mix_PlayChannel(-1, sfxShipHit, 0);

				//if we destroy stop comparing
				if (blasterIterator == playerBlasterContainer.end())
				{
					break; // leave for loop
				}
			}
			if (enemyIterator != enemyContainer.end())
			{
				enemyIterator++;
			}
		}
		if (blasterIterator != playerBlasterContainer.end())
		{
			blasterIterator++;
		}
	}
}
void RemoveOffscreenSprites()
{
	for (auto blasterIterator = playerBlasterContainer.begin(); blasterIterator != playerBlasterContainer.end(); blasterIterator++)
	{
		if (IsOffScreen(blasterIterator->sprite))
		{
			blasterIterator->sprite.Cleanup();
			blasterIterator = playerBlasterContainer.erase(blasterIterator);
			if (blasterIterator == playerBlasterContainer.end())
			{
				break;
			}
		}

	}
	for (auto enemyBlasterIterator = enemyBlasterContainer.begin(); enemyBlasterIterator != enemyBlasterContainer.end(); enemyBlasterIterator++)
	{
		if (IsOffScreen(enemyBlasterIterator->sprite))
		{
			enemyBlasterIterator->sprite.Cleanup();
			enemyBlasterIterator = enemyBlasterContainer.erase(enemyBlasterIterator);
			if (enemyBlasterIterator == enemyBlasterContainer.end())
			{
				break;
			}
		}

	}
	for (auto enemyIterator = enemyContainer.begin(); enemyIterator != enemyContainer.end(); enemyIterator++)
	{
		if (IsOffScreen(enemyIterator->sprite))
		{
			enemyIterator = enemyContainer.erase(enemyIterator);
			if (enemyIterator == enemyContainer.end())
			{
				break;
			}
		}

	}
}
//Player
void UpdatePlayer()
{
	//moves the sprites
	Vec2 inputVector;
	if (isUpPressed)
	{
		inputVector.y = -1;
		if (player.sprite.position.y < 0)
		{
			player.sprite.position.y = 0;
		}
	}

	if (isDownPressed)
	{
		inputVector.y = 1;
		const int lowestPointScreen = SCREEN_HEIGHT - player.sprite.getSize().y;
		if (player.sprite.position.y > lowestPointScreen)
		{
			player.sprite.position.y = lowestPointScreen;
		}
	}
	if (isLeftPressed)
	{
		inputVector.x = -1;
		if (player.sprite.position.x < 0)
		{
			player.sprite.position.x = 0;
		}
	}
	if (isRightPressed)
	{
		inputVector.x = 1;
		const int leftmostPointScreen = SCREEN_WIDTH - player.sprite.getSize().x;
		if (player.sprite.position.x > leftmostPointScreen)
		{
			player.sprite.position.x = leftmostPointScreen;
		}
	}

	//if shooting and our shooting is off cooldown
	if (isShootPressed && player.CanShoot())
	{
		bool toUp = true;
		Vec2 velocity{ 0, -1000 };
		// Pass Blaster Container by referance to add blasts to the container specifically
		player.Shoot(toUp, playerBlasterContainer, velocity, pRenderer);

		//play shooting sound
		Mix_PlayChannel(-1, sfxPlayerShoot, 0);
	}
	
	if (isDodgePressed && player.CanDodge())
	{
		player.startDodge();
	}
	if (!player.duringDodge())
	{
		player.endDodge();
	}

	player.Move(inputVector,deltaTime);
	player.Update(deltaTime);
	//std::cout << player.sprite.position.y << std::endl;
}

//Keep
bool Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "SDL Init failed: " << SDL_GetError() << std::endl;
		return false;
	}
	std::cout << "SDL Init success\n";

	//Create and assign our SDL_Window pointer
	pWindow = SDL_CreateWindow("Milestone 4", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

	//not necessary to work but help figure out why it doens't work
	if (pWindow == NULL)
	{
		std::cout << "Window creation failed: " << SDL_GetError() << std::endl;
		return false;
	}
	else
	{
		std::cout << "Window creation success\n";
	}

	//Create and assign out SDL_Renderer pointer
	pRenderer = SDL_CreateRenderer(pWindow, -1, 0);

	if (pRenderer == NULL) //If CreateRenderer failed...
	{
		std::cout << "Renderer creation failed: " << SDL_GetError() << std::endl;
		return false;
	}
	else
	{
		std::cout << "Renderer creation success\n";
	}

	int  playbackFrequency = 22050;
	int chunkSize = 1024;
	if (Mix_OpenAudio(playbackFrequency, MIX_DEFAULT_FORMAT, 1, chunkSize) != 0)
	{
		std::cout << "Mix_OpenAudio failed: " << SDL_GetError() << std::endl;
		return false;
	}

	if (TTF_Init() != 0)
	{
		std::cout << "TTF Init creation failed: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}//keep
void Load()
{
	//Level textures
	map.LoadTextureForTile(F, pRenderer, "../Assets/textures/floor_tile_gray.png");
	map.LoadTextureForTile(W, pRenderer, "../Assets/textures/wall_red.png");


	//player textures
	char* fileToLoad = "../Assets/textures/fighter.png";

	player.sprite = Sprite(pRenderer, fileToLoad);

	Vec2 shipSize = player.sprite.getSize();
	int shipWidth = shipSize.x;
	int shipHeight = shipSize.y;

	//Describe location to paste to on the screen
	player.sprite.setSize(shipWidth, shipHeight);
	player.sprite.position = { (SCREEN_WIDTH / 2) - 50, 500 };

	//background texture
	background = Sprite(pRenderer, "../Assets/textures/stars.png");
	background.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);

	//planet texture
	planet = Sprite(pRenderer, "../Assets/textures/ring-planet.png");
	planet.position = { 300, 400 };

	//asteroid textures
	asteroid = Sprite(pRenderer, "../Assets/textures/asteroid1.png");
	asteroid.setSize(50, 50);
	asteroid.position = { 700, 350 };

	//load audio files
	sfxPlayerShoot = LoadSound("../Assets/audio/blaster.mp3");
	bgmDefault = Mix_LoadMUS("../Assets/audio/bgm.mp3");
	sfxShipHit = LoadSound("../Assets/audio/hit.mp3");

	if (bgmDefault == NULL)
	{
		std::cout << "Mix_LoadMUS failed to load file: " << SDL_GetError() << std::endl;
	}

	//load font
	fileToLoad = "../Assets/fonts/Consolas.ttf";
	uiFont = TTF_OpenFont(fileToLoad, 24);
	if (uiFont == NULL)
	{
		std::cout << "Font failed to load: " << fileToLoad;
	}
	uiLoseFont = TTF_OpenFont(fileToLoad, 70);
	if (uiLoseFont == NULL)
	{
		std::cout << "Font failed to load: " << fileToLoad;
	}

	enemyOriginal = Sprite(pRenderer, "../Assets/textures/d7_small.png");
} //keep
void Input()
{
	SDL_Event event; //event data polled each time
	while (SDL_PollEvent(&event)) //polled until all events are handeled
	{
		//decide what to do with this event
		switch (event.type)
		{
		case(SDL_KEYDOWN):
		{
			SDL_Scancode key = event.key.keysym.scancode;
			switch (key)
			{
			case(SDL_SCANCODE_W):
			{
				isUpPressed = true;
				break;
			}

			case(SDL_SCANCODE_S):
			{
				isDownPressed = true;
				break;
			}

			case(SDL_SCANCODE_A):
			{
				isLeftPressed = true;
				break;
			}

			case(SDL_SCANCODE_D):
			{
				isRightPressed = true;
				break;
			}

			case(SDL_SCANCODE_SPACE):
			{
				isShootPressed = true;
				break;
			}
			case(SDL_SCANCODE_R):
			{
				Restart();
				break;
			}
			case(SDL_SCANCODE_I):
			{
				isDodgePressed = true;
				break;
			}
			break;
			}
			break;
		}
		case(SDL_KEYUP):
		{
			SDL_Scancode key = event.key.keysym.scancode;
			switch (key)
			{
			case(SDL_SCANCODE_W):
			{
				isUpPressed = false;
				break;
			}

			case(SDL_SCANCODE_S):
			{
				isDownPressed = false;
				break;
			}

			case(SDL_SCANCODE_A):
			{
				isLeftPressed = false;
				break;
			}

			case(SDL_SCANCODE_D):
			{
				isRightPressed = false;
				break;
			}

			case(SDL_SCANCODE_SPACE):
			{
				isShootPressed = false;
				break;
			}
			case(SDL_SCANCODE_I):
			{
				isDodgePressed = false;
				break;
			}
			case(SDL_SCANCODE_EQUALS):
			{
				//increase volume
				audioVolumeCurrent = min(audioVolumeCurrent + 10, MIX_MAX_VOLUME);
				Mix_Volume(-1, audioVolumeCurrent);
				std::cout << "Volume: " << audioVolumeCurrent << std::endl;
				break;
			}
			case(SDL_SCANCODE_MINUS):
			{
				//decrease volume
				audioVolumeCurrent = max(audioVolumeCurrent - 10, 0);
				Mix_Volume(-1, audioVolumeCurrent);
				std::cout << "Volume: " << audioVolumeCurrent << std::endl;
				break;
			}
			}
			break;
		}

		}
	}
}//keep
void Update()
{
	if (loseGame == false)
	{
		UpdatePlayer();//moves the sprites
		CollisionDetection(); //Detects collsions
	}


	Vec2 inputVector;


	//Update blasters across the screen
	for (int i = 0; i < playerBlasterContainer.size(); i++)
	{

		playerBlasterContainer[i].Update(deltaTime);
	}
	//Update enemy blasters across the screen
	for (int i = 0; i < enemyBlasterContainer.size(); i++)
	{

		enemyBlasterContainer[i].Update(deltaTime);
	}
	//Update enemy ships
	for (int i = 0; i < enemyContainer.size(); i++)
	{
		//Reference to enemy at index I
		Player& enemy = enemyContainer[i];

		enemy.Move({ 0, 1 }, deltaTime);
		enemy.Update(deltaTime);
		if (enemy.CanShoot())
		{
			bool towardUp = false;
			Vec2 velocity = { 0,200 };
			enemy.Shoot(towardUp, enemyBlasterContainer, velocity, pRenderer);
		}
	}
	//Spawn enemies on timer
	if (loseGame == false)
	{
		if (enemySpawnTimer <= 0)
		{
			SpawnEnemy();
		}
		else
		{
			enemySpawnTimer -= deltaTime;
		}
	}

	//moves background
	planet.position.y += 0.7;
	if (planet.position.y >= SCREEN_HEIGHT)
	{
		planet.position.y = -200;
	}
	//moves background
	background.position.y += 0.5;
	if (background.position.y >= SCREEN_HEIGHT)
	{
		background.position.y = -SCREEN_HEIGHT;

	}
	//moves background
	asteroid.position.y += 1;
	if (asteroid.position.y >= SCREEN_HEIGHT)
	{
		asteroid.position.y = -SCREEN_HEIGHT;

	}
	RemoveOffscreenSprites();
}//keep
void Draw()
{
	if (loseGame == false)
	{
		//changes background color
		SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 0);

		// refreshes the frame so ship doesn't smear when it moves
		SDL_RenderClear(pRenderer);
		background.Draw(pRenderer);
		map.Draw(pRenderer);

		planet.Draw(pRenderer);
		asteroid.Draw(pRenderer);
		player.sprite.Draw(pRenderer);

		//draw all blasters on the screen
		for (int i = 0; i < playerBlasterContainer.size(); i++)
		{
			playerBlasterContainer[i].sprite.Draw(pRenderer);
		}

		//draw enemy blasters
		for (int i = 0; i < enemyBlasterContainer.size(); i++)
		{
			enemyBlasterContainer[i].sprite.Draw(pRenderer);
		}
		//draw all enemies
		for (int i = 0; i < enemyContainer.size(); i++)
		{
			enemyContainer[i].sprite.Draw(pRenderer);
		}

		std::string scoreString = "Score: " + std::to_string(scoreCurrent);
		SDL_Color color = { 255,255,255,255 };

		uiSpriteScore = Sprite(uiFont, scoreString.c_str(), color, pRenderer);

		std::string healthString = "Player Health: " + std::to_string(player.GetHealth());

		uiSpriteHealth = Sprite(uiFont, healthString.c_str(), color, pRenderer);

		// RIP takeoff o7
		Vec2 offset =
		{
			shakeLevel * shakeMagnitude * (float)(rand() % 10000) * 0.0001,
			shakeLevel * shakeMagnitude * (float)(rand() % 10000) * 0.0001
		};

		uiSpriteScore.position.x = scoreSpriteBasePosiiton.x + offset.x;
		uiSpriteScore.position.y = scoreSpriteBasePosiiton.y + offset.y;

		uiSpriteHealth.position.x = healthSpriteBasePosiiton.x + offset.x;
		uiSpriteHealth.position.y = healthSpriteBasePosiiton.y + offset.y;

		uiSpriteScore.Draw(pRenderer);
		uiSpriteHealth.Draw(pRenderer);

		shakeLevel = max(0, shakeLevel - deltaTime * shakeDecay);
		//show the hidden space we were drawing to called the BackBuffer. 
		//For more information why we use this, look up Double Buffering
		SDL_RenderPresent(pRenderer);
	}
	else
	{
		//changes background color
		SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 0);
		// refreshes the frame so ship doesn't smear when it moves
		SDL_RenderClear(pRenderer);
		background.Draw(pRenderer);
		planet.Draw(pRenderer);
		uiSpriteLose.Draw(pRenderer);
		SDL_RenderPresent(pRenderer);
	}


}//keep
void Cleanup()
{
	background.Cleanup();
	player.sprite.Cleanup();
	//iterate through all sprites and call cleanup
	for (auto blaster : playerBlasterContainer)
	{
		blaster.sprite.Cleanup();
	}
	for (auto blaster : enemyBlasterContainer)
	{
		blaster.sprite.Cleanup();
	}
	for (auto enemy : enemyContainer)
	{
		enemy.sprite.Cleanup();
	}

	player.sprite.Cleanup();
	TTF_Quit();
	Mix_FreeChunk(sfxPlayerShoot);
	Mix_FreeMusic(bgmDefault);
	Mix_CloseAudio();
	SDL_DestroyWindow(pWindow);
	SDL_DestroyRenderer(pRenderer);
	SDL_Quit();
}//keep


/**
 * \brief Program Entry Point
 */
int main(int argc, char* args[])
{

	// show and position the application console
	AllocConsole();
	auto console = freopen("CON", "w", stdout);
	const auto window_handle = GetConsoleWindow();
	MoveWindow(window_handle, 100, 700, 800, 200, TRUE);

	// Display Main SDL Window
	isGameRunning = Init();

	Load();

	Start();

	enemySpawnTimer = enemyStartSpawnTimer;

	// Main Game Loop
	while (isGameRunning)
	{
		const auto frame_start = static_cast<float>(SDL_GetTicks());
		//if statement?
		Input();//take player input

		Update();//update game state (presumably based on other conditions and input)

		Draw();//draw to screen to show new game state to player

		//figure out how long we need to wait for the next frame timing
		//current time - time at start of frame = time elapsed during this frame

		if (const float frame_time = static_cast<float>(SDL_GetTicks()) - frame_start;
			frame_time < DELAY_TIME)
		{
			SDL_Delay(static_cast<int>(DELAY_TIME - frame_time));
		}

		// delta time
		deltaTime = (static_cast<float>(SDL_GetTicks()) - frame_start) / 1000.0f;


	}

	return 0;
}
