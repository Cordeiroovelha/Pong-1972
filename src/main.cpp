#include <raylib.h>

class Ball{
public:
    float x, y;
    int speed_x, speed_y, radius;

    void Draw(){
        DrawCircle(x, y, radius, WHITE);
    }

    void Updade(){
        x += speed_x;
        y += speed_y;

        if(y + radius >= GetScreenHeight() || y - radius <= 0)
            speed_y *= -1;
        if(x + radius >= GetScreenWidth() || x - radius <= 0)
            speed_x *= -1;
    }

    void Update(){

    }
};
class Player{
public:
    float x, y;
    float width, height;
    int speed;

    void Draw(){
        DrawRectangle(x, y, width, height, WHITE);
    }

    void Update(){
        if(IsKeyDown(KEY_UP))
            y = y-speed;
        if (IsKeyDown(KEY_DOWN))
            y = y + speed;
        
        LimitMovement();
    }

protected:
    void LimitMovement(){
        if(y <= 0)
            y = 0;
        if(y + height >= GetScreenHeight())
            y = GetScreenHeight() - height;
    }
};

class AI: public Player{
public:
    void Update(int ball_y){
        if(y + height/2 > ball_y)
            y = y - speed;
        if(y + height/2 <= ball_y)
            y = y + speed;
        
        LimitMovement();
    }
};

Ball ball;
Player player;
AI cpu;

int main(void){
    // inicialização da tela com as medidas, o nome do programa e o fps
    constexpr int scream_width{950}, scream_height{550};
    InitWindow(scream_width, scream_height, "Ping Pong");
    SetTargetFPS(60);

    ball.radius = 20;
    ball.x = scream_width / 2;
    ball.y = scream_height / 2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    player.width = 25;
    player.height = 120;
    player.x = 10;
    player.y = scream_height / 2 - player.height / 2;
    player.speed = 6;

    cpu.width = 25;
    cpu.height = 120;
    cpu.x = scream_width - cpu.width - 10;
    cpu.y = scream_height / 2 - cpu.height / 2;
    cpu.speed = 6;

    // Game Loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        // Event Handling


        // Updating Positions
        ball.Updade();
        player.Update();
        cpu.Update(ball.y);

        // Drawing
        
            ClearBackground(BLACK);

            DrawLine(scream_width / 2, 0,scream_width / 2, scream_height, WHITE);
            
            ball.Draw();

            player.Draw();
            cpu.Draw();
        EndDrawing();
    }
    
    // fecha o programa e a janela
    CloseWindow();
    return 0;
}