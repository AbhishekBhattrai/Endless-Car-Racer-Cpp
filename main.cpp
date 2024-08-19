#include <iostream>
#include <raylib.h>
int main()
{

        Color red = {255, 0, 0, 255};
        
        SetTargetFPS(120);

        //initial position
        int ball_in_x_axis = 400;
        int ball_in_y_axis = 400;

        InitWindow(800, 800, "RAYLIB program!");
        while (WindowShouldClose() == false)
        {

                if (IsKeyDown(KEY_RIGHT))
                {
                        ball_in_x_axis += 3;
                }
                else if (IsKeyDown(KEY_LEFT))
                {
                        ball_in_x_axis -= 3;
                }
                if (IsKeyDown(KEY_UP))
                {
                        ball_in_y_axis -= 3;
                }
                else if (IsKeyDown(KEY_DOWN))
                {
                        ball_in_y_axis += 3;
                }

                BeginDrawing();
                ClearBackground(red);
                DrawCircle(ball_in_x_axis, ball_in_y_axis, 20, WHITE);
                EndDrawing();
        }

        CloseWindow();
}