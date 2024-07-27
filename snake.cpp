#include <iostream>
#include "raylib.h"


//1. Creating a blank canvas 8 Game Loop tamam 
//2. Creating the Food tamam
//3. Creating the Snake
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
     
private:


};

int main(){
    InitWindow(noktaboyutu*noktsayimi, noktaboyutu * noktsayimi, "hello for my game");
    SetTargetFPS(60);

    Elma elma;
    while (WindowShouldClose() == false) {
       
        BeginDrawing();

        //arka plan
        ClearBackground(blue);
        elma.Draw();
        EndDrawing();
    }

  
    CloseWindow();
    return 0;
}

