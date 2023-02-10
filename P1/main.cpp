#include <iostream>
#include <raylib.h>

using namespace std;

int main () {

    const int screenWidth = 800;
    const int screenHeight = 600;
    Image logo = LoadImage("./logo.png");
    ImageResize(&logo, 100, 100);

    int ball_x = 100;
    int ball_y = 100;
    int ball_speed_x = 5;
    int ball_speed_y = 5;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    InitAudioDevice();              // Initialize audio device

    Sound sound = LoadSound("sonido2.mp3");

    Texture2D texture = LoadTextureFromImage(logo); //Las texturas se deben declarar despues del InitWindow.
    SetTargetFPS(60);
    int i = 1;
    SetTextureFilter(texture, i);

    while (WindowShouldClose() == false){
        int windowWidth = GetScreenWidth();
        int windowHeight = GetScreenHeight();
        i += 1;
        BeginDrawing();
        ClearBackground(BLUE);
        ball_x += ball_speed_x;
        ball_y += ball_speed_y;

        if(ball_x + texture.width/2 >= windowWidth  || ball_x - texture.width/2 <= 0)
        {
            ball_speed_x *= -1;
            PlaySoundMulti(sound);
            SetTextureFilter(texture, i);
        }

        if(ball_y + texture.height/2 >= windowHeight  || ball_y - texture.height/2 <= 0)
        {
            ball_speed_y *= -1;
            PlaySoundMulti(sound);
            SetTextureFilter(texture, i);
        }

        DrawTexture(texture, ball_x - texture.width/2, ball_y - texture.height/2, WHITE);

        EndDrawing();
    }
    StopSoundMulti();
    UnloadSound(sound);
    CloseAudioDevice();
    
    UnloadTexture(texture);
    CloseWindow();
    return 0;
}


/*

#include <iostream>
#include <raylib.h>

#define NUM 5
#define TAM_INI 0.0f
#define TAM_AUM 2.0f
#define ROT_INI 0
#define ROT_AUM 5

using namespace std;

int main () {

    const int screenWidth = 800;
    const int screenHeight = 600;
    Image logo = LoadImage("./logo.png");
    ImageResize(&logo, 50, 50);

    int ball_x[NUM];
    int ball_y[NUM];
    int ball_speed_x[NUM];
    int ball_speed_y[NUM];
    float ball_size[NUM];
    int ball_rotation[NUM];

    for (int i = 0; i < NUM; i++) {
        ball_x[i] = screenWidth/2;
        ball_y[i] = screenHeight/2;
        ball_speed_x[i] = (rand() % 11) + -5;
        ball_speed_y[i] = (rand() % 11) + -5;
        ball_size[i] = TAM_INI + (rand() % 20);
        ball_rotation[i] = ROT_INI + (rand() % 3);
    }

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    Texture2D texture = LoadTextureFromImage(logo); //Las texturas se deben declarar despues del InitWindow.

    int frameWidth = texture.width;
    int frameHeight = texture.height;

    // Source rectangle (part of the texture to use for drawing)
    Rectangle sourceRec[NUM];

    // Destination rectangle (screen rectangle where drawing part of texture)
    Rectangle destRec[NUM];

    for (int i = 0; i < NUM; i++) {
        sourceRec[i] = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };
        destRec[i] = { screenWidth/2.0f, screenHeight/2.0f, frameWidth*2.0f, frameHeight*2.0f };
    }

    // Origin of the texture (rotation/scale point), it's relative to destination rectangle size
    Vector2 origin = { (float)frameWidth, (float)frameHeight };

    SetTargetFPS(60);

    while (WindowShouldClose() == false){

        int windowWidth = GetScreenWidth();
        int windowHeight = GetScreenHeight();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < NUM; i++) 
        {
            ball_x[i] += ball_speed_x[i];
            ball_y[i] += ball_speed_y[i];

            if(destRec[i].x + texture.width/2 >= windowWidth  || destRec[i].x - texture.width/2 <= 0)
            {
                sourceRec[i] = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };
                destRec[i] = { screenWidth/2.0f, screenHeight/2.0f, frameWidth*2.0f, frameHeight*2.0f };
            }

            if(destRec[i].y + texture.height/2 >= windowHeight  || destRec[i].y - texture.height/2 <= 0)
            {
                sourceRec[i] = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };
                destRec[i] = { screenWidth/2.0f, screenHeight/2.0f, frameWidth*2.0f, frameHeight*2.0f };
            }

            Vector2 position = { (float)(ball_x[i] - texture.width/2), (float)(ball_y[i] - texture.height/2)};
            ball_size[i] += TAM_AUM + (rand() % 3);
            ball_rotation[i] += ROT_AUM + (rand() % 10);
            //DrawTextureEx(texture, position, ball_rotation[i], ball_size[i], WHITE);
            //DrawTexturePro(texture, (Rectangle){ -25, -25, texture.width, texture.height }, 
            //    (Rectangle){ 25, 25, texture.width, texture.height },position, ball_rotation[i], WHITE);
            destRec[i].x += ball_speed_x[i];
            destRec[i].y += ball_speed_y[i];
            destRec[i].height += TAM_AUM;
            destRec[i].width += TAM_AUM;
            DrawTexturePro(texture, sourceRec[i], destRec[i], origin, (float)ball_rotation[i], WHITE);

            //DrawLine((int)destRec.x, 0, (int)destRec.x, screenHeight, GRAY);
            //DrawLine(0, (int)destRec.y, screenWidth, (int)destRec.y, GRAY);
            
        }

        EndDrawing();
    }

    UnloadTexture(texture);
    CloseWindow();
    return 0;
}
*/