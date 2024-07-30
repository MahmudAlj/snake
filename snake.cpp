#include <iostream>
#include "raylib.h"
#include <deque>
#include <raymath.h>

//1. Creating a blank canvas 8 Game Loop tamam 
//2. Creating the Food tamam
//3. Creating the Snake tamam
//4. Moving the Snake 
//5. Making the Snake eat the Food
//6. Making the Snake grow longer
//7. Checking for collision with edges 8 kail
//8. Adding kitle 8 frame
//9. Keeping score
//10. Adding sounds


Color blue = { 151 ,255 ,255 ,255 };
Color green = { 0, 0, 0, 255 };

int noktaboyutu = 30;
int noktsayimi = 25;

double lastUpdateTime = 0;

static bool eventTriggered(double interval) {
    double  currentTime = GetTime();
    if(currentTime - lastUpdateTime >= interval){
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

class Snake {
public:
    std::deque<Vector2> body = { Vector2{6,9}, Vector2{5,9}, Vector2{4,9} };
    Vector2 direction = { 1,0 };
    void Draw() {
        for (int i = 0; i < body.size(); i++) {
            float x = body[i].x;
            float y = body[i].y;
            Rectangle segment = Rectangle{x * noktaboyutu, y * noktaboyutu, float(noktaboyutu), float(noktaboyutu) };
            DrawRectangleRounded(segment,0.5,6,green);
        }
    }
    void Update() {
        body.pop_back();
        body.push_front(Vector2Add(body[0],direction));


    }
};
class Elma {
public:  
    Vector2 position = {4 ,6};
    Texture2D texture;

    Elma() {
        Image image = LoadImage("graph/gomb1.png");  // yapamadım
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = GenerateRandomPos();
    }

    ~Elma() {
        UnloadTexture(texture);
    }

    void Draw() {
       DrawTexture(texture, position.x * noktaboyutu, position.y * noktaboyutu, WHITE);
    }

    Vector2 GenerateRandomPos() {
        float x = GetRandomValue(0, noktsayimi - 1);
        float y = GetRandomValue(0, noktsayimi - 1);
        return Vector2{x, y};
    }
     
};
class Game {

public:
    Snake snake = Snake();
    Elma elma = Elma();

    void Draw() {
        elma.Draw();
        snake.Draw();
    }

    void Update() {
        snake.Update();
    }





};





int main(){
    InitWindow(noktaboyutu*noktsayimi, noktaboyutu * noktsayimi, "THE SNAKE");
    SetTargetFPS(120);

    Game game;
    while (WindowShouldClose() == false) {
       
        BeginDrawing();

        if (eventTriggered(0.1)) {
            game.Update();
        }
        if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1) {
            game.snake.direction = { 0, -1 };
        }
        if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1) {
            game.snake.direction = { 0, 1 };
        }
        if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1) {
            game.snake.direction = { -1, 0 };
        }
        if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1) {
            game.snake.direction = { 1, 0 };
        }

        //arka plan
        ClearBackground(blue);
        game.Draw();
        EndDrawing();
    }
    
  
    CloseWindow();
    return 0;
}

