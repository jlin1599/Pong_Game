#include <iostream>
#include <raylib.h>

using namespace std;

Color Maroon = Color{128, 0, 0, 255};
Color Dark_Maroon = Color{102, 0, 0, 255};
Color Light_Maroon = Color{153, 51, 51, 255};
Color Gold = Color{255, 215, 0, 255};

int player_score = 0;
int cpu_score = 0;

class Ball{
public:
    float x,y;
    int speed_x, speed_y;
    int radius;

    void Draw(){
        DrawCircle(x, y , radius, Gold);   //we took the original in the while loop and made a function, then called it there
    }

    void Update(){
        x += speed_x;    //this is the function that makes the balls move at the speed we made it in main()
        y += speed_y; 

        if (y + radius >= GetScreenHeight() || y - radius <= 0) {  // If ball hits the top or bottom of the window
            speed_y *= -1;  // Reverses the vertical speed (bounces the ball vertically)
        }
        if (x + radius >= GetScreenWidth()){
            cpu_score++;
            ResetBall();
        }
        
        if(x - radius <= 0) {  
            player_score++;
            ResetBall();
        }
    }

    void ResetBall(){
        x = GetScreenWidth()/2;
        y = GetScreenHeight()/2;

        int speed_choices[2] = {-1,1};
        speed_x *= speed_choices[GetRandomValue(0,1)];
        speed_y *= speed_choices[GetRandomValue(0,1)];
    }
};

class Paddle{

protected:

void LimitMovement(){
    if(y <= 0){
        y = 0;
    }
    if(y + height >= GetScreenHeight()){
        y = GetScreenHeight() - height;
    }
}

public:
    float x,y;
    float width,height;
    int speed;

    void Draw() {
        DrawRectangleRounded(Rectangle{x,y,width,height}, 0.8, 0, WHITE);
    }
    void Update() { 
        if(IsKeyDown(KEY_UP)){
            y = y - speed;
        }
        if(IsKeyDown(KEY_DOWN)){
            y = y + speed;
        }
        // this is just to make sure the paddles don't go outside so it fits

        LimitMovement();
    }
};

class CPUPaddle: public Paddle{
    public:

    void Update(int ball_y){
        if(y+height/2 > ball_y){
            y = y-speed;
        }
        if(y+height/2 <= ball_y){
            y = y+speed;
        }
        LimitMovement();
    }
};

Ball ball;
Paddle player;
CPUPaddle cpu;

int main() {

    cout << "Starting the game" << endl;
    const int screen_width = 1000;  //values of width/height don't change
    const int screen_height = 600;
    InitWindow(screen_width,screen_height,"My Pong Game!");   //this creates the window for the game

    SetTargetFPS(60); // how fast the game runs

    ball.radius = 20;
    ball.x = screen_width/2;
    ball.y = screen_height/2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    player.width = 25;
    player.height = 120;
    player.x = screen_width - player.width - 10;
    player.y = screen_height/2 - player.height/2;
    player.speed = 6;
    cpu.height = 120;
    cpu.width = 25;
    cpu.x =10;
    cpu.y = screen_height/2 - cpu.height/2;
    cpu.speed = 6;


    while(WindowShouldClose() == false){
        BeginDrawing(); //drawing game objects

        //Updating
        ball.Update();  // moves the ball
        player.Update();
        cpu.Update(ball.y);

        //Checking for collision with paddles
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius,Rectangle {player.x, player.y, player.width, player.height})){
            ball.speed_x *= -1; //reverses speed
        }
        if(CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius,Rectangle{cpu.x, cpu.y, cpu.width, cpu.height})){
            ball.speed_x *= -1; // reverses speed when hit
        }



        //Drawing
        ClearBackground(Dark_Maroon);
        DrawRectangle(screen_width/2, 0 , screen_width/2, screen_height, Maroon); //makes right side of screen regular green
        DrawCircle(screen_width/2, screen_height/2, 150, Light_Maroon);  //middle circle is light green
        DrawLine(screen_width/2 , 0 , screen_width/2, screen_height, WHITE); 
        ball.Draw();
        cpu.Draw();
        player.Draw();
        DrawText(TextFormat("%i",cpu_score), screen_width/4-20 , 20, 80, WHITE);
        DrawText(TextFormat("%i",player_score), 3 *screen_width/4-20 , 20, 80, WHITE);

        EndDrawing(); //ends the canvas drawing

    }

    CloseWindow();
    return 0;
}