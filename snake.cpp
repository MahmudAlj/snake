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

static int noktaboyutu = 30;
static int noktsayimi = 25;
static int offset = 75;

double lastUpdateTime = 0;

static bool ElementInDeque(Vector2 element, std::deque<Vector2> deque) {
    for (unsigned int i = 0; i < deque.size(); i++) {
        if (Vector2Equals(deque[i], element)) {
            return true;
        }
    }
    return false;
}

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
    bool addSegment = false;

    void Draw() {
        for (int i = 0; i < body.size(); i++) {
            float x = body[i].x;
            float y = body[i].y;
            Rectangle segment = Rectangle{offset + x * noktaboyutu, offset + y * noktaboyutu, float(noktaboyutu), float(noktaboyutu) };
            DrawRectangleRounded(segment,0.5,6,green);
        }
    }
    void Update() {
        body.push_front(Vector2Add(body[0], direction));
        if (addSegment == true) {
           
            addSegment = false;

        }
        else {
            body.pop_back();
        }
    }

    void Reset() {
        body = { Vector2{6,9}, Vector2{5,9}, Vector2{4,9} };
        direction = { 1,0 };
    }
};
class Elma {
public:  
    Vector2 position = {4 ,6};
    Texture2D texture;

    Elma(std::deque<Vector2> snakeBody) {
        Image image = LoadImage("graph/gomb1.png");  // yapamadım
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = GenerateRandomPos(snakeBody);
    }

    ~Elma() {
        UnloadTexture(texture);
    }

    void Draw() {
       DrawTexture(texture, offset + position.x * noktaboyutu, offset + position.y * noktaboyutu, WHITE);
    }

    Vector2 GenerateRandomhucre() {
        float x = GetRandomValue(0, noktsayimi - 1);
        float y = GetRandomValue(0, noktsayimi - 1);
        return Vector2{ x,y };
    }
    Vector2 GenerateRandomPos(std::deque<Vector2> snakeBody) {
       
        Vector2 position = GenerateRandomhucre();
        while (ElementInDeque(position, snakeBody)) {
            position = GenerateRandomhucre();
        }
        return position;
    }
     
};
class Game {

public:
    Snake snake = Snake();
    Elma elma = Elma(snake.body);
    bool running = true;
    int score = 0;

    void Draw() {
        elma.Draw();
        snake.Draw();
    }

    void Update() {
        snake.Update();
        CheckCollisionWithElma();
        CheckCollisionWithEdges();
        CheckCollisionWithTail();
    }

    void CheckCollisionWithElma() {
        if (Vector2Equals(snake.body[0], elma.position)) {
            elma.position = elma.GenerateRandomPos(snake.body);
            snake.addSegment = true;
            score ++;
        }
    }

    void CheckCollisionWithEdges() {
        if (snake.body[0].x == noktaboyutu || snake.body[0].x == -1) {
            GameOver();
        }
        if (snake.body[0].y == noktaboyutu || snake.body[0].y == -1) {
            GameOver();
        }
    }

    void GameOver() {
        std::cout << "game over" << std::endl;
        snake.Reset();
        elma.position = elma.GenerateRandomPos(snake.body);
        running = false;
        score = 0;
        //exit(1);
    }
    

    void CheckCollisionWithTail() {
        std::deque<Vector2> headlessBody = snake.body;
        headlessBody.pop_front();
        if (ElementInDeque(snake.body[0], headlessBody)) {
            GameOver();
        }
        
    
    }

};





int main(){
    InitWindow(2* offset + noktaboyutu * noktsayimi, 2 * offset + noktaboyutu * noktsayimi, "THE SNAKE");
    SetTargetFPS(120);

    Game game;
    while (WindowShouldClose() == false) {
       
        BeginDrawing();

        if (eventTriggered(0.1)) {
            game.Update();
        }
        if (IsKeyPressed(KEY_UP) && game.snake.direction.y != 1) {
            game.snake.direction = { 0, -1 };
            game.running = true;
        }
        if (IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1) {
            game.snake.direction = { 0, 1 };
            game.running = true;
        }
        if (IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1) {
            game.snake.direction = { -1, 0 };
            game.running = true;
        }
        if (IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1) {
            game.snake.direction = { 1, 0 };
            game.running = true;
        }

        //arka plan
        ClearBackground(blue);
        DrawRectangleLinesEx(Rectangle{(float)offset-5,(float)offset-5,(float)noktaboyutu* noktsayimi+10,(float)noktaboyutu * noktsayimi + 10 }, 5, green);
        game.Draw();
        DrawText("hello world", offset - 5, 20, 40, green);
        DrawText(TextFormat("%i", game.score), offset - 5, offset + noktaboyutu * noktsayimi + 10, 40, green);
        EndDrawing();
    }
    
  
    CloseWindow();
    return 0;
}

