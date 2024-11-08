#include "raylib.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

const int screenWidth = 1400;
const int screenHeight = 1400;
const char *highScoreFile = "highscore.txt";

Color white = WHITE;
Color red = RED;
Color lightGreen = (Color){148, 238, 144, 255};
Color gray = (Color){100, 100, 100, 255};

const int roadSize = ((3.0 / 5) * screenWidth);
const int laneWidth = roadSize / 3;
const int left = (1.0 / 5) * screenWidth;
const int center = left + laneWidth;
const int right = left + 2 * laneWidth;
const int borderWidth = 10;
const int borderHeight = 50;
const int playerYCoordinate = (4.0 / 5) * screenHeight;

class Vehicle
{
public:
    Texture2D texture;
    Rectangle rect;
    int speed;

    Vehicle() : speed(0) {}

    void Initialize(const char *texturePath, int lane)
    {
        texture = LoadTexture(texturePath);
        rect = (Rectangle){(float)(lane + laneWidth / 2 - texture.width / 2),
                           -(float)texture.height,
                           (float)texture.width, (float)texture.height};
    }

    void Unload()
    {
        UnloadTexture(texture);
    }
};

class Player
{
public:
    Texture2D texture;
    Rectangle rect;
    int lane;

    Player() : lane(1) {}

    void Initialize(const char *texturePath)
    {
        texture = LoadTexture(texturePath);
        rect = (Rectangle){(float)(center + 0.5 * laneWidth - texture.width / 2),
                           (float)playerYCoordinate,
                           (float)texture.width, (float)texture.height};
    }

    void Unload()
    {
        UnloadTexture(texture);
    }
};

enum class GameScreen
{
    MENU,
    PLAY,
    HOW_TO_PLAY,
    HIGH_SCORE
};

int LoadHighScore()
{
    int highScore = 0;
    std::ifstream file(highScoreFile);
    if (file.is_open())
    {
        file >> highScore;
        file.close();
    }
    return highScore;
}

void SaveHighScore(int score)
{
    int highScore = LoadHighScore();
    if (score > highScore)
    {
        std::ofstream file(highScoreFile);
        if (file.is_open())
        {
            file << score;
            file.close();
        }
    }
}

void ResetGame(Player &player, Vehicle *vehicles, int &vehicleCount, int &score, int &speed, bool &gameOver, int &laneMoveY)
{
    vehicleCount = 0;
    score = 0;

    speed = 2;
    gameOver = false;
    laneMoveY = 0;

    player.rect.x = center + 0.5 * laneWidth - player.texture.width / 2;
    player.rect.y = playerYCoordinate;
    player.lane = 1;

    for (int i = 0; i < 3; i++)
    {
        vehicles[i].Unload();
    }
}
void SpawnVehicle(Vehicle *vehicles, int &vehicleCount, const char *vehicleTextures[])
{
    bool laneOccupied[3] = {false, false, false}; 
    for (int i = 0; i < vehicleCount; i++)
    {
        if (vehicles[i].rect.y < screenHeight) 
        {
            laneOccupied[(int)((vehicles[i].rect.x - left) / laneWidth)] = true; 
        }
    }
    int lane = rand() % 3; 
    while (laneOccupied[lane]) 
    {
        lane = rand() % 3;
    }
    int offset = rand() % 2 == 0 ? -200 : 0;
    vehicles[vehicleCount].Initialize(vehicleTextures[rand() % 4], left + lane * laneWidth);
    vehicles[vehicleCount].rect.y += offset;
    vehicleCount++;
}


int main()
{
    InitWindow(screenWidth, screenHeight, "Endless Car Racer");
    SetTargetFPS(120);

    Player player;
    player.Initialize("images/car.png");

    Vehicle vehicles[3];
    int vehicleCount = 0;
    int speed = 2;
    int score = 0;
    int laneMoveY = 0;
    bool gameOver = false;
    GameScreen currentScreen = GameScreen::MENU;

    const char *vehicleTextures[] = {"images/pickup_truck.png", "images/semi_trailer.png",
                                     "images/taxi.png", "images/van.png"};
    srand(time(0));

    Texture2D crashImage = LoadTexture("images/crash.png");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(lightGreen);

        if (currentScreen == GameScreen::MENU)
        {
            int roadCenter = left + roadSize / 2;
            DrawText("Endless Car Racer", roadCenter - MeasureText("Endless Car Racer", 60) / 2, screenHeight / 4, 60, red);
            DrawText("1. Play", roadCenter - MeasureText("1. Play", 40) / 2, screenHeight / 2 - 50, 40, white);
            DrawText("2. How to Play", roadCenter - MeasureText("2. How to Play", 40) / 2, screenHeight / 2, 40, white);
            DrawText("3. High Score", roadCenter - MeasureText("3. High Score", 40) / 2, screenHeight / 2 + 50, 40, white);
            DrawText("Press the respective number key to select an option", roadCenter - MeasureText("Press the respective number key to select an option", 30) / 2, screenHeight / 2 + 150, 30, white);

            if (IsKeyPressed(KEY_ONE))
                currentScreen = GameScreen::PLAY;
            else if (IsKeyPressed(KEY_TWO))
                currentScreen = GameScreen::HOW_TO_PLAY;
            else if (IsKeyPressed(KEY_THREE))
                currentScreen = GameScreen::HIGH_SCORE;
        }
        else if (currentScreen == GameScreen::HOW_TO_PLAY)
        {
            int roadCenter = left + roadSize / 2;
            DrawText("How to Play", roadCenter - MeasureText("How to Play", 60) / 2, screenHeight / 4, 60, red);
            DrawText("Use arrow keys to move left or right.", roadCenter - MeasureText("Use arrow keys to move left or right.", 30) / 2, screenHeight / 2 - 50, 30, white);
            DrawText("Avoid other vehicles and stay on the road!", roadCenter - MeasureText("Avoid other vehicles and stay on the road!", 30) / 2, screenHeight / 2, 30, white);
            DrawText("Press 'Backspace' to return to the menu", roadCenter - MeasureText("Press 'Backspace' to return to the menu", 20) / 2, screenHeight / 2 + 100, 20, white);

            if (IsKeyPressed(KEY_BACKSPACE))
                currentScreen = GameScreen::MENU;
        }
        else if (currentScreen == GameScreen::HIGH_SCORE)
        {
            int roadCenter = left + roadSize / 2;
            int highScore = LoadHighScore();
            DrawText("High Score", roadCenter - MeasureText("High Score", 60) / 2, screenHeight / 4, 60, red);
            DrawText(TextFormat("High Score: %d", highScore), roadCenter - MeasureText(TextFormat("High Score: %d", highScore), 40) / 2, screenHeight / 2, 40, white);
            DrawText("Press 'Backspace' to return to the menu", roadCenter - MeasureText("Press 'Backspace' to return to the menu", 20) / 2, screenHeight / 2 + 100, 20, white);

            if (IsKeyPressed(KEY_BACKSPACE))
                currentScreen = GameScreen::MENU;
        }
        else if (currentScreen == GameScreen::PLAY)
        {
            if (!gameOver)
            {
                if (IsKeyPressed(KEY_LEFT) && player.lane > 0)
                {
                    player.lane--;
                    player.rect.x = left + player.lane * laneWidth + 0.5 * laneWidth - player.texture.width / 2;
                }
                if (IsKeyPressed(KEY_RIGHT) && player.lane < 2)
                {
                    player.lane++;
                    player.rect.x = left + player.lane * laneWidth + 0.5 * laneWidth - player.texture.width / 2;
                }

                if (vehicleCount < 2)
                {
                    // int lane = left + laneWidth * (rand() % 3);
                    // vehicles[vehicleCount].Initialize(vehicleTextures[rand() % 4], lane);
                    // vehicleCount++;
                    SpawnVehicle(vehicles, vehicleCount, vehicleTextures);
                }

                for (int i = 0; i < vehicleCount; i++)
                {
                    vehicles[i].rect.y += speed;
                    if (vehicles[i].rect.y >= screenHeight)
                    {
                        vehicles[i].Unload();
                        vehicles[i] = vehicles[--vehicleCount];
                        score++;
                        if (score % 5 == 0 && score < 70)
                            speed++;
                    }

                    if (CheckCollisionRecs(player.rect, vehicles[i].rect))
                    {
                        gameOver = true;
                        SaveHighScore(score);
                    }
                }

                laneMoveY += speed * 2;
                if (laneMoveY >= borderHeight * 2)
                    laneMoveY = 0;
            }

            DrawRectangle(left, 0, roadSize, screenHeight, gray);
            DrawRectangle(left, 0, borderWidth, screenHeight, red);
            DrawRectangle(left + roadSize - borderWidth, 0, borderWidth, screenHeight, red);
            for (int y = -borderHeight * 2; y < screenHeight; y += borderHeight * 2)
            {
                DrawRectangle(center, y + laneMoveY, borderWidth, borderHeight, white);
                DrawRectangle(right, y + laneMoveY, borderWidth, borderHeight, white);
            }
                        DrawTexture(player.texture, player.rect.x, player.rect.y, white);

            for (int i = 0; i < vehicleCount; i++)
            {
                DrawTexture(vehicles[i].texture, vehicles[i].rect.x, vehicles[i].rect.y, white);
            }

            DrawText(TextFormat("Score: %d", score), 50, 50, 40, white);
            DrawText(TextFormat("Speed: %d", speed), 50, 100, 40, white);

            if (gameOver)
            {
                int roadCenter = left + roadSize / 2;

                DrawTexture(crashImage, player.rect.x, player.rect.y - player.texture.height / 2, white);

                DrawText("GAME OVER", roadCenter - MeasureText("GAME OVER", 60) / 2, screenHeight / 4, 60, red);
                DrawText(TextFormat("Your Score: %d", score), roadCenter - MeasureText(TextFormat("Your Score: %d", score), 30) / 2, screenHeight / 4 + 80, 30, white);

                int highScore1 = LoadHighScore();
                DrawText(TextFormat("High Score: %d", highScore1), roadCenter - MeasureText(TextFormat("High Score: %d", highScore1), 30) / 2, screenHeight / 4 + 120, 30, white);

                DrawText("Play Again?", roadCenter - MeasureText("Play Again?", 40) / 2, screenHeight / 2 - 20, 40, GREEN);
                DrawText("Y - Restart", roadCenter - MeasureText("Y - Restart", 30) / 2, screenHeight / 2 + 50, 30, white);
                DrawText("N - Exit", roadCenter - MeasureText("N - Exit", 30) / 2, screenHeight / 2 + 100, 30, white);
                DrawText("Press 'Backspace' to return to the menu", roadCenter - MeasureText("Press 'Backspace' to return to the menu", 32) / 2, screenHeight / 2 + 150, 32, red);

                if (IsKeyPressed(KEY_Y))
                {
                    ResetGame(player, vehicles, vehicleCount, score, speed, gameOver, laneMoveY); 
                    gameOver = false;                                                            
                }

                if (IsKeyPressed(KEY_N))
                    break; 

                if (IsKeyPressed(KEY_BACKSPACE))
                {
                    ResetGame(player, vehicles, vehicleCount, score, speed, gameOver, laneMoveY); 
                    gameOver = false;                                                            
                    currentScreen = GameScreen::MENU;                                             
                }
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
